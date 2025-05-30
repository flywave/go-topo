#include <ifcparse/Ifc4x3.h>
#include <ifcparse/IfcSchema.h>
#include <string>

using namespace std::string_literals;
using namespace IfcParse;

declaration *IFC4X3_types[1311] = {nullptr};

const std::string strings[] = {
    "IfcAbsorbedDoseMeasure"s,
    "IfcAccelerationMeasure"s,
    "IfcActionRequestTypeEnum"s,
    "EMAIL"s,
    "FAX"s,
    "PHONE"s,
    "POST"s,
    "VERBAL"s,
    "USERDEFINED"s,
    "NOTDEFINED"s,
    "IfcActionSourceTypeEnum"s,
    "BRAKES"s,
    "BUOYANCY"s,
    "COMPLETION_G1"s,
    "CREEP"s,
    "CURRENT"s,
    "DEAD_LOAD_G"s,
    "EARTHQUAKE_E"s,
    "ERECTION"s,
    "FIRE"s,
    "ICE"s,
    "IMPACT"s,
    "IMPULSE"s,
    "LACK_OF_FIT"s,
    "LIVE_LOAD_Q"s,
    "PRESTRESSING_P"s,
    "PROPPING"s,
    "RAIN"s,
    "SETTLEMENT_U"s,
    "SHRINKAGE"s,
    "SNOW_S"s,
    "SYSTEM_IMPERFECTION"s,
    "TEMPERATURE_T"s,
    "TRANSPORT"s,
    "WAVE"s,
    "WIND_W"s,
    "IfcActionTypeEnum"s,
    "EXTRAORDINARY_A"s,
    "PERMANENT_G"s,
    "VARIABLE_Q"s,
    "IfcActuatorTypeEnum"s,
    "ELECTRICACTUATOR"s,
    "HANDOPERATEDACTUATOR"s,
    "HYDRAULICACTUATOR"s,
    "PNEUMATICACTUATOR"s,
    "THERMOSTATICACTUATOR"s,
    "IfcAddressTypeEnum"s,
    "DISTRIBUTIONPOINT"s,
    "HOME"s,
    "OFFICE"s,
    "SITE"s,
    "IfcAirTerminalBoxTypeEnum"s,
    "CONSTANTFLOW"s,
    "VARIABLEFLOWPRESSUREDEPENDANT"s,
    "VARIABLEFLOWPRESSUREINDEPENDANT"s,
    "IfcAirTerminalTypeEnum"s,
    "DIFFUSER"s,
    "GRILLE"s,
    "LOUVRE"s,
    "REGISTER"s,
    "IfcAirToAirHeatRecoveryTypeEnum"s,
    "FIXEDPLATECOUNTERFLOWEXCHANGER"s,
    "FIXEDPLATECROSSFLOWEXCHANGER"s,
    "FIXEDPLATEPARALLELFLOWEXCHANGER"s,
    "HEATPIPE"s,
    "ROTARYWHEEL"s,
    "RUNAROUNDCOILLOOP"s,
    "THERMOSIPHONCOILTYPEHEATEXCHANGERS"s,
    "THERMOSIPHONSEALEDTUBEHEATEXCHANGERS"s,
    "TWINTOWERENTHALPYRECOVERYLOOPS"s,
    "IfcAlarmTypeEnum"s,
    "BELL"s,
    "BREAKGLASSBUTTON"s,
    "LIGHT"s,
    "MANUALPULLBOX"s,
    "RAILWAYCROCODILE"s,
    "RAILWAYDETONATOR"s,
    "SIREN"s,
    "WHISTLE"s,
    "IfcAlignmentCantSegmentTypeEnum"s,
    "BLOSSCURVE"s,
    "CONSTANTCANT"s,
    "COSINECURVE"s,
    "HELMERTCURVE"s,
    "LINEARTRANSITION"s,
    "SINECURVE"s,
    "VIENNESEBEND"s,
    "IfcAlignmentHorizontalSegmentTypeEnum"s,
    "CIRCULARARC"s,
    "CLOTHOID"s,
    "CUBIC"s,
    "LINE"s,
    "IfcAlignmentTypeEnum"s,
    "IfcAlignmentVerticalSegmentTypeEnum"s,
    "CONSTANTGRADIENT"s,
    "PARABOLICARC"s,
    "IfcAmountOfSubstanceMeasure"s,
    "IfcAnalysisModelTypeEnum"s,
    "IN_PLANE_LOADING_2D"s,
    "LOADING_3D"s,
    "OUT_PLANE_LOADING_2D"s,
    "IfcAnalysisTheoryTypeEnum"s,
    "FIRST_ORDER_THEORY"s,
    "FULL_NONLINEAR_THEORY"s,
    "SECOND_ORDER_THEORY"s,
    "THIRD_ORDER_THEORY"s,
    "IfcAngularVelocityMeasure"s,
    "IfcAnnotationTypeEnum"s,
    "ASBUILTAREA"s,
    "ASBUILTLINE"s,
    "ASBUILTPOINT"s,
    "ASSUMEDAREA"s,
    "ASSUMEDLINE"s,
    "ASSUMEDPOINT"s,
    "NON_PHYSICAL_SIGNAL"s,
    "SUPERELEVATIONEVENT"s,
    "WIDTHEVENT"s,
    "IfcAreaDensityMeasure"s,
    "IfcAreaMeasure"s,
    "IfcArithmeticOperatorEnum"s,
    "ADD"s,
    "DIVIDE"s,
    "MULTIPLY"s,
    "SUBTRACT"s,
    "IfcAssemblyPlaceEnum"s,
    "FACTORY"s,
    "IfcAudioVisualApplianceTypeEnum"s,
    "AMPLIFIER"s,
    "CAMERA"s,
    "COMMUNICATIONTERMINAL"s,
    "DISPLAY"s,
    "MICROPHONE"s,
    "PLAYER"s,
    "PROJECTOR"s,
    "RECEIVER"s,
    "RECORDINGEQUIPMENT"s,
    "SPEAKER"s,
    "SWITCHER"s,
    "TELEPHONE"s,
    "TUNER"s,
    "IfcBSplineCurveForm"s,
    "CIRCULAR_ARC"s,
    "ELLIPTIC_ARC"s,
    "HYPERBOLIC_ARC"s,
    "PARABOLIC_ARC"s,
    "POLYLINE_FORM"s,
    "UNSPECIFIED"s,
    "IfcBSplineSurfaceForm"s,
    "CONICAL_SURF"s,
    "CYLINDRICAL_SURF"s,
    "GENERALISED_CONE"s,
    "PLANE_SURF"s,
    "QUADRIC_SURF"s,
    "RULED_SURF"s,
    "SPHERICAL_SURF"s,
    "SURF_OF_LINEAR_EXTRUSION"s,
    "SURF_OF_REVOLUTION"s,
    "TOROIDAL_SURF"s,
    "IfcBeamTypeEnum"s,
    "BEAM"s,
    "CORNICE"s,
    "DIAPHRAGM"s,
    "EDGEBEAM"s,
    "GIRDER_SEGMENT"s,
    "HATSTONE"s,
    "HOLLOWCORE"s,
    "JOIST"s,
    "LINTEL"s,
    "PIERCAP"s,
    "SPANDREL"s,
    "T_BEAM"s,
    "IfcBearingTypeDisplacementEnum"s,
    "FIXED_MOVEMENT"s,
    "FREE_MOVEMENT"s,
    "GUIDED_LONGITUDINAL"s,
    "GUIDED_TRANSVERSAL"s,
    "IfcBearingTypeEnum"s,
    "CYLINDRICAL"s,
    "DISK"s,
    "ELASTOMERIC"s,
    "GUIDE"s,
    "POT"s,
    "ROCKER"s,
    "ROLLER"s,
    "SPHERICAL"s,
    "IfcBenchmarkEnum"s,
    "EQUALTO"s,
    "GREATERTHAN"s,
    "GREATERTHANOREQUALTO"s,
    "INCLUDEDIN"s,
    "INCLUDES"s,
    "LESSTHAN"s,
    "LESSTHANOREQUALTO"s,
    "NOTEQUALTO"s,
    "NOTINCLUDEDIN"s,
    "NOTINCLUDES"s,
    "IfcBinary"s,
    "IfcBoilerTypeEnum"s,
    "STEAM"s,
    "WATER"s,
    "IfcBoolean"s,
    "IfcBooleanOperator"s,
    "DIFFERENCE"s,
    "INTERSECTION"s,
    "UNION"s,
    "IfcBridgePartTypeEnum"s,
    "ABUTMENT"s,
    "DECK"s,
    "DECK_SEGMENT"s,
    "FOUNDATION"s,
    "PIER"s,
    "PIER_SEGMENT"s,
    "PYLON"s,
    "SUBSTRUCTURE"s,
    "SUPERSTRUCTURE"s,
    "SURFACESTRUCTURE"s,
    "IfcBridgeTypeEnum"s,
    "ARCHED"s,
    "CABLE_STAYED"s,
    "CANTILEVER"s,
    "CULVERT"s,
    "FRAMEWORK"s,
    "GIRDER"s,
    "SUSPENSION"s,
    "TRUSS"s,
    "IfcBuildingElementPartTypeEnum"s,
    "APRON"s,
    "ARMOURUNIT"s,
    "INSULATION"s,
    "PRECASTPANEL"s,
    "SAFETYCAGE"s,
    "IfcBuildingElementProxyTypeEnum"s,
    "COMPLEX"s,
    "ELEMENT"s,
    "PARTIAL"s,
    "IfcBuildingSystemTypeEnum"s,
    "EROSIONPREVENTION"s,
    "FENESTRATION"s,
    "LOADBEARING"s,
    "OUTERSHELL"s,
    "PRESTRESSING"s,
    "REINFORCING"s,
    "SHADING"s,
    "IfcBuiltSystemTypeEnum"s,
    "MOORING"s,
    "RAILWAYLINE"s,
    "RAILWAYTRACK"s,
    "TRACKCIRCUIT"s,
    "IfcBurnerTypeEnum"s,
    "IfcCableCarrierFittingTypeEnum"s,
    "BEND"s,
    "CONNECTOR"s,
    "CROSS"s,
    "JUNCTION"s,
    "TEE"s,
    "TRANSITION"s,
    "IfcCableCarrierSegmentTypeEnum"s,
    "CABLEBRACKET"s,
    "CABLELADDERSEGMENT"s,
    "CABLETRAYSEGMENT"s,
    "CABLETRUNKINGSEGMENT"s,
    "CATENARYWIRE"s,
    "CONDUITSEGMENT"s,
    "DROPPER"s,
    "IfcCableFittingTypeEnum"s,
    "ENTRY"s,
    "EXIT"s,
    "FANOUT"s,
    "IfcCableSegmentTypeEnum"s,
    "BUSBARSEGMENT"s,
    "CABLESEGMENT"s,
    "CONDUCTORSEGMENT"s,
    "CONTACTWIRESEGMENT"s,
    "CORESEGMENT"s,
    "FIBERSEGMENT"s,
    "FIBERTUBE"s,
    "OPTICALCABLESEGMENT"s,
    "STITCHWIRE"s,
    "WIREPAIRSEGMENT"s,
    "IfcCaissonFoundationTypeEnum"s,
    "CAISSON"s,
    "WELL"s,
    "IfcCardinalPointReference"s,
    "IfcChangeActionEnum"s,
    "ADDED"s,
    "DELETED"s,
    "MODIFIED"s,
    "NOCHANGE"s,
    "IfcChillerTypeEnum"s,
    "AIRCOOLED"s,
    "HEATRECOVERY"s,
    "WATERCOOLED"s,
    "IfcChimneyTypeEnum"s,
    "IfcCoilTypeEnum"s,
    "DXCOOLINGCOIL"s,
    "ELECTRICHEATINGCOIL"s,
    "GASHEATINGCOIL"s,
    "HYDRONICCOIL"s,
    "STEAMHEATINGCOIL"s,
    "WATERCOOLINGCOIL"s,
    "WATERHEATINGCOIL"s,
    "IfcColumnTypeEnum"s,
    "COLUMN"s,
    "PIERSTEM"s,
    "PIERSTEM_SEGMENT"s,
    "PILASTER"s,
    "STANDCOLUMN"s,
    "IfcCommunicationsApplianceTypeEnum"s,
    "ANTENNA"s,
    "AUTOMATON"s,
    "COMPUTER"s,
    "GATEWAY"s,
    "INTELLIGENTPERIPHERAL"s,
    "IPNETWORKEQUIPMENT"s,
    "LINESIDEELECTRONICUNIT"s,
    "MODEM"s,
    "NETWORKAPPLIANCE"s,
    "NETWORKBRIDGE"s,
    "NETWORKHUB"s,
    "OPTICALLINETERMINAL"s,
    "OPTICALNETWORKUNIT"s,
    "PRINTER"s,
    "RADIOBLOCKCENTER"s,
    "REPEATER"s,
    "ROUTER"s,
    "SCANNER"s,
    "TELECOMMAND"s,
    "TELEPHONYEXCHANGE"s,
    "TRANSITIONCOMPONENT"s,
    "TRANSPONDER"s,
    "TRANSPORTEQUIPMENT"s,
    "IfcComplexNumber"s,
    "IfcComplexPropertyTemplateTypeEnum"s,
    "P_COMPLEX"s,
    "Q_COMPLEX"s,
    "IfcCompoundPlaneAngleMeasure"s,
    "IfcCompressorTypeEnum"s,
    "BOOSTER"s,
    "DYNAMIC"s,
    "HERMETIC"s,
    "OPENTYPE"s,
    "RECIPROCATING"s,
    "ROLLINGPISTON"s,
    "ROTARY"s,
    "ROTARYVANE"s,
    "SCROLL"s,
    "SEMIHERMETIC"s,
    "SINGLESCREW"s,
    "SINGLESTAGE"s,
    "TROCHOIDAL"s,
    "TWINSCREW"s,
    "WELDEDSHELLHERMETIC"s,
    "IfcCondenserTypeEnum"s,
    "EVAPORATIVECOOLED"s,
    "WATERCOOLEDBRAZEDPLATE"s,
    "WATERCOOLEDSHELLCOIL"s,
    "WATERCOOLEDSHELLTUBE"s,
    "WATERCOOLEDTUBEINTUBE"s,
    "IfcConnectionTypeEnum"s,
    "ATEND"s,
    "ATPATH"s,
    "ATSTART"s,
    "IfcConstraintEnum"s,
    "ADVISORY"s,
    "HARD"s,
    "SOFT"s,
    "IfcConstructionEquipmentResourceTypeEnum"s,
    "DEMOLISHING"s,
    "EARTHMOVING"s,
    "ERECTING"s,
    "HEATING"s,
    "LIGHTING"s,
    "PAVING"s,
    "PUMPING"s,
    "TRANSPORTING"s,
    "IfcConstructionMaterialResourceTypeEnum"s,
    "AGGREGATES"s,
    "CONCRETE"s,
    "DRYWALL"s,
    "FUEL"s,
    "GYPSUM"s,
    "MASONRY"s,
    "METAL"s,
    "PLASTIC"s,
    "WOOD"s,
    "IfcConstructionProductResourceTypeEnum"s,
    "ASSEMBLY"s,
    "FORMWORK"s,
    "IfcContextDependentMeasure"s,
    "IfcControllerTypeEnum"s,
    "FLOATING"s,
    "MULTIPOSITION"s,
    "PROGRAMMABLE"s,
    "PROPORTIONAL"s,
    "TWOPOSITION"s,
    "IfcConveyorSegmentTypeEnum"s,
    "BELTCONVEYOR"s,
    "BUCKETCONVEYOR"s,
    "CHUTECONVEYOR"s,
    "SCREWCONVEYOR"s,
    "IfcCooledBeamTypeEnum"s,
    "ACTIVE"s,
    "PASSIVE"s,
    "IfcCoolingTowerTypeEnum"s,
    "MECHANICALFORCEDDRAFT"s,
    "MECHANICALINDUCEDDRAFT"s,
    "NATURALDRAFT"s,
    "IfcCostItemTypeEnum"s,
    "IfcCostScheduleTypeEnum"s,
    "BUDGET"s,
    "COSTPLAN"s,
    "ESTIMATE"s,
    "PRICEDBILLOFQUANTITIES"s,
    "SCHEDULEOFRATES"s,
    "TENDER"s,
    "UNPRICEDBILLOFQUANTITIES"s,
    "IfcCountMeasure"s,
    "IfcCourseTypeEnum"s,
    "ARMOUR"s,
    "BALLASTBED"s,
    "CORE"s,
    "FILTER"s,
    "PAVEMENT"s,
    "PROTECTION"s,
    "IfcCoveringTypeEnum"s,
    "CEILING"s,
    "CLADDING"s,
    "COPING"s,
    "FLOORING"s,
    "MEMBRANE"s,
    "MOLDING"s,
    "ROOFING"s,
    "SKIRTINGBOARD"s,
    "SLEEVING"s,
    "TOPPING"s,
    "WRAPPING"s,
    "IfcCrewResourceTypeEnum"s,
    "IfcCurtainWallTypeEnum"s,
    "IfcCurvatureMeasure"s,
    "IfcCurveInterpolationEnum"s,
    "LINEAR"s,
    "LOG_LINEAR"s,
    "LOG_LOG"s,
    "IfcDamperTypeEnum"s,
    "BACKDRAFTDAMPER"s,
    "BALANCINGDAMPER"s,
    "BLASTDAMPER"s,
    "CONTROLDAMPER"s,
    "FIREDAMPER"s,
    "FIRESMOKEDAMPER"s,
    "FUMEHOODEXHAUST"s,
    "GRAVITYDAMPER"s,
    "GRAVITYRELIEFDAMPER"s,
    "RELIEFDAMPER"s,
    "SMOKEDAMPER"s,
    "IfcDataOriginEnum"s,
    "MEASURED"s,
    "PREDICTED"s,
    "SIMULATED"s,
    "IfcDate"s,
    "IfcDateTime"s,
    "IfcDayInMonthNumber"s,
    "IfcDayInWeekNumber"s,
    "IfcDerivedUnitEnum"s,
    "ACCELERATIONUNIT"s,
    "ANGULARVELOCITYUNIT"s,
    "AREADENSITYUNIT"s,
    "COMPOUNDPLANEANGLEUNIT"s,
    "CURVATUREUNIT"s,
    "DYNAMICVISCOSITYUNIT"s,
    "HEATFLUXDENSITYUNIT"s,
    "HEATINGVALUEUNIT"s,
    "INTEGERCOUNTRATEUNIT"s,
    "IONCONCENTRATIONUNIT"s,
    "ISOTHERMALMOISTURECAPACITYUNIT"s,
    "KINEMATICVISCOSITYUNIT"s,
    "LINEARFORCEUNIT"s,
    "LINEARMOMENTUNIT"s,
    "LINEARSTIFFNESSUNIT"s,
    "LINEARVELOCITYUNIT"s,
    "LUMINOUSINTENSITYDISTRIBUTIONUNIT"s,
    "MASSDENSITYUNIT"s,
    "MASSFLOWRATEUNIT"s,
    "MASSPERLENGTHUNIT"s,
    "MODULUSOFELASTICITYUNIT"s,
    "MODULUSOFLINEARSUBGRADEREACTIONUNIT"s,
    "MODULUSOFROTATIONALSUBGRADEREACTIONUNIT"s,
    "MODULUSOFSUBGRADEREACTIONUNIT"s,
    "MOISTUREDIFFUSIVITYUNIT"s,
    "MOLECULARWEIGHTUNIT"s,
    "MOMENTOFINERTIAUNIT"s,
    "PHUNIT"s,
    "PLANARFORCEUNIT"s,
    "ROTATIONALFREQUENCYUNIT"s,
    "ROTATIONALMASSUNIT"s,
    "ROTATIONALSTIFFNESSUNIT"s,
    "SECTIONAREAINTEGRALUNIT"s,
    "SECTIONMODULUSUNIT"s,
    "SHEARMODULUSUNIT"s,
    "SOUNDPOWERLEVELUNIT"s,
    "SOUNDPOWERUNIT"s,
    "SOUNDPRESSURELEVELUNIT"s,
    "SOUNDPRESSUREUNIT"s,
    "SPECIFICHEATCAPACITYUNIT"s,
    "TEMPERATUREGRADIENTUNIT"s,
    "TEMPERATURERATEOFCHANGEUNIT"s,
    "THERMALADMITTANCEUNIT"s,
    "THERMALCONDUCTANCEUNIT"s,
    "THERMALEXPANSIONCOEFFICIENTUNIT"s,
    "THERMALRESISTANCEUNIT"s,
    "THERMALTRANSMITTANCEUNIT"s,
    "TORQUEUNIT"s,
    "VAPORPERMEABILITYUNIT"s,
    "VOLUMETRICFLOWRATEUNIT"s,
    "WARPINGCONSTANTUNIT"s,
    "WARPINGMOMENTUNIT"s,
    "IfcDescriptiveMeasure"s,
    "IfcDimensionCount"s,
    "IfcDirectionSenseEnum"s,
    "NEGATIVE"s,
    "POSITIVE"s,
    "IfcDiscreteAccessoryTypeEnum"s,
    "ANCHORPLATE"s,
    "BIRDPROTECTION"s,
    "BRACKET"s,
    "CABLEARRANGER"s,
    "ELASTIC_CUSHION"s,
    "EXPANSION_JOINT_DEVICE"s,
    "FILLER"s,
    "FLASHING"s,
    "INSULATOR"s,
    "LOCK"s,
    "PANEL_STRENGTHENING"s,
    "POINTMACHINEMOUNTINGDEVICE"s,
    "POINT_MACHINE_LOCKING_DEVICE"s,
    "RAILBRACE"s,
    "RAILPAD"s,
    "RAIL_LUBRICATION"s,
    "RAIL_MECHANICAL_EQUIPMENT"s,
    "SHOE"s,
    "SLIDINGCHAIR"s,
    "SOUNDABSORPTION"s,
    "TENSIONINGEQUIPMENT"s,
    "IfcDistributionBoardTypeEnum"s,
    "CONSUMERUNIT"s,
    "DISPATCHINGBOARD"s,
    "DISTRIBUTIONBOARD"s,
    "DISTRIBUTIONFRAME"s,
    "MOTORCONTROLCENTRE"s,
    "SWITCHBOARD"s,
    "IfcDistributionChamberElementTypeEnum"s,
    "FORMEDDUCT"s,
    "INSPECTIONCHAMBER"s,
    "INSPECTIONPIT"s,
    "MANHOLE"s,
    "METERCHAMBER"s,
    "SUMP"s,
    "TRENCH"s,
    "VALVECHAMBER"s,
    "IfcDistributionPortTypeEnum"s,
    "CABLE"s,
    "CABLECARRIER"s,
    "DUCT"s,
    "PIPE"s,
    "WIRELESS"s,
    "IfcDistributionSystemEnum"s,
    "AIRCONDITIONING"s,
    "AUDIOVISUAL"s,
    "CATENARY_SYSTEM"s,
    "CHEMICAL"s,
    "CHILLEDWATER"s,
    "COMMUNICATION"s,
    "COMPRESSEDAIR"s,
    "CONDENSERWATER"s,
    "CONTROL"s,
    "CONVEYING"s,
    "DATA"s,
    "DISPOSAL"s,
    "DOMESTICCOLDWATER"s,
    "DOMESTICHOTWATER"s,
    "DRAINAGE"s,
    "EARTHING"s,
    "ELECTRICAL"s,
    "ELECTROACOUSTIC"s,
    "EXHAUST"s,
    "FIREPROTECTION"s,
    "FIXEDTRANSMISSIONNETWORK"s,
    "GAS"s,
    "HAZARDOUS"s,
    "LIGHTNINGPROTECTION"s,
    "MOBILENETWORK"s,
    "MONITORINGSYSTEM"s,
    "MUNICIPALSOLIDWASTE"s,
    "OIL"s,
    "OPERATIONAL"s,
    "OPERATIONALTELEPHONYSYSTEM"s,
    "OVERHEAD_CONTACTLINE_SYSTEM"s,
    "POWERGENERATION"s,
    "RAINWATER"s,
    "REFRIGERATION"s,
    "RETURN_CIRCUIT"s,
    "SECURITY"s,
    "SEWAGE"s,
    "SIGNAL"s,
    "STORMWATER"s,
    "TV"s,
    "VACUUM"s,
    "VENT"s,
    "VENTILATION"s,
    "WASTEWATER"s,
    "WATERSUPPLY"s,
    "IfcDocumentConfidentialityEnum"s,
    "CONFIDENTIAL"s,
    "PERSONAL"s,
    "PUBLIC"s,
    "RESTRICTED"s,
    "IfcDocumentStatusEnum"s,
    "DRAFT"s,
    "FINAL"s,
    "FINALDRAFT"s,
    "REVISION"s,
    "IfcDoorPanelOperationEnum"s,
    "DOUBLE_ACTING"s,
    "FIXEDPANEL"s,
    "FOLDING"s,
    "REVOLVING"s,
    "ROLLINGUP"s,
    "SLIDING"s,
    "SWINGING"s,
    "IfcDoorPanelPositionEnum"s,
    "LEFT"s,
    "MIDDLE"s,
    "RIGHT"s,
    "IfcDoorStyleConstructionEnum"s,
    "ALUMINIUM"s,
    "ALUMINIUM_PLASTIC"s,
    "ALUMINIUM_WOOD"s,
    "HIGH_GRADE_STEEL"s,
    "STEEL"s,
    "IfcDoorStyleOperationEnum"s,
    "DOUBLE_DOOR_DOUBLE_SWING"s,
    "DOUBLE_DOOR_FOLDING"s,
    "DOUBLE_DOOR_SINGLE_SWING"s,
    "DOUBLE_DOOR_SINGLE_SWING_OPPOSITE_LEFT"s,
    "DOUBLE_DOOR_SINGLE_SWING_OPPOSITE_RIGHT"s,
    "DOUBLE_DOOR_SLIDING"s,
    "DOUBLE_SWING_LEFT"s,
    "DOUBLE_SWING_RIGHT"s,
    "FOLDING_TO_LEFT"s,
    "FOLDING_TO_RIGHT"s,
    "SINGLE_SWING_LEFT"s,
    "SINGLE_SWING_RIGHT"s,
    "SLIDING_TO_LEFT"s,
    "SLIDING_TO_RIGHT"s,
    "IfcDoorTypeEnum"s,
    "BOOM_BARRIER"s,
    "DOOR"s,
    "GATE"s,
    "TRAPDOOR"s,
    "TURNSTILE"s,
    "IfcDoorTypeOperationEnum"s,
    "DOUBLE_PANEL_DOUBLE_SWING"s,
    "DOUBLE_PANEL_FOLDING"s,
    "DOUBLE_PANEL_LIFTING_VERTICAL"s,
    "DOUBLE_PANEL_SINGLE_SWING"s,
    "DOUBLE_PANEL_SINGLE_SWING_OPPOSITE_LEFT"s,
    "DOUBLE_PANEL_SINGLE_SWING_OPPOSITE_RIGHT"s,
    "DOUBLE_PANEL_SLIDING"s,
    "LIFTING_HORIZONTAL"s,
    "LIFTING_VERTICAL_LEFT"s,
    "LIFTING_VERTICAL_RIGHT"s,
    "REVOLVING_HORIZONTAL"s,
    "REVOLVING_VERTICAL"s,
    "SWING_FIXED_LEFT"s,
    "SWING_FIXED_RIGHT"s,
    "IfcDoseEquivalentMeasure"s,
    "IfcDuctFittingTypeEnum"s,
    "OBSTRUCTION"s,
    "IfcDuctSegmentTypeEnum"s,
    "FLEXIBLESEGMENT"s,
    "RIGIDSEGMENT"s,
    "IfcDuctSilencerTypeEnum"s,
    "FLATOVAL"s,
    "RECTANGULAR"s,
    "ROUND"s,
    "IfcDuration"s,
    "IfcDynamicViscosityMeasure"s,
    "IfcEarthworksCutTypeEnum"s,
    "BASE_EXCAVATION"s,
    "CUT"s,
    "DREDGING"s,
    "EXCAVATION"s,
    "OVEREXCAVATION"s,
    "PAVEMENTMILLING"s,
    "STEPEXCAVATION"s,
    "TOPSOILREMOVAL"s,
    "IfcEarthworksFillTypeEnum"s,
    "BACKFILL"s,
    "COUNTERWEIGHT"s,
    "EMBANKMENT"s,
    "SLOPEFILL"s,
    "SUBGRADE"s,
    "SUBGRADEBED"s,
    "TRANSITIONSECTION"s,
    "IfcElectricApplianceTypeEnum"s,
    "DISHWASHER"s,
    "ELECTRICCOOKER"s,
    "FREESTANDINGELECTRICHEATER"s,
    "FREESTANDINGFAN"s,
    "FREESTANDINGWATERCOOLER"s,
    "FREESTANDINGWATERHEATER"s,
    "FREEZER"s,
    "FRIDGE_FREEZER"s,
    "HANDDRYER"s,
    "KITCHENMACHINE"s,
    "MICROWAVE"s,
    "PHOTOCOPIER"s,
    "REFRIGERATOR"s,
    "TUMBLEDRYER"s,
    "VENDINGMACHINE"s,
    "WASHINGMACHINE"s,
    "IfcElectricCapacitanceMeasure"s,
    "IfcElectricChargeMeasure"s,
    "IfcElectricConductanceMeasure"s,
    "IfcElectricCurrentMeasure"s,
    "IfcElectricDistributionBoardTypeEnum"s,
    "IfcElectricFlowStorageDeviceTypeEnum"s,
    "BATTERY"s,
    "CAPACITOR"s,
    "CAPACITORBANK"s,
    "COMPENSATOR"s,
    "HARMONICFILTER"s,
    "INDUCTOR"s,
    "INDUCTORBANK"s,
    "RECHARGER"s,
    "UPS"s,
    "IfcElectricFlowTreatmentDeviceTypeEnum"s,
    "ELECTRONICFILTER"s,
    "IfcElectricGeneratorTypeEnum"s,
    "CHP"s,
    "ENGINEGENERATOR"s,
    "STANDALONE"s,
    "IfcElectricMotorTypeEnum"s,
    "DC"s,
    "INDUCTION"s,
    "POLYPHASE"s,
    "RELUCTANCESYNCHRONOUS"s,
    "SYNCHRONOUS"s,
    "IfcElectricResistanceMeasure"s,
    "IfcElectricTimeControlTypeEnum"s,
    "RELAY"s,
    "TIMECLOCK"s,
    "TIMEDELAY"s,
    "IfcElectricVoltageMeasure"s,
    "IfcElementAssemblyTypeEnum"s,
    "ACCESSORY_ASSEMBLY"s,
    "ARCH"s,
    "BEAM_GRID"s,
    "BRACED_FRAME"s,
    "CROSS_BRACING"s,
    "DILATATIONPANEL"s,
    "ENTRANCEWORKS"s,
    "GRID"s,
    "MAST"s,
    "RAIL_MECHANICAL_EQUIPMENT_ASSEMBLY"s,
    "REINFORCEMENT_UNIT"s,
    "RIGID_FRAME"s,
    "SHELTER"s,
    "SIGNALASSEMBLY"s,
    "SLAB_FIELD"s,
    "SUMPBUSTER"s,
    "SUPPORTINGASSEMBLY"s,
    "SUSPENSIONASSEMBLY"s,
    "TRACKPANEL"s,
    "TRACTION_SWITCHING_ASSEMBLY"s,
    "TRAFFIC_CALMING_DEVICE"s,
    "TURNOUTPANEL"s,
    "IfcElementCompositionEnum"s,
    "IfcEnergyMeasure"s,
    "IfcEngineTypeEnum"s,
    "EXTERNALCOMBUSTION"s,
    "INTERNALCOMBUSTION"s,
    "IfcEvaporativeCoolerTypeEnum"s,
    "DIRECTEVAPORATIVEAIRWASHER"s,
    "DIRECTEVAPORATIVEPACKAGEDROTARYAIRCOOLER"s,
    "DIRECTEVAPORATIVERANDOMMEDIAAIRCOOLER"s,
    "DIRECTEVAPORATIVERIGIDMEDIAAIRCOOLER"s,
    "DIRECTEVAPORATIVESLINGERSPACKAGEDAIRCOOLER"s,
    "INDIRECTDIRECTCOMBINATION"s,
    "INDIRECTEVAPORATIVECOOLINGTOWERORCOILCOOLER"s,
    "INDIRECTEVAPORATIVEPACKAGEAIRCOOLER"s,
    "INDIRECTEVAPORATIVEWETCOIL"s,
    "IfcEvaporatorTypeEnum"s,
    "DIRECTEXPANSION"s,
    "DIRECTEXPANSIONBRAZEDPLATE"s,
    "DIRECTEXPANSIONSHELLANDTUBE"s,
    "DIRECTEXPANSIONTUBEINTUBE"s,
    "FLOODEDSHELLANDTUBE"s,
    "SHELLANDCOIL"s,
    "IfcEventTriggerTypeEnum"s,
    "EVENTCOMPLEX"s,
    "EVENTMESSAGE"s,
    "EVENTRULE"s,
    "EVENTTIME"s,
    "IfcEventTypeEnum"s,
    "ENDEVENT"s,
    "INTERMEDIATEEVENT"s,
    "STARTEVENT"s,
    "IfcExternalSpatialElementTypeEnum"s,
    "EXTERNAL"s,
    "EXTERNAL_EARTH"s,
    "EXTERNAL_FIRE"s,
    "EXTERNAL_WATER"s,
    "IfcFacilityPartCommonTypeEnum"s,
    "ABOVEGROUND"s,
    "BELOWGROUND"s,
    "LEVELCROSSING"s,
    "SEGMENT"s,
    "TERMINAL"s,
    "IfcFacilityUsageEnum"s,
    "LATERAL"s,
    "LONGITUDINAL"s,
    "REGION"s,
    "VERTICAL"s,
    "IfcFanTypeEnum"s,
    "CENTRIFUGALAIRFOIL"s,
    "CENTRIFUGALBACKWARDINCLINEDCURVED"s,
    "CENTRIFUGALFORWARDCURVED"s,
    "CENTRIFUGALRADIAL"s,
    "PROPELLORAXIAL"s,
    "TUBEAXIAL"s,
    "VANEAXIAL"s,
    "IfcFastenerTypeEnum"s,
    "GLUE"s,
    "MORTAR"s,
    "WELD"s,
    "IfcFilterTypeEnum"s,
    "AIRPARTICLEFILTER"s,
    "COMPRESSEDAIRFILTER"s,
    "ODORFILTER"s,
    "OILFILTER"s,
    "STRAINER"s,
    "WATERFILTER"s,
    "IfcFireSuppressionTerminalTypeEnum"s,
    "BREECHINGINLET"s,
    "FIREHYDRANT"s,
    "FIREMONITOR"s,
    "HOSEREEL"s,
    "SPRINKLER"s,
    "SPRINKLERDEFLECTOR"s,
    "IfcFlowDirectionEnum"s,
    "SINK"s,
    "SOURCE"s,
    "SOURCEANDSINK"s,
    "IfcFlowInstrumentTypeEnum"s,
    "AMMETER"s,
    "COMBINED"s,
    "FREQUENCYMETER"s,
    "PHASEANGLEMETER"s,
    "POWERFACTORMETER"s,
    "PRESSUREGAUGE"s,
    "THERMOMETER"s,
    "VOLTMETER"s,
    "VOLTMETER_PEAK"s,
    "VOLTMETER_RMS"s,
    "IfcFlowMeterTypeEnum"s,
    "ENERGYMETER"s,
    "GASMETER"s,
    "OILMETER"s,
    "WATERMETER"s,
    "IfcFontStyle"s,
    "IfcFontVariant"s,
    "IfcFontWeight"s,
    "IfcFootingTypeEnum"s,
    "CAISSON_FOUNDATION"s,
    "FOOTING_BEAM"s,
    "PAD_FOOTING"s,
    "PILE_CAP"s,
    "STRIP_FOOTING"s,
    "IfcForceMeasure"s,
    "IfcFrequencyMeasure"s,
    "IfcFurnitureTypeEnum"s,
    "BED"s,
    "CHAIR"s,
    "DESK"s,
    "FILECABINET"s,
    "SHELF"s,
    "SOFA"s,
    "TABLE"s,
    "TECHNICALCABINET"s,
    "IfcGeographicElementTypeEnum"s,
    "SOIL_BORING_POINT"s,
    "TERRAIN"s,
    "VEGETATION"s,
    "IfcGeometricProjectionEnum"s,
    "ELEVATION_VIEW"s,
    "GRAPH_VIEW"s,
    "MODEL_VIEW"s,
    "PLAN_VIEW"s,
    "REFLECTED_PLAN_VIEW"s,
    "SECTION_VIEW"s,
    "SKETCH_VIEW"s,
    "IfcGeotechnicalStratumTypeEnum"s,
    "SOLID"s,
    "VOID"s,
    "IfcGlobalOrLocalEnum"s,
    "GLOBAL_COORDS"s,
    "LOCAL_COORDS"s,
    "IfcGloballyUniqueId"s,
    "IfcGridTypeEnum"s,
    "IRREGULAR"s,
    "RADIAL"s,
    "TRIANGULAR"s,
    "IfcHeatExchangerTypeEnum"s,
    "PLATE"s,
    "SHELLANDTUBE"s,
    "TURNOUTHEATING"s,
    "IfcHeatFluxDensityMeasure"s,
    "IfcHeatingValueMeasure"s,
    "IfcHumidifierTypeEnum"s,
    "ADIABATICAIRWASHER"s,
    "ADIABATICATOMIZING"s,
    "ADIABATICCOMPRESSEDAIRNOZZLE"s,
    "ADIABATICPAN"s,
    "ADIABATICRIGIDMEDIA"s,
    "ADIABATICULTRASONIC"s,
    "ADIABATICWETTEDELEMENT"s,
    "ASSISTEDBUTANE"s,
    "ASSISTEDELECTRIC"s,
    "ASSISTEDNATURALGAS"s,
    "ASSISTEDPROPANE"s,
    "ASSISTEDSTEAM"s,
    "STEAMINJECTION"s,
    "IfcIdentifier"s,
    "IfcIlluminanceMeasure"s,
    "IfcImpactProtectionDeviceTypeEnum"s,
    "BUMPER"s,
    "CRASHCUSHION"s,
    "DAMPINGSYSTEM"s,
    "FENDER"s,
    "IfcInductanceMeasure"s,
    "IfcInteger"s,
    "IfcIntegerCountRateMeasure"s,
    "IfcInterceptorTypeEnum"s,
    "CYCLONIC"s,
    "GREASE"s,
    "PETROL"s,
    "IfcInternalOrExternalEnum"s,
    "INTERNAL"s,
    "IfcInventoryTypeEnum"s,
    "ASSETINVENTORY"s,
    "FURNITUREINVENTORY"s,
    "SPACEINVENTORY"s,
    "IfcIonConcentrationMeasure"s,
    "IfcIsothermalMoistureCapacityMeasure"s,
    "IfcJunctionBoxTypeEnum"s,
    "POWER"s,
    "IfcKinematicViscosityMeasure"s,
    "IfcKnotType"s,
    "PIECEWISE_BEZIER_KNOTS"s,
    "QUASI_UNIFORM_KNOTS"s,
    "UNIFORM_KNOTS"s,
    "IfcLabel"s,
    "IfcLaborResourceTypeEnum"s,
    "ADMINISTRATION"s,
    "CARPENTRY"s,
    "CLEANING"s,
    "ELECTRIC"s,
    "FINISHING"s,
    "GENERAL"s,
    "HVAC"s,
    "LANDSCAPING"s,
    "PAINTING"s,
    "PLUMBING"s,
    "SITEGRADING"s,
    "STEELWORK"s,
    "SURVEYING"s,
    "IfcLampTypeEnum"s,
    "COMPACTFLUORESCENT"s,
    "FLUORESCENT"s,
    "HALOGEN"s,
    "HIGHPRESSUREMERCURY"s,
    "HIGHPRESSURESODIUM"s,
    "LED"s,
    "METALHALIDE"s,
    "OLED"s,
    "TUNGSTENFILAMENT"s,
    "IfcLanguageId"s,
    "IfcLayerSetDirectionEnum"s,
    "AXIS1"s,
    "AXIS2"s,
    "AXIS3"s,
    "IfcLengthMeasure"s,
    "IfcLightDistributionCurveEnum"s,
    "TYPE_A"s,
    "TYPE_B"s,
    "TYPE_C"s,
    "IfcLightEmissionSourceEnum"s,
    "LIGHTEMITTINGDIODE"s,
    "LOWPRESSURESODIUM"s,
    "LOWVOLTAGEHALOGEN"s,
    "MAINVOLTAGEHALOGEN"s,
    "IfcLightFixtureTypeEnum"s,
    "DIRECTIONSOURCE"s,
    "POINTSOURCE"s,
    "SECURITYLIGHTING"s,
    "IfcLinearForceMeasure"s,
    "IfcLinearMomentMeasure"s,
    "IfcLinearStiffnessMeasure"s,
    "IfcLinearVelocityMeasure"s,
    "IfcLiquidTerminalTypeEnum"s,
    "LOADINGARM"s,
    "IfcLoadGroupTypeEnum"s,
    "LOAD_CASE"s,
    "LOAD_COMBINATION"s,
    "LOAD_GROUP"s,
    "IfcLogical"s,
    "IfcLogicalOperatorEnum"s,
    "LOGICALAND"s,
    "LOGICALNOTAND"s,
    "LOGICALNOTOR"s,
    "LOGICALOR"s,
    "LOGICALXOR"s,
    "IfcLuminousFluxMeasure"s,
    "IfcLuminousIntensityDistributionMeasure"s,
    "IfcLuminousIntensityMeasure"s,
    "IfcMagneticFluxDensityMeasure"s,
    "IfcMagneticFluxMeasure"s,
    "IfcMarineFacilityTypeEnum"s,
    "BARRIERBEACH"s,
    "BREAKWATER"s,
    "CANAL"s,
    "DRYDOCK"s,
    "FLOATINGDOCK"s,
    "HYDROLIFT"s,
    "JETTY"s,
    "LAUNCHRECOVERY"s,
    "MARINEDEFENCE"s,
    "NAVIGATIONALCHANNEL"s,
    "PORT"s,
    "QUAY"s,
    "REVETMENT"s,
    "SHIPLIFT"s,
    "SHIPLOCK"s,
    "SHIPYARD"s,
    "SLIPWAY"s,
    "WATERWAY"s,
    "WATERWAYSHIPLIFT"s,
    "IfcMarinePartTypeEnum"s,
    "ABOVEWATERLINE"s,
    "ANCHORAGE"s,
    "APPROACHCHANNEL"s,
    "BELOWWATERLINE"s,
    "BERTHINGSTRUCTURE"s,
    "CHAMBER"s,
    "CILL_LEVEL"s,
    "COPELEVEL"s,
    "CREST"s,
    "GATEHEAD"s,
    "GUDINGSTRUCTURE"s,
    "HIGHWATERLINE"s,
    "LANDFIELD"s,
    "LEEWARDSIDE"s,
    "LOWWATERLINE"s,
    "MANUFACTURING"s,
    "NAVIGATIONALAREA"s,
    "SHIPTRANSFER"s,
    "STORAGEAREA"s,
    "VEHICLESERVICING"s,
    "WATERFIELD"s,
    "WEATHERSIDE"s,
    "IfcMassDensityMeasure"s,
    "IfcMassFlowRateMeasure"s,
    "IfcMassMeasure"s,
    "IfcMassPerLengthMeasure"s,
    "IfcMechanicalFastenerTypeEnum"s,
    "ANCHORBOLT"s,
    "BOLT"s,
    "CHAIN"s,
    "COUPLER"s,
    "DOWEL"s,
    "NAIL"s,
    "NAILPLATE"s,
    "RAILFASTENING"s,
    "RAILJOINT"s,
    "RIVET"s,
    "ROPE"s,
    "SCREW"s,
    "SHEARCONNECTOR"s,
    "STAPLE"s,
    "STUDSHEARCONNECTOR"s,
    "IfcMedicalDeviceTypeEnum"s,
    "AIRSTATION"s,
    "FEEDAIRUNIT"s,
    "OXYGENGENERATOR"s,
    "OXYGENPLANT"s,
    "VACUUMSTATION"s,
    "IfcMemberTypeEnum"s,
    "ARCH_SEGMENT"s,
    "BRACE"s,
    "CHORD"s,
    "COLLAR"s,
    "MEMBER"s,
    "MULLION"s,
    "PURLIN"s,
    "RAFTER"s,
    "STAY_CABLE"s,
    "STIFFENING_RIB"s,
    "STRINGER"s,
    "STRUCTURALCABLE"s,
    "STRUT"s,
    "STUD"s,
    "SUSPENDER"s,
    "SUSPENSION_CABLE"s,
    "TIEBAR"s,
    "IfcMobileTelecommunicationsApplianceTypeEnum"s,
    "ACCESSPOINT"s,
    "BASEBANDUNIT"s,
    "BASETRANSCEIVERSTATION"s,
    "E_UTRAN_NODE_B"s,
    "GATEWAY_GPRS_SUPPORT_NODE"s,
    "MASTERUNIT"s,
    "MOBILESWITCHINGCENTER"s,
    "MSCSERVER"s,
    "PACKETCONTROLUNIT"s,
    "REMOTERADIOUNIT"s,
    "REMOTEUNIT"s,
    "SERVICE_GPRS_SUPPORT_NODE"s,
    "SUBSCRIBERSERVER"s,
    "IfcModulusOfElasticityMeasure"s,
    "IfcModulusOfLinearSubgradeReactionMeasure"s,
    "IfcModulusOfRotationalSubgradeReactionMeasure"s,
    "IfcModulusOfRotationalSubgradeReactionSelect"s,
    "IfcModulusOfSubgradeReactionMeasure"s,
    "IfcModulusOfSubgradeReactionSelect"s,
    "IfcModulusOfTranslationalSubgradeReactionSelect"s,
    "IfcMoistureDiffusivityMeasure"s,
    "IfcMolecularWeightMeasure"s,
    "IfcMomentOfInertiaMeasure"s,
    "IfcMonetaryMeasure"s,
    "IfcMonthInYearNumber"s,
    "IfcMooringDeviceTypeEnum"s,
    "BOLLARD"s,
    "LINETENSIONER"s,
    "MAGNETICDEVICE"s,
    "MOORINGHOOKS"s,
    "VACUUMDEVICE"s,
    "IfcMotorConnectionTypeEnum"s,
    "BELTDRIVE"s,
    "COUPLING"s,
    "DIRECTDRIVE"s,
    "IfcNavigationElementTypeEnum"s,
    "BEACON"s,
    "BUOY"s,
    "IfcNonNegativeLengthMeasure"s,
    "IfcNumericMeasure"s,
    "IfcObjectTypeEnum"s,
    "ACTOR"s,
    "GROUP"s,
    "PROCESS"s,
    "PRODUCT"s,
    "PROJECT"s,
    "RESOURCE"s,
    "IfcObjectiveEnum"s,
    "CODECOMPLIANCE"s,
    "CODEWAIVER"s,
    "DESIGNINTENT"s,
    "HEALTHANDSAFETY"s,
    "MERGECONFLICT"s,
    "MODELVIEW"s,
    "PARAMETER"s,
    "REQUIREMENT"s,
    "SPECIFICATION"s,
    "TRIGGERCONDITION"s,
    "IfcOccupantTypeEnum"s,
    "ASSIGNEE"s,
    "ASSIGNOR"s,
    "LESSEE"s,
    "LESSOR"s,
    "LETTINGAGENT"s,
    "OWNER"s,
    "TENANT"s,
    "IfcOpeningElementTypeEnum"s,
    "OPENING"s,
    "RECESS"s,
    "IfcOutletTypeEnum"s,
    "AUDIOVISUALOUTLET"s,
    "COMMUNICATIONSOUTLET"s,
    "DATAOUTLET"s,
    "POWEROUTLET"s,
    "TELEPHONEOUTLET"s,
    "IfcPHMeasure"s,
    "IfcParameterValue"s,
    "IfcPavementTypeEnum"s,
    "FLEXIBLE"s,
    "RIGID"s,
    "IfcPerformanceHistoryTypeEnum"s,
    "IfcPermeableCoveringOperationEnum"s,
    "GRILL"s,
    "LOUVER"s,
    "SCREEN"s,
    "IfcPermitTypeEnum"s,
    "ACCESS"s,
    "BUILDING"s,
    "WORK"s,
    "IfcPhysicalOrVirtualEnum"s,
    "PHYSICAL"s,
    "VIRTUAL"s,
    "IfcPileConstructionEnum"s,
    "CAST_IN_PLACE"s,
    "COMPOSITE"s,
    "PRECAST_CONCRETE"s,
    "PREFAB_STEEL"s,
    "IfcPileTypeEnum"s,
    "BORED"s,
    "COHESION"s,
    "DRIVEN"s,
    "FRICTION"s,
    "JETGROUTING"s,
    "SUPPORT"s,
    "IfcPipeFittingTypeEnum"s,
    "IfcPipeSegmentTypeEnum"s,
    "GUTTER"s,
    "SPOOL"s,
    "IfcPlanarForceMeasure"s,
    "IfcPlaneAngleMeasure"s,
    "IfcPlateTypeEnum"s,
    "BASE_PLATE"s,
    "COVER_PLATE"s,
    "CURTAIN_PANEL"s,
    "FLANGE_PLATE"s,
    "GUSSET_PLATE"s,
    "SHEET"s,
    "SPLICE_PLATE"s,
    "STIFFENER_PLATE"s,
    "WEB_PLATE"s,
    "IfcPositiveInteger"s,
    "IfcPositiveLengthMeasure"s,
    "IfcPositivePlaneAngleMeasure"s,
    "IfcPowerMeasure"s,
    "IfcPreferredSurfaceCurveRepresentation"s,
    "CURVE3D"s,
    "PCURVE_S1"s,
    "PCURVE_S2"s,
    "IfcPresentableText"s,
    "IfcPressureMeasure"s,
    "IfcProcedureTypeEnum"s,
    "ADVICE_CAUTION"s,
    "ADVICE_NOTE"s,
    "ADVICE_WARNING"s,
    "CALIBRATION"s,
    "DIAGNOSTIC"s,
    "SHUTDOWN"s,
    "STARTUP"s,
    "IfcProfileTypeEnum"s,
    "AREA"s,
    "CURVE"s,
    "IfcProjectOrderTypeEnum"s,
    "CHANGEORDER"s,
    "MAINTENANCEWORKORDER"s,
    "MOVEORDER"s,
    "PURCHASEORDER"s,
    "WORKORDER"s,
    "IfcProjectedOrTrueLengthEnum"s,
    "PROJECTED_LENGTH"s,
    "TRUE_LENGTH"s,
    "IfcProjectionElementTypeEnum"s,
    "BLISTER"s,
    "DEVIATOR"s,
    "IfcPropertySetTemplateTypeEnum"s,
    "PSET_MATERIALDRIVEN"s,
    "PSET_OCCURRENCEDRIVEN"s,
    "PSET_PERFORMANCEDRIVEN"s,
    "PSET_PROFILEDRIVEN"s,
    "PSET_TYPEDRIVENONLY"s,
    "PSET_TYPEDRIVENOVERRIDE"s,
    "QTO_OCCURRENCEDRIVEN"s,
    "QTO_TYPEDRIVENONLY"s,
    "QTO_TYPEDRIVENOVERRIDE"s,
    "IfcProtectiveDeviceTrippingUnitTypeEnum"s,
    "ELECTROMAGNETIC"s,
    "ELECTRONIC"s,
    "RESIDUALCURRENT"s,
    "THERMAL"s,
    "IfcProtectiveDeviceTypeEnum"s,
    "ANTI_ARCING_DEVICE"s,
    "CIRCUITBREAKER"s,
    "EARTHINGSWITCH"s,
    "EARTHLEAKAGECIRCUITBREAKER"s,
    "FUSEDISCONNECTOR"s,
    "RESIDUALCURRENTCIRCUITBREAKER"s,
    "RESIDUALCURRENTSWITCH"s,
    "SPARKGAP"s,
    "VARISTOR"s,
    "VOLTAGELIMITER"s,
    "IfcPumpTypeEnum"s,
    "CIRCULATOR"s,
    "ENDSUCTION"s,
    "SPLITCASE"s,
    "SUBMERSIBLEPUMP"s,
    "SUMPPUMP"s,
    "VERTICALINLINE"s,
    "VERTICALTURBINE"s,
    "IfcRadioActivityMeasure"s,
    "IfcRailTypeEnum"s,
    "BLADE"s,
    "CHECKRAIL"s,
    "GUARDRAIL"s,
    "RACKRAIL"s,
    "RAIL"s,
    "STOCKRAIL"s,
    "IfcRailingTypeEnum"s,
    "BALUSTRADE"s,
    "FENCE"s,
    "HANDRAIL"s,
    "IfcRailwayPartTypeEnum"s,
    "DILATATIONSUPERSTRUCTURE"s,
    "LINESIDESTRUCTURE"s,
    "LINESIDESTRUCTUREPART"s,
    "PLAINTRACKSUPERSTRUCTURE"s,
    "TRACKSTRUCTURE"s,
    "TRACKSTRUCTUREPART"s,
    "TURNOUTSUPERSTRUCTURE"s,
    "IfcRailwayTypeEnum"s,
    "IfcRampFlightTypeEnum"s,
    "SPIRAL"s,
    "STRAIGHT"s,
    "IfcRampTypeEnum"s,
    "HALF_TURN_RAMP"s,
    "QUARTER_TURN_RAMP"s,
    "SPIRAL_RAMP"s,
    "STRAIGHT_RUN_RAMP"s,
    "TWO_QUARTER_TURN_RAMP"s,
    "TWO_STRAIGHT_RUN_RAMP"s,
    "IfcRatioMeasure"s,
    "IfcReal"s,
    "IfcRecurrenceTypeEnum"s,
    "BY_DAY_COUNT"s,
    "BY_WEEKDAY_COUNT"s,
    "DAILY"s,
    "MONTHLY_BY_DAY_OF_MONTH"s,
    "MONTHLY_BY_POSITION"s,
    "WEEKLY"s,
    "YEARLY_BY_DAY_OF_MONTH"s,
    "YEARLY_BY_POSITION"s,
    "IfcReferentTypeEnum"s,
    "BOUNDARY"s,
    "KILOPOINT"s,
    "LANDMARK"s,
    "MILEPOINT"s,
    "POSITION"s,
    "REFERENCEMARKER"s,
    "STATION"s,
    "IfcReflectanceMethodEnum"s,
    "BLINN"s,
    "FLAT"s,
    "GLASS"s,
    "MATT"s,
    "MIRROR"s,
    "PHONG"s,
    "STRAUSS"s,
    "IfcReinforcedSoilTypeEnum"s,
    "DYNAMICALLYCOMPACTED"s,
    "GROUTED"s,
    "REPLACED"s,
    "ROLLERCOMPACTED"s,
    "SURCHARGEPRELOADED"s,
    "VERTICALLYDRAINED"s,
    "IfcReinforcingBarRoleEnum"s,
    "ANCHORING"s,
    "EDGE"s,
    "LIGATURE"s,
    "MAIN"s,
    "PUNCHING"s,
    "RING"s,
    "SHEAR"s,
    "IfcReinforcingBarSurfaceEnum"s,
    "PLAIN"s,
    "TEXTURED"s,
    "IfcReinforcingBarTypeEnum"s,
    "SPACEBAR"s,
    "IfcReinforcingMeshTypeEnum"s,
    "IfcRoadPartTypeEnum"s,
    "BICYCLECROSSING"s,
    "BUS_STOP"s,
    "CARRIAGEWAY"s,
    "CENTRALISLAND"s,
    "CENTRALRESERVE"s,
    "HARDSHOULDER"s,
    "LAYBY"s,
    "PARKINGBAY"s,
    "PASSINGBAY"s,
    "PEDESTRIAN_CROSSING"s,
    "RAILWAYCROSSING"s,
    "REFUGEISLAND"s,
    "ROADSEGMENT"s,
    "ROADSIDE"s,
    "ROADSIDEPART"s,
    "ROADWAYPLATEAU"s,
    "ROUNDABOUT"s,
    "SHOULDER"s,
    "SIDEWALK"s,
    "SOFTSHOULDER"s,
    "TOLLPLAZA"s,
    "TRAFFICISLAND"s,
    "TRAFFICLANE"s,
    "IfcRoadTypeEnum"s,
    "IfcRoleEnum"s,
    "ARCHITECT"s,
    "BUILDINGOPERATOR"s,
    "BUILDINGOWNER"s,
    "CIVILENGINEER"s,
    "CLIENT"s,
    "COMMISSIONINGENGINEER"s,
    "CONSTRUCTIONMANAGER"s,
    "CONSULTANT"s,
    "CONTRACTOR"s,
    "COSTENGINEER"s,
    "ELECTRICALENGINEER"s,
    "ENGINEER"s,
    "FACILITIESMANAGER"s,
    "FIELDCONSTRUCTIONMANAGER"s,
    "MANUFACTURER"s,
    "MECHANICALENGINEER"s,
    "PROJECTMANAGER"s,
    "RESELLER"s,
    "STRUCTURALENGINEER"s,
    "SUBCONTRACTOR"s,
    "SUPPLIER"s,
    "IfcRoofTypeEnum"s,
    "BARREL_ROOF"s,
    "BUTTERFLY_ROOF"s,
    "DOME_ROOF"s,
    "FLAT_ROOF"s,
    "FREEFORM"s,
    "GABLE_ROOF"s,
    "GAMBREL_ROOF"s,
    "HIPPED_GABLE_ROOF"s,
    "HIP_ROOF"s,
    "MANSARD_ROOF"s,
    "PAVILION_ROOF"s,
    "RAINBOW_ROOF"s,
    "SHED_ROOF"s,
    "IfcRotationalFrequencyMeasure"s,
    "IfcRotationalMassMeasure"s,
    "IfcRotationalStiffnessMeasure"s,
    "IfcRotationalStiffnessSelect"s,
    "IfcSIPrefix"s,
    "ATTO"s,
    "CENTI"s,
    "DECA"s,
    "DECI"s,
    "EXA"s,
    "FEMTO"s,
    "GIGA"s,
    "HECTO"s,
    "KILO"s,
    "MEGA"s,
    "MICRO"s,
    "MILLI"s,
    "NANO"s,
    "PETA"s,
    "PICO"s,
    "TERA"s,
    "IfcSIUnitName"s,
    "AMPERE"s,
    "BECQUEREL"s,
    "CANDELA"s,
    "COULOMB"s,
    "CUBIC_METRE"s,
    "DEGREE_CELSIUS"s,
    "FARAD"s,
    "GRAM"s,
    "GRAY"s,
    "HENRY"s,
    "HERTZ"s,
    "JOULE"s,
    "KELVIN"s,
    "LUMEN"s,
    "LUX"s,
    "METRE"s,
    "MOLE"s,
    "NEWTON"s,
    "OHM"s,
    "PASCAL"s,
    "RADIAN"s,
    "SECOND"s,
    "SIEMENS"s,
    "SIEVERT"s,
    "SQUARE_METRE"s,
    "STERADIAN"s,
    "TESLA"s,
    "VOLT"s,
    "WATT"s,
    "WEBER"s,
    "IfcSanitaryTerminalTypeEnum"s,
    "BATH"s,
    "BIDET"s,
    "CISTERN"s,
    "SANITARYFOUNTAIN"s,
    "SHOWER"s,
    "TOILETPAN"s,
    "URINAL"s,
    "WASHHANDBASIN"s,
    "WCSEAT"s,
    "IfcSectionModulusMeasure"s,
    "IfcSectionTypeEnum"s,
    "TAPERED"s,
    "UNIFORM"s,
    "IfcSectionalAreaIntegralMeasure"s,
    "IfcSensorTypeEnum"s,
    "CO2SENSOR"s,
    "CONDUCTANCESENSOR"s,
    "CONTACTSENSOR"s,
    "COSENSOR"s,
    "EARTHQUAKESENSOR"s,
    "FIRESENSOR"s,
    "FLOWSENSOR"s,
    "FOREIGNOBJECTDETECTIONSENSOR"s,
    "FROSTSENSOR"s,
    "GASSENSOR"s,
    "HEATSENSOR"s,
    "HUMIDITYSENSOR"s,
    "IDENTIFIERSENSOR"s,
    "IONCONCENTRATIONSENSOR"s,
    "LEVELSENSOR"s,
    "LIGHTSENSOR"s,
    "MOISTURESENSOR"s,
    "MOVEMENTSENSOR"s,
    "OBSTACLESENSOR"s,
    "PHSENSOR"s,
    "PRESSURESENSOR"s,
    "RADIATIONSENSOR"s,
    "RADIOACTIVITYSENSOR"s,
    "RAINSENSOR"s,
    "SMOKESENSOR"s,
    "SNOWDEPTHSENSOR"s,
    "SOUNDSENSOR"s,
    "TEMPERATURESENSOR"s,
    "TRAINSENSOR"s,
    "TURNOUTCLOSURESENSOR"s,
    "WHEELSENSOR"s,
    "WINDSENSOR"s,
    "IfcSequenceEnum"s,
    "FINISH_FINISH"s,
    "FINISH_START"s,
    "START_FINISH"s,
    "START_START"s,
    "IfcShadingDeviceTypeEnum"s,
    "AWNING"s,
    "JALOUSIE"s,
    "SHUTTER"s,
    "IfcShearModulusMeasure"s,
    "IfcSignTypeEnum"s,
    "MARKER"s,
    "PICTORAL"s,
    "IfcSignalTypeEnum"s,
    "AUDIO"s,
    "MIXED"s,
    "VISUAL"s,
    "IfcSimplePropertyTemplateTypeEnum"s,
    "P_BOUNDEDVALUE"s,
    "P_ENUMERATEDVALUE"s,
    "P_LISTVALUE"s,
    "P_REFERENCEVALUE"s,
    "P_SINGLEVALUE"s,
    "P_TABLEVALUE"s,
    "Q_AREA"s,
    "Q_COUNT"s,
    "Q_LENGTH"s,
    "Q_NUMBER"s,
    "Q_TIME"s,
    "Q_VOLUME"s,
    "Q_WEIGHT"s,
    "IfcSlabTypeEnum"s,
    "APPROACH_SLAB"s,
    "BASESLAB"s,
    "FLOOR"s,
    "LANDING"s,
    "ROOF"s,
    "TRACKSLAB"s,
    "WEARING"s,
    "IfcSolarDeviceTypeEnum"s,
    "SOLARCOLLECTOR"s,
    "SOLARPANEL"s,
    "IfcSolidAngleMeasure"s,
    "IfcSoundPowerLevelMeasure"s,
    "IfcSoundPowerMeasure"s,
    "IfcSoundPressureLevelMeasure"s,
    "IfcSoundPressureMeasure"s,
    "IfcSpaceHeaterTypeEnum"s,
    "CONVECTOR"s,
    "RADIATOR"s,
    "IfcSpaceTypeEnum"s,
    "BERTH"s,
    "GFA"s,
    "PARKING"s,
    "SPACE"s,
    "IfcSpatialZoneTypeEnum"s,
    "CONSTRUCTION"s,
    "FIRESAFETY"s,
    "INTERFERENCE"s,
    "OCCUPANCY"s,
    "RESERVATION"s,
    "IfcSpecificHeatCapacityMeasure"s,
    "IfcSpecularExponent"s,
    "IfcSpecularRoughness"s,
    "IfcStackTerminalTypeEnum"s,
    "BIRDCAGE"s,
    "COWL"s,
    "RAINWATERHOPPER"s,
    "IfcStairFlightTypeEnum"s,
    "CURVED"s,
    "WINDER"s,
    "IfcStairTypeEnum"s,
    "CURVED_RUN_STAIR"s,
    "DOUBLE_RETURN_STAIR"s,
    "HALF_TURN_STAIR"s,
    "HALF_WINDING_STAIR"s,
    "LADDER"s,
    "QUARTER_TURN_STAIR"s,
    "QUARTER_WINDING_STAIR"s,
    "SPIRAL_STAIR"s,
    "STRAIGHT_RUN_STAIR"s,
    "THREE_QUARTER_TURN_STAIR"s,
    "THREE_QUARTER_WINDING_STAIR"s,
    "TWO_CURVED_RUN_STAIR"s,
    "TWO_QUARTER_TURN_STAIR"s,
    "TWO_QUARTER_WINDING_STAIR"s,
    "TWO_STRAIGHT_RUN_STAIR"s,
    "IfcStateEnum"s,
    "LOCKED"s,
    "READONLY"s,
    "READONLYLOCKED"s,
    "READWRITE"s,
    "READWRITELOCKED"s,
    "IfcStructuralCurveActivityTypeEnum"s,
    "CONST"s,
    "DISCRETE"s,
    "EQUIDISTANT"s,
    "PARABOLA"s,
    "POLYGONAL"s,
    "SINUS"s,
    "IfcStructuralCurveMemberTypeEnum"s,
    "COMPRESSION_MEMBER"s,
    "PIN_JOINED_MEMBER"s,
    "RIGID_JOINED_MEMBER"s,
    "TENSION_MEMBER"s,
    "IfcStructuralSurfaceActivityTypeEnum"s,
    "BILINEAR"s,
    "ISOCONTOUR"s,
    "IfcStructuralSurfaceMemberTypeEnum"s,
    "BENDING_ELEMENT"s,
    "MEMBRANE_ELEMENT"s,
    "SHELL"s,
    "IfcSubContractResourceTypeEnum"s,
    "PURCHASE"s,
    "IfcSurfaceFeatureTypeEnum"s,
    "DEFECT"s,
    "HATCHMARKING"s,
    "LINEMARKING"s,
    "MARK"s,
    "NONSKIDSURFACING"s,
    "PAVEMENTSURFACEMARKING"s,
    "RUMBLESTRIP"s,
    "SYMBOLMARKING"s,
    "TAG"s,
    "TRANSVERSERUMBLESTRIP"s,
    "TREATMENT"s,
    "IfcSurfaceSide"s,
    "BOTH"s,
    "IfcSwitchingDeviceTypeEnum"s,
    "CONTACTOR"s,
    "DIMMERSWITCH"s,
    "EMERGENCYSTOP"s,
    "KEYPAD"s,
    "MOMENTARYSWITCH"s,
    "SELECTORSWITCH"s,
    "STARTER"s,
    "START_AND_STOP_EQUIPMENT"s,
    "SWITCHDISCONNECTOR"s,
    "TOGGLESWITCH"s,
    "IfcSystemFurnitureElementTypeEnum"s,
    "PANEL"s,
    "SUBRACK"s,
    "WORKSURFACE"s,
    "IfcTankTypeEnum"s,
    "BASIN"s,
    "BREAKPRESSURE"s,
    "EXPANSION"s,
    "FEEDANDEXPANSION"s,
    "OILRETENTIONTRAY"s,
    "PRESSUREVESSEL"s,
    "STORAGE"s,
    "VESSEL"s,
    "IfcTaskDurationEnum"s,
    "ELAPSEDTIME"s,
    "WORKTIME"s,
    "IfcTaskTypeEnum"s,
    "ADJUSTMENT"s,
    "ATTENDANCE"s,
    "DEMOLITION"s,
    "DISMANTLE"s,
    "EMERGENCY"s,
    "INSPECTION"s,
    "INSTALLATION"s,
    "LOGISTIC"s,
    "MAINTENANCE"s,
    "MOVE"s,
    "OPERATION"s,
    "REMOVAL"s,
    "RENOVATION"s,
    "SAFETY"s,
    "TESTING"s,
    "TROUBLESHOOTING"s,
    "IfcTemperatureGradientMeasure"s,
    "IfcTemperatureRateOfChangeMeasure"s,
    "IfcTendonAnchorTypeEnum"s,
    "FIXED_END"s,
    "TENSIONING_END"s,
    "IfcTendonConduitTypeEnum"s,
    "DIABOLO"s,
    "GROUTING_DUCT"s,
    "TRUMPET"s,
    "IfcTendonTypeEnum"s,
    "BAR"s,
    "COATED"s,
    "STRAND"s,
    "WIRE"s,
    "IfcText"s,
    "IfcTextAlignment"s,
    "IfcTextDecoration"s,
    "IfcTextFontName"s,
    "IfcTextPath"s,
    "DOWN"s,
    "UP"s,
    "IfcTextTransformation"s,
    "IfcThermalAdmittanceMeasure"s,
    "IfcThermalConductivityMeasure"s,
    "IfcThermalExpansionCoefficientMeasure"s,
    "IfcThermalResistanceMeasure"s,
    "IfcThermalTransmittanceMeasure"s,
    "IfcThermodynamicTemperatureMeasure"s,
    "IfcTime"s,
    "IfcTimeMeasure"s,
    "IfcTimeOrRatioSelect"s,
    "IfcTimeSeriesDataTypeEnum"s,
    "CONTINUOUS"s,
    "DISCRETEBINARY"s,
    "PIECEWISEBINARY"s,
    "PIECEWISECONSTANT"s,
    "PIECEWISECONTINUOUS"s,
    "IfcTimeStamp"s,
    "IfcTorqueMeasure"s,
    "IfcTrackElementTypeEnum"s,
    "BLOCKINGDEVICE"s,
    "DERAILER"s,
    "FROG"s,
    "HALF_SET_OF_BLADES"s,
    "SLEEPER"s,
    "SPEEDREGULATOR"s,
    "TRACKENDOFALIGNMENT"s,
    "VEHICLESTOP"s,
    "IfcTransformerTypeEnum"s,
    "CHOPPER"s,
    "FREQUENCY"s,
    "INVERTER"s,
    "RECTIFIER"s,
    "VOLTAGE"s,
    "IfcTransitionCode"s,
    "CONTSAMEGRADIENT"s,
    "CONTSAMEGRADIENTSAMECURVATURE"s,
    "DISCONTINUOUS"s,
    "IfcTranslationalStiffnessSelect"s,
    "IfcTransportElementTypeEnum"s,
    "CRANEWAY"s,
    "ELEVATOR"s,
    "ESCALATOR"s,
    "HAULINGGEAR"s,
    "LIFTINGGEAR"s,
    "MOVINGWALKWAY"s,
    "IfcTrimmingPreference"s,
    "CARTESIAN"s,
    "IfcTubeBundleTypeEnum"s,
    "FINNED"s,
    "IfcURIReference"s,
    "IfcUnitEnum"s,
    "ABSORBEDDOSEUNIT"s,
    "AMOUNTOFSUBSTANCEUNIT"s,
    "AREAUNIT"s,
    "DOSEEQUIVALENTUNIT"s,
    "ELECTRICCAPACITANCEUNIT"s,
    "ELECTRICCHARGEUNIT"s,
    "ELECTRICCONDUCTANCEUNIT"s,
    "ELECTRICCURRENTUNIT"s,
    "ELECTRICRESISTANCEUNIT"s,
    "ELECTRICVOLTAGEUNIT"s,
    "ENERGYUNIT"s,
    "FORCEUNIT"s,
    "FREQUENCYUNIT"s,
    "ILLUMINANCEUNIT"s,
    "INDUCTANCEUNIT"s,
    "LENGTHUNIT"s,
    "LUMINOUSFLUXUNIT"s,
    "LUMINOUSINTENSITYUNIT"s,
    "MAGNETICFLUXDENSITYUNIT"s,
    "MAGNETICFLUXUNIT"s,
    "MASSUNIT"s,
    "PLANEANGLEUNIT"s,
    "POWERUNIT"s,
    "PRESSUREUNIT"s,
    "RADIOACTIVITYUNIT"s,
    "SOLIDANGLEUNIT"s,
    "THERMODYNAMICTEMPERATUREUNIT"s,
    "TIMEUNIT"s,
    "VOLUMEUNIT"s,
    "IfcUnitaryControlElementTypeEnum"s,
    "ALARMPANEL"s,
    "BASESTATIONCONTROLLER"s,
    "CONTROLPANEL"s,
    "GASDETECTIONPANEL"s,
    "HUMIDISTAT"s,
    "INDICATORPANEL"s,
    "MIMICPANEL"s,
    "THERMOSTAT"s,
    "WEATHERSTATION"s,
    "IfcUnitaryEquipmentTypeEnum"s,
    "AIRCONDITIONINGUNIT"s,
    "AIRHANDLER"s,
    "DEHUMIDIFIER"s,
    "ROOFTOPUNIT"s,
    "SPLITSYSTEM"s,
    "IfcValveTypeEnum"s,
    "AIRRELEASE"s,
    "ANTIVACUUM"s,
    "CHANGEOVER"s,
    "CHECK"s,
    "COMMISSIONING"s,
    "DIVERTING"s,
    "DOUBLECHECK"s,
    "DOUBLEREGULATING"s,
    "DRAWOFFCOCK"s,
    "FAUCET"s,
    "FLUSHING"s,
    "GASCOCK"s,
    "GASTAP"s,
    "ISOLATING"s,
    "MIXING"s,
    "PRESSUREREDUCING"s,
    "PRESSURERELIEF"s,
    "REGULATING"s,
    "SAFETYCUTOFF"s,
    "STEAMTRAP"s,
    "STOPCOCK"s,
    "IfcVaporPermeabilityMeasure"s,
    "IfcVehicleTypeEnum"s,
    "CARGO"s,
    "ROLLINGSTOCK"s,
    "VEHICLE"s,
    "VEHICLEAIR"s,
    "VEHICLEMARINE"s,
    "VEHICLETRACKED"s,
    "VEHICLEWHEELED"s,
    "IfcVibrationDamperTypeEnum"s,
    "AXIAL_YIELD"s,
    "BENDING_YIELD"s,
    "RUBBER"s,
    "SHEAR_YIELD"s,
    "VISCOUS"s,
    "IfcVibrationIsolatorTypeEnum"s,
    "BASE"s,
    "COMPRESSION"s,
    "SPRING"s,
    "IfcVirtualElementTypeEnum"s,
    "CLEARANCE"s,
    "PROVISIONFORVOID"s,
    "IfcVoidingFeatureTypeEnum"s,
    "CHAMFER"s,
    "CUTOUT"s,
    "HOLE"s,
    "MITER"s,
    "NOTCH"s,
    "IfcVolumeMeasure"s,
    "IfcVolumetricFlowRateMeasure"s,
    "IfcWallTypeEnum"s,
    "ELEMENTEDWALL"s,
    "MOVABLE"s,
    "PARAPET"s,
    "PARTITIONING"s,
    "PLUMBINGWALL"s,
    "RETAININGWALL"s,
    "SOLIDWALL"s,
    "STANDARD"s,
    "WAVEWALL"s,
    "IfcWarpingConstantMeasure"s,
    "IfcWarpingMomentMeasure"s,
    "IfcWarpingStiffnessSelect"s,
    "IfcWasteTerminalTypeEnum"s,
    "FLOORTRAP"s,
    "FLOORWASTE"s,
    "GULLYSUMP"s,
    "GULLYTRAP"s,
    "ROOFDRAIN"s,
    "WASTEDISPOSALUNIT"s,
    "WASTETRAP"s,
    "IfcWindowPanelOperationEnum"s,
    "BOTTOMHUNG"s,
    "FIXEDCASEMENT"s,
    "OTHEROPERATION"s,
    "PIVOTHORIZONTAL"s,
    "PIVOTVERTICAL"s,
    "REMOVABLECASEMENT"s,
    "SIDEHUNGLEFTHAND"s,
    "SIDEHUNGRIGHTHAND"s,
    "SLIDINGHORIZONTAL"s,
    "SLIDINGVERTICAL"s,
    "TILTANDTURNLEFTHAND"s,
    "TILTANDTURNRIGHTHAND"s,
    "TOPHUNG"s,
    "IfcWindowPanelPositionEnum"s,
    "BOTTOM"s,
    "TOP"s,
    "IfcWindowStyleConstructionEnum"s,
    "OTHER_CONSTRUCTION"s,
    "IfcWindowStyleOperationEnum"s,
    "DOUBLE_PANEL_HORIZONTAL"s,
    "DOUBLE_PANEL_VERTICAL"s,
    "SINGLE_PANEL"s,
    "TRIPLE_PANEL_BOTTOM"s,
    "TRIPLE_PANEL_HORIZONTAL"s,
    "TRIPLE_PANEL_LEFT"s,
    "TRIPLE_PANEL_RIGHT"s,
    "TRIPLE_PANEL_TOP"s,
    "TRIPLE_PANEL_VERTICAL"s,
    "IfcWindowTypeEnum"s,
    "LIGHTDOME"s,
    "SKYLIGHT"s,
    "WINDOW"s,
    "IfcWindowTypePartitioningEnum"s,
    "IfcWorkCalendarTypeEnum"s,
    "FIRSTSHIFT"s,
    "SECONDSHIFT"s,
    "THIRDSHIFT"s,
    "IfcWorkPlanTypeEnum"s,
    "ACTUAL"s,
    "BASELINE"s,
    "PLANNED"s,
    "IfcWorkScheduleTypeEnum"s,
    "IfcActorRole"s,
    "IfcAddress"s,
    "IfcAlignmentParameterSegment"s,
    "IfcAlignmentVerticalSegment"s,
    "IfcApplication"s,
    "IfcAppliedValue"s,
    "IfcApproval"s,
    "IfcBoundaryCondition"s,
    "IfcBoundaryEdgeCondition"s,
    "IfcBoundaryFaceCondition"s,
    "IfcBoundaryNodeCondition"s,
    "IfcBoundaryNodeConditionWarping"s,
    "IfcConnectionGeometry"s,
    "IfcConnectionPointGeometry"s,
    "IfcConnectionSurfaceGeometry"s,
    "IfcConnectionVolumeGeometry"s,
    "IfcConstraint"s,
    "IfcCoordinateOperation"s,
    "IfcCoordinateReferenceSystem"s,
    "IfcCostValue"s,
    "IfcDerivedUnit"s,
    "IfcDerivedUnitElement"s,
    "IfcDimensionalExponents"s,
    "IfcExternalInformation"s,
    "IfcExternalReference"s,
    "IfcExternallyDefinedHatchStyle"s,
    "IfcExternallyDefinedSurfaceStyle"s,
    "IfcExternallyDefinedTextFont"s,
    "IfcGridAxis"s,
    "IfcIrregularTimeSeriesValue"s,
    "IfcLibraryInformation"s,
    "IfcLibraryReference"s,
    "IfcLightDistributionData"s,
    "IfcLightIntensityDistribution"s,
    "IfcMapConversion"s,
    "IfcMaterialClassificationRelationship"s,
    "IfcMaterialDefinition"s,
    "IfcMaterialLayer"s,
    "IfcMaterialLayerSet"s,
    "IfcMaterialLayerWithOffsets"s,
    "IfcMaterialList"s,
    "IfcMaterialProfile"s,
    "IfcMaterialProfileSet"s,
    "IfcMaterialProfileWithOffsets"s,
    "IfcMaterialUsageDefinition"s,
    "IfcMeasureWithUnit"s,
    "IfcMetric"s,
    "IfcMonetaryUnit"s,
    "IfcNamedUnit"s,
    "IfcObjectPlacement"s,
    "IfcObjective"s,
    "IfcOrganization"s,
    "IfcOwnerHistory"s,
    "IfcPerson"s,
    "IfcPersonAndOrganization"s,
    "IfcPhysicalQuantity"s,
    "IfcPhysicalSimpleQuantity"s,
    "IfcPostalAddress"s,
    "IfcPresentationItem"s,
    "IfcPresentationLayerAssignment"s,
    "IfcPresentationLayerWithStyle"s,
    "IfcPresentationStyle"s,
    "IfcProductRepresentation"s,
    "IfcProfileDef"s,
    "IfcProjectedCRS"s,
    "IfcPropertyAbstraction"s,
    "IfcPropertyEnumeration"s,
    "IfcQuantityArea"s,
    "IfcQuantityCount"s,
    "IfcQuantityLength"s,
    "IfcQuantityNumber"s,
    "IfcQuantityTime"s,
    "IfcQuantityVolume"s,
    "IfcQuantityWeight"s,
    "IfcRecurrencePattern"s,
    "IfcReference"s,
    "IfcRepresentation"s,
    "IfcRepresentationContext"s,
    "IfcRepresentationItem"s,
    "IfcRepresentationMap"s,
    "IfcResourceLevelRelationship"s,
    "IfcRoot"s,
    "IfcSIUnit"s,
    "IfcSchedulingTime"s,
    "IfcShapeAspect"s,
    "IfcShapeModel"s,
    "IfcShapeRepresentation"s,
    "IfcStructuralConnectionCondition"s,
    "IfcStructuralLoad"s,
    "IfcStructuralLoadConfiguration"s,
    "IfcStructuralLoadOrResult"s,
    "IfcStructuralLoadStatic"s,
    "IfcStructuralLoadTemperature"s,
    "IfcStyleModel"s,
    "IfcStyledItem"s,
    "IfcStyledRepresentation"s,
    "IfcSurfaceReinforcementArea"s,
    "IfcSurfaceStyle"s,
    "IfcSurfaceStyleLighting"s,
    "IfcSurfaceStyleRefraction"s,
    "IfcSurfaceStyleShading"s,
    "IfcSurfaceStyleWithTextures"s,
    "IfcSurfaceTexture"s,
    "IfcTable"s,
    "IfcTableColumn"s,
    "IfcTableRow"s,
    "IfcTaskTime"s,
    "IfcTaskTimeRecurring"s,
    "IfcTelecomAddress"s,
    "IfcTextStyle"s,
    "IfcTextStyleForDefinedFont"s,
    "IfcTextStyleTextModel"s,
    "IfcTextureCoordinate"s,
    "IfcTextureCoordinateGenerator"s,
    "IfcTextureCoordinateIndices"s,
    "IfcTextureCoordinateIndicesWithVoids"s,
    "IfcTextureMap"s,
    "IfcTextureVertex"s,
    "IfcTextureVertexList"s,
    "IfcTimePeriod"s,
    "IfcTimeSeries"s,
    "IfcTimeSeriesValue"s,
    "IfcTopologicalRepresentationItem"s,
    "IfcTopologyRepresentation"s,
    "IfcUnitAssignment"s,
    "IfcVertex"s,
    "IfcVertexPoint"s,
    "IfcVirtualGridIntersection"s,
    "IfcWorkTime"s,
    "IfcActorSelect"s,
    "IfcArcIndex"s,
    "IfcBendingParameterSelect"s,
    "IfcBoxAlignment"s,
    "IfcCurveMeasureSelect"s,
    "IfcDerivedMeasureValue"s,
    "IfcLayeredItem"s,
    "IfcLibrarySelect"s,
    "IfcLightDistributionDataSourceSelect"s,
    "IfcLineIndex"s,
    "IfcMaterialSelect"s,
    "IfcNormalisedRatioMeasure"s,
    "IfcObjectReferenceSelect"s,
    "IfcPositiveRatioMeasure"s,
    "IfcSegmentIndexSelect"s,
    "IfcSimpleValue"s,
    "IfcSizeSelect"s,
    "IfcSpecularHighlightSelect"s,
    "IfcSurfaceStyleElementSelect"s,
    "IfcUnit"s,
    "IfcAlignmentCantSegment"s,
    "IfcAlignmentHorizontalSegment"s,
    "IfcApprovalRelationship"s,
    "IfcArbitraryClosedProfileDef"s,
    "IfcArbitraryOpenProfileDef"s,
    "IfcArbitraryProfileDefWithVoids"s,
    "IfcBlobTexture"s,
    "IfcCenterLineProfileDef"s,
    "IfcClassification"s,
    "IfcClassificationReference"s,
    "IfcColourRgbList"s,
    "IfcColourSpecification"s,
    "IfcCompositeProfileDef"s,
    "IfcConnectedFaceSet"s,
    "IfcConnectionCurveGeometry"s,
    "IfcConnectionPointEccentricity"s,
    "IfcContextDependentUnit"s,
    "IfcConversionBasedUnit"s,
    "IfcConversionBasedUnitWithOffset"s,
    "IfcCurrencyRelationship"s,
    "IfcCurveStyle"s,
    "IfcCurveStyleFont"s,
    "IfcCurveStyleFontAndScaling"s,
    "IfcCurveStyleFontPattern"s,
    "IfcDerivedProfileDef"s,
    "IfcDocumentInformation"s,
    "IfcDocumentInformationRelationship"s,
    "IfcDocumentReference"s,
    "IfcEdge"s,
    "IfcEdgeCurve"s,
    "IfcEventTime"s,
    "IfcExtendedProperties"s,
    "IfcExternalReferenceRelationship"s,
    "IfcFace"s,
    "IfcFaceBound"s,
    "IfcFaceOuterBound"s,
    "IfcFaceSurface"s,
    "IfcFailureConnectionCondition"s,
    "IfcFillAreaStyle"s,
    "IfcGeometricRepresentationContext"s,
    "IfcGeometricRepresentationItem"s,
    "IfcGeometricRepresentationSubContext"s,
    "IfcGeometricSet"s,
    "IfcGridPlacement"s,
    "IfcHalfSpaceSolid"s,
    "IfcImageTexture"s,
    "IfcIndexedColourMap"s,
    "IfcIndexedTextureMap"s,
    "IfcIndexedTriangleTextureMap"s,
    "IfcIrregularTimeSeries"s,
    "IfcLagTime"s,
    "IfcLightSource"s,
    "IfcLightSourceAmbient"s,
    "IfcLightSourceDirectional"s,
    "IfcLightSourceGoniometric"s,
    "IfcLightSourcePositional"s,
    "IfcLightSourceSpot"s,
    "IfcLinearPlacement"s,
    "IfcLocalPlacement"s,
    "IfcLoop"s,
    "IfcMappedItem"s,
    "IfcMaterial"s,
    "IfcMaterialConstituent"s,
    "IfcMaterialConstituentSet"s,
    "IfcMaterialDefinitionRepresentation"s,
    "IfcMaterialLayerSetUsage"s,
    "IfcMaterialProfileSetUsage"s,
    "IfcMaterialProfileSetUsageTapering"s,
    "IfcMaterialProperties"s,
    "IfcMaterialRelationship"s,
    "IfcMirroredProfileDef"s,
    "IfcObjectDefinition"s,
    "IfcOpenCrossProfileDef"s,
    "IfcOpenShell"s,
    "IfcOrganizationRelationship"s,
    "IfcOrientedEdge"s,
    "IfcParameterizedProfileDef"s,
    "IfcPath"s,
    "IfcPhysicalComplexQuantity"s,
    "IfcPixelTexture"s,
    "IfcPlacement"s,
    "IfcPlanarExtent"s,
    "IfcPoint"s,
    "IfcPointByDistanceExpression"s,
    "IfcPointOnCurve"s,
    "IfcPointOnSurface"s,
    "IfcPolyLoop"s,
    "IfcPolygonalBoundedHalfSpace"s,
    "IfcPreDefinedItem"s,
    "IfcPreDefinedProperties"s,
    "IfcPreDefinedTextFont"s,
    "IfcProductDefinitionShape"s,
    "IfcProfileProperties"s,
    "IfcProperty"s,
    "IfcPropertyDefinition"s,
    "IfcPropertyDependencyRelationship"s,
    "IfcPropertySetDefinition"s,
    "IfcPropertyTemplateDefinition"s,
    "IfcQuantitySet"s,
    "IfcRectangleProfileDef"s,
    "IfcRegularTimeSeries"s,
    "IfcReinforcementBarProperties"s,
    "IfcRelationship"s,
    "IfcResourceApprovalRelationship"s,
    "IfcResourceConstraintRelationship"s,
    "IfcResourceTime"s,
    "IfcRoundedRectangleProfileDef"s,
    "IfcSectionProperties"s,
    "IfcSectionReinforcementProperties"s,
    "IfcSectionedSpine"s,
    "IfcSegment"s,
    "IfcShellBasedSurfaceModel"s,
    "IfcSimpleProperty"s,
    "IfcSlippageConnectionCondition"s,
    "IfcSolidModel"s,
    "IfcStructuralLoadLinearForce"s,
    "IfcStructuralLoadPlanarForce"s,
    "IfcStructuralLoadSingleDisplacement"s,
    "IfcStructuralLoadSingleDisplacementDistortion"s,
    "IfcStructuralLoadSingleForce"s,
    "IfcStructuralLoadSingleForceWarping"s,
    "IfcSubedge"s,
    "IfcSurface"s,
    "IfcSurfaceStyleRendering"s,
    "IfcSweptAreaSolid"s,
    "IfcSweptDiskSolid"s,
    "IfcSweptDiskSolidPolygonal"s,
    "IfcSweptSurface"s,
    "IfcTShapeProfileDef"s,
    "IfcTessellatedItem"s,
    "IfcTextLiteral"s,
    "IfcTextLiteralWithExtent"s,
    "IfcTextStyleFontModel"s,
    "IfcTrapeziumProfileDef"s,
    "IfcTypeObject"s,
    "IfcTypeProcess"s,
    "IfcTypeProduct"s,
    "IfcTypeResource"s,
    "IfcUShapeProfileDef"s,
    "IfcVector"s,
    "IfcVertexLoop"s,
    "IfcZShapeProfileDef"s,
    "IfcClassificationReferenceSelect"s,
    "IfcClassificationSelect"s,
    "IfcCoordinateReferenceSystemSelect"s,
    "IfcDefinitionSelect"s,
    "IfcDocumentSelect"s,
    "IfcHatchLineDistanceSelect"s,
    "IfcMeasureValue"s,
    "IfcPointOrVertexPoint"s,
    "IfcProductRepresentationSelect"s,
    "IfcPropertySetDefinitionSet"s,
    "IfcResourceObjectSelect"s,
    "IfcTextFontSelect"s,
    "IfcValue"s,
    "IfcAdvancedFace"s,
    "IfcAnnotationFillArea"s,
    "IfcAsymmetricIShapeProfileDef"s,
    "IfcAxis1Placement"s,
    "IfcAxis2Placement2D"s,
    "IfcAxis2Placement3D"s,
    "IfcAxis2PlacementLinear"s,
    "IfcBooleanResult"s,
    "IfcBoundedSurface"s,
    "IfcBoundingBox"s,
    "IfcBoxedHalfSpace"s,
    "IfcCShapeProfileDef"s,
    "IfcCartesianPoint"s,
    "IfcCartesianPointList"s,
    "IfcCartesianPointList2D"s,
    "IfcCartesianPointList3D"s,
    "IfcCartesianTransformationOperator"s,
    "IfcCartesianTransformationOperator2D"s,
    "IfcCartesianTransformationOperator2DnonUniform"s,
    "IfcCartesianTransformationOperator3D"s,
    "IfcCartesianTransformationOperator3DnonUniform"s,
    "IfcCircleProfileDef"s,
    "IfcClosedShell"s,
    "IfcColourRgb"s,
    "IfcComplexProperty"s,
    "IfcCompositeCurveSegment"s,
    "IfcConstructionResourceType"s,
    "IfcContext"s,
    "IfcCrewResourceType"s,
    "IfcCsgPrimitive3D"s,
    "IfcCsgSolid"s,
    "IfcCurve"s,
    "IfcCurveBoundedPlane"s,
    "IfcCurveBoundedSurface"s,
    "IfcCurveSegment"s,
    "IfcDirection"s,
    "IfcDirectrixCurveSweptAreaSolid"s,
    "IfcEdgeLoop"s,
    "IfcElementQuantity"s,
    "IfcElementType"s,
    "IfcElementarySurface"s,
    "IfcEllipseProfileDef"s,
    "IfcEventType"s,
    "IfcExtrudedAreaSolid"s,
    "IfcExtrudedAreaSolidTapered"s,
    "IfcFaceBasedSurfaceModel"s,
    "IfcFillAreaStyleHatching"s,
    "IfcFillAreaStyleTiles"s,
    "IfcFixedReferenceSweptAreaSolid"s,
    "IfcFurnishingElementType"s,
    "IfcFurnitureType"s,
    "IfcGeographicElementType"s,
    "IfcGeometricCurveSet"s,
    "IfcIShapeProfileDef"s,
    "IfcIndexedPolygonalFace"s,
    "IfcIndexedPolygonalFaceWithVoids"s,
    "IfcIndexedPolygonalTextureMap"s,
    "IfcLShapeProfileDef"s,
    "IfcLaborResourceType"s,
    "IfcLine"s,
    "IfcManifoldSolidBrep"s,
    "IfcObject"s,
    "IfcOffsetCurve"s,
    "IfcOffsetCurve2D"s,
    "IfcOffsetCurve3D"s,
    "IfcOffsetCurveByDistances"s,
    "IfcPcurve"s,
    "IfcPlanarBox"s,
    "IfcPlane"s,
    "IfcPolynomialCurve"s,
    "IfcPreDefinedColour"s,
    "IfcPreDefinedCurveFont"s,
    "IfcPreDefinedPropertySet"s,
    "IfcProcedureType"s,
    "IfcProcess"s,
    "IfcProduct"s,
    "IfcProject"s,
    "IfcProjectLibrary"s,
    "IfcPropertyBoundedValue"s,
    "IfcPropertyEnumeratedValue"s,
    "IfcPropertyListValue"s,
    "IfcPropertyReferenceValue"s,
    "IfcPropertySet"s,
    "IfcPropertySetTemplate"s,
    "IfcPropertySingleValue"s,
    "IfcPropertyTableValue"s,
    "IfcPropertyTemplate"s,
    "IfcRectangleHollowProfileDef"s,
    "IfcRectangularPyramid"s,
    "IfcRectangularTrimmedSurface"s,
    "IfcReinforcementDefinitionProperties"s,
    "IfcRelAssigns"s,
    "IfcRelAssignsToActor"s,
    "IfcRelAssignsToControl"s,
    "IfcRelAssignsToGroup"s,
    "IfcRelAssignsToGroupByFactor"s,
    "IfcRelAssignsToProcess"s,
    "IfcRelAssignsToProduct"s,
    "IfcRelAssignsToResource"s,
    "IfcRelAssociates"s,
    "IfcRelAssociatesApproval"s,
    "IfcRelAssociatesClassification"s,
    "IfcRelAssociatesConstraint"s,
    "IfcRelAssociatesDocument"s,
    "IfcRelAssociatesLibrary"s,
    "IfcRelAssociatesMaterial"s,
    "IfcRelAssociatesProfileDef"s,
    "IfcRelConnects"s,
    "IfcRelConnectsElements"s,
    "IfcRelConnectsPathElements"s,
    "IfcRelConnectsPortToElement"s,
    "IfcRelConnectsPorts"s,
    "IfcRelConnectsStructuralActivity"s,
    "IfcRelConnectsStructuralMember"s,
    "IfcRelConnectsWithEccentricity"s,
    "IfcRelConnectsWithRealizingElements"s,
    "IfcRelContainedInSpatialStructure"s,
    "IfcRelCoversBldgElements"s,
    "IfcRelCoversSpaces"s,
    "IfcRelDeclares"s,
    "IfcRelDecomposes"s,
    "IfcRelDefines"s,
    "IfcRelDefinesByObject"s,
    "IfcRelDefinesByProperties"s,
    "IfcRelDefinesByTemplate"s,
    "IfcRelDefinesByType"s,
    "IfcRelFillsElement"s,
    "IfcRelFlowControlElements"s,
    "IfcRelInterferesElements"s,
    "IfcRelNests"s,
    "IfcRelPositions"s,
    "IfcRelProjectsElement"s,
    "IfcRelReferencedInSpatialStructure"s,
    "IfcRelSequence"s,
    "IfcRelServicesBuildings"s,
    "IfcRelSpaceBoundary"s,
    "IfcRelSpaceBoundary1stLevel"s,
    "IfcRelSpaceBoundary2ndLevel"s,
    "IfcRelVoidsElement"s,
    "IfcReparametrisedCompositeCurveSegment"s,
    "IfcResource"s,
    "IfcRevolvedAreaSolid"s,
    "IfcRevolvedAreaSolidTapered"s,
    "IfcRightCircularCone"s,
    "IfcRightCircularCylinder"s,
    "IfcSectionedSolid"s,
    "IfcSectionedSolidHorizontal"s,
    "IfcSectionedSurface"s,
    "IfcSimplePropertyTemplate"s,
    "IfcSpatialElement"s,
    "IfcSpatialElementType"s,
    "IfcSpatialStructureElement"s,
    "IfcSpatialStructureElementType"s,
    "IfcSpatialZone"s,
    "IfcSpatialZoneType"s,
    "IfcSphere"s,
    "IfcSphericalSurface"s,
    "IfcSpiral"s,
    "IfcStructuralActivity"s,
    "IfcStructuralItem"s,
    "IfcStructuralMember"s,
    "IfcStructuralReaction"s,
    "IfcStructuralSurfaceMember"s,
    "IfcStructuralSurfaceMemberVarying"s,
    "IfcStructuralSurfaceReaction"s,
    "IfcSubContractResourceType"s,
    "IfcSurfaceCurve"s,
    "IfcSurfaceCurveSweptAreaSolid"s,
    "IfcSurfaceOfLinearExtrusion"s,
    "IfcSurfaceOfRevolution"s,
    "IfcSystemFurnitureElementType"s,
    "IfcTask"s,
    "IfcTaskType"s,
    "IfcTessellatedFaceSet"s,
    "IfcThirdOrderPolynomialSpiral"s,
    "IfcToroidalSurface"s,
    "IfcTransportationDeviceType"s,
    "IfcTriangulatedFaceSet"s,
    "IfcTriangulatedIrregularNetwork"s,
    "IfcVehicleType"s,
    "IfcWindowLiningProperties"s,
    "IfcWindowPanelProperties"s,
    "IfcAppliedValueSelect"s,
    "IfcAxis2Placement"s,
    "IfcBooleanOperand"s,
    "IfcColour"s,
    "IfcColourOrFactor"s,
    "IfcCsgSelect"s,
    "IfcCurveStyleFontSelect"s,
    "IfcFillStyleSelect"s,
    "IfcGeometricSetSelect"s,
    "IfcGridPlacementDirectionSelect"s,
    "IfcMetricValueSelect"s,
    "IfcProcessSelect"s,
    "IfcProductSelect"s,
    "IfcPropertySetDefinitionSelect"s,
    "IfcResourceSelect"s,
    "IfcShell"s,
    "IfcSolidOrShell"s,
    "IfcSurfaceOrFaceSurface"s,
    "IfcTrimmingSelect"s,
    "IfcVectorOrDirection"s,
    "IfcActor"s,
    "IfcAdvancedBrep"s,
    "IfcAdvancedBrepWithVoids"s,
    "IfcAnnotation"s,
    "IfcBSplineSurface"s,
    "IfcBSplineSurfaceWithKnots"s,
    "IfcBlock"s,
    "IfcBooleanClippingResult"s,
    "IfcBoundedCurve"s,
    "IfcBuildingStorey"s,
    "IfcBuiltElementType"s,
    "IfcChimneyType"s,
    "IfcCircleHollowProfileDef"s,
    "IfcCivilElementType"s,
    "IfcClothoid"s,
    "IfcColumnType"s,
    "IfcComplexPropertyTemplate"s,
    "IfcCompositeCurve"s,
    "IfcCompositeCurveOnSurface"s,
    "IfcConic"s,
    "IfcConstructionEquipmentResourceType"s,
    "IfcConstructionMaterialResourceType"s,
    "IfcConstructionProductResourceType"s,
    "IfcConstructionResource"s,
    "IfcControl"s,
    "IfcCosineSpiral"s,
    "IfcCostItem"s,
    "IfcCostSchedule"s,
    "IfcCourseType"s,
    "IfcCoveringType"s,
    "IfcCrewResource"s,
    "IfcCurtainWallType"s,
    "IfcCylindricalSurface"s,
    "IfcDeepFoundationType"s,
    "IfcDirectrixDerivedReferenceSweptAreaSolid"s,
    "IfcDistributionElementType"s,
    "IfcDistributionFlowElementType"s,
    "IfcDoorLiningProperties"s,
    "IfcDoorPanelProperties"s,
    "IfcDoorType"s,
    "IfcDraughtingPreDefinedColour"s,
    "IfcDraughtingPreDefinedCurveFont"s,
    "IfcElement"s,
    "IfcElementAssembly"s,
    "IfcElementAssemblyType"s,
    "IfcElementComponent"s,
    "IfcElementComponentType"s,
    "IfcEllipse"s,
    "IfcEnergyConversionDeviceType"s,
    "IfcEngineType"s,
    "IfcEvaporativeCoolerType"s,
    "IfcEvaporatorType"s,
    "IfcEvent"s,
    "IfcExternalSpatialStructureElement"s,
    "IfcFacetedBrep"s,
    "IfcFacetedBrepWithVoids"s,
    "IfcFacility"s,
    "IfcFacilityPart"s,
    "IfcFacilityPartCommon"s,
    "IfcFastener"s,
    "IfcFastenerType"s,
    "IfcFeatureElement"s,
    "IfcFeatureElementAddition"s,
    "IfcFeatureElementSubtraction"s,
    "IfcFlowControllerType"s,
    "IfcFlowFittingType"s,
    "IfcFlowMeterType"s,
    "IfcFlowMovingDeviceType"s,
    "IfcFlowSegmentType"s,
    "IfcFlowStorageDeviceType"s,
    "IfcFlowTerminalType"s,
    "IfcFlowTreatmentDeviceType"s,
    "IfcFootingType"s,
    "IfcFurnishingElement"s,
    "IfcFurniture"s,
    "IfcGeographicElement"s,
    "IfcGeotechnicalElement"s,
    "IfcGeotechnicalStratum"s,
    "IfcGradientCurve"s,
    "IfcGroup"s,
    "IfcHeatExchangerType"s,
    "IfcHumidifierType"s,
    "IfcImpactProtectionDevice"s,
    "IfcImpactProtectionDeviceType"s,
    "IfcIndexedPolyCurve"s,
    "IfcInterceptorType"s,
    "IfcIntersectionCurve"s,
    "IfcInventory"s,
    "IfcJunctionBoxType"s,
    "IfcKerbType"s,
    "IfcLaborResource"s,
    "IfcLampType"s,
    "IfcLightFixtureType"s,
    "IfcLinearElement"s,
    "IfcLiquidTerminalType"s,
    "IfcMarineFacility"s,
    "IfcMarinePart"s,
    "IfcMechanicalFastener"s,
    "IfcMechanicalFastenerType"s,
    "IfcMedicalDeviceType"s,
    "IfcMemberType"s,
    "IfcMobileTelecommunicationsApplianceType"s,
    "IfcMooringDeviceType"s,
    "IfcMotorConnectionType"s,
    "IfcNavigationElementType"s,
    "IfcOccupant"s,
    "IfcOpeningElement"s,
    "IfcOutletType"s,
    "IfcPavementType"s,
    "IfcPerformanceHistory"s,
    "IfcPermeableCoveringProperties"s,
    "IfcPermit"s,
    "IfcPileType"s,
    "IfcPipeFittingType"s,
    "IfcPipeSegmentType"s,
    "IfcPlateType"s,
    "IfcPolygonalFaceSet"s,
    "IfcPolyline"s,
    "IfcPort"s,
    "IfcPositioningElement"s,
    "IfcProcedure"s,
    "IfcProjectOrder"s,
    "IfcProjectionElement"s,
    "IfcProtectiveDeviceType"s,
    "IfcPumpType"s,
    "IfcRailType"s,
    "IfcRailingType"s,
    "IfcRailway"s,
    "IfcRailwayPart"s,
    "IfcRampFlightType"s,
    "IfcRampType"s,
    "IfcRationalBSplineSurfaceWithKnots"s,
    "IfcReferent"s,
    "IfcReinforcingElement"s,
    "IfcReinforcingElementType"s,
    "IfcReinforcingMesh"s,
    "IfcReinforcingMeshType"s,
    "IfcRelAdheresToElement"s,
    "IfcRelAggregates"s,
    "IfcRoad"s,
    "IfcRoadPart"s,
    "IfcRoofType"s,
    "IfcSanitaryTerminalType"s,
    "IfcSeamCurve"s,
    "IfcSecondOrderPolynomialSpiral"s,
    "IfcSegmentedReferenceCurve"s,
    "IfcSeventhOrderPolynomialSpiral"s,
    "IfcShadingDeviceType"s,
    "IfcSign"s,
    "IfcSignType"s,
    "IfcSignalType"s,
    "IfcSineSpiral"s,
    "IfcSite"s,
    "IfcSlabType"s,
    "IfcSolarDeviceType"s,
    "IfcSpace"s,
    "IfcSpaceHeaterType"s,
    "IfcSpaceType"s,
    "IfcStackTerminalType"s,
    "IfcStairFlightType"s,
    "IfcStairType"s,
    "IfcStructuralAction"s,
    "IfcStructuralConnection"s,
    "IfcStructuralCurveAction"s,
    "IfcStructuralCurveConnection"s,
    "IfcStructuralCurveMember"s,
    "IfcStructuralCurveMemberVarying"s,
    "IfcStructuralCurveReaction"s,
    "IfcStructuralLinearAction"s,
    "IfcStructuralLoadGroup"s,
    "IfcStructuralPointAction"s,
    "IfcStructuralPointConnection"s,
    "IfcStructuralPointReaction"s,
    "IfcStructuralResultGroup"s,
    "IfcStructuralSurfaceAction"s,
    "IfcStructuralSurfaceConnection"s,
    "IfcSubContractResource"s,
    "IfcSurfaceFeature"s,
    "IfcSwitchingDeviceType"s,
    "IfcSystem"s,
    "IfcSystemFurnitureElement"s,
    "IfcTankType"s,
    "IfcTendon"s,
    "IfcTendonAnchor"s,
    "IfcTendonAnchorType"s,
    "IfcTendonConduit"s,
    "IfcTendonConduitType"s,
    "IfcTendonType"s,
    "IfcTrackElementType"s,
    "IfcTransformerType"s,
    "IfcTransportElementType"s,
    "IfcTransportationDevice"s,
    "IfcTrimmedCurve"s,
    "IfcTubeBundleType"s,
    "IfcUnitaryEquipmentType"s,
    "IfcValveType"s,
    "IfcVehicle"s,
    "IfcVibrationDamper"s,
    "IfcVibrationDamperType"s,
    "IfcVibrationIsolator"s,
    "IfcVibrationIsolatorType"s,
    "IfcVirtualElement"s,
    "IfcVoidingFeature"s,
    "IfcWallType"s,
    "IfcWasteTerminalType"s,
    "IfcWindowType"s,
    "IfcWorkCalendar"s,
    "IfcWorkControl"s,
    "IfcWorkPlan"s,
    "IfcWorkSchedule"s,
    "IfcZone"s,
    "IfcCurveFontOrScaledCurveFontSelect"s,
    "IfcCurveOnSurface"s,
    "IfcCurveOrEdgeCurve"s,
    "IfcInterferenceSelect"s,
    "IfcSpatialReferenceSelect"s,
    "IfcStructuralActivityAssignmentSelect"s,
    "IfcActionRequest"s,
    "IfcAirTerminalBoxType"s,
    "IfcAirTerminalType"s,
    "IfcAirToAirHeatRecoveryType"s,
    "IfcAlignmentCant"s,
    "IfcAlignmentHorizontal"s,
    "IfcAlignmentSegment"s,
    "IfcAlignmentVertical"s,
    "IfcAsset"s,
    "IfcAudioVisualApplianceType"s,
    "IfcBSplineCurve"s,
    "IfcBSplineCurveWithKnots"s,
    "IfcBeamType"s,
    "IfcBearingType"s,
    "IfcBoilerType"s,
    "IfcBoundaryCurve"s,
    "IfcBridge"s,
    "IfcBridgePart"s,
    "IfcBuilding"s,
    "IfcBuildingElementPart"s,
    "IfcBuildingElementPartType"s,
    "IfcBuildingElementProxyType"s,
    "IfcBuildingSystem"s,
    "IfcBuiltElement"s,
    "IfcBuiltSystem"s,
    "IfcBurnerType"s,
    "IfcCableCarrierFittingType"s,
    "IfcCableCarrierSegmentType"s,
    "IfcCableFittingType"s,
    "IfcCableSegmentType"s,
    "IfcCaissonFoundationType"s,
    "IfcChillerType"s,
    "IfcChimney"s,
    "IfcCircle"s,
    "IfcCivilElement"s,
    "IfcCoilType"s,
    "IfcColumn"s,
    "IfcCommunicationsApplianceType"s,
    "IfcCompressorType"s,
    "IfcCondenserType"s,
    "IfcConstructionEquipmentResource"s,
    "IfcConstructionMaterialResource"s,
    "IfcConstructionProductResource"s,
    "IfcConveyorSegmentType"s,
    "IfcCooledBeamType"s,
    "IfcCoolingTowerType"s,
    "IfcCourse"s,
    "IfcCovering"s,
    "IfcCurtainWall"s,
    "IfcDamperType"s,
    "IfcDeepFoundation"s,
    "IfcDiscreteAccessory"s,
    "IfcDiscreteAccessoryType"s,
    "IfcDistributionBoardType"s,
    "IfcDistributionChamberElementType"s,
    "IfcDistributionControlElementType"s,
    "IfcDistributionElement"s,
    "IfcDistributionFlowElement"s,
    "IfcDistributionPort"s,
    "IfcDistributionSystem"s,
    "IfcDoor"s,
    "IfcDuctFittingType"s,
    "IfcDuctSegmentType"s,
    "IfcDuctSilencerType"s,
    "IfcEarthworksCut"s,
    "IfcEarthworksElement"s,
    "IfcEarthworksFill"s,
    "IfcElectricApplianceType"s,
    "IfcElectricDistributionBoardType"s,
    "IfcElectricFlowStorageDeviceType"s,
    "IfcElectricFlowTreatmentDeviceType"s,
    "IfcElectricGeneratorType"s,
    "IfcElectricMotorType"s,
    "IfcElectricTimeControlType"s,
    "IfcEnergyConversionDevice"s,
    "IfcEngine"s,
    "IfcEvaporativeCooler"s,
    "IfcEvaporator"s,
    "IfcExternalSpatialElement"s,
    "IfcFanType"s,
    "IfcFilterType"s,
    "IfcFireSuppressionTerminalType"s,
    "IfcFlowController"s,
    "IfcFlowFitting"s,
    "IfcFlowInstrumentType"s,
    "IfcFlowMeter"s,
    "IfcFlowMovingDevice"s,
    "IfcFlowSegment"s,
    "IfcFlowStorageDevice"s,
    "IfcFlowTerminal"s,
    "IfcFlowTreatmentDevice"s,
    "IfcFooting"s,
    "IfcGeotechnicalAssembly"s,
    "IfcGrid"s,
    "IfcHeatExchanger"s,
    "IfcHumidifier"s,
    "IfcInterceptor"s,
    "IfcJunctionBox"s,
    "IfcKerb"s,
    "IfcLamp"s,
    "IfcLightFixture"s,
    "IfcLinearPositioningElement"s,
    "IfcLiquidTerminal"s,
    "IfcMedicalDevice"s,
    "IfcMember"s,
    "IfcMobileTelecommunicationsAppliance"s,
    "IfcMooringDevice"s,
    "IfcMotorConnection"s,
    "IfcNavigationElement"s,
    "IfcOuterBoundaryCurve"s,
    "IfcOutlet"s,
    "IfcPavement"s,
    "IfcPile"s,
    "IfcPipeFitting"s,
    "IfcPipeSegment"s,
    "IfcPlate"s,
    "IfcProtectiveDevice"s,
    "IfcProtectiveDeviceTrippingUnitType"s,
    "IfcPump"s,
    "IfcRail"s,
    "IfcRailing"s,
    "IfcRamp"s,
    "IfcRampFlight"s,
    "IfcRationalBSplineCurveWithKnots"s,
    "IfcReinforcedSoil"s,
    "IfcReinforcingBar"s,
    "IfcReinforcingBarType"s,
    "IfcRoof"s,
    "IfcSanitaryTerminal"s,
    "IfcSensorType"s,
    "IfcShadingDevice"s,
    "IfcSignal"s,
    "IfcSlab"s,
    "IfcSolarDevice"s,
    "IfcSpaceHeater"s,
    "IfcStackTerminal"s,
    "IfcStair"s,
    "IfcStairFlight"s,
    "IfcStructuralAnalysisModel"s,
    "IfcStructuralLoadCase"s,
    "IfcStructuralPlanarAction"s,
    "IfcSwitchingDevice"s,
    "IfcTank"s,
    "IfcTrackElement"s,
    "IfcTransformer"s,
    "IfcTransportElement"s,
    "IfcTubeBundle"s,
    "IfcUnitaryControlElementType"s,
    "IfcUnitaryEquipment"s,
    "IfcValve"s,
    "IfcWall"s,
    "IfcWallStandardCase"s,
    "IfcWasteTerminal"s,
    "IfcWindow"s,
    "IfcSpaceBoundarySelect"s,
    "IfcActuatorType"s,
    "IfcAirTerminal"s,
    "IfcAirTerminalBox"s,
    "IfcAirToAirHeatRecovery"s,
    "IfcAlarmType"s,
    "IfcAlignment"s,
    "IfcAudioVisualAppliance"s,
    "IfcBeam"s,
    "IfcBearing"s,
    "IfcBoiler"s,
    "IfcBorehole"s,
    "IfcBuildingElementProxy"s,
    "IfcBurner"s,
    "IfcCableCarrierFitting"s,
    "IfcCableCarrierSegment"s,
    "IfcCableFitting"s,
    "IfcCableSegment"s,
    "IfcCaissonFoundation"s,
    "IfcChiller"s,
    "IfcCoil"s,
    "IfcCommunicationsAppliance"s,
    "IfcCompressor"s,
    "IfcCondenser"s,
    "IfcControllerType"s,
    "IfcConveyorSegment"s,
    "IfcCooledBeam"s,
    "IfcCoolingTower"s,
    "IfcDamper"s,
    "IfcDistributionBoard"s,
    "IfcDistributionChamberElement"s,
    "IfcDistributionCircuit"s,
    "IfcDistributionControlElement"s,
    "IfcDuctFitting"s,
    "IfcDuctSegment"s,
    "IfcDuctSilencer"s,
    "IfcElectricAppliance"s,
    "IfcElectricDistributionBoard"s,
    "IfcElectricFlowStorageDevice"s,
    "IfcElectricFlowTreatmentDevice"s,
    "IfcElectricGenerator"s,
    "IfcElectricMotor"s,
    "IfcElectricTimeControl"s,
    "IfcFan"s,
    "IfcFilter"s,
    "IfcFireSuppressionTerminal"s,
    "IfcFlowInstrument"s,
    "IfcGeomodel"s,
    "IfcGeoslice"s,
    "IfcProtectiveDeviceTrippingUnit"s,
    "IfcSensor"s,
    "IfcUnitaryControlElement"s,
    "IfcActuator"s,
    "IfcAlarm"s,
    "IfcController"s,
    "PredefinedType"s,
    "Status"s,
    "LongDescription"s,
    "TheActor"s,
    "Role"s,
    "UserDefinedRole"s,
    "Description"s,
    "Purpose"s,
    "UserDefinedPurpose"s,
    "Voids"s,
    "RailHeadDistance"s,
    "StartDistAlong"s,
    "HorizontalLength"s,
    "StartCantLeft"s,
    "EndCantLeft"s,
    "StartCantRight"s,
    "EndCantRight"s,
    "StartPoint"s,
    "StartDirection"s,
    "StartRadiusOfCurvature"s,
    "EndRadiusOfCurvature"s,
    "SegmentLength"s,
    "GravityCenterLineHeight"s,
    "StartTag"s,
    "EndTag"s,
    "DesignParameters"s,
    "StartHeight"s,
    "StartGradient"s,
    "EndGradient"s,
    "RadiusOfCurvature"s,
    "OuterBoundary"s,
    "InnerBoundaries"s,
    "ApplicationDeveloper"s,
    "Version"s,
    "ApplicationFullName"s,
    "ApplicationIdentifier"s,
    "Name"s,
    "AppliedValue"s,
    "UnitBasis"s,
    "ApplicableDate"s,
    "FixedUntilDate"s,
    "Category"s,
    "Condition"s,
    "ArithmeticOperator"s,
    "Components"s,
    "Identifier"s,
    "TimeOfApproval"s,
    "Level"s,
    "Qualifier"s,
    "RequestingApproval"s,
    "GivingApproval"s,
    "RelatingApproval"s,
    "RelatedApprovals"s,
    "OuterCurve"s,
    "Curve"s,
    "InnerCurves"s,
    "Identification"s,
    "OriginalValue"s,
    "CurrentValue"s,
    "TotalReplacementCost"s,
    "Owner"s,
    "User"s,
    "ResponsiblePerson"s,
    "IncorporationDate"s,
    "DepreciatedValue"s,
    "BottomFlangeWidth"s,
    "OverallDepth"s,
    "WebThickness"s,
    "BottomFlangeThickness"s,
    "BottomFlangeFilletRadius"s,
    "TopFlangeWidth"s,
    "TopFlangeThickness"s,
    "TopFlangeFilletRadius"s,
    "BottomFlangeEdgeRadius"s,
    "BottomFlangeSlope"s,
    "TopFlangeEdgeRadius"s,
    "TopFlangeSlope"s,
    "Axis"s,
    "RefDirection"s,
    "Degree"s,
    "ControlPointsList"s,
    "CurveForm"s,
    "ClosedCurve"s,
    "SelfIntersect"s,
    "KnotMultiplicities"s,
    "Knots"s,
    "KnotSpec"s,
    "UDegree"s,
    "VDegree"s,
    "SurfaceForm"s,
    "UClosed"s,
    "VClosed"s,
    "UMultiplicities"s,
    "VMultiplicities"s,
    "UKnots"s,
    "VKnots"s,
    "RasterFormat"s,
    "RasterCode"s,
    "XLength"s,
    "YLength"s,
    "ZLength"s,
    "Operator"s,
    "FirstOperand"s,
    "SecondOperand"s,
    "TranslationalStiffnessByLengthX"s,
    "TranslationalStiffnessByLengthY"s,
    "TranslationalStiffnessByLengthZ"s,
    "RotationalStiffnessByLengthX"s,
    "RotationalStiffnessByLengthY"s,
    "RotationalStiffnessByLengthZ"s,
    "TranslationalStiffnessByAreaX"s,
    "TranslationalStiffnessByAreaY"s,
    "TranslationalStiffnessByAreaZ"s,
    "TranslationalStiffnessX"s,
    "TranslationalStiffnessY"s,
    "TranslationalStiffnessZ"s,
    "RotationalStiffnessX"s,
    "RotationalStiffnessY"s,
    "RotationalStiffnessZ"s,
    "WarpingStiffness"s,
    "Corner"s,
    "XDim"s,
    "YDim"s,
    "ZDim"s,
    "Enclosure"s,
    "ElevationOfRefHeight"s,
    "ElevationOfTerrain"s,
    "BuildingAddress"s,
    "Elevation"s,
    "LongName"s,
    "Depth"s,
    "Width"s,
    "WallThickness"s,
    "Girth"s,
    "InternalFilletRadius"s,
    "Coordinates"s,
    "CoordList"s,
    "TagList"s,
    "Axis1"s,
    "Axis2"s,
    "LocalOrigin"s,
    "Scale"s,
    "Scale2"s,
    "Axis3"s,
    "Scale3"s,
    "Thickness"s,
    "Radius"s,
    "Source"s,
    "Edition"s,
    "EditionDate"s,
    "Specification"s,
    "ReferenceTokens"s,
    "ReferencedSource"s,
    "Sort"s,
    "ClothoidConstant"s,
    "Red"s,
    "Green"s,
    "Blue"s,
    "ColourList"s,
    "UsageName"s,
    "HasProperties"s,
    "TemplateType"s,
    "HasPropertyTemplates"s,
    "Segments"s,
    "SameSense"s,
    "ParentCurve"s,
    "Profiles"s,
    "Label"s,
    "Position"s,
    "CfsFaces"s,
    "CurveOnRelatingElement"s,
    "CurveOnRelatedElement"s,
    "EccentricityInX"s,
    "EccentricityInY"s,
    "EccentricityInZ"s,
    "PointOnRelatingElement"s,
    "PointOnRelatedElement"s,
    "SurfaceOnRelatingElement"s,
    "SurfaceOnRelatedElement"s,
    "VolumeOnRelatingElement"s,
    "VolumeOnRelatedElement"s,
    "ConstraintGrade"s,
    "ConstraintSource"s,
    "CreatingActor"s,
    "CreationTime"s,
    "UserDefinedGrade"s,
    "Usage"s,
    "BaseCosts"s,
    "BaseQuantity"s,
    "ObjectType"s,
    "Phase"s,
    "RepresentationContexts"s,
    "UnitsInContext"s,
    "ConversionFactor"s,
    "ConversionOffset"s,
    "SourceCRS"s,
    "TargetCRS"s,
    "GeodeticDatum"s,
    "VerticalDatum"s,
    "CosineTerm"s,
    "ConstantTerm"s,
    "CostValues"s,
    "CostQuantities"s,
    "SubmittedOn"s,
    "UpdateDate"s,
    "TreeRootExpression"s,
    "RelatingMonetaryUnit"s,
    "RelatedMonetaryUnit"s,
    "ExchangeRate"s,
    "RateDateTime"s,
    "RateSource"s,
    "BasisSurface"s,
    "Boundaries"s,
    "ImplicitOuter"s,
    "Placement"s,
    "SegmentStart"s,
    "CurveFont"s,
    "CurveWidth"s,
    "CurveColour"s,
    "ModelOrDraughting"s,
    "PatternList"s,
    "CurveStyleFont"s,
    "CurveFontScaling"s,
    "VisibleSegmentLength"s,
    "InvisibleSegmentLength"s,
    "ParentProfile"s,
    "Elements"s,
    "UnitType"s,
    "UserDefinedType"s,
    "Unit"s,
    "Exponent"s,
    "LengthExponent"s,
    "MassExponent"s,
    "TimeExponent"s,
    "ElectricCurrentExponent"s,
    "ThermodynamicTemperatureExponent"s,
    "AmountOfSubstanceExponent"s,
    "LuminousIntensityExponent"s,
    "DirectionRatios"s,
    "Directrix"s,
    "StartParam"s,
    "EndParam"s,
    "FlowDirection"s,
    "SystemType"s,
    "Location"s,
    "IntendedUse"s,
    "Scope"s,
    "Revision"s,
    "DocumentOwner"s,
    "Editors"s,
    "LastRevisionTime"s,
    "ElectronicFormat"s,
    "ValidFrom"s,
    "ValidUntil"s,
    "Confidentiality"s,
    "RelatingDocument"s,
    "RelatedDocuments"s,
    "RelationshipType"s,
    "ReferencedDocument"s,
    "OverallHeight"s,
    "OverallWidth"s,
    "OperationType"s,
    "UserDefinedOperationType"s,
    "LiningDepth"s,
    "LiningThickness"s,
    "ThresholdDepth"s,
    "ThresholdThickness"s,
    "TransomThickness"s,
    "TransomOffset"s,
    "LiningOffset"s,
    "ThresholdOffset"s,
    "CasingThickness"s,
    "CasingDepth"s,
    "ShapeAspectStyle"s,
    "LiningToPanelOffsetX"s,
    "LiningToPanelOffsetY"s,
    "PanelDepth"s,
    "PanelOperation"s,
    "PanelWidth"s,
    "PanelPosition"s,
    "ParameterTakesPrecedence"s,
    "EdgeStart"s,
    "EdgeEnd"s,
    "EdgeGeometry"s,
    "EdgeList"s,
    "Tag"s,
    "AssemblyPlace"s,
    "MethodOfMeasurement"s,
    "Quantities"s,
    "ElementType"s,
    "SemiAxis1"s,
    "SemiAxis2"s,
    "EventTriggerType"s,
    "UserDefinedEventTriggerType"s,
    "EventOccurenceTime"s,
    "ActualDate"s,
    "EarlyDate"s,
    "LateDate"s,
    "ScheduleDate"s,
    "Properties"s,
    "RelatingReference"s,
    "RelatedResourceObjects"s,
    "ExtrudedDirection"s,
    "EndSweptArea"s,
    "Bounds"s,
    "FbsmFaces"s,
    "Bound"s,
    "Orientation"s,
    "FaceSurface"s,
    "UsageType"s,
    "TensionFailureX"s,
    "TensionFailureY"s,
    "TensionFailureZ"s,
    "CompressionFailureX"s,
    "CompressionFailureY"s,
    "CompressionFailureZ"s,
    "FillStyles"s,
    "HatchLineAppearance"s,
    "StartOfNextHatchLine"s,
    "PointOfReferenceHatchLine"s,
    "PatternStart"s,
    "HatchLineAngle"s,
    "TilingPattern"s,
    "Tiles"s,
    "TilingScale"s,
    "FixedReference"s,
    "CoordinateSpaceDimension"s,
    "Precision"s,
    "WorldCoordinateSystem"s,
    "TrueNorth"s,
    "ParentContext"s,
    "TargetScale"s,
    "TargetView"s,
    "UserDefinedTargetView"s,
    "BaseCurve"s,
    "EndPoint"s,
    "UAxes"s,
    "VAxes"s,
    "WAxes"s,
    "AxisTag"s,
    "AxisCurve"s,
    "PlacementLocation"s,
    "PlacementRefDirection"s,
    "BaseSurface"s,
    "AgreementFlag"s,
    "FlangeThickness"s,
    "FilletRadius"s,
    "FlangeEdgeRadius"s,
    "FlangeSlope"s,
    "URLReference"s,
    "MappedTo"s,
    "Opacity"s,
    "Colours"s,
    "ColourIndex"s,
    "Points"s,
    "CoordIndex"s,
    "InnerCoordIndices"s,
    "TexCoordIndices"s,
    "TexCoords"s,
    "TexCoordIndex"s,
    "Jurisdiction"s,
    "ResponsiblePersons"s,
    "LastUpdateDate"s,
    "Values"s,
    "TimeStamp"s,
    "ListValues"s,
    "Mountable"s,
    "EdgeRadius"s,
    "LegSlope"s,
    "LagValue"s,
    "DurationType"s,
    "Publisher"s,
    "VersionDate"s,
    "Language"s,
    "ReferencedLibrary"s,
    "MainPlaneAngle"s,
    "SecondaryPlaneAngle"s,
    "LuminousIntensity"s,
    "LightDistributionCurve"s,
    "DistributionData"s,
    "LightColour"s,
    "AmbientIntensity"s,
    "Intensity"s,
    "ColourAppearance"s,
    "ColourTemperature"s,
    "LuminousFlux"s,
    "LightEmissionSource"s,
    "LightDistributionDataSource"s,
    "ConstantAttenuation"s,
    "DistanceAttenuation"s,
    "QuadricAttenuation"s,
    "ConcentrationExponent"s,
    "SpreadAngle"s,
    "BeamWidthAngle"s,
    "Pnt"s,
    "Dir"s,
    "RelativePlacement"s,
    "CartesianPosition"s,
    "Outer"s,
    "Eastings"s,
    "Northings"s,
    "OrthogonalHeight"s,
    "XAxisAbscissa"s,
    "XAxisOrdinate"s,
    "ScaleY"s,
    "ScaleZ"s,
    "MappingSource"s,
    "MappingTarget"s,
    "MaterialClassifications"s,
    "ClassifiedMaterial"s,
    "Material"s,
    "Fraction"s,
    "MaterialConstituents"s,
    "RepresentedMaterial"s,
    "LayerThickness"s,
    "IsVentilated"s,
    "Priority"s,
    "MaterialLayers"s,
    "LayerSetName"s,
    "ForLayerSet"s,
    "LayerSetDirection"s,
    "DirectionSense"s,
    "OffsetFromReferenceLine"s,
    "ReferenceExtent"s,
    "OffsetDirection"s,
    "OffsetValues"s,
    "Materials"s,
    "Profile"s,
    "MaterialProfiles"s,
    "CompositeProfile"s,
    "ForProfileSet"s,
    "CardinalPoint"s,
    "ForProfileEndSet"s,
    "CardinalEndPoint"s,
    "RelatingMaterial"s,
    "RelatedMaterials"s,
    "MaterialExpression"s,
    "ValueComponent"s,
    "UnitComponent"s,
    "NominalDiameter"s,
    "NominalLength"s,
    "Benchmark"s,
    "ValueSource"s,
    "DataValue"s,
    "ReferencePath"s,
    "Currency"s,
    "Dimensions"s,
    "PlacementRelTo"s,
    "BenchmarkValues"s,
    "LogicalAggregator"s,
    "ObjectiveQualifier"s,
    "UserDefinedQualifier"s,
    "BasisCurve"s,
    "Distance"s,
    "HorizontalWidths"s,
    "Widths"s,
    "Slopes"s,
    "Tags"s,
    "OffsetPoint"s,
    "Roles"s,
    "Addresses"s,
    "RelatingOrganization"s,
    "RelatedOrganizations"s,
    "EdgeElement"s,
    "OwningUser"s,
    "OwningApplication"s,
    "State"s,
    "ChangeAction"s,
    "LastModifiedDate"s,
    "LastModifyingUser"s,
    "LastModifyingApplication"s,
    "CreationDate"s,
    "ReferenceCurve"s,
    "LifeCyclePhase"s,
    "FrameDepth"s,
    "FrameThickness"s,
    "FamilyName"s,
    "GivenName"s,
    "MiddleNames"s,
    "PrefixTitles"s,
    "SuffixTitles"s,
    "ThePerson"s,
    "TheOrganization"s,
    "HasQuantities"s,
    "Discrimination"s,
    "Quality"s,
    "ConstructionType"s,
    "Height"s,
    "ColourComponents"s,
    "Pixel"s,
    "SizeInX"s,
    "SizeInY"s,
    "DistanceAlong"s,
    "OffsetLateral"s,
    "OffsetVertical"s,
    "OffsetLongitudinal"s,
    "PointParameter"s,
    "PointParameterU"s,
    "PointParameterV"s,
    "Polygon"s,
    "PolygonalBoundary"s,
    "Faces"s,
    "PnIndex"s,
    "CoefficientsX"s,
    "CoefficientsY"s,
    "CoefficientsZ"s,
    "InternalLocation"s,
    "AddressLines"s,
    "PostalBox"s,
    "Town"s,
    "Region"s,
    "PostalCode"s,
    "Country"s,
    "AssignedItems"s,
    "LayerOn"s,
    "LayerFrozen"s,
    "LayerBlocked"s,
    "LayerStyles"s,
    "ObjectPlacement"s,
    "Representation"s,
    "Representations"s,
    "ProfileType"s,
    "ProfileName"s,
    "ProfileDefinition"s,
    "MapProjection"s,
    "MapZone"s,
    "MapUnit"s,
    "UpperBoundValue"s,
    "LowerBoundValue"s,
    "SetPointValue"s,
    "DependingProperty"s,
    "DependantProperty"s,
    "Expression"s,
    "EnumerationValues"s,
    "EnumerationReference"s,
    "PropertyReference"s,
    "ApplicableEntity"s,
    "NominalValue"s,
    "DefiningValues"s,
    "DefinedValues"s,
    "DefiningUnit"s,
    "DefinedUnit"s,
    "CurveInterpolation"s,
    "AreaValue"s,
    "Formula"s,
    "CountValue"s,
    "LengthValue"s,
    "NumberValue"s,
    "TimeValue"s,
    "VolumeValue"s,
    "WeightValue"s,
    "WeightsData"s,
    "InnerFilletRadius"s,
    "OuterFilletRadius"s,
    "U1"s,
    "V1"s,
    "U2"s,
    "V2"s,
    "Usense"s,
    "Vsense"s,
    "RecurrenceType"s,
    "DayComponent"s,
    "WeekdayComponent"s,
    "MonthComponent"s,
    "Interval"s,
    "Occurrences"s,
    "TimePeriods"s,
    "TypeIdentifier"s,
    "AttributeIdentifier"s,
    "InstanceName"s,
    "ListPositions"s,
    "InnerReference"s,
    "TimeStep"s,
    "TotalCrossSectionArea"s,
    "SteelGrade"s,
    "BarSurface"s,
    "EffectiveDepth"s,
    "NominalBarDiameter"s,
    "BarCount"s,
    "DefinitionType"s,
    "ReinforcementSectionDefinitions"s,
    "CrossSectionArea"s,
    "BarLength"s,
    "BendingShapeCode"s,
    "BendingParameters"s,
    "MeshLength"s,
    "MeshWidth"s,
    "LongitudinalBarNominalDiameter"s,
    "TransverseBarNominalDiameter"s,
    "LongitudinalBarCrossSectionArea"s,
    "TransverseBarCrossSectionArea"s,
    "LongitudinalBarSpacing"s,
    "TransverseBarSpacing"s,
    "RelatingElement"s,
    "RelatedSurfaceFeatures"s,
    "RelatingObject"s,
    "RelatedObjects"s,
    "RelatedObjectsType"s,
    "RelatingActor"s,
    "ActingRole"s,
    "RelatingControl"s,
    "RelatingGroup"s,
    "Factor"s,
    "RelatingProcess"s,
    "QuantityInProcess"s,
    "RelatingProduct"s,
    "RelatingResource"s,
    "RelatingClassification"s,
    "Intent"s,
    "RelatingConstraint"s,
    "RelatingLibrary"s,
    "RelatingProfileDef"s,
    "ConnectionGeometry"s,
    "RelatedElement"s,
    "RelatingPriorities"s,
    "RelatedPriorities"s,
    "RelatedConnectionType"s,
    "RelatingConnectionType"s,
    "RelatingPort"s,
    "RelatedPort"s,
    "RealizingElement"s,
    "RelatedStructuralActivity"s,
    "RelatingStructuralMember"s,
    "RelatedStructuralConnection"s,
    "AppliedCondition"s,
    "AdditionalConditions"s,
    "SupportedLength"s,
    "ConditionCoordinateSystem"s,
    "ConnectionConstraint"s,
    "RealizingElements"s,
    "ConnectionType"s,
    "RelatedElements"s,
    "RelatingStructure"s,
    "RelatingBuildingElement"s,
    "RelatedCoverings"s,
    "RelatingSpace"s,
    "RelatingContext"s,
    "RelatedDefinitions"s,
    "RelatingPropertyDefinition"s,
    "RelatedPropertySets"s,
    "RelatingTemplate"s,
    "RelatingType"s,
    "RelatingOpeningElement"s,
    "RelatedBuildingElement"s,
    "RelatedControlElements"s,
    "RelatingFlowElement"s,
    "InterferenceGeometry"s,
    "InterferenceSpace"s,
    "InterferenceType"s,
    "ImpliedOrder"s,
    "RelatingPositioningElement"s,
    "RelatedProducts"s,
    "RelatedFeatureElement"s,
    "RelatedProcess"s,
    "TimeLag"s,
    "SequenceType"s,
    "UserDefinedSequenceType"s,
    "RelatingSystem"s,
    "RelatedBuildings"s,
    "PhysicalOrVirtualBoundary"s,
    "InternalOrExternalBoundary"s,
    "ParentBoundary"s,
    "CorrespondingBoundary"s,
    "RelatedOpeningElement"s,
    "ParamLength"s,
    "ContextOfItems"s,
    "RepresentationIdentifier"s,
    "RepresentationType"s,
    "Items"s,
    "ContextIdentifier"s,
    "ContextType"s,
    "MappingOrigin"s,
    "MappedRepresentation"s,
    "ScheduleWork"s,
    "ScheduleUsage"s,
    "ScheduleStart"s,
    "ScheduleFinish"s,
    "ScheduleContour"s,
    "LevelingDelay"s,
    "IsOverAllocated"s,
    "StatusTime"s,
    "ActualWork"s,
    "ActualUsage"s,
    "ActualStart"s,
    "ActualFinish"s,
    "RemainingWork"s,
    "RemainingUsage"s,
    "Completion"s,
    "Angle"s,
    "BottomRadius"s,
    "GlobalId"s,
    "OwnerHistory"s,
    "RoundingRadius"s,
    "Prefix"s,
    "DataOrigin"s,
    "UserDefinedDataOrigin"s,
    "QuadraticTerm"s,
    "LinearTerm"s,
    "SectionType"s,
    "StartProfile"s,
    "EndProfile"s,
    "LongitudinalStartPosition"s,
    "LongitudinalEndPosition"s,
    "TransversePosition"s,
    "ReinforcementRole"s,
    "SectionDefinition"s,
    "CrossSectionReinforcementDefinitions"s,
    "CrossSections"s,
    "CrossSectionPositions"s,
    "SpineCurve"s,
    "Transition"s,
    "SepticTerm"s,
    "SexticTerm"s,
    "QuinticTerm"s,
    "QuarticTerm"s,
    "CubicTerm"s,
    "ShapeRepresentations"s,
    "ProductDefinitional"s,
    "PartOfProductDefinitionShape"s,
    "SbsmBoundary"s,
    "PrimaryMeasureType"s,
    "SecondaryMeasureType"s,
    "Enumerators"s,
    "PrimaryUnit"s,
    "SecondaryUnit"s,
    "AccessState"s,
    "SineTerm"s,
    "RefLatitude"s,
    "RefLongitude"s,
    "RefElevation"s,
    "LandTitleNumber"s,
    "SiteAddress"s,
    "SlippageX"s,
    "SlippageY"s,
    "SlippageZ"s,
    "ElevationWithFlooring"s,
    "CompositionType"s,
    "NumberOfRisers"s,
    "NumberOfTreads"s,
    "RiserHeight"s,
    "TreadLength"s,
    "DestabilizingLoad"s,
    "AppliedLoad"s,
    "GlobalOrLocal"s,
    "OrientationOf2DPlane"s,
    "LoadedBy"s,
    "HasResults"s,
    "SharedPlacement"s,
    "ProjectedOrTrue"s,
    "AxisDirection"s,
    "SelfWeightCoefficients"s,
    "Locations"s,
    "ActionType"s,
    "ActionSource"s,
    "Coefficient"s,
    "LinearForceX"s,
    "LinearForceY"s,
    "LinearForceZ"s,
    "LinearMomentX"s,
    "LinearMomentY"s,
    "LinearMomentZ"s,
    "PlanarForceX"s,
    "PlanarForceY"s,
    "PlanarForceZ"s,
    "DisplacementX"s,
    "DisplacementY"s,
    "DisplacementZ"s,
    "RotationalDisplacementRX"s,
    "RotationalDisplacementRY"s,
    "RotationalDisplacementRZ"s,
    "Distortion"s,
    "ForceX"s,
    "ForceY"s,
    "ForceZ"s,
    "MomentX"s,
    "MomentY"s,
    "MomentZ"s,
    "WarpingMoment"s,
    "DeltaTConstant"s,
    "DeltaTY"s,
    "DeltaTZ"s,
    "TheoryType"s,
    "ResultForLoadGroup"s,
    "IsLinear"s,
    "Item"s,
    "Styles"s,
    "ParentEdge"s,
    "Curve3D"s,
    "AssociatedGeometry"s,
    "MasterRepresentation"s,
    "ReferenceSurface"s,
    "AxisPosition"s,
    "SurfaceReinforcement1"s,
    "SurfaceReinforcement2"s,
    "ShearReinforcement"s,
    "Side"s,
    "DiffuseTransmissionColour"s,
    "DiffuseReflectionColour"s,
    "TransmissionColour"s,
    "ReflectanceColour"s,
    "RefractionIndex"s,
    "DispersionFactor"s,
    "DiffuseColour"s,
    "ReflectionColour"s,
    "SpecularColour"s,
    "SpecularHighlight"s,
    "ReflectanceMethod"s,
    "SurfaceColour"s,
    "Transparency"s,
    "Textures"s,
    "RepeatS"s,
    "RepeatT"s,
    "Mode"s,
    "TextureTransform"s,
    "Parameter"s,
    "SweptArea"s,
    "InnerRadius"s,
    "SweptCurve"s,
    "FlangeWidth"s,
    "WebEdgeRadius"s,
    "WebSlope"s,
    "Rows"s,
    "Columns"s,
    "RowCells"s,
    "IsHeading"s,
    "WorkMethod"s,
    "IsMilestone"s,
    "TaskTime"s,
    "ScheduleDuration"s,
    "EarlyStart"s,
    "EarlyFinish"s,
    "LateStart"s,
    "LateFinish"s,
    "FreeFloat"s,
    "TotalFloat"s,
    "IsCritical"s,
    "ActualDuration"s,
    "RemainingTime"s,
    "Recurrence"s,
    "TelephoneNumbers"s,
    "FacsimileNumbers"s,
    "PagerNumber"s,
    "ElectronicMailAddresses"s,
    "WWWHomePageURL"s,
    "MessagingIDs"s,
    "TensionForce"s,
    "PreStress"s,
    "FrictionCoefficient"s,
    "AnchorageSlip"s,
    "MinCurvatureRadius"s,
    "SheathDiameter"s,
    "Closed"s,
    "Literal"s,
    "Path"s,
    "Extent"s,
    "BoxAlignment"s,
    "TextCharacterAppearance"s,
    "TextStyle"s,
    "TextFontStyle"s,
    "FontFamily"s,
    "FontStyle"s,
    "FontVariant"s,
    "FontWeight"s,
    "FontSize"s,
    "Colour"s,
    "BackgroundColour"s,
    "TextIndent"s,
    "TextAlign"s,
    "TextDecoration"s,
    "LetterSpacing"s,
    "WordSpacing"s,
    "TextTransform"s,
    "LineHeight"s,
    "Maps"s,
    "TexCoordsOf"s,
    "InnerTexCoordIndices"s,
    "Vertices"s,
    "TexCoordsList"s,
    "StartTime"s,
    "EndTime"s,
    "TimeSeriesDataType"s,
    "MajorRadius"s,
    "MinorRadius"s,
    "BottomXDim"s,
    "TopXDim"s,
    "TopXOffset"s,
    "Normals"s,
    "Flags"s,
    "Trim1"s,
    "Trim2"s,
    "SenseAgreement"s,
    "ApplicableOccurrence"s,
    "HasPropertySets"s,
    "ProcessType"s,
    "RepresentationMaps"s,
    "ResourceType"s,
    "Units"s,
    "Magnitude"s,
    "LoopVertex"s,
    "VertexGeometry"s,
    "IntersectingAxes"s,
    "OffsetDistances"s,
    "PartitioningType"s,
    "UserDefinedPartitioningType"s,
    "MullionThickness"s,
    "FirstTransomOffset"s,
    "SecondTransomOffset"s,
    "FirstMullionOffset"s,
    "SecondMullionOffset"s,
    "WorkingTimes"s,
    "ExceptionTimes"s,
    "Creators"s,
    "Duration"s,
    "FinishTime"s,
    "RecurrencePattern"s,
    "StartDate"s,
    "FinishDate"s,
    "IsActingUpon"s,
    "HasExternalReference"s,
    "OfPerson"s,
    "OfOrganization"s,
    "ContainedInStructure"s,
    "HasExternalReferences"s,
    "ApprovedObjects"s,
    "ApprovedResources"s,
    "IsRelatedWith"s,
    "Relates"s,
    "ClassificationForObjects"s,
    "HasReferences"s,
    "ClassificationRefForObjects"s,
    "PropertiesForConstraint"s,
    "IsDefinedBy"s,
    "Declares"s,
    "Controls"s,
    "HasCoordinateOperation"s,
    "CoversSpaces"s,
    "CoversElements"s,
    "AssignedToFlowElement"s,
    "HasPorts"s,
    "HasControlElements"s,
    "DocumentInfoForObjects"s,
    "HasDocumentReferences"s,
    "IsPointedTo"s,
    "IsPointer"s,
    "DocumentRefForObjects"s,
    "FillsVoids"s,
    "ConnectedTo"s,
    "IsInterferedByElements"s,
    "InterferesElements"s,
    "HasProjections"s,
    "HasOpenings"s,
    "IsConnectionRealization"s,
    "ProvidesBoundaries"s,
    "ConnectedFrom"s,
    "HasCoverings"s,
    "HasSurfaceFeatures"s,
    "ExternalReferenceForResources"s,
    "BoundedBy"s,
    "HasTextureMaps"s,
    "ProjectsElements"s,
    "VoidsElements"s,
    "HasSubContexts"s,
    "PartOfW"s,
    "PartOfV"s,
    "PartOfU"s,
    "HasIntersections"s,
    "IsGroupedBy"s,
    "ReferencedInStructures"s,
    "ToFaceSet"s,
    "HasTexCoords"s,
    "LibraryInfoForObjects"s,
    "HasLibraryReferences"s,
    "LibraryRefForObjects"s,
    "HasRepresentation"s,
    "RelatesTo"s,
    "ToMaterialConstituentSet"s,
    "AssociatedTo"s,
    "ToMaterialLayerSet"s,
    "ToMaterialProfileSet"s,
    "IsDeclaredBy"s,
    "IsTypedBy"s,
    "HasAssignments"s,
    "Nests"s,
    "IsNestedBy"s,
    "HasContext"s,
    "IsDecomposedBy"s,
    "Decomposes"s,
    "HasAssociations"s,
    "PlacesObject"s,
    "ReferencedByPlacements"s,
    "HasFillings"s,
    "IsRelatedBy"s,
    "Engages"s,
    "EngagedIn"s,
    "PartOfComplex"s,
    "ContainedIn"s,
    "Positions"s,
    "IsPredecessorTo"s,
    "IsSuccessorFrom"s,
    "OperatesOn"s,
    "ReferencedBy"s,
    "PositionedRelativeTo"s,
    "ShapeOfProduct"s,
    "HasShapeAspects"s,
    "PartOfPset"s,
    "PropertyForDependance"s,
    "PropertyDependsOn"s,
    "HasConstraints"s,
    "HasApprovals"s,
    "DefinesType"s,
    "DefinesOccurrence"s,
    "Defines"s,
    "PartOfComplexTemplate"s,
    "PartOfPsetTemplate"s,
    "Corresponds"s,
    "RepresentationMap"s,
    "LayerAssignments"s,
    "OfProductRepresentation"s,
    "RepresentationsInContext"s,
    "LayerAssignment"s,
    "StyledByItem"s,
    "MapUsage"s,
    "ResourceOf"s,
    "UsingCurves"s,
    "OfShapeAspect"s,
    "ContainsElements"s,
    "ServicedBySystems"s,
    "ReferencesElements"s,
    "AssignedToStructuralItem"s,
    "ConnectsStructuralMembers"s,
    "AssignedStructuralActivity"s,
    "SourceOfResultGroup"s,
    "LoadGroupFor"s,
    "ConnectedBy"s,
    "ResultGroupFor"s,
    "AdheresToElement"s,
    "IsMappedBy"s,
    "UsedInStyles"s,
    "ServicesBuildings"s,
    "ServicesFacilities"s,
    "HasColours"s,
    "HasTextures"s,
    "ToTexMap"s,
    "Types"s,
    "IFC4X3"s};

class IFC4X3_instance_factory : public IfcParse::instance_factory {
  virtual IfcUtil::IfcBaseClass *
  operator()(const IfcParse::declaration *decl,
             IfcEntityInstanceData &&data) const {
    switch (decl->index_in_schema()) {
    case 0:
      return new ::Ifc4x3::IfcAbsorbedDoseMeasure(std::move(data));
    case 1:
      return new ::Ifc4x3::IfcAccelerationMeasure(std::move(data));
    case 2:
      return new ::Ifc4x3::IfcActionRequest(std::move(data));
    case 3:
      return new ::Ifc4x3::IfcActionRequestTypeEnum(std::move(data));
    case 4:
      return new ::Ifc4x3::IfcActionSourceTypeEnum(std::move(data));
    case 5:
      return new ::Ifc4x3::IfcActionTypeEnum(std::move(data));
    case 6:
      return new ::Ifc4x3::IfcActor(std::move(data));
    case 7:
      return new ::Ifc4x3::IfcActorRole(std::move(data));
    case 9:
      return new ::Ifc4x3::IfcActuator(std::move(data));
    case 10:
      return new ::Ifc4x3::IfcActuatorType(std::move(data));
    case 11:
      return new ::Ifc4x3::IfcActuatorTypeEnum(std::move(data));
    case 12:
      return new ::Ifc4x3::IfcAddress(std::move(data));
    case 13:
      return new ::Ifc4x3::IfcAddressTypeEnum(std::move(data));
    case 14:
      return new ::Ifc4x3::IfcAdvancedBrep(std::move(data));
    case 15:
      return new ::Ifc4x3::IfcAdvancedBrepWithVoids(std::move(data));
    case 16:
      return new ::Ifc4x3::IfcAdvancedFace(std::move(data));
    case 17:
      return new ::Ifc4x3::IfcAirTerminal(std::move(data));
    case 18:
      return new ::Ifc4x3::IfcAirTerminalBox(std::move(data));
    case 19:
      return new ::Ifc4x3::IfcAirTerminalBoxType(std::move(data));
    case 20:
      return new ::Ifc4x3::IfcAirTerminalBoxTypeEnum(std::move(data));
    case 21:
      return new ::Ifc4x3::IfcAirTerminalType(std::move(data));
    case 22:
      return new ::Ifc4x3::IfcAirTerminalTypeEnum(std::move(data));
    case 23:
      return new ::Ifc4x3::IfcAirToAirHeatRecovery(std::move(data));
    case 24:
      return new ::Ifc4x3::IfcAirToAirHeatRecoveryType(std::move(data));
    case 25:
      return new ::Ifc4x3::IfcAirToAirHeatRecoveryTypeEnum(std::move(data));
    case 26:
      return new ::Ifc4x3::IfcAlarm(std::move(data));
    case 27:
      return new ::Ifc4x3::IfcAlarmType(std::move(data));
    case 28:
      return new ::Ifc4x3::IfcAlarmTypeEnum(std::move(data));
    case 29:
      return new ::Ifc4x3::IfcAlignment(std::move(data));
    case 30:
      return new ::Ifc4x3::IfcAlignmentCant(std::move(data));
    case 31:
      return new ::Ifc4x3::IfcAlignmentCantSegment(std::move(data));
    case 32:
      return new ::Ifc4x3::IfcAlignmentCantSegmentTypeEnum(std::move(data));
    case 33:
      return new ::Ifc4x3::IfcAlignmentHorizontal(std::move(data));
    case 34:
      return new ::Ifc4x3::IfcAlignmentHorizontalSegment(std::move(data));
    case 35:
      return new ::Ifc4x3::IfcAlignmentHorizontalSegmentTypeEnum(
          std::move(data));
    case 36:
      return new ::Ifc4x3::IfcAlignmentParameterSegment(std::move(data));
    case 37:
      return new ::Ifc4x3::IfcAlignmentSegment(std::move(data));
    case 38:
      return new ::Ifc4x3::IfcAlignmentTypeEnum(std::move(data));
    case 39:
      return new ::Ifc4x3::IfcAlignmentVertical(std::move(data));
    case 40:
      return new ::Ifc4x3::IfcAlignmentVerticalSegment(std::move(data));
    case 41:
      return new ::Ifc4x3::IfcAlignmentVerticalSegmentTypeEnum(std::move(data));
    case 42:
      return new ::Ifc4x3::IfcAmountOfSubstanceMeasure(std::move(data));
    case 43:
      return new ::Ifc4x3::IfcAnalysisModelTypeEnum(std::move(data));
    case 44:
      return new ::Ifc4x3::IfcAnalysisTheoryTypeEnum(std::move(data));
    case 45:
      return new ::Ifc4x3::IfcAngularVelocityMeasure(std::move(data));
    case 46:
      return new ::Ifc4x3::IfcAnnotation(std::move(data));
    case 47:
      return new ::Ifc4x3::IfcAnnotationFillArea(std::move(data));
    case 48:
      return new ::Ifc4x3::IfcAnnotationTypeEnum(std::move(data));
    case 49:
      return new ::Ifc4x3::IfcApplication(std::move(data));
    case 50:
      return new ::Ifc4x3::IfcAppliedValue(std::move(data));
    case 52:
      return new ::Ifc4x3::IfcApproval(std::move(data));
    case 53:
      return new ::Ifc4x3::IfcApprovalRelationship(std::move(data));
    case 54:
      return new ::Ifc4x3::IfcArbitraryClosedProfileDef(std::move(data));
    case 55:
      return new ::Ifc4x3::IfcArbitraryOpenProfileDef(std::move(data));
    case 56:
      return new ::Ifc4x3::IfcArbitraryProfileDefWithVoids(std::move(data));
    case 57:
      return new ::Ifc4x3::IfcArcIndex(std::move(data));
    case 58:
      return new ::Ifc4x3::IfcAreaDensityMeasure(std::move(data));
    case 59:
      return new ::Ifc4x3::IfcAreaMeasure(std::move(data));
    case 60:
      return new ::Ifc4x3::IfcArithmeticOperatorEnum(std::move(data));
    case 61:
      return new ::Ifc4x3::IfcAssemblyPlaceEnum(std::move(data));
    case 62:
      return new ::Ifc4x3::IfcAsset(std::move(data));
    case 63:
      return new ::Ifc4x3::IfcAsymmetricIShapeProfileDef(std::move(data));
    case 64:
      return new ::Ifc4x3::IfcAudioVisualAppliance(std::move(data));
    case 65:
      return new ::Ifc4x3::IfcAudioVisualApplianceType(std::move(data));
    case 66:
      return new ::Ifc4x3::IfcAudioVisualApplianceTypeEnum(std::move(data));
    case 67:
      return new ::Ifc4x3::IfcAxis1Placement(std::move(data));
    case 69:
      return new ::Ifc4x3::IfcAxis2Placement2D(std::move(data));
    case 70:
      return new ::Ifc4x3::IfcAxis2Placement3D(std::move(data));
    case 71:
      return new ::Ifc4x3::IfcAxis2PlacementLinear(std::move(data));
    case 72:
      return new ::Ifc4x3::IfcBeam(std::move(data));
    case 73:
      return new ::Ifc4x3::IfcBeamType(std::move(data));
    case 74:
      return new ::Ifc4x3::IfcBeamTypeEnum(std::move(data));
    case 75:
      return new ::Ifc4x3::IfcBearing(std::move(data));
    case 76:
      return new ::Ifc4x3::IfcBearingType(std::move(data));
    case 77:
      return new ::Ifc4x3::IfcBearingTypeDisplacementEnum(std::move(data));
    case 78:
      return new ::Ifc4x3::IfcBearingTypeEnum(std::move(data));
    case 79:
      return new ::Ifc4x3::IfcBenchmarkEnum(std::move(data));
    case 81:
      return new ::Ifc4x3::IfcBinary(std::move(data));
    case 82:
      return new ::Ifc4x3::IfcBlobTexture(std::move(data));
    case 83:
      return new ::Ifc4x3::IfcBlock(std::move(data));
    case 84:
      return new ::Ifc4x3::IfcBoiler(std::move(data));
    case 85:
      return new ::Ifc4x3::IfcBoilerType(std::move(data));
    case 86:
      return new ::Ifc4x3::IfcBoilerTypeEnum(std::move(data));
    case 87:
      return new ::Ifc4x3::IfcBoolean(std::move(data));
    case 88:
      return new ::Ifc4x3::IfcBooleanClippingResult(std::move(data));
    case 90:
      return new ::Ifc4x3::IfcBooleanOperator(std::move(data));
    case 91:
      return new ::Ifc4x3::IfcBooleanResult(std::move(data));
    case 92:
      return new ::Ifc4x3::IfcBorehole(std::move(data));
    case 93:
      return new ::Ifc4x3::IfcBoundaryCondition(std::move(data));
    case 94:
      return new ::Ifc4x3::IfcBoundaryCurve(std::move(data));
    case 95:
      return new ::Ifc4x3::IfcBoundaryEdgeCondition(std::move(data));
    case 96:
      return new ::Ifc4x3::IfcBoundaryFaceCondition(std::move(data));
    case 97:
      return new ::Ifc4x3::IfcBoundaryNodeCondition(std::move(data));
    case 98:
      return new ::Ifc4x3::IfcBoundaryNodeConditionWarping(std::move(data));
    case 99:
      return new ::Ifc4x3::IfcBoundedCurve(std::move(data));
    case 100:
      return new ::Ifc4x3::IfcBoundedSurface(std::move(data));
    case 101:
      return new ::Ifc4x3::IfcBoundingBox(std::move(data));
    case 102:
      return new ::Ifc4x3::IfcBoxAlignment(std::move(data));
    case 103:
      return new ::Ifc4x3::IfcBoxedHalfSpace(std::move(data));
    case 104:
      return new ::Ifc4x3::IfcBridge(std::move(data));
    case 105:
      return new ::Ifc4x3::IfcBridgePart(std::move(data));
    case 106:
      return new ::Ifc4x3::IfcBridgePartTypeEnum(std::move(data));
    case 107:
      return new ::Ifc4x3::IfcBridgeTypeEnum(std::move(data));
    case 108:
      return new ::Ifc4x3::IfcBSplineCurve(std::move(data));
    case 109:
      return new ::Ifc4x3::IfcBSplineCurveForm(std::move(data));
    case 110:
      return new ::Ifc4x3::IfcBSplineCurveWithKnots(std::move(data));
    case 111:
      return new ::Ifc4x3::IfcBSplineSurface(std::move(data));
    case 112:
      return new ::Ifc4x3::IfcBSplineSurfaceForm(std::move(data));
    case 113:
      return new ::Ifc4x3::IfcBSplineSurfaceWithKnots(std::move(data));
    case 114:
      return new ::Ifc4x3::IfcBuilding(std::move(data));
    case 115:
      return new ::Ifc4x3::IfcBuildingElementPart(std::move(data));
    case 116:
      return new ::Ifc4x3::IfcBuildingElementPartType(std::move(data));
    case 117:
      return new ::Ifc4x3::IfcBuildingElementPartTypeEnum(std::move(data));
    case 118:
      return new ::Ifc4x3::IfcBuildingElementProxy(std::move(data));
    case 119:
      return new ::Ifc4x3::IfcBuildingElementProxyType(std::move(data));
    case 120:
      return new ::Ifc4x3::IfcBuildingElementProxyTypeEnum(std::move(data));
    case 121:
      return new ::Ifc4x3::IfcBuildingStorey(std::move(data));
    case 122:
      return new ::Ifc4x3::IfcBuildingSystem(std::move(data));
    case 123:
      return new ::Ifc4x3::IfcBuildingSystemTypeEnum(std::move(data));
    case 124:
      return new ::Ifc4x3::IfcBuiltElement(std::move(data));
    case 125:
      return new ::Ifc4x3::IfcBuiltElementType(std::move(data));
    case 126:
      return new ::Ifc4x3::IfcBuiltSystem(std::move(data));
    case 127:
      return new ::Ifc4x3::IfcBuiltSystemTypeEnum(std::move(data));
    case 128:
      return new ::Ifc4x3::IfcBurner(std::move(data));
    case 129:
      return new ::Ifc4x3::IfcBurnerType(std::move(data));
    case 130:
      return new ::Ifc4x3::IfcBurnerTypeEnum(std::move(data));
    case 131:
      return new ::Ifc4x3::IfcCableCarrierFitting(std::move(data));
    case 132:
      return new ::Ifc4x3::IfcCableCarrierFittingType(std::move(data));
    case 133:
      return new ::Ifc4x3::IfcCableCarrierFittingTypeEnum(std::move(data));
    case 134:
      return new ::Ifc4x3::IfcCableCarrierSegment(std::move(data));
    case 135:
      return new ::Ifc4x3::IfcCableCarrierSegmentType(std::move(data));
    case 136:
      return new ::Ifc4x3::IfcCableCarrierSegmentTypeEnum(std::move(data));
    case 137:
      return new ::Ifc4x3::IfcCableFitting(std::move(data));
    case 138:
      return new ::Ifc4x3::IfcCableFittingType(std::move(data));
    case 139:
      return new ::Ifc4x3::IfcCableFittingTypeEnum(std::move(data));
    case 140:
      return new ::Ifc4x3::IfcCableSegment(std::move(data));
    case 141:
      return new ::Ifc4x3::IfcCableSegmentType(std::move(data));
    case 142:
      return new ::Ifc4x3::IfcCableSegmentTypeEnum(std::move(data));
    case 143:
      return new ::Ifc4x3::IfcCaissonFoundation(std::move(data));
    case 144:
      return new ::Ifc4x3::IfcCaissonFoundationType(std::move(data));
    case 145:
      return new ::Ifc4x3::IfcCaissonFoundationTypeEnum(std::move(data));
    case 146:
      return new ::Ifc4x3::IfcCardinalPointReference(std::move(data));
    case 147:
      return new ::Ifc4x3::IfcCartesianPoint(std::move(data));
    case 148:
      return new ::Ifc4x3::IfcCartesianPointList(std::move(data));
    case 149:
      return new ::Ifc4x3::IfcCartesianPointList2D(std::move(data));
    case 150:
      return new ::Ifc4x3::IfcCartesianPointList3D(std::move(data));
    case 151:
      return new ::Ifc4x3::IfcCartesianTransformationOperator(std::move(data));
    case 152:
      return new ::Ifc4x3::IfcCartesianTransformationOperator2D(
          std::move(data));
    case 153:
      return new ::Ifc4x3::IfcCartesianTransformationOperator2DnonUniform(
          std::move(data));
    case 154:
      return new ::Ifc4x3::IfcCartesianTransformationOperator3D(
          std::move(data));
    case 155:
      return new ::Ifc4x3::IfcCartesianTransformationOperator3DnonUniform(
          std::move(data));
    case 156:
      return new ::Ifc4x3::IfcCenterLineProfileDef(std::move(data));
    case 157:
      return new ::Ifc4x3::IfcChangeActionEnum(std::move(data));
    case 158:
      return new ::Ifc4x3::IfcChiller(std::move(data));
    case 159:
      return new ::Ifc4x3::IfcChillerType(std::move(data));
    case 160:
      return new ::Ifc4x3::IfcChillerTypeEnum(std::move(data));
    case 161:
      return new ::Ifc4x3::IfcChimney(std::move(data));
    case 162:
      return new ::Ifc4x3::IfcChimneyType(std::move(data));
    case 163:
      return new ::Ifc4x3::IfcChimneyTypeEnum(std::move(data));
    case 164:
      return new ::Ifc4x3::IfcCircle(std::move(data));
    case 165:
      return new ::Ifc4x3::IfcCircleHollowProfileDef(std::move(data));
    case 166:
      return new ::Ifc4x3::IfcCircleProfileDef(std::move(data));
    case 167:
      return new ::Ifc4x3::IfcCivilElement(std::move(data));
    case 168:
      return new ::Ifc4x3::IfcCivilElementType(std::move(data));
    case 169:
      return new ::Ifc4x3::IfcClassification(std::move(data));
    case 170:
      return new ::Ifc4x3::IfcClassificationReference(std::move(data));
    case 173:
      return new ::Ifc4x3::IfcClosedShell(std::move(data));
    case 174:
      return new ::Ifc4x3::IfcClothoid(std::move(data));
    case 175:
      return new ::Ifc4x3::IfcCoil(std::move(data));
    case 176:
      return new ::Ifc4x3::IfcCoilType(std::move(data));
    case 177:
      return new ::Ifc4x3::IfcCoilTypeEnum(std::move(data));
    case 180:
      return new ::Ifc4x3::IfcColourRgb(std::move(data));
    case 181:
      return new ::Ifc4x3::IfcColourRgbList(std::move(data));
    case 182:
      return new ::Ifc4x3::IfcColourSpecification(std::move(data));
    case 183:
      return new ::Ifc4x3::IfcColumn(std::move(data));
    case 184:
      return new ::Ifc4x3::IfcColumnType(std::move(data));
    case 185:
      return new ::Ifc4x3::IfcColumnTypeEnum(std::move(data));
    case 186:
      return new ::Ifc4x3::IfcCommunicationsAppliance(std::move(data));
    case 187:
      return new ::Ifc4x3::IfcCommunicationsApplianceType(std::move(data));
    case 188:
      return new ::Ifc4x3::IfcCommunicationsApplianceTypeEnum(std::move(data));
    case 189:
      return new ::Ifc4x3::IfcComplexNumber(std::move(data));
    case 190:
      return new ::Ifc4x3::IfcComplexProperty(std::move(data));
    case 191:
      return new ::Ifc4x3::IfcComplexPropertyTemplate(std::move(data));
    case 192:
      return new ::Ifc4x3::IfcComplexPropertyTemplateTypeEnum(std::move(data));
    case 193:
      return new ::Ifc4x3::IfcCompositeCurve(std::move(data));
    case 194:
      return new ::Ifc4x3::IfcCompositeCurveOnSurface(std::move(data));
    case 195:
      return new ::Ifc4x3::IfcCompositeCurveSegment(std::move(data));
    case 196:
      return new ::Ifc4x3::IfcCompositeProfileDef(std::move(data));
    case 197:
      return new ::Ifc4x3::IfcCompoundPlaneAngleMeasure(std::move(data));
    case 198:
      return new ::Ifc4x3::IfcCompressor(std::move(data));
    case 199:
      return new ::Ifc4x3::IfcCompressorType(std::move(data));
    case 200:
      return new ::Ifc4x3::IfcCompressorTypeEnum(std::move(data));
    case 201:
      return new ::Ifc4x3::IfcCondenser(std::move(data));
    case 202:
      return new ::Ifc4x3::IfcCondenserType(std::move(data));
    case 203:
      return new ::Ifc4x3::IfcCondenserTypeEnum(std::move(data));
    case 204:
      return new ::Ifc4x3::IfcConic(std::move(data));
    case 205:
      return new ::Ifc4x3::IfcConnectedFaceSet(std::move(data));
    case 206:
      return new ::Ifc4x3::IfcConnectionCurveGeometry(std::move(data));
    case 207:
      return new ::Ifc4x3::IfcConnectionGeometry(std::move(data));
    case 208:
      return new ::Ifc4x3::IfcConnectionPointEccentricity(std::move(data));
    case 209:
      return new ::Ifc4x3::IfcConnectionPointGeometry(std::move(data));
    case 210:
      return new ::Ifc4x3::IfcConnectionSurfaceGeometry(std::move(data));
    case 211:
      return new ::Ifc4x3::IfcConnectionTypeEnum(std::move(data));
    case 212:
      return new ::Ifc4x3::IfcConnectionVolumeGeometry(std::move(data));
    case 213:
      return new ::Ifc4x3::IfcConstraint(std::move(data));
    case 214:
      return new ::Ifc4x3::IfcConstraintEnum(std::move(data));
    case 215:
      return new ::Ifc4x3::IfcConstructionEquipmentResource(std::move(data));
    case 216:
      return new ::Ifc4x3::IfcConstructionEquipmentResourceType(
          std::move(data));
    case 217:
      return new ::Ifc4x3::IfcConstructionEquipmentResourceTypeEnum(
          std::move(data));
    case 218:
      return new ::Ifc4x3::IfcConstructionMaterialResource(std::move(data));
    case 219:
      return new ::Ifc4x3::IfcConstructionMaterialResourceType(std::move(data));
    case 220:
      return new ::Ifc4x3::IfcConstructionMaterialResourceTypeEnum(
          std::move(data));
    case 221:
      return new ::Ifc4x3::IfcConstructionProductResource(std::move(data));
    case 222:
      return new ::Ifc4x3::IfcConstructionProductResourceType(std::move(data));
    case 223:
      return new ::Ifc4x3::IfcConstructionProductResourceTypeEnum(
          std::move(data));
    case 224:
      return new ::Ifc4x3::IfcConstructionResource(std::move(data));
    case 225:
      return new ::Ifc4x3::IfcConstructionResourceType(std::move(data));
    case 226:
      return new ::Ifc4x3::IfcContext(std::move(data));
    case 227:
      return new ::Ifc4x3::IfcContextDependentMeasure(std::move(data));
    case 228:
      return new ::Ifc4x3::IfcContextDependentUnit(std::move(data));
    case 229:
      return new ::Ifc4x3::IfcControl(std::move(data));
    case 230:
      return new ::Ifc4x3::IfcController(std::move(data));
    case 231:
      return new ::Ifc4x3::IfcControllerType(std::move(data));
    case 232:
      return new ::Ifc4x3::IfcControllerTypeEnum(std::move(data));
    case 233:
      return new ::Ifc4x3::IfcConversionBasedUnit(std::move(data));
    case 234:
      return new ::Ifc4x3::IfcConversionBasedUnitWithOffset(std::move(data));
    case 235:
      return new ::Ifc4x3::IfcConveyorSegment(std::move(data));
    case 236:
      return new ::Ifc4x3::IfcConveyorSegmentType(std::move(data));
    case 237:
      return new ::Ifc4x3::IfcConveyorSegmentTypeEnum(std::move(data));
    case 238:
      return new ::Ifc4x3::IfcCooledBeam(std::move(data));
    case 239:
      return new ::Ifc4x3::IfcCooledBeamType(std::move(data));
    case 240:
      return new ::Ifc4x3::IfcCooledBeamTypeEnum(std::move(data));
    case 241:
      return new ::Ifc4x3::IfcCoolingTower(std::move(data));
    case 242:
      return new ::Ifc4x3::IfcCoolingTowerType(std::move(data));
    case 243:
      return new ::Ifc4x3::IfcCoolingTowerTypeEnum(std::move(data));
    case 244:
      return new ::Ifc4x3::IfcCoordinateOperation(std::move(data));
    case 245:
      return new ::Ifc4x3::IfcCoordinateReferenceSystem(std::move(data));
    case 247:
      return new ::Ifc4x3::IfcCosineSpiral(std::move(data));
    case 248:
      return new ::Ifc4x3::IfcCostItem(std::move(data));
    case 249:
      return new ::Ifc4x3::IfcCostItemTypeEnum(std::move(data));
    case 250:
      return new ::Ifc4x3::IfcCostSchedule(std::move(data));
    case 251:
      return new ::Ifc4x3::IfcCostScheduleTypeEnum(std::move(data));
    case 252:
      return new ::Ifc4x3::IfcCostValue(std::move(data));
    case 253:
      return new ::Ifc4x3::IfcCountMeasure(std::move(data));
    case 254:
      return new ::Ifc4x3::IfcCourse(std::move(data));
    case 255:
      return new ::Ifc4x3::IfcCourseType(std::move(data));
    case 256:
      return new ::Ifc4x3::IfcCourseTypeEnum(std::move(data));
    case 257:
      return new ::Ifc4x3::IfcCovering(std::move(data));
    case 258:
      return new ::Ifc4x3::IfcCoveringType(std::move(data));
    case 259:
      return new ::Ifc4x3::IfcCoveringTypeEnum(std::move(data));
    case 260:
      return new ::Ifc4x3::IfcCrewResource(std::move(data));
    case 261:
      return new ::Ifc4x3::IfcCrewResourceType(std::move(data));
    case 262:
      return new ::Ifc4x3::IfcCrewResourceTypeEnum(std::move(data));
    case 263:
      return new ::Ifc4x3::IfcCsgPrimitive3D(std::move(data));
    case 265:
      return new ::Ifc4x3::IfcCsgSolid(std::move(data));
    case 266:
      return new ::Ifc4x3::IfcCShapeProfileDef(std::move(data));
    case 267:
      return new ::Ifc4x3::IfcCurrencyRelationship(std::move(data));
    case 268:
      return new ::Ifc4x3::IfcCurtainWall(std::move(data));
    case 269:
      return new ::Ifc4x3::IfcCurtainWallType(std::move(data));
    case 270:
      return new ::Ifc4x3::IfcCurtainWallTypeEnum(std::move(data));
    case 271:
      return new ::Ifc4x3::IfcCurvatureMeasure(std::move(data));
    case 272:
      return new ::Ifc4x3::IfcCurve(std::move(data));
    case 273:
      return new ::Ifc4x3::IfcCurveBoundedPlane(std::move(data));
    case 274:
      return new ::Ifc4x3::IfcCurveBoundedSurface(std::move(data));
    case 276:
      return new ::Ifc4x3::IfcCurveInterpolationEnum(std::move(data));
    case 280:
      return new ::Ifc4x3::IfcCurveSegment(std::move(data));
    case 281:
      return new ::Ifc4x3::IfcCurveStyle(std::move(data));
    case 282:
      return new ::Ifc4x3::IfcCurveStyleFont(std::move(data));
    case 283:
      return new ::Ifc4x3::IfcCurveStyleFontAndScaling(std::move(data));
    case 284:
      return new ::Ifc4x3::IfcCurveStyleFontPattern(std::move(data));
    case 286:
      return new ::Ifc4x3::IfcCylindricalSurface(std::move(data));
    case 287:
      return new ::Ifc4x3::IfcDamper(std::move(data));
    case 288:
      return new ::Ifc4x3::IfcDamperType(std::move(data));
    case 289:
      return new ::Ifc4x3::IfcDamperTypeEnum(std::move(data));
    case 290:
      return new ::Ifc4x3::IfcDataOriginEnum(std::move(data));
    case 291:
      return new ::Ifc4x3::IfcDate(std::move(data));
    case 292:
      return new ::Ifc4x3::IfcDateTime(std::move(data));
    case 293:
      return new ::Ifc4x3::IfcDayInMonthNumber(std::move(data));
    case 294:
      return new ::Ifc4x3::IfcDayInWeekNumber(std::move(data));
    case 295:
      return new ::Ifc4x3::IfcDeepFoundation(std::move(data));
    case 296:
      return new ::Ifc4x3::IfcDeepFoundationType(std::move(data));
    case 299:
      return new ::Ifc4x3::IfcDerivedProfileDef(std::move(data));
    case 300:
      return new ::Ifc4x3::IfcDerivedUnit(std::move(data));
    case 301:
      return new ::Ifc4x3::IfcDerivedUnitElement(std::move(data));
    case 302:
      return new ::Ifc4x3::IfcDerivedUnitEnum(std::move(data));
    case 303:
      return new ::Ifc4x3::IfcDescriptiveMeasure(std::move(data));
    case 304:
      return new ::Ifc4x3::IfcDimensionalExponents(std::move(data));
    case 305:
      return new ::Ifc4x3::IfcDimensionCount(std::move(data));
    case 306:
      return new ::Ifc4x3::IfcDirection(std::move(data));
    case 307:
      return new ::Ifc4x3::IfcDirectionSenseEnum(std::move(data));
    case 308:
      return new ::Ifc4x3::IfcDirectrixCurveSweptAreaSolid(std::move(data));
    case 309:
      return new ::Ifc4x3::IfcDirectrixDerivedReferenceSweptAreaSolid(
          std::move(data));
    case 310:
      return new ::Ifc4x3::IfcDiscreteAccessory(std::move(data));
    case 311:
      return new ::Ifc4x3::IfcDiscreteAccessoryType(std::move(data));
    case 312:
      return new ::Ifc4x3::IfcDiscreteAccessoryTypeEnum(std::move(data));
    case 313:
      return new ::Ifc4x3::IfcDistributionBoard(std::move(data));
    case 314:
      return new ::Ifc4x3::IfcDistributionBoardType(std::move(data));
    case 315:
      return new ::Ifc4x3::IfcDistributionBoardTypeEnum(std::move(data));
    case 316:
      return new ::Ifc4x3::IfcDistributionChamberElement(std::move(data));
    case 317:
      return new ::Ifc4x3::IfcDistributionChamberElementType(std::move(data));
    case 318:
      return new ::Ifc4x3::IfcDistributionChamberElementTypeEnum(
          std::move(data));
    case 319:
      return new ::Ifc4x3::IfcDistributionCircuit(std::move(data));
    case 320:
      return new ::Ifc4x3::IfcDistributionControlElement(std::move(data));
    case 321:
      return new ::Ifc4x3::IfcDistributionControlElementType(std::move(data));
    case 322:
      return new ::Ifc4x3::IfcDistributionElement(std::move(data));
    case 323:
      return new ::Ifc4x3::IfcDistributionElementType(std::move(data));
    case 324:
      return new ::Ifc4x3::IfcDistributionFlowElement(std::move(data));
    case 325:
      return new ::Ifc4x3::IfcDistributionFlowElementType(std::move(data));
    case 326:
      return new ::Ifc4x3::IfcDistributionPort(std::move(data));
    case 327:
      return new ::Ifc4x3::IfcDistributionPortTypeEnum(std::move(data));
    case 328:
      return new ::Ifc4x3::IfcDistributionSystem(std::move(data));
    case 329:
      return new ::Ifc4x3::IfcDistributionSystemEnum(std::move(data));
    case 330:
      return new ::Ifc4x3::IfcDocumentConfidentialityEnum(std::move(data));
    case 331:
      return new ::Ifc4x3::IfcDocumentInformation(std::move(data));
    case 332:
      return new ::Ifc4x3::IfcDocumentInformationRelationship(std::move(data));
    case 333:
      return new ::Ifc4x3::IfcDocumentReference(std::move(data));
    case 335:
      return new ::Ifc4x3::IfcDocumentStatusEnum(std::move(data));
    case 336:
      return new ::Ifc4x3::IfcDoor(std::move(data));
    case 337:
      return new ::Ifc4x3::IfcDoorLiningProperties(std::move(data));
    case 338:
      return new ::Ifc4x3::IfcDoorPanelOperationEnum(std::move(data));
    case 339:
      return new ::Ifc4x3::IfcDoorPanelPositionEnum(std::move(data));
    case 340:
      return new ::Ifc4x3::IfcDoorPanelProperties(std::move(data));
    case 341:
      return new ::Ifc4x3::IfcDoorStyleConstructionEnum(std::move(data));
    case 342:
      return new ::Ifc4x3::IfcDoorStyleOperationEnum(std::move(data));
    case 343:
      return new ::Ifc4x3::IfcDoorType(std::move(data));
    case 344:
      return new ::Ifc4x3::IfcDoorTypeEnum(std::move(data));
    case 345:
      return new ::Ifc4x3::IfcDoorTypeOperationEnum(std::move(data));
    case 346:
      return new ::Ifc4x3::IfcDoseEquivalentMeasure(std::move(data));
    case 347:
      return new ::Ifc4x3::IfcDraughtingPreDefinedColour(std::move(data));
    case 348:
      return new ::Ifc4x3::IfcDraughtingPreDefinedCurveFont(std::move(data));
    case 349:
      return new ::Ifc4x3::IfcDuctFitting(std::move(data));
    case 350:
      return new ::Ifc4x3::IfcDuctFittingType(std::move(data));
    case 351:
      return new ::Ifc4x3::IfcDuctFittingTypeEnum(std::move(data));
    case 352:
      return new ::Ifc4x3::IfcDuctSegment(std::move(data));
    case 353:
      return new ::Ifc4x3::IfcDuctSegmentType(std::move(data));
    case 354:
      return new ::Ifc4x3::IfcDuctSegmentTypeEnum(std::move(data));
    case 355:
      return new ::Ifc4x3::IfcDuctSilencer(std::move(data));
    case 356:
      return new ::Ifc4x3::IfcDuctSilencerType(std::move(data));
    case 357:
      return new ::Ifc4x3::IfcDuctSilencerTypeEnum(std::move(data));
    case 358:
      return new ::Ifc4x3::IfcDuration(std::move(data));
    case 359:
      return new ::Ifc4x3::IfcDynamicViscosityMeasure(std::move(data));
    case 360:
      return new ::Ifc4x3::IfcEarthworksCut(std::move(data));
    case 361:
      return new ::Ifc4x3::IfcEarthworksCutTypeEnum(std::move(data));
    case 362:
      return new ::Ifc4x3::IfcEarthworksElement(std::move(data));
    case 363:
      return new ::Ifc4x3::IfcEarthworksFill(std::move(data));
    case 364:
      return new ::Ifc4x3::IfcEarthworksFillTypeEnum(std::move(data));
    case 365:
      return new ::Ifc4x3::IfcEdge(std::move(data));
    case 366:
      return new ::Ifc4x3::IfcEdgeCurve(std::move(data));
    case 367:
      return new ::Ifc4x3::IfcEdgeLoop(std::move(data));
    case 368:
      return new ::Ifc4x3::IfcElectricAppliance(std::move(data));
    case 369:
      return new ::Ifc4x3::IfcElectricApplianceType(std::move(data));
    case 370:
      return new ::Ifc4x3::IfcElectricApplianceTypeEnum(std::move(data));
    case 371:
      return new ::Ifc4x3::IfcElectricCapacitanceMeasure(std::move(data));
    case 372:
      return new ::Ifc4x3::IfcElectricChargeMeasure(std::move(data));
    case 373:
      return new ::Ifc4x3::IfcElectricConductanceMeasure(std::move(data));
    case 374:
      return new ::Ifc4x3::IfcElectricCurrentMeasure(std::move(data));
    case 375:
      return new ::Ifc4x3::IfcElectricDistributionBoard(std::move(data));
    case 376:
      return new ::Ifc4x3::IfcElectricDistributionBoardType(std::move(data));
    case 377:
      return new ::Ifc4x3::IfcElectricDistributionBoardTypeEnum(
          std::move(data));
    case 378:
      return new ::Ifc4x3::IfcElectricFlowStorageDevice(std::move(data));
    case 379:
      return new ::Ifc4x3::IfcElectricFlowStorageDeviceType(std::move(data));
    case 380:
      return new ::Ifc4x3::IfcElectricFlowStorageDeviceTypeEnum(
          std::move(data));
    case 381:
      return new ::Ifc4x3::IfcElectricFlowTreatmentDevice(std::move(data));
    case 382:
      return new ::Ifc4x3::IfcElectricFlowTreatmentDeviceType(std::move(data));
    case 383:
      return new ::Ifc4x3::IfcElectricFlowTreatmentDeviceTypeEnum(
          std::move(data));
    case 384:
      return new ::Ifc4x3::IfcElectricGenerator(std::move(data));
    case 385:
      return new ::Ifc4x3::IfcElectricGeneratorType(std::move(data));
    case 386:
      return new ::Ifc4x3::IfcElectricGeneratorTypeEnum(std::move(data));
    case 387:
      return new ::Ifc4x3::IfcElectricMotor(std::move(data));
    case 388:
      return new ::Ifc4x3::IfcElectricMotorType(std::move(data));
    case 389:
      return new ::Ifc4x3::IfcElectricMotorTypeEnum(std::move(data));
    case 390:
      return new ::Ifc4x3::IfcElectricResistanceMeasure(std::move(data));
    case 391:
      return new ::Ifc4x3::IfcElectricTimeControl(std::move(data));
    case 392:
      return new ::Ifc4x3::IfcElectricTimeControlType(std::move(data));
    case 393:
      return new ::Ifc4x3::IfcElectricTimeControlTypeEnum(std::move(data));
    case 394:
      return new ::Ifc4x3::IfcElectricVoltageMeasure(std::move(data));
    case 395:
      return new ::Ifc4x3::IfcElement(std::move(data));
    case 396:
      return new ::Ifc4x3::IfcElementarySurface(std::move(data));
    case 397:
      return new ::Ifc4x3::IfcElementAssembly(std::move(data));
    case 398:
      return new ::Ifc4x3::IfcElementAssemblyType(std::move(data));
    case 399:
      return new ::Ifc4x3::IfcElementAssemblyTypeEnum(std::move(data));
    case 400:
      return new ::Ifc4x3::IfcElementComponent(std::move(data));
    case 401:
      return new ::Ifc4x3::IfcElementComponentType(std::move(data));
    case 402:
      return new ::Ifc4x3::IfcElementCompositionEnum(std::move(data));
    case 403:
      return new ::Ifc4x3::IfcElementQuantity(std::move(data));
    case 404:
      return new ::Ifc4x3::IfcElementType(std::move(data));
    case 405:
      return new ::Ifc4x3::IfcEllipse(std::move(data));
    case 406:
      return new ::Ifc4x3::IfcEllipseProfileDef(std::move(data));
    case 407:
      return new ::Ifc4x3::IfcEnergyConversionDevice(std::move(data));
    case 408:
      return new ::Ifc4x3::IfcEnergyConversionDeviceType(std::move(data));
    case 409:
      return new ::Ifc4x3::IfcEnergyMeasure(std::move(data));
    case 410:
      return new ::Ifc4x3::IfcEngine(std::move(data));
    case 411:
      return new ::Ifc4x3::IfcEngineType(std::move(data));
    case 412:
      return new ::Ifc4x3::IfcEngineTypeEnum(std::move(data));
    case 413:
      return new ::Ifc4x3::IfcEvaporativeCooler(std::move(data));
    case 414:
      return new ::Ifc4x3::IfcEvaporativeCoolerType(std::move(data));
    case 415:
      return new ::Ifc4x3::IfcEvaporativeCoolerTypeEnum(std::move(data));
    case 416:
      return new ::Ifc4x3::IfcEvaporator(std::move(data));
    case 417:
      return new ::Ifc4x3::IfcEvaporatorType(std::move(data));
    case 418:
      return new ::Ifc4x3::IfcEvaporatorTypeEnum(std::move(data));
    case 419:
      return new ::Ifc4x3::IfcEvent(std::move(data));
    case 420:
      return new ::Ifc4x3::IfcEventTime(std::move(data));
    case 421:
      return new ::Ifc4x3::IfcEventTriggerTypeEnum(std::move(data));
    case 422:
      return new ::Ifc4x3::IfcEventType(std::move(data));
    case 423:
      return new ::Ifc4x3::IfcEventTypeEnum(std::move(data));
    case 424:
      return new ::Ifc4x3::IfcExtendedProperties(std::move(data));
    case 425:
      return new ::Ifc4x3::IfcExternalInformation(std::move(data));
    case 426:
      return new ::Ifc4x3::IfcExternallyDefinedHatchStyle(std::move(data));
    case 427:
      return new ::Ifc4x3::IfcExternallyDefinedSurfaceStyle(std::move(data));
    case 428:
      return new ::Ifc4x3::IfcExternallyDefinedTextFont(std::move(data));
    case 429:
      return new ::Ifc4x3::IfcExternalReference(std::move(data));
    case 430:
      return new ::Ifc4x3::IfcExternalReferenceRelationship(std::move(data));
    case 431:
      return new ::Ifc4x3::IfcExternalSpatialElement(std::move(data));
    case 432:
      return new ::Ifc4x3::IfcExternalSpatialElementTypeEnum(std::move(data));
    case 433:
      return new ::Ifc4x3::IfcExternalSpatialStructureElement(std::move(data));
    case 434:
      return new ::Ifc4x3::IfcExtrudedAreaSolid(std::move(data));
    case 435:
      return new ::Ifc4x3::IfcExtrudedAreaSolidTapered(std::move(data));
    case 436:
      return new ::Ifc4x3::IfcFace(std::move(data));
    case 437:
      return new ::Ifc4x3::IfcFaceBasedSurfaceModel(std::move(data));
    case 438:
      return new ::Ifc4x3::IfcFaceBound(std::move(data));
    case 439:
      return new ::Ifc4x3::IfcFaceOuterBound(std::move(data));
    case 440:
      return new ::Ifc4x3::IfcFaceSurface(std::move(data));
    case 441:
      return new ::Ifc4x3::IfcFacetedBrep(std::move(data));
    case 442:
      return new ::Ifc4x3::IfcFacetedBrepWithVoids(std::move(data));
    case 443:
      return new ::Ifc4x3::IfcFacility(std::move(data));
    case 444:
      return new ::Ifc4x3::IfcFacilityPart(std::move(data));
    case 445:
      return new ::Ifc4x3::IfcFacilityPartCommon(std::move(data));
    case 446:
      return new ::Ifc4x3::IfcFacilityPartCommonTypeEnum(std::move(data));
    case 447:
      return new ::Ifc4x3::IfcFacilityUsageEnum(std::move(data));
    case 448:
      return new ::Ifc4x3::IfcFailureConnectionCondition(std::move(data));
    case 449:
      return new ::Ifc4x3::IfcFan(std::move(data));
    case 450:
      return new ::Ifc4x3::IfcFanType(std::move(data));
    case 451:
      return new ::Ifc4x3::IfcFanTypeEnum(std::move(data));
    case 452:
      return new ::Ifc4x3::IfcFastener(std::move(data));
    case 453:
      return new ::Ifc4x3::IfcFastenerType(std::move(data));
    case 454:
      return new ::Ifc4x3::IfcFastenerTypeEnum(std::move(data));
    case 455:
      return new ::Ifc4x3::IfcFeatureElement(std::move(data));
    case 456:
      return new ::Ifc4x3::IfcFeatureElementAddition(std::move(data));
    case 457:
      return new ::Ifc4x3::IfcFeatureElementSubtraction(std::move(data));
    case 458:
      return new ::Ifc4x3::IfcFillAreaStyle(std::move(data));
    case 459:
      return new ::Ifc4x3::IfcFillAreaStyleHatching(std::move(data));
    case 460:
      return new ::Ifc4x3::IfcFillAreaStyleTiles(std::move(data));
    case 462:
      return new ::Ifc4x3::IfcFilter(std::move(data));
    case 463:
      return new ::Ifc4x3::IfcFilterType(std::move(data));
    case 464:
      return new ::Ifc4x3::IfcFilterTypeEnum(std::move(data));
    case 465:
      return new ::Ifc4x3::IfcFireSuppressionTerminal(std::move(data));
    case 466:
      return new ::Ifc4x3::IfcFireSuppressionTerminalType(std::move(data));
    case 467:
      return new ::Ifc4x3::IfcFireSuppressionTerminalTypeEnum(std::move(data));
    case 468:
      return new ::Ifc4x3::IfcFixedReferenceSweptAreaSolid(std::move(data));
    case 469:
      return new ::Ifc4x3::IfcFlowController(std::move(data));
    case 470:
      return new ::Ifc4x3::IfcFlowControllerType(std::move(data));
    case 471:
      return new ::Ifc4x3::IfcFlowDirectionEnum(std::move(data));
    case 472:
      return new ::Ifc4x3::IfcFlowFitting(std::move(data));
    case 473:
      return new ::Ifc4x3::IfcFlowFittingType(std::move(data));
    case 474:
      return new ::Ifc4x3::IfcFlowInstrument(std::move(data));
    case 475:
      return new ::Ifc4x3::IfcFlowInstrumentType(std::move(data));
    case 476:
      return new ::Ifc4x3::IfcFlowInstrumentTypeEnum(std::move(data));
    case 477:
      return new ::Ifc4x3::IfcFlowMeter(std::move(data));
    case 478:
      return new ::Ifc4x3::IfcFlowMeterType(std::move(data));
    case 479:
      return new ::Ifc4x3::IfcFlowMeterTypeEnum(std::move(data));
    case 480:
      return new ::Ifc4x3::IfcFlowMovingDevice(std::move(data));
    case 481:
      return new ::Ifc4x3::IfcFlowMovingDeviceType(std::move(data));
    case 482:
      return new ::Ifc4x3::IfcFlowSegment(std::move(data));
    case 483:
      return new ::Ifc4x3::IfcFlowSegmentType(std::move(data));
    case 484:
      return new ::Ifc4x3::IfcFlowStorageDevice(std::move(data));
    case 485:
      return new ::Ifc4x3::IfcFlowStorageDeviceType(std::move(data));
    case 486:
      return new ::Ifc4x3::IfcFlowTerminal(std::move(data));
    case 487:
      return new ::Ifc4x3::IfcFlowTerminalType(std::move(data));
    case 488:
      return new ::Ifc4x3::IfcFlowTreatmentDevice(std::move(data));
    case 489:
      return new ::Ifc4x3::IfcFlowTreatmentDeviceType(std::move(data));
    case 490:
      return new ::Ifc4x3::IfcFontStyle(std::move(data));
    case 491:
      return new ::Ifc4x3::IfcFontVariant(std::move(data));
    case 492:
      return new ::Ifc4x3::IfcFontWeight(std::move(data));
    case 493:
      return new ::Ifc4x3::IfcFooting(std::move(data));
    case 494:
      return new ::Ifc4x3::IfcFootingType(std::move(data));
    case 495:
      return new ::Ifc4x3::IfcFootingTypeEnum(std::move(data));
    case 496:
      return new ::Ifc4x3::IfcForceMeasure(std::move(data));
    case 497:
      return new ::Ifc4x3::IfcFrequencyMeasure(std::move(data));
    case 498:
      return new ::Ifc4x3::IfcFurnishingElement(std::move(data));
    case 499:
      return new ::Ifc4x3::IfcFurnishingElementType(std::move(data));
    case 500:
      return new ::Ifc4x3::IfcFurniture(std::move(data));
    case 501:
      return new ::Ifc4x3::IfcFurnitureType(std::move(data));
    case 502:
      return new ::Ifc4x3::IfcFurnitureTypeEnum(std::move(data));
    case 503:
      return new ::Ifc4x3::IfcGeographicElement(std::move(data));
    case 504:
      return new ::Ifc4x3::IfcGeographicElementType(std::move(data));
    case 505:
      return new ::Ifc4x3::IfcGeographicElementTypeEnum(std::move(data));
    case 506:
      return new ::Ifc4x3::IfcGeometricCurveSet(std::move(data));
    case 507:
      return new ::Ifc4x3::IfcGeometricProjectionEnum(std::move(data));
    case 508:
      return new ::Ifc4x3::IfcGeometricRepresentationContext(std::move(data));
    case 509:
      return new ::Ifc4x3::IfcGeometricRepresentationItem(std::move(data));
    case 510:
      return new ::Ifc4x3::IfcGeometricRepresentationSubContext(
          std::move(data));
    case 511:
      return new ::Ifc4x3::IfcGeometricSet(std::move(data));
    case 513:
      return new ::Ifc4x3::IfcGeomodel(std::move(data));
    case 514:
      return new ::Ifc4x3::IfcGeoslice(std::move(data));
    case 515:
      return new ::Ifc4x3::IfcGeotechnicalAssembly(std::move(data));
    case 516:
      return new ::Ifc4x3::IfcGeotechnicalElement(std::move(data));
    case 517:
      return new ::Ifc4x3::IfcGeotechnicalStratum(std::move(data));
    case 518:
      return new ::Ifc4x3::IfcGeotechnicalStratumTypeEnum(std::move(data));
    case 519:
      return new ::Ifc4x3::IfcGloballyUniqueId(std::move(data));
    case 520:
      return new ::Ifc4x3::IfcGlobalOrLocalEnum(std::move(data));
    case 521:
      return new ::Ifc4x3::IfcGradientCurve(std::move(data));
    case 522:
      return new ::Ifc4x3::IfcGrid(std::move(data));
    case 523:
      return new ::Ifc4x3::IfcGridAxis(std::move(data));
    case 524:
      return new ::Ifc4x3::IfcGridPlacement(std::move(data));
    case 526:
      return new ::Ifc4x3::IfcGridTypeEnum(std::move(data));
    case 527:
      return new ::Ifc4x3::IfcGroup(std::move(data));
    case 528:
      return new ::Ifc4x3::IfcHalfSpaceSolid(std::move(data));
    case 530:
      return new ::Ifc4x3::IfcHeatExchanger(std::move(data));
    case 531:
      return new ::Ifc4x3::IfcHeatExchangerType(std::move(data));
    case 532:
      return new ::Ifc4x3::IfcHeatExchangerTypeEnum(std::move(data));
    case 533:
      return new ::Ifc4x3::IfcHeatFluxDensityMeasure(std::move(data));
    case 534:
      return new ::Ifc4x3::IfcHeatingValueMeasure(std::move(data));
    case 535:
      return new ::Ifc4x3::IfcHumidifier(std::move(data));
    case 536:
      return new ::Ifc4x3::IfcHumidifierType(std::move(data));
    case 537:
      return new ::Ifc4x3::IfcHumidifierTypeEnum(std::move(data));
    case 538:
      return new ::Ifc4x3::IfcIdentifier(std::move(data));
    case 539:
      return new ::Ifc4x3::IfcIlluminanceMeasure(std::move(data));
    case 540:
      return new ::Ifc4x3::IfcImageTexture(std::move(data));
    case 541:
      return new ::Ifc4x3::IfcImpactProtectionDevice(std::move(data));
    case 542:
      return new ::Ifc4x3::IfcImpactProtectionDeviceType(std::move(data));
    case 543:
      return new ::Ifc4x3::IfcImpactProtectionDeviceTypeEnum(std::move(data));
    case 544:
      return new ::Ifc4x3::IfcIndexedColourMap(std::move(data));
    case 545:
      return new ::Ifc4x3::IfcIndexedPolyCurve(std::move(data));
    case 546:
      return new ::Ifc4x3::IfcIndexedPolygonalFace(std::move(data));
    case 547:
      return new ::Ifc4x3::IfcIndexedPolygonalFaceWithVoids(std::move(data));
    case 548:
      return new ::Ifc4x3::IfcIndexedPolygonalTextureMap(std::move(data));
    case 549:
      return new ::Ifc4x3::IfcIndexedTextureMap(std::move(data));
    case 550:
      return new ::Ifc4x3::IfcIndexedTriangleTextureMap(std::move(data));
    case 551:
      return new ::Ifc4x3::IfcInductanceMeasure(std::move(data));
    case 552:
      return new ::Ifc4x3::IfcInteger(std::move(data));
    case 553:
      return new ::Ifc4x3::IfcIntegerCountRateMeasure(std::move(data));
    case 554:
      return new ::Ifc4x3::IfcInterceptor(std::move(data));
    case 555:
      return new ::Ifc4x3::IfcInterceptorType(std::move(data));
    case 556:
      return new ::Ifc4x3::IfcInterceptorTypeEnum(std::move(data));
    case 558:
      return new ::Ifc4x3::IfcInternalOrExternalEnum(std::move(data));
    case 559:
      return new ::Ifc4x3::IfcIntersectionCurve(std::move(data));
    case 560:
      return new ::Ifc4x3::IfcInventory(std::move(data));
    case 561:
      return new ::Ifc4x3::IfcInventoryTypeEnum(std::move(data));
    case 562:
      return new ::Ifc4x3::IfcIonConcentrationMeasure(std::move(data));
    case 563:
      return new ::Ifc4x3::IfcIrregularTimeSeries(std::move(data));
    case 564:
      return new ::Ifc4x3::IfcIrregularTimeSeriesValue(std::move(data));
    case 565:
      return new ::Ifc4x3::IfcIShapeProfileDef(std::move(data));
    case 566:
      return new ::Ifc4x3::IfcIsothermalMoistureCapacityMeasure(
          std::move(data));
    case 567:
      return new ::Ifc4x3::IfcJunctionBox(std::move(data));
    case 568:
      return new ::Ifc4x3::IfcJunctionBoxType(std::move(data));
    case 569:
      return new ::Ifc4x3::IfcJunctionBoxTypeEnum(std::move(data));
    case 570:
      return new ::Ifc4x3::IfcKerb(std::move(data));
    case 571:
      return new ::Ifc4x3::IfcKerbType(std::move(data));
    case 572:
      return new ::Ifc4x3::IfcKinematicViscosityMeasure(std::move(data));
    case 573:
      return new ::Ifc4x3::IfcKnotType(std::move(data));
    case 574:
      return new ::Ifc4x3::IfcLabel(std::move(data));
    case 575:
      return new ::Ifc4x3::IfcLaborResource(std::move(data));
    case 576:
      return new ::Ifc4x3::IfcLaborResourceType(std::move(data));
    case 577:
      return new ::Ifc4x3::IfcLaborResourceTypeEnum(std::move(data));
    case 578:
      return new ::Ifc4x3::IfcLagTime(std::move(data));
    case 579:
      return new ::Ifc4x3::IfcLamp(std::move(data));
    case 580:
      return new ::Ifc4x3::IfcLampType(std::move(data));
    case 581:
      return new ::Ifc4x3::IfcLampTypeEnum(std::move(data));
    case 582:
      return new ::Ifc4x3::IfcLanguageId(std::move(data));
    case 584:
      return new ::Ifc4x3::IfcLayerSetDirectionEnum(std::move(data));
    case 585:
      return new ::Ifc4x3::IfcLengthMeasure(std::move(data));
    case 586:
      return new ::Ifc4x3::IfcLibraryInformation(std::move(data));
    case 587:
      return new ::Ifc4x3::IfcLibraryReference(std::move(data));
    case 589:
      return new ::Ifc4x3::IfcLightDistributionCurveEnum(std::move(data));
    case 590:
      return new ::Ifc4x3::IfcLightDistributionData(std::move(data));
    case 592:
      return new ::Ifc4x3::IfcLightEmissionSourceEnum(std::move(data));
    case 593:
      return new ::Ifc4x3::IfcLightFixture(std::move(data));
    case 594:
      return new ::Ifc4x3::IfcLightFixtureType(std::move(data));
    case 595:
      return new ::Ifc4x3::IfcLightFixtureTypeEnum(std::move(data));
    case 596:
      return new ::Ifc4x3::IfcLightIntensityDistribution(std::move(data));
    case 597:
      return new ::Ifc4x3::IfcLightSource(std::move(data));
    case 598:
      return new ::Ifc4x3::IfcLightSourceAmbient(std::move(data));
    case 599:
      return new ::Ifc4x3::IfcLightSourceDirectional(std::move(data));
    case 600:
      return new ::Ifc4x3::IfcLightSourceGoniometric(std::move(data));
    case 601:
      return new ::Ifc4x3::IfcLightSourcePositional(std::move(data));
    case 602:
      return new ::Ifc4x3::IfcLightSourceSpot(std::move(data));
    case 603:
      return new ::Ifc4x3::IfcLine(std::move(data));
    case 604:
      return new ::Ifc4x3::IfcLinearElement(std::move(data));
    case 605:
      return new ::Ifc4x3::IfcLinearForceMeasure(std::move(data));
    case 606:
      return new ::Ifc4x3::IfcLinearMomentMeasure(std::move(data));
    case 607:
      return new ::Ifc4x3::IfcLinearPlacement(std::move(data));
    case 608:
      return new ::Ifc4x3::IfcLinearPositioningElement(std::move(data));
    case 609:
      return new ::Ifc4x3::IfcLinearStiffnessMeasure(std::move(data));
    case 610:
      return new ::Ifc4x3::IfcLinearVelocityMeasure(std::move(data));
    case 611:
      return new ::Ifc4x3::IfcLineIndex(std::move(data));
    case 612:
      return new ::Ifc4x3::IfcLiquidTerminal(std::move(data));
    case 613:
      return new ::Ifc4x3::IfcLiquidTerminalType(std::move(data));
    case 614:
      return new ::Ifc4x3::IfcLiquidTerminalTypeEnum(std::move(data));
    case 615:
      return new ::Ifc4x3::IfcLoadGroupTypeEnum(std::move(data));
    case 616:
      return new ::Ifc4x3::IfcLocalPlacement(std::move(data));
    case 617:
      return new ::Ifc4x3::IfcLogical(std::move(data));
    case 618:
      return new ::Ifc4x3::IfcLogicalOperatorEnum(std::move(data));
    case 619:
      return new ::Ifc4x3::IfcLoop(std::move(data));
    case 620:
      return new ::Ifc4x3::IfcLShapeProfileDef(std::move(data));
    case 621:
      return new ::Ifc4x3::IfcLuminousFluxMeasure(std::move(data));
    case 622:
      return new ::Ifc4x3::IfcLuminousIntensityDistributionMeasure(
          std::move(data));
    case 623:
      return new ::Ifc4x3::IfcLuminousIntensityMeasure(std::move(data));
    case 624:
      return new ::Ifc4x3::IfcMagneticFluxDensityMeasure(std::move(data));
    case 625:
      return new ::Ifc4x3::IfcMagneticFluxMeasure(std::move(data));
    case 626:
      return new ::Ifc4x3::IfcManifoldSolidBrep(std::move(data));
    case 627:
      return new ::Ifc4x3::IfcMapConversion(std::move(data));
    case 628:
      return new ::Ifc4x3::IfcMappedItem(std::move(data));
    case 629:
      return new ::Ifc4x3::IfcMarineFacility(std::move(data));
    case 630:
      return new ::Ifc4x3::IfcMarineFacilityTypeEnum(std::move(data));
    case 631:
      return new ::Ifc4x3::IfcMarinePart(std::move(data));
    case 632:
      return new ::Ifc4x3::IfcMarinePartTypeEnum(std::move(data));
    case 633:
      return new ::Ifc4x3::IfcMassDensityMeasure(std::move(data));
    case 634:
      return new ::Ifc4x3::IfcMassFlowRateMeasure(std::move(data));
    case 635:
      return new ::Ifc4x3::IfcMassMeasure(std::move(data));
    case 636:
      return new ::Ifc4x3::IfcMassPerLengthMeasure(std::move(data));
    case 637:
      return new ::Ifc4x3::IfcMaterial(std::move(data));
    case 638:
      return new ::Ifc4x3::IfcMaterialClassificationRelationship(
          std::move(data));
    case 639:
      return new ::Ifc4x3::IfcMaterialConstituent(std::move(data));
    case 640:
      return new ::Ifc4x3::IfcMaterialConstituentSet(std::move(data));
    case 641:
      return new ::Ifc4x3::IfcMaterialDefinition(std::move(data));
    case 642:
      return new ::Ifc4x3::IfcMaterialDefinitionRepresentation(std::move(data));
    case 643:
      return new ::Ifc4x3::IfcMaterialLayer(std::move(data));
    case 644:
      return new ::Ifc4x3::IfcMaterialLayerSet(std::move(data));
    case 645:
      return new ::Ifc4x3::IfcMaterialLayerSetUsage(std::move(data));
    case 646:
      return new ::Ifc4x3::IfcMaterialLayerWithOffsets(std::move(data));
    case 647:
      return new ::Ifc4x3::IfcMaterialList(std::move(data));
    case 648:
      return new ::Ifc4x3::IfcMaterialProfile(std::move(data));
    case 649:
      return new ::Ifc4x3::IfcMaterialProfileSet(std::move(data));
    case 650:
      return new ::Ifc4x3::IfcMaterialProfileSetUsage(std::move(data));
    case 651:
      return new ::Ifc4x3::IfcMaterialProfileSetUsageTapering(std::move(data));
    case 652:
      return new ::Ifc4x3::IfcMaterialProfileWithOffsets(std::move(data));
    case 653:
      return new ::Ifc4x3::IfcMaterialProperties(std::move(data));
    case 654:
      return new ::Ifc4x3::IfcMaterialRelationship(std::move(data));
    case 656:
      return new ::Ifc4x3::IfcMaterialUsageDefinition(std::move(data));
    case 658:
      return new ::Ifc4x3::IfcMeasureWithUnit(std::move(data));
    case 659:
      return new ::Ifc4x3::IfcMechanicalFastener(std::move(data));
    case 660:
      return new ::Ifc4x3::IfcMechanicalFastenerType(std::move(data));
    case 661:
      return new ::Ifc4x3::IfcMechanicalFastenerTypeEnum(std::move(data));
    case 662:
      return new ::Ifc4x3::IfcMedicalDevice(std::move(data));
    case 663:
      return new ::Ifc4x3::IfcMedicalDeviceType(std::move(data));
    case 664:
      return new ::Ifc4x3::IfcMedicalDeviceTypeEnum(std::move(data));
    case 665:
      return new ::Ifc4x3::IfcMember(std::move(data));
    case 666:
      return new ::Ifc4x3::IfcMemberType(std::move(data));
    case 667:
      return new ::Ifc4x3::IfcMemberTypeEnum(std::move(data));
    case 668:
      return new ::Ifc4x3::IfcMetric(std::move(data));
    case 670:
      return new ::Ifc4x3::IfcMirroredProfileDef(std::move(data));
    case 671:
      return new ::Ifc4x3::IfcMobileTelecommunicationsAppliance(
          std::move(data));
    case 672:
      return new ::Ifc4x3::IfcMobileTelecommunicationsApplianceType(
          std::move(data));
    case 673:
      return new ::Ifc4x3::IfcMobileTelecommunicationsApplianceTypeEnum(
          std::move(data));
    case 674:
      return new ::Ifc4x3::IfcModulusOfElasticityMeasure(std::move(data));
    case 675:
      return new ::Ifc4x3::IfcModulusOfLinearSubgradeReactionMeasure(
          std::move(data));
    case 676:
      return new ::Ifc4x3::IfcModulusOfRotationalSubgradeReactionMeasure(
          std::move(data));
    case 678:
      return new ::Ifc4x3::IfcModulusOfSubgradeReactionMeasure(std::move(data));
    case 681:
      return new ::Ifc4x3::IfcMoistureDiffusivityMeasure(std::move(data));
    case 682:
      return new ::Ifc4x3::IfcMolecularWeightMeasure(std::move(data));
    case 683:
      return new ::Ifc4x3::IfcMomentOfInertiaMeasure(std::move(data));
    case 684:
      return new ::Ifc4x3::IfcMonetaryMeasure(std::move(data));
    case 685:
      return new ::Ifc4x3::IfcMonetaryUnit(std::move(data));
    case 686:
      return new ::Ifc4x3::IfcMonthInYearNumber(std::move(data));
    case 687:
      return new ::Ifc4x3::IfcMooringDevice(std::move(data));
    case 688:
      return new ::Ifc4x3::IfcMooringDeviceType(std::move(data));
    case 689:
      return new ::Ifc4x3::IfcMooringDeviceTypeEnum(std::move(data));
    case 690:
      return new ::Ifc4x3::IfcMotorConnection(std::move(data));
    case 691:
      return new ::Ifc4x3::IfcMotorConnectionType(std::move(data));
    case 692:
      return new ::Ifc4x3::IfcMotorConnectionTypeEnum(std::move(data));
    case 693:
      return new ::Ifc4x3::IfcNamedUnit(std::move(data));
    case 694:
      return new ::Ifc4x3::IfcNavigationElement(std::move(data));
    case 695:
      return new ::Ifc4x3::IfcNavigationElementType(std::move(data));
    case 696:
      return new ::Ifc4x3::IfcNavigationElementTypeEnum(std::move(data));
    case 697:
      return new ::Ifc4x3::IfcNonNegativeLengthMeasure(std::move(data));
    case 698:
      return new ::Ifc4x3::IfcNormalisedRatioMeasure(std::move(data));
    case 699:
      return new ::Ifc4x3::IfcNumericMeasure(std::move(data));
    case 700:
      return new ::Ifc4x3::IfcObject(std::move(data));
    case 701:
      return new ::Ifc4x3::IfcObjectDefinition(std::move(data));
    case 702:
      return new ::Ifc4x3::IfcObjective(std::move(data));
    case 703:
      return new ::Ifc4x3::IfcObjectiveEnum(std::move(data));
    case 704:
      return new ::Ifc4x3::IfcObjectPlacement(std::move(data));
    case 706:
      return new ::Ifc4x3::IfcObjectTypeEnum(std::move(data));
    case 707:
      return new ::Ifc4x3::IfcOccupant(std::move(data));
    case 708:
      return new ::Ifc4x3::IfcOccupantTypeEnum(std::move(data));
    case 709:
      return new ::Ifc4x3::IfcOffsetCurve(std::move(data));
    case 710:
      return new ::Ifc4x3::IfcOffsetCurve2D(std::move(data));
    case 711:
      return new ::Ifc4x3::IfcOffsetCurve3D(std::move(data));
    case 712:
      return new ::Ifc4x3::IfcOffsetCurveByDistances(std::move(data));
    case 713:
      return new ::Ifc4x3::IfcOpenCrossProfileDef(std::move(data));
    case 714:
      return new ::Ifc4x3::IfcOpeningElement(std::move(data));
    case 715:
      return new ::Ifc4x3::IfcOpeningElementTypeEnum(std::move(data));
    case 716:
      return new ::Ifc4x3::IfcOpenShell(std::move(data));
    case 717:
      return new ::Ifc4x3::IfcOrganization(std::move(data));
    case 718:
      return new ::Ifc4x3::IfcOrganizationRelationship(std::move(data));
    case 719:
      return new ::Ifc4x3::IfcOrientedEdge(std::move(data));
    case 720:
      return new ::Ifc4x3::IfcOuterBoundaryCurve(std::move(data));
    case 721:
      return new ::Ifc4x3::IfcOutlet(std::move(data));
    case 722:
      return new ::Ifc4x3::IfcOutletType(std::move(data));
    case 723:
      return new ::Ifc4x3::IfcOutletTypeEnum(std::move(data));
    case 724:
      return new ::Ifc4x3::IfcOwnerHistory(std::move(data));
    case 725:
      return new ::Ifc4x3::IfcParameterizedProfileDef(std::move(data));
    case 726:
      return new ::Ifc4x3::IfcParameterValue(std::move(data));
    case 727:
      return new ::Ifc4x3::IfcPath(std::move(data));
    case 728:
      return new ::Ifc4x3::IfcPavement(std::move(data));
    case 729:
      return new ::Ifc4x3::IfcPavementType(std::move(data));
    case 730:
      return new ::Ifc4x3::IfcPavementTypeEnum(std::move(data));
    case 731:
      return new ::Ifc4x3::IfcPcurve(std::move(data));
    case 732:
      return new ::Ifc4x3::IfcPerformanceHistory(std::move(data));
    case 733:
      return new ::Ifc4x3::IfcPerformanceHistoryTypeEnum(std::move(data));
    case 734:
      return new ::Ifc4x3::IfcPermeableCoveringOperationEnum(std::move(data));
    case 735:
      return new ::Ifc4x3::IfcPermeableCoveringProperties(std::move(data));
    case 736:
      return new ::Ifc4x3::IfcPermit(std::move(data));
    case 737:
      return new ::Ifc4x3::IfcPermitTypeEnum(std::move(data));
    case 738:
      return new ::Ifc4x3::IfcPerson(std::move(data));
    case 739:
      return new ::Ifc4x3::IfcPersonAndOrganization(std::move(data));
    case 740:
      return new ::Ifc4x3::IfcPHMeasure(std::move(data));
    case 741:
      return new ::Ifc4x3::IfcPhysicalComplexQuantity(std::move(data));
    case 742:
      return new ::Ifc4x3::IfcPhysicalOrVirtualEnum(std::move(data));
    case 743:
      return new ::Ifc4x3::IfcPhysicalQuantity(std::move(data));
    case 744:
      return new ::Ifc4x3::IfcPhysicalSimpleQuantity(std::move(data));
    case 745:
      return new ::Ifc4x3::IfcPile(std::move(data));
    case 746:
      return new ::Ifc4x3::IfcPileConstructionEnum(std::move(data));
    case 747:
      return new ::Ifc4x3::IfcPileType(std::move(data));
    case 748:
      return new ::Ifc4x3::IfcPileTypeEnum(std::move(data));
    case 749:
      return new ::Ifc4x3::IfcPipeFitting(std::move(data));
    case 750:
      return new ::Ifc4x3::IfcPipeFittingType(std::move(data));
    case 751:
      return new ::Ifc4x3::IfcPipeFittingTypeEnum(std::move(data));
    case 752:
      return new ::Ifc4x3::IfcPipeSegment(std::move(data));
    case 753:
      return new ::Ifc4x3::IfcPipeSegmentType(std::move(data));
    case 754:
      return new ::Ifc4x3::IfcPipeSegmentTypeEnum(std::move(data));
    case 755:
      return new ::Ifc4x3::IfcPixelTexture(std::move(data));
    case 756:
      return new ::Ifc4x3::IfcPlacement(std::move(data));
    case 757:
      return new ::Ifc4x3::IfcPlanarBox(std::move(data));
    case 758:
      return new ::Ifc4x3::IfcPlanarExtent(std::move(data));
    case 759:
      return new ::Ifc4x3::IfcPlanarForceMeasure(std::move(data));
    case 760:
      return new ::Ifc4x3::IfcPlane(std::move(data));
    case 761:
      return new ::Ifc4x3::IfcPlaneAngleMeasure(std::move(data));
    case 762:
      return new ::Ifc4x3::IfcPlate(std::move(data));
    case 763:
      return new ::Ifc4x3::IfcPlateType(std::move(data));
    case 764:
      return new ::Ifc4x3::IfcPlateTypeEnum(std::move(data));
    case 765:
      return new ::Ifc4x3::IfcPoint(std::move(data));
    case 766:
      return new ::Ifc4x3::IfcPointByDistanceExpression(std::move(data));
    case 767:
      return new ::Ifc4x3::IfcPointOnCurve(std::move(data));
    case 768:
      return new ::Ifc4x3::IfcPointOnSurface(std::move(data));
    case 770:
      return new ::Ifc4x3::IfcPolygonalBoundedHalfSpace(std::move(data));
    case 771:
      return new ::Ifc4x3::IfcPolygonalFaceSet(std::move(data));
    case 772:
      return new ::Ifc4x3::IfcPolyline(std::move(data));
    case 773:
      return new ::Ifc4x3::IfcPolyLoop(std::move(data));
    case 774:
      return new ::Ifc4x3::IfcPolynomialCurve(std::move(data));
    case 775:
      return new ::Ifc4x3::IfcPort(std::move(data));
    case 776:
      return new ::Ifc4x3::IfcPositioningElement(std::move(data));
    case 777:
      return new ::Ifc4x3::IfcPositiveInteger(std::move(data));
    case 778:
      return new ::Ifc4x3::IfcPositiveLengthMeasure(std::move(data));
    case 779:
      return new ::Ifc4x3::IfcPositivePlaneAngleMeasure(std::move(data));
    case 780:
      return new ::Ifc4x3::IfcPositiveRatioMeasure(std::move(data));
    case 781:
      return new ::Ifc4x3::IfcPostalAddress(std::move(data));
    case 782:
      return new ::Ifc4x3::IfcPowerMeasure(std::move(data));
    case 783:
      return new ::Ifc4x3::IfcPreDefinedColour(std::move(data));
    case 784:
      return new ::Ifc4x3::IfcPreDefinedCurveFont(std::move(data));
    case 785:
      return new ::Ifc4x3::IfcPreDefinedItem(std::move(data));
    case 786:
      return new ::Ifc4x3::IfcPreDefinedProperties(std::move(data));
    case 787:
      return new ::Ifc4x3::IfcPreDefinedPropertySet(std::move(data));
    case 788:
      return new ::Ifc4x3::IfcPreDefinedTextFont(std::move(data));
    case 789:
      return new ::Ifc4x3::IfcPreferredSurfaceCurveRepresentation(
          std::move(data));
    case 790:
      return new ::Ifc4x3::IfcPresentableText(std::move(data));
    case 791:
      return new ::Ifc4x3::IfcPresentationItem(std::move(data));
    case 792:
      return new ::Ifc4x3::IfcPresentationLayerAssignment(std::move(data));
    case 793:
      return new ::Ifc4x3::IfcPresentationLayerWithStyle(std::move(data));
    case 794:
      return new ::Ifc4x3::IfcPresentationStyle(std::move(data));
    case 795:
      return new ::Ifc4x3::IfcPressureMeasure(std::move(data));
    case 796:
      return new ::Ifc4x3::IfcProcedure(std::move(data));
    case 797:
      return new ::Ifc4x3::IfcProcedureType(std::move(data));
    case 798:
      return new ::Ifc4x3::IfcProcedureTypeEnum(std::move(data));
    case 799:
      return new ::Ifc4x3::IfcProcess(std::move(data));
    case 801:
      return new ::Ifc4x3::IfcProduct(std::move(data));
    case 802:
      return new ::Ifc4x3::IfcProductDefinitionShape(std::move(data));
    case 803:
      return new ::Ifc4x3::IfcProductRepresentation(std::move(data));
    case 806:
      return new ::Ifc4x3::IfcProfileDef(std::move(data));
    case 807:
      return new ::Ifc4x3::IfcProfileProperties(std::move(data));
    case 808:
      return new ::Ifc4x3::IfcProfileTypeEnum(std::move(data));
    case 809:
      return new ::Ifc4x3::IfcProject(std::move(data));
    case 810:
      return new ::Ifc4x3::IfcProjectedCRS(std::move(data));
    case 811:
      return new ::Ifc4x3::IfcProjectedOrTrueLengthEnum(std::move(data));
    case 812:
      return new ::Ifc4x3::IfcProjectionElement(std::move(data));
    case 813:
      return new ::Ifc4x3::IfcProjectionElementTypeEnum(std::move(data));
    case 814:
      return new ::Ifc4x3::IfcProjectLibrary(std::move(data));
    case 815:
      return new ::Ifc4x3::IfcProjectOrder(std::move(data));
    case 816:
      return new ::Ifc4x3::IfcProjectOrderTypeEnum(std::move(data));
    case 817:
      return new ::Ifc4x3::IfcProperty(std::move(data));
    case 818:
      return new ::Ifc4x3::IfcPropertyAbstraction(std::move(data));
    case 819:
      return new ::Ifc4x3::IfcPropertyBoundedValue(std::move(data));
    case 820:
      return new ::Ifc4x3::IfcPropertyDefinition(std::move(data));
    case 821:
      return new ::Ifc4x3::IfcPropertyDependencyRelationship(std::move(data));
    case 822:
      return new ::Ifc4x3::IfcPropertyEnumeratedValue(std::move(data));
    case 823:
      return new ::Ifc4x3::IfcPropertyEnumeration(std::move(data));
    case 824:
      return new ::Ifc4x3::IfcPropertyListValue(std::move(data));
    case 825:
      return new ::Ifc4x3::IfcPropertyReferenceValue(std::move(data));
    case 826:
      return new ::Ifc4x3::IfcPropertySet(std::move(data));
    case 827:
      return new ::Ifc4x3::IfcPropertySetDefinition(std::move(data));
    case 829:
      return new ::Ifc4x3::IfcPropertySetDefinitionSet(std::move(data));
    case 830:
      return new ::Ifc4x3::IfcPropertySetTemplate(std::move(data));
    case 831:
      return new ::Ifc4x3::IfcPropertySetTemplateTypeEnum(std::move(data));
    case 832:
      return new ::Ifc4x3::IfcPropertySingleValue(std::move(data));
    case 833:
      return new ::Ifc4x3::IfcPropertyTableValue(std::move(data));
    case 834:
      return new ::Ifc4x3::IfcPropertyTemplate(std::move(data));
    case 835:
      return new ::Ifc4x3::IfcPropertyTemplateDefinition(std::move(data));
    case 836:
      return new ::Ifc4x3::IfcProtectiveDevice(std::move(data));
    case 837:
      return new ::Ifc4x3::IfcProtectiveDeviceTrippingUnit(std::move(data));
    case 838:
      return new ::Ifc4x3::IfcProtectiveDeviceTrippingUnitType(std::move(data));
    case 839:
      return new ::Ifc4x3::IfcProtectiveDeviceTrippingUnitTypeEnum(
          std::move(data));
    case 840:
      return new ::Ifc4x3::IfcProtectiveDeviceType(std::move(data));
    case 841:
      return new ::Ifc4x3::IfcProtectiveDeviceTypeEnum(std::move(data));
    case 842:
      return new ::Ifc4x3::IfcPump(std::move(data));
    case 843:
      return new ::Ifc4x3::IfcPumpType(std::move(data));
    case 844:
      return new ::Ifc4x3::IfcPumpTypeEnum(std::move(data));
    case 845:
      return new ::Ifc4x3::IfcQuantityArea(std::move(data));
    case 846:
      return new ::Ifc4x3::IfcQuantityCount(std::move(data));
    case 847:
      return new ::Ifc4x3::IfcQuantityLength(std::move(data));
    case 848:
      return new ::Ifc4x3::IfcQuantityNumber(std::move(data));
    case 849:
      return new ::Ifc4x3::IfcQuantitySet(std::move(data));
    case 850:
      return new ::Ifc4x3::IfcQuantityTime(std::move(data));
    case 851:
      return new ::Ifc4x3::IfcQuantityVolume(std::move(data));
    case 852:
      return new ::Ifc4x3::IfcQuantityWeight(std::move(data));
    case 853:
      return new ::Ifc4x3::IfcRadioActivityMeasure(std::move(data));
    case 854:
      return new ::Ifc4x3::IfcRail(std::move(data));
    case 855:
      return new ::Ifc4x3::IfcRailing(std::move(data));
    case 856:
      return new ::Ifc4x3::IfcRailingType(std::move(data));
    case 857:
      return new ::Ifc4x3::IfcRailingTypeEnum(std::move(data));
    case 858:
      return new ::Ifc4x3::IfcRailType(std::move(data));
    case 859:
      return new ::Ifc4x3::IfcRailTypeEnum(std::move(data));
    case 860:
      return new ::Ifc4x3::IfcRailway(std::move(data));
    case 861:
      return new ::Ifc4x3::IfcRailwayPart(std::move(data));
    case 862:
      return new ::Ifc4x3::IfcRailwayPartTypeEnum(std::move(data));
    case 863:
      return new ::Ifc4x3::IfcRailwayTypeEnum(std::move(data));
    case 864:
      return new ::Ifc4x3::IfcRamp(std::move(data));
    case 865:
      return new ::Ifc4x3::IfcRampFlight(std::move(data));
    case 866:
      return new ::Ifc4x3::IfcRampFlightType(std::move(data));
    case 867:
      return new ::Ifc4x3::IfcRampFlightTypeEnum(std::move(data));
    case 868:
      return new ::Ifc4x3::IfcRampType(std::move(data));
    case 869:
      return new ::Ifc4x3::IfcRampTypeEnum(std::move(data));
    case 870:
      return new ::Ifc4x3::IfcRatioMeasure(std::move(data));
    case 871:
      return new ::Ifc4x3::IfcRationalBSplineCurveWithKnots(std::move(data));
    case 872:
      return new ::Ifc4x3::IfcRationalBSplineSurfaceWithKnots(std::move(data));
    case 873:
      return new ::Ifc4x3::IfcReal(std::move(data));
    case 874:
      return new ::Ifc4x3::IfcRectangleHollowProfileDef(std::move(data));
    case 875:
      return new ::Ifc4x3::IfcRectangleProfileDef(std::move(data));
    case 876:
      return new ::Ifc4x3::IfcRectangularPyramid(std::move(data));
    case 877:
      return new ::Ifc4x3::IfcRectangularTrimmedSurface(std::move(data));
    case 878:
      return new ::Ifc4x3::IfcRecurrencePattern(std::move(data));
    case 879:
      return new ::Ifc4x3::IfcRecurrenceTypeEnum(std::move(data));
    case 880:
      return new ::Ifc4x3::IfcReference(std::move(data));
    case 881:
      return new ::Ifc4x3::IfcReferent(std::move(data));
    case 882:
      return new ::Ifc4x3::IfcReferentTypeEnum(std::move(data));
    case 883:
      return new ::Ifc4x3::IfcReflectanceMethodEnum(std::move(data));
    case 884:
      return new ::Ifc4x3::IfcRegularTimeSeries(std::move(data));
    case 885:
      return new ::Ifc4x3::IfcReinforcedSoil(std::move(data));
    case 886:
      return new ::Ifc4x3::IfcReinforcedSoilTypeEnum(std::move(data));
    case 887:
      return new ::Ifc4x3::IfcReinforcementBarProperties(std::move(data));
    case 888:
      return new ::Ifc4x3::IfcReinforcementDefinitionProperties(
          std::move(data));
    case 889:
      return new ::Ifc4x3::IfcReinforcingBar(std::move(data));
    case 890:
      return new ::Ifc4x3::IfcReinforcingBarRoleEnum(std::move(data));
    case 891:
      return new ::Ifc4x3::IfcReinforcingBarSurfaceEnum(std::move(data));
    case 892:
      return new ::Ifc4x3::IfcReinforcingBarType(std::move(data));
    case 893:
      return new ::Ifc4x3::IfcReinforcingBarTypeEnum(std::move(data));
    case 894:
      return new ::Ifc4x3::IfcReinforcingElement(std::move(data));
    case 895:
      return new ::Ifc4x3::IfcReinforcingElementType(std::move(data));
    case 896:
      return new ::Ifc4x3::IfcReinforcingMesh(std::move(data));
    case 897:
      return new ::Ifc4x3::IfcReinforcingMeshType(std::move(data));
    case 898:
      return new ::Ifc4x3::IfcReinforcingMeshTypeEnum(std::move(data));
    case 899:
      return new ::Ifc4x3::IfcRelAdheresToElement(std::move(data));
    case 900:
      return new ::Ifc4x3::IfcRelAggregates(std::move(data));
    case 901:
      return new ::Ifc4x3::IfcRelAssigns(std::move(data));
    case 902:
      return new ::Ifc4x3::IfcRelAssignsToActor(std::move(data));
    case 903:
      return new ::Ifc4x3::IfcRelAssignsToControl(std::move(data));
    case 904:
      return new ::Ifc4x3::IfcRelAssignsToGroup(std::move(data));
    case 905:
      return new ::Ifc4x3::IfcRelAssignsToGroupByFactor(std::move(data));
    case 906:
      return new ::Ifc4x3::IfcRelAssignsToProcess(std::move(data));
    case 907:
      return new ::Ifc4x3::IfcRelAssignsToProduct(std::move(data));
    case 908:
      return new ::Ifc4x3::IfcRelAssignsToResource(std::move(data));
    case 909:
      return new ::Ifc4x3::IfcRelAssociates(std::move(data));
    case 910:
      return new ::Ifc4x3::IfcRelAssociatesApproval(std::move(data));
    case 911:
      return new ::Ifc4x3::IfcRelAssociatesClassification(std::move(data));
    case 912:
      return new ::Ifc4x3::IfcRelAssociatesConstraint(std::move(data));
    case 913:
      return new ::Ifc4x3::IfcRelAssociatesDocument(std::move(data));
    case 914:
      return new ::Ifc4x3::IfcRelAssociatesLibrary(std::move(data));
    case 915:
      return new ::Ifc4x3::IfcRelAssociatesMaterial(std::move(data));
    case 916:
      return new ::Ifc4x3::IfcRelAssociatesProfileDef(std::move(data));
    case 917:
      return new ::Ifc4x3::IfcRelationship(std::move(data));
    case 918:
      return new ::Ifc4x3::IfcRelConnects(std::move(data));
    case 919:
      return new ::Ifc4x3::IfcRelConnectsElements(std::move(data));
    case 920:
      return new ::Ifc4x3::IfcRelConnectsPathElements(std::move(data));
    case 921:
      return new ::Ifc4x3::IfcRelConnectsPorts(std::move(data));
    case 922:
      return new ::Ifc4x3::IfcRelConnectsPortToElement(std::move(data));
    case 923:
      return new ::Ifc4x3::IfcRelConnectsStructuralActivity(std::move(data));
    case 924:
      return new ::Ifc4x3::IfcRelConnectsStructuralMember(std::move(data));
    case 925:
      return new ::Ifc4x3::IfcRelConnectsWithEccentricity(std::move(data));
    case 926:
      return new ::Ifc4x3::IfcRelConnectsWithRealizingElements(std::move(data));
    case 927:
      return new ::Ifc4x3::IfcRelContainedInSpatialStructure(std::move(data));
    case 928:
      return new ::Ifc4x3::IfcRelCoversBldgElements(std::move(data));
    case 929:
      return new ::Ifc4x3::IfcRelCoversSpaces(std::move(data));
    case 930:
      return new ::Ifc4x3::IfcRelDeclares(std::move(data));
    case 931:
      return new ::Ifc4x3::IfcRelDecomposes(std::move(data));
    case 932:
      return new ::Ifc4x3::IfcRelDefines(std::move(data));
    case 933:
      return new ::Ifc4x3::IfcRelDefinesByObject(std::move(data));
    case 934:
      return new ::Ifc4x3::IfcRelDefinesByProperties(std::move(data));
    case 935:
      return new ::Ifc4x3::IfcRelDefinesByTemplate(std::move(data));
    case 936:
      return new ::Ifc4x3::IfcRelDefinesByType(std::move(data));
    case 937:
      return new ::Ifc4x3::IfcRelFillsElement(std::move(data));
    case 938:
      return new ::Ifc4x3::IfcRelFlowControlElements(std::move(data));
    case 939:
      return new ::Ifc4x3::IfcRelInterferesElements(std::move(data));
    case 940:
      return new ::Ifc4x3::IfcRelNests(std::move(data));
    case 941:
      return new ::Ifc4x3::IfcRelPositions(std::move(data));
    case 942:
      return new ::Ifc4x3::IfcRelProjectsElement(std::move(data));
    case 943:
      return new ::Ifc4x3::IfcRelReferencedInSpatialStructure(std::move(data));
    case 944:
      return new ::Ifc4x3::IfcRelSequence(std::move(data));
    case 945:
      return new ::Ifc4x3::IfcRelServicesBuildings(std::move(data));
    case 946:
      return new ::Ifc4x3::IfcRelSpaceBoundary(std::move(data));
    case 947:
      return new ::Ifc4x3::IfcRelSpaceBoundary1stLevel(std::move(data));
    case 948:
      return new ::Ifc4x3::IfcRelSpaceBoundary2ndLevel(std::move(data));
    case 949:
      return new ::Ifc4x3::IfcRelVoidsElement(std::move(data));
    case 950:
      return new ::Ifc4x3::IfcReparametrisedCompositeCurveSegment(
          std::move(data));
    case 951:
      return new ::Ifc4x3::IfcRepresentation(std::move(data));
    case 952:
      return new ::Ifc4x3::IfcRepresentationContext(std::move(data));
    case 953:
      return new ::Ifc4x3::IfcRepresentationItem(std::move(data));
    case 954:
      return new ::Ifc4x3::IfcRepresentationMap(std::move(data));
    case 955:
      return new ::Ifc4x3::IfcResource(std::move(data));
    case 956:
      return new ::Ifc4x3::IfcResourceApprovalRelationship(std::move(data));
    case 957:
      return new ::Ifc4x3::IfcResourceConstraintRelationship(std::move(data));
    case 958:
      return new ::Ifc4x3::IfcResourceLevelRelationship(std::move(data));
    case 961:
      return new ::Ifc4x3::IfcResourceTime(std::move(data));
    case 962:
      return new ::Ifc4x3::IfcRevolvedAreaSolid(std::move(data));
    case 963:
      return new ::Ifc4x3::IfcRevolvedAreaSolidTapered(std::move(data));
    case 964:
      return new ::Ifc4x3::IfcRightCircularCone(std::move(data));
    case 965:
      return new ::Ifc4x3::IfcRightCircularCylinder(std::move(data));
    case 966:
      return new ::Ifc4x3::IfcRoad(std::move(data));
    case 967:
      return new ::Ifc4x3::IfcRoadPart(std::move(data));
    case 968:
      return new ::Ifc4x3::IfcRoadPartTypeEnum(std::move(data));
    case 969:
      return new ::Ifc4x3::IfcRoadTypeEnum(std::move(data));
    case 970:
      return new ::Ifc4x3::IfcRoleEnum(std::move(data));
    case 971:
      return new ::Ifc4x3::IfcRoof(std::move(data));
    case 972:
      return new ::Ifc4x3::IfcRoofType(std::move(data));
    case 973:
      return new ::Ifc4x3::IfcRoofTypeEnum(std::move(data));
    case 974:
      return new ::Ifc4x3::IfcRoot(std::move(data));
    case 975:
      return new ::Ifc4x3::IfcRotationalFrequencyMeasure(std::move(data));
    case 976:
      return new ::Ifc4x3::IfcRotationalMassMeasure(std::move(data));
    case 977:
      return new ::Ifc4x3::IfcRotationalStiffnessMeasure(std::move(data));
    case 979:
      return new ::Ifc4x3::IfcRoundedRectangleProfileDef(std::move(data));
    case 980:
      return new ::Ifc4x3::IfcSanitaryTerminal(std::move(data));
    case 981:
      return new ::Ifc4x3::IfcSanitaryTerminalType(std::move(data));
    case 982:
      return new ::Ifc4x3::IfcSanitaryTerminalTypeEnum(std::move(data));
    case 983:
      return new ::Ifc4x3::IfcSchedulingTime(std::move(data));
    case 984:
      return new ::Ifc4x3::IfcSeamCurve(std::move(data));
    case 985:
      return new ::Ifc4x3::IfcSecondOrderPolynomialSpiral(std::move(data));
    case 986:
      return new ::Ifc4x3::IfcSectionalAreaIntegralMeasure(std::move(data));
    case 987:
      return new ::Ifc4x3::IfcSectionedSolid(std::move(data));
    case 988:
      return new ::Ifc4x3::IfcSectionedSolidHorizontal(std::move(data));
    case 989:
      return new ::Ifc4x3::IfcSectionedSpine(std::move(data));
    case 990:
      return new ::Ifc4x3::IfcSectionedSurface(std::move(data));
    case 991:
      return new ::Ifc4x3::IfcSectionModulusMeasure(std::move(data));
    case 992:
      return new ::Ifc4x3::IfcSectionProperties(std::move(data));
    case 993:
      return new ::Ifc4x3::IfcSectionReinforcementProperties(std::move(data));
    case 994:
      return new ::Ifc4x3::IfcSectionTypeEnum(std::move(data));
    case 995:
      return new ::Ifc4x3::IfcSegment(std::move(data));
    case 996:
      return new ::Ifc4x3::IfcSegmentedReferenceCurve(std::move(data));
    case 998:
      return new ::Ifc4x3::IfcSensor(std::move(data));
    case 999:
      return new ::Ifc4x3::IfcSensorType(std::move(data));
    case 1000:
      return new ::Ifc4x3::IfcSensorTypeEnum(std::move(data));
    case 1001:
      return new ::Ifc4x3::IfcSequenceEnum(std::move(data));
    case 1002:
      return new ::Ifc4x3::IfcSeventhOrderPolynomialSpiral(std::move(data));
    case 1003:
      return new ::Ifc4x3::IfcShadingDevice(std::move(data));
    case 1004:
      return new ::Ifc4x3::IfcShadingDeviceType(std::move(data));
    case 1005:
      return new ::Ifc4x3::IfcShadingDeviceTypeEnum(std::move(data));
    case 1006:
      return new ::Ifc4x3::IfcShapeAspect(std::move(data));
    case 1007:
      return new ::Ifc4x3::IfcShapeModel(std::move(data));
    case 1008:
      return new ::Ifc4x3::IfcShapeRepresentation(std::move(data));
    case 1009:
      return new ::Ifc4x3::IfcShearModulusMeasure(std::move(data));
    case 1011:
      return new ::Ifc4x3::IfcShellBasedSurfaceModel(std::move(data));
    case 1012:
      return new ::Ifc4x3::IfcSign(std::move(data));
    case 1013:
      return new ::Ifc4x3::IfcSignal(std::move(data));
    case 1014:
      return new ::Ifc4x3::IfcSignalType(std::move(data));
    case 1015:
      return new ::Ifc4x3::IfcSignalTypeEnum(std::move(data));
    case 1016:
      return new ::Ifc4x3::IfcSignType(std::move(data));
    case 1017:
      return new ::Ifc4x3::IfcSignTypeEnum(std::move(data));
    case 1018:
      return new ::Ifc4x3::IfcSimpleProperty(std::move(data));
    case 1019:
      return new ::Ifc4x3::IfcSimplePropertyTemplate(std::move(data));
    case 1020:
      return new ::Ifc4x3::IfcSimplePropertyTemplateTypeEnum(std::move(data));
    case 1022:
      return new ::Ifc4x3::IfcSineSpiral(std::move(data));
    case 1023:
      return new ::Ifc4x3::IfcSIPrefix(std::move(data));
    case 1024:
      return new ::Ifc4x3::IfcSite(std::move(data));
    case 1025:
      return new ::Ifc4x3::IfcSIUnit(std::move(data));
    case 1026:
      return new ::Ifc4x3::IfcSIUnitName(std::move(data));
    case 1028:
      return new ::Ifc4x3::IfcSlab(std::move(data));
    case 1029:
      return new ::Ifc4x3::IfcSlabType(std::move(data));
    case 1030:
      return new ::Ifc4x3::IfcSlabTypeEnum(std::move(data));
    case 1031:
      return new ::Ifc4x3::IfcSlippageConnectionCondition(std::move(data));
    case 1032:
      return new ::Ifc4x3::IfcSolarDevice(std::move(data));
    case 1033:
      return new ::Ifc4x3::IfcSolarDeviceType(std::move(data));
    case 1034:
      return new ::Ifc4x3::IfcSolarDeviceTypeEnum(std::move(data));
    case 1035:
      return new ::Ifc4x3::IfcSolidAngleMeasure(std::move(data));
    case 1036:
      return new ::Ifc4x3::IfcSolidModel(std::move(data));
    case 1038:
      return new ::Ifc4x3::IfcSoundPowerLevelMeasure(std::move(data));
    case 1039:
      return new ::Ifc4x3::IfcSoundPowerMeasure(std::move(data));
    case 1040:
      return new ::Ifc4x3::IfcSoundPressureLevelMeasure(std::move(data));
    case 1041:
      return new ::Ifc4x3::IfcSoundPressureMeasure(std::move(data));
    case 1042:
      return new ::Ifc4x3::IfcSpace(std::move(data));
    case 1044:
      return new ::Ifc4x3::IfcSpaceHeater(std::move(data));
    case 1045:
      return new ::Ifc4x3::IfcSpaceHeaterType(std::move(data));
    case 1046:
      return new ::Ifc4x3::IfcSpaceHeaterTypeEnum(std::move(data));
    case 1047:
      return new ::Ifc4x3::IfcSpaceType(std::move(data));
    case 1048:
      return new ::Ifc4x3::IfcSpaceTypeEnum(std::move(data));
    case 1049:
      return new ::Ifc4x3::IfcSpatialElement(std::move(data));
    case 1050:
      return new ::Ifc4x3::IfcSpatialElementType(std::move(data));
    case 1052:
      return new ::Ifc4x3::IfcSpatialStructureElement(std::move(data));
    case 1053:
      return new ::Ifc4x3::IfcSpatialStructureElementType(std::move(data));
    case 1054:
      return new ::Ifc4x3::IfcSpatialZone(std::move(data));
    case 1055:
      return new ::Ifc4x3::IfcSpatialZoneType(std::move(data));
    case 1056:
      return new ::Ifc4x3::IfcSpatialZoneTypeEnum(std::move(data));
    case 1057:
      return new ::Ifc4x3::IfcSpecificHeatCapacityMeasure(std::move(data));
    case 1058:
      return new ::Ifc4x3::IfcSpecularExponent(std::move(data));
    case 1060:
      return new ::Ifc4x3::IfcSpecularRoughness(std::move(data));
    case 1061:
      return new ::Ifc4x3::IfcSphere(std::move(data));
    case 1062:
      return new ::Ifc4x3::IfcSphericalSurface(std::move(data));
    case 1063:
      return new ::Ifc4x3::IfcSpiral(std::move(data));
    case 1064:
      return new ::Ifc4x3::IfcStackTerminal(std::move(data));
    case 1065:
      return new ::Ifc4x3::IfcStackTerminalType(std::move(data));
    case 1066:
      return new ::Ifc4x3::IfcStackTerminalTypeEnum(std::move(data));
    case 1067:
      return new ::Ifc4x3::IfcStair(std::move(data));
    case 1068:
      return new ::Ifc4x3::IfcStairFlight(std::move(data));
    case 1069:
      return new ::Ifc4x3::IfcStairFlightType(std::move(data));
    case 1070:
      return new ::Ifc4x3::IfcStairFlightTypeEnum(std::move(data));
    case 1071:
      return new ::Ifc4x3::IfcStairType(std::move(data));
    case 1072:
      return new ::Ifc4x3::IfcStairTypeEnum(std::move(data));
    case 1073:
      return new ::Ifc4x3::IfcStateEnum(std::move(data));
    case 1074:
      return new ::Ifc4x3::IfcStructuralAction(std::move(data));
    case 1075:
      return new ::Ifc4x3::IfcStructuralActivity(std::move(data));
    case 1077:
      return new ::Ifc4x3::IfcStructuralAnalysisModel(std::move(data));
    case 1078:
      return new ::Ifc4x3::IfcStructuralConnection(std::move(data));
    case 1079:
      return new ::Ifc4x3::IfcStructuralConnectionCondition(std::move(data));
    case 1080:
      return new ::Ifc4x3::IfcStructuralCurveAction(std::move(data));
    case 1081:
      return new ::Ifc4x3::IfcStructuralCurveActivityTypeEnum(std::move(data));
    case 1082:
      return new ::Ifc4x3::IfcStructuralCurveConnection(std::move(data));
    case 1083:
      return new ::Ifc4x3::IfcStructuralCurveMember(std::move(data));
    case 1084:
      return new ::Ifc4x3::IfcStructuralCurveMemberTypeEnum(std::move(data));
    case 1085:
      return new ::Ifc4x3::IfcStructuralCurveMemberVarying(std::move(data));
    case 1086:
      return new ::Ifc4x3::IfcStructuralCurveReaction(std::move(data));
    case 1087:
      return new ::Ifc4x3::IfcStructuralItem(std::move(data));
    case 1088:
      return new ::Ifc4x3::IfcStructuralLinearAction(std::move(data));
    case 1089:
      return new ::Ifc4x3::IfcStructuralLoad(std::move(data));
    case 1090:
      return new ::Ifc4x3::IfcStructuralLoadCase(std::move(data));
    case 1091:
      return new ::Ifc4x3::IfcStructuralLoadConfiguration(std::move(data));
    case 1092:
      return new ::Ifc4x3::IfcStructuralLoadGroup(std::move(data));
    case 1093:
      return new ::Ifc4x3::IfcStructuralLoadLinearForce(std::move(data));
    case 1094:
      return new ::Ifc4x3::IfcStructuralLoadOrResult(std::move(data));
    case 1095:
      return new ::Ifc4x3::IfcStructuralLoadPlanarForce(std::move(data));
    case 1096:
      return new ::Ifc4x3::IfcStructuralLoadSingleDisplacement(std::move(data));
    case 1097:
      return new ::Ifc4x3::IfcStructuralLoadSingleDisplacementDistortion(
          std::move(data));
    case 1098:
      return new ::Ifc4x3::IfcStructuralLoadSingleForce(std::move(data));
    case 1099:
      return new ::Ifc4x3::IfcStructuralLoadSingleForceWarping(std::move(data));
    case 1100:
      return new ::Ifc4x3::IfcStructuralLoadStatic(std::move(data));
    case 1101:
      return new ::Ifc4x3::IfcStructuralLoadTemperature(std::move(data));
    case 1102:
      return new ::Ifc4x3::IfcStructuralMember(std::move(data));
    case 1103:
      return new ::Ifc4x3::IfcStructuralPlanarAction(std::move(data));
    case 1104:
      return new ::Ifc4x3::IfcStructuralPointAction(std::move(data));
    case 1105:
      return new ::Ifc4x3::IfcStructuralPointConnection(std::move(data));
    case 1106:
      return new ::Ifc4x3::IfcStructuralPointReaction(std::move(data));
    case 1107:
      return new ::Ifc4x3::IfcStructuralReaction(std::move(data));
    case 1108:
      return new ::Ifc4x3::IfcStructuralResultGroup(std::move(data));
    case 1109:
      return new ::Ifc4x3::IfcStructuralSurfaceAction(std::move(data));
    case 1110:
      return new ::Ifc4x3::IfcStructuralSurfaceActivityTypeEnum(
          std::move(data));
    case 1111:
      return new ::Ifc4x3::IfcStructuralSurfaceConnection(std::move(data));
    case 1112:
      return new ::Ifc4x3::IfcStructuralSurfaceMember(std::move(data));
    case 1113:
      return new ::Ifc4x3::IfcStructuralSurfaceMemberTypeEnum(std::move(data));
    case 1114:
      return new ::Ifc4x3::IfcStructuralSurfaceMemberVarying(std::move(data));
    case 1115:
      return new ::Ifc4x3::IfcStructuralSurfaceReaction(std::move(data));
    case 1116:
      return new ::Ifc4x3::IfcStyledItem(std::move(data));
    case 1117:
      return new ::Ifc4x3::IfcStyledRepresentation(std::move(data));
    case 1118:
      return new ::Ifc4x3::IfcStyleModel(std::move(data));
    case 1119:
      return new ::Ifc4x3::IfcSubContractResource(std::move(data));
    case 1120:
      return new ::Ifc4x3::IfcSubContractResourceType(std::move(data));
    case 1121:
      return new ::Ifc4x3::IfcSubContractResourceTypeEnum(std::move(data));
    case 1122:
      return new ::Ifc4x3::IfcSubedge(std::move(data));
    case 1123:
      return new ::Ifc4x3::IfcSurface(std::move(data));
    case 1124:
      return new ::Ifc4x3::IfcSurfaceCurve(std::move(data));
    case 1125:
      return new ::Ifc4x3::IfcSurfaceCurveSweptAreaSolid(std::move(data));
    case 1126:
      return new ::Ifc4x3::IfcSurfaceFeature(std::move(data));
    case 1127:
      return new ::Ifc4x3::IfcSurfaceFeatureTypeEnum(std::move(data));
    case 1128:
      return new ::Ifc4x3::IfcSurfaceOfLinearExtrusion(std::move(data));
    case 1129:
      return new ::Ifc4x3::IfcSurfaceOfRevolution(std::move(data));
    case 1131:
      return new ::Ifc4x3::IfcSurfaceReinforcementArea(std::move(data));
    case 1132:
      return new ::Ifc4x3::IfcSurfaceSide(std::move(data));
    case 1133:
      return new ::Ifc4x3::IfcSurfaceStyle(std::move(data));
    case 1135:
      return new ::Ifc4x3::IfcSurfaceStyleLighting(std::move(data));
    case 1136:
      return new ::Ifc4x3::IfcSurfaceStyleRefraction(std::move(data));
    case 1137:
      return new ::Ifc4x3::IfcSurfaceStyleRendering(std::move(data));
    case 1138:
      return new ::Ifc4x3::IfcSurfaceStyleShading(std::move(data));
    case 1139:
      return new ::Ifc4x3::IfcSurfaceStyleWithTextures(std::move(data));
    case 1140:
      return new ::Ifc4x3::IfcSurfaceTexture(std::move(data));
    case 1141:
      return new ::Ifc4x3::IfcSweptAreaSolid(std::move(data));
    case 1142:
      return new ::Ifc4x3::IfcSweptDiskSolid(std::move(data));
    case 1143:
      return new ::Ifc4x3::IfcSweptDiskSolidPolygonal(std::move(data));
    case 1144:
      return new ::Ifc4x3::IfcSweptSurface(std::move(data));
    case 1145:
      return new ::Ifc4x3::IfcSwitchingDevice(std::move(data));
    case 1146:
      return new ::Ifc4x3::IfcSwitchingDeviceType(std::move(data));
    case 1147:
      return new ::Ifc4x3::IfcSwitchingDeviceTypeEnum(std::move(data));
    case 1148:
      return new ::Ifc4x3::IfcSystem(std::move(data));
    case 1149:
      return new ::Ifc4x3::IfcSystemFurnitureElement(std::move(data));
    case 1150:
      return new ::Ifc4x3::IfcSystemFurnitureElementType(std::move(data));
    case 1151:
      return new ::Ifc4x3::IfcSystemFurnitureElementTypeEnum(std::move(data));
    case 1152:
      return new ::Ifc4x3::IfcTable(std::move(data));
    case 1153:
      return new ::Ifc4x3::IfcTableColumn(std::move(data));
    case 1154:
      return new ::Ifc4x3::IfcTableRow(std::move(data));
    case 1155:
      return new ::Ifc4x3::IfcTank(std::move(data));
    case 1156:
      return new ::Ifc4x3::IfcTankType(std::move(data));
    case 1157:
      return new ::Ifc4x3::IfcTankTypeEnum(std::move(data));
    case 1158:
      return new ::Ifc4x3::IfcTask(std::move(data));
    case 1159:
      return new ::Ifc4x3::IfcTaskDurationEnum(std::move(data));
    case 1160:
      return new ::Ifc4x3::IfcTaskTime(std::move(data));
    case 1161:
      return new ::Ifc4x3::IfcTaskTimeRecurring(std::move(data));
    case 1162:
      return new ::Ifc4x3::IfcTaskType(std::move(data));
    case 1163:
      return new ::Ifc4x3::IfcTaskTypeEnum(std::move(data));
    case 1164:
      return new ::Ifc4x3::IfcTelecomAddress(std::move(data));
    case 1165:
      return new ::Ifc4x3::IfcTemperatureGradientMeasure(std::move(data));
    case 1166:
      return new ::Ifc4x3::IfcTemperatureRateOfChangeMeasure(std::move(data));
    case 1167:
      return new ::Ifc4x3::IfcTendon(std::move(data));
    case 1168:
      return new ::Ifc4x3::IfcTendonAnchor(std::move(data));
    case 1169:
      return new ::Ifc4x3::IfcTendonAnchorType(std::move(data));
    case 1170:
      return new ::Ifc4x3::IfcTendonAnchorTypeEnum(std::move(data));
    case 1171:
      return new ::Ifc4x3::IfcTendonConduit(std::move(data));
    case 1172:
      return new ::Ifc4x3::IfcTendonConduitType(std::move(data));
    case 1173:
      return new ::Ifc4x3::IfcTendonConduitTypeEnum(std::move(data));
    case 1174:
      return new ::Ifc4x3::IfcTendonType(std::move(data));
    case 1175:
      return new ::Ifc4x3::IfcTendonTypeEnum(std::move(data));
    case 1176:
      return new ::Ifc4x3::IfcTessellatedFaceSet(std::move(data));
    case 1177:
      return new ::Ifc4x3::IfcTessellatedItem(std::move(data));
    case 1178:
      return new ::Ifc4x3::IfcText(std::move(data));
    case 1179:
      return new ::Ifc4x3::IfcTextAlignment(std::move(data));
    case 1180:
      return new ::Ifc4x3::IfcTextDecoration(std::move(data));
    case 1181:
      return new ::Ifc4x3::IfcTextFontName(std::move(data));
    case 1183:
      return new ::Ifc4x3::IfcTextLiteral(std::move(data));
    case 1184:
      return new ::Ifc4x3::IfcTextLiteralWithExtent(std::move(data));
    case 1185:
      return new ::Ifc4x3::IfcTextPath(std::move(data));
    case 1186:
      return new ::Ifc4x3::IfcTextStyle(std::move(data));
    case 1187:
      return new ::Ifc4x3::IfcTextStyleFontModel(std::move(data));
    case 1188:
      return new ::Ifc4x3::IfcTextStyleForDefinedFont(std::move(data));
    case 1189:
      return new ::Ifc4x3::IfcTextStyleTextModel(std::move(data));
    case 1190:
      return new ::Ifc4x3::IfcTextTransformation(std::move(data));
    case 1191:
      return new ::Ifc4x3::IfcTextureCoordinate(std::move(data));
    case 1192:
      return new ::Ifc4x3::IfcTextureCoordinateGenerator(std::move(data));
    case 1193:
      return new ::Ifc4x3::IfcTextureCoordinateIndices(std::move(data));
    case 1194:
      return new ::Ifc4x3::IfcTextureCoordinateIndicesWithVoids(
          std::move(data));
    case 1195:
      return new ::Ifc4x3::IfcTextureMap(std::move(data));
    case 1196:
      return new ::Ifc4x3::IfcTextureVertex(std::move(data));
    case 1197:
      return new ::Ifc4x3::IfcTextureVertexList(std::move(data));
    case 1198:
      return new ::Ifc4x3::IfcThermalAdmittanceMeasure(std::move(data));
    case 1199:
      return new ::Ifc4x3::IfcThermalConductivityMeasure(std::move(data));
    case 1200:
      return new ::Ifc4x3::IfcThermalExpansionCoefficientMeasure(
          std::move(data));
    case 1201:
      return new ::Ifc4x3::IfcThermalResistanceMeasure(std::move(data));
    case 1202:
      return new ::Ifc4x3::IfcThermalTransmittanceMeasure(std::move(data));
    case 1203:
      return new ::Ifc4x3::IfcThermodynamicTemperatureMeasure(std::move(data));
    case 1204:
      return new ::Ifc4x3::IfcThirdOrderPolynomialSpiral(std::move(data));
    case 1205:
      return new ::Ifc4x3::IfcTime(std::move(data));
    case 1206:
      return new ::Ifc4x3::IfcTimeMeasure(std::move(data));
    case 1208:
      return new ::Ifc4x3::IfcTimePeriod(std::move(data));
    case 1209:
      return new ::Ifc4x3::IfcTimeSeries(std::move(data));
    case 1210:
      return new ::Ifc4x3::IfcTimeSeriesDataTypeEnum(std::move(data));
    case 1211:
      return new ::Ifc4x3::IfcTimeSeriesValue(std::move(data));
    case 1212:
      return new ::Ifc4x3::IfcTimeStamp(std::move(data));
    case 1213:
      return new ::Ifc4x3::IfcTopologicalRepresentationItem(std::move(data));
    case 1214:
      return new ::Ifc4x3::IfcTopologyRepresentation(std::move(data));
    case 1215:
      return new ::Ifc4x3::IfcToroidalSurface(std::move(data));
    case 1216:
      return new ::Ifc4x3::IfcTorqueMeasure(std::move(data));
    case 1217:
      return new ::Ifc4x3::IfcTrackElement(std::move(data));
    case 1218:
      return new ::Ifc4x3::IfcTrackElementType(std::move(data));
    case 1219:
      return new ::Ifc4x3::IfcTrackElementTypeEnum(std::move(data));
    case 1220:
      return new ::Ifc4x3::IfcTransformer(std::move(data));
    case 1221:
      return new ::Ifc4x3::IfcTransformerType(std::move(data));
    case 1222:
      return new ::Ifc4x3::IfcTransformerTypeEnum(std::move(data));
    case 1223:
      return new ::Ifc4x3::IfcTransitionCode(std::move(data));
    case 1225:
      return new ::Ifc4x3::IfcTransportationDevice(std::move(data));
    case 1226:
      return new ::Ifc4x3::IfcTransportationDeviceType(std::move(data));
    case 1227:
      return new ::Ifc4x3::IfcTransportElement(std::move(data));
    case 1228:
      return new ::Ifc4x3::IfcTransportElementType(std::move(data));
    case 1229:
      return new ::Ifc4x3::IfcTransportElementTypeEnum(std::move(data));
    case 1230:
      return new ::Ifc4x3::IfcTrapeziumProfileDef(std::move(data));
    case 1231:
      return new ::Ifc4x3::IfcTriangulatedFaceSet(std::move(data));
    case 1232:
      return new ::Ifc4x3::IfcTriangulatedIrregularNetwork(std::move(data));
    case 1233:
      return new ::Ifc4x3::IfcTrimmedCurve(std::move(data));
    case 1234:
      return new ::Ifc4x3::IfcTrimmingPreference(std::move(data));
    case 1236:
      return new ::Ifc4x3::IfcTShapeProfileDef(std::move(data));
    case 1237:
      return new ::Ifc4x3::IfcTubeBundle(std::move(data));
    case 1238:
      return new ::Ifc4x3::IfcTubeBundleType(std::move(data));
    case 1239:
      return new ::Ifc4x3::IfcTubeBundleTypeEnum(std::move(data));
    case 1240:
      return new ::Ifc4x3::IfcTypeObject(std::move(data));
    case 1241:
      return new ::Ifc4x3::IfcTypeProcess(std::move(data));
    case 1242:
      return new ::Ifc4x3::IfcTypeProduct(std::move(data));
    case 1243:
      return new ::Ifc4x3::IfcTypeResource(std::move(data));
    case 1245:
      return new ::Ifc4x3::IfcUnitaryControlElement(std::move(data));
    case 1246:
      return new ::Ifc4x3::IfcUnitaryControlElementType(std::move(data));
    case 1247:
      return new ::Ifc4x3::IfcUnitaryControlElementTypeEnum(std::move(data));
    case 1248:
      return new ::Ifc4x3::IfcUnitaryEquipment(std::move(data));
    case 1249:
      return new ::Ifc4x3::IfcUnitaryEquipmentType(std::move(data));
    case 1250:
      return new ::Ifc4x3::IfcUnitaryEquipmentTypeEnum(std::move(data));
    case 1251:
      return new ::Ifc4x3::IfcUnitAssignment(std::move(data));
    case 1252:
      return new ::Ifc4x3::IfcUnitEnum(std::move(data));
    case 1253:
      return new ::Ifc4x3::IfcURIReference(std::move(data));
    case 1254:
      return new ::Ifc4x3::IfcUShapeProfileDef(std::move(data));
    case 1256:
      return new ::Ifc4x3::IfcValve(std::move(data));
    case 1257:
      return new ::Ifc4x3::IfcValveType(std::move(data));
    case 1258:
      return new ::Ifc4x3::IfcValveTypeEnum(std::move(data));
    case 1259:
      return new ::Ifc4x3::IfcVaporPermeabilityMeasure(std::move(data));
    case 1260:
      return new ::Ifc4x3::IfcVector(std::move(data));
    case 1262:
      return new ::Ifc4x3::IfcVehicle(std::move(data));
    case 1263:
      return new ::Ifc4x3::IfcVehicleType(std::move(data));
    case 1264:
      return new ::Ifc4x3::IfcVehicleTypeEnum(std::move(data));
    case 1265:
      return new ::Ifc4x3::IfcVertex(std::move(data));
    case 1266:
      return new ::Ifc4x3::IfcVertexLoop(std::move(data));
    case 1267:
      return new ::Ifc4x3::IfcVertexPoint(std::move(data));
    case 1268:
      return new ::Ifc4x3::IfcVibrationDamper(std::move(data));
    case 1269:
      return new ::Ifc4x3::IfcVibrationDamperType(std::move(data));
    case 1270:
      return new ::Ifc4x3::IfcVibrationDamperTypeEnum(std::move(data));
    case 1271:
      return new ::Ifc4x3::IfcVibrationIsolator(std::move(data));
    case 1272:
      return new ::Ifc4x3::IfcVibrationIsolatorType(std::move(data));
    case 1273:
      return new ::Ifc4x3::IfcVibrationIsolatorTypeEnum(std::move(data));
    case 1274:
      return new ::Ifc4x3::IfcVirtualElement(std::move(data));
    case 1275:
      return new ::Ifc4x3::IfcVirtualElementTypeEnum(std::move(data));
    case 1276:
      return new ::Ifc4x3::IfcVirtualGridIntersection(std::move(data));
    case 1277:
      return new ::Ifc4x3::IfcVoidingFeature(std::move(data));
    case 1278:
      return new ::Ifc4x3::IfcVoidingFeatureTypeEnum(std::move(data));
    case 1279:
      return new ::Ifc4x3::IfcVolumeMeasure(std::move(data));
    case 1280:
      return new ::Ifc4x3::IfcVolumetricFlowRateMeasure(std::move(data));
    case 1281:
      return new ::Ifc4x3::IfcWall(std::move(data));
    case 1282:
      return new ::Ifc4x3::IfcWallStandardCase(std::move(data));
    case 1283:
      return new ::Ifc4x3::IfcWallType(std::move(data));
    case 1284:
      return new ::Ifc4x3::IfcWallTypeEnum(std::move(data));
    case 1285:
      return new ::Ifc4x3::IfcWarpingConstantMeasure(std::move(data));
    case 1286:
      return new ::Ifc4x3::IfcWarpingMomentMeasure(std::move(data));
    case 1288:
      return new ::Ifc4x3::IfcWasteTerminal(std::move(data));
    case 1289:
      return new ::Ifc4x3::IfcWasteTerminalType(std::move(data));
    case 1290:
      return new ::Ifc4x3::IfcWasteTerminalTypeEnum(std::move(data));
    case 1291:
      return new ::Ifc4x3::IfcWindow(std::move(data));
    case 1292:
      return new ::Ifc4x3::IfcWindowLiningProperties(std::move(data));
    case 1293:
      return new ::Ifc4x3::IfcWindowPanelOperationEnum(std::move(data));
    case 1294:
      return new ::Ifc4x3::IfcWindowPanelPositionEnum(std::move(data));
    case 1295:
      return new ::Ifc4x3::IfcWindowPanelProperties(std::move(data));
    case 1296:
      return new ::Ifc4x3::IfcWindowStyleConstructionEnum(std::move(data));
    case 1297:
      return new ::Ifc4x3::IfcWindowStyleOperationEnum(std::move(data));
    case 1298:
      return new ::Ifc4x3::IfcWindowType(std::move(data));
    case 1299:
      return new ::Ifc4x3::IfcWindowTypeEnum(std::move(data));
    case 1300:
      return new ::Ifc4x3::IfcWindowTypePartitioningEnum(std::move(data));
    case 1301:
      return new ::Ifc4x3::IfcWorkCalendar(std::move(data));
    case 1302:
      return new ::Ifc4x3::IfcWorkCalendarTypeEnum(std::move(data));
    case 1303:
      return new ::Ifc4x3::IfcWorkControl(std::move(data));
    case 1304:
      return new ::Ifc4x3::IfcWorkPlan(std::move(data));
    case 1305:
      return new ::Ifc4x3::IfcWorkPlanTypeEnum(std::move(data));
    case 1306:
      return new ::Ifc4x3::IfcWorkSchedule(std::move(data));
    case 1307:
      return new ::Ifc4x3::IfcWorkScheduleTypeEnum(std::move(data));
    case 1308:
      return new ::Ifc4x3::IfcWorkTime(std::move(data));
    case 1309:
      return new ::Ifc4x3::IfcZone(std::move(data));
    case 1310:
      return new ::Ifc4x3::IfcZShapeProfileDef(std::move(data));
    default:
      throw IfcParse::IfcException(decl->name() + " cannot be instantiated");
    }
  }
};

IfcParse::schema_definition *IFC4X3_populate_schema() {
  IFC4X3_types[0] = new type_declaration(
      strings[0], 0, new simple_type(simple_type::real_type));
  IFC4X3_types[1] = new type_declaration(
      strings[1], 1, new simple_type(simple_type::real_type));
  IFC4X3_types[3] =
      new enumeration_type(strings[2], 3,
                           {strings[3], strings[4], strings[5], strings[6],
                            strings[7], strings[8], strings[9]});
  IFC4X3_types[4] = new enumeration_type(
      strings[10], 4,
      {strings[11], strings[12], strings[13], strings[14], strings[15],
       strings[16], strings[17], strings[18], strings[19], strings[20],
       strings[21], strings[22], strings[23], strings[24], strings[25],
       strings[26], strings[27], strings[28], strings[29], strings[30],
       strings[31], strings[32], strings[33], strings[34], strings[35],
       strings[8],  strings[9]});
  IFC4X3_types[5] = new enumeration_type(
      strings[36], 5,
      {strings[37], strings[38], strings[39], strings[8], strings[9]});
  IFC4X3_types[11] =
      new enumeration_type(strings[40], 11,
                           {strings[41], strings[42], strings[43], strings[44],
                            strings[45], strings[8], strings[9]});
  IFC4X3_types[13] = new enumeration_type(
      strings[46], 13,
      {strings[47], strings[48], strings[49], strings[50], strings[8]});
  IFC4X3_types[20] = new enumeration_type(
      strings[51], 20,
      {strings[52], strings[53], strings[54], strings[8], strings[9]});
  IFC4X3_types[22] =
      new enumeration_type(strings[55], 22,
                           {strings[56], strings[57], strings[58], strings[59],
                            strings[8], strings[9]});
  IFC4X3_types[25] =
      new enumeration_type(strings[60], 25,
                           {strings[61], strings[62], strings[63], strings[64],
                            strings[65], strings[66], strings[67], strings[68],
                            strings[69], strings[8], strings[9]});
  IFC4X3_types[28] = new enumeration_type(
      strings[70], 28,
      {strings[71], strings[72], strings[73], strings[74], strings[75],
       strings[76], strings[77], strings[78], strings[8], strings[9]});
  IFC4X3_types[32] =
      new enumeration_type(strings[79], 32,
                           {strings[80], strings[81], strings[82], strings[83],
                            strings[84], strings[85], strings[86]});
  IFC4X3_types[35] = new enumeration_type(
      strings[87], 35,
      {strings[80], strings[88], strings[89], strings[82], strings[90],
       strings[83], strings[91], strings[85], strings[86]});
  IFC4X3_types[38] =
      new enumeration_type(strings[92], 38, {strings[8], strings[9]});
  IFC4X3_types[41] = new enumeration_type(
      strings[93], 41, {strings[88], strings[89], strings[94], strings[95]});
  IFC4X3_types[42] = new type_declaration(
      strings[96], 42, new simple_type(simple_type::real_type));
  IFC4X3_types[43] = new enumeration_type(
      strings[97], 43,
      {strings[98], strings[99], strings[100], strings[8], strings[9]});
  IFC4X3_types[44] =
      new enumeration_type(strings[101], 44,
                           {strings[102], strings[103], strings[104],
                            strings[105], strings[8], strings[9]});
  IFC4X3_types[45] = new type_declaration(
      strings[106], 45, new simple_type(simple_type::real_type));
  IFC4X3_types[48] = new enumeration_type(
      strings[107], 48,
      {strings[108], strings[109], strings[110], strings[111], strings[112],
       strings[113], strings[114], strings[115], strings[116], strings[8],
       strings[9]});
  IFC4X3_types[58] = new type_declaration(
      strings[117], 58, new simple_type(simple_type::real_type));
  IFC4X3_types[59] = new type_declaration(
      strings[118], 59, new simple_type(simple_type::real_type));
  IFC4X3_types[60] = new enumeration_type(
      strings[119], 60,
      {strings[120], strings[121], strings[122], strings[123]});
  IFC4X3_types[61] = new enumeration_type(
      strings[124], 61, {strings[125], strings[50], strings[9]});
  IFC4X3_types[66] = new enumeration_type(
      strings[126], 66,
      {strings[127], strings[128], strings[129], strings[130], strings[131],
       strings[132], strings[133], strings[134], strings[135], strings[136],
       strings[137], strings[138], strings[139], strings[8], strings[9]});
  IFC4X3_types[109] =
      new enumeration_type(strings[140], 109,
                           {strings[141], strings[142], strings[143],
                            strings[144], strings[145], strings[146]});
  IFC4X3_types[112] = new enumeration_type(
      strings[147], 112,
      {strings[148], strings[149], strings[150], strings[151], strings[152],
       strings[153], strings[154], strings[155], strings[156], strings[157],
       strings[146]});
  IFC4X3_types[74] = new enumeration_type(
      strings[158], 74,
      {strings[159], strings[160], strings[161], strings[162], strings[163],
       strings[164], strings[165], strings[166], strings[167], strings[168],
       strings[169], strings[170], strings[8], strings[9]});
  IFC4X3_types[77] = new enumeration_type(
      strings[171], 77,
      {strings[172], strings[173], strings[174], strings[175], strings[9]});
  IFC4X3_types[78] = new enumeration_type(
      strings[176], 78,
      {strings[177], strings[178], strings[179], strings[180], strings[181],
       strings[182], strings[183], strings[184], strings[8], strings[9]});
  IFC4X3_types[79] = new enumeration_type(
      strings[185], 79,
      {strings[186], strings[187], strings[188], strings[189], strings[190],
       strings[191], strings[192], strings[193], strings[194], strings[195]});
  IFC4X3_types[81] = new type_declaration(
      strings[196], 81, new simple_type(simple_type::binary_type));
  IFC4X3_types[86] = new enumeration_type(
      strings[197], 86, {strings[198], strings[199], strings[8], strings[9]});
  IFC4X3_types[87] = new type_declaration(
      strings[200], 87, new simple_type(simple_type::boolean_type));
  IFC4X3_types[90] = new enumeration_type(
      strings[201], 90, {strings[202], strings[203], strings[204]});
  IFC4X3_types[106] = new enumeration_type(
      strings[205], 106,
      {strings[206], strings[207], strings[208], strings[209], strings[210],
       strings[211], strings[212], strings[213], strings[214], strings[215],
       strings[8], strings[9]});
  IFC4X3_types[107] = new enumeration_type(
      strings[216], 107,
      {strings[217], strings[218], strings[219], strings[220], strings[221],
       strings[222], strings[223], strings[224], strings[8], strings[9]});
  IFC4X3_types[117] = new enumeration_type(
      strings[225], 117,
      {strings[226], strings[227], strings[228], strings[229], strings[230],
       strings[8], strings[9]});
  IFC4X3_types[120] = new enumeration_type(
      strings[231], 120,
      {strings[232], strings[233], strings[234], strings[8], strings[9]});
  IFC4X3_types[123] = new enumeration_type(
      strings[235], 123,
      {strings[236], strings[237], strings[209], strings[238], strings[239],
       strings[240], strings[241], strings[242], strings[33], strings[8],
       strings[9]});
  IFC4X3_types[127] = new enumeration_type(
      strings[243], 127,
      {strings[236], strings[237], strings[209], strings[238], strings[244],
       strings[239], strings[240], strings[245], strings[246], strings[241],
       strings[242], strings[247], strings[33], strings[8], strings[9]});
  IFC4X3_types[130] =
      new enumeration_type(strings[248], 130, {strings[8], strings[9]});
  IFC4X3_types[133] = new enumeration_type(
      strings[249], 133,
      {strings[250], strings[251], strings[252], strings[253], strings[254],
       strings[255], strings[8], strings[9]});
  IFC4X3_types[136] = new enumeration_type(
      strings[256], 136,
      {strings[257], strings[258], strings[259], strings[260], strings[261],
       strings[262], strings[263], strings[8], strings[9]});
  IFC4X3_types[139] = new enumeration_type(
      strings[264], 139,
      {strings[251], strings[265], strings[266], strings[267], strings[253],
       strings[255], strings[8], strings[9]});
  IFC4X3_types[142] = new enumeration_type(
      strings[268], 142,
      {strings[269], strings[270], strings[271], strings[272], strings[273],
       strings[274], strings[275], strings[276], strings[277], strings[278],
       strings[8], strings[9]});
  IFC4X3_types[145] = new enumeration_type(
      strings[279], 145, {strings[280], strings[281], strings[8], strings[9]});
  IFC4X3_types[146] = new type_declaration(
      strings[282], 146, new simple_type(simple_type::integer_type));
  IFC4X3_types[157] = new enumeration_type(
      strings[283], 157,
      {strings[284], strings[285], strings[286], strings[287], strings[9]});
  IFC4X3_types[160] = new enumeration_type(
      strings[288], 160,
      {strings[289], strings[290], strings[291], strings[8], strings[9]});
  IFC4X3_types[163] =
      new enumeration_type(strings[292], 163, {strings[8], strings[9]});
  IFC4X3_types[177] = new enumeration_type(
      strings[293], 177,
      {strings[294], strings[295], strings[296], strings[297], strings[298],
       strings[299], strings[300], strings[8], strings[9]});
  IFC4X3_types[185] = new enumeration_type(
      strings[301], 185,
      {strings[302], strings[303], strings[304], strings[305], strings[306],
       strings[8], strings[9]});
  IFC4X3_types[188] = new enumeration_type(
      strings[307], 188,
      {strings[308], strings[309], strings[310], strings[4],   strings[311],
       strings[312], strings[313], strings[314], strings[315], strings[316],
       strings[317], strings[318], strings[319], strings[320], strings[321],
       strings[322], strings[323], strings[324], strings[325], strings[326],
       strings[327], strings[328], strings[329], strings[330], strings[8],
       strings[9]});
  IFC4X3_types[189] = new type_declaration(
      strings[331], 189,
      new aggregation_type(aggregation_type::array_type, 1, 2,
                           new simple_type(simple_type::real_type)));
  IFC4X3_types[192] =
      new enumeration_type(strings[332], 192, {strings[333], strings[334]});
  IFC4X3_types[197] = new type_declaration(
      strings[335], 197,
      new aggregation_type(aggregation_type::list_type, 3, 4,
                           new simple_type(simple_type::integer_type)));
  IFC4X3_types[200] = new enumeration_type(
      strings[336], 200,
      {strings[337], strings[338], strings[339], strings[340], strings[341],
       strings[342], strings[343], strings[344], strings[345], strings[346],
       strings[347], strings[348], strings[349], strings[350], strings[351],
       strings[8], strings[9]});
  IFC4X3_types[203] = new enumeration_type(
      strings[352], 203,
      {strings[289], strings[353], strings[291], strings[354], strings[355],
       strings[356], strings[357], strings[8], strings[9]});
  IFC4X3_types[211] = new enumeration_type(
      strings[358], 211,
      {strings[359], strings[360], strings[361], strings[9]});
  IFC4X3_types[214] = new enumeration_type(
      strings[362], 214,
      {strings[363], strings[364], strings[365], strings[8], strings[9]});
  IFC4X3_types[217] = new enumeration_type(
      strings[366], 217,
      {strings[367], strings[368], strings[369], strings[370], strings[371],
       strings[372], strings[373], strings[374], strings[8], strings[9]});
  IFC4X3_types[220] = new enumeration_type(
      strings[375], 220,
      {strings[376], strings[377], strings[378], strings[379], strings[380],
       strings[381], strings[382], strings[383], strings[384], strings[8],
       strings[9]});
  IFC4X3_types[223] = new enumeration_type(
      strings[385], 223, {strings[386], strings[387], strings[8], strings[9]});
  IFC4X3_types[227] = new type_declaration(
      strings[388], 227, new simple_type(simple_type::real_type));
  IFC4X3_types[232] = new enumeration_type(
      strings[389], 232,
      {strings[390], strings[391], strings[392], strings[393], strings[394],
       strings[8], strings[9]});
  IFC4X3_types[237] =
      new enumeration_type(strings[395], 237,
                           {strings[396], strings[397], strings[398],
                            strings[399], strings[8], strings[9]});
  IFC4X3_types[240] = new enumeration_type(
      strings[400], 240, {strings[401], strings[402], strings[8], strings[9]});
  IFC4X3_types[243] = new enumeration_type(
      strings[403], 243,
      {strings[404], strings[405], strings[406], strings[8], strings[9]});
  IFC4X3_types[249] =
      new enumeration_type(strings[407], 249, {strings[8], strings[9]});
  IFC4X3_types[251] = new enumeration_type(
      strings[408], 251,
      {strings[409], strings[410], strings[411], strings[412], strings[413],
       strings[414], strings[415], strings[8], strings[9]});
  IFC4X3_types[253] = new type_declaration(
      strings[416], 253, new simple_type(simple_type::integer_type));
  IFC4X3_types[256] = new enumeration_type(
      strings[417], 256,
      {strings[418], strings[419], strings[420], strings[421], strings[422],
       strings[423], strings[8], strings[9]});
  IFC4X3_types[259] = new enumeration_type(
      strings[424], 259,
      {strings[425], strings[426], strings[427], strings[428], strings[228],
       strings[429], strings[430], strings[431], strings[432], strings[433],
       strings[434], strings[435], strings[8], strings[9]});
  IFC4X3_types[262] = new enumeration_type(
      strings[436], 262, {strings[49], strings[50], strings[8], strings[9]});
  IFC4X3_types[270] =
      new enumeration_type(strings[437], 270, {strings[8], strings[9]});
  IFC4X3_types[271] = new type_declaration(
      strings[438], 271, new simple_type(simple_type::real_type));
  IFC4X3_types[276] = new enumeration_type(
      strings[439], 276,
      {strings[440], strings[441], strings[442], strings[9]});
  IFC4X3_types[289] = new enumeration_type(
      strings[443], 289,
      {strings[444], strings[445], strings[446], strings[447], strings[448],
       strings[449], strings[450], strings[451], strings[452], strings[453],
       strings[454], strings[8], strings[9]});
  IFC4X3_types[290] = new enumeration_type(
      strings[455], 290,
      {strings[456], strings[457], strings[458], strings[8], strings[9]});
  IFC4X3_types[291] = new type_declaration(
      strings[459], 291, new simple_type(simple_type::string_type));
  IFC4X3_types[292] = new type_declaration(
      strings[460], 292, new simple_type(simple_type::string_type));
  IFC4X3_types[293] = new type_declaration(
      strings[461], 293, new simple_type(simple_type::integer_type));
  IFC4X3_types[294] = new type_declaration(
      strings[462], 294, new simple_type(simple_type::integer_type));
  IFC4X3_types[302] = new enumeration_type(
      strings[463], 302,
      {strings[464], strings[465], strings[466], strings[467], strings[468],
       strings[469], strings[470], strings[471], strings[472], strings[473],
       strings[474], strings[475], strings[476], strings[477], strings[478],
       strings[479], strings[480], strings[481], strings[482], strings[483],
       strings[484], strings[485], strings[486], strings[487], strings[488],
       strings[489], strings[490], strings[491], strings[492], strings[493],
       strings[494], strings[495], strings[496], strings[497], strings[498],
       strings[499], strings[500], strings[501], strings[502], strings[503],
       strings[504], strings[505], strings[506], strings[507], strings[508],
       strings[509], strings[510], strings[511], strings[512], strings[513],
       strings[514], strings[515], strings[8]});
  IFC4X3_types[303] = new type_declaration(
      strings[516], 303, new simple_type(simple_type::string_type));
  IFC4X3_types[305] = new type_declaration(
      strings[517], 305, new simple_type(simple_type::integer_type));
  IFC4X3_types[307] =
      new enumeration_type(strings[518], 307, {strings[519], strings[520]});
  IFC4X3_types[312] = new enumeration_type(
      strings[521], 312,
      {strings[522], strings[523], strings[524], strings[525], strings[526],
       strings[527], strings[528], strings[529], strings[530], strings[531],
       strings[532], strings[533], strings[534], strings[535], strings[536],
       strings[537], strings[538], strings[539], strings[540], strings[541],
       strings[542], strings[8],   strings[9]});
  IFC4X3_types[315] = new enumeration_type(
      strings[543], 315,
      {strings[544], strings[545], strings[546], strings[547], strings[548],
       strings[549], strings[8], strings[9]});
  IFC4X3_types[318] = new enumeration_type(
      strings[550], 318,
      {strings[551], strings[552], strings[553], strings[554], strings[555],
       strings[556], strings[557], strings[558], strings[8], strings[9]});
  IFC4X3_types[327] = new enumeration_type(
      strings[559], 327,
      {strings[560], strings[561], strings[562], strings[563], strings[564],
       strings[8], strings[9]});
  IFC4X3_types[329] = new enumeration_type(
      strings[565], 329,
      {strings[566], strings[567], strings[568], strings[569], strings[570],
       strings[571], strings[572], strings[573], strings[574], strings[575],
       strings[576], strings[577], strings[578], strings[579], strings[580],
       strings[581], strings[582], strings[583], strings[584], strings[585],
       strings[586], strings[379], strings[587], strings[588], strings[370],
       strings[371], strings[589], strings[590], strings[591], strings[592],
       strings[593], strings[594], strings[595], strings[596], strings[597],
       strings[598], strings[599], strings[600], strings[601], strings[602],
       strings[603], strings[604], strings[138], strings[605], strings[606],
       strings[607], strings[608], strings[609], strings[610], strings[8],
       strings[9]});
  IFC4X3_types[330] =
      new enumeration_type(strings[611], 330,
                           {strings[612], strings[613], strings[614],
                            strings[615], strings[8], strings[9]});
  IFC4X3_types[335] = new enumeration_type(
      strings[616], 335,
      {strings[617], strings[618], strings[619], strings[620], strings[9]});
  IFC4X3_types[338] = new enumeration_type(
      strings[621], 338,
      {strings[622], strings[623], strings[624], strings[625], strings[626],
       strings[627], strings[628], strings[8], strings[9]});
  IFC4X3_types[339] = new enumeration_type(
      strings[629], 339,
      {strings[630], strings[631], strings[632], strings[9]});
  IFC4X3_types[341] = new enumeration_type(
      strings[633], 341,
      {strings[634], strings[635], strings[636], strings[637], strings[383],
       strings[638], strings[384], strings[8], strings[9]});
  IFC4X3_types[342] = new enumeration_type(
      strings[639], 342,
      {strings[640], strings[641], strings[642], strings[643], strings[644],
       strings[645], strings[646], strings[647], strings[648], strings[649],
       strings[625], strings[626], strings[650], strings[651], strings[652],
       strings[653], strings[8], strings[9]});
  IFC4X3_types[344] = new enumeration_type(
      strings[654], 344,
      {strings[655], strings[656], strings[657], strings[658], strings[659],
       strings[8], strings[9]});
  IFC4X3_types[345] = new enumeration_type(
      strings[660], 345,
      {strings[661], strings[662], strings[663], strings[664], strings[665],
       strings[666], strings[667], strings[646], strings[647], strings[648],
       strings[649], strings[668], strings[669], strings[670], strings[671],
       strings[672], strings[626], strings[650], strings[651], strings[652],
       strings[653], strings[673], strings[674], strings[8],   strings[9]});
  IFC4X3_types[346] = new type_declaration(
      strings[675], 346, new simple_type(simple_type::real_type));
  IFC4X3_types[351] = new enumeration_type(
      strings[676], 351,
      {strings[250], strings[251], strings[265], strings[266], strings[253],
       strings[677], strings[255], strings[8], strings[9]});
  IFC4X3_types[354] = new enumeration_type(
      strings[678], 354, {strings[679], strings[680], strings[8], strings[9]});
  IFC4X3_types[357] = new enumeration_type(
      strings[681], 357,
      {strings[682], strings[683], strings[684], strings[8], strings[9]});
  IFC4X3_types[358] = new type_declaration(
      strings[685], 358, new simple_type(simple_type::string_type));
  IFC4X3_types[359] = new type_declaration(
      strings[686], 359, new simple_type(simple_type::real_type));
  IFC4X3_types[361] = new enumeration_type(
      strings[687], 361,
      {strings[688], strings[689], strings[690], strings[691], strings[692],
       strings[693], strings[694], strings[695], strings[557], strings[8],
       strings[9]});
  IFC4X3_types[364] = new enumeration_type(
      strings[696], 364,
      {strings[697], strings[698], strings[699], strings[700], strings[701],
       strings[702], strings[703], strings[8], strings[9]});
  IFC4X3_types[370] = new enumeration_type(
      strings[704], 370,
      {strings[705], strings[706], strings[707], strings[708], strings[709],
       strings[710], strings[711], strings[712], strings[713], strings[714],
       strings[715], strings[716], strings[717], strings[718], strings[719],
       strings[720], strings[8], strings[9]});
  IFC4X3_types[371] = new type_declaration(
      strings[721], 371, new simple_type(simple_type::real_type));
  IFC4X3_types[372] = new type_declaration(
      strings[722], 372, new simple_type(simple_type::real_type));
  IFC4X3_types[373] = new type_declaration(
      strings[723], 373, new simple_type(simple_type::real_type));
  IFC4X3_types[374] = new type_declaration(
      strings[724], 374, new simple_type(simple_type::real_type));
  IFC4X3_types[377] =
      new enumeration_type(strings[725], 377,
                           {strings[544], strings[546], strings[548],
                            strings[549], strings[8], strings[9]});
  IFC4X3_types[380] = new enumeration_type(
      strings[726], 380,
      {strings[727], strings[728], strings[729], strings[730], strings[731],
       strings[732], strings[733], strings[734], strings[735], strings[8],
       strings[9]});
  IFC4X3_types[383] = new enumeration_type(
      strings[736], 383, {strings[737], strings[8], strings[9]});
  IFC4X3_types[386] = new enumeration_type(
      strings[738], 386,
      {strings[739], strings[740], strings[741], strings[8], strings[9]});
  IFC4X3_types[389] = new enumeration_type(
      strings[742], 389,
      {strings[743], strings[744], strings[745], strings[746], strings[747],
       strings[8], strings[9]});
  IFC4X3_types[390] = new type_declaration(
      strings[748], 390, new simple_type(simple_type::real_type));
  IFC4X3_types[393] = new enumeration_type(
      strings[749], 393,
      {strings[750], strings[751], strings[752], strings[8], strings[9]});
  IFC4X3_types[394] = new type_declaration(
      strings[753], 394, new simple_type(simple_type::real_type));
  IFC4X3_types[399] = new enumeration_type(
      strings[754], 399,
      {strings[206], strings[755], strings[756], strings[757], strings[758],
       strings[759], strings[207], strings[760], strings[761], strings[222],
       strings[762], strings[763], strings[210], strings[212], strings[764],
       strings[765], strings[766], strings[767], strings[768], strings[769],
       strings[770], strings[771], strings[772], strings[773], strings[774],
       strings[775], strings[224], strings[776], strings[8],   strings[9]});
  IFC4X3_types[402] = new enumeration_type(
      strings[777], 402, {strings[232], strings[233], strings[234]});
  IFC4X3_types[409] = new type_declaration(
      strings[778], 409, new simple_type(simple_type::real_type));
  IFC4X3_types[412] = new enumeration_type(
      strings[779], 412, {strings[780], strings[781], strings[8], strings[9]});
  IFC4X3_types[415] = new enumeration_type(
      strings[782], 415,
      {strings[783], strings[784], strings[785], strings[786], strings[787],
       strings[788], strings[789], strings[790], strings[791], strings[8],
       strings[9]});
  IFC4X3_types[418] = new enumeration_type(
      strings[792], 418,
      {strings[793], strings[794], strings[795], strings[796], strings[797],
       strings[798], strings[8], strings[9]});
  IFC4X3_types[421] =
      new enumeration_type(strings[799], 421,
                           {strings[800], strings[801], strings[802],
                            strings[803], strings[8], strings[9]});
  IFC4X3_types[423] = new enumeration_type(
      strings[804], 423,
      {strings[805], strings[806], strings[807], strings[8], strings[9]});
  IFC4X3_types[432] =
      new enumeration_type(strings[808], 432,
                           {strings[809], strings[810], strings[811],
                            strings[812], strings[8], strings[9]});
  IFC4X3_types[446] = new enumeration_type(
      strings[813], 446,
      {strings[814], strings[815], strings[253], strings[816], strings[817],
       strings[213], strings[214], strings[818], strings[8], strings[9]});
  IFC4X3_types[447] =
      new enumeration_type(strings[819], 447,
                           {strings[820], strings[821], strings[822],
                            strings[823], strings[8], strings[9]});
  IFC4X3_types[451] = new enumeration_type(
      strings[824], 451,
      {strings[825], strings[826], strings[827], strings[828], strings[829],
       strings[830], strings[831], strings[8], strings[9]});
  IFC4X3_types[454] = new enumeration_type(
      strings[832], 454,
      {strings[833], strings[834], strings[835], strings[8], strings[9]});
  IFC4X3_types[464] = new enumeration_type(
      strings[836], 464,
      {strings[837], strings[838], strings[839], strings[840], strings[841],
       strings[842], strings[8], strings[9]});
  IFC4X3_types[467] = new enumeration_type(
      strings[843], 467,
      {strings[844], strings[845], strings[846], strings[847], strings[848],
       strings[849], strings[8], strings[9]});
  IFC4X3_types[471] = new enumeration_type(
      strings[850], 471,
      {strings[851], strings[852], strings[853], strings[9]});
  IFC4X3_types[476] = new enumeration_type(
      strings[854], 476,
      {strings[855], strings[856], strings[857], strings[858], strings[859],
       strings[860], strings[861], strings[862], strings[863], strings[864],
       strings[8], strings[9]});
  IFC4X3_types[479] =
      new enumeration_type(strings[865], 479,
                           {strings[866], strings[867], strings[868],
                            strings[869], strings[8], strings[9]});
  IFC4X3_types[490] = new type_declaration(
      strings[870], 490, new simple_type(simple_type::string_type));
  IFC4X3_types[491] = new type_declaration(
      strings[871], 491, new simple_type(simple_type::string_type));
  IFC4X3_types[492] = new type_declaration(
      strings[872], 492, new simple_type(simple_type::string_type));
  IFC4X3_types[495] = new enumeration_type(
      strings[873], 495,
      {strings[874], strings[875], strings[876], strings[877], strings[878],
       strings[8], strings[9]});
  IFC4X3_types[496] = new type_declaration(
      strings[879], 496, new simple_type(simple_type::real_type));
  IFC4X3_types[497] = new type_declaration(
      strings[880], 497, new simple_type(simple_type::real_type));
  IFC4X3_types[502] = new enumeration_type(
      strings[881], 502,
      {strings[882], strings[883], strings[884], strings[885], strings[886],
       strings[887], strings[888], strings[889], strings[8], strings[9]});
  IFC4X3_types[505] = new enumeration_type(
      strings[890], 505,
      {strings[891], strings[892], strings[893], strings[8], strings[9]});
  IFC4X3_types[507] = new enumeration_type(
      strings[894], 507,
      {strings[895], strings[896], strings[897], strings[898], strings[899],
       strings[900], strings[901], strings[8], strings[9]});
  IFC4X3_types[518] = new enumeration_type(
      strings[902], 518,
      {strings[903], strings[904], strings[199], strings[8], strings[9]});
  IFC4X3_types[520] =
      new enumeration_type(strings[905], 520, {strings[906], strings[907]});
  IFC4X3_types[519] = new type_declaration(
      strings[908], 519, new simple_type(simple_type::string_type));
  IFC4X3_types[526] =
      new enumeration_type(strings[909], 526,
                           {strings[910], strings[911], strings[683],
                            strings[912], strings[8], strings[9]});
  IFC4X3_types[532] = new enumeration_type(
      strings[913], 532,
      {strings[914], strings[915], strings[916], strings[8], strings[9]});
  IFC4X3_types[533] = new type_declaration(
      strings[917], 533, new simple_type(simple_type::real_type));
  IFC4X3_types[534] = new type_declaration(
      strings[918], 534, new simple_type(simple_type::real_type));
  IFC4X3_types[537] = new enumeration_type(
      strings[919], 537,
      {strings[920], strings[921], strings[922], strings[923], strings[924],
       strings[925], strings[926], strings[927], strings[928], strings[929],
       strings[930], strings[931], strings[932], strings[8], strings[9]});
  IFC4X3_types[538] = new type_declaration(
      strings[933], 538, new simple_type(simple_type::string_type));
  IFC4X3_types[539] = new type_declaration(
      strings[934], 539, new simple_type(simple_type::real_type));
  IFC4X3_types[543] =
      new enumeration_type(strings[935], 543,
                           {strings[936], strings[937], strings[938],
                            strings[939], strings[8], strings[9]});
  IFC4X3_types[551] = new type_declaration(
      strings[940], 551, new simple_type(simple_type::real_type));
  IFC4X3_types[552] = new type_declaration(
      strings[941], 552, new simple_type(simple_type::integer_type));
  IFC4X3_types[553] = new type_declaration(
      strings[942], 553, new simple_type(simple_type::integer_type));
  IFC4X3_types[556] =
      new enumeration_type(strings[943], 556,
                           {strings[944], strings[945], strings[593],
                            strings[946], strings[8], strings[9]});
  IFC4X3_types[558] =
      new enumeration_type(strings[947], 558,
                           {strings[809], strings[810], strings[811],
                            strings[812], strings[948], strings[9]});
  IFC4X3_types[561] = new enumeration_type(
      strings[949], 561,
      {strings[950], strings[951], strings[952], strings[8], strings[9]});
  IFC4X3_types[562] = new type_declaration(
      strings[953], 562, new simple_type(simple_type::real_type));
  IFC4X3_types[566] = new type_declaration(
      strings[954], 566, new simple_type(simple_type::real_type));
  IFC4X3_types[569] = new enumeration_type(
      strings[955], 569, {strings[576], strings[956], strings[8], strings[9]});
  IFC4X3_types[572] = new type_declaration(
      strings[957], 572, new simple_type(simple_type::real_type));
  IFC4X3_types[573] = new enumeration_type(
      strings[958], 573,
      {strings[959], strings[960], strings[961], strings[146]});
  IFC4X3_types[574] = new type_declaration(
      strings[962], 574, new simple_type(simple_type::string_type));
  IFC4X3_types[577] = new enumeration_type(
      strings[963], 577,
      {strings[964], strings[965], strings[966], strings[377], strings[378],
       strings[967], strings[968], strings[428], strings[969], strings[970],
       strings[971], strings[381], strings[972], strings[372], strings[973],
       strings[431], strings[974], strings[975], strings[976], strings[8],
       strings[9]});
  IFC4X3_types[581] = new enumeration_type(
      strings[977], 581,
      {strings[978], strings[979], strings[980], strings[981], strings[982],
       strings[983], strings[984], strings[985], strings[986], strings[8],
       strings[9]});
  IFC4X3_types[582] = new type_declaration(strings[987], 582,
                                           new named_type(IFC4X3_types[538]));
  IFC4X3_types[584] = new enumeration_type(
      strings[988], 584, {strings[989], strings[990], strings[991]});
  IFC4X3_types[585] = new type_declaration(
      strings[992], 585, new simple_type(simple_type::real_type));
  IFC4X3_types[589] = new enumeration_type(
      strings[993], 589,
      {strings[994], strings[995], strings[996], strings[9]});
  IFC4X3_types[592] = new enumeration_type(
      strings[997], 592,
      {strings[978], strings[979], strings[981], strings[982], strings[998],
       strings[999], strings[1000], strings[1001], strings[984], strings[986],
       strings[9]});
  IFC4X3_types[595] = new enumeration_type(
      strings[1002], 595,
      {strings[1003], strings[1004], strings[1005], strings[8], strings[9]});
  IFC4X3_types[605] = new type_declaration(
      strings[1006], 605, new simple_type(simple_type::real_type));
  IFC4X3_types[606] = new type_declaration(
      strings[1007], 606, new simple_type(simple_type::real_type));
  IFC4X3_types[609] = new type_declaration(
      strings[1008], 609, new simple_type(simple_type::real_type));
  IFC4X3_types[610] = new type_declaration(
      strings[1009], 610, new simple_type(simple_type::real_type));
  IFC4X3_types[614] = new enumeration_type(
      strings[1010], 614,
      {strings[847], strings[1011], strings[8], strings[9]});
  IFC4X3_types[615] = new enumeration_type(
      strings[1012], 615,
      {strings[1013], strings[1014], strings[1015], strings[8], strings[9]});
  IFC4X3_types[617] = new type_declaration(
      strings[1016], 617, new simple_type(simple_type::logical_type));
  IFC4X3_types[618] =
      new enumeration_type(strings[1017], 618,
                           {strings[1018], strings[1019], strings[1020],
                            strings[1021], strings[1022]});
  IFC4X3_types[621] = new type_declaration(
      strings[1023], 621, new simple_type(simple_type::real_type));
  IFC4X3_types[622] = new type_declaration(
      strings[1024], 622, new simple_type(simple_type::real_type));
  IFC4X3_types[623] = new type_declaration(
      strings[1025], 623, new simple_type(simple_type::real_type));
  IFC4X3_types[624] = new type_declaration(
      strings[1026], 624, new simple_type(simple_type::real_type));
  IFC4X3_types[625] = new type_declaration(
      strings[1027], 625, new simple_type(simple_type::real_type));
  IFC4X3_types[630] = new enumeration_type(
      strings[1028], 630,
      {strings[1029], strings[1030], strings[1031], strings[1032],
       strings[1033], strings[1034], strings[1035], strings[1036],
       strings[1037], strings[1038], strings[1039], strings[1040],
       strings[1041], strings[1042], strings[1043], strings[1044],
       strings[1045], strings[1046], strings[1047], strings[8],
       strings[9]});
  IFC4X3_types[632] = new enumeration_type(
      strings[1048], 632,
      {strings[1049], strings[1050], strings[1051], strings[1052],
       strings[1053], strings[1054], strings[1055], strings[1056],
       strings[420],  strings[1057], strings[1058], strings[1059],
       strings[1060], strings[1061], strings[1062], strings[1063],
       strings[1064], strings[1065], strings[423],  strings[1066],
       strings[1067], strings[1068], strings[1069], strings[1070],
       strings[8],    strings[9]});
  IFC4X3_types[633] = new type_declaration(
      strings[1071], 633, new simple_type(simple_type::real_type));
  IFC4X3_types[634] = new type_declaration(
      strings[1072], 634, new simple_type(simple_type::real_type));
  IFC4X3_types[635] = new type_declaration(
      strings[1073], 635, new simple_type(simple_type::real_type));
  IFC4X3_types[636] = new type_declaration(
      strings[1074], 636, new simple_type(simple_type::real_type));
  IFC4X3_types[661] = new enumeration_type(
      strings[1075], 661,
      {strings[1076], strings[1077], strings[1078], strings[1079],
       strings[1080], strings[1081], strings[1082], strings[1083],
       strings[1084], strings[1085], strings[1086], strings[1087],
       strings[1088], strings[1089], strings[1090], strings[8], strings[9]});
  IFC4X3_types[664] = new enumeration_type(
      strings[1091], 664,
      {strings[1092], strings[1093], strings[1094], strings[1095],
       strings[1096], strings[8], strings[9]});
  IFC4X3_types[667] = new enumeration_type(
      strings[1097], 667,
      {strings[1098], strings[1099], strings[1100], strings[1101],
       strings[1102], strings[1103], strings[914],  strings[6],
       strings[1104], strings[1105], strings[1106], strings[1107],
       strings[1108], strings[1109], strings[1110], strings[1111],
       strings[1112], strings[1113], strings[1114], strings[8],
       strings[9]});
  IFC4X3_types[673] = new enumeration_type(
      strings[1115], 673,
      {strings[1116], strings[1117], strings[1118], strings[1119],
       strings[1120], strings[1121], strings[1122], strings[1123],
       strings[1124], strings[1125], strings[1126], strings[1127],
       strings[1128], strings[8], strings[9]});
  IFC4X3_types[674] = new type_declaration(
      strings[1129], 674, new simple_type(simple_type::real_type));
  IFC4X3_types[675] = new type_declaration(
      strings[1130], 675, new simple_type(simple_type::real_type));
  IFC4X3_types[676] = new type_declaration(
      strings[1131], 676, new simple_type(simple_type::real_type));
  IFC4X3_types[677] = new select_type(strings[1132], 677,
                                      {IFC4X3_types[87], IFC4X3_types[676]});
  IFC4X3_types[678] = new type_declaration(
      strings[1133], 678, new simple_type(simple_type::real_type));
  IFC4X3_types[679] = new select_type(strings[1134], 679,
                                      {IFC4X3_types[87], IFC4X3_types[678]});
  IFC4X3_types[680] = new select_type(strings[1135], 680,
                                      {IFC4X3_types[87], IFC4X3_types[675]});
  IFC4X3_types[681] = new type_declaration(
      strings[1136], 681, new simple_type(simple_type::real_type));
  IFC4X3_types[682] = new type_declaration(
      strings[1137], 682, new simple_type(simple_type::real_type));
  IFC4X3_types[683] = new type_declaration(
      strings[1138], 683, new simple_type(simple_type::real_type));
  IFC4X3_types[684] = new type_declaration(
      strings[1139], 684, new simple_type(simple_type::real_type));
  IFC4X3_types[686] = new type_declaration(
      strings[1140], 686, new simple_type(simple_type::integer_type));
  IFC4X3_types[689] = new enumeration_type(
      strings[1141], 689,
      {strings[1142], strings[1143], strings[1144], strings[1145],
       strings[1146], strings[8], strings[9]});
  IFC4X3_types[692] = new enumeration_type(
      strings[1147], 692,
      {strings[1148], strings[1149], strings[1150], strings[8], strings[9]});
  IFC4X3_types[696] = new enumeration_type(
      strings[1151], 696,
      {strings[1152], strings[1153], strings[8], strings[9]});
  IFC4X3_types[697] = new type_declaration(strings[1154], 697,
                                           new named_type(IFC4X3_types[585]));
  IFC4X3_types[699] = new type_declaration(
      strings[1155], 699, new simple_type(simple_type::number_type));
  IFC4X3_types[706] = new enumeration_type(
      strings[1156], 706,
      {strings[1157], strings[574], strings[1158], strings[1159], strings[1160],
       strings[1161], strings[1162], strings[9]});
  IFC4X3_types[703] = new enumeration_type(
      strings[1163], 703,
      {strings[1164], strings[1165], strings[1166], strings[809], strings[1167],
       strings[1168], strings[1169], strings[1170], strings[1171],
       strings[1172], strings[1173], strings[8], strings[9]});
  IFC4X3_types[708] = new enumeration_type(
      strings[1174], 708,
      {strings[1175], strings[1176], strings[1177], strings[1178],
       strings[1179], strings[1180], strings[1181], strings[8], strings[9]});
  IFC4X3_types[715] = new enumeration_type(
      strings[1182], 715,
      {strings[1183], strings[1184], strings[8], strings[9]});
  IFC4X3_types[723] = new enumeration_type(
      strings[1185], 723,
      {strings[1186], strings[1187], strings[1188], strings[1189],
       strings[1190], strings[8], strings[9]});
  IFC4X3_types[740] = new type_declaration(
      strings[1191], 740, new simple_type(simple_type::real_type));
  IFC4X3_types[726] = new type_declaration(
      strings[1192], 726, new simple_type(simple_type::real_type));
  IFC4X3_types[730] = new enumeration_type(
      strings[1193], 730,
      {strings[1194], strings[1195], strings[8], strings[9]});
  IFC4X3_types[733] =
      new enumeration_type(strings[1196], 733, {strings[8], strings[9]});
  IFC4X3_types[734] = new enumeration_type(
      strings[1197], 734,
      {strings[1198], strings[1199], strings[1200], strings[8], strings[9]});
  IFC4X3_types[737] = new enumeration_type(
      strings[1201], 737,
      {strings[1202], strings[1203], strings[1204], strings[8], strings[9]});
  IFC4X3_types[742] = new enumeration_type(
      strings[1205], 742, {strings[1206], strings[1207], strings[9]});
  IFC4X3_types[746] =
      new enumeration_type(strings[1208], 746,
                           {strings[1209], strings[1210], strings[1211],
                            strings[1212], strings[8], strings[9]});
  IFC4X3_types[748] = new enumeration_type(
      strings[1213], 748,
      {strings[1214], strings[1215], strings[1216], strings[1217],
       strings[1218], strings[1219], strings[8], strings[9]});
  IFC4X3_types[751] = new enumeration_type(
      strings[1220], 751,
      {strings[250], strings[251], strings[265], strings[266], strings[253],
       strings[677], strings[255], strings[8], strings[9]});
  IFC4X3_types[754] = new enumeration_type(
      strings[1221], 754,
      {strings[220], strings[679], strings[1222], strings[680], strings[1223],
       strings[8], strings[9]});
  IFC4X3_types[759] = new type_declaration(
      strings[1224], 759, new simple_type(simple_type::real_type));
  IFC4X3_types[761] = new type_declaration(
      strings[1225], 761, new simple_type(simple_type::real_type));
  IFC4X3_types[764] = new enumeration_type(
      strings[1226], 764,
      {strings[1227], strings[1228], strings[1229], strings[1230],
       strings[1231], strings[1232], strings[1233], strings[1234],
       strings[1235], strings[8], strings[9]});
  IFC4X3_types[777] = new type_declaration(strings[1236], 777,
                                           new named_type(IFC4X3_types[552]));
  IFC4X3_types[778] = new type_declaration(strings[1237], 778,
                                           new named_type(IFC4X3_types[585]));
  IFC4X3_types[779] = new type_declaration(strings[1238], 779,
                                           new named_type(IFC4X3_types[761]));
  IFC4X3_types[782] = new type_declaration(
      strings[1239], 782, new simple_type(simple_type::real_type));
  IFC4X3_types[789] = new enumeration_type(
      strings[1240], 789, {strings[1241], strings[1242], strings[1243]});
  IFC4X3_types[790] = new type_declaration(
      strings[1244], 790, new simple_type(simple_type::string_type));
  IFC4X3_types[795] = new type_declaration(
      strings[1245], 795, new simple_type(simple_type::real_type));
  IFC4X3_types[798] = new enumeration_type(
      strings[1246], 798,
      {strings[1247], strings[1248], strings[1249], strings[1250],
       strings[1251], strings[1252], strings[1253], strings[8], strings[9]});
  IFC4X3_types[808] =
      new enumeration_type(strings[1254], 808, {strings[1255], strings[1256]});
  IFC4X3_types[816] = new enumeration_type(
      strings[1257], 816,
      {strings[1258], strings[1259], strings[1260], strings[1261],
       strings[1262], strings[8], strings[9]});
  IFC4X3_types[811] =
      new enumeration_type(strings[1263], 811, {strings[1264], strings[1265]});
  IFC4X3_types[813] = new enumeration_type(
      strings[1266], 813,
      {strings[1267], strings[1268], strings[8], strings[9]});
  IFC4X3_types[831] = new enumeration_type(
      strings[1269], 831,
      {strings[1270], strings[1271], strings[1272], strings[1273],
       strings[1274], strings[1275], strings[1276], strings[1277],
       strings[1278], strings[9]});
  IFC4X3_types[839] =
      new enumeration_type(strings[1279], 839,
                           {strings[1280], strings[1281], strings[1282],
                            strings[1283], strings[8], strings[9]});
  IFC4X3_types[841] = new enumeration_type(
      strings[1284], 841,
      {strings[1285], strings[1286], strings[1287], strings[1288],
       strings[1289], strings[1290], strings[1291], strings[1292],
       strings[1293], strings[1294], strings[8], strings[9]});
  IFC4X3_types[844] = new enumeration_type(
      strings[1295], 844,
      {strings[1296], strings[1297], strings[1298], strings[1299],
       strings[1300], strings[1301], strings[1302], strings[8], strings[9]});
  IFC4X3_types[853] = new type_declaration(
      strings[1303], 853, new simple_type(simple_type::real_type));
  IFC4X3_types[859] = new enumeration_type(
      strings[1304], 859,
      {strings[1305], strings[1306], strings[1307], strings[1308],
       strings[1309], strings[1310], strings[8], strings[9]});
  IFC4X3_types[857] =
      new enumeration_type(strings[1311], 857,
                           {strings[1312], strings[1313], strings[1307],
                            strings[1314], strings[8], strings[9]});
  IFC4X3_types[862] = new enumeration_type(
      strings[1315], 862,
      {strings[1316], strings[1317], strings[1318], strings[1319], strings[214],
       strings[1320], strings[1321], strings[1322], strings[8], strings[9]});
  IFC4X3_types[863] =
      new enumeration_type(strings[1323], 863, {strings[8], strings[9]});
  IFC4X3_types[867] = new enumeration_type(
      strings[1324], 867,
      {strings[1325], strings[1326], strings[8], strings[9]});
  IFC4X3_types[869] = new enumeration_type(
      strings[1327], 869,
      {strings[1328], strings[1329], strings[1330], strings[1331],
       strings[1332], strings[1333], strings[8], strings[9]});
  IFC4X3_types[870] = new type_declaration(
      strings[1334], 870, new simple_type(simple_type::real_type));
  IFC4X3_types[873] = new type_declaration(
      strings[1335], 873, new simple_type(simple_type::real_type));
  IFC4X3_types[879] = new enumeration_type(
      strings[1336], 879,
      {strings[1337], strings[1338], strings[1339], strings[1340],
       strings[1341], strings[1342], strings[1343], strings[1344]});
  IFC4X3_types[882] = new enumeration_type(
      strings[1345], 882,
      {strings[1346], strings[203], strings[1347], strings[1348], strings[1349],
       strings[1350], strings[1351], strings[1352], strings[8], strings[9]});
  IFC4X3_types[883] = new enumeration_type(
      strings[1353], 883,
      {strings[1354], strings[1355], strings[1356], strings[1357], strings[382],
       strings[1358], strings[1359], strings[1206], strings[383], strings[1360],
       strings[9]});
  IFC4X3_types[886] = new enumeration_type(
      strings[1361], 886,
      {strings[1362], strings[1363], strings[1364], strings[1365],
       strings[1366], strings[1367], strings[8], strings[9]});
  IFC4X3_types[890] = new enumeration_type(
      strings[1368], 890,
      {strings[1369], strings[1370], strings[1371], strings[1372],
       strings[1373], strings[1374], strings[1375], strings[1111], strings[8],
       strings[9]});
  IFC4X3_types[891] =
      new enumeration_type(strings[1376], 891, {strings[1377], strings[1378]});
  IFC4X3_types[893] = new enumeration_type(
      strings[1379], 893,
      {strings[1369], strings[1370], strings[1371], strings[1372],
       strings[1373], strings[1374], strings[1375], strings[1380],
       strings[1111], strings[8], strings[9]});
  IFC4X3_types[898] =
      new enumeration_type(strings[1381], 898, {strings[8], strings[9]});
  IFC4X3_types[968] = new enumeration_type(
      strings[1382], 968,
      {strings[1383], strings[1384], strings[1385], strings[1386],
       strings[1387], strings[1388], strings[203],  strings[1389],
       strings[1390], strings[1391], strings[1392], strings[1393],
       strings[1394], strings[1395], strings[1396], strings[1397],
       strings[1398], strings[1399], strings[1400], strings[1401],
       strings[1402], strings[1403], strings[1404], strings[1405],
       strings[8],    strings[9]});
  IFC4X3_types[969] =
      new enumeration_type(strings[1406], 969, {strings[8], strings[9]});
  IFC4X3_types[970] = new enumeration_type(
      strings[1407], 970,
      {strings[1408], strings[1409], strings[1410], strings[1411],
       strings[1412], strings[1413], strings[1414], strings[1415],
       strings[1416], strings[1417], strings[1418], strings[1419],
       strings[1420], strings[1421], strings[1422], strings[1423],
       strings[1180], strings[1424], strings[1425], strings[1426],
       strings[1427], strings[1428], strings[8]});
  IFC4X3_types[973] = new enumeration_type(
      strings[1429], 973,
      {strings[1430], strings[1431], strings[1432], strings[1433],
       strings[1434], strings[1435], strings[1436], strings[1437],
       strings[1438], strings[1439], strings[1440], strings[1441],
       strings[1442], strings[8], strings[9]});
  IFC4X3_types[975] = new type_declaration(
      strings[1443], 975, new simple_type(simple_type::real_type));
  IFC4X3_types[976] = new type_declaration(
      strings[1444], 976, new simple_type(simple_type::real_type));
  IFC4X3_types[977] = new type_declaration(
      strings[1445], 977, new simple_type(simple_type::real_type));
  IFC4X3_types[978] = new select_type(strings[1446], 978,
                                      {IFC4X3_types[87], IFC4X3_types[977]});
  IFC4X3_types[1023] = new enumeration_type(
      strings[1447], 1023,
      {strings[1448], strings[1449], strings[1450], strings[1451],
       strings[1452], strings[1453], strings[1454], strings[1455],
       strings[1456], strings[1457], strings[1458], strings[1459],
       strings[1460], strings[1461], strings[1462], strings[1463]});
  IFC4X3_types[1026] = new enumeration_type(
      strings[1464], 1026,
      {strings[1465], strings[1466], strings[1467], strings[1468],
       strings[1469], strings[1470], strings[1471], strings[1472],
       strings[1473], strings[1474], strings[1475], strings[1476],
       strings[1477], strings[1478], strings[1479], strings[1480],
       strings[1481], strings[1482], strings[1483], strings[1484],
       strings[1485], strings[1486], strings[1487], strings[1488],
       strings[1489], strings[1490], strings[1491], strings[1492],
       strings[1493], strings[1494]});
  IFC4X3_types[982] = new enumeration_type(
      strings[1495], 982,
      {strings[1496], strings[1497], strings[1498], strings[1499],
       strings[1500], strings[851], strings[1501], strings[1502], strings[1503],
       strings[1504], strings[8], strings[9]});
  IFC4X3_types[991] = new type_declaration(
      strings[1505], 991, new simple_type(simple_type::real_type));
  IFC4X3_types[994] =
      new enumeration_type(strings[1506], 994, {strings[1507], strings[1508]});
  IFC4X3_types[986] = new type_declaration(
      strings[1509], 986, new simple_type(simple_type::real_type));
  IFC4X3_types[1000] = new enumeration_type(
      strings[1510], 1000,
      {strings[1511], strings[1512], strings[1513], strings[1514],
       strings[1515], strings[1516], strings[1517], strings[1518],
       strings[1519], strings[1520], strings[1521], strings[1522],
       strings[1523], strings[1524], strings[1525], strings[1526],
       strings[1527], strings[1528], strings[1529], strings[1530],
       strings[1531], strings[1532], strings[1533], strings[1534],
       strings[1535], strings[1536], strings[1537], strings[1538],
       strings[1539], strings[1540], strings[1541], strings[1542],
       strings[8],    strings[9]});
  IFC4X3_types[1001] =
      new enumeration_type(strings[1543], 1001,
                           {strings[1544], strings[1545], strings[1546],
                            strings[1547], strings[8], strings[9]});
  IFC4X3_types[1005] = new enumeration_type(
      strings[1548], 1005,
      {strings[1549], strings[1550], strings[1551], strings[8], strings[9]});
  IFC4X3_types[1009] = new type_declaration(
      strings[1552], 1009, new simple_type(simple_type::real_type));
  IFC4X3_types[1017] = new enumeration_type(
      strings[1553], 1017,
      {strings[1554], strings[1358], strings[1555], strings[8], strings[9]});
  IFC4X3_types[1015] = new enumeration_type(
      strings[1556], 1015,
      {strings[1557], strings[1558], strings[1559], strings[8], strings[9]});
  IFC4X3_types[1020] = new enumeration_type(
      strings[1560], 1020,
      {strings[1561], strings[1562], strings[1563], strings[1564],
       strings[1565], strings[1566], strings[1567], strings[1568],
       strings[1569], strings[1570], strings[1571], strings[1572],
       strings[1573]});
  IFC4X3_types[1030] = new enumeration_type(
      strings[1574], 1030,
      {strings[1575], strings[1576], strings[1577], strings[1578], strings[372],
       strings[1579], strings[1401], strings[1580], strings[1581], strings[8],
       strings[9]});
  IFC4X3_types[1034] = new enumeration_type(
      strings[1582], 1034,
      {strings[1583], strings[1584], strings[8], strings[9]});
  IFC4X3_types[1035] = new type_declaration(
      strings[1585], 1035, new simple_type(simple_type::real_type));
  IFC4X3_types[1038] = new type_declaration(
      strings[1586], 1038, new simple_type(simple_type::real_type));
  IFC4X3_types[1039] = new type_declaration(
      strings[1587], 1039, new simple_type(simple_type::real_type));
  IFC4X3_types[1040] = new type_declaration(
      strings[1588], 1040, new simple_type(simple_type::real_type));
  IFC4X3_types[1041] = new type_declaration(
      strings[1589], 1041, new simple_type(simple_type::real_type));
  IFC4X3_types[1046] = new enumeration_type(
      strings[1590], 1046,
      {strings[1591], strings[1592], strings[8], strings[9]});
  IFC4X3_types[1048] = new enumeration_type(
      strings[1593], 1048,
      {strings[1594], strings[809], strings[1595], strings[948], strings[1596],
       strings[1597], strings[8], strings[9]});
  IFC4X3_types[1056] = new enumeration_type(
      strings[1598], 1056,
      {strings[1599], strings[1600], strings[1601], strings[371], strings[1602],
       strings[1603], strings[601], strings[1283], strings[33], strings[608],
       strings[8], strings[9]});
  IFC4X3_types[1057] = new type_declaration(
      strings[1604], 1057, new simple_type(simple_type::real_type));
  IFC4X3_types[1058] = new type_declaration(
      strings[1605], 1058, new simple_type(simple_type::real_type));
  IFC4X3_types[1060] = new type_declaration(
      strings[1606], 1060, new simple_type(simple_type::real_type));
  IFC4X3_types[1066] = new enumeration_type(
      strings[1607], 1066,
      {strings[1608], strings[1609], strings[1610], strings[8], strings[9]});
  IFC4X3_types[1070] = new enumeration_type(
      strings[1611], 1070,
      {strings[1612], strings[1434], strings[1325], strings[1326],
       strings[1613], strings[8], strings[9]});
  IFC4X3_types[1072] = new enumeration_type(
      strings[1614], 1072,
      {strings[1615], strings[1616], strings[1617], strings[1618],
       strings[1619], strings[1620], strings[1621], strings[1622],
       strings[1623], strings[1624], strings[1625], strings[1626],
       strings[1627], strings[1628], strings[1629], strings[8], strings[9]});
  IFC4X3_types[1073] =
      new enumeration_type(strings[1630], 1073,
                           {strings[1631], strings[1632], strings[1633],
                            strings[1634], strings[1635]});
  IFC4X3_types[1081] = new enumeration_type(
      strings[1636], 1081,
      {strings[1637], strings[1638], strings[1639], strings[440], strings[1640],
       strings[1641], strings[1642], strings[8], strings[9]});
  IFC4X3_types[1084] = new enumeration_type(
      strings[1643], 1084,
      {strings[560], strings[1644], strings[1645], strings[1646], strings[1647],
       strings[8], strings[9]});
  IFC4X3_types[1110] =
      new enumeration_type(strings[1648], 1110,
                           {strings[1649], strings[1637], strings[1638],
                            strings[1650], strings[8], strings[9]});
  IFC4X3_types[1113] = new enumeration_type(
      strings[1651], 1113,
      {strings[1652], strings[1653], strings[1654], strings[8], strings[9]});
  IFC4X3_types[1121] = new enumeration_type(
      strings[1655], 1121,
      {strings[1656], strings[1204], strings[8], strings[9]});
  IFC4X3_types[1127] = new enumeration_type(
      strings[1657], 1127,
      {strings[1658], strings[1659], strings[1660], strings[1661],
       strings[1662], strings[1663], strings[1664], strings[1665],
       strings[1666], strings[1667], strings[1668], strings[8], strings[9]});
  IFC4X3_types[1132] = new enumeration_type(
      strings[1669], 1132, {strings[1670], strings[519], strings[520]});
  IFC4X3_types[1147] = new enumeration_type(
      strings[1671], 1147,
      {strings[1672], strings[1673], strings[1674], strings[1675],
       strings[1676], strings[750], strings[1677], strings[1678], strings[1679],
       strings[1680], strings[1681], strings[8], strings[9]});
  IFC4X3_types[1151] = new enumeration_type(
      strings[1682], 1151,
      {strings[1683], strings[1684], strings[1685], strings[8], strings[9]});
  IFC4X3_types[1157] = new enumeration_type(
      strings[1686], 1157,
      {strings[1687], strings[1688], strings[1689], strings[1690],
       strings[1691], strings[1692], strings[1693], strings[1694], strings[8],
       strings[9]});
  IFC4X3_types[1159] = new enumeration_type(
      strings[1695], 1159, {strings[1696], strings[1697], strings[9]});
  IFC4X3_types[1163] = new enumeration_type(
      strings[1698], 1163,
      {strings[1699], strings[1700], strings[1250], strings[1599],
       strings[1701], strings[1702], strings[577],  strings[1703],
       strings[1704], strings[1705], strings[1706], strings[1707],
       strings[1708], strings[1709], strings[1710], strings[1711],
       strings[1712], strings[1252], strings[1253], strings[1713],
       strings[1714], strings[8],    strings[9]});
  IFC4X3_types[1165] = new type_declaration(
      strings[1715], 1165, new simple_type(simple_type::real_type));
  IFC4X3_types[1166] = new type_declaration(
      strings[1716], 1166, new simple_type(simple_type::real_type));
  IFC4X3_types[1170] = new enumeration_type(
      strings[1717], 1170,
      {strings[1079], strings[1718], strings[1719], strings[8], strings[9]});
  IFC4X3_types[1173] = new enumeration_type(
      strings[1720], 1173,
      {strings[1079], strings[1721], strings[562], strings[1722], strings[1723],
       strings[8], strings[9]});
  IFC4X3_types[1175] =
      new enumeration_type(strings[1724], 1175,
                           {strings[1725], strings[1726], strings[1727],
                            strings[1728], strings[8], strings[9]});
  IFC4X3_types[1178] = new type_declaration(
      strings[1729], 1178, new simple_type(simple_type::string_type));
  IFC4X3_types[1179] = new type_declaration(
      strings[1730], 1179, new simple_type(simple_type::string_type));
  IFC4X3_types[1180] = new type_declaration(
      strings[1731], 1180, new simple_type(simple_type::string_type));
  IFC4X3_types[1181] = new type_declaration(
      strings[1732], 1181, new simple_type(simple_type::string_type));
  IFC4X3_types[1185] = new enumeration_type(
      strings[1733], 1185,
      {strings[1734], strings[630], strings[632], strings[1735]});
  IFC4X3_types[1190] = new type_declaration(
      strings[1736], 1190, new simple_type(simple_type::string_type));
  IFC4X3_types[1198] = new type_declaration(
      strings[1737], 1198, new simple_type(simple_type::real_type));
  IFC4X3_types[1199] = new type_declaration(
      strings[1738], 1199, new simple_type(simple_type::real_type));
  IFC4X3_types[1200] = new type_declaration(
      strings[1739], 1200, new simple_type(simple_type::real_type));
  IFC4X3_types[1201] = new type_declaration(
      strings[1740], 1201, new simple_type(simple_type::real_type));
  IFC4X3_types[1202] = new type_declaration(
      strings[1741], 1202, new simple_type(simple_type::real_type));
  IFC4X3_types[1203] = new type_declaration(
      strings[1742], 1203, new simple_type(simple_type::real_type));
  IFC4X3_types[1205] = new type_declaration(
      strings[1743], 1205, new simple_type(simple_type::string_type));
  IFC4X3_types[1206] = new type_declaration(
      strings[1744], 1206, new simple_type(simple_type::real_type));
  IFC4X3_types[1207] = new select_type(strings[1745], 1207,
                                       {IFC4X3_types[358], IFC4X3_types[870]});
  IFC4X3_types[1210] = new enumeration_type(
      strings[1746], 1210,
      {strings[1747], strings[1638], strings[1748], strings[1749],
       strings[1750], strings[1751], strings[9]});
  IFC4X3_types[1212] = new type_declaration(
      strings[1752], 1212, new simple_type(simple_type::integer_type));
  IFC4X3_types[1216] = new type_declaration(
      strings[1753], 1216, new simple_type(simple_type::real_type));
  IFC4X3_types[1219] = new enumeration_type(
      strings[1754], 1219,
      {strings[1755], strings[1756], strings[1757], strings[1758],
       strings[1759], strings[1760], strings[1761], strings[1762], strings[8],
       strings[9]});
  IFC4X3_types[1222] = new enumeration_type(
      strings[1763], 1222,
      {strings[1764], strings[856], strings[15], strings[1765], strings[1766],
       strings[1767], strings[1768], strings[8], strings[9]});
  IFC4X3_types[1223] = new enumeration_type(
      strings[1769], 1223,
      {strings[1747], strings[1770], strings[1771], strings[1772]});
  IFC4X3_types[1224] = new select_type(strings[1773], 1224,
                                       {IFC4X3_types[87], IFC4X3_types[609]});
  IFC4X3_types[1229] = new enumeration_type(
      strings[1774], 1229,
      {strings[1775], strings[1776], strings[1777], strings[1778],
       strings[1779], strings[1780], strings[8], strings[9]});
  IFC4X3_types[1234] = new enumeration_type(
      strings[1781], 1234, {strings[1782], strings[1170], strings[146]});
  IFC4X3_types[1239] = new enumeration_type(
      strings[1783], 1239, {strings[1784], strings[8], strings[9]});
  IFC4X3_types[1253] = new type_declaration(
      strings[1785], 1253, new simple_type(simple_type::string_type));
  IFC4X3_types[1252] = new enumeration_type(
      strings[1786], 1252,
      {strings[1787], strings[1788], strings[1789], strings[1790],
       strings[1791], strings[1792], strings[1793], strings[1794],
       strings[1795], strings[1796], strings[1797], strings[1798],
       strings[1799], strings[1800], strings[1801], strings[1802],
       strings[1803], strings[1804], strings[1805], strings[1806],
       strings[1807], strings[1808], strings[1809], strings[1810],
       strings[1811], strings[1812], strings[1813], strings[1814],
       strings[1815], strings[8]});
  IFC4X3_types[1247] = new enumeration_type(
      strings[1816], 1247,
      {strings[1817], strings[1818], strings[856], strings[1819], strings[1820],
       strings[1821], strings[1822], strings[1823], strings[1824],
       strings[1825], strings[8], strings[9]});
  IFC4X3_types[1250] = new enumeration_type(
      strings[1826], 1250,
      {strings[1827], strings[1828], strings[1829], strings[1830],
       strings[1831], strings[8], strings[9]});
  IFC4X3_types[1258] = new enumeration_type(
      strings[1832], 1258,
      {strings[1833], strings[1834], strings[1835], strings[1836],
       strings[1837], strings[1838], strings[1839], strings[1840],
       strings[1841], strings[1842], strings[1843], strings[1844],
       strings[1845], strings[1846], strings[1847], strings[1848],
       strings[1849], strings[1850], strings[1851], strings[1852],
       strings[1853], strings[8],    strings[9]});
  IFC4X3_types[1259] = new type_declaration(
      strings[1854], 1259, new simple_type(simple_type::real_type));
  IFC4X3_types[1264] = new enumeration_type(
      strings[1855], 1264,
      {strings[1856], strings[1857], strings[1858], strings[1859],
       strings[1860], strings[1861], strings[1862], strings[8], strings[9]});
  IFC4X3_types[1270] = new enumeration_type(
      strings[1863], 1270,
      {strings[1864], strings[1865], strings[1217], strings[1866],
       strings[1867], strings[1868], strings[8], strings[9]});
  IFC4X3_types[1273] = new enumeration_type(
      strings[1869], 1273,
      {strings[1870], strings[1871], strings[1872], strings[8], strings[9]});
  IFC4X3_types[1275] = new enumeration_type(
      strings[1873], 1275,
      {strings[1346], strings[1874], strings[1875], strings[8], strings[9]});
  IFC4X3_types[1278] = new enumeration_type(
      strings[1876], 1278,
      {strings[1877], strings[1878], strings[1370], strings[1879],
       strings[1880], strings[1881], strings[8], strings[9]});
  IFC4X3_types[1279] = new type_declaration(
      strings[1882], 1279, new simple_type(simple_type::real_type));
  IFC4X3_types[1280] = new type_declaration(
      strings[1883], 1280, new simple_type(simple_type::real_type));
  IFC4X3_types[1284] = new enumeration_type(
      strings[1884], 1284,
      {strings[1885], strings[1886], strings[1887], strings[1888],
       strings[1889], strings[1641], strings[1890], strings[1375],
       strings[1891], strings[1892], strings[1893], strings[8], strings[9]});
  IFC4X3_types[1285] = new type_declaration(
      strings[1894], 1285, new simple_type(simple_type::real_type));
  IFC4X3_types[1286] = new type_declaration(
      strings[1895], 1286, new simple_type(simple_type::real_type));
  IFC4X3_types[1287] = new select_type(strings[1896], 1287,
                                       {IFC4X3_types[87], IFC4X3_types[1286]});
  IFC4X3_types[1290] = new enumeration_type(
      strings[1897], 1290,
      {strings[1898], strings[1899], strings[1900], strings[1901],
       strings[1902], strings[1903], strings[1904], strings[8], strings[9]});
  IFC4X3_types[1293] = new enumeration_type(
      strings[1905], 1293,
      {strings[1906], strings[1907], strings[1908], strings[1909],
       strings[1910], strings[1911], strings[1912], strings[1913],
       strings[1914], strings[1915], strings[1916], strings[1917],
       strings[1918], strings[9]});
  IFC4X3_types[1294] =
      new enumeration_type(strings[1919], 1294,
                           {strings[1920], strings[630], strings[631],
                            strings[632], strings[1921], strings[9]});
  IFC4X3_types[1296] = new enumeration_type(
      strings[1922], 1296,
      {strings[634], strings[636], strings[637], strings[1923], strings[383],
       strings[638], strings[384], strings[9]});
  IFC4X3_types[1297] = new enumeration_type(
      strings[1924], 1297,
      {strings[1925], strings[1926], strings[1927], strings[1928],
       strings[1929], strings[1930], strings[1931], strings[1932],
       strings[1933], strings[8], strings[9]});
  IFC4X3_types[1299] = new enumeration_type(
      strings[1934], 1299,
      {strings[1935], strings[1936], strings[1937], strings[8], strings[9]});
  IFC4X3_types[1300] = new enumeration_type(
      strings[1938], 1300,
      {strings[1925], strings[1926], strings[1927], strings[1928],
       strings[1929], strings[1930], strings[1931], strings[1932],
       strings[1933], strings[8], strings[9]});
  IFC4X3_types[1302] = new enumeration_type(
      strings[1939], 1302,
      {strings[1940], strings[1941], strings[1942], strings[8], strings[9]});
  IFC4X3_types[1305] = new enumeration_type(
      strings[1943], 1305,
      {strings[1944], strings[1945], strings[1946], strings[8], strings[9]});
  IFC4X3_types[1307] = new enumeration_type(
      strings[1947], 1307,
      {strings[1944], strings[1945], strings[1946], strings[8], strings[9]});
  IFC4X3_types[7] = new entity(strings[1948], false, 7, (entity *)0);
  IFC4X3_types[12] = new entity(strings[1949], true, 12, (entity *)0);
  IFC4X3_types[36] = new entity(strings[1950], true, 36, (entity *)0);
  IFC4X3_types[40] =
      new entity(strings[1951], false, 40, (entity *)IFC4X3_types[36]);
  IFC4X3_types[49] = new entity(strings[1952], false, 49, (entity *)0);
  IFC4X3_types[50] = new entity(strings[1953], false, 50, (entity *)0);
  IFC4X3_types[52] = new entity(strings[1954], false, 52, (entity *)0);
  IFC4X3_types[93] = new entity(strings[1955], true, 93, (entity *)0);
  IFC4X3_types[95] =
      new entity(strings[1956], false, 95, (entity *)IFC4X3_types[93]);
  IFC4X3_types[96] =
      new entity(strings[1957], false, 96, (entity *)IFC4X3_types[93]);
  IFC4X3_types[97] =
      new entity(strings[1958], false, 97, (entity *)IFC4X3_types[93]);
  IFC4X3_types[98] =
      new entity(strings[1959], false, 98, (entity *)IFC4X3_types[97]);
  IFC4X3_types[207] = new entity(strings[1960], true, 207, (entity *)0);
  IFC4X3_types[209] =
      new entity(strings[1961], false, 209, (entity *)IFC4X3_types[207]);
  IFC4X3_types[210] =
      new entity(strings[1962], false, 210, (entity *)IFC4X3_types[207]);
  IFC4X3_types[212] =
      new entity(strings[1963], false, 212, (entity *)IFC4X3_types[207]);
  IFC4X3_types[213] = new entity(strings[1964], true, 213, (entity *)0);
  IFC4X3_types[244] = new entity(strings[1965], true, 244, (entity *)0);
  IFC4X3_types[245] = new entity(strings[1966], true, 245, (entity *)0);
  IFC4X3_types[252] =
      new entity(strings[1967], false, 252, (entity *)IFC4X3_types[50]);
  IFC4X3_types[300] = new entity(strings[1968], false, 300, (entity *)0);
  IFC4X3_types[301] = new entity(strings[1969], false, 301, (entity *)0);
  IFC4X3_types[304] = new entity(strings[1970], false, 304, (entity *)0);
  IFC4X3_types[425] = new entity(strings[1971], true, 425, (entity *)0);
  IFC4X3_types[429] = new entity(strings[1972], true, 429, (entity *)0);
  IFC4X3_types[426] =
      new entity(strings[1973], false, 426, (entity *)IFC4X3_types[429]);
  IFC4X3_types[427] =
      new entity(strings[1974], false, 427, (entity *)IFC4X3_types[429]);
  IFC4X3_types[428] =
      new entity(strings[1975], false, 428, (entity *)IFC4X3_types[429]);
  IFC4X3_types[523] = new entity(strings[1976], false, 523, (entity *)0);
  IFC4X3_types[564] = new entity(strings[1977], false, 564, (entity *)0);
  IFC4X3_types[586] =
      new entity(strings[1978], false, 586, (entity *)IFC4X3_types[425]);
  IFC4X3_types[587] =
      new entity(strings[1979], false, 587, (entity *)IFC4X3_types[429]);
  IFC4X3_types[590] = new entity(strings[1980], false, 590, (entity *)0);
  IFC4X3_types[596] = new entity(strings[1981], false, 596, (entity *)0);
  IFC4X3_types[627] =
      new entity(strings[1982], false, 627, (entity *)IFC4X3_types[244]);
  IFC4X3_types[638] = new entity(strings[1983], false, 638, (entity *)0);
  IFC4X3_types[641] = new entity(strings[1984], true, 641, (entity *)0);
  IFC4X3_types[643] =
      new entity(strings[1985], false, 643, (entity *)IFC4X3_types[641]);
  IFC4X3_types[644] =
      new entity(strings[1986], false, 644, (entity *)IFC4X3_types[641]);
  IFC4X3_types[646] =
      new entity(strings[1987], false, 646, (entity *)IFC4X3_types[643]);
  IFC4X3_types[647] = new entity(strings[1988], false, 647, (entity *)0);
  IFC4X3_types[648] =
      new entity(strings[1989], false, 648, (entity *)IFC4X3_types[641]);
  IFC4X3_types[649] =
      new entity(strings[1990], false, 649, (entity *)IFC4X3_types[641]);
  IFC4X3_types[652] =
      new entity(strings[1991], false, 652, (entity *)IFC4X3_types[648]);
  IFC4X3_types[656] = new entity(strings[1992], true, 656, (entity *)0);
  IFC4X3_types[658] = new entity(strings[1993], false, 658, (entity *)0);
  IFC4X3_types[668] =
      new entity(strings[1994], false, 668, (entity *)IFC4X3_types[213]);
  IFC4X3_types[685] = new entity(strings[1995], false, 685, (entity *)0);
  IFC4X3_types[693] = new entity(strings[1996], true, 693, (entity *)0);
  IFC4X3_types[704] = new entity(strings[1997], true, 704, (entity *)0);
  IFC4X3_types[702] =
      new entity(strings[1998], false, 702, (entity *)IFC4X3_types[213]);
  IFC4X3_types[717] = new entity(strings[1999], false, 717, (entity *)0);
  IFC4X3_types[724] = new entity(strings[2000], false, 724, (entity *)0);
  IFC4X3_types[738] = new entity(strings[2001], false, 738, (entity *)0);
  IFC4X3_types[739] = new entity(strings[2002], false, 739, (entity *)0);
  IFC4X3_types[743] = new entity(strings[2003], true, 743, (entity *)0);
  IFC4X3_types[744] =
      new entity(strings[2004], true, 744, (entity *)IFC4X3_types[743]);
  IFC4X3_types[781] =
      new entity(strings[2005], false, 781, (entity *)IFC4X3_types[12]);
  IFC4X3_types[791] = new entity(strings[2006], true, 791, (entity *)0);
  IFC4X3_types[792] = new entity(strings[2007], false, 792, (entity *)0);
  IFC4X3_types[793] =
      new entity(strings[2008], false, 793, (entity *)IFC4X3_types[792]);
  IFC4X3_types[794] = new entity(strings[2009], true, 794, (entity *)0);
  IFC4X3_types[803] = new entity(strings[2010], true, 803, (entity *)0);
  IFC4X3_types[806] = new entity(strings[2011], false, 806, (entity *)0);
  IFC4X3_types[810] =
      new entity(strings[2012], false, 810, (entity *)IFC4X3_types[245]);
  IFC4X3_types[818] = new entity(strings[2013], true, 818, (entity *)0);
  IFC4X3_types[823] =
      new entity(strings[2014], false, 823, (entity *)IFC4X3_types[818]);
  IFC4X3_types[845] =
      new entity(strings[2015], false, 845, (entity *)IFC4X3_types[744]);
  IFC4X3_types[846] =
      new entity(strings[2016], false, 846, (entity *)IFC4X3_types[744]);
  IFC4X3_types[847] =
      new entity(strings[2017], false, 847, (entity *)IFC4X3_types[744]);
  IFC4X3_types[848] =
      new entity(strings[2018], false, 848, (entity *)IFC4X3_types[744]);
  IFC4X3_types[850] =
      new entity(strings[2019], false, 850, (entity *)IFC4X3_types[744]);
  IFC4X3_types[851] =
      new entity(strings[2020], false, 851, (entity *)IFC4X3_types[744]);
  IFC4X3_types[852] =
      new entity(strings[2021], false, 852, (entity *)IFC4X3_types[744]);
  IFC4X3_types[878] = new entity(strings[2022], false, 878, (entity *)0);
  IFC4X3_types[880] = new entity(strings[2023], false, 880, (entity *)0);
  IFC4X3_types[951] = new entity(strings[2024], true, 951, (entity *)0);
  IFC4X3_types[952] = new entity(strings[2025], true, 952, (entity *)0);
  IFC4X3_types[953] = new entity(strings[2026], true, 953, (entity *)0);
  IFC4X3_types[954] = new entity(strings[2027], false, 954, (entity *)0);
  IFC4X3_types[958] = new entity(strings[2028], true, 958, (entity *)0);
  IFC4X3_types[974] = new entity(strings[2029], true, 974, (entity *)0);
  IFC4X3_types[1025] =
      new entity(strings[2030], false, 1025, (entity *)IFC4X3_types[693]);
  IFC4X3_types[983] = new entity(strings[2031], true, 983, (entity *)0);
  IFC4X3_types[1006] = new entity(strings[2032], false, 1006, (entity *)0);
  IFC4X3_types[1007] =
      new entity(strings[2033], true, 1007, (entity *)IFC4X3_types[951]);
  IFC4X3_types[1008] =
      new entity(strings[2034], false, 1008, (entity *)IFC4X3_types[1007]);
  IFC4X3_types[1079] = new entity(strings[2035], true, 1079, (entity *)0);
  IFC4X3_types[1089] = new entity(strings[2036], true, 1089, (entity *)0);
  IFC4X3_types[1091] =
      new entity(strings[2037], false, 1091, (entity *)IFC4X3_types[1089]);
  IFC4X3_types[1094] =
      new entity(strings[2038], true, 1094, (entity *)IFC4X3_types[1089]);
  IFC4X3_types[1100] =
      new entity(strings[2039], true, 1100, (entity *)IFC4X3_types[1094]);
  IFC4X3_types[1101] =
      new entity(strings[2040], false, 1101, (entity *)IFC4X3_types[1100]);
  IFC4X3_types[1118] =
      new entity(strings[2041], true, 1118, (entity *)IFC4X3_types[951]);
  IFC4X3_types[1116] =
      new entity(strings[2042], false, 1116, (entity *)IFC4X3_types[953]);
  IFC4X3_types[1117] =
      new entity(strings[2043], false, 1117, (entity *)IFC4X3_types[1118]);
  IFC4X3_types[1131] =
      new entity(strings[2044], false, 1131, (entity *)IFC4X3_types[1094]);
  IFC4X3_types[1133] =
      new entity(strings[2045], false, 1133, (entity *)IFC4X3_types[794]);
  IFC4X3_types[1135] =
      new entity(strings[2046], false, 1135, (entity *)IFC4X3_types[791]);
  IFC4X3_types[1136] =
      new entity(strings[2047], false, 1136, (entity *)IFC4X3_types[791]);
  IFC4X3_types[1138] =
      new entity(strings[2048], false, 1138, (entity *)IFC4X3_types[791]);
  IFC4X3_types[1139] =
      new entity(strings[2049], false, 1139, (entity *)IFC4X3_types[791]);
  IFC4X3_types[1140] =
      new entity(strings[2050], true, 1140, (entity *)IFC4X3_types[791]);
  IFC4X3_types[1152] = new entity(strings[2051], false, 1152, (entity *)0);
  IFC4X3_types[1153] = new entity(strings[2052], false, 1153, (entity *)0);
  IFC4X3_types[1154] = new entity(strings[2053], false, 1154, (entity *)0);
  IFC4X3_types[1160] =
      new entity(strings[2054], false, 1160, (entity *)IFC4X3_types[983]);
  IFC4X3_types[1161] =
      new entity(strings[2055], false, 1161, (entity *)IFC4X3_types[1160]);
  IFC4X3_types[1164] =
      new entity(strings[2056], false, 1164, (entity *)IFC4X3_types[12]);
  IFC4X3_types[1186] =
      new entity(strings[2057], false, 1186, (entity *)IFC4X3_types[794]);
  IFC4X3_types[1188] =
      new entity(strings[2058], false, 1188, (entity *)IFC4X3_types[791]);
  IFC4X3_types[1189] =
      new entity(strings[2059], false, 1189, (entity *)IFC4X3_types[791]);
  IFC4X3_types[1191] =
      new entity(strings[2060], true, 1191, (entity *)IFC4X3_types[791]);
  IFC4X3_types[1192] =
      new entity(strings[2061], false, 1192, (entity *)IFC4X3_types[1191]);
  IFC4X3_types[1193] = new entity(strings[2062], false, 1193, (entity *)0);
  IFC4X3_types[1194] =
      new entity(strings[2063], false, 1194, (entity *)IFC4X3_types[1193]);
  IFC4X3_types[1195] =
      new entity(strings[2064], false, 1195, (entity *)IFC4X3_types[1191]);
  IFC4X3_types[1196] =
      new entity(strings[2065], false, 1196, (entity *)IFC4X3_types[791]);
  IFC4X3_types[1197] =
      new entity(strings[2066], false, 1197, (entity *)IFC4X3_types[791]);
  IFC4X3_types[1208] = new entity(strings[2067], false, 1208, (entity *)0);
  IFC4X3_types[1209] = new entity(strings[2068], true, 1209, (entity *)0);
  IFC4X3_types[1211] = new entity(strings[2069], false, 1211, (entity *)0);
  IFC4X3_types[1213] =
      new entity(strings[2070], true, 1213, (entity *)IFC4X3_types[953]);
  IFC4X3_types[1214] =
      new entity(strings[2071], false, 1214, (entity *)IFC4X3_types[1007]);
  IFC4X3_types[1251] = new entity(strings[2072], false, 1251, (entity *)0);
  IFC4X3_types[1265] =
      new entity(strings[2073], false, 1265, (entity *)IFC4X3_types[1213]);
  IFC4X3_types[1267] =
      new entity(strings[2074], false, 1267, (entity *)IFC4X3_types[1265]);
  IFC4X3_types[1276] = new entity(strings[2075], false, 1276, (entity *)0);
  IFC4X3_types[1308] =
      new entity(strings[2076], false, 1308, (entity *)IFC4X3_types[983]);
  IFC4X3_types[8] = new select_type(
      strings[2077], 8,
      {IFC4X3_types[717], IFC4X3_types[738], IFC4X3_types[739]});
  IFC4X3_types[57] = new type_declaration(
      strings[2078], 57,
      new aggregation_type(aggregation_type::list_type, 3, 3,
                           new named_type(IFC4X3_types[777])));
  IFC4X3_types[80] = new select_type(strings[2079], 80,
                                     {IFC4X3_types[585], IFC4X3_types[761]});
  IFC4X3_types[102] = new type_declaration(strings[2080], 102,
                                           new named_type(IFC4X3_types[574]));
  IFC4X3_types[277] = new select_type(strings[2081], 277,
                                      {IFC4X3_types[697], IFC4X3_types[726]});
  IFC4X3_types[298] = new select_type(
      strings[2082], 298,
      {IFC4X3_types[0],    IFC4X3_types[1],    IFC4X3_types[45],
       IFC4X3_types[58],   IFC4X3_types[197],  IFC4X3_types[271],
       IFC4X3_types[346],  IFC4X3_types[359],  IFC4X3_types[371],
       IFC4X3_types[372],  IFC4X3_types[373],  IFC4X3_types[390],
       IFC4X3_types[394],  IFC4X3_types[409],  IFC4X3_types[496],
       IFC4X3_types[497],  IFC4X3_types[533],  IFC4X3_types[534],
       IFC4X3_types[539],  IFC4X3_types[551],  IFC4X3_types[553],
       IFC4X3_types[562],  IFC4X3_types[566],  IFC4X3_types[572],
       IFC4X3_types[605],  IFC4X3_types[606],  IFC4X3_types[609],
       IFC4X3_types[610],  IFC4X3_types[621],  IFC4X3_types[622],
       IFC4X3_types[624],  IFC4X3_types[625],  IFC4X3_types[633],
       IFC4X3_types[634],  IFC4X3_types[636],  IFC4X3_types[674],
       IFC4X3_types[675],  IFC4X3_types[676],  IFC4X3_types[678],
       IFC4X3_types[681],  IFC4X3_types[682],  IFC4X3_types[683],
       IFC4X3_types[684],  IFC4X3_types[740],  IFC4X3_types[759],
       IFC4X3_types[782],  IFC4X3_types[795],  IFC4X3_types[853],
       IFC4X3_types[975],  IFC4X3_types[976],  IFC4X3_types[977],
       IFC4X3_types[991],  IFC4X3_types[986],  IFC4X3_types[1009],
       IFC4X3_types[1038], IFC4X3_types[1039], IFC4X3_types[1040],
       IFC4X3_types[1041], IFC4X3_types[1057], IFC4X3_types[1165],
       IFC4X3_types[1166], IFC4X3_types[1198], IFC4X3_types[1199],
       IFC4X3_types[1200], IFC4X3_types[1201], IFC4X3_types[1202],
       IFC4X3_types[1216], IFC4X3_types[1259], IFC4X3_types[1280],
       IFC4X3_types[1285], IFC4X3_types[1286]});
  IFC4X3_types[583] = new select_type(strings[2083], 583,
                                      {IFC4X3_types[951], IFC4X3_types[953]});
  IFC4X3_types[588] = new select_type(strings[2084], 588,
                                      {IFC4X3_types[586], IFC4X3_types[587]});
  IFC4X3_types[591] = new select_type(strings[2085], 591,
                                      {IFC4X3_types[429], IFC4X3_types[596]});
  IFC4X3_types[611] = new type_declaration(
      strings[2086], 611,
      new aggregation_type(aggregation_type::list_type, 2, -1,
                           new named_type(IFC4X3_types[777])));
  IFC4X3_types[655] = new select_type(
      strings[2087], 655,
      {IFC4X3_types[641], IFC4X3_types[647], IFC4X3_types[656]});
  IFC4X3_types[698] = new type_declaration(strings[2088], 698,
                                           new named_type(IFC4X3_types[870]));
  IFC4X3_types[705] = new select_type(
      strings[2089], 705,
      {IFC4X3_types[12], IFC4X3_types[50], IFC4X3_types[429], IFC4X3_types[641],
       IFC4X3_types[717], IFC4X3_types[738], IFC4X3_types[739],
       IFC4X3_types[1152], IFC4X3_types[1209]});
  IFC4X3_types[780] = new type_declaration(strings[2090], 780,
                                           new named_type(IFC4X3_types[870]));
  IFC4X3_types[997] = new select_type(strings[2091], 997,
                                      {IFC4X3_types[57], IFC4X3_types[611]});
  IFC4X3_types[1021] =
      new select_type(strings[2092], 1021,
                      {IFC4X3_types[81], IFC4X3_types[87], IFC4X3_types[291],
                       IFC4X3_types[292], IFC4X3_types[358], IFC4X3_types[538],
                       IFC4X3_types[552], IFC4X3_types[574], IFC4X3_types[617],
                       IFC4X3_types[777], IFC4X3_types[873], IFC4X3_types[1178],
                       IFC4X3_types[1205], IFC4X3_types[1212]});
  IFC4X3_types[1027] = new select_type(strings[2093], 1027,
                                       {IFC4X3_types[303], IFC4X3_types[585],
                                        IFC4X3_types[698], IFC4X3_types[778],
                                        IFC4X3_types[780], IFC4X3_types[870]});
  IFC4X3_types[1059] = new select_type(
      strings[2094], 1059, {IFC4X3_types[1058], IFC4X3_types[1060]});
  IFC4X3_types[1134] = new select_type(strings[2095], 1134,
                                       {IFC4X3_types[427], IFC4X3_types[1135],
                                        IFC4X3_types[1136], IFC4X3_types[1138],
                                        IFC4X3_types[1139]});
  IFC4X3_types[1244] = new select_type(
      strings[2096], 1244,
      {IFC4X3_types[300], IFC4X3_types[685], IFC4X3_types[693]});
  IFC4X3_types[31] =
      new entity(strings[2097], false, 31, (entity *)IFC4X3_types[36]);
  IFC4X3_types[34] =
      new entity(strings[2098], false, 34, (entity *)IFC4X3_types[36]);
  IFC4X3_types[53] =
      new entity(strings[2099], false, 53, (entity *)IFC4X3_types[958]);
  IFC4X3_types[54] =
      new entity(strings[2100], false, 54, (entity *)IFC4X3_types[806]);
  IFC4X3_types[55] =
      new entity(strings[2101], false, 55, (entity *)IFC4X3_types[806]);
  IFC4X3_types[56] =
      new entity(strings[2102], false, 56, (entity *)IFC4X3_types[54]);
  IFC4X3_types[82] =
      new entity(strings[2103], false, 82, (entity *)IFC4X3_types[1140]);
  IFC4X3_types[156] =
      new entity(strings[2104], false, 156, (entity *)IFC4X3_types[55]);
  IFC4X3_types[169] =
      new entity(strings[2105], false, 169, (entity *)IFC4X3_types[425]);
  IFC4X3_types[170] =
      new entity(strings[2106], false, 170, (entity *)IFC4X3_types[429]);
  IFC4X3_types[181] =
      new entity(strings[2107], false, 181, (entity *)IFC4X3_types[791]);
  IFC4X3_types[182] =
      new entity(strings[2108], true, 182, (entity *)IFC4X3_types[791]);
  IFC4X3_types[196] =
      new entity(strings[2109], false, 196, (entity *)IFC4X3_types[806]);
  IFC4X3_types[205] =
      new entity(strings[2110], false, 205, (entity *)IFC4X3_types[1213]);
  IFC4X3_types[206] =
      new entity(strings[2111], false, 206, (entity *)IFC4X3_types[207]);
  IFC4X3_types[208] =
      new entity(strings[2112], false, 208, (entity *)IFC4X3_types[209]);
  IFC4X3_types[228] =
      new entity(strings[2113], false, 228, (entity *)IFC4X3_types[693]);
  IFC4X3_types[233] =
      new entity(strings[2114], false, 233, (entity *)IFC4X3_types[693]);
  IFC4X3_types[234] =
      new entity(strings[2115], false, 234, (entity *)IFC4X3_types[233]);
  IFC4X3_types[267] =
      new entity(strings[2116], false, 267, (entity *)IFC4X3_types[958]);
  IFC4X3_types[281] =
      new entity(strings[2117], false, 281, (entity *)IFC4X3_types[794]);
  IFC4X3_types[282] =
      new entity(strings[2118], false, 282, (entity *)IFC4X3_types[791]);
  IFC4X3_types[283] =
      new entity(strings[2119], false, 283, (entity *)IFC4X3_types[791]);
  IFC4X3_types[284] =
      new entity(strings[2120], false, 284, (entity *)IFC4X3_types[791]);
  IFC4X3_types[299] =
      new entity(strings[2121], false, 299, (entity *)IFC4X3_types[806]);
  IFC4X3_types[331] =
      new entity(strings[2122], false, 331, (entity *)IFC4X3_types[425]);
  IFC4X3_types[332] =
      new entity(strings[2123], false, 332, (entity *)IFC4X3_types[958]);
  IFC4X3_types[333] =
      new entity(strings[2124], false, 333, (entity *)IFC4X3_types[429]);
  IFC4X3_types[365] =
      new entity(strings[2125], false, 365, (entity *)IFC4X3_types[1213]);
  IFC4X3_types[366] =
      new entity(strings[2126], false, 366, (entity *)IFC4X3_types[365]);
  IFC4X3_types[420] =
      new entity(strings[2127], false, 420, (entity *)IFC4X3_types[983]);
  IFC4X3_types[424] =
      new entity(strings[2128], true, 424, (entity *)IFC4X3_types[818]);
  IFC4X3_types[430] =
      new entity(strings[2129], false, 430, (entity *)IFC4X3_types[958]);
  IFC4X3_types[436] =
      new entity(strings[2130], false, 436, (entity *)IFC4X3_types[1213]);
  IFC4X3_types[438] =
      new entity(strings[2131], false, 438, (entity *)IFC4X3_types[1213]);
  IFC4X3_types[439] =
      new entity(strings[2132], false, 439, (entity *)IFC4X3_types[438]);
  IFC4X3_types[440] =
      new entity(strings[2133], false, 440, (entity *)IFC4X3_types[436]);
  IFC4X3_types[448] =
      new entity(strings[2134], false, 448, (entity *)IFC4X3_types[1079]);
  IFC4X3_types[458] =
      new entity(strings[2135], false, 458, (entity *)IFC4X3_types[794]);
  IFC4X3_types[508] =
      new entity(strings[2136], false, 508, (entity *)IFC4X3_types[952]);
  IFC4X3_types[509] =
      new entity(strings[2137], true, 509, (entity *)IFC4X3_types[953]);
  IFC4X3_types[510] =
      new entity(strings[2138], false, 510, (entity *)IFC4X3_types[508]);
  IFC4X3_types[511] =
      new entity(strings[2139], false, 511, (entity *)IFC4X3_types[509]);
  IFC4X3_types[524] =
      new entity(strings[2140], false, 524, (entity *)IFC4X3_types[704]);
  IFC4X3_types[528] =
      new entity(strings[2141], false, 528, (entity *)IFC4X3_types[509]);
  IFC4X3_types[540] =
      new entity(strings[2142], false, 540, (entity *)IFC4X3_types[1140]);
  IFC4X3_types[544] =
      new entity(strings[2143], false, 544, (entity *)IFC4X3_types[791]);
  IFC4X3_types[549] =
      new entity(strings[2144], true, 549, (entity *)IFC4X3_types[1191]);
  IFC4X3_types[550] =
      new entity(strings[2145], false, 550, (entity *)IFC4X3_types[549]);
  IFC4X3_types[563] =
      new entity(strings[2146], false, 563, (entity *)IFC4X3_types[1209]);
  IFC4X3_types[578] =
      new entity(strings[2147], false, 578, (entity *)IFC4X3_types[983]);
  IFC4X3_types[597] =
      new entity(strings[2148], true, 597, (entity *)IFC4X3_types[509]);
  IFC4X3_types[598] =
      new entity(strings[2149], false, 598, (entity *)IFC4X3_types[597]);
  IFC4X3_types[599] =
      new entity(strings[2150], false, 599, (entity *)IFC4X3_types[597]);
  IFC4X3_types[600] =
      new entity(strings[2151], false, 600, (entity *)IFC4X3_types[597]);
  IFC4X3_types[601] =
      new entity(strings[2152], false, 601, (entity *)IFC4X3_types[597]);
  IFC4X3_types[602] =
      new entity(strings[2153], false, 602, (entity *)IFC4X3_types[601]);
  IFC4X3_types[607] =
      new entity(strings[2154], false, 607, (entity *)IFC4X3_types[704]);
  IFC4X3_types[616] =
      new entity(strings[2155], false, 616, (entity *)IFC4X3_types[704]);
  IFC4X3_types[619] =
      new entity(strings[2156], false, 619, (entity *)IFC4X3_types[1213]);
  IFC4X3_types[628] =
      new entity(strings[2157], false, 628, (entity *)IFC4X3_types[953]);
  IFC4X3_types[637] =
      new entity(strings[2158], false, 637, (entity *)IFC4X3_types[641]);
  IFC4X3_types[639] =
      new entity(strings[2159], false, 639, (entity *)IFC4X3_types[641]);
  IFC4X3_types[640] =
      new entity(strings[2160], false, 640, (entity *)IFC4X3_types[641]);
  IFC4X3_types[642] =
      new entity(strings[2161], false, 642, (entity *)IFC4X3_types[803]);
  IFC4X3_types[645] =
      new entity(strings[2162], false, 645, (entity *)IFC4X3_types[656]);
  IFC4X3_types[650] =
      new entity(strings[2163], false, 650, (entity *)IFC4X3_types[656]);
  IFC4X3_types[651] =
      new entity(strings[2164], false, 651, (entity *)IFC4X3_types[650]);
  IFC4X3_types[653] =
      new entity(strings[2165], false, 653, (entity *)IFC4X3_types[424]);
  IFC4X3_types[654] =
      new entity(strings[2166], false, 654, (entity *)IFC4X3_types[958]);
  IFC4X3_types[670] =
      new entity(strings[2167], false, 670, (entity *)IFC4X3_types[299]);
  IFC4X3_types[701] =
      new entity(strings[2168], true, 701, (entity *)IFC4X3_types[974]);
  IFC4X3_types[713] =
      new entity(strings[2169], false, 713, (entity *)IFC4X3_types[806]);
  IFC4X3_types[716] =
      new entity(strings[2170], false, 716, (entity *)IFC4X3_types[205]);
  IFC4X3_types[718] =
      new entity(strings[2171], false, 718, (entity *)IFC4X3_types[958]);
  IFC4X3_types[719] =
      new entity(strings[2172], false, 719, (entity *)IFC4X3_types[365]);
  IFC4X3_types[725] =
      new entity(strings[2173], true, 725, (entity *)IFC4X3_types[806]);
  IFC4X3_types[727] =
      new entity(strings[2174], false, 727, (entity *)IFC4X3_types[1213]);
  IFC4X3_types[741] =
      new entity(strings[2175], false, 741, (entity *)IFC4X3_types[743]);
  IFC4X3_types[755] =
      new entity(strings[2176], false, 755, (entity *)IFC4X3_types[1140]);
  IFC4X3_types[756] =
      new entity(strings[2177], true, 756, (entity *)IFC4X3_types[509]);
  IFC4X3_types[758] =
      new entity(strings[2178], false, 758, (entity *)IFC4X3_types[509]);
  IFC4X3_types[765] =
      new entity(strings[2179], true, 765, (entity *)IFC4X3_types[509]);
  IFC4X3_types[766] =
      new entity(strings[2180], false, 766, (entity *)IFC4X3_types[765]);
  IFC4X3_types[767] =
      new entity(strings[2181], false, 767, (entity *)IFC4X3_types[765]);
  IFC4X3_types[768] =
      new entity(strings[2182], false, 768, (entity *)IFC4X3_types[765]);
  IFC4X3_types[773] =
      new entity(strings[2183], false, 773, (entity *)IFC4X3_types[619]);
  IFC4X3_types[770] =
      new entity(strings[2184], false, 770, (entity *)IFC4X3_types[528]);
  IFC4X3_types[785] =
      new entity(strings[2185], true, 785, (entity *)IFC4X3_types[791]);
  IFC4X3_types[786] =
      new entity(strings[2186], true, 786, (entity *)IFC4X3_types[818]);
  IFC4X3_types[788] =
      new entity(strings[2187], true, 788, (entity *)IFC4X3_types[785]);
  IFC4X3_types[802] =
      new entity(strings[2188], false, 802, (entity *)IFC4X3_types[803]);
  IFC4X3_types[807] =
      new entity(strings[2189], false, 807, (entity *)IFC4X3_types[424]);
  IFC4X3_types[817] =
      new entity(strings[2190], true, 817, (entity *)IFC4X3_types[818]);
  IFC4X3_types[820] =
      new entity(strings[2191], true, 820, (entity *)IFC4X3_types[974]);
  IFC4X3_types[821] =
      new entity(strings[2192], false, 821, (entity *)IFC4X3_types[958]);
  IFC4X3_types[827] =
      new entity(strings[2193], true, 827, (entity *)IFC4X3_types[820]);
  IFC4X3_types[835] =
      new entity(strings[2194], true, 835, (entity *)IFC4X3_types[820]);
  IFC4X3_types[849] =
      new entity(strings[2195], true, 849, (entity *)IFC4X3_types[827]);
  IFC4X3_types[875] =
      new entity(strings[2196], false, 875, (entity *)IFC4X3_types[725]);
  IFC4X3_types[884] =
      new entity(strings[2197], false, 884, (entity *)IFC4X3_types[1209]);
  IFC4X3_types[887] =
      new entity(strings[2198], false, 887, (entity *)IFC4X3_types[786]);
  IFC4X3_types[917] =
      new entity(strings[2199], true, 917, (entity *)IFC4X3_types[974]);
  IFC4X3_types[956] =
      new entity(strings[2200], false, 956, (entity *)IFC4X3_types[958]);
  IFC4X3_types[957] =
      new entity(strings[2201], false, 957, (entity *)IFC4X3_types[958]);
  IFC4X3_types[961] =
      new entity(strings[2202], false, 961, (entity *)IFC4X3_types[983]);
  IFC4X3_types[979] =
      new entity(strings[2203], false, 979, (entity *)IFC4X3_types[875]);
  IFC4X3_types[992] =
      new entity(strings[2204], false, 992, (entity *)IFC4X3_types[786]);
  IFC4X3_types[993] =
      new entity(strings[2205], false, 993, (entity *)IFC4X3_types[786]);
  IFC4X3_types[989] =
      new entity(strings[2206], false, 989, (entity *)IFC4X3_types[509]);
  IFC4X3_types[995] =
      new entity(strings[2207], true, 995, (entity *)IFC4X3_types[509]);
  IFC4X3_types[1011] =
      new entity(strings[2208], false, 1011, (entity *)IFC4X3_types[509]);
  IFC4X3_types[1018] =
      new entity(strings[2209], true, 1018, (entity *)IFC4X3_types[817]);
  IFC4X3_types[1031] =
      new entity(strings[2210], false, 1031, (entity *)IFC4X3_types[1079]);
  IFC4X3_types[1036] =
      new entity(strings[2211], true, 1036, (entity *)IFC4X3_types[509]);
  IFC4X3_types[1093] =
      new entity(strings[2212], false, 1093, (entity *)IFC4X3_types[1100]);
  IFC4X3_types[1095] =
      new entity(strings[2213], false, 1095, (entity *)IFC4X3_types[1100]);
  IFC4X3_types[1096] =
      new entity(strings[2214], false, 1096, (entity *)IFC4X3_types[1100]);
  IFC4X3_types[1097] =
      new entity(strings[2215], false, 1097, (entity *)IFC4X3_types[1096]);
  IFC4X3_types[1098] =
      new entity(strings[2216], false, 1098, (entity *)IFC4X3_types[1100]);
  IFC4X3_types[1099] =
      new entity(strings[2217], false, 1099, (entity *)IFC4X3_types[1098]);
  IFC4X3_types[1122] =
      new entity(strings[2218], false, 1122, (entity *)IFC4X3_types[365]);
  IFC4X3_types[1123] =
      new entity(strings[2219], true, 1123, (entity *)IFC4X3_types[509]);
  IFC4X3_types[1137] =
      new entity(strings[2220], false, 1137, (entity *)IFC4X3_types[1138]);
  IFC4X3_types[1141] =
      new entity(strings[2221], true, 1141, (entity *)IFC4X3_types[1036]);
  IFC4X3_types[1142] =
      new entity(strings[2222], false, 1142, (entity *)IFC4X3_types[1036]);
  IFC4X3_types[1143] =
      new entity(strings[2223], false, 1143, (entity *)IFC4X3_types[1142]);
  IFC4X3_types[1144] =
      new entity(strings[2224], true, 1144, (entity *)IFC4X3_types[1123]);
  IFC4X3_types[1236] =
      new entity(strings[2225], false, 1236, (entity *)IFC4X3_types[725]);
  IFC4X3_types[1177] =
      new entity(strings[2226], true, 1177, (entity *)IFC4X3_types[509]);
  IFC4X3_types[1183] =
      new entity(strings[2227], false, 1183, (entity *)IFC4X3_types[509]);
  IFC4X3_types[1184] =
      new entity(strings[2228], false, 1184, (entity *)IFC4X3_types[1183]);
  IFC4X3_types[1187] =
      new entity(strings[2229], false, 1187, (entity *)IFC4X3_types[788]);
  IFC4X3_types[1230] =
      new entity(strings[2230], false, 1230, (entity *)IFC4X3_types[725]);
  IFC4X3_types[1240] =
      new entity(strings[2231], false, 1240, (entity *)IFC4X3_types[701]);
  IFC4X3_types[1241] =
      new entity(strings[2232], true, 1241, (entity *)IFC4X3_types[1240]);
  IFC4X3_types[1242] =
      new entity(strings[2233], false, 1242, (entity *)IFC4X3_types[1240]);
  IFC4X3_types[1243] =
      new entity(strings[2234], true, 1243, (entity *)IFC4X3_types[1240]);
  IFC4X3_types[1254] =
      new entity(strings[2235], false, 1254, (entity *)IFC4X3_types[725]);
  IFC4X3_types[1260] =
      new entity(strings[2236], false, 1260, (entity *)IFC4X3_types[509]);
  IFC4X3_types[1266] =
      new entity(strings[2237], false, 1266, (entity *)IFC4X3_types[619]);
  IFC4X3_types[1310] =
      new entity(strings[2238], false, 1310, (entity *)IFC4X3_types[725]);
  IFC4X3_types[171] = new select_type(strings[2239], 171,
                                      {IFC4X3_types[169], IFC4X3_types[170]});
  IFC4X3_types[172] = new select_type(strings[2240], 172,
                                      {IFC4X3_types[169], IFC4X3_types[170]});
  IFC4X3_types[246] = new select_type(strings[2241], 246,
                                      {IFC4X3_types[245], IFC4X3_types[508]});
  IFC4X3_types[297] = new select_type(strings[2242], 297,
                                      {IFC4X3_types[701], IFC4X3_types[820]});
  IFC4X3_types[334] = new select_type(strings[2243], 334,
                                      {IFC4X3_types[331], IFC4X3_types[333]});
  IFC4X3_types[529] = new select_type(strings[2244], 529,
                                      {IFC4X3_types[778], IFC4X3_types[1260]});
  IFC4X3_types[657] = new select_type(
      strings[2245], 657,
      {IFC4X3_types[42],   IFC4X3_types[59],   IFC4X3_types[189],
       IFC4X3_types[227],  IFC4X3_types[253],  IFC4X3_types[303],
       IFC4X3_types[374],  IFC4X3_types[585],  IFC4X3_types[623],
       IFC4X3_types[635],  IFC4X3_types[697],  IFC4X3_types[698],
       IFC4X3_types[699],  IFC4X3_types[726],  IFC4X3_types[761],
       IFC4X3_types[778],  IFC4X3_types[779],  IFC4X3_types[780],
       IFC4X3_types[870],  IFC4X3_types[1035], IFC4X3_types[1203],
       IFC4X3_types[1206], IFC4X3_types[1279]});
  IFC4X3_types[769] = new select_type(strings[2246], 769,
                                      {IFC4X3_types[765], IFC4X3_types[1267]});
  IFC4X3_types[804] = new select_type(strings[2247], 804,
                                      {IFC4X3_types[802], IFC4X3_types[954]});
  IFC4X3_types[829] = new type_declaration(
      strings[2248], 829,
      new aggregation_type(aggregation_type::set_type, 1, -1,
                           new named_type(IFC4X3_types[827])));
  IFC4X3_types[959] =
      new select_type(strings[2249], 959,
                      {IFC4X3_types[7], IFC4X3_types[50], IFC4X3_types[52],
                       IFC4X3_types[213], IFC4X3_types[228], IFC4X3_types[233],
                       IFC4X3_types[425], IFC4X3_types[429], IFC4X3_types[641],
                       IFC4X3_types[717], IFC4X3_types[738], IFC4X3_types[739],
                       IFC4X3_types[743], IFC4X3_types[806], IFC4X3_types[818],
                       IFC4X3_types[1006], IFC4X3_types[1209]});
  IFC4X3_types[1182] = new select_type(strings[2250], 1182,
                                       {IFC4X3_types[428], IFC4X3_types[788]});
  IFC4X3_types[1255] = new select_type(
      strings[2251], 1255,
      {IFC4X3_types[298], IFC4X3_types[657], IFC4X3_types[1021]});
  IFC4X3_types[16] =
      new entity(strings[2252], false, 16, (entity *)IFC4X3_types[440]);
  IFC4X3_types[47] =
      new entity(strings[2253], false, 47, (entity *)IFC4X3_types[509]);
  IFC4X3_types[63] =
      new entity(strings[2254], false, 63, (entity *)IFC4X3_types[725]);
  IFC4X3_types[67] =
      new entity(strings[2255], false, 67, (entity *)IFC4X3_types[756]);
  IFC4X3_types[69] =
      new entity(strings[2256], false, 69, (entity *)IFC4X3_types[756]);
  IFC4X3_types[70] =
      new entity(strings[2257], false, 70, (entity *)IFC4X3_types[756]);
  IFC4X3_types[71] =
      new entity(strings[2258], false, 71, (entity *)IFC4X3_types[756]);
  IFC4X3_types[91] =
      new entity(strings[2259], false, 91, (entity *)IFC4X3_types[509]);
  IFC4X3_types[100] =
      new entity(strings[2260], true, 100, (entity *)IFC4X3_types[1123]);
  IFC4X3_types[101] =
      new entity(strings[2261], false, 101, (entity *)IFC4X3_types[509]);
  IFC4X3_types[103] =
      new entity(strings[2262], false, 103, (entity *)IFC4X3_types[528]);
  IFC4X3_types[266] =
      new entity(strings[2263], false, 266, (entity *)IFC4X3_types[725]);
  IFC4X3_types[147] =
      new entity(strings[2264], false, 147, (entity *)IFC4X3_types[765]);
  IFC4X3_types[148] =
      new entity(strings[2265], true, 148, (entity *)IFC4X3_types[509]);
  IFC4X3_types[149] =
      new entity(strings[2266], false, 149, (entity *)IFC4X3_types[148]);
  IFC4X3_types[150] =
      new entity(strings[2267], false, 150, (entity *)IFC4X3_types[148]);
  IFC4X3_types[151] =
      new entity(strings[2268], true, 151, (entity *)IFC4X3_types[509]);
  IFC4X3_types[152] =
      new entity(strings[2269], false, 152, (entity *)IFC4X3_types[151]);
  IFC4X3_types[153] =
      new entity(strings[2270], false, 153, (entity *)IFC4X3_types[152]);
  IFC4X3_types[154] =
      new entity(strings[2271], false, 154, (entity *)IFC4X3_types[151]);
  IFC4X3_types[155] =
      new entity(strings[2272], false, 155, (entity *)IFC4X3_types[154]);
  IFC4X3_types[166] =
      new entity(strings[2273], false, 166, (entity *)IFC4X3_types[725]);
  IFC4X3_types[173] =
      new entity(strings[2274], false, 173, (entity *)IFC4X3_types[205]);
  IFC4X3_types[180] =
      new entity(strings[2275], false, 180, (entity *)IFC4X3_types[182]);
  IFC4X3_types[190] =
      new entity(strings[2276], false, 190, (entity *)IFC4X3_types[817]);
  IFC4X3_types[195] =
      new entity(strings[2277], false, 195, (entity *)IFC4X3_types[995]);
  IFC4X3_types[225] =
      new entity(strings[2278], true, 225, (entity *)IFC4X3_types[1243]);
  IFC4X3_types[226] =
      new entity(strings[2279], true, 226, (entity *)IFC4X3_types[701]);
  IFC4X3_types[261] =
      new entity(strings[2280], false, 261, (entity *)IFC4X3_types[225]);
  IFC4X3_types[263] =
      new entity(strings[2281], true, 263, (entity *)IFC4X3_types[509]);
  IFC4X3_types[265] =
      new entity(strings[2282], false, 265, (entity *)IFC4X3_types[1036]);
  IFC4X3_types[272] =
      new entity(strings[2283], true, 272, (entity *)IFC4X3_types[509]);
  IFC4X3_types[273] =
      new entity(strings[2284], false, 273, (entity *)IFC4X3_types[100]);
  IFC4X3_types[274] =
      new entity(strings[2285], false, 274, (entity *)IFC4X3_types[100]);
  IFC4X3_types[280] =
      new entity(strings[2286], false, 280, (entity *)IFC4X3_types[995]);
  IFC4X3_types[306] =
      new entity(strings[2287], false, 306, (entity *)IFC4X3_types[509]);
  IFC4X3_types[308] =
      new entity(strings[2288], true, 308, (entity *)IFC4X3_types[1141]);
  IFC4X3_types[367] =
      new entity(strings[2289], false, 367, (entity *)IFC4X3_types[619]);
  IFC4X3_types[403] =
      new entity(strings[2290], false, 403, (entity *)IFC4X3_types[849]);
  IFC4X3_types[404] =
      new entity(strings[2291], true, 404, (entity *)IFC4X3_types[1242]);
  IFC4X3_types[396] =
      new entity(strings[2292], true, 396, (entity *)IFC4X3_types[1123]);
  IFC4X3_types[406] =
      new entity(strings[2293], false, 406, (entity *)IFC4X3_types[725]);
  IFC4X3_types[422] =
      new entity(strings[2294], false, 422, (entity *)IFC4X3_types[1241]);
  IFC4X3_types[434] =
      new entity(strings[2295], false, 434, (entity *)IFC4X3_types[1141]);
  IFC4X3_types[435] =
      new entity(strings[2296], false, 435, (entity *)IFC4X3_types[434]);
  IFC4X3_types[437] =
      new entity(strings[2297], false, 437, (entity *)IFC4X3_types[509]);
  IFC4X3_types[459] =
      new entity(strings[2298], false, 459, (entity *)IFC4X3_types[509]);
  IFC4X3_types[460] =
      new entity(strings[2299], false, 460, (entity *)IFC4X3_types[509]);
  IFC4X3_types[468] =
      new entity(strings[2300], false, 468, (entity *)IFC4X3_types[308]);
  IFC4X3_types[499] =
      new entity(strings[2301], false, 499, (entity *)IFC4X3_types[404]);
  IFC4X3_types[501] =
      new entity(strings[2302], false, 501, (entity *)IFC4X3_types[499]);
  IFC4X3_types[504] =
      new entity(strings[2303], false, 504, (entity *)IFC4X3_types[404]);
  IFC4X3_types[506] =
      new entity(strings[2304], false, 506, (entity *)IFC4X3_types[511]);
  IFC4X3_types[565] =
      new entity(strings[2305], false, 565, (entity *)IFC4X3_types[725]);
  IFC4X3_types[546] =
      new entity(strings[2306], false, 546, (entity *)IFC4X3_types[1177]);
  IFC4X3_types[547] =
      new entity(strings[2307], false, 547, (entity *)IFC4X3_types[546]);
  IFC4X3_types[548] =
      new entity(strings[2308], false, 548, (entity *)IFC4X3_types[549]);
  IFC4X3_types[620] =
      new entity(strings[2309], false, 620, (entity *)IFC4X3_types[725]);
  IFC4X3_types[576] =
      new entity(strings[2310], false, 576, (entity *)IFC4X3_types[225]);
  IFC4X3_types[603] =
      new entity(strings[2311], false, 603, (entity *)IFC4X3_types[272]);
  IFC4X3_types[626] =
      new entity(strings[2312], true, 626, (entity *)IFC4X3_types[1036]);
  IFC4X3_types[700] =
      new entity(strings[2313], true, 700, (entity *)IFC4X3_types[701]);
  IFC4X3_types[709] =
      new entity(strings[2314], true, 709, (entity *)IFC4X3_types[272]);
  IFC4X3_types[710] =
      new entity(strings[2315], false, 710, (entity *)IFC4X3_types[709]);
  IFC4X3_types[711] =
      new entity(strings[2316], false, 711, (entity *)IFC4X3_types[709]);
  IFC4X3_types[712] =
      new entity(strings[2317], false, 712, (entity *)IFC4X3_types[709]);
  IFC4X3_types[731] =
      new entity(strings[2318], false, 731, (entity *)IFC4X3_types[272]);
  IFC4X3_types[757] =
      new entity(strings[2319], false, 757, (entity *)IFC4X3_types[758]);
  IFC4X3_types[760] =
      new entity(strings[2320], false, 760, (entity *)IFC4X3_types[396]);
  IFC4X3_types[774] =
      new entity(strings[2321], false, 774, (entity *)IFC4X3_types[272]);
  IFC4X3_types[783] =
      new entity(strings[2322], true, 783, (entity *)IFC4X3_types[785]);
  IFC4X3_types[784] =
      new entity(strings[2323], true, 784, (entity *)IFC4X3_types[785]);
  IFC4X3_types[787] =
      new entity(strings[2324], true, 787, (entity *)IFC4X3_types[827]);
  IFC4X3_types[797] =
      new entity(strings[2325], false, 797, (entity *)IFC4X3_types[1241]);
  IFC4X3_types[799] =
      new entity(strings[2326], true, 799, (entity *)IFC4X3_types[700]);
  IFC4X3_types[801] =
      new entity(strings[2327], true, 801, (entity *)IFC4X3_types[700]);
  IFC4X3_types[809] =
      new entity(strings[2328], false, 809, (entity *)IFC4X3_types[226]);
  IFC4X3_types[814] =
      new entity(strings[2329], false, 814, (entity *)IFC4X3_types[226]);
  IFC4X3_types[819] =
      new entity(strings[2330], false, 819, (entity *)IFC4X3_types[1018]);
  IFC4X3_types[822] =
      new entity(strings[2331], false, 822, (entity *)IFC4X3_types[1018]);
  IFC4X3_types[824] =
      new entity(strings[2332], false, 824, (entity *)IFC4X3_types[1018]);
  IFC4X3_types[825] =
      new entity(strings[2333], false, 825, (entity *)IFC4X3_types[1018]);
  IFC4X3_types[826] =
      new entity(strings[2334], false, 826, (entity *)IFC4X3_types[827]);
  IFC4X3_types[830] =
      new entity(strings[2335], false, 830, (entity *)IFC4X3_types[835]);
  IFC4X3_types[832] =
      new entity(strings[2336], false, 832, (entity *)IFC4X3_types[1018]);
  IFC4X3_types[833] =
      new entity(strings[2337], false, 833, (entity *)IFC4X3_types[1018]);
  IFC4X3_types[834] =
      new entity(strings[2338], true, 834, (entity *)IFC4X3_types[835]);
  IFC4X3_types[874] =
      new entity(strings[2339], false, 874, (entity *)IFC4X3_types[875]);
  IFC4X3_types[876] =
      new entity(strings[2340], false, 876, (entity *)IFC4X3_types[263]);
  IFC4X3_types[877] =
      new entity(strings[2341], false, 877, (entity *)IFC4X3_types[100]);
  IFC4X3_types[888] =
      new entity(strings[2342], false, 888, (entity *)IFC4X3_types[787]);
  IFC4X3_types[901] =
      new entity(strings[2343], true, 901, (entity *)IFC4X3_types[917]);
  IFC4X3_types[902] =
      new entity(strings[2344], false, 902, (entity *)IFC4X3_types[901]);
  IFC4X3_types[903] =
      new entity(strings[2345], false, 903, (entity *)IFC4X3_types[901]);
  IFC4X3_types[904] =
      new entity(strings[2346], false, 904, (entity *)IFC4X3_types[901]);
  IFC4X3_types[905] =
      new entity(strings[2347], false, 905, (entity *)IFC4X3_types[904]);
  IFC4X3_types[906] =
      new entity(strings[2348], false, 906, (entity *)IFC4X3_types[901]);
  IFC4X3_types[907] =
      new entity(strings[2349], false, 907, (entity *)IFC4X3_types[901]);
  IFC4X3_types[908] =
      new entity(strings[2350], false, 908, (entity *)IFC4X3_types[901]);
  IFC4X3_types[909] =
      new entity(strings[2351], true, 909, (entity *)IFC4X3_types[917]);
  IFC4X3_types[910] =
      new entity(strings[2352], false, 910, (entity *)IFC4X3_types[909]);
  IFC4X3_types[911] =
      new entity(strings[2353], false, 911, (entity *)IFC4X3_types[909]);
  IFC4X3_types[912] =
      new entity(strings[2354], false, 912, (entity *)IFC4X3_types[909]);
  IFC4X3_types[913] =
      new entity(strings[2355], false, 913, (entity *)IFC4X3_types[909]);
  IFC4X3_types[914] =
      new entity(strings[2356], false, 914, (entity *)IFC4X3_types[909]);
  IFC4X3_types[915] =
      new entity(strings[2357], false, 915, (entity *)IFC4X3_types[909]);
  IFC4X3_types[916] =
      new entity(strings[2358], false, 916, (entity *)IFC4X3_types[909]);
  IFC4X3_types[918] =
      new entity(strings[2359], true, 918, (entity *)IFC4X3_types[917]);
  IFC4X3_types[919] =
      new entity(strings[2360], false, 919, (entity *)IFC4X3_types[918]);
  IFC4X3_types[920] =
      new entity(strings[2361], false, 920, (entity *)IFC4X3_types[919]);
  IFC4X3_types[922] =
      new entity(strings[2362], false, 922, (entity *)IFC4X3_types[918]);
  IFC4X3_types[921] =
      new entity(strings[2363], false, 921, (entity *)IFC4X3_types[918]);
  IFC4X3_types[923] =
      new entity(strings[2364], false, 923, (entity *)IFC4X3_types[918]);
  IFC4X3_types[924] =
      new entity(strings[2365], false, 924, (entity *)IFC4X3_types[918]);
  IFC4X3_types[925] =
      new entity(strings[2366], false, 925, (entity *)IFC4X3_types[924]);
  IFC4X3_types[926] =
      new entity(strings[2367], false, 926, (entity *)IFC4X3_types[919]);
  IFC4X3_types[927] =
      new entity(strings[2368], false, 927, (entity *)IFC4X3_types[918]);
  IFC4X3_types[928] =
      new entity(strings[2369], false, 928, (entity *)IFC4X3_types[918]);
  IFC4X3_types[929] =
      new entity(strings[2370], false, 929, (entity *)IFC4X3_types[918]);
  IFC4X3_types[930] =
      new entity(strings[2371], false, 930, (entity *)IFC4X3_types[917]);
  IFC4X3_types[931] =
      new entity(strings[2372], true, 931, (entity *)IFC4X3_types[917]);
  IFC4X3_types[932] =
      new entity(strings[2373], true, 932, (entity *)IFC4X3_types[917]);
  IFC4X3_types[933] =
      new entity(strings[2374], false, 933, (entity *)IFC4X3_types[932]);
  IFC4X3_types[934] =
      new entity(strings[2375], false, 934, (entity *)IFC4X3_types[932]);
  IFC4X3_types[935] =
      new entity(strings[2376], false, 935, (entity *)IFC4X3_types[932]);
  IFC4X3_types[936] =
      new entity(strings[2377], false, 936, (entity *)IFC4X3_types[932]);
  IFC4X3_types[937] =
      new entity(strings[2378], false, 937, (entity *)IFC4X3_types[918]);
  IFC4X3_types[938] =
      new entity(strings[2379], false, 938, (entity *)IFC4X3_types[918]);
  IFC4X3_types[939] =
      new entity(strings[2380], false, 939, (entity *)IFC4X3_types[918]);
  IFC4X3_types[940] =
      new entity(strings[2381], false, 940, (entity *)IFC4X3_types[931]);
  IFC4X3_types[941] =
      new entity(strings[2382], false, 941, (entity *)IFC4X3_types[918]);
  IFC4X3_types[942] =
      new entity(strings[2383], false, 942, (entity *)IFC4X3_types[931]);
  IFC4X3_types[943] =
      new entity(strings[2384], false, 943, (entity *)IFC4X3_types[918]);
  IFC4X3_types[944] =
      new entity(strings[2385], false, 944, (entity *)IFC4X3_types[918]);
  IFC4X3_types[945] =
      new entity(strings[2386], false, 945, (entity *)IFC4X3_types[918]);
  IFC4X3_types[946] =
      new entity(strings[2387], false, 946, (entity *)IFC4X3_types[918]);
  IFC4X3_types[947] =
      new entity(strings[2388], false, 947, (entity *)IFC4X3_types[946]);
  IFC4X3_types[948] =
      new entity(strings[2389], false, 948, (entity *)IFC4X3_types[947]);
  IFC4X3_types[949] =
      new entity(strings[2390], false, 949, (entity *)IFC4X3_types[931]);
  IFC4X3_types[950] =
      new entity(strings[2391], false, 950, (entity *)IFC4X3_types[195]);
  IFC4X3_types[955] =
      new entity(strings[2392], true, 955, (entity *)IFC4X3_types[700]);
  IFC4X3_types[962] =
      new entity(strings[2393], false, 962, (entity *)IFC4X3_types[1141]);
  IFC4X3_types[963] =
      new entity(strings[2394], false, 963, (entity *)IFC4X3_types[962]);
  IFC4X3_types[964] =
      new entity(strings[2395], false, 964, (entity *)IFC4X3_types[263]);
  IFC4X3_types[965] =
      new entity(strings[2396], false, 965, (entity *)IFC4X3_types[263]);
  IFC4X3_types[987] =
      new entity(strings[2397], true, 987, (entity *)IFC4X3_types[1036]);
  IFC4X3_types[988] =
      new entity(strings[2398], false, 988, (entity *)IFC4X3_types[987]);
  IFC4X3_types[990] =
      new entity(strings[2399], false, 990, (entity *)IFC4X3_types[1123]);
  IFC4X3_types[1019] =
      new entity(strings[2400], false, 1019, (entity *)IFC4X3_types[834]);
  IFC4X3_types[1049] =
      new entity(strings[2401], true, 1049, (entity *)IFC4X3_types[801]);
  IFC4X3_types[1050] =
      new entity(strings[2402], true, 1050, (entity *)IFC4X3_types[1242]);
  IFC4X3_types[1052] =
      new entity(strings[2403], true, 1052, (entity *)IFC4X3_types[1049]);
  IFC4X3_types[1053] =
      new entity(strings[2404], true, 1053, (entity *)IFC4X3_types[1050]);
  IFC4X3_types[1054] =
      new entity(strings[2405], false, 1054, (entity *)IFC4X3_types[1049]);
  IFC4X3_types[1055] =
      new entity(strings[2406], false, 1055, (entity *)IFC4X3_types[1050]);
  IFC4X3_types[1061] =
      new entity(strings[2407], false, 1061, (entity *)IFC4X3_types[263]);
  IFC4X3_types[1062] =
      new entity(strings[2408], false, 1062, (entity *)IFC4X3_types[396]);
  IFC4X3_types[1063] =
      new entity(strings[2409], true, 1063, (entity *)IFC4X3_types[272]);
  IFC4X3_types[1075] =
      new entity(strings[2410], true, 1075, (entity *)IFC4X3_types[801]);
  IFC4X3_types[1087] =
      new entity(strings[2411], true, 1087, (entity *)IFC4X3_types[801]);
  IFC4X3_types[1102] =
      new entity(strings[2412], true, 1102, (entity *)IFC4X3_types[1087]);
  IFC4X3_types[1107] =
      new entity(strings[2413], true, 1107, (entity *)IFC4X3_types[1075]);
  IFC4X3_types[1112] =
      new entity(strings[2414], false, 1112, (entity *)IFC4X3_types[1102]);
  IFC4X3_types[1114] =
      new entity(strings[2415], false, 1114, (entity *)IFC4X3_types[1112]);
  IFC4X3_types[1115] =
      new entity(strings[2416], false, 1115, (entity *)IFC4X3_types[1107]);
  IFC4X3_types[1120] =
      new entity(strings[2417], false, 1120, (entity *)IFC4X3_types[225]);
  IFC4X3_types[1124] =
      new entity(strings[2418], false, 1124, (entity *)IFC4X3_types[272]);
  IFC4X3_types[1125] =
      new entity(strings[2419], false, 1125, (entity *)IFC4X3_types[308]);
  IFC4X3_types[1128] =
      new entity(strings[2420], false, 1128, (entity *)IFC4X3_types[1144]);
  IFC4X3_types[1129] =
      new entity(strings[2421], false, 1129, (entity *)IFC4X3_types[1144]);
  IFC4X3_types[1150] =
      new entity(strings[2422], false, 1150, (entity *)IFC4X3_types[499]);
  IFC4X3_types[1158] =
      new entity(strings[2423], false, 1158, (entity *)IFC4X3_types[799]);
  IFC4X3_types[1162] =
      new entity(strings[2424], false, 1162, (entity *)IFC4X3_types[1241]);
  IFC4X3_types[1176] =
      new entity(strings[2425], true, 1176, (entity *)IFC4X3_types[1177]);
  IFC4X3_types[1204] =
      new entity(strings[2426], false, 1204, (entity *)IFC4X3_types[1063]);
  IFC4X3_types[1215] =
      new entity(strings[2427], false, 1215, (entity *)IFC4X3_types[396]);
  IFC4X3_types[1226] =
      new entity(strings[2428], true, 1226, (entity *)IFC4X3_types[404]);
  IFC4X3_types[1231] =
      new entity(strings[2429], false, 1231, (entity *)IFC4X3_types[1176]);
  IFC4X3_types[1232] =
      new entity(strings[2430], false, 1232, (entity *)IFC4X3_types[1231]);
  IFC4X3_types[1263] =
      new entity(strings[2431], false, 1263, (entity *)IFC4X3_types[1226]);
  IFC4X3_types[1292] =
      new entity(strings[2432], false, 1292, (entity *)IFC4X3_types[787]);
  IFC4X3_types[1295] =
      new entity(strings[2433], false, 1295, (entity *)IFC4X3_types[787]);
  IFC4X3_types[51] = new select_type(
      strings[2434], 51,
      {IFC4X3_types[658], IFC4X3_types[880], IFC4X3_types[1255]});
  IFC4X3_types[68] =
      new select_type(strings[2435], 68, {IFC4X3_types[69], IFC4X3_types[70]});
  IFC4X3_types[89] =
      new select_type(strings[2436], 89,
                      {IFC4X3_types[91], IFC4X3_types[263], IFC4X3_types[528],
                       IFC4X3_types[1036], IFC4X3_types[1176]});
  IFC4X3_types[178] = new select_type(strings[2437], 178,
                                      {IFC4X3_types[182], IFC4X3_types[783]});
  IFC4X3_types[179] = new select_type(strings[2438], 179,
                                      {IFC4X3_types[180], IFC4X3_types[698]});
  IFC4X3_types[264] = new select_type(strings[2439], 264,
                                      {IFC4X3_types[91], IFC4X3_types[263]});
  IFC4X3_types[285] = new select_type(strings[2440], 285,
                                      {IFC4X3_types[282], IFC4X3_types[784]});
  IFC4X3_types[461] = new select_type(strings[2441], 461,
                                      {IFC4X3_types[178], IFC4X3_types[426],
                                       IFC4X3_types[459], IFC4X3_types[460]});
  IFC4X3_types[512] = new select_type(
      strings[2442], 512,
      {IFC4X3_types[272], IFC4X3_types[765], IFC4X3_types[1123]});
  IFC4X3_types[525] = new select_type(strings[2443], 525,
                                      {IFC4X3_types[306], IFC4X3_types[1276]});
  IFC4X3_types[669] = new select_type(strings[2444], 669,
                                      {IFC4X3_types[50], IFC4X3_types[658],
                                       IFC4X3_types[880], IFC4X3_types[1152],
                                       IFC4X3_types[1209], IFC4X3_types[1255]});
  IFC4X3_types[800] = new select_type(strings[2445], 800,
                                      {IFC4X3_types[799], IFC4X3_types[1241]});
  IFC4X3_types[805] = new select_type(strings[2446], 805,
                                      {IFC4X3_types[801], IFC4X3_types[1242]});
  IFC4X3_types[828] = new select_type(strings[2447], 828,
                                      {IFC4X3_types[827], IFC4X3_types[829]});
  IFC4X3_types[960] = new select_type(strings[2448], 960,
                                      {IFC4X3_types[955], IFC4X3_types[1243]});
  IFC4X3_types[1010] = new select_type(strings[2449], 1010,
                                       {IFC4X3_types[173], IFC4X3_types[716]});
  IFC4X3_types[1037] = new select_type(strings[2450], 1037,
                                       {IFC4X3_types[173], IFC4X3_types[1036]});
  IFC4X3_types[1130] = new select_type(
      strings[2451], 1130,
      {IFC4X3_types[437], IFC4X3_types[440], IFC4X3_types[1123]});
  IFC4X3_types[1235] = new select_type(strings[2452], 1235,
                                       {IFC4X3_types[147], IFC4X3_types[726]});
  IFC4X3_types[1261] = new select_type(strings[2453], 1261,
                                       {IFC4X3_types[306], IFC4X3_types[1260]});
  IFC4X3_types[6] =
      new entity(strings[2454], false, 6, (entity *)IFC4X3_types[700]);
  IFC4X3_types[14] =
      new entity(strings[2455], false, 14, (entity *)IFC4X3_types[626]);
  IFC4X3_types[15] =
      new entity(strings[2456], false, 15, (entity *)IFC4X3_types[14]);
  IFC4X3_types[46] =
      new entity(strings[2457], false, 46, (entity *)IFC4X3_types[801]);
  IFC4X3_types[111] =
      new entity(strings[2458], true, 111, (entity *)IFC4X3_types[100]);
  IFC4X3_types[113] =
      new entity(strings[2459], false, 113, (entity *)IFC4X3_types[111]);
  IFC4X3_types[83] =
      new entity(strings[2460], false, 83, (entity *)IFC4X3_types[263]);
  IFC4X3_types[88] =
      new entity(strings[2461], false, 88, (entity *)IFC4X3_types[91]);
  IFC4X3_types[99] =
      new entity(strings[2462], true, 99, (entity *)IFC4X3_types[272]);
  IFC4X3_types[121] =
      new entity(strings[2463], false, 121, (entity *)IFC4X3_types[1052]);
  IFC4X3_types[125] =
      new entity(strings[2464], false, 125, (entity *)IFC4X3_types[404]);
  IFC4X3_types[162] =
      new entity(strings[2465], false, 162, (entity *)IFC4X3_types[125]);
  IFC4X3_types[165] =
      new entity(strings[2466], false, 165, (entity *)IFC4X3_types[166]);
  IFC4X3_types[168] =
      new entity(strings[2467], false, 168, (entity *)IFC4X3_types[404]);
  IFC4X3_types[174] =
      new entity(strings[2468], false, 174, (entity *)IFC4X3_types[1063]);
  IFC4X3_types[184] =
      new entity(strings[2469], false, 184, (entity *)IFC4X3_types[125]);
  IFC4X3_types[191] =
      new entity(strings[2470], false, 191, (entity *)IFC4X3_types[834]);
  IFC4X3_types[193] =
      new entity(strings[2471], false, 193, (entity *)IFC4X3_types[99]);
  IFC4X3_types[194] =
      new entity(strings[2472], false, 194, (entity *)IFC4X3_types[193]);
  IFC4X3_types[204] =
      new entity(strings[2473], true, 204, (entity *)IFC4X3_types[272]);
  IFC4X3_types[216] =
      new entity(strings[2474], false, 216, (entity *)IFC4X3_types[225]);
  IFC4X3_types[219] =
      new entity(strings[2475], false, 219, (entity *)IFC4X3_types[225]);
  IFC4X3_types[222] =
      new entity(strings[2476], false, 222, (entity *)IFC4X3_types[225]);
  IFC4X3_types[224] =
      new entity(strings[2477], true, 224, (entity *)IFC4X3_types[955]);
  IFC4X3_types[229] =
      new entity(strings[2478], true, 229, (entity *)IFC4X3_types[700]);
  IFC4X3_types[247] =
      new entity(strings[2479], false, 247, (entity *)IFC4X3_types[1063]);
  IFC4X3_types[248] =
      new entity(strings[2480], false, 248, (entity *)IFC4X3_types[229]);
  IFC4X3_types[250] =
      new entity(strings[2481], false, 250, (entity *)IFC4X3_types[229]);
  IFC4X3_types[255] =
      new entity(strings[2482], false, 255, (entity *)IFC4X3_types[125]);
  IFC4X3_types[258] =
      new entity(strings[2483], false, 258, (entity *)IFC4X3_types[125]);
  IFC4X3_types[260] =
      new entity(strings[2484], false, 260, (entity *)IFC4X3_types[224]);
  IFC4X3_types[269] =
      new entity(strings[2485], false, 269, (entity *)IFC4X3_types[125]);
  IFC4X3_types[286] =
      new entity(strings[2486], false, 286, (entity *)IFC4X3_types[396]);
  IFC4X3_types[296] =
      new entity(strings[2487], false, 296, (entity *)IFC4X3_types[125]);
  IFC4X3_types[309] =
      new entity(strings[2488], false, 309, (entity *)IFC4X3_types[468]);
  IFC4X3_types[323] =
      new entity(strings[2489], false, 323, (entity *)IFC4X3_types[404]);
  IFC4X3_types[325] =
      new entity(strings[2490], true, 325, (entity *)IFC4X3_types[323]);
  IFC4X3_types[337] =
      new entity(strings[2491], false, 337, (entity *)IFC4X3_types[787]);
  IFC4X3_types[340] =
      new entity(strings[2492], false, 340, (entity *)IFC4X3_types[787]);
  IFC4X3_types[343] =
      new entity(strings[2493], false, 343, (entity *)IFC4X3_types[125]);
  IFC4X3_types[347] =
      new entity(strings[2494], false, 347, (entity *)IFC4X3_types[783]);
  IFC4X3_types[348] =
      new entity(strings[2495], false, 348, (entity *)IFC4X3_types[784]);
  IFC4X3_types[395] =
      new entity(strings[2496], true, 395, (entity *)IFC4X3_types[801]);
  IFC4X3_types[397] =
      new entity(strings[2497], false, 397, (entity *)IFC4X3_types[395]);
  IFC4X3_types[398] =
      new entity(strings[2498], false, 398, (entity *)IFC4X3_types[404]);
  IFC4X3_types[400] =
      new entity(strings[2499], true, 400, (entity *)IFC4X3_types[395]);
  IFC4X3_types[401] =
      new entity(strings[2500], true, 401, (entity *)IFC4X3_types[404]);
  IFC4X3_types[405] =
      new entity(strings[2501], false, 405, (entity *)IFC4X3_types[204]);
  IFC4X3_types[408] =
      new entity(strings[2502], true, 408, (entity *)IFC4X3_types[325]);
  IFC4X3_types[411] =
      new entity(strings[2503], false, 411, (entity *)IFC4X3_types[408]);
  IFC4X3_types[414] =
      new entity(strings[2504], false, 414, (entity *)IFC4X3_types[408]);
  IFC4X3_types[417] =
      new entity(strings[2505], false, 417, (entity *)IFC4X3_types[408]);
  IFC4X3_types[419] =
      new entity(strings[2506], false, 419, (entity *)IFC4X3_types[799]);
  IFC4X3_types[433] =
      new entity(strings[2507], true, 433, (entity *)IFC4X3_types[1049]);
  IFC4X3_types[441] =
      new entity(strings[2508], false, 441, (entity *)IFC4X3_types[626]);
  IFC4X3_types[442] =
      new entity(strings[2509], false, 442, (entity *)IFC4X3_types[441]);
  IFC4X3_types[443] =
      new entity(strings[2510], false, 443, (entity *)IFC4X3_types[1052]);
  IFC4X3_types[444] =
      new entity(strings[2511], true, 444, (entity *)IFC4X3_types[1052]);
  IFC4X3_types[445] =
      new entity(strings[2512], false, 445, (entity *)IFC4X3_types[444]);
  IFC4X3_types[452] =
      new entity(strings[2513], false, 452, (entity *)IFC4X3_types[400]);
  IFC4X3_types[453] =
      new entity(strings[2514], false, 453, (entity *)IFC4X3_types[401]);
  IFC4X3_types[455] =
      new entity(strings[2515], true, 455, (entity *)IFC4X3_types[395]);
  IFC4X3_types[456] =
      new entity(strings[2516], true, 456, (entity *)IFC4X3_types[455]);
  IFC4X3_types[457] =
      new entity(strings[2517], true, 457, (entity *)IFC4X3_types[455]);
  IFC4X3_types[470] =
      new entity(strings[2518], true, 470, (entity *)IFC4X3_types[325]);
  IFC4X3_types[473] =
      new entity(strings[2519], true, 473, (entity *)IFC4X3_types[325]);
  IFC4X3_types[478] =
      new entity(strings[2520], false, 478, (entity *)IFC4X3_types[470]);
  IFC4X3_types[481] =
      new entity(strings[2521], true, 481, (entity *)IFC4X3_types[325]);
  IFC4X3_types[483] =
      new entity(strings[2522], true, 483, (entity *)IFC4X3_types[325]);
  IFC4X3_types[485] =
      new entity(strings[2523], true, 485, (entity *)IFC4X3_types[325]);
  IFC4X3_types[487] =
      new entity(strings[2524], true, 487, (entity *)IFC4X3_types[325]);
  IFC4X3_types[489] =
      new entity(strings[2525], true, 489, (entity *)IFC4X3_types[325]);
  IFC4X3_types[494] =
      new entity(strings[2526], false, 494, (entity *)IFC4X3_types[125]);
  IFC4X3_types[498] =
      new entity(strings[2527], false, 498, (entity *)IFC4X3_types[395]);
  IFC4X3_types[500] =
      new entity(strings[2528], false, 500, (entity *)IFC4X3_types[498]);
  IFC4X3_types[503] =
      new entity(strings[2529], false, 503, (entity *)IFC4X3_types[395]);
  IFC4X3_types[516] =
      new entity(strings[2530], true, 516, (entity *)IFC4X3_types[395]);
  IFC4X3_types[517] =
      new entity(strings[2531], false, 517, (entity *)IFC4X3_types[516]);
  IFC4X3_types[521] =
      new entity(strings[2532], false, 521, (entity *)IFC4X3_types[193]);
  IFC4X3_types[527] =
      new entity(strings[2533], false, 527, (entity *)IFC4X3_types[700]);
  IFC4X3_types[531] =
      new entity(strings[2534], false, 531, (entity *)IFC4X3_types[408]);
  IFC4X3_types[536] =
      new entity(strings[2535], false, 536, (entity *)IFC4X3_types[408]);
  IFC4X3_types[541] =
      new entity(strings[2536], false, 541, (entity *)IFC4X3_types[400]);
  IFC4X3_types[542] =
      new entity(strings[2537], false, 542, (entity *)IFC4X3_types[401]);
  IFC4X3_types[545] =
      new entity(strings[2538], false, 545, (entity *)IFC4X3_types[99]);
  IFC4X3_types[555] =
      new entity(strings[2539], false, 555, (entity *)IFC4X3_types[489]);
  IFC4X3_types[559] =
      new entity(strings[2540], false, 559, (entity *)IFC4X3_types[1124]);
  IFC4X3_types[560] =
      new entity(strings[2541], false, 560, (entity *)IFC4X3_types[527]);
  IFC4X3_types[568] =
      new entity(strings[2542], false, 568, (entity *)IFC4X3_types[473]);
  IFC4X3_types[571] =
      new entity(strings[2543], false, 571, (entity *)IFC4X3_types[125]);
  IFC4X3_types[575] =
      new entity(strings[2544], false, 575, (entity *)IFC4X3_types[224]);
  IFC4X3_types[580] =
      new entity(strings[2545], false, 580, (entity *)IFC4X3_types[487]);
  IFC4X3_types[594] =
      new entity(strings[2546], false, 594, (entity *)IFC4X3_types[487]);
  IFC4X3_types[604] =
      new entity(strings[2547], false, 604, (entity *)IFC4X3_types[801]);
  IFC4X3_types[613] =
      new entity(strings[2548], false, 613, (entity *)IFC4X3_types[487]);
  IFC4X3_types[629] =
      new entity(strings[2549], false, 629, (entity *)IFC4X3_types[443]);
  IFC4X3_types[631] =
      new entity(strings[2550], false, 631, (entity *)IFC4X3_types[444]);
  IFC4X3_types[659] =
      new entity(strings[2551], false, 659, (entity *)IFC4X3_types[400]);
  IFC4X3_types[660] =
      new entity(strings[2552], false, 660, (entity *)IFC4X3_types[401]);
  IFC4X3_types[663] =
      new entity(strings[2553], false, 663, (entity *)IFC4X3_types[487]);
  IFC4X3_types[666] =
      new entity(strings[2554], false, 666, (entity *)IFC4X3_types[125]);
  IFC4X3_types[672] =
      new entity(strings[2555], false, 672, (entity *)IFC4X3_types[487]);
  IFC4X3_types[688] =
      new entity(strings[2556], false, 688, (entity *)IFC4X3_types[125]);
  IFC4X3_types[691] =
      new entity(strings[2557], false, 691, (entity *)IFC4X3_types[408]);
  IFC4X3_types[695] =
      new entity(strings[2558], false, 695, (entity *)IFC4X3_types[125]);
  IFC4X3_types[707] =
      new entity(strings[2559], false, 707, (entity *)IFC4X3_types[6]);
  IFC4X3_types[714] =
      new entity(strings[2560], false, 714, (entity *)IFC4X3_types[457]);
  IFC4X3_types[722] =
      new entity(strings[2561], false, 722, (entity *)IFC4X3_types[487]);
  IFC4X3_types[729] =
      new entity(strings[2562], false, 729, (entity *)IFC4X3_types[125]);
  IFC4X3_types[732] =
      new entity(strings[2563], false, 732, (entity *)IFC4X3_types[229]);
  IFC4X3_types[735] =
      new entity(strings[2564], false, 735, (entity *)IFC4X3_types[787]);
  IFC4X3_types[736] =
      new entity(strings[2565], false, 736, (entity *)IFC4X3_types[229]);
  IFC4X3_types[747] =
      new entity(strings[2566], false, 747, (entity *)IFC4X3_types[296]);
  IFC4X3_types[750] =
      new entity(strings[2567], false, 750, (entity *)IFC4X3_types[473]);
  IFC4X3_types[753] =
      new entity(strings[2568], false, 753, (entity *)IFC4X3_types[483]);
  IFC4X3_types[763] =
      new entity(strings[2569], false, 763, (entity *)IFC4X3_types[125]);
  IFC4X3_types[771] =
      new entity(strings[2570], false, 771, (entity *)IFC4X3_types[1176]);
  IFC4X3_types[772] =
      new entity(strings[2571], false, 772, (entity *)IFC4X3_types[99]);
  IFC4X3_types[775] =
      new entity(strings[2572], true, 775, (entity *)IFC4X3_types[801]);
  IFC4X3_types[776] =
      new entity(strings[2573], true, 776, (entity *)IFC4X3_types[801]);
  IFC4X3_types[796] =
      new entity(strings[2574], false, 796, (entity *)IFC4X3_types[799]);
  IFC4X3_types[815] =
      new entity(strings[2575], false, 815, (entity *)IFC4X3_types[229]);
  IFC4X3_types[812] =
      new entity(strings[2576], false, 812, (entity *)IFC4X3_types[456]);
  IFC4X3_types[840] =
      new entity(strings[2577], false, 840, (entity *)IFC4X3_types[470]);
  IFC4X3_types[843] =
      new entity(strings[2578], false, 843, (entity *)IFC4X3_types[481]);
  IFC4X3_types[858] =
      new entity(strings[2579], false, 858, (entity *)IFC4X3_types[125]);
  IFC4X3_types[856] =
      new entity(strings[2580], false, 856, (entity *)IFC4X3_types[125]);
  IFC4X3_types[860] =
      new entity(strings[2581], false, 860, (entity *)IFC4X3_types[443]);
  IFC4X3_types[861] =
      new entity(strings[2582], false, 861, (entity *)IFC4X3_types[444]);
  IFC4X3_types[866] =
      new entity(strings[2583], false, 866, (entity *)IFC4X3_types[125]);
  IFC4X3_types[868] =
      new entity(strings[2584], false, 868, (entity *)IFC4X3_types[125]);
  IFC4X3_types[872] =
      new entity(strings[2585], false, 872, (entity *)IFC4X3_types[113]);
  IFC4X3_types[881] =
      new entity(strings[2586], false, 881, (entity *)IFC4X3_types[776]);
  IFC4X3_types[894] =
      new entity(strings[2587], true, 894, (entity *)IFC4X3_types[400]);
  IFC4X3_types[895] =
      new entity(strings[2588], true, 895, (entity *)IFC4X3_types[401]);
  IFC4X3_types[896] =
      new entity(strings[2589], false, 896, (entity *)IFC4X3_types[894]);
  IFC4X3_types[897] =
      new entity(strings[2590], false, 897, (entity *)IFC4X3_types[895]);
  IFC4X3_types[899] =
      new entity(strings[2591], false, 899, (entity *)IFC4X3_types[931]);
  IFC4X3_types[900] =
      new entity(strings[2592], false, 900, (entity *)IFC4X3_types[931]);
  IFC4X3_types[966] =
      new entity(strings[2593], false, 966, (entity *)IFC4X3_types[443]);
  IFC4X3_types[967] =
      new entity(strings[2594], false, 967, (entity *)IFC4X3_types[444]);
  IFC4X3_types[972] =
      new entity(strings[2595], false, 972, (entity *)IFC4X3_types[125]);
  IFC4X3_types[981] =
      new entity(strings[2596], false, 981, (entity *)IFC4X3_types[487]);
  IFC4X3_types[984] =
      new entity(strings[2597], false, 984, (entity *)IFC4X3_types[1124]);
  IFC4X3_types[985] =
      new entity(strings[2598], false, 985, (entity *)IFC4X3_types[1063]);
  IFC4X3_types[996] =
      new entity(strings[2599], false, 996, (entity *)IFC4X3_types[193]);
  IFC4X3_types[1002] =
      new entity(strings[2600], false, 1002, (entity *)IFC4X3_types[1063]);
  IFC4X3_types[1004] =
      new entity(strings[2601], false, 1004, (entity *)IFC4X3_types[125]);
  IFC4X3_types[1012] =
      new entity(strings[2602], false, 1012, (entity *)IFC4X3_types[400]);
  IFC4X3_types[1016] =
      new entity(strings[2603], false, 1016, (entity *)IFC4X3_types[401]);
  IFC4X3_types[1014] =
      new entity(strings[2604], false, 1014, (entity *)IFC4X3_types[487]);
  IFC4X3_types[1022] =
      new entity(strings[2605], false, 1022, (entity *)IFC4X3_types[1063]);
  IFC4X3_types[1024] =
      new entity(strings[2606], false, 1024, (entity *)IFC4X3_types[1052]);
  IFC4X3_types[1029] =
      new entity(strings[2607], false, 1029, (entity *)IFC4X3_types[125]);
  IFC4X3_types[1033] =
      new entity(strings[2608], false, 1033, (entity *)IFC4X3_types[408]);
  IFC4X3_types[1042] =
      new entity(strings[2609], false, 1042, (entity *)IFC4X3_types[1052]);
  IFC4X3_types[1045] =
      new entity(strings[2610], false, 1045, (entity *)IFC4X3_types[487]);
  IFC4X3_types[1047] =
      new entity(strings[2611], false, 1047, (entity *)IFC4X3_types[1053]);
  IFC4X3_types[1065] =
      new entity(strings[2612], false, 1065, (entity *)IFC4X3_types[487]);
  IFC4X3_types[1069] =
      new entity(strings[2613], false, 1069, (entity *)IFC4X3_types[125]);
  IFC4X3_types[1071] =
      new entity(strings[2614], false, 1071, (entity *)IFC4X3_types[125]);
  IFC4X3_types[1074] =
      new entity(strings[2615], true, 1074, (entity *)IFC4X3_types[1075]);
  IFC4X3_types[1078] =
      new entity(strings[2616], true, 1078, (entity *)IFC4X3_types[1087]);
  IFC4X3_types[1080] =
      new entity(strings[2617], false, 1080, (entity *)IFC4X3_types[1074]);
  IFC4X3_types[1082] =
      new entity(strings[2618], false, 1082, (entity *)IFC4X3_types[1078]);
  IFC4X3_types[1083] =
      new entity(strings[2619], false, 1083, (entity *)IFC4X3_types[1102]);
  IFC4X3_types[1085] =
      new entity(strings[2620], false, 1085, (entity *)IFC4X3_types[1083]);
  IFC4X3_types[1086] =
      new entity(strings[2621], false, 1086, (entity *)IFC4X3_types[1107]);
  IFC4X3_types[1088] =
      new entity(strings[2622], false, 1088, (entity *)IFC4X3_types[1080]);
  IFC4X3_types[1092] =
      new entity(strings[2623], false, 1092, (entity *)IFC4X3_types[527]);
  IFC4X3_types[1104] =
      new entity(strings[2624], false, 1104, (entity *)IFC4X3_types[1074]);
  IFC4X3_types[1105] =
      new entity(strings[2625], false, 1105, (entity *)IFC4X3_types[1078]);
  IFC4X3_types[1106] =
      new entity(strings[2626], false, 1106, (entity *)IFC4X3_types[1107]);
  IFC4X3_types[1108] =
      new entity(strings[2627], false, 1108, (entity *)IFC4X3_types[527]);
  IFC4X3_types[1109] =
      new entity(strings[2628], false, 1109, (entity *)IFC4X3_types[1074]);
  IFC4X3_types[1111] =
      new entity(strings[2629], false, 1111, (entity *)IFC4X3_types[1078]);
  IFC4X3_types[1119] =
      new entity(strings[2630], false, 1119, (entity *)IFC4X3_types[224]);
  IFC4X3_types[1126] =
      new entity(strings[2631], false, 1126, (entity *)IFC4X3_types[455]);
  IFC4X3_types[1146] =
      new entity(strings[2632], false, 1146, (entity *)IFC4X3_types[470]);
  IFC4X3_types[1148] =
      new entity(strings[2633], false, 1148, (entity *)IFC4X3_types[527]);
  IFC4X3_types[1149] =
      new entity(strings[2634], false, 1149, (entity *)IFC4X3_types[498]);
  IFC4X3_types[1156] =
      new entity(strings[2635], false, 1156, (entity *)IFC4X3_types[485]);
  IFC4X3_types[1167] =
      new entity(strings[2636], false, 1167, (entity *)IFC4X3_types[894]);
  IFC4X3_types[1168] =
      new entity(strings[2637], false, 1168, (entity *)IFC4X3_types[894]);
  IFC4X3_types[1169] =
      new entity(strings[2638], false, 1169, (entity *)IFC4X3_types[895]);
  IFC4X3_types[1171] =
      new entity(strings[2639], false, 1171, (entity *)IFC4X3_types[894]);
  IFC4X3_types[1172] =
      new entity(strings[2640], false, 1172, (entity *)IFC4X3_types[895]);
  IFC4X3_types[1174] =
      new entity(strings[2641], false, 1174, (entity *)IFC4X3_types[895]);
  IFC4X3_types[1218] =
      new entity(strings[2642], false, 1218, (entity *)IFC4X3_types[125]);
  IFC4X3_types[1221] =
      new entity(strings[2643], false, 1221, (entity *)IFC4X3_types[408]);
  IFC4X3_types[1228] =
      new entity(strings[2644], false, 1228, (entity *)IFC4X3_types[1226]);
  IFC4X3_types[1225] =
      new entity(strings[2645], true, 1225, (entity *)IFC4X3_types[395]);
  IFC4X3_types[1233] =
      new entity(strings[2646], false, 1233, (entity *)IFC4X3_types[99]);
  IFC4X3_types[1238] =
      new entity(strings[2647], false, 1238, (entity *)IFC4X3_types[408]);
  IFC4X3_types[1249] =
      new entity(strings[2648], false, 1249, (entity *)IFC4X3_types[408]);
  IFC4X3_types[1257] =
      new entity(strings[2649], false, 1257, (entity *)IFC4X3_types[470]);
  IFC4X3_types[1262] =
      new entity(strings[2650], false, 1262, (entity *)IFC4X3_types[1225]);
  IFC4X3_types[1268] =
      new entity(strings[2651], false, 1268, (entity *)IFC4X3_types[400]);
  IFC4X3_types[1269] =
      new entity(strings[2652], false, 1269, (entity *)IFC4X3_types[401]);
  IFC4X3_types[1271] =
      new entity(strings[2653], false, 1271, (entity *)IFC4X3_types[400]);
  IFC4X3_types[1272] =
      new entity(strings[2654], false, 1272, (entity *)IFC4X3_types[401]);
  IFC4X3_types[1274] =
      new entity(strings[2655], false, 1274, (entity *)IFC4X3_types[395]);
  IFC4X3_types[1277] =
      new entity(strings[2656], false, 1277, (entity *)IFC4X3_types[457]);
  IFC4X3_types[1283] =
      new entity(strings[2657], false, 1283, (entity *)IFC4X3_types[125]);
  IFC4X3_types[1289] =
      new entity(strings[2658], false, 1289, (entity *)IFC4X3_types[487]);
  IFC4X3_types[1298] =
      new entity(strings[2659], false, 1298, (entity *)IFC4X3_types[125]);
  IFC4X3_types[1301] =
      new entity(strings[2660], false, 1301, (entity *)IFC4X3_types[229]);
  IFC4X3_types[1303] =
      new entity(strings[2661], true, 1303, (entity *)IFC4X3_types[229]);
  IFC4X3_types[1304] =
      new entity(strings[2662], false, 1304, (entity *)IFC4X3_types[1303]);
  IFC4X3_types[1306] =
      new entity(strings[2663], false, 1306, (entity *)IFC4X3_types[1303]);
  IFC4X3_types[1309] =
      new entity(strings[2664], false, 1309, (entity *)IFC4X3_types[1148]);
  IFC4X3_types[275] = new select_type(strings[2665], 275,
                                      {IFC4X3_types[283], IFC4X3_types[285]});
  IFC4X3_types[278] = new select_type(
      strings[2666], 278,
      {IFC4X3_types[194], IFC4X3_types[731], IFC4X3_types[1124]});
  IFC4X3_types[279] = new select_type(strings[2667], 279,
                                      {IFC4X3_types[99], IFC4X3_types[366]});
  IFC4X3_types[557] = new select_type(strings[2668], 557,
                                      {IFC4X3_types[395], IFC4X3_types[1049]});
  IFC4X3_types[1051] = new select_type(strings[2669], 1051,
                                       {IFC4X3_types[527], IFC4X3_types[801]});
  IFC4X3_types[1076] = new select_type(strings[2670], 1076,
                                       {IFC4X3_types[395], IFC4X3_types[1087]});
  IFC4X3_types[2] =
      new entity(strings[2671], false, 2, (entity *)IFC4X3_types[229]);
  IFC4X3_types[19] =
      new entity(strings[2672], false, 19, (entity *)IFC4X3_types[470]);
  IFC4X3_types[21] =
      new entity(strings[2673], false, 21, (entity *)IFC4X3_types[487]);
  IFC4X3_types[24] =
      new entity(strings[2674], false, 24, (entity *)IFC4X3_types[408]);
  IFC4X3_types[30] =
      new entity(strings[2675], false, 30, (entity *)IFC4X3_types[604]);
  IFC4X3_types[33] =
      new entity(strings[2676], false, 33, (entity *)IFC4X3_types[604]);
  IFC4X3_types[37] =
      new entity(strings[2677], false, 37, (entity *)IFC4X3_types[604]);
  IFC4X3_types[39] =
      new entity(strings[2678], false, 39, (entity *)IFC4X3_types[604]);
  IFC4X3_types[62] =
      new entity(strings[2679], false, 62, (entity *)IFC4X3_types[527]);
  IFC4X3_types[65] =
      new entity(strings[2680], false, 65, (entity *)IFC4X3_types[487]);
  IFC4X3_types[108] =
      new entity(strings[2681], true, 108, (entity *)IFC4X3_types[99]);
  IFC4X3_types[110] =
      new entity(strings[2682], false, 110, (entity *)IFC4X3_types[108]);
  IFC4X3_types[73] =
      new entity(strings[2683], false, 73, (entity *)IFC4X3_types[125]);
  IFC4X3_types[76] =
      new entity(strings[2684], false, 76, (entity *)IFC4X3_types[125]);
  IFC4X3_types[85] =
      new entity(strings[2685], false, 85, (entity *)IFC4X3_types[408]);
  IFC4X3_types[94] =
      new entity(strings[2686], false, 94, (entity *)IFC4X3_types[194]);
  IFC4X3_types[104] =
      new entity(strings[2687], false, 104, (entity *)IFC4X3_types[443]);
  IFC4X3_types[105] =
      new entity(strings[2688], false, 105, (entity *)IFC4X3_types[444]);
  IFC4X3_types[114] =
      new entity(strings[2689], false, 114, (entity *)IFC4X3_types[443]);
  IFC4X3_types[115] =
      new entity(strings[2690], false, 115, (entity *)IFC4X3_types[400]);
  IFC4X3_types[116] =
      new entity(strings[2691], false, 116, (entity *)IFC4X3_types[401]);
  IFC4X3_types[119] =
      new entity(strings[2692], false, 119, (entity *)IFC4X3_types[125]);
  IFC4X3_types[122] =
      new entity(strings[2693], false, 122, (entity *)IFC4X3_types[1148]);
  IFC4X3_types[124] =
      new entity(strings[2694], false, 124, (entity *)IFC4X3_types[395]);
  IFC4X3_types[126] =
      new entity(strings[2695], false, 126, (entity *)IFC4X3_types[1148]);
  IFC4X3_types[129] =
      new entity(strings[2696], false, 129, (entity *)IFC4X3_types[408]);
  IFC4X3_types[132] =
      new entity(strings[2697], false, 132, (entity *)IFC4X3_types[473]);
  IFC4X3_types[135] =
      new entity(strings[2698], false, 135, (entity *)IFC4X3_types[483]);
  IFC4X3_types[138] =
      new entity(strings[2699], false, 138, (entity *)IFC4X3_types[473]);
  IFC4X3_types[141] =
      new entity(strings[2700], false, 141, (entity *)IFC4X3_types[483]);
  IFC4X3_types[144] =
      new entity(strings[2701], false, 144, (entity *)IFC4X3_types[296]);
  IFC4X3_types[159] =
      new entity(strings[2702], false, 159, (entity *)IFC4X3_types[408]);
  IFC4X3_types[161] =
      new entity(strings[2703], false, 161, (entity *)IFC4X3_types[124]);
  IFC4X3_types[164] =
      new entity(strings[2704], false, 164, (entity *)IFC4X3_types[204]);
  IFC4X3_types[167] =
      new entity(strings[2705], false, 167, (entity *)IFC4X3_types[395]);
  IFC4X3_types[176] =
      new entity(strings[2706], false, 176, (entity *)IFC4X3_types[408]);
  IFC4X3_types[183] =
      new entity(strings[2707], false, 183, (entity *)IFC4X3_types[124]);
  IFC4X3_types[187] =
      new entity(strings[2708], false, 187, (entity *)IFC4X3_types[487]);
  IFC4X3_types[199] =
      new entity(strings[2709], false, 199, (entity *)IFC4X3_types[481]);
  IFC4X3_types[202] =
      new entity(strings[2710], false, 202, (entity *)IFC4X3_types[408]);
  IFC4X3_types[215] =
      new entity(strings[2711], false, 215, (entity *)IFC4X3_types[224]);
  IFC4X3_types[218] =
      new entity(strings[2712], false, 218, (entity *)IFC4X3_types[224]);
  IFC4X3_types[221] =
      new entity(strings[2713], false, 221, (entity *)IFC4X3_types[224]);
  IFC4X3_types[236] =
      new entity(strings[2714], false, 236, (entity *)IFC4X3_types[483]);
  IFC4X3_types[239] =
      new entity(strings[2715], false, 239, (entity *)IFC4X3_types[408]);
  IFC4X3_types[242] =
      new entity(strings[2716], false, 242, (entity *)IFC4X3_types[408]);
  IFC4X3_types[254] =
      new entity(strings[2717], false, 254, (entity *)IFC4X3_types[124]);
  IFC4X3_types[257] =
      new entity(strings[2718], false, 257, (entity *)IFC4X3_types[124]);
  IFC4X3_types[268] =
      new entity(strings[2719], false, 268, (entity *)IFC4X3_types[124]);
  IFC4X3_types[288] =
      new entity(strings[2720], false, 288, (entity *)IFC4X3_types[470]);
  IFC4X3_types[295] =
      new entity(strings[2721], false, 295, (entity *)IFC4X3_types[124]);
  IFC4X3_types[310] =
      new entity(strings[2722], false, 310, (entity *)IFC4X3_types[400]);
  IFC4X3_types[311] =
      new entity(strings[2723], false, 311, (entity *)IFC4X3_types[401]);
  IFC4X3_types[314] =
      new entity(strings[2724], false, 314, (entity *)IFC4X3_types[470]);
  IFC4X3_types[317] =
      new entity(strings[2725], false, 317, (entity *)IFC4X3_types[325]);
  IFC4X3_types[321] =
      new entity(strings[2726], true, 321, (entity *)IFC4X3_types[323]);
  IFC4X3_types[322] =
      new entity(strings[2727], false, 322, (entity *)IFC4X3_types[395]);
  IFC4X3_types[324] =
      new entity(strings[2728], false, 324, (entity *)IFC4X3_types[322]);
  IFC4X3_types[326] =
      new entity(strings[2729], false, 326, (entity *)IFC4X3_types[775]);
  IFC4X3_types[328] =
      new entity(strings[2730], false, 328, (entity *)IFC4X3_types[1148]);
  IFC4X3_types[336] =
      new entity(strings[2731], false, 336, (entity *)IFC4X3_types[124]);
  IFC4X3_types[350] =
      new entity(strings[2732], false, 350, (entity *)IFC4X3_types[473]);
  IFC4X3_types[353] =
      new entity(strings[2733], false, 353, (entity *)IFC4X3_types[483]);
  IFC4X3_types[356] =
      new entity(strings[2734], false, 356, (entity *)IFC4X3_types[489]);
  IFC4X3_types[360] =
      new entity(strings[2735], false, 360, (entity *)IFC4X3_types[457]);
  IFC4X3_types[362] =
      new entity(strings[2736], false, 362, (entity *)IFC4X3_types[124]);
  IFC4X3_types[363] =
      new entity(strings[2737], false, 363, (entity *)IFC4X3_types[362]);
  IFC4X3_types[369] =
      new entity(strings[2738], false, 369, (entity *)IFC4X3_types[487]);
  IFC4X3_types[376] =
      new entity(strings[2739], false, 376, (entity *)IFC4X3_types[470]);
  IFC4X3_types[379] =
      new entity(strings[2740], false, 379, (entity *)IFC4X3_types[485]);
  IFC4X3_types[382] =
      new entity(strings[2741], false, 382, (entity *)IFC4X3_types[489]);
  IFC4X3_types[385] =
      new entity(strings[2742], false, 385, (entity *)IFC4X3_types[408]);
  IFC4X3_types[388] =
      new entity(strings[2743], false, 388, (entity *)IFC4X3_types[408]);
  IFC4X3_types[392] =
      new entity(strings[2744], false, 392, (entity *)IFC4X3_types[470]);
  IFC4X3_types[407] =
      new entity(strings[2745], false, 407, (entity *)IFC4X3_types[324]);
  IFC4X3_types[410] =
      new entity(strings[2746], false, 410, (entity *)IFC4X3_types[407]);
  IFC4X3_types[413] =
      new entity(strings[2747], false, 413, (entity *)IFC4X3_types[407]);
  IFC4X3_types[416] =
      new entity(strings[2748], false, 416, (entity *)IFC4X3_types[407]);
  IFC4X3_types[431] =
      new entity(strings[2749], false, 431, (entity *)IFC4X3_types[433]);
  IFC4X3_types[450] =
      new entity(strings[2750], false, 450, (entity *)IFC4X3_types[481]);
  IFC4X3_types[463] =
      new entity(strings[2751], false, 463, (entity *)IFC4X3_types[489]);
  IFC4X3_types[466] =
      new entity(strings[2752], false, 466, (entity *)IFC4X3_types[487]);
  IFC4X3_types[469] =
      new entity(strings[2753], false, 469, (entity *)IFC4X3_types[324]);
  IFC4X3_types[472] =
      new entity(strings[2754], false, 472, (entity *)IFC4X3_types[324]);
  IFC4X3_types[475] =
      new entity(strings[2755], false, 475, (entity *)IFC4X3_types[321]);
  IFC4X3_types[477] =
      new entity(strings[2756], false, 477, (entity *)IFC4X3_types[469]);
  IFC4X3_types[480] =
      new entity(strings[2757], false, 480, (entity *)IFC4X3_types[324]);
  IFC4X3_types[482] =
      new entity(strings[2758], false, 482, (entity *)IFC4X3_types[324]);
  IFC4X3_types[484] =
      new entity(strings[2759], false, 484, (entity *)IFC4X3_types[324]);
  IFC4X3_types[486] =
      new entity(strings[2760], false, 486, (entity *)IFC4X3_types[324]);
  IFC4X3_types[488] =
      new entity(strings[2761], false, 488, (entity *)IFC4X3_types[324]);
  IFC4X3_types[493] =
      new entity(strings[2762], false, 493, (entity *)IFC4X3_types[124]);
  IFC4X3_types[515] =
      new entity(strings[2763], true, 515, (entity *)IFC4X3_types[516]);
  IFC4X3_types[522] =
      new entity(strings[2764], false, 522, (entity *)IFC4X3_types[776]);
  IFC4X3_types[530] =
      new entity(strings[2765], false, 530, (entity *)IFC4X3_types[407]);
  IFC4X3_types[535] =
      new entity(strings[2766], false, 535, (entity *)IFC4X3_types[407]);
  IFC4X3_types[554] =
      new entity(strings[2767], false, 554, (entity *)IFC4X3_types[488]);
  IFC4X3_types[567] =
      new entity(strings[2768], false, 567, (entity *)IFC4X3_types[472]);
  IFC4X3_types[570] =
      new entity(strings[2769], false, 570, (entity *)IFC4X3_types[124]);
  IFC4X3_types[579] =
      new entity(strings[2770], false, 579, (entity *)IFC4X3_types[486]);
  IFC4X3_types[593] =
      new entity(strings[2771], false, 593, (entity *)IFC4X3_types[486]);
  IFC4X3_types[608] =
      new entity(strings[2772], false, 608, (entity *)IFC4X3_types[776]);
  IFC4X3_types[612] =
      new entity(strings[2773], false, 612, (entity *)IFC4X3_types[486]);
  IFC4X3_types[662] =
      new entity(strings[2774], false, 662, (entity *)IFC4X3_types[486]);
  IFC4X3_types[665] =
      new entity(strings[2775], false, 665, (entity *)IFC4X3_types[124]);
  IFC4X3_types[671] =
      new entity(strings[2776], false, 671, (entity *)IFC4X3_types[486]);
  IFC4X3_types[687] =
      new entity(strings[2777], false, 687, (entity *)IFC4X3_types[124]);
  IFC4X3_types[690] =
      new entity(strings[2778], false, 690, (entity *)IFC4X3_types[407]);
  IFC4X3_types[694] =
      new entity(strings[2779], false, 694, (entity *)IFC4X3_types[124]);
  IFC4X3_types[720] =
      new entity(strings[2780], false, 720, (entity *)IFC4X3_types[94]);
  IFC4X3_types[721] =
      new entity(strings[2781], false, 721, (entity *)IFC4X3_types[486]);
  IFC4X3_types[728] =
      new entity(strings[2782], false, 728, (entity *)IFC4X3_types[124]);
  IFC4X3_types[745] =
      new entity(strings[2783], false, 745, (entity *)IFC4X3_types[295]);
  IFC4X3_types[749] =
      new entity(strings[2784], false, 749, (entity *)IFC4X3_types[472]);
  IFC4X3_types[752] =
      new entity(strings[2785], false, 752, (entity *)IFC4X3_types[482]);
  IFC4X3_types[762] =
      new entity(strings[2786], false, 762, (entity *)IFC4X3_types[124]);
  IFC4X3_types[836] =
      new entity(strings[2787], false, 836, (entity *)IFC4X3_types[469]);
  IFC4X3_types[838] =
      new entity(strings[2788], false, 838, (entity *)IFC4X3_types[321]);
  IFC4X3_types[842] =
      new entity(strings[2789], false, 842, (entity *)IFC4X3_types[480]);
  IFC4X3_types[854] =
      new entity(strings[2790], false, 854, (entity *)IFC4X3_types[124]);
  IFC4X3_types[855] =
      new entity(strings[2791], false, 855, (entity *)IFC4X3_types[124]);
  IFC4X3_types[864] =
      new entity(strings[2792], false, 864, (entity *)IFC4X3_types[124]);
  IFC4X3_types[865] =
      new entity(strings[2793], false, 865, (entity *)IFC4X3_types[124]);
  IFC4X3_types[871] =
      new entity(strings[2794], false, 871, (entity *)IFC4X3_types[110]);
  IFC4X3_types[885] =
      new entity(strings[2795], false, 885, (entity *)IFC4X3_types[362]);
  IFC4X3_types[889] =
      new entity(strings[2796], false, 889, (entity *)IFC4X3_types[894]);
  IFC4X3_types[892] =
      new entity(strings[2797], false, 892, (entity *)IFC4X3_types[895]);
  IFC4X3_types[971] =
      new entity(strings[2798], false, 971, (entity *)IFC4X3_types[124]);
  IFC4X3_types[980] =
      new entity(strings[2799], false, 980, (entity *)IFC4X3_types[486]);
  IFC4X3_types[999] =
      new entity(strings[2800], false, 999, (entity *)IFC4X3_types[321]);
  IFC4X3_types[1003] =
      new entity(strings[2801], false, 1003, (entity *)IFC4X3_types[124]);
  IFC4X3_types[1013] =
      new entity(strings[2802], false, 1013, (entity *)IFC4X3_types[486]);
  IFC4X3_types[1028] =
      new entity(strings[2803], false, 1028, (entity *)IFC4X3_types[124]);
  IFC4X3_types[1032] =
      new entity(strings[2804], false, 1032, (entity *)IFC4X3_types[407]);
  IFC4X3_types[1044] =
      new entity(strings[2805], false, 1044, (entity *)IFC4X3_types[486]);
  IFC4X3_types[1064] =
      new entity(strings[2806], false, 1064, (entity *)IFC4X3_types[486]);
  IFC4X3_types[1067] =
      new entity(strings[2807], false, 1067, (entity *)IFC4X3_types[124]);
  IFC4X3_types[1068] =
      new entity(strings[2808], false, 1068, (entity *)IFC4X3_types[124]);
  IFC4X3_types[1077] =
      new entity(strings[2809], false, 1077, (entity *)IFC4X3_types[1148]);
  IFC4X3_types[1090] =
      new entity(strings[2810], false, 1090, (entity *)IFC4X3_types[1092]);
  IFC4X3_types[1103] =
      new entity(strings[2811], false, 1103, (entity *)IFC4X3_types[1109]);
  IFC4X3_types[1145] =
      new entity(strings[2812], false, 1145, (entity *)IFC4X3_types[469]);
  IFC4X3_types[1155] =
      new entity(strings[2813], false, 1155, (entity *)IFC4X3_types[484]);
  IFC4X3_types[1217] =
      new entity(strings[2814], false, 1217, (entity *)IFC4X3_types[124]);
  IFC4X3_types[1220] =
      new entity(strings[2815], false, 1220, (entity *)IFC4X3_types[407]);
  IFC4X3_types[1227] =
      new entity(strings[2816], false, 1227, (entity *)IFC4X3_types[1225]);
  IFC4X3_types[1237] =
      new entity(strings[2817], false, 1237, (entity *)IFC4X3_types[407]);
  IFC4X3_types[1246] =
      new entity(strings[2818], false, 1246, (entity *)IFC4X3_types[321]);
  IFC4X3_types[1248] =
      new entity(strings[2819], false, 1248, (entity *)IFC4X3_types[407]);
  IFC4X3_types[1256] =
      new entity(strings[2820], false, 1256, (entity *)IFC4X3_types[469]);
  IFC4X3_types[1281] =
      new entity(strings[2821], false, 1281, (entity *)IFC4X3_types[124]);
  IFC4X3_types[1282] =
      new entity(strings[2822], false, 1282, (entity *)IFC4X3_types[1281]);
  IFC4X3_types[1288] =
      new entity(strings[2823], false, 1288, (entity *)IFC4X3_types[486]);
  IFC4X3_types[1291] =
      new entity(strings[2824], false, 1291, (entity *)IFC4X3_types[124]);
  IFC4X3_types[1043] = new select_type(strings[2825], 1043,
                                       {IFC4X3_types[431], IFC4X3_types[1042]});
  IFC4X3_types[10] =
      new entity(strings[2826], false, 10, (entity *)IFC4X3_types[321]);
  IFC4X3_types[17] =
      new entity(strings[2827], false, 17, (entity *)IFC4X3_types[486]);
  IFC4X3_types[18] =
      new entity(strings[2828], false, 18, (entity *)IFC4X3_types[469]);
  IFC4X3_types[23] =
      new entity(strings[2829], false, 23, (entity *)IFC4X3_types[407]);
  IFC4X3_types[27] =
      new entity(strings[2830], false, 27, (entity *)IFC4X3_types[321]);
  IFC4X3_types[29] =
      new entity(strings[2831], false, 29, (entity *)IFC4X3_types[608]);
  IFC4X3_types[64] =
      new entity(strings[2832], false, 64, (entity *)IFC4X3_types[486]);
  IFC4X3_types[72] =
      new entity(strings[2833], false, 72, (entity *)IFC4X3_types[124]);
  IFC4X3_types[75] =
      new entity(strings[2834], false, 75, (entity *)IFC4X3_types[124]);
  IFC4X3_types[84] =
      new entity(strings[2835], false, 84, (entity *)IFC4X3_types[407]);
  IFC4X3_types[92] =
      new entity(strings[2836], false, 92, (entity *)IFC4X3_types[515]);
  IFC4X3_types[118] =
      new entity(strings[2837], false, 118, (entity *)IFC4X3_types[124]);
  IFC4X3_types[128] =
      new entity(strings[2838], false, 128, (entity *)IFC4X3_types[407]);
  IFC4X3_types[131] =
      new entity(strings[2839], false, 131, (entity *)IFC4X3_types[472]);
  IFC4X3_types[134] =
      new entity(strings[2840], false, 134, (entity *)IFC4X3_types[482]);
  IFC4X3_types[137] =
      new entity(strings[2841], false, 137, (entity *)IFC4X3_types[472]);
  IFC4X3_types[140] =
      new entity(strings[2842], false, 140, (entity *)IFC4X3_types[482]);
  IFC4X3_types[143] =
      new entity(strings[2843], false, 143, (entity *)IFC4X3_types[295]);
  IFC4X3_types[158] =
      new entity(strings[2844], false, 158, (entity *)IFC4X3_types[407]);
  IFC4X3_types[175] =
      new entity(strings[2845], false, 175, (entity *)IFC4X3_types[407]);
  IFC4X3_types[186] =
      new entity(strings[2846], false, 186, (entity *)IFC4X3_types[486]);
  IFC4X3_types[198] =
      new entity(strings[2847], false, 198, (entity *)IFC4X3_types[480]);
  IFC4X3_types[201] =
      new entity(strings[2848], false, 201, (entity *)IFC4X3_types[407]);
  IFC4X3_types[231] =
      new entity(strings[2849], false, 231, (entity *)IFC4X3_types[321]);
  IFC4X3_types[235] =
      new entity(strings[2850], false, 235, (entity *)IFC4X3_types[482]);
  IFC4X3_types[238] =
      new entity(strings[2851], false, 238, (entity *)IFC4X3_types[407]);
  IFC4X3_types[241] =
      new entity(strings[2852], false, 241, (entity *)IFC4X3_types[407]);
  IFC4X3_types[287] =
      new entity(strings[2853], false, 287, (entity *)IFC4X3_types[469]);
  IFC4X3_types[313] =
      new entity(strings[2854], false, 313, (entity *)IFC4X3_types[469]);
  IFC4X3_types[316] =
      new entity(strings[2855], false, 316, (entity *)IFC4X3_types[324]);
  IFC4X3_types[319] =
      new entity(strings[2856], false, 319, (entity *)IFC4X3_types[328]);
  IFC4X3_types[320] =
      new entity(strings[2857], false, 320, (entity *)IFC4X3_types[322]);
  IFC4X3_types[349] =
      new entity(strings[2858], false, 349, (entity *)IFC4X3_types[472]);
  IFC4X3_types[352] =
      new entity(strings[2859], false, 352, (entity *)IFC4X3_types[482]);
  IFC4X3_types[355] =
      new entity(strings[2860], false, 355, (entity *)IFC4X3_types[488]);
  IFC4X3_types[368] =
      new entity(strings[2861], false, 368, (entity *)IFC4X3_types[486]);
  IFC4X3_types[375] =
      new entity(strings[2862], false, 375, (entity *)IFC4X3_types[469]);
  IFC4X3_types[378] =
      new entity(strings[2863], false, 378, (entity *)IFC4X3_types[484]);
  IFC4X3_types[381] =
      new entity(strings[2864], false, 381, (entity *)IFC4X3_types[488]);
  IFC4X3_types[384] =
      new entity(strings[2865], false, 384, (entity *)IFC4X3_types[407]);
  IFC4X3_types[387] =
      new entity(strings[2866], false, 387, (entity *)IFC4X3_types[407]);
  IFC4X3_types[391] =
      new entity(strings[2867], false, 391, (entity *)IFC4X3_types[469]);
  IFC4X3_types[449] =
      new entity(strings[2868], false, 449, (entity *)IFC4X3_types[480]);
  IFC4X3_types[462] =
      new entity(strings[2869], false, 462, (entity *)IFC4X3_types[488]);
  IFC4X3_types[465] =
      new entity(strings[2870], false, 465, (entity *)IFC4X3_types[486]);
  IFC4X3_types[474] =
      new entity(strings[2871], false, 474, (entity *)IFC4X3_types[320]);
  IFC4X3_types[513] =
      new entity(strings[2872], false, 513, (entity *)IFC4X3_types[515]);
  IFC4X3_types[514] =
      new entity(strings[2873], false, 514, (entity *)IFC4X3_types[515]);
  IFC4X3_types[837] =
      new entity(strings[2874], false, 837, (entity *)IFC4X3_types[320]);
  IFC4X3_types[998] =
      new entity(strings[2875], false, 998, (entity *)IFC4X3_types[320]);
  IFC4X3_types[1245] =
      new entity(strings[2876], false, 1245, (entity *)IFC4X3_types[320]);
  IFC4X3_types[9] =
      new entity(strings[2877], false, 9, (entity *)IFC4X3_types[320]);
  IFC4X3_types[26] =
      new entity(strings[2878], false, 26, (entity *)IFC4X3_types[320]);
  IFC4X3_types[230] =
      new entity(strings[2879], false, 230, (entity *)IFC4X3_types[320]);
  ((entity *)IFC4X3_types[2])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[3]), true),
           new attribute(strings[2881], new named_type(IFC4X3_types[574]),
                         true),
           new attribute(strings[2882], new named_type(IFC4X3_types[1178]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[6])
      ->set_attributes({new attribute(strings[2883],
                                      new named_type(IFC4X3_types[8]), false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[7])
      ->set_attributes(
          {new attribute(strings[2884], new named_type(IFC4X3_types[970]),
                         false),
           new attribute(strings[2885], new named_type(IFC4X3_types[574]),
                         true),
           new attribute(strings[2886], new named_type(IFC4X3_types[1178]),
                         true)},
          {false, false, false});
  ((entity *)IFC4X3_types[9])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[11]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[10])
      ->set_attributes({new attribute(strings[2880],
                                      new named_type(IFC4X3_types[11]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X3_types[12])
      ->set_attributes(
          {new attribute(strings[2887], new named_type(IFC4X3_types[13]), true),
           new attribute(strings[2886], new named_type(IFC4X3_types[1178]),
                         true),
           new attribute(strings[2888], new named_type(IFC4X3_types[574]),
                         true)},
          {false, false, false});
  ((entity *)IFC4X3_types[14])->set_attributes({}, {false});
  ((entity *)IFC4X3_types[15])
      ->set_attributes({new attribute(strings[2889],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X3_types[173])),
                                      false)},
                       {false, false});
  ((entity *)IFC4X3_types[16])->set_attributes({}, {false, false, false});
  ((entity *)IFC4X3_types[17])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[22]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[18])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[20]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[19])
      ->set_attributes({new attribute(strings[2880],
                                      new named_type(IFC4X3_types[20]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X3_types[21])
      ->set_attributes({new attribute(strings[2880],
                                      new named_type(IFC4X3_types[22]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X3_types[23])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[25]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[24])
      ->set_attributes({new attribute(strings[2880],
                                      new named_type(IFC4X3_types[25]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X3_types[26])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[28]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[27])
      ->set_attributes({new attribute(strings[2880],
                                      new named_type(IFC4X3_types[28]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X3_types[29])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[38]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[30])
      ->set_attributes(
          {new attribute(strings[2890], new named_type(IFC4X3_types[778]),
                         false)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[31])
      ->set_attributes(
          {new attribute(strings[2891], new named_type(IFC4X3_types[585]),
                         false),
           new attribute(strings[2892], new named_type(IFC4X3_types[697]),
                         false),
           new attribute(strings[2893], new named_type(IFC4X3_types[585]),
                         false),
           new attribute(strings[2894], new named_type(IFC4X3_types[585]),
                         true),
           new attribute(strings[2895], new named_type(IFC4X3_types[585]),
                         false),
           new attribute(strings[2896], new named_type(IFC4X3_types[585]),
                         true),
           new attribute(strings[2880], new named_type(IFC4X3_types[32]),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[33])
      ->set_attributes({}, {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[34])
      ->set_attributes(
          {new attribute(strings[2897], new named_type(IFC4X3_types[147]),
                         false),
           new attribute(strings[2898], new named_type(IFC4X3_types[761]),
                         false),
           new attribute(strings[2899], new named_type(IFC4X3_types[585]),
                         false),
           new attribute(strings[2900], new named_type(IFC4X3_types[585]),
                         false),
           new attribute(strings[2901], new named_type(IFC4X3_types[697]),
                         false),
           new attribute(strings[2902], new named_type(IFC4X3_types[778]),
                         true),
           new attribute(strings[2880], new named_type(IFC4X3_types[35]),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[36])
      ->set_attributes({new attribute(strings[2903],
                                      new named_type(IFC4X3_types[574]), true),
                        new attribute(strings[2904],
                                      new named_type(IFC4X3_types[574]), true)},
                       {false, false});
  ((entity *)IFC4X3_types[37])
      ->set_attributes(
          {new attribute(strings[2905], new named_type(IFC4X3_types[36]),
                         false)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[39])
      ->set_attributes({}, {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[40])
      ->set_attributes(
          {new attribute(strings[2891], new named_type(IFC4X3_types[585]),
                         false),
           new attribute(strings[2892], new named_type(IFC4X3_types[697]),
                         false),
           new attribute(strings[2906], new named_type(IFC4X3_types[585]),
                         false),
           new attribute(strings[2907], new named_type(IFC4X3_types[870]),
                         false),
           new attribute(strings[2908], new named_type(IFC4X3_types[870]),
                         false),
           new attribute(strings[2909], new named_type(IFC4X3_types[585]),
                         true),
           new attribute(strings[2880], new named_type(IFC4X3_types[41]),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[46])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[48]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[47])
      ->set_attributes({new attribute(strings[2910],
                                      new named_type(IFC4X3_types[272]), false),
                        new attribute(strings[2911],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X3_types[272])),
                                      true)},
                       {false, false});
  ((entity *)IFC4X3_types[49])
      ->set_attributes(
          {new attribute(strings[2912], new named_type(IFC4X3_types[717]),
                         false),
           new attribute(strings[2913], new named_type(IFC4X3_types[574]),
                         false),
           new attribute(strings[2914], new named_type(IFC4X3_types[574]),
                         false),
           new attribute(strings[2915], new named_type(IFC4X3_types[538]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X3_types[50])
      ->set_attributes(
          {new attribute(strings[2916], new named_type(IFC4X3_types[574]),
                         true),
           new attribute(strings[2886], new named_type(IFC4X3_types[1178]),
                         true),
           new attribute(strings[2917], new named_type(IFC4X3_types[51]), true),
           new attribute(strings[2918], new named_type(IFC4X3_types[658]),
                         true),
           new attribute(strings[2919], new named_type(IFC4X3_types[291]),
                         true),
           new attribute(strings[2920], new named_type(IFC4X3_types[291]),
                         true),
           new attribute(strings[2921], new named_type(IFC4X3_types[574]),
                         true),
           new attribute(strings[2922], new named_type(IFC4X3_types[574]),
                         true),
           new attribute(strings[2923], new named_type(IFC4X3_types[60]), true),
           new attribute(strings[2924],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4X3_types[50])),
                         true)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[52])
      ->set_attributes(
          {new attribute(strings[2925], new named_type(IFC4X3_types[538]),
                         true),
           new attribute(strings[2916], new named_type(IFC4X3_types[574]),
                         true),
           new attribute(strings[2886], new named_type(IFC4X3_types[1178]),
                         true),
           new attribute(strings[2926], new named_type(IFC4X3_types[292]),
                         true),
           new attribute(strings[2881], new named_type(IFC4X3_types[574]),
                         true),
           new attribute(strings[2927], new named_type(IFC4X3_types[574]),
                         true),
           new attribute(strings[2928], new named_type(IFC4X3_types[1178]),
                         true),
           new attribute(strings[2929], new named_type(IFC4X3_types[8]), true),
           new attribute(strings[2930], new named_type(IFC4X3_types[8]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[53])
      ->set_attributes(
          {new attribute(strings[2931], new named_type(IFC4X3_types[52]),
                         false),
           new attribute(strings[2932],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4X3_types[52])),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X3_types[54])
      ->set_attributes(
          {new attribute(strings[2933], new named_type(IFC4X3_types[272]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X3_types[55])
      ->set_attributes({new attribute(strings[2934],
                                      new named_type(IFC4X3_types[99]), false)},
                       {false, false, false});
  ((entity *)IFC4X3_types[56])
      ->set_attributes({new attribute(strings[2935],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X3_types[272])),
                                      false)},
                       {false, false, false, false});
  ((entity *)IFC4X3_types[62])
      ->set_attributes(
          {new attribute(strings[2936], new named_type(IFC4X3_types[538]),
                         true),
           new attribute(strings[2937], new named_type(IFC4X3_types[252]),
                         true),
           new attribute(strings[2938], new named_type(IFC4X3_types[252]),
                         true),
           new attribute(strings[2939], new named_type(IFC4X3_types[252]),
                         true),
           new attribute(strings[2940], new named_type(IFC4X3_types[8]), true),
           new attribute(strings[2941], new named_type(IFC4X3_types[8]), true),
           new attribute(strings[2942], new named_type(IFC4X3_types[738]),
                         true),
           new attribute(strings[2943], new named_type(IFC4X3_types[291]),
                         true),
           new attribute(strings[2944], new named_type(IFC4X3_types[252]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false});
  ((entity *)IFC4X3_types[63])
      ->set_attributes({new attribute(strings[2945],
                                      new named_type(IFC4X3_types[778]), false),
                        new attribute(strings[2946],
                                      new named_type(IFC4X3_types[778]), false),
                        new attribute(strings[2947],
                                      new named_type(IFC4X3_types[778]), false),
                        new attribute(strings[2948],
                                      new named_type(IFC4X3_types[778]), false),
                        new attribute(strings[2949],
                                      new named_type(IFC4X3_types[697]), true),
                        new attribute(strings[2950],
                                      new named_type(IFC4X3_types[778]), false),
                        new attribute(strings[2951],
                                      new named_type(IFC4X3_types[778]), true),
                        new attribute(strings[2952],
                                      new named_type(IFC4X3_types[697]), true),
                        new attribute(strings[2953],
                                      new named_type(IFC4X3_types[697]), true),
                        new attribute(strings[2954],
                                      new named_type(IFC4X3_types[761]), true),
                        new attribute(strings[2955],
                                      new named_type(IFC4X3_types[697]), true),
                        new attribute(strings[2956],
                                      new named_type(IFC4X3_types[761]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[64])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[66]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[65])
      ->set_attributes({new attribute(strings[2880],
                                      new named_type(IFC4X3_types[66]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X3_types[67])
      ->set_attributes({new attribute(strings[2957],
                                      new named_type(IFC4X3_types[306]), true)},
                       {false, false});
  ((entity *)IFC4X3_types[69])
      ->set_attributes({new attribute(strings[2958],
                                      new named_type(IFC4X3_types[306]), true)},
                       {false, false});
  ((entity *)IFC4X3_types[70])
      ->set_attributes({new attribute(strings[2957],
                                      new named_type(IFC4X3_types[306]), true),
                        new attribute(strings[2958],
                                      new named_type(IFC4X3_types[306]), true)},
                       {false, false, false});
  ((entity *)IFC4X3_types[71])
      ->set_attributes({new attribute(strings[2957],
                                      new named_type(IFC4X3_types[306]), true),
                        new attribute(strings[2958],
                                      new named_type(IFC4X3_types[306]), true)},
                       {false, false, false});
  ((entity *)IFC4X3_types[108])
      ->set_attributes(
          {new attribute(strings[2959], new named_type(IFC4X3_types[552]),
                         false),
           new attribute(
               strings[2960],
               new aggregation_type(aggregation_type::list_type, 2, -1,
                                    new named_type(IFC4X3_types[147])),
               false),
           new attribute(strings[2961], new named_type(IFC4X3_types[109]),
                         false),
           new attribute(strings[2962], new named_type(IFC4X3_types[617]),
                         false),
           new attribute(strings[2963], new named_type(IFC4X3_types[617]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC4X3_types[110])
      ->set_attributes(
          {new attribute(
               strings[2964],
               new aggregation_type(aggregation_type::list_type, 2, -1,
                                    new named_type(IFC4X3_types[552])),
               false),
           new attribute(
               strings[2965],
               new aggregation_type(aggregation_type::list_type, 2, -1,
                                    new named_type(IFC4X3_types[726])),
               false),
           new attribute(strings[2966], new named_type(IFC4X3_types[573]),
                         false)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[111])
      ->set_attributes(
          {new attribute(strings[2967], new named_type(IFC4X3_types[552]),
                         false),
           new attribute(strings[2968], new named_type(IFC4X3_types[552]),
                         false),
           new attribute(
               strings[2960],
               new aggregation_type(
                   aggregation_type::list_type, 2, -1,
                   new aggregation_type(aggregation_type::list_type, 2, -1,
                                        new named_type(IFC4X3_types[147]))),
               false),
           new attribute(strings[2969], new named_type(IFC4X3_types[112]),
                         false),
           new attribute(strings[2970], new named_type(IFC4X3_types[617]),
                         false),
           new attribute(strings[2971], new named_type(IFC4X3_types[617]),
                         false),
           new attribute(strings[2963], new named_type(IFC4X3_types[617]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[113])
      ->set_attributes(
          {new attribute(
               strings[2972],
               new aggregation_type(aggregation_type::list_type, 2, -1,
                                    new named_type(IFC4X3_types[552])),
               false),
           new attribute(
               strings[2973],
               new aggregation_type(aggregation_type::list_type, 2, -1,
                                    new named_type(IFC4X3_types[552])),
               false),
           new attribute(
               strings[2974],
               new aggregation_type(aggregation_type::list_type, 2, -1,
                                    new named_type(IFC4X3_types[726])),
               false),
           new attribute(
               strings[2975],
               new aggregation_type(aggregation_type::list_type, 2, -1,
                                    new named_type(IFC4X3_types[726])),
               false),
           new attribute(strings[2966], new named_type(IFC4X3_types[573]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC4X3_types[72])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[74]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[73])
      ->set_attributes({new attribute(strings[2880],
                                      new named_type(IFC4X3_types[74]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X3_types[75])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[78]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[76])
      ->set_attributes({new attribute(strings[2880],
                                      new named_type(IFC4X3_types[78]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X3_types[82])
      ->set_attributes({new attribute(strings[2976],
                                      new named_type(IFC4X3_types[538]), false),
                        new attribute(strings[2977],
                                      new named_type(IFC4X3_types[81]), false)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[83])
      ->set_attributes(
          {new attribute(strings[2978], new named_type(IFC4X3_types[778]),
                         false),
           new attribute(strings[2979], new named_type(IFC4X3_types[778]),
                         false),
           new attribute(strings[2980], new named_type(IFC4X3_types[778]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X3_types[84])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[86]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[85])
      ->set_attributes({new attribute(strings[2880],
                                      new named_type(IFC4X3_types[86]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X3_types[88])->set_attributes({}, {false, false, false});
  ((entity *)IFC4X3_types[91])
      ->set_attributes({new attribute(strings[2981],
                                      new named_type(IFC4X3_types[90]), false),
                        new attribute(strings[2982],
                                      new named_type(IFC4X3_types[89]), false),
                        new attribute(strings[2983],
                                      new named_type(IFC4X3_types[89]), false)},
                       {false, false, false});
  ((entity *)IFC4X3_types[92])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[93])
      ->set_attributes({new attribute(strings[2916],
                                      new named_type(IFC4X3_types[574]), true)},
                       {false});
  ((entity *)IFC4X3_types[94])->set_attributes({}, {false, false});
  ((entity *)IFC4X3_types[95])
      ->set_attributes({new attribute(strings[2984],
                                      new named_type(IFC4X3_types[680]), true),
                        new attribute(strings[2985],
                                      new named_type(IFC4X3_types[680]), true),
                        new attribute(strings[2986],
                                      new named_type(IFC4X3_types[680]), true),
                        new attribute(strings[2987],
                                      new named_type(IFC4X3_types[677]), true),
                        new attribute(strings[2988],
                                      new named_type(IFC4X3_types[677]), true),
                        new attribute(strings[2989],
                                      new named_type(IFC4X3_types[677]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[96])
      ->set_attributes({new attribute(strings[2990],
                                      new named_type(IFC4X3_types[679]), true),
                        new attribute(strings[2991],
                                      new named_type(IFC4X3_types[679]), true),
                        new attribute(strings[2992],
                                      new named_type(IFC4X3_types[679]), true)},
                       {false, false, false, false});
  ((entity *)IFC4X3_types[97])
      ->set_attributes({new attribute(strings[2993],
                                      new named_type(IFC4X3_types[1224]), true),
                        new attribute(strings[2994],
                                      new named_type(IFC4X3_types[1224]), true),
                        new attribute(strings[2995],
                                      new named_type(IFC4X3_types[1224]), true),
                        new attribute(strings[2996],
                                      new named_type(IFC4X3_types[978]), true),
                        new attribute(strings[2997],
                                      new named_type(IFC4X3_types[978]), true),
                        new attribute(strings[2998],
                                      new named_type(IFC4X3_types[978]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[98])
      ->set_attributes(
          {new attribute(strings[2999], new named_type(IFC4X3_types[1287]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[99])->set_attributes({}, {});
  ((entity *)IFC4X3_types[100])->set_attributes({}, {});
  ((entity *)IFC4X3_types[101])
      ->set_attributes(
          {new attribute(strings[3000], new named_type(IFC4X3_types[147]),
                         false),
           new attribute(strings[3001], new named_type(IFC4X3_types[778]),
                         false),
           new attribute(strings[3002], new named_type(IFC4X3_types[778]),
                         false),
           new attribute(strings[3003], new named_type(IFC4X3_types[778]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X3_types[103])
      ->set_attributes(
          {new attribute(strings[3004], new named_type(IFC4X3_types[101]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X3_types[104])
      ->set_attributes({new attribute(strings[2880],
                                      new named_type(IFC4X3_types[107]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X3_types[105])
      ->set_attributes({new attribute(strings[2880],
                                      new named_type(IFC4X3_types[106]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X3_types[114])
      ->set_attributes({new attribute(strings[3005],
                                      new named_type(IFC4X3_types[585]), true),
                        new attribute(strings[3006],
                                      new named_type(IFC4X3_types[585]), true),
                        new attribute(strings[3007],
                                      new named_type(IFC4X3_types[781]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false});
  ((entity *)IFC4X3_types[115])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[117]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[116])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[117]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[118])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[120]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[119])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[120]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[121])
      ->set_attributes({new attribute(strings[3008],
                                      new named_type(IFC4X3_types[585]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X3_types[122])
      ->set_attributes({new attribute(strings[2880],
                                      new named_type(IFC4X3_types[123]), true),
                        new attribute(strings[3009],
                                      new named_type(IFC4X3_types[574]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[124])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[125])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[126])
      ->set_attributes({new attribute(strings[2880],
                                      new named_type(IFC4X3_types[127]), true),
                        new attribute(strings[3009],
                                      new named_type(IFC4X3_types[574]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[128])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[130]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[129])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[130]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[266])
      ->set_attributes(
          {new attribute(strings[3010], new named_type(IFC4X3_types[778]),
                         false),
           new attribute(strings[3011], new named_type(IFC4X3_types[778]),
                         false),
           new attribute(strings[3012], new named_type(IFC4X3_types[778]),
                         false),
           new attribute(strings[3013], new named_type(IFC4X3_types[778]),
                         false),
           new attribute(strings[3014], new named_type(IFC4X3_types[697]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[131])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[133]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[132])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[133]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[134])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[136]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[135])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[136]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[137])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[139]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[138])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[139]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[140])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[142]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[141])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[142]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[143])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[145]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[144])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[145]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[147])
      ->set_attributes({new attribute(strings[3015],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, 3,
                                          new named_type(IFC4X3_types[585])),
                                      false)},
                       {false});
  ((entity *)IFC4X3_types[148])->set_attributes({}, {});
  ((entity *)IFC4X3_types[149])
      ->set_attributes(
          {new attribute(
               strings[3016],
               new aggregation_type(
                   aggregation_type::list_type, 1, -1,
                   new aggregation_type(aggregation_type::list_type, 2, 2,
                                        new named_type(IFC4X3_types[585]))),
               false),
           new attribute(
               strings[3017],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X3_types[574])),
               true)},
          {false, false});
  ((entity *)IFC4X3_types[150])
      ->set_attributes(
          {new attribute(
               strings[3016],
               new aggregation_type(
                   aggregation_type::list_type, 1, -1,
                   new aggregation_type(aggregation_type::list_type, 3, 3,
                                        new named_type(IFC4X3_types[585]))),
               false),
           new attribute(
               strings[3017],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X3_types[574])),
               true)},
          {false, false});
  ((entity *)IFC4X3_types[151])
      ->set_attributes({new attribute(strings[3018],
                                      new named_type(IFC4X3_types[306]), true),
                        new attribute(strings[3019],
                                      new named_type(IFC4X3_types[306]), true),
                        new attribute(strings[3020],
                                      new named_type(IFC4X3_types[147]), false),
                        new attribute(strings[3021],
                                      new named_type(IFC4X3_types[873]), true)},
                       {false, false, false, false});
  ((entity *)IFC4X3_types[152])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X3_types[153])
      ->set_attributes({new attribute(strings[3022],
                                      new named_type(IFC4X3_types[873]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X3_types[154])
      ->set_attributes({new attribute(strings[3023],
                                      new named_type(IFC4X3_types[306]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X3_types[155])
      ->set_attributes({new attribute(strings[3022],
                                      new named_type(IFC4X3_types[873]), true),
                        new attribute(strings[3024],
                                      new named_type(IFC4X3_types[873]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[156])
      ->set_attributes(
          {new attribute(strings[3025], new named_type(IFC4X3_types[778]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X3_types[158])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[160]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[159])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[160]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[161])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[163]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[162])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[163]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[164])
      ->set_attributes(
          {new attribute(strings[3026], new named_type(IFC4X3_types[778]),
                         false)},
          {false, false});
  ((entity *)IFC4X3_types[165])
      ->set_attributes(
          {new attribute(strings[3012], new named_type(IFC4X3_types[778]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC4X3_types[166])
      ->set_attributes(
          {new attribute(strings[3026], new named_type(IFC4X3_types[778]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X3_types[167])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[168])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[169])
      ->set_attributes({new attribute(strings[3027],
                                      new named_type(IFC4X3_types[574]), true),
                        new attribute(strings[3028],
                                      new named_type(IFC4X3_types[574]), true),
                        new attribute(strings[3029],
                                      new named_type(IFC4X3_types[291]), true),
                        new attribute(strings[2916],
                                      new named_type(IFC4X3_types[574]), false),
                        new attribute(strings[2886],
                                      new named_type(IFC4X3_types[1178]), true),
                        new attribute(strings[3030],
                                      new named_type(IFC4X3_types[1253]), true),
                        new attribute(strings[3031],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X3_types[538])),
                                      true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[170])
      ->set_attributes({new attribute(strings[3032],
                                      new named_type(IFC4X3_types[171]), true),
                        new attribute(strings[2886],
                                      new named_type(IFC4X3_types[1178]), true),
                        new attribute(strings[3033],
                                      new named_type(IFC4X3_types[538]), true)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[173])->set_attributes({}, {false});
  ((entity *)IFC4X3_types[174])
      ->set_attributes(
          {new attribute(strings[3034], new named_type(IFC4X3_types[585]),
                         false)},
          {false, false});
  ((entity *)IFC4X3_types[175])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[177]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[176])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[177]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[180])
      ->set_attributes(
          {new attribute(strings[3035], new named_type(IFC4X3_types[698]),
                         false),
           new attribute(strings[3036], new named_type(IFC4X3_types[698]),
                         false),
           new attribute(strings[3037], new named_type(IFC4X3_types[698]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X3_types[181])
      ->set_attributes(
          {new attribute(
              strings[3038],
              new aggregation_type(
                  aggregation_type::list_type, 1, -1,
                  new aggregation_type(aggregation_type::list_type, 3, 3,
                                       new named_type(IFC4X3_types[698]))),
              false)},
          {false});
  ((entity *)IFC4X3_types[182])
      ->set_attributes({new attribute(strings[2916],
                                      new named_type(IFC4X3_types[574]), true)},
                       {false});
  ((entity *)IFC4X3_types[183])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[185]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[184])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[185]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[186])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[188]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[187])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[188]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[190])
      ->set_attributes({new attribute(strings[3039],
                                      new named_type(IFC4X3_types[538]), false),
                        new attribute(strings[3040],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X3_types[817])),
                                      false)},
                       {false, false, false, false});
  ((entity *)IFC4X3_types[191])
      ->set_attributes({new attribute(strings[3039],
                                      new named_type(IFC4X3_types[574]), true),
                        new attribute(strings[3041],
                                      new named_type(IFC4X3_types[192]), true),
                        new attribute(strings[3042],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X3_types[834])),
                                      true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[193])
      ->set_attributes(
          {new attribute(
               strings[3043],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X3_types[995])),
               false),
           new attribute(strings[2963], new named_type(IFC4X3_types[617]),
                         false)},
          {false, false});
  ((entity *)IFC4X3_types[194])->set_attributes({}, {false, false});
  ((entity *)IFC4X3_types[195])
      ->set_attributes(
          {new attribute(strings[3044], new named_type(IFC4X3_types[87]),
                         false),
           new attribute(strings[3045], new named_type(IFC4X3_types[272]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X3_types[196])
      ->set_attributes({new attribute(strings[3046],
                                      new aggregation_type(
                                          aggregation_type::set_type, 2, -1,
                                          new named_type(IFC4X3_types[806])),
                                      false),
                        new attribute(strings[3047],
                                      new named_type(IFC4X3_types[574]), true)},
                       {false, false, false, false});
  ((entity *)IFC4X3_types[198])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[200]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[199])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[200]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[201])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[203]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[202])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[203]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[204])
      ->set_attributes({new attribute(strings[3048],
                                      new named_type(IFC4X3_types[68]), false)},
                       {false});
  ((entity *)IFC4X3_types[205])
      ->set_attributes({new attribute(strings[3049],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X3_types[436])),
                                      false)},
                       {false});
  ((entity *)IFC4X3_types[206])
      ->set_attributes({new attribute(strings[3050],
                                      new named_type(IFC4X3_types[279]), false),
                        new attribute(strings[3051],
                                      new named_type(IFC4X3_types[279]), true)},
                       {false, false});
  ((entity *)IFC4X3_types[207])->set_attributes({}, {});
  ((entity *)IFC4X3_types[208])
      ->set_attributes({new attribute(strings[3052],
                                      new named_type(IFC4X3_types[585]), true),
                        new attribute(strings[3053],
                                      new named_type(IFC4X3_types[585]), true),
                        new attribute(strings[3054],
                                      new named_type(IFC4X3_types[585]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X3_types[209])
      ->set_attributes({new attribute(strings[3055],
                                      new named_type(IFC4X3_types[769]), false),
                        new attribute(strings[3056],
                                      new named_type(IFC4X3_types[769]), true)},
                       {false, false});
  ((entity *)IFC4X3_types[210])
      ->set_attributes(
          {new attribute(strings[3057], new named_type(IFC4X3_types[1130]),
                         false),
           new attribute(strings[3058], new named_type(IFC4X3_types[1130]),
                         true)},
          {false, false});
  ((entity *)IFC4X3_types[212])
      ->set_attributes(
          {new attribute(strings[3059], new named_type(IFC4X3_types[1037]),
                         false),
           new attribute(strings[3060], new named_type(IFC4X3_types[1037]),
                         true)},
          {false, false});
  ((entity *)IFC4X3_types[213])
      ->set_attributes(
          {new attribute(strings[2916], new named_type(IFC4X3_types[574]),
                         false),
           new attribute(strings[2886], new named_type(IFC4X3_types[1178]),
                         true),
           new attribute(strings[3061], new named_type(IFC4X3_types[214]),
                         false),
           new attribute(strings[3062], new named_type(IFC4X3_types[574]),
                         true),
           new attribute(strings[3063], new named_type(IFC4X3_types[8]), true),
           new attribute(strings[3064], new named_type(IFC4X3_types[292]),
                         true),
           new attribute(strings[3065], new named_type(IFC4X3_types[574]),
                         true)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[215])
      ->set_attributes({new attribute(strings[2880],
                                      new named_type(IFC4X3_types[217]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X3_types[216])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[217]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC4X3_types[218])
      ->set_attributes({new attribute(strings[2880],
                                      new named_type(IFC4X3_types[220]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X3_types[219])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[220]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC4X3_types[221])
      ->set_attributes({new attribute(strings[2880],
                                      new named_type(IFC4X3_types[223]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X3_types[222])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[223]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC4X3_types[224])
      ->set_attributes({new attribute(strings[3066],
                                      new named_type(IFC4X3_types[961]), true),
                        new attribute(strings[3067],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X3_types[50])),
                                      true),
                        new attribute(strings[3068],
                                      new named_type(IFC4X3_types[743]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X3_types[225])
      ->set_attributes({new attribute(strings[3067],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X3_types[50])),
                                      true),
                        new attribute(strings[3068],
                                      new named_type(IFC4X3_types[743]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X3_types[226])
      ->set_attributes(
          {new attribute(strings[3069], new named_type(IFC4X3_types[574]),
                         true),
           new attribute(strings[3009], new named_type(IFC4X3_types[574]),
                         true),
           new attribute(strings[3070], new named_type(IFC4X3_types[574]),
                         true),
           new attribute(
               strings[3071],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X3_types[952])),
               true),
           new attribute(strings[3072], new named_type(IFC4X3_types[1251]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[228])
      ->set_attributes(
          {new attribute(strings[2916], new named_type(IFC4X3_types[574]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X3_types[229])
      ->set_attributes({new attribute(strings[2936],
                                      new named_type(IFC4X3_types[538]), true)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[230])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[232]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[231])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[232]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[233])
      ->set_attributes(
          {new attribute(strings[2916], new named_type(IFC4X3_types[574]),
                         false),
           new attribute(strings[3073], new named_type(IFC4X3_types[658]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X3_types[234])
      ->set_attributes(
          {new attribute(strings[3074], new named_type(IFC4X3_types[873]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC4X3_types[235])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[237]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[236])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[237]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[238])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[240]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[239])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[240]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[241])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[243]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[242])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[243]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[244])
      ->set_attributes(
          {new attribute(strings[3075], new named_type(IFC4X3_types[246]),
                         false),
           new attribute(strings[3076], new named_type(IFC4X3_types[245]),
                         false)},
          {false, false});
  ((entity *)IFC4X3_types[245])
      ->set_attributes({new attribute(strings[2916],
                                      new named_type(IFC4X3_types[574]), false),
                        new attribute(strings[2886],
                                      new named_type(IFC4X3_types[1178]), true),
                        new attribute(strings[3077],
                                      new named_type(IFC4X3_types[538]), true),
                        new attribute(strings[3078],
                                      new named_type(IFC4X3_types[538]), true)},
                       {false, false, false, false});
  ((entity *)IFC4X3_types[247])
      ->set_attributes({new attribute(strings[3079],
                                      new named_type(IFC4X3_types[585]), false),
                        new attribute(strings[3080],
                                      new named_type(IFC4X3_types[585]), true)},
                       {false, false, false});
  ((entity *)IFC4X3_types[248])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[249]),
                         true),
           new attribute(
               strings[3081],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X3_types[252])),
               true),
           new attribute(
               strings[3082],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X3_types[743])),
               true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[250])
      ->set_attributes({new attribute(strings[2880],
                                      new named_type(IFC4X3_types[251]), true),
                        new attribute(strings[2881],
                                      new named_type(IFC4X3_types[574]), true),
                        new attribute(strings[3083],
                                      new named_type(IFC4X3_types[292]), true),
                        new attribute(strings[3084],
                                      new named_type(IFC4X3_types[292]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X3_types[252])
      ->set_attributes({}, {false, false, false, false, false, false, false,
                            false, false, false});
  ((entity *)IFC4X3_types[254])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[256]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[255])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[256]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[257])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[259]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[258])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[259]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[260])
      ->set_attributes({new attribute(strings[2880],
                                      new named_type(IFC4X3_types[262]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X3_types[261])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[262]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC4X3_types[263])
      ->set_attributes({new attribute(strings[3048],
                                      new named_type(IFC4X3_types[70]), false)},
                       {false});
  ((entity *)IFC4X3_types[265])
      ->set_attributes(
          {new attribute(strings[3085], new named_type(IFC4X3_types[264]),
                         false)},
          {false});
  ((entity *)IFC4X3_types[267])
      ->set_attributes({new attribute(strings[3086],
                                      new named_type(IFC4X3_types[685]), false),
                        new attribute(strings[3087],
                                      new named_type(IFC4X3_types[685]), false),
                        new attribute(strings[3088],
                                      new named_type(IFC4X3_types[780]), false),
                        new attribute(strings[3089],
                                      new named_type(IFC4X3_types[292]), true),
                        new attribute(strings[3090],
                                      new named_type(IFC4X3_types[586]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[268])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[270]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[269])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[270]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[272])->set_attributes({}, {});
  ((entity *)IFC4X3_types[273])
      ->set_attributes({new attribute(strings[3091],
                                      new named_type(IFC4X3_types[760]), false),
                        new attribute(strings[2910],
                                      new named_type(IFC4X3_types[272]), false),
                        new attribute(strings[2911],
                                      new aggregation_type(
                                          aggregation_type::set_type, 0, -1,
                                          new named_type(IFC4X3_types[272])),
                                      false)},
                       {false, false, false});
  ((entity *)IFC4X3_types[274])
      ->set_attributes(
          {new attribute(strings[3091], new named_type(IFC4X3_types[1123]),
                         false),
           new attribute(strings[3092],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4X3_types[94])),
                         false),
           new attribute(strings[3093], new named_type(IFC4X3_types[87]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X3_types[280])
      ->set_attributes(
          {new attribute(strings[3094], new named_type(IFC4X3_types[756]),
                         false),
           new attribute(strings[3095], new named_type(IFC4X3_types[277]),
                         false),
           new attribute(strings[2901], new named_type(IFC4X3_types[277]),
                         false),
           new attribute(strings[3045], new named_type(IFC4X3_types[272]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC4X3_types[281])
      ->set_attributes({new attribute(strings[3096],
                                      new named_type(IFC4X3_types[275]), true),
                        new attribute(strings[3097],
                                      new named_type(IFC4X3_types[1027]), true),
                        new attribute(strings[3098],
                                      new named_type(IFC4X3_types[178]), true),
                        new attribute(strings[3099],
                                      new named_type(IFC4X3_types[87]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X3_types[282])
      ->set_attributes({new attribute(strings[2916],
                                      new named_type(IFC4X3_types[574]), true),
                        new attribute(strings[3100],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X3_types[284])),
                                      false)},
                       {false, false});
  ((entity *)IFC4X3_types[283])
      ->set_attributes(
          {new attribute(strings[2916], new named_type(IFC4X3_types[574]),
                         true),
           new attribute(strings[3101], new named_type(IFC4X3_types[285]),
                         false),
           new attribute(strings[3102], new named_type(IFC4X3_types[780]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X3_types[284])
      ->set_attributes(
          {new attribute(strings[3103], new named_type(IFC4X3_types[585]),
                         false),
           new attribute(strings[3104], new named_type(IFC4X3_types[778]),
                         false)},
          {false, false});
  ((entity *)IFC4X3_types[286])
      ->set_attributes(
          {new attribute(strings[3026], new named_type(IFC4X3_types[778]),
                         false)},
          {false, false});
  ((entity *)IFC4X3_types[287])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[289]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[288])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[289]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[295])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[296])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[299])
      ->set_attributes({new attribute(strings[3105],
                                      new named_type(IFC4X3_types[806]), false),
                        new attribute(strings[2981],
                                      new named_type(IFC4X3_types[152]), false),
                        new attribute(strings[3047],
                                      new named_type(IFC4X3_types[574]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X3_types[300])
      ->set_attributes({new attribute(strings[3106],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X3_types[301])),
                                      false),
                        new attribute(strings[3107],
                                      new named_type(IFC4X3_types[302]), false),
                        new attribute(strings[3108],
                                      new named_type(IFC4X3_types[574]), true),
                        new attribute(strings[2916],
                                      new named_type(IFC4X3_types[574]), true)},
                       {false, false, false, false});
  ((entity *)IFC4X3_types[301])
      ->set_attributes(
          {new attribute(strings[3109], new named_type(IFC4X3_types[693]),
                         false),
           new attribute(strings[3110],
                         new simple_type(simple_type::integer_type), false)},
          {false, false});
  ((entity *)IFC4X3_types[304])
      ->set_attributes(
          {new attribute(strings[3111],
                         new simple_type(simple_type::integer_type), false),
           new attribute(strings[3112],
                         new simple_type(simple_type::integer_type), false),
           new attribute(strings[3113],
                         new simple_type(simple_type::integer_type), false),
           new attribute(strings[3114],
                         new simple_type(simple_type::integer_type), false),
           new attribute(strings[3115],
                         new simple_type(simple_type::integer_type), false),
           new attribute(strings[3116],
                         new simple_type(simple_type::integer_type), false),
           new attribute(strings[3117],
                         new simple_type(simple_type::integer_type), false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[306])
      ->set_attributes({new attribute(strings[3118],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, 3,
                                          new named_type(IFC4X3_types[873])),
                                      false)},
                       {false});
  ((entity *)IFC4X3_types[308])
      ->set_attributes({new attribute(strings[3119],
                                      new named_type(IFC4X3_types[272]), false),
                        new attribute(strings[3120],
                                      new named_type(IFC4X3_types[277]), true),
                        new attribute(strings[3121],
                                      new named_type(IFC4X3_types[277]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X3_types[309])
      ->set_attributes({}, {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[310])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[312]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[311])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[312]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[313])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[315]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[314])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[315]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[316])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[318]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[317])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[318]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[319])
      ->set_attributes({}, {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[320])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[321])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[322])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[323])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[324])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[325])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[326])
      ->set_attributes({new attribute(strings[3122],
                                      new named_type(IFC4X3_types[471]), true),
                        new attribute(strings[2880],
                                      new named_type(IFC4X3_types[327]), true),
                        new attribute(strings[3123],
                                      new named_type(IFC4X3_types[329]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X3_types[328])
      ->set_attributes({new attribute(strings[3009],
                                      new named_type(IFC4X3_types[574]), true),
                        new attribute(strings[2880],
                                      new named_type(IFC4X3_types[329]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[331])
      ->set_attributes(
          {new attribute(strings[2936], new named_type(IFC4X3_types[538]),
                         false),
           new attribute(strings[2916], new named_type(IFC4X3_types[574]),
                         false),
           new attribute(strings[2886], new named_type(IFC4X3_types[1178]),
                         true),
           new attribute(strings[3124], new named_type(IFC4X3_types[1253]),
                         true),
           new attribute(strings[2887], new named_type(IFC4X3_types[1178]),
                         true),
           new attribute(strings[3125], new named_type(IFC4X3_types[1178]),
                         true),
           new attribute(strings[3126], new named_type(IFC4X3_types[1178]),
                         true),
           new attribute(strings[3127], new named_type(IFC4X3_types[574]),
                         true),
           new attribute(strings[3128], new named_type(IFC4X3_types[8]), true),
           new attribute(strings[3129],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4X3_types[8])),
                         true),
           new attribute(strings[3064], new named_type(IFC4X3_types[292]),
                         true),
           new attribute(strings[3130], new named_type(IFC4X3_types[292]),
                         true),
           new attribute(strings[3131], new named_type(IFC4X3_types[538]),
                         true),
           new attribute(strings[3132], new named_type(IFC4X3_types[291]),
                         true),
           new attribute(strings[3133], new named_type(IFC4X3_types[291]),
                         true),
           new attribute(strings[3134], new named_type(IFC4X3_types[330]),
                         true),
           new attribute(strings[2881], new named_type(IFC4X3_types[335]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[332])
      ->set_attributes({new attribute(strings[3135],
                                      new named_type(IFC4X3_types[331]), false),
                        new attribute(strings[3136],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X3_types[331])),
                                      false),
                        new attribute(strings[3137],
                                      new named_type(IFC4X3_types[574]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X3_types[333])
      ->set_attributes({new attribute(strings[2886],
                                      new named_type(IFC4X3_types[1178]), true),
                        new attribute(strings[3138],
                                      new named_type(IFC4X3_types[331]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X3_types[336])
      ->set_attributes({new attribute(strings[3139],
                                      new named_type(IFC4X3_types[778]), true),
                        new attribute(strings[3140],
                                      new named_type(IFC4X3_types[778]), true),
                        new attribute(strings[2880],
                                      new named_type(IFC4X3_types[344]), true),
                        new attribute(strings[3141],
                                      new named_type(IFC4X3_types[345]), true),
                        new attribute(strings[3142],
                                      new named_type(IFC4X3_types[574]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false, false});
  ((entity *)IFC4X3_types[337])
      ->set_attributes({new attribute(strings[3143],
                                      new named_type(IFC4X3_types[778]), true),
                        new attribute(strings[3144],
                                      new named_type(IFC4X3_types[697]), true),
                        new attribute(strings[3145],
                                      new named_type(IFC4X3_types[778]), true),
                        new attribute(strings[3146],
                                      new named_type(IFC4X3_types[697]), true),
                        new attribute(strings[3147],
                                      new named_type(IFC4X3_types[697]), true),
                        new attribute(strings[3148],
                                      new named_type(IFC4X3_types[585]), true),
                        new attribute(strings[3149],
                                      new named_type(IFC4X3_types[585]), true),
                        new attribute(strings[3150],
                                      new named_type(IFC4X3_types[585]), true),
                        new attribute(strings[3151],
                                      new named_type(IFC4X3_types[778]), true),
                        new attribute(strings[3152],
                                      new named_type(IFC4X3_types[778]), true),
                        new attribute(strings[3153],
                                      new named_type(IFC4X3_types[1006]), true),
                        new attribute(strings[3154],
                                      new named_type(IFC4X3_types[585]), true),
                        new attribute(strings[3155],
                                      new named_type(IFC4X3_types[585]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false, false, false, false, false,
                        false});
  ((entity *)IFC4X3_types[340])
      ->set_attributes(
          {new attribute(strings[3156], new named_type(IFC4X3_types[778]),
                         true),
           new attribute(strings[3157], new named_type(IFC4X3_types[338]),
                         false),
           new attribute(strings[3158], new named_type(IFC4X3_types[698]),
                         true),
           new attribute(strings[3159], new named_type(IFC4X3_types[339]),
                         false),
           new attribute(strings[3153], new named_type(IFC4X3_types[1006]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[343])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[344]),
                         false),
           new attribute(strings[3141], new named_type(IFC4X3_types[345]),
                         false),
           new attribute(strings[3160], new named_type(IFC4X3_types[87]), true),
           new attribute(strings[3142], new named_type(IFC4X3_types[574]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false});
  ((entity *)IFC4X3_types[347])->set_attributes({}, {false});
  ((entity *)IFC4X3_types[348])->set_attributes({}, {false});
  ((entity *)IFC4X3_types[349])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[351]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[350])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[351]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[352])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[354]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[353])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[354]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[355])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[357]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[356])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[357]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[360])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[361]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[362])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[363])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[364]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[365])
      ->set_attributes(
          {new attribute(strings[3161], new named_type(IFC4X3_types[1265]),
                         false),
           new attribute(strings[3162], new named_type(IFC4X3_types[1265]),
                         false)},
          {false, false});
  ((entity *)IFC4X3_types[366])
      ->set_attributes({new attribute(strings[3163],
                                      new named_type(IFC4X3_types[272]), false),
                        new attribute(strings[3044],
                                      new named_type(IFC4X3_types[87]), false)},
                       {false, false, false, false});
  ((entity *)IFC4X3_types[367])
      ->set_attributes({new attribute(strings[3164],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X3_types[719])),
                                      false)},
                       {false});
  ((entity *)IFC4X3_types[368])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[370]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[369])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[370]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[375])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[377]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[376])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[377]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[378])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[380]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[379])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[380]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[381])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[383]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[382])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[383]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[384])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[386]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[385])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[386]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[387])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[389]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[388])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[389]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[391])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[393]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[392])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[393]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[395])
      ->set_attributes(
          {new attribute(strings[3165], new named_type(IFC4X3_types[538]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[397])
      ->set_attributes(
          {new attribute(strings[3166], new named_type(IFC4X3_types[61]), true),
           new attribute(strings[2880], new named_type(IFC4X3_types[399]),
                         true)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[398])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[399]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[400])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[401])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[403])
      ->set_attributes({new attribute(strings[3167],
                                      new named_type(IFC4X3_types[574]), true),
                        new attribute(strings[3168],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X3_types[743])),
                                      false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[404])
      ->set_attributes(
          {new attribute(strings[3169], new named_type(IFC4X3_types[574]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[396])
      ->set_attributes({new attribute(strings[3048],
                                      new named_type(IFC4X3_types[70]), false)},
                       {false});
  ((entity *)IFC4X3_types[405])
      ->set_attributes(
          {new attribute(strings[3170], new named_type(IFC4X3_types[778]),
                         false),
           new attribute(strings[3171], new named_type(IFC4X3_types[778]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X3_types[406])
      ->set_attributes(
          {new attribute(strings[3170], new named_type(IFC4X3_types[778]),
                         false),
           new attribute(strings[3171], new named_type(IFC4X3_types[778]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC4X3_types[407])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[408])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[410])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[412]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[411])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[412]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[413])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[415]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[414])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[415]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[416])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[418]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[417])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[418]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[419])
      ->set_attributes({new attribute(strings[2880],
                                      new named_type(IFC4X3_types[423]), true),
                        new attribute(strings[3172],
                                      new named_type(IFC4X3_types[421]), true),
                        new attribute(strings[3173],
                                      new named_type(IFC4X3_types[574]), true),
                        new attribute(strings[3174],
                                      new named_type(IFC4X3_types[420]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X3_types[420])
      ->set_attributes({new attribute(strings[3175],
                                      new named_type(IFC4X3_types[292]), true),
                        new attribute(strings[3176],
                                      new named_type(IFC4X3_types[292]), true),
                        new attribute(strings[3177],
                                      new named_type(IFC4X3_types[292]), true),
                        new attribute(strings[3178],
                                      new named_type(IFC4X3_types[292]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[422])
      ->set_attributes({new attribute(strings[2880],
                                      new named_type(IFC4X3_types[423]), false),
                        new attribute(strings[3172],
                                      new named_type(IFC4X3_types[421]), false),
                        new attribute(strings[3173],
                                      new named_type(IFC4X3_types[574]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false});
  ((entity *)IFC4X3_types[424])
      ->set_attributes({new attribute(strings[2916],
                                      new named_type(IFC4X3_types[538]), true),
                        new attribute(strings[2886],
                                      new named_type(IFC4X3_types[1178]), true),
                        new attribute(strings[3179],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X3_types[817])),
                                      false)},
                       {false, false, false});
  ((entity *)IFC4X3_types[425])->set_attributes({}, {});
  ((entity *)IFC4X3_types[429])
      ->set_attributes({new attribute(strings[3124],
                                      new named_type(IFC4X3_types[1253]), true),
                        new attribute(strings[2936],
                                      new named_type(IFC4X3_types[538]), true),
                        new attribute(strings[2916],
                                      new named_type(IFC4X3_types[574]), true)},
                       {false, false, false});
  ((entity *)IFC4X3_types[430])
      ->set_attributes({new attribute(strings[3180],
                                      new named_type(IFC4X3_types[429]), false),
                        new attribute(strings[3181],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X3_types[959])),
                                      false)},
                       {false, false, false, false});
  ((entity *)IFC4X3_types[431])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[432]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[433])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[426])->set_attributes({}, {false, false, false});
  ((entity *)IFC4X3_types[427])->set_attributes({}, {false, false, false});
  ((entity *)IFC4X3_types[428])->set_attributes({}, {false, false, false});
  ((entity *)IFC4X3_types[434])
      ->set_attributes(
          {new attribute(strings[3182], new named_type(IFC4X3_types[306]),
                         false),
           new attribute(strings[3010], new named_type(IFC4X3_types[778]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X3_types[435])
      ->set_attributes(
          {new attribute(strings[3183], new named_type(IFC4X3_types[806]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC4X3_types[436])
      ->set_attributes({new attribute(strings[3184],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X3_types[438])),
                                      false)},
                       {false});
  ((entity *)IFC4X3_types[437])
      ->set_attributes({new attribute(strings[3185],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X3_types[205])),
                                      false)},
                       {false});
  ((entity *)IFC4X3_types[438])
      ->set_attributes({new attribute(strings[3186],
                                      new named_type(IFC4X3_types[619]), false),
                        new attribute(strings[3187],
                                      new named_type(IFC4X3_types[87]), false)},
                       {false, false});
  ((entity *)IFC4X3_types[439])->set_attributes({}, {false, false});
  ((entity *)IFC4X3_types[440])
      ->set_attributes(
          {new attribute(strings[3188], new named_type(IFC4X3_types[1123]),
                         false),
           new attribute(strings[3044], new named_type(IFC4X3_types[87]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X3_types[441])->set_attributes({}, {false});
  ((entity *)IFC4X3_types[442])
      ->set_attributes({new attribute(strings[2889],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X3_types[173])),
                                      false)},
                       {false, false});
  ((entity *)IFC4X3_types[443])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[444])
      ->set_attributes(
          {new attribute(strings[3189], new named_type(IFC4X3_types[447]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[445])
      ->set_attributes({new attribute(strings[2880],
                                      new named_type(IFC4X3_types[446]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X3_types[448])
      ->set_attributes({new attribute(strings[3190],
                                      new named_type(IFC4X3_types[496]), true),
                        new attribute(strings[3191],
                                      new named_type(IFC4X3_types[496]), true),
                        new attribute(strings[3192],
                                      new named_type(IFC4X3_types[496]), true),
                        new attribute(strings[3193],
                                      new named_type(IFC4X3_types[496]), true),
                        new attribute(strings[3194],
                                      new named_type(IFC4X3_types[496]), true),
                        new attribute(strings[3195],
                                      new named_type(IFC4X3_types[496]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[449])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[451]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[450])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[451]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[452])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[454]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[453])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[454]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[455])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[456])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[457])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[458])
      ->set_attributes({new attribute(strings[3196],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X3_types[461])),
                                      false),
                        new attribute(strings[3099],
                                      new named_type(IFC4X3_types[87]), true)},
                       {false, false, false});
  ((entity *)IFC4X3_types[459])
      ->set_attributes(
          {new attribute(strings[3197], new named_type(IFC4X3_types[281]),
                         false),
           new attribute(strings[3198], new named_type(IFC4X3_types[529]),
                         false),
           new attribute(strings[3199], new named_type(IFC4X3_types[147]),
                         true),
           new attribute(strings[3200], new named_type(IFC4X3_types[147]),
                         true),
           new attribute(strings[3201], new named_type(IFC4X3_types[761]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC4X3_types[460])
      ->set_attributes(
          {new attribute(
               strings[3202],
               new aggregation_type(aggregation_type::list_type, 2, 2,
                                    new named_type(IFC4X3_types[1260])),
               false),
           new attribute(
               strings[3203],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X3_types[1116])),
               false),
           new attribute(strings[3204], new named_type(IFC4X3_types[780]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X3_types[462])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[464]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[463])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[464]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[465])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[467]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[466])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[467]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[468])
      ->set_attributes(
          {new attribute(strings[3205], new named_type(IFC4X3_types[306]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[469])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[470])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[472])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[473])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[474])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[476]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[475])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[476]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[477])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[479]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[478])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[479]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[480])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[481])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[482])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[483])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[484])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[485])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[486])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[487])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[488])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[489])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[493])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[495]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[494])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[495]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[498])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[499])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[500])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[502]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[501])
      ->set_attributes({new attribute(strings[3166],
                                      new named_type(IFC4X3_types[61]), false),
                        new attribute(strings[2880],
                                      new named_type(IFC4X3_types[502]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X3_types[503])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[505]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[504])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[505]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[506])->set_attributes({}, {false});
  ((entity *)IFC4X3_types[508])
      ->set_attributes({new attribute(strings[3206],
                                      new named_type(IFC4X3_types[305]), false),
                        new attribute(strings[3207],
                                      new named_type(IFC4X3_types[873]), true),
                        new attribute(strings[3208],
                                      new named_type(IFC4X3_types[68]), false),
                        new attribute(strings[3209],
                                      new named_type(IFC4X3_types[306]), true)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[509])->set_attributes({}, {});
  ((entity *)IFC4X3_types[510])
      ->set_attributes(
          {new attribute(strings[3210], new named_type(IFC4X3_types[508]),
                         false),
           new attribute(strings[3211], new named_type(IFC4X3_types[780]),
                         true),
           new attribute(strings[3212], new named_type(IFC4X3_types[507]),
                         false),
           new attribute(strings[3213], new named_type(IFC4X3_types[574]),
                         true)},
          {false, false, true, true, true, true, false, false, false, false});
  ((entity *)IFC4X3_types[511])
      ->set_attributes({new attribute(strings[3106],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X3_types[512])),
                                      false)},
                       {false});
  ((entity *)IFC4X3_types[513])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[514])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[515])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[516])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[517])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[518]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[521])
      ->set_attributes({new attribute(strings[3214],
                                      new named_type(IFC4X3_types[99]), false),
                        new attribute(strings[3215],
                                      new named_type(IFC4X3_types[756]), true)},
                       {false, false, false, false});
  ((entity *)IFC4X3_types[522])
      ->set_attributes({new attribute(strings[3216],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X3_types[523])),
                                      false),
                        new attribute(strings[3217],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X3_types[523])),
                                      false),
                        new attribute(strings[3218],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X3_types[523])),
                                      true),
                        new attribute(strings[2880],
                                      new named_type(IFC4X3_types[526]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X3_types[523])
      ->set_attributes({new attribute(strings[3219],
                                      new named_type(IFC4X3_types[574]), true),
                        new attribute(strings[3220],
                                      new named_type(IFC4X3_types[272]), false),
                        new attribute(strings[3044],
                                      new named_type(IFC4X3_types[87]), false)},
                       {false, false, false});
  ((entity *)IFC4X3_types[524])
      ->set_attributes(
          {new attribute(strings[3221], new named_type(IFC4X3_types[1276]),
                         false),
           new attribute(strings[3222], new named_type(IFC4X3_types[525]),
                         true)},
          {false, false, false});
  ((entity *)IFC4X3_types[527])
      ->set_attributes({}, {false, false, false, false, false});
  ((entity *)IFC4X3_types[528])
      ->set_attributes(
          {new attribute(strings[3223], new named_type(IFC4X3_types[1123]),
                         false),
           new attribute(strings[3224], new named_type(IFC4X3_types[87]),
                         false)},
          {false, false});
  ((entity *)IFC4X3_types[530])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[532]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[531])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[532]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[535])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[537]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[536])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[537]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[565])
      ->set_attributes({new attribute(strings[3140],
                                      new named_type(IFC4X3_types[778]), false),
                        new attribute(strings[2946],
                                      new named_type(IFC4X3_types[778]), false),
                        new attribute(strings[2947],
                                      new named_type(IFC4X3_types[778]), false),
                        new attribute(strings[3225],
                                      new named_type(IFC4X3_types[778]), false),
                        new attribute(strings[3226],
                                      new named_type(IFC4X3_types[697]), true),
                        new attribute(strings[3227],
                                      new named_type(IFC4X3_types[697]), true),
                        new attribute(strings[3228],
                                      new named_type(IFC4X3_types[761]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X3_types[540])
      ->set_attributes(
          {new attribute(strings[3229], new named_type(IFC4X3_types[1253]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[541])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[543]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[542])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[543]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[544])
      ->set_attributes(
          {new attribute(strings[3230], new named_type(IFC4X3_types[1176]),
                         false),
           new attribute(strings[3231], new named_type(IFC4X3_types[698]),
                         true),
           new attribute(strings[3232], new named_type(IFC4X3_types[181]),
                         false),
           new attribute(
               strings[3233],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X3_types[777])),
               false)},
          {false, false, false, false});
  ((entity *)IFC4X3_types[545])
      ->set_attributes(
          {new attribute(strings[3234], new named_type(IFC4X3_types[148]),
                         false),
           new attribute(
               strings[3043],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X3_types[997])),
               true),
           new attribute(strings[2963], new named_type(IFC4X3_types[617]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X3_types[546])
      ->set_attributes({new attribute(strings[3235],
                                      new aggregation_type(
                                          aggregation_type::list_type, 3, -1,
                                          new named_type(IFC4X3_types[777])),
                                      false)},
                       {false});
  ((entity *)IFC4X3_types[547])
      ->set_attributes(
          {new attribute(
              strings[3236],
              new aggregation_type(
                  aggregation_type::list_type, 1, -1,
                  new aggregation_type(aggregation_type::list_type, 3, -1,
                                       new named_type(IFC4X3_types[777]))),
              false)},
          {false, false});
  ((entity *)IFC4X3_types[548])
      ->set_attributes({new attribute(strings[3237],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X3_types[1193])),
                                      false)},
                       {false, false, false, false});
  ((entity *)IFC4X3_types[549])
      ->set_attributes(
          {new attribute(strings[3230], new named_type(IFC4X3_types[1176]),
                         false),
           new attribute(strings[3238], new named_type(IFC4X3_types[1197]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X3_types[550])
      ->set_attributes(
          {new attribute(
              strings[3239],
              new aggregation_type(
                  aggregation_type::list_type, 1, -1,
                  new aggregation_type(aggregation_type::list_type, 3, 3,
                                       new named_type(IFC4X3_types[777]))),
              true)},
          {false, false, false, false});
  ((entity *)IFC4X3_types[554])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[556]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[555])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[556]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[559])->set_attributes({}, {false, false, false});
  ((entity *)IFC4X3_types[560])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[561]),
                         true),
           new attribute(strings[3240], new named_type(IFC4X3_types[8]), true),
           new attribute(
               strings[3241],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X3_types[738])),
               true),
           new attribute(strings[3242], new named_type(IFC4X3_types[291]),
                         true),
           new attribute(strings[2938], new named_type(IFC4X3_types[252]),
                         true),
           new attribute(strings[2937], new named_type(IFC4X3_types[252]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[563])
      ->set_attributes(
          {new attribute(
              strings[3243],
              new aggregation_type(aggregation_type::list_type, 1, -1,
                                   new named_type(IFC4X3_types[564])),
              false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[564])
      ->set_attributes({new attribute(strings[3244],
                                      new named_type(IFC4X3_types[292]), false),
                        new attribute(strings[3245],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X3_types[1255])),
                                      false)},
                       {false, false});
  ((entity *)IFC4X3_types[567])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[569]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[568])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[569]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[570])
      ->set_attributes(
          {new attribute(strings[3246], new named_type(IFC4X3_types[87]),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[571])
      ->set_attributes({new attribute(strings[3246],
                                      new named_type(IFC4X3_types[87]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X3_types[620])
      ->set_attributes(
          {new attribute(strings[3010], new named_type(IFC4X3_types[778]),
                         false),
           new attribute(strings[3011], new named_type(IFC4X3_types[778]),
                         true),
           new attribute(strings[3025], new named_type(IFC4X3_types[778]),
                         false),
           new attribute(strings[3226], new named_type(IFC4X3_types[697]),
                         true),
           new attribute(strings[3247], new named_type(IFC4X3_types[697]),
                         true),
           new attribute(strings[3248], new named_type(IFC4X3_types[761]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[575])
      ->set_attributes({new attribute(strings[2880],
                                      new named_type(IFC4X3_types[577]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X3_types[576])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[577]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC4X3_types[578])
      ->set_attributes(
          {new attribute(strings[3249], new named_type(IFC4X3_types[1207]),
                         false),
           new attribute(strings[3250], new named_type(IFC4X3_types[1159]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC4X3_types[579])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[581]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[580])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[581]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[586])
      ->set_attributes(
          {new attribute(strings[2916], new named_type(IFC4X3_types[574]),
                         false),
           new attribute(strings[2913], new named_type(IFC4X3_types[574]),
                         true),
           new attribute(strings[3251], new named_type(IFC4X3_types[8]), true),
           new attribute(strings[3252], new named_type(IFC4X3_types[292]),
                         true),
           new attribute(strings[3124], new named_type(IFC4X3_types[1253]),
                         true),
           new attribute(strings[2886], new named_type(IFC4X3_types[1178]),
                         true)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[587])
      ->set_attributes({new attribute(strings[2886],
                                      new named_type(IFC4X3_types[1178]), true),
                        new attribute(strings[3253],
                                      new named_type(IFC4X3_types[582]), true),
                        new attribute(strings[3254],
                                      new named_type(IFC4X3_types[586]), true)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[590])
      ->set_attributes({new attribute(strings[3255],
                                      new named_type(IFC4X3_types[761]), false),
                        new attribute(strings[3256],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X3_types[761])),
                                      false),
                        new attribute(strings[3257],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X3_types[622])),
                                      false)},
                       {false, false, false});
  ((entity *)IFC4X3_types[593])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[595]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[594])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[595]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[596])
      ->set_attributes({new attribute(strings[3258],
                                      new named_type(IFC4X3_types[589]), false),
                        new attribute(strings[3259],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X3_types[590])),
                                      false)},
                       {false, false});
  ((entity *)IFC4X3_types[597])
      ->set_attributes({new attribute(strings[2916],
                                      new named_type(IFC4X3_types[574]), true),
                        new attribute(strings[3260],
                                      new named_type(IFC4X3_types[180]), false),
                        new attribute(strings[3261],
                                      new named_type(IFC4X3_types[698]), true),
                        new attribute(strings[3262],
                                      new named_type(IFC4X3_types[698]), true)},
                       {false, false, false, false});
  ((entity *)IFC4X3_types[598])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X3_types[599])
      ->set_attributes(
          {new attribute(strings[3187], new named_type(IFC4X3_types[306]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC4X3_types[600])
      ->set_attributes(
          {new attribute(strings[3048], new named_type(IFC4X3_types[70]),
                         false),
           new attribute(strings[3263], new named_type(IFC4X3_types[180]),
                         true),
           new attribute(strings[3264], new named_type(IFC4X3_types[1203]),
                         false),
           new attribute(strings[3265], new named_type(IFC4X3_types[621]),
                         false),
           new attribute(strings[3266], new named_type(IFC4X3_types[592]),
                         false),
           new attribute(strings[3267], new named_type(IFC4X3_types[591]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[601])
      ->set_attributes(
          {new attribute(strings[3048], new named_type(IFC4X3_types[147]),
                         false),
           new attribute(strings[3026], new named_type(IFC4X3_types[778]),
                         false),
           new attribute(strings[3268], new named_type(IFC4X3_types[873]),
                         false),
           new attribute(strings[3269], new named_type(IFC4X3_types[873]),
                         false),
           new attribute(strings[3270], new named_type(IFC4X3_types[873]),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[602])
      ->set_attributes(
          {new attribute(strings[3187], new named_type(IFC4X3_types[306]),
                         false),
           new attribute(strings[3271], new named_type(IFC4X3_types[873]),
                         true),
           new attribute(strings[3272], new named_type(IFC4X3_types[779]),
                         false),
           new attribute(strings[3273], new named_type(IFC4X3_types[779]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false});
  ((entity *)IFC4X3_types[603])
      ->set_attributes(
          {new attribute(strings[3274], new named_type(IFC4X3_types[147]),
                         false),
           new attribute(strings[3275], new named_type(IFC4X3_types[1260]),
                         false)},
          {false, false});
  ((entity *)IFC4X3_types[604])
      ->set_attributes({}, {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[607])
      ->set_attributes({new attribute(strings[3276],
                                      new named_type(IFC4X3_types[71]), false),
                        new attribute(strings[3277],
                                      new named_type(IFC4X3_types[70]), true)},
                       {false, false, false});
  ((entity *)IFC4X3_types[608])
      ->set_attributes({}, {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[612])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[614]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[613])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[614]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[616])
      ->set_attributes({new attribute(strings[3276],
                                      new named_type(IFC4X3_types[68]), false)},
                       {false, false});
  ((entity *)IFC4X3_types[619])->set_attributes({}, {});
  ((entity *)IFC4X3_types[626])
      ->set_attributes(
          {new attribute(strings[3278], new named_type(IFC4X3_types[173]),
                         false)},
          {false});
  ((entity *)IFC4X3_types[627])
      ->set_attributes({new attribute(strings[3279],
                                      new named_type(IFC4X3_types[585]), false),
                        new attribute(strings[3280],
                                      new named_type(IFC4X3_types[585]), false),
                        new attribute(strings[3281],
                                      new named_type(IFC4X3_types[585]), false),
                        new attribute(strings[3282],
                                      new named_type(IFC4X3_types[873]), true),
                        new attribute(strings[3283],
                                      new named_type(IFC4X3_types[873]), true),
                        new attribute(strings[3021],
                                      new named_type(IFC4X3_types[873]), true),
                        new attribute(strings[3284],
                                      new named_type(IFC4X3_types[873]), true),
                        new attribute(strings[3285],
                                      new named_type(IFC4X3_types[873]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X3_types[628])
      ->set_attributes(
          {new attribute(strings[3286], new named_type(IFC4X3_types[954]),
                         false),
           new attribute(strings[3287], new named_type(IFC4X3_types[151]),
                         false)},
          {false, false});
  ((entity *)IFC4X3_types[629])
      ->set_attributes({new attribute(strings[2880],
                                      new named_type(IFC4X3_types[630]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X3_types[631])
      ->set_attributes({new attribute(strings[2880],
                                      new named_type(IFC4X3_types[632]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X3_types[637])
      ->set_attributes({new attribute(strings[2916],
                                      new named_type(IFC4X3_types[574]), false),
                        new attribute(strings[2886],
                                      new named_type(IFC4X3_types[1178]), true),
                        new attribute(strings[2921],
                                      new named_type(IFC4X3_types[574]), true)},
                       {false, false, false});
  ((entity *)IFC4X3_types[638])
      ->set_attributes(
          {new attribute(
               strings[3288],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X3_types[172])),
               false),
           new attribute(strings[3289], new named_type(IFC4X3_types[637]),
                         false)},
          {false, false});
  ((entity *)IFC4X3_types[639])
      ->set_attributes({new attribute(strings[2916],
                                      new named_type(IFC4X3_types[574]), true),
                        new attribute(strings[2886],
                                      new named_type(IFC4X3_types[1178]), true),
                        new attribute(strings[3290],
                                      new named_type(IFC4X3_types[637]), false),
                        new attribute(strings[3291],
                                      new named_type(IFC4X3_types[698]), true),
                        new attribute(strings[2921],
                                      new named_type(IFC4X3_types[574]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X3_types[640])
      ->set_attributes({new attribute(strings[2916],
                                      new named_type(IFC4X3_types[574]), true),
                        new attribute(strings[2886],
                                      new named_type(IFC4X3_types[1178]), true),
                        new attribute(strings[3292],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X3_types[639])),
                                      true)},
                       {false, false, false});
  ((entity *)IFC4X3_types[641])->set_attributes({}, {});
  ((entity *)IFC4X3_types[642])
      ->set_attributes(
          {new attribute(strings[3293], new named_type(IFC4X3_types[637]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X3_types[643])
      ->set_attributes({new attribute(strings[3290],
                                      new named_type(IFC4X3_types[637]), true),
                        new attribute(strings[3294],
                                      new named_type(IFC4X3_types[697]), false),
                        new attribute(strings[3295],
                                      new named_type(IFC4X3_types[617]), true),
                        new attribute(strings[2916],
                                      new named_type(IFC4X3_types[574]), true),
                        new attribute(strings[2886],
                                      new named_type(IFC4X3_types[1178]), true),
                        new attribute(strings[2921],
                                      new named_type(IFC4X3_types[574]), true),
                        new attribute(strings[3296],
                                      new named_type(IFC4X3_types[552]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[644])
      ->set_attributes(
          {new attribute(
               strings[3297],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X3_types[643])),
               false),
           new attribute(strings[3298], new named_type(IFC4X3_types[574]),
                         true),
           new attribute(strings[2886], new named_type(IFC4X3_types[1178]),
                         true)},
          {false, false, false});
  ((entity *)IFC4X3_types[645])
      ->set_attributes({new attribute(strings[3299],
                                      new named_type(IFC4X3_types[644]), false),
                        new attribute(strings[3300],
                                      new named_type(IFC4X3_types[584]), false),
                        new attribute(strings[3301],
                                      new named_type(IFC4X3_types[307]), false),
                        new attribute(strings[3302],
                                      new named_type(IFC4X3_types[585]), false),
                        new attribute(strings[3303],
                                      new named_type(IFC4X3_types[778]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X3_types[646])
      ->set_attributes(
          {new attribute(strings[3304], new named_type(IFC4X3_types[584]),
                         false),
           new attribute(
               strings[3305],
               new aggregation_type(aggregation_type::array_type, 1, 2,
                                    new named_type(IFC4X3_types[585])),
               false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[647])
      ->set_attributes({new attribute(strings[3306],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X3_types[637])),
                                      false)},
                       {false});
  ((entity *)IFC4X3_types[648])
      ->set_attributes({new attribute(strings[2916],
                                      new named_type(IFC4X3_types[574]), true),
                        new attribute(strings[2886],
                                      new named_type(IFC4X3_types[1178]), true),
                        new attribute(strings[3290],
                                      new named_type(IFC4X3_types[637]), true),
                        new attribute(strings[3307],
                                      new named_type(IFC4X3_types[806]), false),
                        new attribute(strings[3296],
                                      new named_type(IFC4X3_types[552]), true),
                        new attribute(strings[2921],
                                      new named_type(IFC4X3_types[574]), true)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[649])
      ->set_attributes({new attribute(strings[2916],
                                      new named_type(IFC4X3_types[574]), true),
                        new attribute(strings[2886],
                                      new named_type(IFC4X3_types[1178]), true),
                        new attribute(strings[3308],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X3_types[648])),
                                      false),
                        new attribute(strings[3309],
                                      new named_type(IFC4X3_types[196]), true)},
                       {false, false, false, false});
  ((entity *)IFC4X3_types[650])
      ->set_attributes({new attribute(strings[3310],
                                      new named_type(IFC4X3_types[649]), false),
                        new attribute(strings[3311],
                                      new named_type(IFC4X3_types[146]), true),
                        new attribute(strings[3303],
                                      new named_type(IFC4X3_types[778]), true)},
                       {false, false, false});
  ((entity *)IFC4X3_types[651])
      ->set_attributes({new attribute(strings[3312],
                                      new named_type(IFC4X3_types[649]), false),
                        new attribute(strings[3313],
                                      new named_type(IFC4X3_types[146]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X3_types[652])
      ->set_attributes({new attribute(strings[3305],
                                      new aggregation_type(
                                          aggregation_type::array_type, 1, 2,
                                          new named_type(IFC4X3_types[585])),
                                      false)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[653])
      ->set_attributes(
          {new attribute(strings[3290], new named_type(IFC4X3_types[641]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X3_types[654])
      ->set_attributes({new attribute(strings[3314],
                                      new named_type(IFC4X3_types[637]), false),
                        new attribute(strings[3315],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X3_types[637])),
                                      false),
                        new attribute(strings[3316],
                                      new named_type(IFC4X3_types[574]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X3_types[656])->set_attributes({}, {});
  ((entity *)IFC4X3_types[658])
      ->set_attributes(
          {new attribute(strings[3317], new named_type(IFC4X3_types[1255]),
                         false),
           new attribute(strings[3318], new named_type(IFC4X3_types[1244]),
                         false)},
          {false, false});
  ((entity *)IFC4X3_types[659])
      ->set_attributes({new attribute(strings[3319],
                                      new named_type(IFC4X3_types[778]), true),
                        new attribute(strings[3320],
                                      new named_type(IFC4X3_types[778]), true),
                        new attribute(strings[2880],
                                      new named_type(IFC4X3_types[661]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X3_types[660])
      ->set_attributes({new attribute(strings[2880],
                                      new named_type(IFC4X3_types[661]), false),
                        new attribute(strings[3319],
                                      new named_type(IFC4X3_types[778]), true),
                        new attribute(strings[3320],
                                      new named_type(IFC4X3_types[778]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false});
  ((entity *)IFC4X3_types[662])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[664]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[663])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[664]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[665])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[667]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[666])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[667]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[668])
      ->set_attributes({new attribute(strings[3321],
                                      new named_type(IFC4X3_types[79]), false),
                        new attribute(strings[3322],
                                      new named_type(IFC4X3_types[574]), true),
                        new attribute(strings[3323],
                                      new named_type(IFC4X3_types[669]), true),
                        new attribute(strings[3324],
                                      new named_type(IFC4X3_types[880]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X3_types[670])
      ->set_attributes({}, {false, false, false, true, false});
  ((entity *)IFC4X3_types[671])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[673]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[672])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[673]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[685])
      ->set_attributes(
          {new attribute(strings[3325], new named_type(IFC4X3_types[574]),
                         false)},
          {false});
  ((entity *)IFC4X3_types[687])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[689]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[688])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[689]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[690])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[692]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[691])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[692]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[693])
      ->set_attributes(
          {new attribute(strings[3326], new named_type(IFC4X3_types[304]),
                         false),
           new attribute(strings[3107], new named_type(IFC4X3_types[1252]),
                         false)},
          {false, false});
  ((entity *)IFC4X3_types[694])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[696]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[695])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[696]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[700])
      ->set_attributes({new attribute(strings[3069],
                                      new named_type(IFC4X3_types[574]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X3_types[701])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X3_types[704])
      ->set_attributes({new attribute(strings[3327],
                                      new named_type(IFC4X3_types[704]), true)},
                       {false});
  ((entity *)IFC4X3_types[702])
      ->set_attributes({new attribute(strings[3328],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X3_types[213])),
                                      true),
                        new attribute(strings[3329],
                                      new named_type(IFC4X3_types[618]), true),
                        new attribute(strings[3330],
                                      new named_type(IFC4X3_types[703]), false),
                        new attribute(strings[3331],
                                      new named_type(IFC4X3_types[574]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X3_types[707])
      ->set_attributes({new attribute(strings[2880],
                                      new named_type(IFC4X3_types[708]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[709])
      ->set_attributes(
          {new attribute(strings[3332], new named_type(IFC4X3_types[272]),
                         false)},
          {false});
  ((entity *)IFC4X3_types[710])
      ->set_attributes(
          {new attribute(strings[3333], new named_type(IFC4X3_types[585]),
                         false),
           new attribute(strings[2963], new named_type(IFC4X3_types[617]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X3_types[711])
      ->set_attributes(
          {new attribute(strings[3333], new named_type(IFC4X3_types[585]),
                         false),
           new attribute(strings[2963], new named_type(IFC4X3_types[617]),
                         false),
           new attribute(strings[2958], new named_type(IFC4X3_types[306]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X3_types[712])
      ->set_attributes({new attribute(strings[3305],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X3_types[766])),
                                      false),
                        new attribute(strings[3165],
                                      new named_type(IFC4X3_types[574]), true)},
                       {false, false, false});
  ((entity *)IFC4X3_types[713])
      ->set_attributes({new attribute(strings[3334],
                                      new named_type(IFC4X3_types[87]), false),
                        new attribute(strings[3335],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X3_types[697])),
                                      false),
                        new attribute(strings[3336],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X3_types[761])),
                                      false),
                        new attribute(strings[3337],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, -1,
                                          new named_type(IFC4X3_types[574])),
                                      true),
                        new attribute(strings[3338],
                                      new named_type(IFC4X3_types[147]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[716])->set_attributes({}, {false});
  ((entity *)IFC4X3_types[714])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[715]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[717])
      ->set_attributes({new attribute(strings[2936],
                                      new named_type(IFC4X3_types[538]), true),
                        new attribute(strings[2916],
                                      new named_type(IFC4X3_types[574]), false),
                        new attribute(strings[2886],
                                      new named_type(IFC4X3_types[1178]), true),
                        new attribute(strings[3339],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X3_types[7])),
                                      true),
                        new attribute(strings[3340],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X3_types[12])),
                                      true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X3_types[718])
      ->set_attributes({new attribute(strings[3341],
                                      new named_type(IFC4X3_types[717]), false),
                        new attribute(strings[3342],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X3_types[717])),
                                      false)},
                       {false, false, false, false});
  ((entity *)IFC4X3_types[719])
      ->set_attributes({new attribute(strings[3343],
                                      new named_type(IFC4X3_types[365]), false),
                        new attribute(strings[3187],
                                      new named_type(IFC4X3_types[87]), false)},
                       {true, true, false, false});
  ((entity *)IFC4X3_types[720])->set_attributes({}, {false, false});
  ((entity *)IFC4X3_types[721])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[723]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[722])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[723]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[724])
      ->set_attributes(
          {new attribute(strings[3344], new named_type(IFC4X3_types[739]),
                         false),
           new attribute(strings[3345], new named_type(IFC4X3_types[49]),
                         false),
           new attribute(strings[3346], new named_type(IFC4X3_types[1073]),
                         true),
           new attribute(strings[3347], new named_type(IFC4X3_types[157]),
                         true),
           new attribute(strings[3348], new named_type(IFC4X3_types[1212]),
                         true),
           new attribute(strings[3349], new named_type(IFC4X3_types[739]),
                         true),
           new attribute(strings[3350], new named_type(IFC4X3_types[49]), true),
           new attribute(strings[3351], new named_type(IFC4X3_types[1212]),
                         false)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[725])
      ->set_attributes({new attribute(strings[3048],
                                      new named_type(IFC4X3_types[69]), true)},
                       {false, false, false});
  ((entity *)IFC4X3_types[727])
      ->set_attributes({new attribute(strings[3164],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X3_types[719])),
                                      false)},
                       {false});
  ((entity *)IFC4X3_types[728])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[730]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[729])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[730]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[731])
      ->set_attributes(
          {new attribute(strings[3091], new named_type(IFC4X3_types[1123]),
                         false),
           new attribute(strings[3352], new named_type(IFC4X3_types[272]),
                         false)},
          {false, false});
  ((entity *)IFC4X3_types[732])
      ->set_attributes(
          {new attribute(strings[3353], new named_type(IFC4X3_types[574]),
                         false),
           new attribute(strings[2880], new named_type(IFC4X3_types[733]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[735])
      ->set_attributes(
          {new attribute(strings[3141], new named_type(IFC4X3_types[734]),
                         false),
           new attribute(strings[3159], new named_type(IFC4X3_types[1294]),
                         false),
           new attribute(strings[3354], new named_type(IFC4X3_types[778]),
                         true),
           new attribute(strings[3355], new named_type(IFC4X3_types[778]),
                         true),
           new attribute(strings[3153], new named_type(IFC4X3_types[1006]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[736])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[737]),
                         true),
           new attribute(strings[2881], new named_type(IFC4X3_types[574]),
                         true),
           new attribute(strings[2882], new named_type(IFC4X3_types[1178]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[738])
      ->set_attributes(
          {new attribute(strings[2936], new named_type(IFC4X3_types[538]),
                         true),
           new attribute(strings[3356], new named_type(IFC4X3_types[574]),
                         true),
           new attribute(strings[3357], new named_type(IFC4X3_types[574]),
                         true),
           new attribute(
               strings[3358],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X3_types[574])),
               true),
           new attribute(
               strings[3359],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X3_types[574])),
               true),
           new attribute(
               strings[3360],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X3_types[574])),
               true),
           new attribute(strings[3339],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4X3_types[7])),
                         true),
           new attribute(strings[3340],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4X3_types[12])),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[739])
      ->set_attributes({new attribute(strings[3361],
                                      new named_type(IFC4X3_types[738]), false),
                        new attribute(strings[3362],
                                      new named_type(IFC4X3_types[717]), false),
                        new attribute(strings[3339],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X3_types[7])),
                                      true)},
                       {false, false, false});
  ((entity *)IFC4X3_types[741])
      ->set_attributes({new attribute(strings[3363],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X3_types[743])),
                                      false),
                        new attribute(strings[3364],
                                      new named_type(IFC4X3_types[574]), false),
                        new attribute(strings[3365],
                                      new named_type(IFC4X3_types[574]), true),
                        new attribute(strings[3066],
                                      new named_type(IFC4X3_types[574]), true)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[743])
      ->set_attributes(
          {new attribute(strings[2916], new named_type(IFC4X3_types[574]),
                         false),
           new attribute(strings[2886], new named_type(IFC4X3_types[1178]),
                         true)},
          {false, false});
  ((entity *)IFC4X3_types[744])
      ->set_attributes({new attribute(strings[3109],
                                      new named_type(IFC4X3_types[693]), true)},
                       {false, false, false});
  ((entity *)IFC4X3_types[745])
      ->set_attributes({new attribute(strings[2880],
                                      new named_type(IFC4X3_types[748]), true),
                        new attribute(strings[3366],
                                      new named_type(IFC4X3_types[746]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X3_types[747])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[748]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[749])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[751]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[750])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[751]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[752])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[754]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[753])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[754]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[755])
      ->set_attributes(
          {new attribute(strings[3011], new named_type(IFC4X3_types[552]),
                         false),
           new attribute(strings[3367], new named_type(IFC4X3_types[552]),
                         false),
           new attribute(strings[3368], new named_type(IFC4X3_types[552]),
                         false),
           new attribute(strings[3369],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4X3_types[81])),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[756])
      ->set_attributes(
          {new attribute(strings[3124], new named_type(IFC4X3_types[765]),
                         false)},
          {false});
  ((entity *)IFC4X3_types[757])
      ->set_attributes({new attribute(strings[3094],
                                      new named_type(IFC4X3_types[68]), false)},
                       {false, false, false});
  ((entity *)IFC4X3_types[758])
      ->set_attributes(
          {new attribute(strings[3370], new named_type(IFC4X3_types[585]),
                         false),
           new attribute(strings[3371], new named_type(IFC4X3_types[585]),
                         false)},
          {false, false});
  ((entity *)IFC4X3_types[760])->set_attributes({}, {false});
  ((entity *)IFC4X3_types[762])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[764]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[763])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[764]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[765])->set_attributes({}, {});
  ((entity *)IFC4X3_types[766])
      ->set_attributes(
          {new attribute(strings[3372], new named_type(IFC4X3_types[277]),
                         false),
           new attribute(strings[3373], new named_type(IFC4X3_types[585]),
                         true),
           new attribute(strings[3374], new named_type(IFC4X3_types[585]),
                         true),
           new attribute(strings[3375], new named_type(IFC4X3_types[585]),
                         true),
           new attribute(strings[3332], new named_type(IFC4X3_types[272]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC4X3_types[767])
      ->set_attributes(
          {new attribute(strings[3332], new named_type(IFC4X3_types[272]),
                         false),
           new attribute(strings[3376], new named_type(IFC4X3_types[726]),
                         false)},
          {false, false});
  ((entity *)IFC4X3_types[768])
      ->set_attributes(
          {new attribute(strings[3091], new named_type(IFC4X3_types[1123]),
                         false),
           new attribute(strings[3377], new named_type(IFC4X3_types[726]),
                         false),
           new attribute(strings[3378], new named_type(IFC4X3_types[726]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X3_types[773])
      ->set_attributes({new attribute(strings[3379],
                                      new aggregation_type(
                                          aggregation_type::list_type, 3, -1,
                                          new named_type(IFC4X3_types[147])),
                                      false)},
                       {false});
  ((entity *)IFC4X3_types[770])
      ->set_attributes({new attribute(strings[3048],
                                      new named_type(IFC4X3_types[70]), false),
                        new attribute(strings[3380],
                                      new named_type(IFC4X3_types[99]), false)},
                       {false, false, false, false});
  ((entity *)IFC4X3_types[771])
      ->set_attributes({new attribute(strings[3381],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X3_types[546])),
                                      false),
                        new attribute(strings[3382],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X3_types[777])),
                                      true)},
                       {false, false, false, false});
  ((entity *)IFC4X3_types[772])
      ->set_attributes({new attribute(strings[3234],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, -1,
                                          new named_type(IFC4X3_types[147])),
                                      false)},
                       {false});
  ((entity *)IFC4X3_types[774])
      ->set_attributes({new attribute(strings[3048],
                                      new named_type(IFC4X3_types[756]), false),
                        new attribute(strings[3383],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, -1,
                                          new named_type(IFC4X3_types[873])),
                                      true),
                        new attribute(strings[3384],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, -1,
                                          new named_type(IFC4X3_types[873])),
                                      true),
                        new attribute(strings[3385],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, -1,
                                          new named_type(IFC4X3_types[873])),
                                      true)},
                       {false, false, false, false});
  ((entity *)IFC4X3_types[775])
      ->set_attributes({}, {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[776])
      ->set_attributes({}, {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[781])
      ->set_attributes({new attribute(strings[3386],
                                      new named_type(IFC4X3_types[574]), true),
                        new attribute(strings[3387],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X3_types[574])),
                                      true),
                        new attribute(strings[3388],
                                      new named_type(IFC4X3_types[574]), true),
                        new attribute(strings[3389],
                                      new named_type(IFC4X3_types[574]), true),
                        new attribute(strings[3390],
                                      new named_type(IFC4X3_types[574]), true),
                        new attribute(strings[3391],
                                      new named_type(IFC4X3_types[574]), true),
                        new attribute(strings[3392],
                                      new named_type(IFC4X3_types[574]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X3_types[783])->set_attributes({}, {false});
  ((entity *)IFC4X3_types[784])->set_attributes({}, {false});
  ((entity *)IFC4X3_types[785])
      ->set_attributes(
          {new attribute(strings[2916], new named_type(IFC4X3_types[574]),
                         false)},
          {false});
  ((entity *)IFC4X3_types[786])->set_attributes({}, {});
  ((entity *)IFC4X3_types[787])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X3_types[788])->set_attributes({}, {false});
  ((entity *)IFC4X3_types[791])->set_attributes({}, {});
  ((entity *)IFC4X3_types[792])
      ->set_attributes({new attribute(strings[2916],
                                      new named_type(IFC4X3_types[574]), false),
                        new attribute(strings[2886],
                                      new named_type(IFC4X3_types[1178]), true),
                        new attribute(strings[3393],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X3_types[583])),
                                      false),
                        new attribute(strings[2925],
                                      new named_type(IFC4X3_types[538]), true)},
                       {false, false, false, false});
  ((entity *)IFC4X3_types[793])
      ->set_attributes(
          {new attribute(strings[3394], new named_type(IFC4X3_types[617]),
                         false),
           new attribute(strings[3395], new named_type(IFC4X3_types[617]),
                         false),
           new attribute(strings[3396], new named_type(IFC4X3_types[617]),
                         false),
           new attribute(
               strings[3397],
               new aggregation_type(aggregation_type::set_type, 0, -1,
                                    new named_type(IFC4X3_types[794])),
               false)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[794])
      ->set_attributes({new attribute(strings[2916],
                                      new named_type(IFC4X3_types[574]), true)},
                       {false});
  ((entity *)IFC4X3_types[796])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[798]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[797])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[798]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[799])
      ->set_attributes(
          {new attribute(strings[2936], new named_type(IFC4X3_types[538]),
                         true),
           new attribute(strings[2882], new named_type(IFC4X3_types[1178]),
                         true)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[801])
      ->set_attributes({new attribute(strings[3398],
                                      new named_type(IFC4X3_types[704]), true),
                        new attribute(strings[3399],
                                      new named_type(IFC4X3_types[803]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[802])->set_attributes({}, {false, false, false});
  ((entity *)IFC4X3_types[803])
      ->set_attributes({new attribute(strings[2916],
                                      new named_type(IFC4X3_types[574]), true),
                        new attribute(strings[2886],
                                      new named_type(IFC4X3_types[1178]), true),
                        new attribute(strings[3400],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X3_types[951])),
                                      false)},
                       {false, false, false});
  ((entity *)IFC4X3_types[806])
      ->set_attributes({new attribute(strings[3401],
                                      new named_type(IFC4X3_types[808]), false),
                        new attribute(strings[3402],
                                      new named_type(IFC4X3_types[574]), true)},
                       {false, false});
  ((entity *)IFC4X3_types[807])
      ->set_attributes(
          {new attribute(strings[3403], new named_type(IFC4X3_types[806]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X3_types[809])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[814])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[815])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[816]),
                         true),
           new attribute(strings[2881], new named_type(IFC4X3_types[574]),
                         true),
           new attribute(strings[2882], new named_type(IFC4X3_types[1178]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[810])
      ->set_attributes({new attribute(strings[3404],
                                      new named_type(IFC4X3_types[538]), true),
                        new attribute(strings[3405],
                                      new named_type(IFC4X3_types[538]), true),
                        new attribute(strings[3406],
                                      new named_type(IFC4X3_types[693]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[812])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[813]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[817])
      ->set_attributes(
          {new attribute(strings[2916], new named_type(IFC4X3_types[538]),
                         false),
           new attribute(strings[3030], new named_type(IFC4X3_types[1178]),
                         true)},
          {false, false});
  ((entity *)IFC4X3_types[818])->set_attributes({}, {});
  ((entity *)IFC4X3_types[819])
      ->set_attributes(
          {new attribute(strings[3407], new named_type(IFC4X3_types[1255]),
                         true),
           new attribute(strings[3408], new named_type(IFC4X3_types[1255]),
                         true),
           new attribute(strings[3109], new named_type(IFC4X3_types[1244]),
                         true),
           new attribute(strings[3409], new named_type(IFC4X3_types[1255]),
                         true)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[820])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X3_types[821])
      ->set_attributes(
          {new attribute(strings[3410], new named_type(IFC4X3_types[817]),
                         false),
           new attribute(strings[3411], new named_type(IFC4X3_types[817]),
                         false),
           new attribute(strings[3412], new named_type(IFC4X3_types[1178]),
                         true)},
          {false, false, false, false, false});
  ((entity *)IFC4X3_types[822])
      ->set_attributes({new attribute(strings[3413],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X3_types[1255])),
                                      true),
                        new attribute(strings[3414],
                                      new named_type(IFC4X3_types[823]), true)},
                       {false, false, false, false});
  ((entity *)IFC4X3_types[823])
      ->set_attributes(
          {new attribute(strings[2916], new named_type(IFC4X3_types[574]),
                         false),
           new attribute(
               strings[3413],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X3_types[1255])),
               false),
           new attribute(strings[3109], new named_type(IFC4X3_types[1244]),
                         true)},
          {false, false, false});
  ((entity *)IFC4X3_types[824])
      ->set_attributes(
          {new attribute(
               strings[3245],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X3_types[1255])),
               true),
           new attribute(strings[3109], new named_type(IFC4X3_types[1244]),
                         true)},
          {false, false, false, false});
  ((entity *)IFC4X3_types[825])
      ->set_attributes({new attribute(strings[3039],
                                      new named_type(IFC4X3_types[1178]), true),
                        new attribute(strings[3415],
                                      new named_type(IFC4X3_types[705]), true)},
                       {false, false, false, false});
  ((entity *)IFC4X3_types[826])
      ->set_attributes({new attribute(strings[3040],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X3_types[817])),
                                      false)},
                       {false, false, false, false, false});
  ((entity *)IFC4X3_types[827])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X3_types[830])
      ->set_attributes({new attribute(strings[3041],
                                      new named_type(IFC4X3_types[831]), true),
                        new attribute(strings[3416],
                                      new named_type(IFC4X3_types[538]), true),
                        new attribute(strings[3042],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X3_types[834])),
                                      false)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[832])
      ->set_attributes(
          {new attribute(strings[3417], new named_type(IFC4X3_types[1255]),
                         true),
           new attribute(strings[3109], new named_type(IFC4X3_types[1244]),
                         true)},
          {false, false, false, false});
  ((entity *)IFC4X3_types[833])
      ->set_attributes(
          {new attribute(
               strings[3418],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X3_types[1255])),
               true),
           new attribute(
               strings[3419],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X3_types[1255])),
               true),
           new attribute(strings[3412], new named_type(IFC4X3_types[1178]),
                         true),
           new attribute(strings[3420], new named_type(IFC4X3_types[1244]),
                         true),
           new attribute(strings[3421], new named_type(IFC4X3_types[1244]),
                         true),
           new attribute(strings[3422], new named_type(IFC4X3_types[276]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[834])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X3_types[835])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X3_types[836])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[841]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[837])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[839]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[838])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[839]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[840])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[841]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[842])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[844]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[843])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[844]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[845])
      ->set_attributes({new attribute(strings[3423],
                                      new named_type(IFC4X3_types[59]), false),
                        new attribute(strings[3424],
                                      new named_type(IFC4X3_types[574]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X3_types[846])
      ->set_attributes({new attribute(strings[3425],
                                      new named_type(IFC4X3_types[253]), false),
                        new attribute(strings[3424],
                                      new named_type(IFC4X3_types[574]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X3_types[847])
      ->set_attributes({new attribute(strings[3426],
                                      new named_type(IFC4X3_types[585]), false),
                        new attribute(strings[3424],
                                      new named_type(IFC4X3_types[574]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X3_types[848])
      ->set_attributes({new attribute(strings[3427],
                                      new named_type(IFC4X3_types[699]), false),
                        new attribute(strings[3424],
                                      new named_type(IFC4X3_types[574]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X3_types[849])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X3_types[850])
      ->set_attributes(
          {new attribute(strings[3428], new named_type(IFC4X3_types[1206]),
                         false),
           new attribute(strings[3424], new named_type(IFC4X3_types[574]),
                         true)},
          {false, false, false, false, false});
  ((entity *)IFC4X3_types[851])
      ->set_attributes(
          {new attribute(strings[3429], new named_type(IFC4X3_types[1279]),
                         false),
           new attribute(strings[3424], new named_type(IFC4X3_types[574]),
                         true)},
          {false, false, false, false, false});
  ((entity *)IFC4X3_types[852])
      ->set_attributes({new attribute(strings[3430],
                                      new named_type(IFC4X3_types[635]), false),
                        new attribute(strings[3424],
                                      new named_type(IFC4X3_types[574]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X3_types[854])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[859]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[858])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[859]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[855])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[857]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[856])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[857]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[860])
      ->set_attributes({new attribute(strings[2880],
                                      new named_type(IFC4X3_types[863]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X3_types[861])
      ->set_attributes({new attribute(strings[2880],
                                      new named_type(IFC4X3_types[862]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X3_types[864])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[869]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[865])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[867]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[866])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[867]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[868])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[869]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[871])
      ->set_attributes(
          {new attribute(
              strings[3431],
              new aggregation_type(aggregation_type::list_type, 2, -1,
                                   new named_type(IFC4X3_types[873])),
              false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[872])
      ->set_attributes(
          {new attribute(
              strings[3431],
              new aggregation_type(
                  aggregation_type::list_type, 2, -1,
                  new aggregation_type(aggregation_type::list_type, 2, -1,
                                       new named_type(IFC4X3_types[873]))),
              false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false});
  ((entity *)IFC4X3_types[874])
      ->set_attributes(
          {new attribute(strings[3012], new named_type(IFC4X3_types[778]),
                         false),
           new attribute(strings[3432], new named_type(IFC4X3_types[697]),
                         true),
           new attribute(strings[3433], new named_type(IFC4X3_types[697]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[875])
      ->set_attributes(
          {new attribute(strings[3001], new named_type(IFC4X3_types[778]),
                         false),
           new attribute(strings[3002], new named_type(IFC4X3_types[778]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC4X3_types[876])
      ->set_attributes(
          {new attribute(strings[2978], new named_type(IFC4X3_types[778]),
                         false),
           new attribute(strings[2979], new named_type(IFC4X3_types[778]),
                         false),
           new attribute(strings[3367], new named_type(IFC4X3_types[778]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X3_types[877])
      ->set_attributes(
          {new attribute(strings[3091], new named_type(IFC4X3_types[1123]),
                         false),
           new attribute(strings[3434], new named_type(IFC4X3_types[726]),
                         false),
           new attribute(strings[3435], new named_type(IFC4X3_types[726]),
                         false),
           new attribute(strings[3436], new named_type(IFC4X3_types[726]),
                         false),
           new attribute(strings[3437], new named_type(IFC4X3_types[726]),
                         false),
           new attribute(strings[3438], new named_type(IFC4X3_types[87]),
                         false),
           new attribute(strings[3439], new named_type(IFC4X3_types[87]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[878])
      ->set_attributes(
          {new attribute(strings[3440], new named_type(IFC4X3_types[879]),
                         false),
           new attribute(
               strings[3441],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X3_types[293])),
               true),
           new attribute(
               strings[3442],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X3_types[294])),
               true),
           new attribute(
               strings[3443],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X3_types[686])),
               true),
           new attribute(strings[3048], new named_type(IFC4X3_types[552]),
                         true),
           new attribute(strings[3444], new named_type(IFC4X3_types[552]),
                         true),
           new attribute(strings[3445], new named_type(IFC4X3_types[552]),
                         true),
           new attribute(
               strings[3446],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X3_types[1208])),
               true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[880])
      ->set_attributes({new attribute(strings[3447],
                                      new named_type(IFC4X3_types[538]), true),
                        new attribute(strings[3448],
                                      new named_type(IFC4X3_types[538]), true),
                        new attribute(strings[3449],
                                      new named_type(IFC4X3_types[574]), true),
                        new attribute(strings[3450],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X3_types[552])),
                                      true),
                        new attribute(strings[3451],
                                      new named_type(IFC4X3_types[880]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X3_types[881])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[882]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[884])
      ->set_attributes(
          {new attribute(strings[3452], new named_type(IFC4X3_types[1206]),
                         false),
           new attribute(
               strings[3243],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X3_types[1211])),
               false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[885])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[886]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[887])
      ->set_attributes({new attribute(strings[3453],
                                      new named_type(IFC4X3_types[59]), false),
                        new attribute(strings[3454],
                                      new named_type(IFC4X3_types[574]), false),
                        new attribute(strings[3455],
                                      new named_type(IFC4X3_types[891]), true),
                        new attribute(strings[3456],
                                      new named_type(IFC4X3_types[585]), true),
                        new attribute(strings[3457],
                                      new named_type(IFC4X3_types[778]), true),
                        new attribute(strings[3458],
                                      new named_type(IFC4X3_types[253]), true)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[888])
      ->set_attributes({new attribute(strings[3459],
                                      new named_type(IFC4X3_types[574]), true),
                        new attribute(strings[3460],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X3_types[993])),
                                      false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[889])
      ->set_attributes(
          {new attribute(strings[3319], new named_type(IFC4X3_types[778]),
                         true),
           new attribute(strings[3461], new named_type(IFC4X3_types[59]), true),
           new attribute(strings[3462], new named_type(IFC4X3_types[778]),
                         true),
           new attribute(strings[2880], new named_type(IFC4X3_types[893]),
                         true),
           new attribute(strings[3455], new named_type(IFC4X3_types[891]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false});
  ((entity *)IFC4X3_types[892])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[893]),
                         false),
           new attribute(strings[3319], new named_type(IFC4X3_types[778]),
                         true),
           new attribute(strings[3461], new named_type(IFC4X3_types[59]), true),
           new attribute(strings[3462], new named_type(IFC4X3_types[778]),
                         true),
           new attribute(strings[3455], new named_type(IFC4X3_types[891]),
                         true),
           new attribute(strings[3463], new named_type(IFC4X3_types[574]),
                         true),
           new attribute(strings[3464],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4X3_types[80])),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false});
  ((entity *)IFC4X3_types[894])
      ->set_attributes(
          {new attribute(strings[3454], new named_type(IFC4X3_types[574]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[895])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[896])
      ->set_attributes(
          {new attribute(strings[3465], new named_type(IFC4X3_types[778]),
                         true),
           new attribute(strings[3466], new named_type(IFC4X3_types[778]),
                         true),
           new attribute(strings[3467], new named_type(IFC4X3_types[778]),
                         true),
           new attribute(strings[3468], new named_type(IFC4X3_types[778]),
                         true),
           new attribute(strings[3469], new named_type(IFC4X3_types[59]), true),
           new attribute(strings[3470], new named_type(IFC4X3_types[59]), true),
           new attribute(strings[3471], new named_type(IFC4X3_types[778]),
                         true),
           new attribute(strings[3472], new named_type(IFC4X3_types[778]),
                         true),
           new attribute(strings[2880], new named_type(IFC4X3_types[898]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[897])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[898]),
                         false),
           new attribute(strings[3465], new named_type(IFC4X3_types[778]),
                         true),
           new attribute(strings[3466], new named_type(IFC4X3_types[778]),
                         true),
           new attribute(strings[3467], new named_type(IFC4X3_types[778]),
                         true),
           new attribute(strings[3468], new named_type(IFC4X3_types[778]),
                         true),
           new attribute(strings[3469], new named_type(IFC4X3_types[59]), true),
           new attribute(strings[3470], new named_type(IFC4X3_types[59]), true),
           new attribute(strings[3471], new named_type(IFC4X3_types[778]),
                         true),
           new attribute(strings[3472], new named_type(IFC4X3_types[778]),
                         true),
           new attribute(strings[3463], new named_type(IFC4X3_types[574]),
                         true),
           new attribute(strings[3464],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4X3_types[80])),
                         true)},
          {false, false, false, false, false, false, false,
           false, false, false, false, false, false, false,
           false, false, false, false, false, false});
  ((entity *)IFC4X3_types[899])
      ->set_attributes({new attribute(strings[3473],
                                      new named_type(IFC4X3_types[395]), false),
                        new attribute(strings[3474],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X3_types[1126])),
                                      false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[900])
      ->set_attributes({new attribute(strings[3475],
                                      new named_type(IFC4X3_types[701]), false),
                        new attribute(strings[3476],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X3_types[701])),
                                      false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[901])
      ->set_attributes({new attribute(strings[3476],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X3_types[701])),
                                      false),
                        new attribute(strings[3477],
                                      new named_type(IFC4X3_types[706]), true)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[902])
      ->set_attributes(
          {new attribute(strings[3478], new named_type(IFC4X3_types[6]), false),
           new attribute(strings[3479], new named_type(IFC4X3_types[7]), true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[903])
      ->set_attributes(
          {new attribute(strings[3480], new named_type(IFC4X3_types[229]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[904])
      ->set_attributes(
          {new attribute(strings[3481], new named_type(IFC4X3_types[527]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[905])
      ->set_attributes(
          {new attribute(strings[3482], new named_type(IFC4X3_types[870]),
                         false)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[906])
      ->set_attributes(
          {new attribute(strings[3483], new named_type(IFC4X3_types[800]),
                         false),
           new attribute(strings[3484], new named_type(IFC4X3_types[658]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[907])
      ->set_attributes(
          {new attribute(strings[3485], new named_type(IFC4X3_types[805]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[908])
      ->set_attributes(
          {new attribute(strings[3486], new named_type(IFC4X3_types[960]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[909])
      ->set_attributes({new attribute(strings[3476],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X3_types[297])),
                                      false)},
                       {false, false, false, false, false});
  ((entity *)IFC4X3_types[910])
      ->set_attributes({new attribute(strings[2931],
                                      new named_type(IFC4X3_types[52]), false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[911])
      ->set_attributes(
          {new attribute(strings[3487], new named_type(IFC4X3_types[172]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[912])
      ->set_attributes(
          {new attribute(strings[3488], new named_type(IFC4X3_types[574]),
                         true),
           new attribute(strings[3489], new named_type(IFC4X3_types[213]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[913])
      ->set_attributes(
          {new attribute(strings[3135], new named_type(IFC4X3_types[334]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[914])
      ->set_attributes(
          {new attribute(strings[3490], new named_type(IFC4X3_types[588]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[915])
      ->set_attributes(
          {new attribute(strings[3314], new named_type(IFC4X3_types[655]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[916])
      ->set_attributes(
          {new attribute(strings[3491], new named_type(IFC4X3_types[806]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[918])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X3_types[919])
      ->set_attributes(
          {new attribute(strings[3492], new named_type(IFC4X3_types[207]),
                         true),
           new attribute(strings[3473], new named_type(IFC4X3_types[395]),
                         false),
           new attribute(strings[3493], new named_type(IFC4X3_types[395]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[920])
      ->set_attributes(
          {new attribute(
               strings[3494],
               new aggregation_type(aggregation_type::list_type, 0, -1,
                                    new named_type(IFC4X3_types[552])),
               false),
           new attribute(
               strings[3495],
               new aggregation_type(aggregation_type::list_type, 0, -1,
                                    new named_type(IFC4X3_types[552])),
               false),
           new attribute(strings[3496], new named_type(IFC4X3_types[211]),
                         false),
           new attribute(strings[3497], new named_type(IFC4X3_types[211]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[922])
      ->set_attributes(
          {new attribute(strings[3498], new named_type(IFC4X3_types[775]),
                         false),
           new attribute(strings[3493], new named_type(IFC4X3_types[322]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[921])
      ->set_attributes({new attribute(strings[3498],
                                      new named_type(IFC4X3_types[775]), false),
                        new attribute(strings[3499],
                                      new named_type(IFC4X3_types[775]), false),
                        new attribute(strings[3500],
                                      new named_type(IFC4X3_types[395]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[923])
      ->set_attributes(
          {new attribute(strings[3473], new named_type(IFC4X3_types[1076]),
                         false),
           new attribute(strings[3501], new named_type(IFC4X3_types[1075]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[924])
      ->set_attributes(
          {new attribute(strings[3502], new named_type(IFC4X3_types[1102]),
                         false),
           new attribute(strings[3503], new named_type(IFC4X3_types[1078]),
                         false),
           new attribute(strings[3504], new named_type(IFC4X3_types[93]), true),
           new attribute(strings[3505], new named_type(IFC4X3_types[1079]),
                         true),
           new attribute(strings[3506], new named_type(IFC4X3_types[585]),
                         true),
           new attribute(strings[3507], new named_type(IFC4X3_types[70]),
                         true)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[925])
      ->set_attributes(
          {new attribute(strings[3508], new named_type(IFC4X3_types[207]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[926])
      ->set_attributes(
          {new attribute(
               strings[3509],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X3_types[395])),
               false),
           new attribute(strings[3510], new named_type(IFC4X3_types[574]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[927])
      ->set_attributes(
          {new attribute(
               strings[3511],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X3_types[801])),
               false),
           new attribute(strings[3512], new named_type(IFC4X3_types[1049]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[928])
      ->set_attributes({new attribute(strings[3513],
                                      new named_type(IFC4X3_types[395]), false),
                        new attribute(strings[3514],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X3_types[257])),
                                      false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[929])
      ->set_attributes(
          {new attribute(strings[3515], new named_type(IFC4X3_types[1042]),
                         false),
           new attribute(
               strings[3514],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X3_types[257])),
               false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[930])
      ->set_attributes({new attribute(strings[3516],
                                      new named_type(IFC4X3_types[226]), false),
                        new attribute(strings[3517],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X3_types[297])),
                                      false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[931])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X3_types[932])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X3_types[933])
      ->set_attributes(
          {new attribute(
               strings[3476],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X3_types[700])),
               false),
           new attribute(strings[3475], new named_type(IFC4X3_types[700]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[934])
      ->set_attributes(
          {new attribute(
               strings[3476],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X3_types[701])),
               false),
           new attribute(strings[3518], new named_type(IFC4X3_types[828]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[935])
      ->set_attributes(
          {new attribute(
               strings[3519],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X3_types[827])),
               false),
           new attribute(strings[3520], new named_type(IFC4X3_types[830]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[936])
      ->set_attributes(
          {new attribute(
               strings[3476],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X3_types[700])),
               false),
           new attribute(strings[3521], new named_type(IFC4X3_types[1240]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[937])
      ->set_attributes(
          {new attribute(strings[3522], new named_type(IFC4X3_types[714]),
                         false),
           new attribute(strings[3523], new named_type(IFC4X3_types[395]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[938])
      ->set_attributes(
          {new attribute(
               strings[3524],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X3_types[320])),
               false),
           new attribute(strings[3525], new named_type(IFC4X3_types[324]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[939])
      ->set_attributes(
          {new attribute(strings[3473], new named_type(IFC4X3_types[557]),
                         false),
           new attribute(strings[3493], new named_type(IFC4X3_types[557]),
                         false),
           new attribute(strings[3526], new named_type(IFC4X3_types[207]),
                         true),
           new attribute(strings[3527], new named_type(IFC4X3_types[1054]),
                         true),
           new attribute(strings[3528], new named_type(IFC4X3_types[538]),
                         true),
           new attribute(strings[3529], new named_type(IFC4X3_types[617]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[940])
      ->set_attributes({new attribute(strings[3475],
                                      new named_type(IFC4X3_types[701]), false),
                        new attribute(strings[3476],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X3_types[701])),
                                      false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[941])
      ->set_attributes({new attribute(strings[3530],
                                      new named_type(IFC4X3_types[776]), false),
                        new attribute(strings[3531],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X3_types[801])),
                                      false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[942])
      ->set_attributes(
          {new attribute(strings[3473], new named_type(IFC4X3_types[395]),
                         false),
           new attribute(strings[3532], new named_type(IFC4X3_types[456]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[943])
      ->set_attributes(
          {new attribute(
               strings[3511],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X3_types[1051])),
               false),
           new attribute(strings[3512], new named_type(IFC4X3_types[1049]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[944])
      ->set_attributes(
          {new attribute(strings[3483], new named_type(IFC4X3_types[799]),
                         false),
           new attribute(strings[3533], new named_type(IFC4X3_types[799]),
                         false),
           new attribute(strings[3534], new named_type(IFC4X3_types[578]),
                         true),
           new attribute(strings[3535], new named_type(IFC4X3_types[1001]),
                         true),
           new attribute(strings[3536], new named_type(IFC4X3_types[574]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[945])
      ->set_attributes(
          {new attribute(strings[3537], new named_type(IFC4X3_types[1148]),
                         false),
           new attribute(
               strings[3538],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X3_types[1049])),
               false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[946])
      ->set_attributes(
          {new attribute(strings[3515], new named_type(IFC4X3_types[1043]),
                         false),
           new attribute(strings[3523], new named_type(IFC4X3_types[395]),
                         false),
           new attribute(strings[3492], new named_type(IFC4X3_types[207]),
                         true),
           new attribute(strings[3539], new named_type(IFC4X3_types[742]),
                         false),
           new attribute(strings[3540], new named_type(IFC4X3_types[558]),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[947])
      ->set_attributes({new attribute(strings[3541],
                                      new named_type(IFC4X3_types[947]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X3_types[948])
      ->set_attributes({new attribute(strings[3542],
                                      new named_type(IFC4X3_types[948]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X3_types[949])
      ->set_attributes(
          {new attribute(strings[3513], new named_type(IFC4X3_types[395]),
                         false),
           new attribute(strings[3543], new named_type(IFC4X3_types[457]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[917])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X3_types[950])
      ->set_attributes(
          {new attribute(strings[3544], new named_type(IFC4X3_types[726]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X3_types[951])
      ->set_attributes({new attribute(strings[3545],
                                      new named_type(IFC4X3_types[952]), false),
                        new attribute(strings[3546],
                                      new named_type(IFC4X3_types[574]), true),
                        new attribute(strings[3547],
                                      new named_type(IFC4X3_types[574]), true),
                        new attribute(strings[3548],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X3_types[953])),
                                      false)},
                       {false, false, false, false});
  ((entity *)IFC4X3_types[952])
      ->set_attributes({new attribute(strings[3549],
                                      new named_type(IFC4X3_types[574]), true),
                        new attribute(strings[3550],
                                      new named_type(IFC4X3_types[574]), true)},
                       {false, false});
  ((entity *)IFC4X3_types[953])->set_attributes({}, {});
  ((entity *)IFC4X3_types[954])
      ->set_attributes(
          {new attribute(strings[3551], new named_type(IFC4X3_types[68]),
                         false),
           new attribute(strings[3552], new named_type(IFC4X3_types[951]),
                         false)},
          {false, false});
  ((entity *)IFC4X3_types[955])
      ->set_attributes(
          {new attribute(strings[2936], new named_type(IFC4X3_types[538]),
                         true),
           new attribute(strings[2882], new named_type(IFC4X3_types[1178]),
                         true)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[956])
      ->set_attributes({new attribute(strings[3181],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X3_types[959])),
                                      false),
                        new attribute(strings[2931],
                                      new named_type(IFC4X3_types[52]), false)},
                       {false, false, false, false});
  ((entity *)IFC4X3_types[957])
      ->set_attributes({new attribute(strings[3489],
                                      new named_type(IFC4X3_types[213]), false),
                        new attribute(strings[3181],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X3_types[959])),
                                      false)},
                       {false, false, false, false});
  ((entity *)IFC4X3_types[958])
      ->set_attributes(
          {new attribute(strings[2916], new named_type(IFC4X3_types[574]),
                         true),
           new attribute(strings[2886], new named_type(IFC4X3_types[1178]),
                         true)},
          {false, false});
  ((entity *)IFC4X3_types[961])
      ->set_attributes(
          {new attribute(strings[3553], new named_type(IFC4X3_types[358]),
                         true),
           new attribute(strings[3554], new named_type(IFC4X3_types[780]),
                         true),
           new attribute(strings[3555], new named_type(IFC4X3_types[292]),
                         true),
           new attribute(strings[3556], new named_type(IFC4X3_types[292]),
                         true),
           new attribute(strings[3557], new named_type(IFC4X3_types[574]),
                         true),
           new attribute(strings[3558], new named_type(IFC4X3_types[358]),
                         true),
           new attribute(strings[3559], new named_type(IFC4X3_types[87]), true),
           new attribute(strings[3560], new named_type(IFC4X3_types[292]),
                         true),
           new attribute(strings[3561], new named_type(IFC4X3_types[358]),
                         true),
           new attribute(strings[3562], new named_type(IFC4X3_types[780]),
                         true),
           new attribute(strings[3563], new named_type(IFC4X3_types[292]),
                         true),
           new attribute(strings[3564], new named_type(IFC4X3_types[292]),
                         true),
           new attribute(strings[3565], new named_type(IFC4X3_types[358]),
                         true),
           new attribute(strings[3566], new named_type(IFC4X3_types[780]),
                         true),
           new attribute(strings[3567], new named_type(IFC4X3_types[780]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[962])
      ->set_attributes(
          {new attribute(strings[2957], new named_type(IFC4X3_types[67]),
                         false),
           new attribute(strings[3568], new named_type(IFC4X3_types[761]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X3_types[963])
      ->set_attributes(
          {new attribute(strings[3183], new named_type(IFC4X3_types[806]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC4X3_types[964])
      ->set_attributes(
          {new attribute(strings[3367], new named_type(IFC4X3_types[778]),
                         false),
           new attribute(strings[3569], new named_type(IFC4X3_types[778]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X3_types[965])
      ->set_attributes(
          {new attribute(strings[3367], new named_type(IFC4X3_types[778]),
                         false),
           new attribute(strings[3026], new named_type(IFC4X3_types[778]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X3_types[966])
      ->set_attributes({new attribute(strings[2880],
                                      new named_type(IFC4X3_types[969]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X3_types[967])
      ->set_attributes({new attribute(strings[2880],
                                      new named_type(IFC4X3_types[968]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X3_types[971])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[973]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[972])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[973]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[974])
      ->set_attributes(
          {new attribute(strings[3570], new named_type(IFC4X3_types[519]),
                         false),
           new attribute(strings[3571], new named_type(IFC4X3_types[724]),
                         true),
           new attribute(strings[2916], new named_type(IFC4X3_types[574]),
                         true),
           new attribute(strings[2886], new named_type(IFC4X3_types[1178]),
                         true)},
          {false, false, false, false});
  ((entity *)IFC4X3_types[979])
      ->set_attributes(
          {new attribute(strings[3572], new named_type(IFC4X3_types[778]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1025])
      ->set_attributes(
          {new attribute(strings[3573], new named_type(IFC4X3_types[1023]),
                         true),
           new attribute(strings[2916], new named_type(IFC4X3_types[1026]),
                         false)},
          {true, false, false, false});
  ((entity *)IFC4X3_types[980])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[982]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[981])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[982]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[983])
      ->set_attributes({new attribute(strings[2916],
                                      new named_type(IFC4X3_types[574]), true),
                        new attribute(strings[3574],
                                      new named_type(IFC4X3_types[290]), true),
                        new attribute(strings[3575],
                                      new named_type(IFC4X3_types[574]), true)},
                       {false, false, false});
  ((entity *)IFC4X3_types[984])->set_attributes({}, {false, false, false});
  ((entity *)IFC4X3_types[985])
      ->set_attributes({new attribute(strings[3576],
                                      new named_type(IFC4X3_types[585]), false),
                        new attribute(strings[3577],
                                      new named_type(IFC4X3_types[585]), true),
                        new attribute(strings[3080],
                                      new named_type(IFC4X3_types[585]), true)},
                       {false, false, false, false});
  ((entity *)IFC4X3_types[992])
      ->set_attributes({new attribute(strings[3578],
                                      new named_type(IFC4X3_types[994]), false),
                        new attribute(strings[3579],
                                      new named_type(IFC4X3_types[806]), false),
                        new attribute(strings[3580],
                                      new named_type(IFC4X3_types[806]), true)},
                       {false, false, false});
  ((entity *)IFC4X3_types[993])
      ->set_attributes({new attribute(strings[3581],
                                      new named_type(IFC4X3_types[585]), false),
                        new attribute(strings[3582],
                                      new named_type(IFC4X3_types[585]), false),
                        new attribute(strings[3583],
                                      new named_type(IFC4X3_types[585]), true),
                        new attribute(strings[3584],
                                      new named_type(IFC4X3_types[890]), false),
                        new attribute(strings[3585],
                                      new named_type(IFC4X3_types[992]), false),
                        new attribute(strings[3586],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X3_types[887])),
                                      false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[987])
      ->set_attributes({new attribute(strings[3119],
                                      new named_type(IFC4X3_types[272]), false),
                        new attribute(strings[3587],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, -1,
                                          new named_type(IFC4X3_types[806])),
                                      false)},
                       {false, false});
  ((entity *)IFC4X3_types[988])
      ->set_attributes({new attribute(strings[3588],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, -1,
                                          new named_type(IFC4X3_types[71])),
                                      false)},
                       {false, false, false});
  ((entity *)IFC4X3_types[989])
      ->set_attributes({new attribute(strings[3589],
                                      new named_type(IFC4X3_types[193]), false),
                        new attribute(strings[3587],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, -1,
                                          new named_type(IFC4X3_types[806])),
                                      false),
                        new attribute(strings[3588],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, -1,
                                          new named_type(IFC4X3_types[70])),
                                      false)},
                       {false, false, false});
  ((entity *)IFC4X3_types[990])
      ->set_attributes({new attribute(strings[3119],
                                      new named_type(IFC4X3_types[272]), false),
                        new attribute(strings[3588],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, -1,
                                          new named_type(IFC4X3_types[71])),
                                      false),
                        new attribute(strings[3587],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, -1,
                                          new named_type(IFC4X3_types[806])),
                                      false)},
                       {false, false, false});
  ((entity *)IFC4X3_types[995])
      ->set_attributes(
          {new attribute(strings[3590], new named_type(IFC4X3_types[1223]),
                         false)},
          {false});
  ((entity *)IFC4X3_types[996])
      ->set_attributes({new attribute(strings[3214],
                                      new named_type(IFC4X3_types[99]), false),
                        new attribute(strings[3215],
                                      new named_type(IFC4X3_types[756]), true)},
                       {false, false, false, false});
  ((entity *)IFC4X3_types[998])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1000]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[999])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1000]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[1002])
      ->set_attributes(
          {new attribute(strings[3591], new named_type(IFC4X3_types[585]),
                         false),
           new attribute(strings[3592], new named_type(IFC4X3_types[585]),
                         true),
           new attribute(strings[3593], new named_type(IFC4X3_types[585]),
                         true),
           new attribute(strings[3594], new named_type(IFC4X3_types[585]),
                         true),
           new attribute(strings[3595], new named_type(IFC4X3_types[585]),
                         true),
           new attribute(strings[3576], new named_type(IFC4X3_types[585]),
                         true),
           new attribute(strings[3577], new named_type(IFC4X3_types[585]),
                         true),
           new attribute(strings[3080], new named_type(IFC4X3_types[585]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1003])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1005]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1004])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1005]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[1006])
      ->set_attributes({new attribute(strings[3596],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X3_types[1007])),
                                      false),
                        new attribute(strings[2916],
                                      new named_type(IFC4X3_types[574]), true),
                        new attribute(strings[2886],
                                      new named_type(IFC4X3_types[1178]), true),
                        new attribute(strings[3597],
                                      new named_type(IFC4X3_types[617]), false),
                        new attribute(strings[3598],
                                      new named_type(IFC4X3_types[804]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X3_types[1007])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X3_types[1008])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X3_types[1011])
      ->set_attributes({new attribute(strings[3599],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X3_types[1010])),
                                      false)},
                       {false});
  ((entity *)IFC4X3_types[1012])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1017]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1016])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1017]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[1013])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1015]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1014])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1015]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[1018])->set_attributes({}, {false, false});
  ((entity *)IFC4X3_types[1019])
      ->set_attributes(
          {new attribute(strings[3041], new named_type(IFC4X3_types[1020]),
                         true),
           new attribute(strings[3600], new named_type(IFC4X3_types[574]),
                         true),
           new attribute(strings[3601], new named_type(IFC4X3_types[574]),
                         true),
           new attribute(strings[3602], new named_type(IFC4X3_types[823]),
                         true),
           new attribute(strings[3603], new named_type(IFC4X3_types[1244]),
                         true),
           new attribute(strings[3604], new named_type(IFC4X3_types[1244]),
                         true),
           new attribute(strings[3412], new named_type(IFC4X3_types[574]),
                         true),
           new attribute(strings[3605], new named_type(IFC4X3_types[1073]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC4X3_types[1022])
      ->set_attributes({new attribute(strings[3606],
                                      new named_type(IFC4X3_types[585]), false),
                        new attribute(strings[3577],
                                      new named_type(IFC4X3_types[585]), true),
                        new attribute(strings[3080],
                                      new named_type(IFC4X3_types[585]), true)},
                       {false, false, false, false});
  ((entity *)IFC4X3_types[1024])
      ->set_attributes({new attribute(strings[3607],
                                      new named_type(IFC4X3_types[197]), true),
                        new attribute(strings[3608],
                                      new named_type(IFC4X3_types[197]), true),
                        new attribute(strings[3609],
                                      new named_type(IFC4X3_types[585]), true),
                        new attribute(strings[3610],
                                      new named_type(IFC4X3_types[574]), true),
                        new attribute(strings[3611],
                                      new named_type(IFC4X3_types[781]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1028])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1030]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1029])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1030]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[1031])
      ->set_attributes({new attribute(strings[3612],
                                      new named_type(IFC4X3_types[585]), true),
                        new attribute(strings[3613],
                                      new named_type(IFC4X3_types[585]), true),
                        new attribute(strings[3614],
                                      new named_type(IFC4X3_types[585]), true)},
                       {false, false, false, false});
  ((entity *)IFC4X3_types[1032])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1034]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1033])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1034]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[1036])->set_attributes({}, {});
  ((entity *)IFC4X3_types[1042])
      ->set_attributes({new attribute(strings[2880],
                                      new named_type(IFC4X3_types[1048]), true),
                        new attribute(strings[3615],
                                      new named_type(IFC4X3_types[585]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X3_types[1044])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1046]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1045])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1046]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[1047])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1048]),
                         false),
           new attribute(strings[3009], new named_type(IFC4X3_types[574]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[1049])
      ->set_attributes(
          {new attribute(strings[3009], new named_type(IFC4X3_types[574]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1050])
      ->set_attributes(
          {new attribute(strings[3169], new named_type(IFC4X3_types[574]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1052])
      ->set_attributes(
          {new attribute(strings[3616], new named_type(IFC4X3_types[402]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1053])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1054])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1056]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1055])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1056]),
                         false),
           new attribute(strings[3009], new named_type(IFC4X3_types[574]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[1061])
      ->set_attributes(
          {new attribute(strings[3026], new named_type(IFC4X3_types[778]),
                         false)},
          {false, false});
  ((entity *)IFC4X3_types[1062])
      ->set_attributes(
          {new attribute(strings[3026], new named_type(IFC4X3_types[778]),
                         false)},
          {false, false});
  ((entity *)IFC4X3_types[1063])
      ->set_attributes({new attribute(strings[3048],
                                      new named_type(IFC4X3_types[68]), true)},
                       {false});
  ((entity *)IFC4X3_types[1064])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1066]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1065])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1066]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[1067])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1072]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1068])
      ->set_attributes(
          {new attribute(strings[3617], new named_type(IFC4X3_types[552]),
                         true),
           new attribute(strings[3618], new named_type(IFC4X3_types[552]),
                         true),
           new attribute(strings[3619], new named_type(IFC4X3_types[778]),
                         true),
           new attribute(strings[3620], new named_type(IFC4X3_types[778]),
                         true),
           new attribute(strings[2880], new named_type(IFC4X3_types[1070]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false});
  ((entity *)IFC4X3_types[1069])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1070]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[1071])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1072]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[1074])
      ->set_attributes({new attribute(strings[3621],
                                      new named_type(IFC4X3_types[87]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X3_types[1075])
      ->set_attributes(
          {new attribute(strings[3622], new named_type(IFC4X3_types[1089]),
                         false),
           new attribute(strings[3623], new named_type(IFC4X3_types[520]),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1077])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[43]),
                         false),
           new attribute(strings[3624], new named_type(IFC4X3_types[70]), true),
           new attribute(
               strings[3625],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X3_types[1092])),
               true),
           new attribute(
               strings[3626],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X3_types[1108])),
               true),
           new attribute(strings[3627], new named_type(IFC4X3_types[704]),
                         true)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[1078])
      ->set_attributes(
          {new attribute(strings[3504], new named_type(IFC4X3_types[93]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1079])
      ->set_attributes({new attribute(strings[2916],
                                      new named_type(IFC4X3_types[574]), true)},
                       {false});
  ((entity *)IFC4X3_types[1080])
      ->set_attributes(
          {new attribute(strings[3628], new named_type(IFC4X3_types[811]),
                         true),
           new attribute(strings[2880], new named_type(IFC4X3_types[1081]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC4X3_types[1082])
      ->set_attributes(
          {new attribute(strings[3629], new named_type(IFC4X3_types[306]),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1083])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1084]),
                         false),
           new attribute(strings[2957], new named_type(IFC4X3_types[306]),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1085])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1086])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1081]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[1087])
      ->set_attributes({}, {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1088])
      ->set_attributes({}, {false, false, false, false, false, false, false,
                            false, false, false, false, false});
  ((entity *)IFC4X3_types[1089])
      ->set_attributes({new attribute(strings[2916],
                                      new named_type(IFC4X3_types[574]), true)},
                       {false});
  ((entity *)IFC4X3_types[1090])
      ->set_attributes({new attribute(strings[3630],
                                      new aggregation_type(
                                          aggregation_type::list_type, 3, 3,
                                          new named_type(IFC4X3_types[870])),
                                      true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X3_types[1091])
      ->set_attributes(
          {new attribute(
               strings[3243],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X3_types[1094])),
               false),
           new attribute(
               strings[3631],
               new aggregation_type(
                   aggregation_type::list_type, 1, -1,
                   new aggregation_type(aggregation_type::list_type, 1, 2,
                                        new named_type(IFC4X3_types[585]))),
               true)},
          {false, false, false});
  ((entity *)IFC4X3_types[1092])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[615]),
                         false),
           new attribute(strings[3632], new named_type(IFC4X3_types[5]), false),
           new attribute(strings[3633], new named_type(IFC4X3_types[4]), false),
           new attribute(strings[3634], new named_type(IFC4X3_types[870]),
                         true),
           new attribute(strings[2887], new named_type(IFC4X3_types[574]),
                         true)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[1093])
      ->set_attributes({new attribute(strings[3635],
                                      new named_type(IFC4X3_types[605]), true),
                        new attribute(strings[3636],
                                      new named_type(IFC4X3_types[605]), true),
                        new attribute(strings[3637],
                                      new named_type(IFC4X3_types[605]), true),
                        new attribute(strings[3638],
                                      new named_type(IFC4X3_types[606]), true),
                        new attribute(strings[3639],
                                      new named_type(IFC4X3_types[606]), true),
                        new attribute(strings[3640],
                                      new named_type(IFC4X3_types[606]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1094])->set_attributes({}, {false});
  ((entity *)IFC4X3_types[1095])
      ->set_attributes({new attribute(strings[3641],
                                      new named_type(IFC4X3_types[759]), true),
                        new attribute(strings[3642],
                                      new named_type(IFC4X3_types[759]), true),
                        new attribute(strings[3643],
                                      new named_type(IFC4X3_types[759]), true)},
                       {false, false, false, false});
  ((entity *)IFC4X3_types[1096])
      ->set_attributes({new attribute(strings[3644],
                                      new named_type(IFC4X3_types[585]), true),
                        new attribute(strings[3645],
                                      new named_type(IFC4X3_types[585]), true),
                        new attribute(strings[3646],
                                      new named_type(IFC4X3_types[585]), true),
                        new attribute(strings[3647],
                                      new named_type(IFC4X3_types[761]), true),
                        new attribute(strings[3648],
                                      new named_type(IFC4X3_types[761]), true),
                        new attribute(strings[3649],
                                      new named_type(IFC4X3_types[761]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1097])
      ->set_attributes(
          {new attribute(strings[3650], new named_type(IFC4X3_types[271]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1098])
      ->set_attributes(
          {new attribute(strings[3651], new named_type(IFC4X3_types[496]),
                         true),
           new attribute(strings[3652], new named_type(IFC4X3_types[496]),
                         true),
           new attribute(strings[3653], new named_type(IFC4X3_types[496]),
                         true),
           new attribute(strings[3654], new named_type(IFC4X3_types[1216]),
                         true),
           new attribute(strings[3655], new named_type(IFC4X3_types[1216]),
                         true),
           new attribute(strings[3656], new named_type(IFC4X3_types[1216]),
                         true)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1099])
      ->set_attributes(
          {new attribute(strings[3657], new named_type(IFC4X3_types[1286]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1100])->set_attributes({}, {false});
  ((entity *)IFC4X3_types[1101])
      ->set_attributes(
          {new attribute(strings[3658], new named_type(IFC4X3_types[1203]),
                         true),
           new attribute(strings[3659], new named_type(IFC4X3_types[1203]),
                         true),
           new attribute(strings[3660], new named_type(IFC4X3_types[1203]),
                         true)},
          {false, false, false, false});
  ((entity *)IFC4X3_types[1102])
      ->set_attributes({}, {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1103])
      ->set_attributes({}, {false, false, false, false, false, false, false,
                            false, false, false, false, false});
  ((entity *)IFC4X3_types[1104])
      ->set_attributes({}, {false, false, false, false, false, false, false,
                            false, false, false});
  ((entity *)IFC4X3_types[1105])
      ->set_attributes(
          {new attribute(strings[3507], new named_type(IFC4X3_types[70]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1106])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1107])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1108])
      ->set_attributes(
          {new attribute(strings[3661], new named_type(IFC4X3_types[44]),
                         false),
           new attribute(strings[3662], new named_type(IFC4X3_types[1092]),
                         true),
           new attribute(strings[3663], new named_type(IFC4X3_types[87]),
                         false)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1109])
      ->set_attributes(
          {new attribute(strings[3628], new named_type(IFC4X3_types[811]),
                         true),
           new attribute(strings[2880], new named_type(IFC4X3_types[1110]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC4X3_types[1111])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1112])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1113]),
                         false),
           new attribute(strings[3025], new named_type(IFC4X3_types[778]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1114])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1115])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1110]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[1118])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X3_types[1116])
      ->set_attributes({new attribute(strings[3664],
                                      new named_type(IFC4X3_types[953]), true),
                        new attribute(strings[3665],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X3_types[794])),
                                      false),
                        new attribute(strings[2916],
                                      new named_type(IFC4X3_types[574]), true)},
                       {false, false, false});
  ((entity *)IFC4X3_types[1117])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X3_types[1119])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1121]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[1120])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1121]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC4X3_types[1122])
      ->set_attributes(
          {new attribute(strings[3666], new named_type(IFC4X3_types[365]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X3_types[1123])->set_attributes({}, {});
  ((entity *)IFC4X3_types[1124])
      ->set_attributes(
          {new attribute(strings[3667], new named_type(IFC4X3_types[272]),
                         false),
           new attribute(
               strings[3668],
               new aggregation_type(aggregation_type::list_type, 1, 2,
                                    new named_type(IFC4X3_types[731])),
               false),
           new attribute(strings[3669], new named_type(IFC4X3_types[789]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X3_types[1125])
      ->set_attributes(
          {new attribute(strings[3670], new named_type(IFC4X3_types[1123]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1126])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1127]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1128])
      ->set_attributes(
          {new attribute(strings[3182], new named_type(IFC4X3_types[306]),
                         false),
           new attribute(strings[3010], new named_type(IFC4X3_types[585]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X3_types[1129])
      ->set_attributes({new attribute(strings[3671],
                                      new named_type(IFC4X3_types[67]), false)},
                       {false, false, false});
  ((entity *)IFC4X3_types[1131])
      ->set_attributes({new attribute(strings[3672],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, 3,
                                          new named_type(IFC4X3_types[585])),
                                      true),
                        new attribute(strings[3673],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, 3,
                                          new named_type(IFC4X3_types[585])),
                                      true),
                        new attribute(strings[3674],
                                      new named_type(IFC4X3_types[870]), true)},
                       {false, false, false, false});
  ((entity *)IFC4X3_types[1133])
      ->set_attributes(
          {new attribute(strings[3675], new named_type(IFC4X3_types[1132]),
                         false),
           new attribute(
               strings[3665],
               new aggregation_type(aggregation_type::set_type, 1, 5,
                                    new named_type(IFC4X3_types[1134])),
               false)},
          {false, false, false});
  ((entity *)IFC4X3_types[1135])
      ->set_attributes(
          {new attribute(strings[3676], new named_type(IFC4X3_types[180]),
                         false),
           new attribute(strings[3677], new named_type(IFC4X3_types[180]),
                         false),
           new attribute(strings[3678], new named_type(IFC4X3_types[180]),
                         false),
           new attribute(strings[3679], new named_type(IFC4X3_types[180]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X3_types[1136])
      ->set_attributes({new attribute(strings[3680],
                                      new named_type(IFC4X3_types[873]), true),
                        new attribute(strings[3681],
                                      new named_type(IFC4X3_types[873]), true)},
                       {false, false});
  ((entity *)IFC4X3_types[1137])
      ->set_attributes(
          {new attribute(strings[3682], new named_type(IFC4X3_types[179]),
                         true),
           new attribute(strings[3678], new named_type(IFC4X3_types[179]),
                         true),
           new attribute(strings[3676], new named_type(IFC4X3_types[179]),
                         true),
           new attribute(strings[3683], new named_type(IFC4X3_types[179]),
                         true),
           new attribute(strings[3684], new named_type(IFC4X3_types[179]),
                         true),
           new attribute(strings[3685], new named_type(IFC4X3_types[1059]),
                         true),
           new attribute(strings[3686], new named_type(IFC4X3_types[883]),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1138])
      ->set_attributes({new attribute(strings[3687],
                                      new named_type(IFC4X3_types[180]), false),
                        new attribute(strings[3688],
                                      new named_type(IFC4X3_types[698]), true)},
                       {false, false});
  ((entity *)IFC4X3_types[1139])
      ->set_attributes({new attribute(strings[3689],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X3_types[1140])),
                                      false)},
                       {false});
  ((entity *)IFC4X3_types[1140])
      ->set_attributes({new attribute(strings[3690],
                                      new named_type(IFC4X3_types[87]), false),
                        new attribute(strings[3691],
                                      new named_type(IFC4X3_types[87]), false),
                        new attribute(strings[3692],
                                      new named_type(IFC4X3_types[538]), true),
                        new attribute(strings[3693],
                                      new named_type(IFC4X3_types[152]), true),
                        new attribute(strings[3694],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X3_types[538])),
                                      true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X3_types[1141])
      ->set_attributes({new attribute(strings[3695],
                                      new named_type(IFC4X3_types[806]), false),
                        new attribute(strings[3048],
                                      new named_type(IFC4X3_types[70]), true)},
                       {false, false});
  ((entity *)IFC4X3_types[1142])
      ->set_attributes({new attribute(strings[3119],
                                      new named_type(IFC4X3_types[272]), false),
                        new attribute(strings[3026],
                                      new named_type(IFC4X3_types[778]), false),
                        new attribute(strings[3696],
                                      new named_type(IFC4X3_types[778]), true),
                        new attribute(strings[3120],
                                      new named_type(IFC4X3_types[726]), true),
                        new attribute(strings[3121],
                                      new named_type(IFC4X3_types[726]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X3_types[1143])
      ->set_attributes({new attribute(strings[3226],
                                      new named_type(IFC4X3_types[697]), true)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1144])
      ->set_attributes({new attribute(strings[3697],
                                      new named_type(IFC4X3_types[806]), false),
                        new attribute(strings[3048],
                                      new named_type(IFC4X3_types[70]), true)},
                       {false, false});
  ((entity *)IFC4X3_types[1145])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1147]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1146])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1147]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[1148])
      ->set_attributes({}, {false, false, false, false, false});
  ((entity *)IFC4X3_types[1149])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1151]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1150])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1151]),
                         true)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[1236])
      ->set_attributes({new attribute(strings[3010],
                                      new named_type(IFC4X3_types[778]), false),
                        new attribute(strings[3698],
                                      new named_type(IFC4X3_types[778]), false),
                        new attribute(strings[2947],
                                      new named_type(IFC4X3_types[778]), false),
                        new attribute(strings[3225],
                                      new named_type(IFC4X3_types[778]), false),
                        new attribute(strings[3226],
                                      new named_type(IFC4X3_types[697]), true),
                        new attribute(strings[3227],
                                      new named_type(IFC4X3_types[697]), true),
                        new attribute(strings[3699],
                                      new named_type(IFC4X3_types[697]), true),
                        new attribute(strings[3700],
                                      new named_type(IFC4X3_types[761]), true),
                        new attribute(strings[3228],
                                      new named_type(IFC4X3_types[761]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false});
  ((entity *)IFC4X3_types[1152])
      ->set_attributes({new attribute(strings[2916],
                                      new named_type(IFC4X3_types[574]), true),
                        new attribute(strings[3701],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X3_types[1154])),
                                      true),
                        new attribute(strings[3702],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X3_types[1153])),
                                      true)},
                       {false, false, false});
  ((entity *)IFC4X3_types[1153])
      ->set_attributes({new attribute(strings[2925],
                                      new named_type(IFC4X3_types[538]), true),
                        new attribute(strings[2916],
                                      new named_type(IFC4X3_types[574]), true),
                        new attribute(strings[2886],
                                      new named_type(IFC4X3_types[1178]), true),
                        new attribute(strings[3109],
                                      new named_type(IFC4X3_types[1244]), true),
                        new attribute(strings[3324],
                                      new named_type(IFC4X3_types[880]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X3_types[1154])
      ->set_attributes({new attribute(strings[3703],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X3_types[1255])),
                                      true),
                        new attribute(strings[3704],
                                      new named_type(IFC4X3_types[87]), true)},
                       {false, false});
  ((entity *)IFC4X3_types[1155])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1157]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1156])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1157]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[1158])
      ->set_attributes(
          {new attribute(strings[2881], new named_type(IFC4X3_types[574]),
                         true),
           new attribute(strings[3705], new named_type(IFC4X3_types[574]),
                         true),
           new attribute(strings[3706], new named_type(IFC4X3_types[87]),
                         false),
           new attribute(strings[3296], new named_type(IFC4X3_types[552]),
                         true),
           new attribute(strings[3707], new named_type(IFC4X3_types[1160]),
                         true),
           new attribute(strings[2880], new named_type(IFC4X3_types[1163]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false});
  ((entity *)IFC4X3_types[1160])
      ->set_attributes(
          {new attribute(strings[3250], new named_type(IFC4X3_types[1159]),
                         true),
           new attribute(strings[3708], new named_type(IFC4X3_types[358]),
                         true),
           new attribute(strings[3555], new named_type(IFC4X3_types[292]),
                         true),
           new attribute(strings[3556], new named_type(IFC4X3_types[292]),
                         true),
           new attribute(strings[3709], new named_type(IFC4X3_types[292]),
                         true),
           new attribute(strings[3710], new named_type(IFC4X3_types[292]),
                         true),
           new attribute(strings[3711], new named_type(IFC4X3_types[292]),
                         true),
           new attribute(strings[3712], new named_type(IFC4X3_types[292]),
                         true),
           new attribute(strings[3713], new named_type(IFC4X3_types[358]),
                         true),
           new attribute(strings[3714], new named_type(IFC4X3_types[358]),
                         true),
           new attribute(strings[3715], new named_type(IFC4X3_types[87]), true),
           new attribute(strings[3560], new named_type(IFC4X3_types[292]),
                         true),
           new attribute(strings[3716], new named_type(IFC4X3_types[358]),
                         true),
           new attribute(strings[3563], new named_type(IFC4X3_types[292]),
                         true),
           new attribute(strings[3564], new named_type(IFC4X3_types[292]),
                         true),
           new attribute(strings[3717], new named_type(IFC4X3_types[358]),
                         true),
           new attribute(strings[3567], new named_type(IFC4X3_types[780]),
                         true)},
          {false, false, false, false, false, false, false,
           false, false, false, false, false, false, false,
           false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1161])
      ->set_attributes(
          {new attribute(strings[3718], new named_type(IFC4X3_types[878]),
                         false)},
          {false, false, false, false, false, false, false,
           false, false, false, false, false, false, false,
           false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1162])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1163]),
                         false),
           new attribute(strings[3705], new named_type(IFC4X3_types[574]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[1164])
      ->set_attributes(
          {new attribute(
               strings[3719],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X3_types[574])),
               true),
           new attribute(
               strings[3720],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X3_types[574])),
               true),
           new attribute(strings[3721], new named_type(IFC4X3_types[574]),
                         true),
           new attribute(
               strings[3722],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X3_types[574])),
               true),
           new attribute(strings[3723], new named_type(IFC4X3_types[1253]),
                         true),
           new attribute(
               strings[3724],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X3_types[1253])),
               true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1167])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1175]),
                         true),
           new attribute(strings[3319], new named_type(IFC4X3_types[778]),
                         true),
           new attribute(strings[3461], new named_type(IFC4X3_types[59]), true),
           new attribute(strings[3725], new named_type(IFC4X3_types[496]),
                         true),
           new attribute(strings[3726], new named_type(IFC4X3_types[795]),
                         true),
           new attribute(strings[3727], new named_type(IFC4X3_types[698]),
                         true),
           new attribute(strings[3728], new named_type(IFC4X3_types[778]),
                         true),
           new attribute(strings[3729], new named_type(IFC4X3_types[778]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1168])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1170]),
                         true)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[1169])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1170]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[1171])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1173]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[1172])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1173]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[1174])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1175]),
                         false),
           new attribute(strings[3319], new named_type(IFC4X3_types[778]),
                         true),
           new attribute(strings[3461], new named_type(IFC4X3_types[59]), true),
           new attribute(strings[3730], new named_type(IFC4X3_types[778]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false});
  ((entity *)IFC4X3_types[1176])
      ->set_attributes({new attribute(strings[3015],
                                      new named_type(IFC4X3_types[150]), false),
                        new attribute(strings[3731],
                                      new named_type(IFC4X3_types[87]), true)},
                       {false, false});
  ((entity *)IFC4X3_types[1177])->set_attributes({}, {});
  ((entity *)IFC4X3_types[1183])
      ->set_attributes(
          {new attribute(strings[3732], new named_type(IFC4X3_types[790]),
                         false),
           new attribute(strings[3094], new named_type(IFC4X3_types[68]),
                         false),
           new attribute(strings[3733], new named_type(IFC4X3_types[1185]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X3_types[1184])
      ->set_attributes(
          {new attribute(strings[3734], new named_type(IFC4X3_types[758]),
                         false),
           new attribute(strings[3735], new named_type(IFC4X3_types[102]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC4X3_types[1186])
      ->set_attributes(
          {new attribute(strings[3736], new named_type(IFC4X3_types[1188]),
                         true),
           new attribute(strings[3737], new named_type(IFC4X3_types[1189]),
                         true),
           new attribute(strings[3738], new named_type(IFC4X3_types[1182]),
                         false),
           new attribute(strings[3099], new named_type(IFC4X3_types[87]),
                         true)},
          {false, false, false, false, false});
  ((entity *)IFC4X3_types[1187])
      ->set_attributes(
          {new attribute(
               strings[3739],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X3_types[1181])),
               false),
           new attribute(strings[3740], new named_type(IFC4X3_types[490]),
                         true),
           new attribute(strings[3741], new named_type(IFC4X3_types[491]),
                         true),
           new attribute(strings[3742], new named_type(IFC4X3_types[492]),
                         true),
           new attribute(strings[3743], new named_type(IFC4X3_types[1027]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1188])
      ->set_attributes({new attribute(strings[3744],
                                      new named_type(IFC4X3_types[178]), false),
                        new attribute(strings[3745],
                                      new named_type(IFC4X3_types[178]), true)},
                       {false, false});
  ((entity *)IFC4X3_types[1189])
      ->set_attributes(
          {new attribute(strings[3746], new named_type(IFC4X3_types[1027]),
                         true),
           new attribute(strings[3747], new named_type(IFC4X3_types[1179]),
                         true),
           new attribute(strings[3748], new named_type(IFC4X3_types[1180]),
                         true),
           new attribute(strings[3749], new named_type(IFC4X3_types[1027]),
                         true),
           new attribute(strings[3750], new named_type(IFC4X3_types[1027]),
                         true),
           new attribute(strings[3751], new named_type(IFC4X3_types[1190]),
                         true),
           new attribute(strings[3752], new named_type(IFC4X3_types[1027]),
                         true)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1191])
      ->set_attributes({new attribute(strings[3753],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X3_types[1140])),
                                      false)},
                       {false});
  ((entity *)IFC4X3_types[1192])
      ->set_attributes({new attribute(strings[3692],
                                      new named_type(IFC4X3_types[574]), false),
                        new attribute(strings[3694],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X3_types[873])),
                                      true)},
                       {false, false, false});
  ((entity *)IFC4X3_types[1193])
      ->set_attributes(
          {new attribute(
               strings[3239],
               new aggregation_type(aggregation_type::list_type, 3, -1,
                                    new named_type(IFC4X3_types[777])),
               false),
           new attribute(strings[3754], new named_type(IFC4X3_types[546]),
                         false)},
          {false, false});
  ((entity *)IFC4X3_types[1194])
      ->set_attributes(
          {new attribute(
              strings[3755],
              new aggregation_type(
                  aggregation_type::list_type, 1, -1,
                  new aggregation_type(aggregation_type::list_type, 3, -1,
                                       new named_type(IFC4X3_types[777]))),
              false)},
          {false, false, false});
  ((entity *)IFC4X3_types[1195])
      ->set_attributes(
          {new attribute(
               strings[3756],
               new aggregation_type(aggregation_type::list_type, 3, -1,
                                    new named_type(IFC4X3_types[1196])),
               false),
           new attribute(strings[3230], new named_type(IFC4X3_types[436]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X3_types[1196])
      ->set_attributes({new attribute(strings[3015],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, 2,
                                          new named_type(IFC4X3_types[726])),
                                      false)},
                       {false});
  ((entity *)IFC4X3_types[1197])
      ->set_attributes(
          {new attribute(
              strings[3757],
              new aggregation_type(
                  aggregation_type::list_type, 1, -1,
                  new aggregation_type(aggregation_type::list_type, 2, 2,
                                       new named_type(IFC4X3_types[726]))),
              false)},
          {false});
  ((entity *)IFC4X3_types[1204])
      ->set_attributes({new attribute(strings[3595],
                                      new named_type(IFC4X3_types[585]), false),
                        new attribute(strings[3576],
                                      new named_type(IFC4X3_types[585]), true),
                        new attribute(strings[3577],
                                      new named_type(IFC4X3_types[585]), true),
                        new attribute(strings[3080],
                                      new named_type(IFC4X3_types[585]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X3_types[1208])
      ->set_attributes(
          {new attribute(strings[3758], new named_type(IFC4X3_types[1205]),
                         false),
           new attribute(strings[3759], new named_type(IFC4X3_types[1205]),
                         false)},
          {false, false});
  ((entity *)IFC4X3_types[1209])
      ->set_attributes(
          {new attribute(strings[2916], new named_type(IFC4X3_types[574]),
                         false),
           new attribute(strings[2886], new named_type(IFC4X3_types[1178]),
                         true),
           new attribute(strings[3758], new named_type(IFC4X3_types[292]),
                         false),
           new attribute(strings[3759], new named_type(IFC4X3_types[292]),
                         false),
           new attribute(strings[3760], new named_type(IFC4X3_types[1210]),
                         false),
           new attribute(strings[3574], new named_type(IFC4X3_types[290]),
                         false),
           new attribute(strings[3575], new named_type(IFC4X3_types[574]),
                         true),
           new attribute(strings[3109], new named_type(IFC4X3_types[1244]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1211])
      ->set_attributes({new attribute(strings[3245],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X3_types[1255])),
                                      false)},
                       {false});
  ((entity *)IFC4X3_types[1213])->set_attributes({}, {});
  ((entity *)IFC4X3_types[1214])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X3_types[1215])
      ->set_attributes(
          {new attribute(strings[3761], new named_type(IFC4X3_types[778]),
                         false),
           new attribute(strings[3762], new named_type(IFC4X3_types[778]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X3_types[1217])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1219]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1218])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1219]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[1220])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1222]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1221])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1222]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[1227])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1229]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1228])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1229]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[1225])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1226])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1230])
      ->set_attributes(
          {new attribute(strings[3763], new named_type(IFC4X3_types[778]),
                         false),
           new attribute(strings[3764], new named_type(IFC4X3_types[778]),
                         false),
           new attribute(strings[3002], new named_type(IFC4X3_types[778]),
                         false),
           new attribute(strings[3765], new named_type(IFC4X3_types[585]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1231])
      ->set_attributes(
          {new attribute(
               strings[3766],
               new aggregation_type(
                   aggregation_type::list_type, 1, -1,
                   new aggregation_type(aggregation_type::list_type, 3, 3,
                                        new named_type(IFC4X3_types[726]))),
               true),
           new attribute(
               strings[3235],
               new aggregation_type(
                   aggregation_type::list_type, 1, -1,
                   new aggregation_type(aggregation_type::list_type, 3, 3,
                                        new named_type(IFC4X3_types[777]))),
               false),
           new attribute(
               strings[3382],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X3_types[777])),
               true)},
          {false, false, false, false, false});
  ((entity *)IFC4X3_types[1232])
      ->set_attributes({new attribute(strings[3767],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X3_types[552])),
                                      false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1233])
      ->set_attributes(
          {new attribute(strings[3332], new named_type(IFC4X3_types[272]),
                         false),
           new attribute(
               strings[3768],
               new aggregation_type(aggregation_type::set_type, 1, 2,
                                    new named_type(IFC4X3_types[1235])),
               false),
           new attribute(
               strings[3769],
               new aggregation_type(aggregation_type::set_type, 1, 2,
                                    new named_type(IFC4X3_types[1235])),
               false),
           new attribute(strings[3770], new named_type(IFC4X3_types[87]),
                         false),
           new attribute(strings[3669], new named_type(IFC4X3_types[1234]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC4X3_types[1237])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1239]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1238])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1239]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[1240])
      ->set_attributes({new attribute(strings[3771],
                                      new named_type(IFC4X3_types[538]), true),
                        new attribute(strings[3772],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X3_types[827])),
                                      true)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1241])
      ->set_attributes(
          {new attribute(strings[2936], new named_type(IFC4X3_types[538]),
                         true),
           new attribute(strings[2882], new named_type(IFC4X3_types[1178]),
                         true),
           new attribute(strings[3773], new named_type(IFC4X3_types[574]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1242])
      ->set_attributes(
          {new attribute(
               strings[3774],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X3_types[954])),
               true),
           new attribute(strings[3165], new named_type(IFC4X3_types[574]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1243])
      ->set_attributes(
          {new attribute(strings[2936], new named_type(IFC4X3_types[538]),
                         true),
           new attribute(strings[2882], new named_type(IFC4X3_types[1178]),
                         true),
           new attribute(strings[3775], new named_type(IFC4X3_types[574]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1254])
      ->set_attributes({new attribute(strings[3010],
                                      new named_type(IFC4X3_types[778]), false),
                        new attribute(strings[3698],
                                      new named_type(IFC4X3_types[778]), false),
                        new attribute(strings[2947],
                                      new named_type(IFC4X3_types[778]), false),
                        new attribute(strings[3225],
                                      new named_type(IFC4X3_types[778]), false),
                        new attribute(strings[3226],
                                      new named_type(IFC4X3_types[697]), true),
                        new attribute(strings[3247],
                                      new named_type(IFC4X3_types[697]), true),
                        new attribute(strings[3228],
                                      new named_type(IFC4X3_types[761]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X3_types[1251])
      ->set_attributes({new attribute(strings[3776],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X3_types[1244])),
                                      false)},
                       {false});
  ((entity *)IFC4X3_types[1245])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1247]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1246])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1247]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[1248])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1250]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1249])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1250]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[1256])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1258]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1257])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1258]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[1260])
      ->set_attributes(
          {new attribute(strings[3187], new named_type(IFC4X3_types[306]),
                         false),
           new attribute(strings[3777], new named_type(IFC4X3_types[585]),
                         false)},
          {false, false});
  ((entity *)IFC4X3_types[1262])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1264]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1263])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1264]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[1265])->set_attributes({}, {});
  ((entity *)IFC4X3_types[1266])
      ->set_attributes(
          {new attribute(strings[3778], new named_type(IFC4X3_types[1265]),
                         false)},
          {false});
  ((entity *)IFC4X3_types[1267])
      ->set_attributes(
          {new attribute(strings[3779], new named_type(IFC4X3_types[765]),
                         false)},
          {false});
  ((entity *)IFC4X3_types[1268])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[289]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1269])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1270]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[1271])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1273]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1272])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1273]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[1274])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1275]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1276])
      ->set_attributes({new attribute(strings[3780],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, 2,
                                          new named_type(IFC4X3_types[523])),
                                      false),
                        new attribute(strings[3781],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, 3,
                                          new named_type(IFC4X3_types[585])),
                                      false)},
                       {false, false});
  ((entity *)IFC4X3_types[1277])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1278]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1281])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1284]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1282])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1283])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1284]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[1288])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1290]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1289])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1290]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X3_types[1291])
      ->set_attributes({new attribute(strings[3139],
                                      new named_type(IFC4X3_types[778]), true),
                        new attribute(strings[3140],
                                      new named_type(IFC4X3_types[778]), true),
                        new attribute(strings[2880],
                                      new named_type(IFC4X3_types[1299]), true),
                        new attribute(strings[3782],
                                      new named_type(IFC4X3_types[1300]), true),
                        new attribute(strings[3783],
                                      new named_type(IFC4X3_types[574]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false, false});
  ((entity *)IFC4X3_types[1292])
      ->set_attributes({new attribute(strings[3143],
                                      new named_type(IFC4X3_types[778]), true),
                        new attribute(strings[3144],
                                      new named_type(IFC4X3_types[697]), true),
                        new attribute(strings[3147],
                                      new named_type(IFC4X3_types[697]), true),
                        new attribute(strings[3784],
                                      new named_type(IFC4X3_types[697]), true),
                        new attribute(strings[3785],
                                      new named_type(IFC4X3_types[698]), true),
                        new attribute(strings[3786],
                                      new named_type(IFC4X3_types[698]), true),
                        new attribute(strings[3787],
                                      new named_type(IFC4X3_types[698]), true),
                        new attribute(strings[3788],
                                      new named_type(IFC4X3_types[698]), true),
                        new attribute(strings[3153],
                                      new named_type(IFC4X3_types[1006]), true),
                        new attribute(strings[3149],
                                      new named_type(IFC4X3_types[585]), true),
                        new attribute(strings[3154],
                                      new named_type(IFC4X3_types[585]), true),
                        new attribute(strings[3155],
                                      new named_type(IFC4X3_types[585]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false, false, false, false,
                        false});
  ((entity *)IFC4X3_types[1295])
      ->set_attributes(
          {new attribute(strings[3141], new named_type(IFC4X3_types[1293]),
                         false),
           new attribute(strings[3159], new named_type(IFC4X3_types[1294]),
                         false),
           new attribute(strings[3354], new named_type(IFC4X3_types[778]),
                         true),
           new attribute(strings[3355], new named_type(IFC4X3_types[778]),
                         true),
           new attribute(strings[3153], new named_type(IFC4X3_types[1006]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1298])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1299]),
                         false),
           new attribute(strings[3782], new named_type(IFC4X3_types[1300]),
                         false),
           new attribute(strings[3160], new named_type(IFC4X3_types[87]), true),
           new attribute(strings[3783], new named_type(IFC4X3_types[574]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false});
  ((entity *)IFC4X3_types[1301])
      ->set_attributes(
          {new attribute(
               strings[3789],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X3_types[1308])),
               true),
           new attribute(
               strings[3790],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X3_types[1308])),
               true),
           new attribute(strings[2880], new named_type(IFC4X3_types[1302]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1303])
      ->set_attributes({new attribute(strings[3351],
                                      new named_type(IFC4X3_types[292]), false),
                        new attribute(strings[3791],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X3_types[738])),
                                      true),
                        new attribute(strings[2887],
                                      new named_type(IFC4X3_types[574]), true),
                        new attribute(strings[3792],
                                      new named_type(IFC4X3_types[358]), true),
                        new attribute(strings[3714],
                                      new named_type(IFC4X3_types[358]), true),
                        new attribute(strings[3758],
                                      new named_type(IFC4X3_types[292]), false),
                        new attribute(strings[3793],
                                      new named_type(IFC4X3_types[292]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false, false});
  ((entity *)IFC4X3_types[1304])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1305]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false});
  ((entity *)IFC4X3_types[1306])
      ->set_attributes(
          {new attribute(strings[2880], new named_type(IFC4X3_types[1307]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false});
  ((entity *)IFC4X3_types[1308])
      ->set_attributes({new attribute(strings[3794],
                                      new named_type(IFC4X3_types[878]), true),
                        new attribute(strings[3795],
                                      new named_type(IFC4X3_types[291]), true),
                        new attribute(strings[3796],
                                      new named_type(IFC4X3_types[291]), true)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1310])
      ->set_attributes(
          {new attribute(strings[3010], new named_type(IFC4X3_types[778]),
                         false),
           new attribute(strings[3698], new named_type(IFC4X3_types[778]),
                         false),
           new attribute(strings[2947], new named_type(IFC4X3_types[778]),
                         false),
           new attribute(strings[3225], new named_type(IFC4X3_types[778]),
                         false),
           new attribute(strings[3226], new named_type(IFC4X3_types[697]),
                         true),
           new attribute(strings[3247], new named_type(IFC4X3_types[697]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X3_types[1309])
      ->set_attributes({new attribute(strings[3009],
                                      new named_type(IFC4X3_types[574]), true)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X3_types[6])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3797], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X3_types[902]),
          ((entity *)IFC4X3_types[902])->attributes()[0])});
  ((entity *)IFC4X3_types[7])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3798], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X3_types[430]),
          ((entity *)IFC4X3_types[430])->attributes()[1])});
  ((entity *)IFC4X3_types[12])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3799], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[738]),
               ((entity *)IFC4X3_types[738])->attributes()[7]),
           new inverse_attribute(
               strings[3800], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[717]),
               ((entity *)IFC4X3_types[717])->attributes()[4])});
  ((entity *)IFC4X3_types[46])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3801], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC4X3_types[927]),
          ((entity *)IFC4X3_types[927])->attributes()[0])});
  ((entity *)IFC4X3_types[50])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3798], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X3_types[430]),
          ((entity *)IFC4X3_types[430])->attributes()[1])});
  ((entity *)IFC4X3_types[52])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3802], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[430]),
               ((entity *)IFC4X3_types[430])->attributes()[1]),
           new inverse_attribute(
               strings[3803], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[910]),
               ((entity *)IFC4X3_types[910])->attributes()[0]),
           new inverse_attribute(
               strings[3804], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[956]),
               ((entity *)IFC4X3_types[956])->attributes()[1]),
           new inverse_attribute(strings[3805], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4X3_types[53]),
                                 ((entity *)IFC4X3_types[53])->attributes()[1]),
           new inverse_attribute(
               strings[3806], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[53]),
               ((entity *)IFC4X3_types[53])->attributes()[0])});
  ((entity *)IFC4X3_types[169])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3807], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[911]),
               ((entity *)IFC4X3_types[911])->attributes()[0]),
           new inverse_attribute(
               strings[3808], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[170]),
               ((entity *)IFC4X3_types[170])->attributes()[0])});
  ((entity *)IFC4X3_types[170])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3809], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[911]),
               ((entity *)IFC4X3_types[911])->attributes()[0]),
           new inverse_attribute(
               strings[3808], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[170]),
               ((entity *)IFC4X3_types[170])->attributes()[0])});
  ((entity *)IFC4X3_types[213])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3802], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[430]),
               ((entity *)IFC4X3_types[430])->attributes()[1]),
           new inverse_attribute(
               strings[3810], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[957]),
               ((entity *)IFC4X3_types[957])->attributes()[0])});
  ((entity *)IFC4X3_types[226])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3811], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[934]),
               ((entity *)IFC4X3_types[934])->attributes()[0]),
           new inverse_attribute(
               strings[3812], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[930]),
               ((entity *)IFC4X3_types[930])->attributes()[0])});
  ((entity *)IFC4X3_types[228])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3798], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X3_types[430]),
          ((entity *)IFC4X3_types[430])->attributes()[1])});
  ((entity *)IFC4X3_types[229])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3813], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X3_types[903]),
          ((entity *)IFC4X3_types[903])->attributes()[0])});
  ((entity *)IFC4X3_types[233])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3798], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X3_types[430]),
          ((entity *)IFC4X3_types[430])->attributes()[1])});
  ((entity *)IFC4X3_types[245])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3814], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC4X3_types[244]),
          ((entity *)IFC4X3_types[244])->attributes()[0])});
  ((entity *)IFC4X3_types[257])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3815], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X3_types[929]),
               ((entity *)IFC4X3_types[929])->attributes()[1]),
           new inverse_attribute(
               strings[3816], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X3_types[928]),
               ((entity *)IFC4X3_types[928])->attributes()[1])});
  ((entity *)IFC4X3_types[320])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3817], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC4X3_types[938]),
          ((entity *)IFC4X3_types[938])->attributes()[0])});
  ((entity *)IFC4X3_types[322])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3818], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X3_types[922]),
          ((entity *)IFC4X3_types[922])->attributes()[1])});
  ((entity *)IFC4X3_types[324])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3819], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC4X3_types[938]),
          ((entity *)IFC4X3_types[938])->attributes()[1])});
  ((entity *)IFC4X3_types[331])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3820], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[913]),
               ((entity *)IFC4X3_types[913])->attributes()[0]),
           new inverse_attribute(
               strings[3821], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[333]),
               ((entity *)IFC4X3_types[333])->attributes()[1]),
           new inverse_attribute(
               strings[3822], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[332]),
               ((entity *)IFC4X3_types[332])->attributes()[1]),
           new inverse_attribute(
               strings[3823], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X3_types[332]),
               ((entity *)IFC4X3_types[332])->attributes()[0])});
  ((entity *)IFC4X3_types[333])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3824], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X3_types[913]),
          ((entity *)IFC4X3_types[913])->attributes()[0])});
  ((entity *)IFC4X3_types[395])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3825], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X3_types[937]),
               ((entity *)IFC4X3_types[937])->attributes()[1]),
           new inverse_attribute(
               strings[3826], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[919]),
               ((entity *)IFC4X3_types[919])->attributes()[1]),
           new inverse_attribute(
               strings[3827], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[939]),
               ((entity *)IFC4X3_types[939])->attributes()[1]),
           new inverse_attribute(
               strings[3828], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[939]),
               ((entity *)IFC4X3_types[939])->attributes()[0]),
           new inverse_attribute(
               strings[3829], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[942]),
               ((entity *)IFC4X3_types[942])->attributes()[0]),
           new inverse_attribute(
               strings[3830], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[949]),
               ((entity *)IFC4X3_types[949])->attributes()[0]),
           new inverse_attribute(
               strings[3831], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[926]),
               ((entity *)IFC4X3_types[926])->attributes()[0]),
           new inverse_attribute(
               strings[3832], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[946]),
               ((entity *)IFC4X3_types[946])->attributes()[1]),
           new inverse_attribute(
               strings[3833], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[919]),
               ((entity *)IFC4X3_types[919])->attributes()[2]),
           new inverse_attribute(
               strings[3801], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X3_types[927]),
               ((entity *)IFC4X3_types[927])->attributes()[0]),
           new inverse_attribute(
               strings[3834], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[928]),
               ((entity *)IFC4X3_types[928])->attributes()[0]),
           new inverse_attribute(
               strings[3835], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[899]),
               ((entity *)IFC4X3_types[899])->attributes()[0])});
  ((entity *)IFC4X3_types[429])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3836], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X3_types[430]),
          ((entity *)IFC4X3_types[430])->attributes()[0])});
  ((entity *)IFC4X3_types[431])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3837], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X3_types[946]),
          ((entity *)IFC4X3_types[946])->attributes()[0])});
  ((entity *)IFC4X3_types[436])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3838], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X3_types[1195]),
          ((entity *)IFC4X3_types[1195])->attributes()[1])});
  ((entity *)IFC4X3_types[456])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3839], inverse_attribute::unspecified_type, -1, -1,
          ((entity *)IFC4X3_types[942]),
          ((entity *)IFC4X3_types[942])->attributes()[1])});
  ((entity *)IFC4X3_types[457])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3840], inverse_attribute::unspecified_type, -1, -1,
          ((entity *)IFC4X3_types[949]),
          ((entity *)IFC4X3_types[949])->attributes()[1])});
  ((entity *)IFC4X3_types[508])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3841], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[510]),
               ((entity *)IFC4X3_types[510])->attributes()[0]),
           new inverse_attribute(
               strings[3814], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X3_types[244]),
               ((entity *)IFC4X3_types[244])->attributes()[0])});
  ((entity *)IFC4X3_types[523])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3842], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X3_types[522]),
               ((entity *)IFC4X3_types[522])->attributes()[2]),
           new inverse_attribute(
               strings[3843], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X3_types[522]),
               ((entity *)IFC4X3_types[522])->attributes()[1]),
           new inverse_attribute(
               strings[3844], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X3_types[522]),
               ((entity *)IFC4X3_types[522])->attributes()[0]),
           new inverse_attribute(
               strings[3845], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[1276]),
               ((entity *)IFC4X3_types[1276])->attributes()[0])});
  ((entity *)IFC4X3_types[527])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3846], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[904]),
               ((entity *)IFC4X3_types[904])->attributes()[0]),
           new inverse_attribute(
               strings[3847], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[943]),
               ((entity *)IFC4X3_types[943])->attributes()[0])});
  ((entity *)IFC4X3_types[546])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3848], inverse_attribute::set_type, 1, -1,
               ((entity *)IFC4X3_types[771]),
               ((entity *)IFC4X3_types[771])->attributes()[0]),
           new inverse_attribute(
               strings[3849], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X3_types[1193]),
               ((entity *)IFC4X3_types[1193])->attributes()[1])});
  ((entity *)IFC4X3_types[586])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3850], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[914]),
               ((entity *)IFC4X3_types[914])->attributes()[0]),
           new inverse_attribute(
               strings[3851], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[587]),
               ((entity *)IFC4X3_types[587])->attributes()[2])});
  ((entity *)IFC4X3_types[587])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3852], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X3_types[914]),
          ((entity *)IFC4X3_types[914])->attributes()[0])});
  ((entity *)IFC4X3_types[637])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3853], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X3_types[642]),
               ((entity *)IFC4X3_types[642])->attributes()[0]),
           new inverse_attribute(
               strings[3805], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[654]),
               ((entity *)IFC4X3_types[654])->attributes()[1]),
           new inverse_attribute(
               strings[3854], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X3_types[654]),
               ((entity *)IFC4X3_types[654])->attributes()[0])});
  ((entity *)IFC4X3_types[639])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3855], inverse_attribute::unspecified_type, -1, -1,
          ((entity *)IFC4X3_types[640]),
          ((entity *)IFC4X3_types[640])->attributes()[2])});
  ((entity *)IFC4X3_types[641])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3856], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[915]),
               ((entity *)IFC4X3_types[915])->attributes()[0]),
           new inverse_attribute(
               strings[3802], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[430]),
               ((entity *)IFC4X3_types[430])->attributes()[1]),
           new inverse_attribute(
               strings[3040], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[653]),
               ((entity *)IFC4X3_types[653])->attributes()[0])});
  ((entity *)IFC4X3_types[643])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3857], inverse_attribute::unspecified_type, -1, -1,
          ((entity *)IFC4X3_types[644]),
          ((entity *)IFC4X3_types[644])->attributes()[0])});
  ((entity *)IFC4X3_types[648])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3858], inverse_attribute::unspecified_type, -1, -1,
          ((entity *)IFC4X3_types[649]),
          ((entity *)IFC4X3_types[649])->attributes()[2])});
  ((entity *)IFC4X3_types[656])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3856], inverse_attribute::set_type, 1, -1,
          ((entity *)IFC4X3_types[915]),
          ((entity *)IFC4X3_types[915])->attributes()[0])});
  ((entity *)IFC4X3_types[700])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3859], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X3_types[933]),
               ((entity *)IFC4X3_types[933])->attributes()[0]),
           new inverse_attribute(
               strings[3812], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[933]),
               ((entity *)IFC4X3_types[933])->attributes()[1]),
           new inverse_attribute(
               strings[3860], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X3_types[936]),
               ((entity *)IFC4X3_types[936])->attributes()[0]),
           new inverse_attribute(
               strings[3811], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[934]),
               ((entity *)IFC4X3_types[934])->attributes()[0])});
  ((entity *)IFC4X3_types[701])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3861], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[901]),
               ((entity *)IFC4X3_types[901])->attributes()[0]),
           new inverse_attribute(
               strings[3862], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X3_types[940]),
               ((entity *)IFC4X3_types[940])->attributes()[1]),
           new inverse_attribute(
               strings[3863], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[940]),
               ((entity *)IFC4X3_types[940])->attributes()[0]),
           new inverse_attribute(
               strings[3864], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X3_types[930]),
               ((entity *)IFC4X3_types[930])->attributes()[1]),
           new inverse_attribute(
               strings[3865], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[900]),
               ((entity *)IFC4X3_types[900])->attributes()[0]),
           new inverse_attribute(
               strings[3866], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X3_types[900]),
               ((entity *)IFC4X3_types[900])->attributes()[1]),
           new inverse_attribute(
               strings[3867], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[909]),
               ((entity *)IFC4X3_types[909])->attributes()[0])});
  ((entity *)IFC4X3_types[704])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3868], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[801]),
               ((entity *)IFC4X3_types[801])->attributes()[0]),
           new inverse_attribute(
               strings[3869], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[704]),
               ((entity *)IFC4X3_types[704])->attributes()[0])});
  ((entity *)IFC4X3_types[714])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3870], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X3_types[937]),
          ((entity *)IFC4X3_types[937])->attributes()[0])});
  ((entity *)IFC4X3_types[717])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3871], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[718]),
               ((entity *)IFC4X3_types[718])->attributes()[1]),
           new inverse_attribute(
               strings[3806], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[718]),
               ((entity *)IFC4X3_types[718])->attributes()[0]),
           new inverse_attribute(
               strings[3872], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[739]),
               ((entity *)IFC4X3_types[739])->attributes()[1])});
  ((entity *)IFC4X3_types[738])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3873], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X3_types[739]),
          ((entity *)IFC4X3_types[739])->attributes()[0])});
  ((entity *)IFC4X3_types[743])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3802], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[430]),
               ((entity *)IFC4X3_types[430])->attributes()[1]),
           new inverse_attribute(
               strings[3874], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X3_types[741]),
               ((entity *)IFC4X3_types[741])->attributes()[0])});
  ((entity *)IFC4X3_types[775])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3875], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X3_types[922]),
               ((entity *)IFC4X3_types[922])->attributes()[0]),
           new inverse_attribute(
               strings[3833], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X3_types[921]),
               ((entity *)IFC4X3_types[921])->attributes()[1]),
           new inverse_attribute(
               strings[3826], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X3_types[921]),
               ((entity *)IFC4X3_types[921])->attributes()[0])});
  ((entity *)IFC4X3_types[776])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3801], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X3_types[927]),
               ((entity *)IFC4X3_types[927])->attributes()[0]),
           new inverse_attribute(
               strings[3876], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[941]),
               ((entity *)IFC4X3_types[941])->attributes()[0])});
  ((entity *)IFC4X3_types[799])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3877], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[944]),
               ((entity *)IFC4X3_types[944])->attributes()[0]),
           new inverse_attribute(
               strings[3878], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[944]),
               ((entity *)IFC4X3_types[944])->attributes()[1]),
           new inverse_attribute(
               strings[3879], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[906]),
               ((entity *)IFC4X3_types[906])->attributes()[0])});
  ((entity *)IFC4X3_types[801])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3880], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[907]),
               ((entity *)IFC4X3_types[907])->attributes()[0]),
           new inverse_attribute(
               strings[3881], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[941]),
               ((entity *)IFC4X3_types[941])->attributes()[1]),
           new inverse_attribute(
               strings[3847], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[943]),
               ((entity *)IFC4X3_types[943])->attributes()[0])});
  ((entity *)IFC4X3_types[802])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3882], inverse_attribute::set_type, 1, -1,
               ((entity *)IFC4X3_types[801]),
               ((entity *)IFC4X3_types[801])->attributes()[1]),
           new inverse_attribute(
               strings[3883], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[1006]),
               ((entity *)IFC4X3_types[1006])->attributes()[4])});
  ((entity *)IFC4X3_types[806])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3798], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[430]),
               ((entity *)IFC4X3_types[430])->attributes()[1]),
           new inverse_attribute(
               strings[3040], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[807]),
               ((entity *)IFC4X3_types[807])->attributes()[0])});
  ((entity *)IFC4X3_types[817])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3884], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[826]),
               ((entity *)IFC4X3_types[826])->attributes()[0]),
           new inverse_attribute(
               strings[3885], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[821]),
               ((entity *)IFC4X3_types[821])->attributes()[0]),
           new inverse_attribute(
               strings[3886], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[821]),
               ((entity *)IFC4X3_types[821])->attributes()[1]),
           new inverse_attribute(
               strings[3874], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[190]),
               ((entity *)IFC4X3_types[190])->attributes()[1]),
           new inverse_attribute(
               strings[3887], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[957]),
               ((entity *)IFC4X3_types[957])->attributes()[1]),
           new inverse_attribute(
               strings[3888], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[956]),
               ((entity *)IFC4X3_types[956])->attributes()[0])});
  ((entity *)IFC4X3_types[818])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3802], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X3_types[430]),
          ((entity *)IFC4X3_types[430])->attributes()[1])});
  ((entity *)IFC4X3_types[820])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3864], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X3_types[930]),
               ((entity *)IFC4X3_types[930])->attributes()[1]),
           new inverse_attribute(
               strings[3867], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[909]),
               ((entity *)IFC4X3_types[909])->attributes()[0])});
  ((entity *)IFC4X3_types[827])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3889], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[1240]),
               ((entity *)IFC4X3_types[1240])->attributes()[1]),
           new inverse_attribute(
               strings[3811], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[935]),
               ((entity *)IFC4X3_types[935])->attributes()[0]),
           new inverse_attribute(
               strings[3890], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[934]),
               ((entity *)IFC4X3_types[934])->attributes()[1])});
  ((entity *)IFC4X3_types[830])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3891], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X3_types[935]),
          ((entity *)IFC4X3_types[935])->attributes()[1])});
  ((entity *)IFC4X3_types[834])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3892], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[191]),
               ((entity *)IFC4X3_types[191])->attributes()[2]),
           new inverse_attribute(
               strings[3893], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[830]),
               ((entity *)IFC4X3_types[830])->attributes()[2])});
  ((entity *)IFC4X3_types[947])
      ->set_inverse_attributes({new inverse_attribute(
          strings[2911], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X3_types[947]),
          ((entity *)IFC4X3_types[947])->attributes()[0])});
  ((entity *)IFC4X3_types[948])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3894], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC4X3_types[948]),
          ((entity *)IFC4X3_types[948])->attributes()[0])});
  ((entity *)IFC4X3_types[951])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3895], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X3_types[954]),
               ((entity *)IFC4X3_types[954])->attributes()[1]),
           new inverse_attribute(
               strings[3896], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[792]),
               ((entity *)IFC4X3_types[792])->attributes()[2]),
           new inverse_attribute(
               strings[3897], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[803]),
               ((entity *)IFC4X3_types[803])->attributes()[2])});
  ((entity *)IFC4X3_types[952])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3898], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X3_types[951]),
          ((entity *)IFC4X3_types[951])->attributes()[0])});
  ((entity *)IFC4X3_types[953])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3899], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X3_types[792]),
               ((entity *)IFC4X3_types[792])->attributes()[2]),
           new inverse_attribute(
               strings[3900], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X3_types[1116]),
               ((entity *)IFC4X3_types[1116])->attributes()[0])});
  ((entity *)IFC4X3_types[954])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3883], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[1006]),
               ((entity *)IFC4X3_types[1006])->attributes()[4]),
           new inverse_attribute(
               strings[3901], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[628]),
               ((entity *)IFC4X3_types[628])->attributes()[0])});
  ((entity *)IFC4X3_types[955])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3902], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X3_types[908]),
          ((entity *)IFC4X3_types[908])->attributes()[0])});
  ((entity *)IFC4X3_types[995])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3903], inverse_attribute::set_type, 1, -1,
          ((entity *)IFC4X3_types[193]),
          ((entity *)IFC4X3_types[193])->attributes()[0])});
  ((entity *)IFC4X3_types[1006])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3802], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X3_types[430]),
          ((entity *)IFC4X3_types[430])->attributes()[1])});
  ((entity *)IFC4X3_types[1007])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3904], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC4X3_types[1006]),
          ((entity *)IFC4X3_types[1006])->attributes()[0])});
  ((entity *)IFC4X3_types[1042])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3834], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[929]),
               ((entity *)IFC4X3_types[929])->attributes()[0]),
           new inverse_attribute(
               strings[3837], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[946]),
               ((entity *)IFC4X3_types[946])->attributes()[0])});
  ((entity *)IFC4X3_types[1049])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3905], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[927]),
               ((entity *)IFC4X3_types[927])->attributes()[1]),
           new inverse_attribute(
               strings[3906], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[945]),
               ((entity *)IFC4X3_types[945])->attributes()[1]),
           new inverse_attribute(
               strings[3907], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[943]),
               ((entity *)IFC4X3_types[943])->attributes()[1]),
           new inverse_attribute(
               strings[3827], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[939]),
               ((entity *)IFC4X3_types[939])->attributes()[1]),
           new inverse_attribute(
               strings[3828], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[939]),
               ((entity *)IFC4X3_types[939])->attributes()[0])});
  ((entity *)IFC4X3_types[1075])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3908], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC4X3_types[923]),
          ((entity *)IFC4X3_types[923])->attributes()[1])});
  ((entity *)IFC4X3_types[1078])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3909], inverse_attribute::set_type, 1, -1,
          ((entity *)IFC4X3_types[924]),
          ((entity *)IFC4X3_types[924])->attributes()[1])});
  ((entity *)IFC4X3_types[1087])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3910], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X3_types[923]),
          ((entity *)IFC4X3_types[923])->attributes()[0])});
  ((entity *)IFC4X3_types[1092])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3911], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X3_types[1108]),
               ((entity *)IFC4X3_types[1108])->attributes()[1]),
           new inverse_attribute(
               strings[3912], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[1077]),
               ((entity *)IFC4X3_types[1077])->attributes()[2])});
  ((entity *)IFC4X3_types[1102])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3913], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X3_types[924]),
          ((entity *)IFC4X3_types[924])->attributes()[0])});
  ((entity *)IFC4X3_types[1108])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3914], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC4X3_types[1077]),
          ((entity *)IFC4X3_types[1077])->attributes()[3])});
  ((entity *)IFC4X3_types[1126])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3915], inverse_attribute::unspecified_type, -1, -1,
          ((entity *)IFC4X3_types[899]),
          ((entity *)IFC4X3_types[899])->attributes()[1])});
  ((entity *)IFC4X3_types[1140])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3916], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[1191]),
               ((entity *)IFC4X3_types[1191])->attributes()[0]),
           new inverse_attribute(
               strings[3917], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[1139]),
               ((entity *)IFC4X3_types[1139])->attributes()[0])});
  ((entity *)IFC4X3_types[1148])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3918], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X3_types[945]),
               ((entity *)IFC4X3_types[945])->attributes()[0]),
           new inverse_attribute(
               strings[3919], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[943]),
               ((entity *)IFC4X3_types[943])->attributes()[0])});
  ((entity *)IFC4X3_types[1176])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3920], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X3_types[544]),
               ((entity *)IFC4X3_types[544])->attributes()[0]),
           new inverse_attribute(
               strings[3921], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X3_types[549]),
               ((entity *)IFC4X3_types[549])->attributes()[0])});
  ((entity *)IFC4X3_types[1193])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3922], inverse_attribute::unspecified_type, -1, -1,
          ((entity *)IFC4X3_types[548]),
          ((entity *)IFC4X3_types[548])->attributes()[0])});
  ((entity *)IFC4X3_types[1209])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3798], inverse_attribute::set_type, 1, -1,
          ((entity *)IFC4X3_types[430]),
          ((entity *)IFC4X3_types[430])->attributes()[1])});
  ((entity *)IFC4X3_types[1240])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3923], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC4X3_types[936]),
          ((entity *)IFC4X3_types[936])->attributes()[1])});
  ((entity *)IFC4X3_types[1241])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3879], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X3_types[906]),
          ((entity *)IFC4X3_types[906])->attributes()[0])});
  ((entity *)IFC4X3_types[1242])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3880], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X3_types[907]),
          ((entity *)IFC4X3_types[907])->attributes()[0])});
  ((entity *)IFC4X3_types[1243])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3902], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X3_types[908]),
          ((entity *)IFC4X3_types[908])->attributes()[0])});
  ((entity *)IFC4X3_types[229])
      ->set_subtypes(
          {((entity *)IFC4X3_types[2]), ((entity *)IFC4X3_types[248]),
           ((entity *)IFC4X3_types[250]), ((entity *)IFC4X3_types[732]),
           ((entity *)IFC4X3_types[736]), ((entity *)IFC4X3_types[815]),
           ((entity *)IFC4X3_types[1301]), ((entity *)IFC4X3_types[1303])});
  ((entity *)IFC4X3_types[700])
      ->set_subtypes(
          {((entity *)IFC4X3_types[6]), ((entity *)IFC4X3_types[229]),
           ((entity *)IFC4X3_types[527]), ((entity *)IFC4X3_types[799]),
           ((entity *)IFC4X3_types[801]), ((entity *)IFC4X3_types[955])});
  ((entity *)IFC4X3_types[320])
      ->set_subtypes(
          {((entity *)IFC4X3_types[9]), ((entity *)IFC4X3_types[26]),
           ((entity *)IFC4X3_types[230]), ((entity *)IFC4X3_types[474]),
           ((entity *)IFC4X3_types[837]), ((entity *)IFC4X3_types[998]),
           ((entity *)IFC4X3_types[1245])});
  ((entity *)IFC4X3_types[321])
      ->set_subtypes(
          {((entity *)IFC4X3_types[10]), ((entity *)IFC4X3_types[27]),
           ((entity *)IFC4X3_types[231]), ((entity *)IFC4X3_types[475]),
           ((entity *)IFC4X3_types[838]), ((entity *)IFC4X3_types[999]),
           ((entity *)IFC4X3_types[1246])});
  ((entity *)IFC4X3_types[626])
      ->set_subtypes(
          {((entity *)IFC4X3_types[14]), ((entity *)IFC4X3_types[441])});
  ((entity *)IFC4X3_types[14])->set_subtypes({((entity *)IFC4X3_types[15])});
  ((entity *)IFC4X3_types[440])->set_subtypes({((entity *)IFC4X3_types[16])});
  ((entity *)IFC4X3_types[486])
      ->set_subtypes(
          {((entity *)IFC4X3_types[17]), ((entity *)IFC4X3_types[64]),
           ((entity *)IFC4X3_types[186]), ((entity *)IFC4X3_types[368]),
           ((entity *)IFC4X3_types[465]), ((entity *)IFC4X3_types[579]),
           ((entity *)IFC4X3_types[593]), ((entity *)IFC4X3_types[612]),
           ((entity *)IFC4X3_types[662]), ((entity *)IFC4X3_types[671]),
           ((entity *)IFC4X3_types[721]), ((entity *)IFC4X3_types[980]),
           ((entity *)IFC4X3_types[1013]), ((entity *)IFC4X3_types[1044]),
           ((entity *)IFC4X3_types[1064]), ((entity *)IFC4X3_types[1288])});
  ((entity *)IFC4X3_types[469])
      ->set_subtypes(
          {((entity *)IFC4X3_types[18]), ((entity *)IFC4X3_types[287]),
           ((entity *)IFC4X3_types[313]), ((entity *)IFC4X3_types[375]),
           ((entity *)IFC4X3_types[391]), ((entity *)IFC4X3_types[477]),
           ((entity *)IFC4X3_types[836]), ((entity *)IFC4X3_types[1145]),
           ((entity *)IFC4X3_types[1256])});
  ((entity *)IFC4X3_types[470])
      ->set_subtypes(
          {((entity *)IFC4X3_types[19]), ((entity *)IFC4X3_types[288]),
           ((entity *)IFC4X3_types[314]), ((entity *)IFC4X3_types[376]),
           ((entity *)IFC4X3_types[392]), ((entity *)IFC4X3_types[478]),
           ((entity *)IFC4X3_types[840]), ((entity *)IFC4X3_types[1146]),
           ((entity *)IFC4X3_types[1257])});
  ((entity *)IFC4X3_types[487])
      ->set_subtypes(
          {((entity *)IFC4X3_types[21]), ((entity *)IFC4X3_types[65]),
           ((entity *)IFC4X3_types[187]), ((entity *)IFC4X3_types[369]),
           ((entity *)IFC4X3_types[466]), ((entity *)IFC4X3_types[580]),
           ((entity *)IFC4X3_types[594]), ((entity *)IFC4X3_types[613]),
           ((entity *)IFC4X3_types[663]), ((entity *)IFC4X3_types[672]),
           ((entity *)IFC4X3_types[722]), ((entity *)IFC4X3_types[981]),
           ((entity *)IFC4X3_types[1014]), ((entity *)IFC4X3_types[1045]),
           ((entity *)IFC4X3_types[1065]), ((entity *)IFC4X3_types[1289])});
  ((entity *)IFC4X3_types[407])
      ->set_subtypes(
          {((entity *)IFC4X3_types[23]),   ((entity *)IFC4X3_types[84]),
           ((entity *)IFC4X3_types[128]),  ((entity *)IFC4X3_types[158]),
           ((entity *)IFC4X3_types[175]),  ((entity *)IFC4X3_types[201]),
           ((entity *)IFC4X3_types[238]),  ((entity *)IFC4X3_types[241]),
           ((entity *)IFC4X3_types[384]),  ((entity *)IFC4X3_types[387]),
           ((entity *)IFC4X3_types[410]),  ((entity *)IFC4X3_types[413]),
           ((entity *)IFC4X3_types[416]),  ((entity *)IFC4X3_types[530]),
           ((entity *)IFC4X3_types[535]),  ((entity *)IFC4X3_types[690]),
           ((entity *)IFC4X3_types[1032]), ((entity *)IFC4X3_types[1220]),
           ((entity *)IFC4X3_types[1237]), ((entity *)IFC4X3_types[1248])});
  ((entity *)IFC4X3_types[408])
      ->set_subtypes(
          {((entity *)IFC4X3_types[24]),   ((entity *)IFC4X3_types[85]),
           ((entity *)IFC4X3_types[129]),  ((entity *)IFC4X3_types[159]),
           ((entity *)IFC4X3_types[176]),  ((entity *)IFC4X3_types[202]),
           ((entity *)IFC4X3_types[239]),  ((entity *)IFC4X3_types[242]),
           ((entity *)IFC4X3_types[385]),  ((entity *)IFC4X3_types[388]),
           ((entity *)IFC4X3_types[411]),  ((entity *)IFC4X3_types[414]),
           ((entity *)IFC4X3_types[417]),  ((entity *)IFC4X3_types[531]),
           ((entity *)IFC4X3_types[536]),  ((entity *)IFC4X3_types[691]),
           ((entity *)IFC4X3_types[1033]), ((entity *)IFC4X3_types[1221]),
           ((entity *)IFC4X3_types[1238]), ((entity *)IFC4X3_types[1249])});
  ((entity *)IFC4X3_types[608])->set_subtypes({((entity *)IFC4X3_types[29])});
  ((entity *)IFC4X3_types[604])
      ->set_subtypes(
          {((entity *)IFC4X3_types[30]), ((entity *)IFC4X3_types[33]),
           ((entity *)IFC4X3_types[37]), ((entity *)IFC4X3_types[39])});
  ((entity *)IFC4X3_types[36])
      ->set_subtypes({((entity *)IFC4X3_types[31]),
                      ((entity *)IFC4X3_types[34]),
                      ((entity *)IFC4X3_types[40])});
  ((entity *)IFC4X3_types[801])
      ->set_subtypes(
          {((entity *)IFC4X3_types[46]), ((entity *)IFC4X3_types[395]),
           ((entity *)IFC4X3_types[604]), ((entity *)IFC4X3_types[775]),
           ((entity *)IFC4X3_types[776]), ((entity *)IFC4X3_types[1049]),
           ((entity *)IFC4X3_types[1075]), ((entity *)IFC4X3_types[1087])});
  ((entity *)IFC4X3_types[509])
      ->set_subtypes(
          {((entity *)IFC4X3_types[47]),   ((entity *)IFC4X3_types[91]),
           ((entity *)IFC4X3_types[101]),  ((entity *)IFC4X3_types[148]),
           ((entity *)IFC4X3_types[151]),  ((entity *)IFC4X3_types[263]),
           ((entity *)IFC4X3_types[272]),  ((entity *)IFC4X3_types[306]),
           ((entity *)IFC4X3_types[437]),  ((entity *)IFC4X3_types[459]),
           ((entity *)IFC4X3_types[460]),  ((entity *)IFC4X3_types[511]),
           ((entity *)IFC4X3_types[528]),  ((entity *)IFC4X3_types[597]),
           ((entity *)IFC4X3_types[756]),  ((entity *)IFC4X3_types[758]),
           ((entity *)IFC4X3_types[765]),  ((entity *)IFC4X3_types[989]),
           ((entity *)IFC4X3_types[995]),  ((entity *)IFC4X3_types[1011]),
           ((entity *)IFC4X3_types[1036]), ((entity *)IFC4X3_types[1123]),
           ((entity *)IFC4X3_types[1177]), ((entity *)IFC4X3_types[1183]),
           ((entity *)IFC4X3_types[1260])});
  ((entity *)IFC4X3_types[958])
      ->set_subtypes(
          {((entity *)IFC4X3_types[53]), ((entity *)IFC4X3_types[267]),
           ((entity *)IFC4X3_types[332]), ((entity *)IFC4X3_types[430]),
           ((entity *)IFC4X3_types[654]), ((entity *)IFC4X3_types[718]),
           ((entity *)IFC4X3_types[821]), ((entity *)IFC4X3_types[956]),
           ((entity *)IFC4X3_types[957])});
  ((entity *)IFC4X3_types[806])
      ->set_subtypes(
          {((entity *)IFC4X3_types[54]), ((entity *)IFC4X3_types[55]),
           ((entity *)IFC4X3_types[196]), ((entity *)IFC4X3_types[299]),
           ((entity *)IFC4X3_types[713]), ((entity *)IFC4X3_types[725])});
  ((entity *)IFC4X3_types[54])->set_subtypes({((entity *)IFC4X3_types[56])});
  ((entity *)IFC4X3_types[527])
      ->set_subtypes(
          {((entity *)IFC4X3_types[62]), ((entity *)IFC4X3_types[560]),
           ((entity *)IFC4X3_types[1092]), ((entity *)IFC4X3_types[1108]),
           ((entity *)IFC4X3_types[1148])});
  ((entity *)IFC4X3_types[725])
      ->set_subtypes(
          {((entity *)IFC4X3_types[63]), ((entity *)IFC4X3_types[266]),
           ((entity *)IFC4X3_types[166]), ((entity *)IFC4X3_types[406]),
           ((entity *)IFC4X3_types[565]), ((entity *)IFC4X3_types[620]),
           ((entity *)IFC4X3_types[875]), ((entity *)IFC4X3_types[1236]),
           ((entity *)IFC4X3_types[1230]), ((entity *)IFC4X3_types[1254]),
           ((entity *)IFC4X3_types[1310])});
  ((entity *)IFC4X3_types[756])
      ->set_subtypes(
          {((entity *)IFC4X3_types[67]), ((entity *)IFC4X3_types[69]),
           ((entity *)IFC4X3_types[70]), ((entity *)IFC4X3_types[71])});
  ((entity *)IFC4X3_types[99])
      ->set_subtypes(
          {((entity *)IFC4X3_types[108]), ((entity *)IFC4X3_types[193]),
           ((entity *)IFC4X3_types[545]), ((entity *)IFC4X3_types[772]),
           ((entity *)IFC4X3_types[1233])});
  ((entity *)IFC4X3_types[108])->set_subtypes({((entity *)IFC4X3_types[110])});
  ((entity *)IFC4X3_types[100])
      ->set_subtypes(
          {((entity *)IFC4X3_types[111]), ((entity *)IFC4X3_types[273]),
           ((entity *)IFC4X3_types[274]), ((entity *)IFC4X3_types[877])});
  ((entity *)IFC4X3_types[111])->set_subtypes({((entity *)IFC4X3_types[113])});
  ((entity *)IFC4X3_types[124])
      ->set_subtypes(
          {((entity *)IFC4X3_types[72]),   ((entity *)IFC4X3_types[75]),
           ((entity *)IFC4X3_types[118]),  ((entity *)IFC4X3_types[161]),
           ((entity *)IFC4X3_types[183]),  ((entity *)IFC4X3_types[254]),
           ((entity *)IFC4X3_types[257]),  ((entity *)IFC4X3_types[268]),
           ((entity *)IFC4X3_types[295]),  ((entity *)IFC4X3_types[336]),
           ((entity *)IFC4X3_types[362]),  ((entity *)IFC4X3_types[493]),
           ((entity *)IFC4X3_types[570]),  ((entity *)IFC4X3_types[665]),
           ((entity *)IFC4X3_types[687]),  ((entity *)IFC4X3_types[694]),
           ((entity *)IFC4X3_types[728]),  ((entity *)IFC4X3_types[762]),
           ((entity *)IFC4X3_types[854]),  ((entity *)IFC4X3_types[855]),
           ((entity *)IFC4X3_types[864]),  ((entity *)IFC4X3_types[865]),
           ((entity *)IFC4X3_types[971]),  ((entity *)IFC4X3_types[1003]),
           ((entity *)IFC4X3_types[1028]), ((entity *)IFC4X3_types[1067]),
           ((entity *)IFC4X3_types[1068]), ((entity *)IFC4X3_types[1217]),
           ((entity *)IFC4X3_types[1281]), ((entity *)IFC4X3_types[1291])});
  ((entity *)IFC4X3_types[125])
      ->set_subtypes(
          {((entity *)IFC4X3_types[73]),   ((entity *)IFC4X3_types[76]),
           ((entity *)IFC4X3_types[119]),  ((entity *)IFC4X3_types[162]),
           ((entity *)IFC4X3_types[184]),  ((entity *)IFC4X3_types[255]),
           ((entity *)IFC4X3_types[258]),  ((entity *)IFC4X3_types[269]),
           ((entity *)IFC4X3_types[296]),  ((entity *)IFC4X3_types[343]),
           ((entity *)IFC4X3_types[494]),  ((entity *)IFC4X3_types[571]),
           ((entity *)IFC4X3_types[666]),  ((entity *)IFC4X3_types[688]),
           ((entity *)IFC4X3_types[695]),  ((entity *)IFC4X3_types[729]),
           ((entity *)IFC4X3_types[763]),  ((entity *)IFC4X3_types[858]),
           ((entity *)IFC4X3_types[856]),  ((entity *)IFC4X3_types[866]),
           ((entity *)IFC4X3_types[868]),  ((entity *)IFC4X3_types[972]),
           ((entity *)IFC4X3_types[1004]), ((entity *)IFC4X3_types[1029]),
           ((entity *)IFC4X3_types[1069]), ((entity *)IFC4X3_types[1071]),
           ((entity *)IFC4X3_types[1218]), ((entity *)IFC4X3_types[1283]),
           ((entity *)IFC4X3_types[1298])});
  ((entity *)IFC4X3_types[1140])
      ->set_subtypes({((entity *)IFC4X3_types[82]),
                      ((entity *)IFC4X3_types[540]),
                      ((entity *)IFC4X3_types[755])});
  ((entity *)IFC4X3_types[263])
      ->set_subtypes(
          {((entity *)IFC4X3_types[83]), ((entity *)IFC4X3_types[876]),
           ((entity *)IFC4X3_types[964]), ((entity *)IFC4X3_types[965]),
           ((entity *)IFC4X3_types[1061])});
  ((entity *)IFC4X3_types[91])->set_subtypes({((entity *)IFC4X3_types[88])});
  ((entity *)IFC4X3_types[515])
      ->set_subtypes({((entity *)IFC4X3_types[92]),
                      ((entity *)IFC4X3_types[513]),
                      ((entity *)IFC4X3_types[514])});
  ((entity *)IFC4X3_types[194])->set_subtypes({((entity *)IFC4X3_types[94])});
  ((entity *)IFC4X3_types[93])
      ->set_subtypes({((entity *)IFC4X3_types[95]),
                      ((entity *)IFC4X3_types[96]),
                      ((entity *)IFC4X3_types[97])});
  ((entity *)IFC4X3_types[97])->set_subtypes({((entity *)IFC4X3_types[98])});
  ((entity *)IFC4X3_types[272])
      ->set_subtypes(
          {((entity *)IFC4X3_types[99]), ((entity *)IFC4X3_types[204]),
           ((entity *)IFC4X3_types[603]), ((entity *)IFC4X3_types[709]),
           ((entity *)IFC4X3_types[731]), ((entity *)IFC4X3_types[774]),
           ((entity *)IFC4X3_types[1063]), ((entity *)IFC4X3_types[1124])});
  ((entity *)IFC4X3_types[1123])
      ->set_subtypes(
          {((entity *)IFC4X3_types[100]), ((entity *)IFC4X3_types[396]),
           ((entity *)IFC4X3_types[990]), ((entity *)IFC4X3_types[1144])});
  ((entity *)IFC4X3_types[528])
      ->set_subtypes(
          {((entity *)IFC4X3_types[103]), ((entity *)IFC4X3_types[770])});
  ((entity *)IFC4X3_types[443])
      ->set_subtypes(
          {((entity *)IFC4X3_types[104]), ((entity *)IFC4X3_types[114]),
           ((entity *)IFC4X3_types[629]), ((entity *)IFC4X3_types[860]),
           ((entity *)IFC4X3_types[966])});
  ((entity *)IFC4X3_types[444])
      ->set_subtypes(
          {((entity *)IFC4X3_types[105]), ((entity *)IFC4X3_types[445]),
           ((entity *)IFC4X3_types[631]), ((entity *)IFC4X3_types[861]),
           ((entity *)IFC4X3_types[967])});
  ((entity *)IFC4X3_types[400])
      ->set_subtypes(
          {((entity *)IFC4X3_types[115]), ((entity *)IFC4X3_types[310]),
           ((entity *)IFC4X3_types[452]), ((entity *)IFC4X3_types[541]),
           ((entity *)IFC4X3_types[659]), ((entity *)IFC4X3_types[894]),
           ((entity *)IFC4X3_types[1012]), ((entity *)IFC4X3_types[1268]),
           ((entity *)IFC4X3_types[1271])});
  ((entity *)IFC4X3_types[401])
      ->set_subtypes(
          {((entity *)IFC4X3_types[116]), ((entity *)IFC4X3_types[311]),
           ((entity *)IFC4X3_types[453]), ((entity *)IFC4X3_types[542]),
           ((entity *)IFC4X3_types[660]), ((entity *)IFC4X3_types[895]),
           ((entity *)IFC4X3_types[1016]), ((entity *)IFC4X3_types[1269]),
           ((entity *)IFC4X3_types[1272])});
  ((entity *)IFC4X3_types[1052])
      ->set_subtypes(
          {((entity *)IFC4X3_types[121]), ((entity *)IFC4X3_types[443]),
           ((entity *)IFC4X3_types[444]), ((entity *)IFC4X3_types[1024]),
           ((entity *)IFC4X3_types[1042])});
  ((entity *)IFC4X3_types[1148])
      ->set_subtypes(
          {((entity *)IFC4X3_types[122]), ((entity *)IFC4X3_types[126]),
           ((entity *)IFC4X3_types[328]), ((entity *)IFC4X3_types[1077]),
           ((entity *)IFC4X3_types[1309])});
  ((entity *)IFC4X3_types[395])
      ->set_subtypes(
          {((entity *)IFC4X3_types[124]), ((entity *)IFC4X3_types[167]),
           ((entity *)IFC4X3_types[322]), ((entity *)IFC4X3_types[397]),
           ((entity *)IFC4X3_types[400]), ((entity *)IFC4X3_types[455]),
           ((entity *)IFC4X3_types[498]), ((entity *)IFC4X3_types[503]),
           ((entity *)IFC4X3_types[516]), ((entity *)IFC4X3_types[1225]),
           ((entity *)IFC4X3_types[1274])});
  ((entity *)IFC4X3_types[404])
      ->set_subtypes(
          {((entity *)IFC4X3_types[125]), ((entity *)IFC4X3_types[168]),
           ((entity *)IFC4X3_types[323]), ((entity *)IFC4X3_types[398]),
           ((entity *)IFC4X3_types[401]), ((entity *)IFC4X3_types[499]),
           ((entity *)IFC4X3_types[504]), ((entity *)IFC4X3_types[1226])});
  ((entity *)IFC4X3_types[472])
      ->set_subtypes(
          {((entity *)IFC4X3_types[131]), ((entity *)IFC4X3_types[137]),
           ((entity *)IFC4X3_types[349]), ((entity *)IFC4X3_types[567]),
           ((entity *)IFC4X3_types[749])});
  ((entity *)IFC4X3_types[473])
      ->set_subtypes(
          {((entity *)IFC4X3_types[132]), ((entity *)IFC4X3_types[138]),
           ((entity *)IFC4X3_types[350]), ((entity *)IFC4X3_types[568]),
           ((entity *)IFC4X3_types[750])});
  ((entity *)IFC4X3_types[482])
      ->set_subtypes(
          {((entity *)IFC4X3_types[134]), ((entity *)IFC4X3_types[140]),
           ((entity *)IFC4X3_types[235]), ((entity *)IFC4X3_types[352]),
           ((entity *)IFC4X3_types[752])});
  ((entity *)IFC4X3_types[483])
      ->set_subtypes(
          {((entity *)IFC4X3_types[135]), ((entity *)IFC4X3_types[141]),
           ((entity *)IFC4X3_types[236]), ((entity *)IFC4X3_types[353]),
           ((entity *)IFC4X3_types[753])});
  ((entity *)IFC4X3_types[295])
      ->set_subtypes(
          {((entity *)IFC4X3_types[143]), ((entity *)IFC4X3_types[745])});
  ((entity *)IFC4X3_types[296])
      ->set_subtypes(
          {((entity *)IFC4X3_types[144]), ((entity *)IFC4X3_types[747])});
  ((entity *)IFC4X3_types[765])
      ->set_subtypes(
          {((entity *)IFC4X3_types[147]), ((entity *)IFC4X3_types[766]),
           ((entity *)IFC4X3_types[767]), ((entity *)IFC4X3_types[768])});
  ((entity *)IFC4X3_types[148])
      ->set_subtypes(
          {((entity *)IFC4X3_types[149]), ((entity *)IFC4X3_types[150])});
  ((entity *)IFC4X3_types[151])
      ->set_subtypes(
          {((entity *)IFC4X3_types[152]), ((entity *)IFC4X3_types[154])});
  ((entity *)IFC4X3_types[152])->set_subtypes({((entity *)IFC4X3_types[153])});
  ((entity *)IFC4X3_types[154])->set_subtypes({((entity *)IFC4X3_types[155])});
  ((entity *)IFC4X3_types[55])->set_subtypes({((entity *)IFC4X3_types[156])});
  ((entity *)IFC4X3_types[204])
      ->set_subtypes(
          {((entity *)IFC4X3_types[164]), ((entity *)IFC4X3_types[405])});
  ((entity *)IFC4X3_types[166])->set_subtypes({((entity *)IFC4X3_types[165])});
  ((entity *)IFC4X3_types[425])
      ->set_subtypes({((entity *)IFC4X3_types[169]),
                      ((entity *)IFC4X3_types[331]),
                      ((entity *)IFC4X3_types[586])});
  ((entity *)IFC4X3_types[429])
      ->set_subtypes(
          {((entity *)IFC4X3_types[170]), ((entity *)IFC4X3_types[333]),
           ((entity *)IFC4X3_types[426]), ((entity *)IFC4X3_types[427]),
           ((entity *)IFC4X3_types[428]), ((entity *)IFC4X3_types[587])});
  ((entity *)IFC4X3_types[205])
      ->set_subtypes(
          {((entity *)IFC4X3_types[173]), ((entity *)IFC4X3_types[716])});
  ((entity *)IFC4X3_types[1063])
      ->set_subtypes(
          {((entity *)IFC4X3_types[174]), ((entity *)IFC4X3_types[247]),
           ((entity *)IFC4X3_types[985]), ((entity *)IFC4X3_types[1002]),
           ((entity *)IFC4X3_types[1022]), ((entity *)IFC4X3_types[1204])});
  ((entity *)IFC4X3_types[182])->set_subtypes({((entity *)IFC4X3_types[180])});
  ((entity *)IFC4X3_types[791])
      ->set_subtypes(
          {((entity *)IFC4X3_types[181]), ((entity *)IFC4X3_types[182]),
           ((entity *)IFC4X3_types[282]), ((entity *)IFC4X3_types[283]),
           ((entity *)IFC4X3_types[284]), ((entity *)IFC4X3_types[544]),
           ((entity *)IFC4X3_types[785]), ((entity *)IFC4X3_types[1135]),
           ((entity *)IFC4X3_types[1136]), ((entity *)IFC4X3_types[1138]),
           ((entity *)IFC4X3_types[1139]), ((entity *)IFC4X3_types[1140]),
           ((entity *)IFC4X3_types[1188]), ((entity *)IFC4X3_types[1189]),
           ((entity *)IFC4X3_types[1191]), ((entity *)IFC4X3_types[1196]),
           ((entity *)IFC4X3_types[1197])});
  ((entity *)IFC4X3_types[817])
      ->set_subtypes(
          {((entity *)IFC4X3_types[190]), ((entity *)IFC4X3_types[1018])});
  ((entity *)IFC4X3_types[834])
      ->set_subtypes(
          {((entity *)IFC4X3_types[191]), ((entity *)IFC4X3_types[1019])});
  ((entity *)IFC4X3_types[193])
      ->set_subtypes({((entity *)IFC4X3_types[194]),
                      ((entity *)IFC4X3_types[521]),
                      ((entity *)IFC4X3_types[996])});
  ((entity *)IFC4X3_types[995])
      ->set_subtypes(
          {((entity *)IFC4X3_types[195]), ((entity *)IFC4X3_types[280])});
  ((entity *)IFC4X3_types[480])
      ->set_subtypes({((entity *)IFC4X3_types[198]),
                      ((entity *)IFC4X3_types[449]),
                      ((entity *)IFC4X3_types[842])});
  ((entity *)IFC4X3_types[481])
      ->set_subtypes({((entity *)IFC4X3_types[199]),
                      ((entity *)IFC4X3_types[450]),
                      ((entity *)IFC4X3_types[843])});
  ((entity *)IFC4X3_types[1213])
      ->set_subtypes(
          {((entity *)IFC4X3_types[205]), ((entity *)IFC4X3_types[365]),
           ((entity *)IFC4X3_types[436]), ((entity *)IFC4X3_types[438]),
           ((entity *)IFC4X3_types[619]), ((entity *)IFC4X3_types[727]),
           ((entity *)IFC4X3_types[1265])});
  ((entity *)IFC4X3_types[207])
      ->set_subtypes(
          {((entity *)IFC4X3_types[206]), ((entity *)IFC4X3_types[209]),
           ((entity *)IFC4X3_types[210]), ((entity *)IFC4X3_types[212])});
  ((entity *)IFC4X3_types[209])->set_subtypes({((entity *)IFC4X3_types[208])});
  ((entity *)IFC4X3_types[224])
      ->set_subtypes(
          {((entity *)IFC4X3_types[215]), ((entity *)IFC4X3_types[218]),
           ((entity *)IFC4X3_types[221]), ((entity *)IFC4X3_types[260]),
           ((entity *)IFC4X3_types[575]), ((entity *)IFC4X3_types[1119])});
  ((entity *)IFC4X3_types[225])
      ->set_subtypes(
          {((entity *)IFC4X3_types[216]), ((entity *)IFC4X3_types[219]),
           ((entity *)IFC4X3_types[222]), ((entity *)IFC4X3_types[261]),
           ((entity *)IFC4X3_types[576]), ((entity *)IFC4X3_types[1120])});
  ((entity *)IFC4X3_types[955])->set_subtypes({((entity *)IFC4X3_types[224])});
  ((entity *)IFC4X3_types[1243])->set_subtypes({((entity *)IFC4X3_types[225])});
  ((entity *)IFC4X3_types[701])
      ->set_subtypes({((entity *)IFC4X3_types[226]),
                      ((entity *)IFC4X3_types[700]),
                      ((entity *)IFC4X3_types[1240])});
  ((entity *)IFC4X3_types[693])
      ->set_subtypes({((entity *)IFC4X3_types[228]),
                      ((entity *)IFC4X3_types[233]),
                      ((entity *)IFC4X3_types[1025])});
  ((entity *)IFC4X3_types[233])->set_subtypes({((entity *)IFC4X3_types[234])});
  ((entity *)IFC4X3_types[50])->set_subtypes({((entity *)IFC4X3_types[252])});
  ((entity *)IFC4X3_types[1036])
      ->set_subtypes(
          {((entity *)IFC4X3_types[265]), ((entity *)IFC4X3_types[626]),
           ((entity *)IFC4X3_types[987]), ((entity *)IFC4X3_types[1141]),
           ((entity *)IFC4X3_types[1142])});
  ((entity *)IFC4X3_types[794])
      ->set_subtypes(
          {((entity *)IFC4X3_types[281]), ((entity *)IFC4X3_types[458]),
           ((entity *)IFC4X3_types[1133]), ((entity *)IFC4X3_types[1186])});
  ((entity *)IFC4X3_types[396])
      ->set_subtypes(
          {((entity *)IFC4X3_types[286]), ((entity *)IFC4X3_types[760]),
           ((entity *)IFC4X3_types[1062]), ((entity *)IFC4X3_types[1215])});
  ((entity *)IFC4X3_types[1141])
      ->set_subtypes({((entity *)IFC4X3_types[308]),
                      ((entity *)IFC4X3_types[434]),
                      ((entity *)IFC4X3_types[962])});
  ((entity *)IFC4X3_types[468])->set_subtypes({((entity *)IFC4X3_types[309])});
  ((entity *)IFC4X3_types[324])
      ->set_subtypes(
          {((entity *)IFC4X3_types[316]), ((entity *)IFC4X3_types[407]),
           ((entity *)IFC4X3_types[469]), ((entity *)IFC4X3_types[472]),
           ((entity *)IFC4X3_types[480]), ((entity *)IFC4X3_types[482]),
           ((entity *)IFC4X3_types[484]), ((entity *)IFC4X3_types[486]),
           ((entity *)IFC4X3_types[488])});
  ((entity *)IFC4X3_types[325])
      ->set_subtypes(
          {((entity *)IFC4X3_types[317]), ((entity *)IFC4X3_types[408]),
           ((entity *)IFC4X3_types[470]), ((entity *)IFC4X3_types[473]),
           ((entity *)IFC4X3_types[481]), ((entity *)IFC4X3_types[483]),
           ((entity *)IFC4X3_types[485]), ((entity *)IFC4X3_types[487]),
           ((entity *)IFC4X3_types[489])});
  ((entity *)IFC4X3_types[328])->set_subtypes({((entity *)IFC4X3_types[319])});
  ((entity *)IFC4X3_types[322])
      ->set_subtypes(
          {((entity *)IFC4X3_types[320]), ((entity *)IFC4X3_types[324])});
  ((entity *)IFC4X3_types[323])
      ->set_subtypes(
          {((entity *)IFC4X3_types[321]), ((entity *)IFC4X3_types[325])});
  ((entity *)IFC4X3_types[775])->set_subtypes({((entity *)IFC4X3_types[326])});
  ((entity *)IFC4X3_types[787])
      ->set_subtypes(
          {((entity *)IFC4X3_types[337]), ((entity *)IFC4X3_types[340]),
           ((entity *)IFC4X3_types[735]), ((entity *)IFC4X3_types[888]),
           ((entity *)IFC4X3_types[1292]), ((entity *)IFC4X3_types[1295])});
  ((entity *)IFC4X3_types[783])->set_subtypes({((entity *)IFC4X3_types[347])});
  ((entity *)IFC4X3_types[784])->set_subtypes({((entity *)IFC4X3_types[348])});
  ((entity *)IFC4X3_types[488])
      ->set_subtypes(
          {((entity *)IFC4X3_types[355]), ((entity *)IFC4X3_types[381]),
           ((entity *)IFC4X3_types[462]), ((entity *)IFC4X3_types[554])});
  ((entity *)IFC4X3_types[489])
      ->set_subtypes(
          {((entity *)IFC4X3_types[356]), ((entity *)IFC4X3_types[382]),
           ((entity *)IFC4X3_types[463]), ((entity *)IFC4X3_types[555])});
  ((entity *)IFC4X3_types[457])
      ->set_subtypes({((entity *)IFC4X3_types[360]),
                      ((entity *)IFC4X3_types[714]),
                      ((entity *)IFC4X3_types[1277])});
  ((entity *)IFC4X3_types[362])
      ->set_subtypes(
          {((entity *)IFC4X3_types[363]), ((entity *)IFC4X3_types[885])});
  ((entity *)IFC4X3_types[365])
      ->set_subtypes({((entity *)IFC4X3_types[366]),
                      ((entity *)IFC4X3_types[719]),
                      ((entity *)IFC4X3_types[1122])});
  ((entity *)IFC4X3_types[619])
      ->set_subtypes({((entity *)IFC4X3_types[367]),
                      ((entity *)IFC4X3_types[773]),
                      ((entity *)IFC4X3_types[1266])});
  ((entity *)IFC4X3_types[484])
      ->set_subtypes(
          {((entity *)IFC4X3_types[378]), ((entity *)IFC4X3_types[1155])});
  ((entity *)IFC4X3_types[485])
      ->set_subtypes(
          {((entity *)IFC4X3_types[379]), ((entity *)IFC4X3_types[1156])});
  ((entity *)IFC4X3_types[849])->set_subtypes({((entity *)IFC4X3_types[403])});
  ((entity *)IFC4X3_types[1242])
      ->set_subtypes(
          {((entity *)IFC4X3_types[404]), ((entity *)IFC4X3_types[1050])});
  ((entity *)IFC4X3_types[799])
      ->set_subtypes({((entity *)IFC4X3_types[419]),
                      ((entity *)IFC4X3_types[796]),
                      ((entity *)IFC4X3_types[1158])});
  ((entity *)IFC4X3_types[983])
      ->set_subtypes(
          {((entity *)IFC4X3_types[420]), ((entity *)IFC4X3_types[578]),
           ((entity *)IFC4X3_types[961]), ((entity *)IFC4X3_types[1160]),
           ((entity *)IFC4X3_types[1308])});
  ((entity *)IFC4X3_types[1241])
      ->set_subtypes({((entity *)IFC4X3_types[422]),
                      ((entity *)IFC4X3_types[797]),
                      ((entity *)IFC4X3_types[1162])});
  ((entity *)IFC4X3_types[818])
      ->set_subtypes(
          {((entity *)IFC4X3_types[424]), ((entity *)IFC4X3_types[786]),
           ((entity *)IFC4X3_types[817]), ((entity *)IFC4X3_types[823])});
  ((entity *)IFC4X3_types[433])->set_subtypes({((entity *)IFC4X3_types[431])});
  ((entity *)IFC4X3_types[1049])
      ->set_subtypes({((entity *)IFC4X3_types[433]),
                      ((entity *)IFC4X3_types[1052]),
                      ((entity *)IFC4X3_types[1054])});
  ((entity *)IFC4X3_types[434])->set_subtypes({((entity *)IFC4X3_types[435])});
  ((entity *)IFC4X3_types[438])->set_subtypes({((entity *)IFC4X3_types[439])});
  ((entity *)IFC4X3_types[436])->set_subtypes({((entity *)IFC4X3_types[440])});
  ((entity *)IFC4X3_types[441])->set_subtypes({((entity *)IFC4X3_types[442])});
  ((entity *)IFC4X3_types[1079])
      ->set_subtypes(
          {((entity *)IFC4X3_types[448]), ((entity *)IFC4X3_types[1031])});
  ((entity *)IFC4X3_types[455])
      ->set_subtypes({((entity *)IFC4X3_types[456]),
                      ((entity *)IFC4X3_types[457]),
                      ((entity *)IFC4X3_types[1126])});
  ((entity *)IFC4X3_types[308])
      ->set_subtypes(
          {((entity *)IFC4X3_types[468]), ((entity *)IFC4X3_types[1125])});
  ((entity *)IFC4X3_types[498])
      ->set_subtypes(
          {((entity *)IFC4X3_types[500]), ((entity *)IFC4X3_types[1149])});
  ((entity *)IFC4X3_types[499])
      ->set_subtypes(
          {((entity *)IFC4X3_types[501]), ((entity *)IFC4X3_types[1150])});
  ((entity *)IFC4X3_types[511])->set_subtypes({((entity *)IFC4X3_types[506])});
  ((entity *)IFC4X3_types[952])->set_subtypes({((entity *)IFC4X3_types[508])});
  ((entity *)IFC4X3_types[953])
      ->set_subtypes(
          {((entity *)IFC4X3_types[509]), ((entity *)IFC4X3_types[628]),
           ((entity *)IFC4X3_types[1116]), ((entity *)IFC4X3_types[1213])});
  ((entity *)IFC4X3_types[508])->set_subtypes({((entity *)IFC4X3_types[510])});
  ((entity *)IFC4X3_types[516])
      ->set_subtypes(
          {((entity *)IFC4X3_types[515]), ((entity *)IFC4X3_types[517])});
  ((entity *)IFC4X3_types[776])
      ->set_subtypes({((entity *)IFC4X3_types[522]),
                      ((entity *)IFC4X3_types[608]),
                      ((entity *)IFC4X3_types[881])});
  ((entity *)IFC4X3_types[704])
      ->set_subtypes({((entity *)IFC4X3_types[524]),
                      ((entity *)IFC4X3_types[607]),
                      ((entity *)IFC4X3_types[616])});
  ((entity *)IFC4X3_types[1177])
      ->set_subtypes(
          {((entity *)IFC4X3_types[546]), ((entity *)IFC4X3_types[1176])});
  ((entity *)IFC4X3_types[546])->set_subtypes({((entity *)IFC4X3_types[547])});
  ((entity *)IFC4X3_types[549])
      ->set_subtypes(
          {((entity *)IFC4X3_types[548]), ((entity *)IFC4X3_types[550])});
  ((entity *)IFC4X3_types[1191])
      ->set_subtypes({((entity *)IFC4X3_types[549]),
                      ((entity *)IFC4X3_types[1192]),
                      ((entity *)IFC4X3_types[1195])});
  ((entity *)IFC4X3_types[1124])
      ->set_subtypes(
          {((entity *)IFC4X3_types[559]), ((entity *)IFC4X3_types[984])});
  ((entity *)IFC4X3_types[1209])
      ->set_subtypes(
          {((entity *)IFC4X3_types[563]), ((entity *)IFC4X3_types[884])});
  ((entity *)IFC4X3_types[597])
      ->set_subtypes(
          {((entity *)IFC4X3_types[598]), ((entity *)IFC4X3_types[599]),
           ((entity *)IFC4X3_types[600]), ((entity *)IFC4X3_types[601])});
  ((entity *)IFC4X3_types[601])->set_subtypes({((entity *)IFC4X3_types[602])});
  ((entity *)IFC4X3_types[244])->set_subtypes({((entity *)IFC4X3_types[627])});
  ((entity *)IFC4X3_types[641])
      ->set_subtypes(
          {((entity *)IFC4X3_types[637]), ((entity *)IFC4X3_types[639]),
           ((entity *)IFC4X3_types[640]), ((entity *)IFC4X3_types[643]),
           ((entity *)IFC4X3_types[644]), ((entity *)IFC4X3_types[648]),
           ((entity *)IFC4X3_types[649])});
  ((entity *)IFC4X3_types[803])
      ->set_subtypes(
          {((entity *)IFC4X3_types[642]), ((entity *)IFC4X3_types[802])});
  ((entity *)IFC4X3_types[656])
      ->set_subtypes(
          {((entity *)IFC4X3_types[645]), ((entity *)IFC4X3_types[650])});
  ((entity *)IFC4X3_types[643])->set_subtypes({((entity *)IFC4X3_types[646])});
  ((entity *)IFC4X3_types[650])->set_subtypes({((entity *)IFC4X3_types[651])});
  ((entity *)IFC4X3_types[648])->set_subtypes({((entity *)IFC4X3_types[652])});
  ((entity *)IFC4X3_types[424])
      ->set_subtypes(
          {((entity *)IFC4X3_types[653]), ((entity *)IFC4X3_types[807])});
  ((entity *)IFC4X3_types[213])
      ->set_subtypes(
          {((entity *)IFC4X3_types[668]), ((entity *)IFC4X3_types[702])});
  ((entity *)IFC4X3_types[299])->set_subtypes({((entity *)IFC4X3_types[670])});
  ((entity *)IFC4X3_types[974])
      ->set_subtypes({((entity *)IFC4X3_types[701]),
                      ((entity *)IFC4X3_types[820]),
                      ((entity *)IFC4X3_types[917])});
  ((entity *)IFC4X3_types[6])->set_subtypes({((entity *)IFC4X3_types[707])});
  ((entity *)IFC4X3_types[709])
      ->set_subtypes({((entity *)IFC4X3_types[710]),
                      ((entity *)IFC4X3_types[711]),
                      ((entity *)IFC4X3_types[712])});
  ((entity *)IFC4X3_types[94])->set_subtypes({((entity *)IFC4X3_types[720])});
  ((entity *)IFC4X3_types[743])
      ->set_subtypes(
          {((entity *)IFC4X3_types[741]), ((entity *)IFC4X3_types[744])});
  ((entity *)IFC4X3_types[758])->set_subtypes({((entity *)IFC4X3_types[757])});
  ((entity *)IFC4X3_types[1176])
      ->set_subtypes(
          {((entity *)IFC4X3_types[771]), ((entity *)IFC4X3_types[1231])});
  ((entity *)IFC4X3_types[12])
      ->set_subtypes(
          {((entity *)IFC4X3_types[781]), ((entity *)IFC4X3_types[1164])});
  ((entity *)IFC4X3_types[785])
      ->set_subtypes({((entity *)IFC4X3_types[783]),
                      ((entity *)IFC4X3_types[784]),
                      ((entity *)IFC4X3_types[788])});
  ((entity *)IFC4X3_types[827])
      ->set_subtypes({((entity *)IFC4X3_types[787]),
                      ((entity *)IFC4X3_types[826]),
                      ((entity *)IFC4X3_types[849])});
  ((entity *)IFC4X3_types[792])->set_subtypes({((entity *)IFC4X3_types[793])});
  ((entity *)IFC4X3_types[226])
      ->set_subtypes(
          {((entity *)IFC4X3_types[809]), ((entity *)IFC4X3_types[814])});
  ((entity *)IFC4X3_types[245])->set_subtypes({((entity *)IFC4X3_types[810])});
  ((entity *)IFC4X3_types[456])->set_subtypes({((entity *)IFC4X3_types[812])});
  ((entity *)IFC4X3_types[1018])
      ->set_subtypes(
          {((entity *)IFC4X3_types[819]), ((entity *)IFC4X3_types[822]),
           ((entity *)IFC4X3_types[824]), ((entity *)IFC4X3_types[825]),
           ((entity *)IFC4X3_types[832]), ((entity *)IFC4X3_types[833])});
  ((entity *)IFC4X3_types[820])
      ->set_subtypes(
          {((entity *)IFC4X3_types[827]), ((entity *)IFC4X3_types[835])});
  ((entity *)IFC4X3_types[835])
      ->set_subtypes(
          {((entity *)IFC4X3_types[830]), ((entity *)IFC4X3_types[834])});
  ((entity *)IFC4X3_types[744])
      ->set_subtypes(
          {((entity *)IFC4X3_types[845]), ((entity *)IFC4X3_types[846]),
           ((entity *)IFC4X3_types[847]), ((entity *)IFC4X3_types[848]),
           ((entity *)IFC4X3_types[850]), ((entity *)IFC4X3_types[851]),
           ((entity *)IFC4X3_types[852])});
  ((entity *)IFC4X3_types[110])->set_subtypes({((entity *)IFC4X3_types[871])});
  ((entity *)IFC4X3_types[113])->set_subtypes({((entity *)IFC4X3_types[872])});
  ((entity *)IFC4X3_types[875])
      ->set_subtypes(
          {((entity *)IFC4X3_types[874]), ((entity *)IFC4X3_types[979])});
  ((entity *)IFC4X3_types[786])
      ->set_subtypes({((entity *)IFC4X3_types[887]),
                      ((entity *)IFC4X3_types[992]),
                      ((entity *)IFC4X3_types[993])});
  ((entity *)IFC4X3_types[894])
      ->set_subtypes(
          {((entity *)IFC4X3_types[889]), ((entity *)IFC4X3_types[896]),
           ((entity *)IFC4X3_types[1167]), ((entity *)IFC4X3_types[1168]),
           ((entity *)IFC4X3_types[1171])});
  ((entity *)IFC4X3_types[895])
      ->set_subtypes(
          {((entity *)IFC4X3_types[892]), ((entity *)IFC4X3_types[897]),
           ((entity *)IFC4X3_types[1169]), ((entity *)IFC4X3_types[1172]),
           ((entity *)IFC4X3_types[1174])});
  ((entity *)IFC4X3_types[931])
      ->set_subtypes(
          {((entity *)IFC4X3_types[899]), ((entity *)IFC4X3_types[900]),
           ((entity *)IFC4X3_types[940]), ((entity *)IFC4X3_types[942]),
           ((entity *)IFC4X3_types[949])});
  ((entity *)IFC4X3_types[917])
      ->set_subtypes(
          {((entity *)IFC4X3_types[901]), ((entity *)IFC4X3_types[909]),
           ((entity *)IFC4X3_types[918]), ((entity *)IFC4X3_types[930]),
           ((entity *)IFC4X3_types[931]), ((entity *)IFC4X3_types[932])});
  ((entity *)IFC4X3_types[901])
      ->set_subtypes(
          {((entity *)IFC4X3_types[902]), ((entity *)IFC4X3_types[903]),
           ((entity *)IFC4X3_types[904]), ((entity *)IFC4X3_types[906]),
           ((entity *)IFC4X3_types[907]), ((entity *)IFC4X3_types[908])});
  ((entity *)IFC4X3_types[904])->set_subtypes({((entity *)IFC4X3_types[905])});
  ((entity *)IFC4X3_types[909])
      ->set_subtypes(
          {((entity *)IFC4X3_types[910]), ((entity *)IFC4X3_types[911]),
           ((entity *)IFC4X3_types[912]), ((entity *)IFC4X3_types[913]),
           ((entity *)IFC4X3_types[914]), ((entity *)IFC4X3_types[915]),
           ((entity *)IFC4X3_types[916])});
  ((entity *)IFC4X3_types[918])
      ->set_subtypes(
          {((entity *)IFC4X3_types[919]), ((entity *)IFC4X3_types[922]),
           ((entity *)IFC4X3_types[921]), ((entity *)IFC4X3_types[923]),
           ((entity *)IFC4X3_types[924]), ((entity *)IFC4X3_types[927]),
           ((entity *)IFC4X3_types[928]), ((entity *)IFC4X3_types[929]),
           ((entity *)IFC4X3_types[937]), ((entity *)IFC4X3_types[938]),
           ((entity *)IFC4X3_types[939]), ((entity *)IFC4X3_types[941]),
           ((entity *)IFC4X3_types[943]), ((entity *)IFC4X3_types[944]),
           ((entity *)IFC4X3_types[945]), ((entity *)IFC4X3_types[946])});
  ((entity *)IFC4X3_types[919])
      ->set_subtypes(
          {((entity *)IFC4X3_types[920]), ((entity *)IFC4X3_types[926])});
  ((entity *)IFC4X3_types[924])->set_subtypes({((entity *)IFC4X3_types[925])});
  ((entity *)IFC4X3_types[932])
      ->set_subtypes(
          {((entity *)IFC4X3_types[933]), ((entity *)IFC4X3_types[934]),
           ((entity *)IFC4X3_types[935]), ((entity *)IFC4X3_types[936])});
  ((entity *)IFC4X3_types[946])->set_subtypes({((entity *)IFC4X3_types[947])});
  ((entity *)IFC4X3_types[947])->set_subtypes({((entity *)IFC4X3_types[948])});
  ((entity *)IFC4X3_types[195])->set_subtypes({((entity *)IFC4X3_types[950])});
  ((entity *)IFC4X3_types[962])->set_subtypes({((entity *)IFC4X3_types[963])});
  ((entity *)IFC4X3_types[987])->set_subtypes({((entity *)IFC4X3_types[988])});
  ((entity *)IFC4X3_types[951])
      ->set_subtypes(
          {((entity *)IFC4X3_types[1007]), ((entity *)IFC4X3_types[1118])});
  ((entity *)IFC4X3_types[1007])
      ->set_subtypes(
          {((entity *)IFC4X3_types[1008]), ((entity *)IFC4X3_types[1214])});
  ((entity *)IFC4X3_types[1053])
      ->set_subtypes({((entity *)IFC4X3_types[1047])});
  ((entity *)IFC4X3_types[1050])
      ->set_subtypes(
          {((entity *)IFC4X3_types[1053]), ((entity *)IFC4X3_types[1055])});
  ((entity *)IFC4X3_types[1075])
      ->set_subtypes(
          {((entity *)IFC4X3_types[1074]), ((entity *)IFC4X3_types[1107])});
  ((entity *)IFC4X3_types[1087])
      ->set_subtypes(
          {((entity *)IFC4X3_types[1078]), ((entity *)IFC4X3_types[1102])});
  ((entity *)IFC4X3_types[1074])
      ->set_subtypes({((entity *)IFC4X3_types[1080]),
                      ((entity *)IFC4X3_types[1104]),
                      ((entity *)IFC4X3_types[1109])});
  ((entity *)IFC4X3_types[1078])
      ->set_subtypes({((entity *)IFC4X3_types[1082]),
                      ((entity *)IFC4X3_types[1105]),
                      ((entity *)IFC4X3_types[1111])});
  ((entity *)IFC4X3_types[1102])
      ->set_subtypes(
          {((entity *)IFC4X3_types[1083]), ((entity *)IFC4X3_types[1112])});
  ((entity *)IFC4X3_types[1083])
      ->set_subtypes({((entity *)IFC4X3_types[1085])});
  ((entity *)IFC4X3_types[1107])
      ->set_subtypes({((entity *)IFC4X3_types[1086]),
                      ((entity *)IFC4X3_types[1106]),
                      ((entity *)IFC4X3_types[1115])});
  ((entity *)IFC4X3_types[1080])
      ->set_subtypes({((entity *)IFC4X3_types[1088])});
  ((entity *)IFC4X3_types[1092])
      ->set_subtypes({((entity *)IFC4X3_types[1090])});
  ((entity *)IFC4X3_types[1089])
      ->set_subtypes(
          {((entity *)IFC4X3_types[1091]), ((entity *)IFC4X3_types[1094])});
  ((entity *)IFC4X3_types[1100])
      ->set_subtypes(
          {((entity *)IFC4X3_types[1093]), ((entity *)IFC4X3_types[1095]),
           ((entity *)IFC4X3_types[1096]), ((entity *)IFC4X3_types[1098]),
           ((entity *)IFC4X3_types[1101])});
  ((entity *)IFC4X3_types[1096])
      ->set_subtypes({((entity *)IFC4X3_types[1097])});
  ((entity *)IFC4X3_types[1098])
      ->set_subtypes({((entity *)IFC4X3_types[1099])});
  ((entity *)IFC4X3_types[1094])
      ->set_subtypes(
          {((entity *)IFC4X3_types[1100]), ((entity *)IFC4X3_types[1131])});
  ((entity *)IFC4X3_types[1109])
      ->set_subtypes({((entity *)IFC4X3_types[1103])});
  ((entity *)IFC4X3_types[1112])
      ->set_subtypes({((entity *)IFC4X3_types[1114])});
  ((entity *)IFC4X3_types[1118])
      ->set_subtypes({((entity *)IFC4X3_types[1117])});
  ((entity *)IFC4X3_types[1144])
      ->set_subtypes(
          {((entity *)IFC4X3_types[1128]), ((entity *)IFC4X3_types[1129])});
  ((entity *)IFC4X3_types[1138])
      ->set_subtypes({((entity *)IFC4X3_types[1137])});
  ((entity *)IFC4X3_types[1142])
      ->set_subtypes({((entity *)IFC4X3_types[1143])});
  ((entity *)IFC4X3_types[1160])
      ->set_subtypes({((entity *)IFC4X3_types[1161])});
  ((entity *)IFC4X3_types[1183])
      ->set_subtypes({((entity *)IFC4X3_types[1184])});
  ((entity *)IFC4X3_types[788])->set_subtypes({((entity *)IFC4X3_types[1187])});
  ((entity *)IFC4X3_types[1193])
      ->set_subtypes({((entity *)IFC4X3_types[1194])});
  ((entity *)IFC4X3_types[1225])
      ->set_subtypes(
          {((entity *)IFC4X3_types[1227]), ((entity *)IFC4X3_types[1262])});
  ((entity *)IFC4X3_types[1226])
      ->set_subtypes(
          {((entity *)IFC4X3_types[1228]), ((entity *)IFC4X3_types[1263])});
  ((entity *)IFC4X3_types[1231])
      ->set_subtypes({((entity *)IFC4X3_types[1232])});
  ((entity *)IFC4X3_types[1240])
      ->set_subtypes({((entity *)IFC4X3_types[1241]),
                      ((entity *)IFC4X3_types[1242]),
                      ((entity *)IFC4X3_types[1243])});
  ((entity *)IFC4X3_types[1265])
      ->set_subtypes({((entity *)IFC4X3_types[1267])});
  ((entity *)IFC4X3_types[1281])
      ->set_subtypes({((entity *)IFC4X3_types[1282])});
  ((entity *)IFC4X3_types[1303])
      ->set_subtypes(
          {((entity *)IFC4X3_types[1304]), ((entity *)IFC4X3_types[1306])});
  return new schema_definition(
      strings[3924],
      {IFC4X3_types[0],    IFC4X3_types[1],    IFC4X3_types[2],
       IFC4X3_types[3],    IFC4X3_types[4],    IFC4X3_types[5],
       IFC4X3_types[6],    IFC4X3_types[7],    IFC4X3_types[8],
       IFC4X3_types[9],    IFC4X3_types[10],   IFC4X3_types[11],
       IFC4X3_types[12],   IFC4X3_types[13],   IFC4X3_types[14],
       IFC4X3_types[15],   IFC4X3_types[16],   IFC4X3_types[17],
       IFC4X3_types[18],   IFC4X3_types[19],   IFC4X3_types[20],
       IFC4X3_types[21],   IFC4X3_types[22],   IFC4X3_types[23],
       IFC4X3_types[24],   IFC4X3_types[25],   IFC4X3_types[26],
       IFC4X3_types[27],   IFC4X3_types[28],   IFC4X3_types[29],
       IFC4X3_types[30],   IFC4X3_types[31],   IFC4X3_types[32],
       IFC4X3_types[33],   IFC4X3_types[34],   IFC4X3_types[35],
       IFC4X3_types[36],   IFC4X3_types[37],   IFC4X3_types[38],
       IFC4X3_types[39],   IFC4X3_types[40],   IFC4X3_types[41],
       IFC4X3_types[42],   IFC4X3_types[43],   IFC4X3_types[44],
       IFC4X3_types[45],   IFC4X3_types[46],   IFC4X3_types[47],
       IFC4X3_types[48],   IFC4X3_types[49],   IFC4X3_types[50],
       IFC4X3_types[51],   IFC4X3_types[52],   IFC4X3_types[53],
       IFC4X3_types[54],   IFC4X3_types[55],   IFC4X3_types[56],
       IFC4X3_types[57],   IFC4X3_types[58],   IFC4X3_types[59],
       IFC4X3_types[60],   IFC4X3_types[61],   IFC4X3_types[62],
       IFC4X3_types[63],   IFC4X3_types[64],   IFC4X3_types[65],
       IFC4X3_types[66],   IFC4X3_types[67],   IFC4X3_types[68],
       IFC4X3_types[69],   IFC4X3_types[70],   IFC4X3_types[71],
       IFC4X3_types[72],   IFC4X3_types[73],   IFC4X3_types[74],
       IFC4X3_types[75],   IFC4X3_types[76],   IFC4X3_types[77],
       IFC4X3_types[78],   IFC4X3_types[79],   IFC4X3_types[80],
       IFC4X3_types[81],   IFC4X3_types[82],   IFC4X3_types[83],
       IFC4X3_types[84],   IFC4X3_types[85],   IFC4X3_types[86],
       IFC4X3_types[87],   IFC4X3_types[88],   IFC4X3_types[89],
       IFC4X3_types[90],   IFC4X3_types[91],   IFC4X3_types[92],
       IFC4X3_types[93],   IFC4X3_types[94],   IFC4X3_types[95],
       IFC4X3_types[96],   IFC4X3_types[97],   IFC4X3_types[98],
       IFC4X3_types[99],   IFC4X3_types[100],  IFC4X3_types[101],
       IFC4X3_types[102],  IFC4X3_types[103],  IFC4X3_types[104],
       IFC4X3_types[105],  IFC4X3_types[106],  IFC4X3_types[107],
       IFC4X3_types[108],  IFC4X3_types[109],  IFC4X3_types[110],
       IFC4X3_types[111],  IFC4X3_types[112],  IFC4X3_types[113],
       IFC4X3_types[114],  IFC4X3_types[115],  IFC4X3_types[116],
       IFC4X3_types[117],  IFC4X3_types[118],  IFC4X3_types[119],
       IFC4X3_types[120],  IFC4X3_types[121],  IFC4X3_types[122],
       IFC4X3_types[123],  IFC4X3_types[124],  IFC4X3_types[125],
       IFC4X3_types[126],  IFC4X3_types[127],  IFC4X3_types[128],
       IFC4X3_types[129],  IFC4X3_types[130],  IFC4X3_types[131],
       IFC4X3_types[132],  IFC4X3_types[133],  IFC4X3_types[134],
       IFC4X3_types[135],  IFC4X3_types[136],  IFC4X3_types[137],
       IFC4X3_types[138],  IFC4X3_types[139],  IFC4X3_types[140],
       IFC4X3_types[141],  IFC4X3_types[142],  IFC4X3_types[143],
       IFC4X3_types[144],  IFC4X3_types[145],  IFC4X3_types[146],
       IFC4X3_types[147],  IFC4X3_types[148],  IFC4X3_types[149],
       IFC4X3_types[150],  IFC4X3_types[151],  IFC4X3_types[152],
       IFC4X3_types[153],  IFC4X3_types[154],  IFC4X3_types[155],
       IFC4X3_types[156],  IFC4X3_types[157],  IFC4X3_types[158],
       IFC4X3_types[159],  IFC4X3_types[160],  IFC4X3_types[161],
       IFC4X3_types[162],  IFC4X3_types[163],  IFC4X3_types[164],
       IFC4X3_types[165],  IFC4X3_types[166],  IFC4X3_types[167],
       IFC4X3_types[168],  IFC4X3_types[169],  IFC4X3_types[170],
       IFC4X3_types[171],  IFC4X3_types[172],  IFC4X3_types[173],
       IFC4X3_types[174],  IFC4X3_types[175],  IFC4X3_types[176],
       IFC4X3_types[177],  IFC4X3_types[178],  IFC4X3_types[179],
       IFC4X3_types[180],  IFC4X3_types[181],  IFC4X3_types[182],
       IFC4X3_types[183],  IFC4X3_types[184],  IFC4X3_types[185],
       IFC4X3_types[186],  IFC4X3_types[187],  IFC4X3_types[188],
       IFC4X3_types[189],  IFC4X3_types[190],  IFC4X3_types[191],
       IFC4X3_types[192],  IFC4X3_types[193],  IFC4X3_types[194],
       IFC4X3_types[195],  IFC4X3_types[196],  IFC4X3_types[197],
       IFC4X3_types[198],  IFC4X3_types[199],  IFC4X3_types[200],
       IFC4X3_types[201],  IFC4X3_types[202],  IFC4X3_types[203],
       IFC4X3_types[204],  IFC4X3_types[205],  IFC4X3_types[206],
       IFC4X3_types[207],  IFC4X3_types[208],  IFC4X3_types[209],
       IFC4X3_types[210],  IFC4X3_types[211],  IFC4X3_types[212],
       IFC4X3_types[213],  IFC4X3_types[214],  IFC4X3_types[215],
       IFC4X3_types[216],  IFC4X3_types[217],  IFC4X3_types[218],
       IFC4X3_types[219],  IFC4X3_types[220],  IFC4X3_types[221],
       IFC4X3_types[222],  IFC4X3_types[223],  IFC4X3_types[224],
       IFC4X3_types[225],  IFC4X3_types[226],  IFC4X3_types[227],
       IFC4X3_types[228],  IFC4X3_types[229],  IFC4X3_types[230],
       IFC4X3_types[231],  IFC4X3_types[232],  IFC4X3_types[233],
       IFC4X3_types[234],  IFC4X3_types[235],  IFC4X3_types[236],
       IFC4X3_types[237],  IFC4X3_types[238],  IFC4X3_types[239],
       IFC4X3_types[240],  IFC4X3_types[241],  IFC4X3_types[242],
       IFC4X3_types[243],  IFC4X3_types[244],  IFC4X3_types[245],
       IFC4X3_types[246],  IFC4X3_types[247],  IFC4X3_types[248],
       IFC4X3_types[249],  IFC4X3_types[250],  IFC4X3_types[251],
       IFC4X3_types[252],  IFC4X3_types[253],  IFC4X3_types[254],
       IFC4X3_types[255],  IFC4X3_types[256],  IFC4X3_types[257],
       IFC4X3_types[258],  IFC4X3_types[259],  IFC4X3_types[260],
       IFC4X3_types[261],  IFC4X3_types[262],  IFC4X3_types[263],
       IFC4X3_types[264],  IFC4X3_types[265],  IFC4X3_types[266],
       IFC4X3_types[267],  IFC4X3_types[268],  IFC4X3_types[269],
       IFC4X3_types[270],  IFC4X3_types[271],  IFC4X3_types[272],
       IFC4X3_types[273],  IFC4X3_types[274],  IFC4X3_types[275],
       IFC4X3_types[276],  IFC4X3_types[277],  IFC4X3_types[278],
       IFC4X3_types[279],  IFC4X3_types[280],  IFC4X3_types[281],
       IFC4X3_types[282],  IFC4X3_types[283],  IFC4X3_types[284],
       IFC4X3_types[285],  IFC4X3_types[286],  IFC4X3_types[287],
       IFC4X3_types[288],  IFC4X3_types[289],  IFC4X3_types[290],
       IFC4X3_types[291],  IFC4X3_types[292],  IFC4X3_types[293],
       IFC4X3_types[294],  IFC4X3_types[295],  IFC4X3_types[296],
       IFC4X3_types[297],  IFC4X3_types[298],  IFC4X3_types[299],
       IFC4X3_types[300],  IFC4X3_types[301],  IFC4X3_types[302],
       IFC4X3_types[303],  IFC4X3_types[304],  IFC4X3_types[305],
       IFC4X3_types[306],  IFC4X3_types[307],  IFC4X3_types[308],
       IFC4X3_types[309],  IFC4X3_types[310],  IFC4X3_types[311],
       IFC4X3_types[312],  IFC4X3_types[313],  IFC4X3_types[314],
       IFC4X3_types[315],  IFC4X3_types[316],  IFC4X3_types[317],
       IFC4X3_types[318],  IFC4X3_types[319],  IFC4X3_types[320],
       IFC4X3_types[321],  IFC4X3_types[322],  IFC4X3_types[323],
       IFC4X3_types[324],  IFC4X3_types[325],  IFC4X3_types[326],
       IFC4X3_types[327],  IFC4X3_types[328],  IFC4X3_types[329],
       IFC4X3_types[330],  IFC4X3_types[331],  IFC4X3_types[332],
       IFC4X3_types[333],  IFC4X3_types[334],  IFC4X3_types[335],
       IFC4X3_types[336],  IFC4X3_types[337],  IFC4X3_types[338],
       IFC4X3_types[339],  IFC4X3_types[340],  IFC4X3_types[341],
       IFC4X3_types[342],  IFC4X3_types[343],  IFC4X3_types[344],
       IFC4X3_types[345],  IFC4X3_types[346],  IFC4X3_types[347],
       IFC4X3_types[348],  IFC4X3_types[349],  IFC4X3_types[350],
       IFC4X3_types[351],  IFC4X3_types[352],  IFC4X3_types[353],
       IFC4X3_types[354],  IFC4X3_types[355],  IFC4X3_types[356],
       IFC4X3_types[357],  IFC4X3_types[358],  IFC4X3_types[359],
       IFC4X3_types[360],  IFC4X3_types[361],  IFC4X3_types[362],
       IFC4X3_types[363],  IFC4X3_types[364],  IFC4X3_types[365],
       IFC4X3_types[366],  IFC4X3_types[367],  IFC4X3_types[368],
       IFC4X3_types[369],  IFC4X3_types[370],  IFC4X3_types[371],
       IFC4X3_types[372],  IFC4X3_types[373],  IFC4X3_types[374],
       IFC4X3_types[375],  IFC4X3_types[376],  IFC4X3_types[377],
       IFC4X3_types[378],  IFC4X3_types[379],  IFC4X3_types[380],
       IFC4X3_types[381],  IFC4X3_types[382],  IFC4X3_types[383],
       IFC4X3_types[384],  IFC4X3_types[385],  IFC4X3_types[386],
       IFC4X3_types[387],  IFC4X3_types[388],  IFC4X3_types[389],
       IFC4X3_types[390],  IFC4X3_types[391],  IFC4X3_types[392],
       IFC4X3_types[393],  IFC4X3_types[394],  IFC4X3_types[395],
       IFC4X3_types[396],  IFC4X3_types[397],  IFC4X3_types[398],
       IFC4X3_types[399],  IFC4X3_types[400],  IFC4X3_types[401],
       IFC4X3_types[402],  IFC4X3_types[403],  IFC4X3_types[404],
       IFC4X3_types[405],  IFC4X3_types[406],  IFC4X3_types[407],
       IFC4X3_types[408],  IFC4X3_types[409],  IFC4X3_types[410],
       IFC4X3_types[411],  IFC4X3_types[412],  IFC4X3_types[413],
       IFC4X3_types[414],  IFC4X3_types[415],  IFC4X3_types[416],
       IFC4X3_types[417],  IFC4X3_types[418],  IFC4X3_types[419],
       IFC4X3_types[420],  IFC4X3_types[421],  IFC4X3_types[422],
       IFC4X3_types[423],  IFC4X3_types[424],  IFC4X3_types[425],
       IFC4X3_types[426],  IFC4X3_types[427],  IFC4X3_types[428],
       IFC4X3_types[429],  IFC4X3_types[430],  IFC4X3_types[431],
       IFC4X3_types[432],  IFC4X3_types[433],  IFC4X3_types[434],
       IFC4X3_types[435],  IFC4X3_types[436],  IFC4X3_types[437],
       IFC4X3_types[438],  IFC4X3_types[439],  IFC4X3_types[440],
       IFC4X3_types[441],  IFC4X3_types[442],  IFC4X3_types[443],
       IFC4X3_types[444],  IFC4X3_types[445],  IFC4X3_types[446],
       IFC4X3_types[447],  IFC4X3_types[448],  IFC4X3_types[449],
       IFC4X3_types[450],  IFC4X3_types[451],  IFC4X3_types[452],
       IFC4X3_types[453],  IFC4X3_types[454],  IFC4X3_types[455],
       IFC4X3_types[456],  IFC4X3_types[457],  IFC4X3_types[458],
       IFC4X3_types[459],  IFC4X3_types[460],  IFC4X3_types[461],
       IFC4X3_types[462],  IFC4X3_types[463],  IFC4X3_types[464],
       IFC4X3_types[465],  IFC4X3_types[466],  IFC4X3_types[467],
       IFC4X3_types[468],  IFC4X3_types[469],  IFC4X3_types[470],
       IFC4X3_types[471],  IFC4X3_types[472],  IFC4X3_types[473],
       IFC4X3_types[474],  IFC4X3_types[475],  IFC4X3_types[476],
       IFC4X3_types[477],  IFC4X3_types[478],  IFC4X3_types[479],
       IFC4X3_types[480],  IFC4X3_types[481],  IFC4X3_types[482],
       IFC4X3_types[483],  IFC4X3_types[484],  IFC4X3_types[485],
       IFC4X3_types[486],  IFC4X3_types[487],  IFC4X3_types[488],
       IFC4X3_types[489],  IFC4X3_types[490],  IFC4X3_types[491],
       IFC4X3_types[492],  IFC4X3_types[493],  IFC4X3_types[494],
       IFC4X3_types[495],  IFC4X3_types[496],  IFC4X3_types[497],
       IFC4X3_types[498],  IFC4X3_types[499],  IFC4X3_types[500],
       IFC4X3_types[501],  IFC4X3_types[502],  IFC4X3_types[503],
       IFC4X3_types[504],  IFC4X3_types[505],  IFC4X3_types[506],
       IFC4X3_types[507],  IFC4X3_types[508],  IFC4X3_types[509],
       IFC4X3_types[510],  IFC4X3_types[511],  IFC4X3_types[512],
       IFC4X3_types[513],  IFC4X3_types[514],  IFC4X3_types[515],
       IFC4X3_types[516],  IFC4X3_types[517],  IFC4X3_types[518],
       IFC4X3_types[519],  IFC4X3_types[520],  IFC4X3_types[521],
       IFC4X3_types[522],  IFC4X3_types[523],  IFC4X3_types[524],
       IFC4X3_types[525],  IFC4X3_types[526],  IFC4X3_types[527],
       IFC4X3_types[528],  IFC4X3_types[529],  IFC4X3_types[530],
       IFC4X3_types[531],  IFC4X3_types[532],  IFC4X3_types[533],
       IFC4X3_types[534],  IFC4X3_types[535],  IFC4X3_types[536],
       IFC4X3_types[537],  IFC4X3_types[538],  IFC4X3_types[539],
       IFC4X3_types[540],  IFC4X3_types[541],  IFC4X3_types[542],
       IFC4X3_types[543],  IFC4X3_types[544],  IFC4X3_types[545],
       IFC4X3_types[546],  IFC4X3_types[547],  IFC4X3_types[548],
       IFC4X3_types[549],  IFC4X3_types[550],  IFC4X3_types[551],
       IFC4X3_types[552],  IFC4X3_types[553],  IFC4X3_types[554],
       IFC4X3_types[555],  IFC4X3_types[556],  IFC4X3_types[557],
       IFC4X3_types[558],  IFC4X3_types[559],  IFC4X3_types[560],
       IFC4X3_types[561],  IFC4X3_types[562],  IFC4X3_types[563],
       IFC4X3_types[564],  IFC4X3_types[565],  IFC4X3_types[566],
       IFC4X3_types[567],  IFC4X3_types[568],  IFC4X3_types[569],
       IFC4X3_types[570],  IFC4X3_types[571],  IFC4X3_types[572],
       IFC4X3_types[573],  IFC4X3_types[574],  IFC4X3_types[575],
       IFC4X3_types[576],  IFC4X3_types[577],  IFC4X3_types[578],
       IFC4X3_types[579],  IFC4X3_types[580],  IFC4X3_types[581],
       IFC4X3_types[582],  IFC4X3_types[583],  IFC4X3_types[584],
       IFC4X3_types[585],  IFC4X3_types[586],  IFC4X3_types[587],
       IFC4X3_types[588],  IFC4X3_types[589],  IFC4X3_types[590],
       IFC4X3_types[591],  IFC4X3_types[592],  IFC4X3_types[593],
       IFC4X3_types[594],  IFC4X3_types[595],  IFC4X3_types[596],
       IFC4X3_types[597],  IFC4X3_types[598],  IFC4X3_types[599],
       IFC4X3_types[600],  IFC4X3_types[601],  IFC4X3_types[602],
       IFC4X3_types[603],  IFC4X3_types[604],  IFC4X3_types[605],
       IFC4X3_types[606],  IFC4X3_types[607],  IFC4X3_types[608],
       IFC4X3_types[609],  IFC4X3_types[610],  IFC4X3_types[611],
       IFC4X3_types[612],  IFC4X3_types[613],  IFC4X3_types[614],
       IFC4X3_types[615],  IFC4X3_types[616],  IFC4X3_types[617],
       IFC4X3_types[618],  IFC4X3_types[619],  IFC4X3_types[620],
       IFC4X3_types[621],  IFC4X3_types[622],  IFC4X3_types[623],
       IFC4X3_types[624],  IFC4X3_types[625],  IFC4X3_types[626],
       IFC4X3_types[627],  IFC4X3_types[628],  IFC4X3_types[629],
       IFC4X3_types[630],  IFC4X3_types[631],  IFC4X3_types[632],
       IFC4X3_types[633],  IFC4X3_types[634],  IFC4X3_types[635],
       IFC4X3_types[636],  IFC4X3_types[637],  IFC4X3_types[638],
       IFC4X3_types[639],  IFC4X3_types[640],  IFC4X3_types[641],
       IFC4X3_types[642],  IFC4X3_types[643],  IFC4X3_types[644],
       IFC4X3_types[645],  IFC4X3_types[646],  IFC4X3_types[647],
       IFC4X3_types[648],  IFC4X3_types[649],  IFC4X3_types[650],
       IFC4X3_types[651],  IFC4X3_types[652],  IFC4X3_types[653],
       IFC4X3_types[654],  IFC4X3_types[655],  IFC4X3_types[656],
       IFC4X3_types[657],  IFC4X3_types[658],  IFC4X3_types[659],
       IFC4X3_types[660],  IFC4X3_types[661],  IFC4X3_types[662],
       IFC4X3_types[663],  IFC4X3_types[664],  IFC4X3_types[665],
       IFC4X3_types[666],  IFC4X3_types[667],  IFC4X3_types[668],
       IFC4X3_types[669],  IFC4X3_types[670],  IFC4X3_types[671],
       IFC4X3_types[672],  IFC4X3_types[673],  IFC4X3_types[674],
       IFC4X3_types[675],  IFC4X3_types[676],  IFC4X3_types[677],
       IFC4X3_types[678],  IFC4X3_types[679],  IFC4X3_types[680],
       IFC4X3_types[681],  IFC4X3_types[682],  IFC4X3_types[683],
       IFC4X3_types[684],  IFC4X3_types[685],  IFC4X3_types[686],
       IFC4X3_types[687],  IFC4X3_types[688],  IFC4X3_types[689],
       IFC4X3_types[690],  IFC4X3_types[691],  IFC4X3_types[692],
       IFC4X3_types[693],  IFC4X3_types[694],  IFC4X3_types[695],
       IFC4X3_types[696],  IFC4X3_types[697],  IFC4X3_types[698],
       IFC4X3_types[699],  IFC4X3_types[700],  IFC4X3_types[701],
       IFC4X3_types[702],  IFC4X3_types[703],  IFC4X3_types[704],
       IFC4X3_types[705],  IFC4X3_types[706],  IFC4X3_types[707],
       IFC4X3_types[708],  IFC4X3_types[709],  IFC4X3_types[710],
       IFC4X3_types[711],  IFC4X3_types[712],  IFC4X3_types[713],
       IFC4X3_types[714],  IFC4X3_types[715],  IFC4X3_types[716],
       IFC4X3_types[717],  IFC4X3_types[718],  IFC4X3_types[719],
       IFC4X3_types[720],  IFC4X3_types[721],  IFC4X3_types[722],
       IFC4X3_types[723],  IFC4X3_types[724],  IFC4X3_types[725],
       IFC4X3_types[726],  IFC4X3_types[727],  IFC4X3_types[728],
       IFC4X3_types[729],  IFC4X3_types[730],  IFC4X3_types[731],
       IFC4X3_types[732],  IFC4X3_types[733],  IFC4X3_types[734],
       IFC4X3_types[735],  IFC4X3_types[736],  IFC4X3_types[737],
       IFC4X3_types[738],  IFC4X3_types[739],  IFC4X3_types[740],
       IFC4X3_types[741],  IFC4X3_types[742],  IFC4X3_types[743],
       IFC4X3_types[744],  IFC4X3_types[745],  IFC4X3_types[746],
       IFC4X3_types[747],  IFC4X3_types[748],  IFC4X3_types[749],
       IFC4X3_types[750],  IFC4X3_types[751],  IFC4X3_types[752],
       IFC4X3_types[753],  IFC4X3_types[754],  IFC4X3_types[755],
       IFC4X3_types[756],  IFC4X3_types[757],  IFC4X3_types[758],
       IFC4X3_types[759],  IFC4X3_types[760],  IFC4X3_types[761],
       IFC4X3_types[762],  IFC4X3_types[763],  IFC4X3_types[764],
       IFC4X3_types[765],  IFC4X3_types[766],  IFC4X3_types[767],
       IFC4X3_types[768],  IFC4X3_types[769],  IFC4X3_types[770],
       IFC4X3_types[771],  IFC4X3_types[772],  IFC4X3_types[773],
       IFC4X3_types[774],  IFC4X3_types[775],  IFC4X3_types[776],
       IFC4X3_types[777],  IFC4X3_types[778],  IFC4X3_types[779],
       IFC4X3_types[780],  IFC4X3_types[781],  IFC4X3_types[782],
       IFC4X3_types[783],  IFC4X3_types[784],  IFC4X3_types[785],
       IFC4X3_types[786],  IFC4X3_types[787],  IFC4X3_types[788],
       IFC4X3_types[789],  IFC4X3_types[790],  IFC4X3_types[791],
       IFC4X3_types[792],  IFC4X3_types[793],  IFC4X3_types[794],
       IFC4X3_types[795],  IFC4X3_types[796],  IFC4X3_types[797],
       IFC4X3_types[798],  IFC4X3_types[799],  IFC4X3_types[800],
       IFC4X3_types[801],  IFC4X3_types[802],  IFC4X3_types[803],
       IFC4X3_types[804],  IFC4X3_types[805],  IFC4X3_types[806],
       IFC4X3_types[807],  IFC4X3_types[808],  IFC4X3_types[809],
       IFC4X3_types[810],  IFC4X3_types[811],  IFC4X3_types[812],
       IFC4X3_types[813],  IFC4X3_types[814],  IFC4X3_types[815],
       IFC4X3_types[816],  IFC4X3_types[817],  IFC4X3_types[818],
       IFC4X3_types[819],  IFC4X3_types[820],  IFC4X3_types[821],
       IFC4X3_types[822],  IFC4X3_types[823],  IFC4X3_types[824],
       IFC4X3_types[825],  IFC4X3_types[826],  IFC4X3_types[827],
       IFC4X3_types[828],  IFC4X3_types[829],  IFC4X3_types[830],
       IFC4X3_types[831],  IFC4X3_types[832],  IFC4X3_types[833],
       IFC4X3_types[834],  IFC4X3_types[835],  IFC4X3_types[836],
       IFC4X3_types[837],  IFC4X3_types[838],  IFC4X3_types[839],
       IFC4X3_types[840],  IFC4X3_types[841],  IFC4X3_types[842],
       IFC4X3_types[843],  IFC4X3_types[844],  IFC4X3_types[845],
       IFC4X3_types[846],  IFC4X3_types[847],  IFC4X3_types[848],
       IFC4X3_types[849],  IFC4X3_types[850],  IFC4X3_types[851],
       IFC4X3_types[852],  IFC4X3_types[853],  IFC4X3_types[854],
       IFC4X3_types[855],  IFC4X3_types[856],  IFC4X3_types[857],
       IFC4X3_types[858],  IFC4X3_types[859],  IFC4X3_types[860],
       IFC4X3_types[861],  IFC4X3_types[862],  IFC4X3_types[863],
       IFC4X3_types[864],  IFC4X3_types[865],  IFC4X3_types[866],
       IFC4X3_types[867],  IFC4X3_types[868],  IFC4X3_types[869],
       IFC4X3_types[870],  IFC4X3_types[871],  IFC4X3_types[872],
       IFC4X3_types[873],  IFC4X3_types[874],  IFC4X3_types[875],
       IFC4X3_types[876],  IFC4X3_types[877],  IFC4X3_types[878],
       IFC4X3_types[879],  IFC4X3_types[880],  IFC4X3_types[881],
       IFC4X3_types[882],  IFC4X3_types[883],  IFC4X3_types[884],
       IFC4X3_types[885],  IFC4X3_types[886],  IFC4X3_types[887],
       IFC4X3_types[888],  IFC4X3_types[889],  IFC4X3_types[890],
       IFC4X3_types[891],  IFC4X3_types[892],  IFC4X3_types[893],
       IFC4X3_types[894],  IFC4X3_types[895],  IFC4X3_types[896],
       IFC4X3_types[897],  IFC4X3_types[898],  IFC4X3_types[899],
       IFC4X3_types[900],  IFC4X3_types[901],  IFC4X3_types[902],
       IFC4X3_types[903],  IFC4X3_types[904],  IFC4X3_types[905],
       IFC4X3_types[906],  IFC4X3_types[907],  IFC4X3_types[908],
       IFC4X3_types[909],  IFC4X3_types[910],  IFC4X3_types[911],
       IFC4X3_types[912],  IFC4X3_types[913],  IFC4X3_types[914],
       IFC4X3_types[915],  IFC4X3_types[916],  IFC4X3_types[917],
       IFC4X3_types[918],  IFC4X3_types[919],  IFC4X3_types[920],
       IFC4X3_types[921],  IFC4X3_types[922],  IFC4X3_types[923],
       IFC4X3_types[924],  IFC4X3_types[925],  IFC4X3_types[926],
       IFC4X3_types[927],  IFC4X3_types[928],  IFC4X3_types[929],
       IFC4X3_types[930],  IFC4X3_types[931],  IFC4X3_types[932],
       IFC4X3_types[933],  IFC4X3_types[934],  IFC4X3_types[935],
       IFC4X3_types[936],  IFC4X3_types[937],  IFC4X3_types[938],
       IFC4X3_types[939],  IFC4X3_types[940],  IFC4X3_types[941],
       IFC4X3_types[942],  IFC4X3_types[943],  IFC4X3_types[944],
       IFC4X3_types[945],  IFC4X3_types[946],  IFC4X3_types[947],
       IFC4X3_types[948],  IFC4X3_types[949],  IFC4X3_types[950],
       IFC4X3_types[951],  IFC4X3_types[952],  IFC4X3_types[953],
       IFC4X3_types[954],  IFC4X3_types[955],  IFC4X3_types[956],
       IFC4X3_types[957],  IFC4X3_types[958],  IFC4X3_types[959],
       IFC4X3_types[960],  IFC4X3_types[961],  IFC4X3_types[962],
       IFC4X3_types[963],  IFC4X3_types[964],  IFC4X3_types[965],
       IFC4X3_types[966],  IFC4X3_types[967],  IFC4X3_types[968],
       IFC4X3_types[969],  IFC4X3_types[970],  IFC4X3_types[971],
       IFC4X3_types[972],  IFC4X3_types[973],  IFC4X3_types[974],
       IFC4X3_types[975],  IFC4X3_types[976],  IFC4X3_types[977],
       IFC4X3_types[978],  IFC4X3_types[979],  IFC4X3_types[980],
       IFC4X3_types[981],  IFC4X3_types[982],  IFC4X3_types[983],
       IFC4X3_types[984],  IFC4X3_types[985],  IFC4X3_types[986],
       IFC4X3_types[987],  IFC4X3_types[988],  IFC4X3_types[989],
       IFC4X3_types[990],  IFC4X3_types[991],  IFC4X3_types[992],
       IFC4X3_types[993],  IFC4X3_types[994],  IFC4X3_types[995],
       IFC4X3_types[996],  IFC4X3_types[997],  IFC4X3_types[998],
       IFC4X3_types[999],  IFC4X3_types[1000], IFC4X3_types[1001],
       IFC4X3_types[1002], IFC4X3_types[1003], IFC4X3_types[1004],
       IFC4X3_types[1005], IFC4X3_types[1006], IFC4X3_types[1007],
       IFC4X3_types[1008], IFC4X3_types[1009], IFC4X3_types[1010],
       IFC4X3_types[1011], IFC4X3_types[1012], IFC4X3_types[1013],
       IFC4X3_types[1014], IFC4X3_types[1015], IFC4X3_types[1016],
       IFC4X3_types[1017], IFC4X3_types[1018], IFC4X3_types[1019],
       IFC4X3_types[1020], IFC4X3_types[1021], IFC4X3_types[1022],
       IFC4X3_types[1023], IFC4X3_types[1024], IFC4X3_types[1025],
       IFC4X3_types[1026], IFC4X3_types[1027], IFC4X3_types[1028],
       IFC4X3_types[1029], IFC4X3_types[1030], IFC4X3_types[1031],
       IFC4X3_types[1032], IFC4X3_types[1033], IFC4X3_types[1034],
       IFC4X3_types[1035], IFC4X3_types[1036], IFC4X3_types[1037],
       IFC4X3_types[1038], IFC4X3_types[1039], IFC4X3_types[1040],
       IFC4X3_types[1041], IFC4X3_types[1042], IFC4X3_types[1043],
       IFC4X3_types[1044], IFC4X3_types[1045], IFC4X3_types[1046],
       IFC4X3_types[1047], IFC4X3_types[1048], IFC4X3_types[1049],
       IFC4X3_types[1050], IFC4X3_types[1051], IFC4X3_types[1052],
       IFC4X3_types[1053], IFC4X3_types[1054], IFC4X3_types[1055],
       IFC4X3_types[1056], IFC4X3_types[1057], IFC4X3_types[1058],
       IFC4X3_types[1059], IFC4X3_types[1060], IFC4X3_types[1061],
       IFC4X3_types[1062], IFC4X3_types[1063], IFC4X3_types[1064],
       IFC4X3_types[1065], IFC4X3_types[1066], IFC4X3_types[1067],
       IFC4X3_types[1068], IFC4X3_types[1069], IFC4X3_types[1070],
       IFC4X3_types[1071], IFC4X3_types[1072], IFC4X3_types[1073],
       IFC4X3_types[1074], IFC4X3_types[1075], IFC4X3_types[1076],
       IFC4X3_types[1077], IFC4X3_types[1078], IFC4X3_types[1079],
       IFC4X3_types[1080], IFC4X3_types[1081], IFC4X3_types[1082],
       IFC4X3_types[1083], IFC4X3_types[1084], IFC4X3_types[1085],
       IFC4X3_types[1086], IFC4X3_types[1087], IFC4X3_types[1088],
       IFC4X3_types[1089], IFC4X3_types[1090], IFC4X3_types[1091],
       IFC4X3_types[1092], IFC4X3_types[1093], IFC4X3_types[1094],
       IFC4X3_types[1095], IFC4X3_types[1096], IFC4X3_types[1097],
       IFC4X3_types[1098], IFC4X3_types[1099], IFC4X3_types[1100],
       IFC4X3_types[1101], IFC4X3_types[1102], IFC4X3_types[1103],
       IFC4X3_types[1104], IFC4X3_types[1105], IFC4X3_types[1106],
       IFC4X3_types[1107], IFC4X3_types[1108], IFC4X3_types[1109],
       IFC4X3_types[1110], IFC4X3_types[1111], IFC4X3_types[1112],
       IFC4X3_types[1113], IFC4X3_types[1114], IFC4X3_types[1115],
       IFC4X3_types[1116], IFC4X3_types[1117], IFC4X3_types[1118],
       IFC4X3_types[1119], IFC4X3_types[1120], IFC4X3_types[1121],
       IFC4X3_types[1122], IFC4X3_types[1123], IFC4X3_types[1124],
       IFC4X3_types[1125], IFC4X3_types[1126], IFC4X3_types[1127],
       IFC4X3_types[1128], IFC4X3_types[1129], IFC4X3_types[1130],
       IFC4X3_types[1131], IFC4X3_types[1132], IFC4X3_types[1133],
       IFC4X3_types[1134], IFC4X3_types[1135], IFC4X3_types[1136],
       IFC4X3_types[1137], IFC4X3_types[1138], IFC4X3_types[1139],
       IFC4X3_types[1140], IFC4X3_types[1141], IFC4X3_types[1142],
       IFC4X3_types[1143], IFC4X3_types[1144], IFC4X3_types[1145],
       IFC4X3_types[1146], IFC4X3_types[1147], IFC4X3_types[1148],
       IFC4X3_types[1149], IFC4X3_types[1150], IFC4X3_types[1151],
       IFC4X3_types[1152], IFC4X3_types[1153], IFC4X3_types[1154],
       IFC4X3_types[1155], IFC4X3_types[1156], IFC4X3_types[1157],
       IFC4X3_types[1158], IFC4X3_types[1159], IFC4X3_types[1160],
       IFC4X3_types[1161], IFC4X3_types[1162], IFC4X3_types[1163],
       IFC4X3_types[1164], IFC4X3_types[1165], IFC4X3_types[1166],
       IFC4X3_types[1167], IFC4X3_types[1168], IFC4X3_types[1169],
       IFC4X3_types[1170], IFC4X3_types[1171], IFC4X3_types[1172],
       IFC4X3_types[1173], IFC4X3_types[1174], IFC4X3_types[1175],
       IFC4X3_types[1176], IFC4X3_types[1177], IFC4X3_types[1178],
       IFC4X3_types[1179], IFC4X3_types[1180], IFC4X3_types[1181],
       IFC4X3_types[1182], IFC4X3_types[1183], IFC4X3_types[1184],
       IFC4X3_types[1185], IFC4X3_types[1186], IFC4X3_types[1187],
       IFC4X3_types[1188], IFC4X3_types[1189], IFC4X3_types[1190],
       IFC4X3_types[1191], IFC4X3_types[1192], IFC4X3_types[1193],
       IFC4X3_types[1194], IFC4X3_types[1195], IFC4X3_types[1196],
       IFC4X3_types[1197], IFC4X3_types[1198], IFC4X3_types[1199],
       IFC4X3_types[1200], IFC4X3_types[1201], IFC4X3_types[1202],
       IFC4X3_types[1203], IFC4X3_types[1204], IFC4X3_types[1205],
       IFC4X3_types[1206], IFC4X3_types[1207], IFC4X3_types[1208],
       IFC4X3_types[1209], IFC4X3_types[1210], IFC4X3_types[1211],
       IFC4X3_types[1212], IFC4X3_types[1213], IFC4X3_types[1214],
       IFC4X3_types[1215], IFC4X3_types[1216], IFC4X3_types[1217],
       IFC4X3_types[1218], IFC4X3_types[1219], IFC4X3_types[1220],
       IFC4X3_types[1221], IFC4X3_types[1222], IFC4X3_types[1223],
       IFC4X3_types[1224], IFC4X3_types[1225], IFC4X3_types[1226],
       IFC4X3_types[1227], IFC4X3_types[1228], IFC4X3_types[1229],
       IFC4X3_types[1230], IFC4X3_types[1231], IFC4X3_types[1232],
       IFC4X3_types[1233], IFC4X3_types[1234], IFC4X3_types[1235],
       IFC4X3_types[1236], IFC4X3_types[1237], IFC4X3_types[1238],
       IFC4X3_types[1239], IFC4X3_types[1240], IFC4X3_types[1241],
       IFC4X3_types[1242], IFC4X3_types[1243], IFC4X3_types[1244],
       IFC4X3_types[1245], IFC4X3_types[1246], IFC4X3_types[1247],
       IFC4X3_types[1248], IFC4X3_types[1249], IFC4X3_types[1250],
       IFC4X3_types[1251], IFC4X3_types[1252], IFC4X3_types[1253],
       IFC4X3_types[1254], IFC4X3_types[1255], IFC4X3_types[1256],
       IFC4X3_types[1257], IFC4X3_types[1258], IFC4X3_types[1259],
       IFC4X3_types[1260], IFC4X3_types[1261], IFC4X3_types[1262],
       IFC4X3_types[1263], IFC4X3_types[1264], IFC4X3_types[1265],
       IFC4X3_types[1266], IFC4X3_types[1267], IFC4X3_types[1268],
       IFC4X3_types[1269], IFC4X3_types[1270], IFC4X3_types[1271],
       IFC4X3_types[1272], IFC4X3_types[1273], IFC4X3_types[1274],
       IFC4X3_types[1275], IFC4X3_types[1276], IFC4X3_types[1277],
       IFC4X3_types[1278], IFC4X3_types[1279], IFC4X3_types[1280],
       IFC4X3_types[1281], IFC4X3_types[1282], IFC4X3_types[1283],
       IFC4X3_types[1284], IFC4X3_types[1285], IFC4X3_types[1286],
       IFC4X3_types[1287], IFC4X3_types[1288], IFC4X3_types[1289],
       IFC4X3_types[1290], IFC4X3_types[1291], IFC4X3_types[1292],
       IFC4X3_types[1293], IFC4X3_types[1294], IFC4X3_types[1295],
       IFC4X3_types[1296], IFC4X3_types[1297], IFC4X3_types[1298],
       IFC4X3_types[1299], IFC4X3_types[1300], IFC4X3_types[1301],
       IFC4X3_types[1302], IFC4X3_types[1303], IFC4X3_types[1304],
       IFC4X3_types[1305], IFC4X3_types[1306], IFC4X3_types[1307],
       IFC4X3_types[1308], IFC4X3_types[1309], IFC4X3_types[1310]},
      new IFC4X3_instance_factory());
}
static std::unique_ptr<schema_definition> schema;

void Ifc4x3::clear_schema() { schema.reset(); }

const schema_definition &Ifc4x3::get_schema() {
  if (!schema) {
    schema.reset(IFC4X3_populate_schema());
  }
  return *schema;
}
