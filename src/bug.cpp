
// Make a catenary curve between two points
//
// A catenary is of the form y = a * cosh((x + k) / a) + c. We want to
// find the curve that passes between two points of different
// heights. This curve is determined by several parameters which may
// be hard to know, such as the maximum tension in the cable and its
// weight. Instead, we assume that the cable is a certain factor
// longer (slack )than the straight-line distance between the two
// attachment points.
//
// Arguments are in ECEF, orientation is at p1. We use that frame for
// the whole catenary.

namespace
{
    void toRow(osg::Matrixd& mat, osg::Vec3d& vec, int row)
    {
        for (int i = 0; i < 3; ++i)
        {
            mat(row, i) = vec[i];
        }
    }

    // Function for a in terms of arc length L, height difference h,
    // and horizontal distance d. This will be solved by a
    // Newton-Raphson solver, so we need both the function and its
    // derivative.

    struct GFunc
    {
        GFunc(double d_, double L, double h)
            : d(d_), rootLh(sqrt(L * L - h * h))
        {}

        double operator()(double a) const
        {
            return 2.0 * a * sinh(d / (2.0 * a)) - rootLh;
        }
        double d;
        double rootLh;
    };

    struct GFuncDeriv
    {
        GFuncDeriv(double d_)
            : d(d_)
        {
        }
        double operator()(double a) const
        {
            double da = d / a;
            return 2.0 * sinh(da/2.0) - da * cosh(da/2.0);
        }
        double d;
    };

    // Support around evaluating the catenary formula x = a * cosh((x + x1) / a) + C
    // and solving for the parameters a,x1, and C given the arc length of the curve L and the
    // horizontal and vertical displacement of the endpoints.
    struct CatenaryFunc
    {
        double a;
        double x1;
        double C;
        double L;
        double d;
        double h;
        CatenaryFunc(double a_, double x1_, double C_, double L_ = 0.0, double d_ = 0.0, double h_ = 0.0)
            : a(a_), x1(x1_), C(C_), L(L_), d(d_), h(h_)
        {
        }
        double operator()(double x) const
        {
            return a * cosh((x + x1) /a) + C;
        }
        static CatenaryFunc solveIt(double L, double d, double h)
        {
            GFunc gfunc(d, L, h);
            GFuncDeriv gfuncDeriv(d);
            bool validSoln = false;
            const double a = solve(gfunc, gfuncDeriv, d / 2, 1.0e-6, validSoln);
            // Parameters of the curve
            const double x1 = (a * log((L + h) / (L - h)) - d) / 2.0;
            const double C = -a * cosh(x1 / a);
            return CatenaryFunc(a, x1, C, L, d, h);
        }
    };
    // Find the difference between a catenary's minimum and refHeight. minHeight should be negative
    // i.e., below both towers in this usage.  d, h, and L are as in CatenaryFunc, but now L is a
    // free variable.
    struct MinCatHeight
    {
        double d;
        double h;
        double refHeight;
        MinCatHeight(double d_, double h_, double refHeight_ = 0.0)
            : d(d_), h(h_), refHeight(refHeight_)
        {
        }
        double operator()(double L) const
        {
            if (L * L < d * d + h * h)
            {
                // not happening
                return 0.0;
            }
            CatenaryFunc func = CatenaryFunc::solveIt(L, d, h);
            double minHeight = 0.0;
            if (func.x1 > 0.0)
            {
                // minimum is out of the range of the curve (x < 0)
                return 0.0;
            }
            // Could use func.a + func.C
            return (func(-func.x1) -refHeight);
        }
    };
}

void makeCatenary(osg::Vec3d p1, osg::Vec3d p2, const osg::Matrixd& orientation, double slack,
                  double maxSag,
                  std::vector<osg::Vec3d>& result, float tessellationSize)
{
    // Create a frame centered at p1 with orientation normal to
    // earth's surface
    osg::Matrixd FrameP1(orientation);
    toRow(FrameP1, p1, 3);
    // p1 in this frame is at origin. Get p2 into the local frame
    osg::Matrixd FrameP1Inv;
    FrameP1Inv.invert(FrameP1);
    osg::Vec3d p2local = p2 * FrameP1Inv;
    // The math for solving the catenary assumes that the higher point
    // is to the right on the X axis. Build a frame that reflects
    // that.
    //
    // If it turns out that p1 is higher, then at the end we will need
    // to generate points in reverse so that the resulting feature
    // makes sense.
    bool swapped = false;
    osg::Vec3d Xaxis;
    if (p2local.z() < 0.0)
    {
        swapped = true;
        Xaxis = osg::Vec3d(-p2local.x(), -p2local.y(), 0.0);
    }
    else
    {
        Xaxis = osg::Vec3d(p2local.x(), p2local.y(), 0.0);
    }
    // Horizontal distance between points
    const double d = Xaxis.normalize();
    osg::Vec3d Yaxis = osg::Vec3d(0.0, 0.0, 1.0) ^ Xaxis;
    osg::Matrixd FrameCat;
    toRow(FrameCat, Xaxis, 0);
    toRow(FrameCat, Yaxis, 1);
    // Height difference between points; should be positive
    double h = 0.0;
    if (swapped)
    {
        h = -p2local.z();
        toRow(FrameCat, p2local, 3);
    }
    else
    {
        h = p2local.z();
    }
    // straight distance between attachment points; obviously a lower limit on the cable length
    double straightDist = p2local.length();
    CatenaryFunc func = CatenaryFunc::solveIt(straightDist * slack, d, h);

    double xMin = -func.x1;
    double yMin = func(xMin);
    if (0.0 < xMin && yMin < -maxSag)
    {
        // Cable droops too much, so try a more expensive strategy
        MinCatHeight minimum(d, h, -maxSag);
        // No downside in choosing a very low lower bound
        double newGuess = ((slack - 1.0) * .01 + 1.0) * straightDist;
        // centimeter tolerence is fine
        double Lmin = solveBisect(minimum, newGuess, straightDist * slack, 0.01, 8);
        func = CatenaryFunc::solveIt(Lmin, d, h);
    }
    const osg::Vec3d P1(0.0, 0.0, 0.0), P2(d, 0.0, h);
    double begin, inc;
    int numSteps = ceil(p2local.length() / tessellationSize);
    std::vector<osg::Vec3d> cablePts;
    if (swapped)
    {
        inc = -d / numSteps;
        begin = d + inc;
        cablePts.push_back(P2);
    }
    else
    {
        inc = d / numSteps;
        begin = inc;
        cablePts.push_back(P1);
    }
    double x = begin;
    for (int i = 1; i <= numSteps; ++i, x += inc)
    {
        double z = func(x);
        cablePts.push_back(osg::Vec3d(x, 0.0, z));
    }
    osg::Matrixd cat2world = FrameCat * FrameP1;
    for (std::vector<osg::Vec3d>::iterator itr = cablePts.begin(), end = cablePts.end();
         itr != end;
         ++itr)
    {
        *itr = *itr * cat2world;
    }
    result.insert(result.end(), cablePts.begin(), cablePts.end());
}
