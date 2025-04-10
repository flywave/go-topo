#pragma once

#include <utility>

namespace flywave {
namespace dxf {

struct rgb_color {
  int r;
  int g;
  int b;
};

// Source: https://gohtx.com/acadcolors.php
const std::pair<int, rgb_color> aci_table[] = {
    {0, rgb_color{0, 0, 0}},         {1, rgb_color{255, 0, 0}},
    {2, rgb_color{255, 255, 0}},     {3, rgb_color{0, 255, 0}},
    {4, rgb_color{0, 255, 255}},     {5, rgb_color{0, 0, 255}},
    {6, rgb_color{255, 0, 255}},     {7, rgb_color{255, 255, 255}},
    {8, rgb_color{65, 65, 65}},      {9, rgb_color{128, 128, 128}},
    {10, rgb_color{255, 0, 0}},      {11, rgb_color{255, 170, 170}},
    {12, rgb_color{189, 0, 0}},      {13, rgb_color{189, 126, 126}},
    {14, rgb_color{129, 0, 0}},      {15, rgb_color{129, 86, 86}},
    {16, rgb_color{104, 0, 0}},      {17, rgb_color{104, 69, 69}},
    {18, rgb_color{79, 0, 0}},       {19, rgb_color{79, 53, 53}},
    {20, rgb_color{255, 63, 0}},     {21, rgb_color{255, 191, 170}},
    {22, rgb_color{189, 46, 0}},     {23, rgb_color{189, 141, 126}},
    {24, rgb_color{129, 31, 0}},     {25, rgb_color{129, 96, 86}},
    {26, rgb_color{104, 25, 0}},     {27, rgb_color{104, 78, 69}},
    {28, rgb_color{79, 19, 0}},      {29, rgb_color{79, 59, 53}},
    {30, rgb_color{255, 127, 0}},    {31, rgb_color{255, 212, 170}},
    {32, rgb_color{189, 94, 0}},     {33, rgb_color{189, 157, 126}},
    {34, rgb_color{129, 64, 0}},     {35, rgb_color{129, 107, 86}},
    {36, rgb_color{104, 52, 0}},     {37, rgb_color{104, 86, 69}},
    {38, rgb_color{79, 39, 0}},      {39, rgb_color{79, 66, 53}},
    {40, rgb_color{255, 191, 0}},    {41, rgb_color{255, 234, 170}},
    {42, rgb_color{189, 141, 0}},    {43, rgb_color{189, 173, 126}},
    {44, rgb_color{129, 96, 0}},     {45, rgb_color{129, 118, 86}},
    {46, rgb_color{104, 78, 0}},     {47, rgb_color{104, 95, 69}},
    {48, rgb_color{79, 59, 0}},      {49, rgb_color{79, 73, 53}},
    {50, rgb_color{255, 255, 0}},    {51, rgb_color{255, 255, 170}},
    {52, rgb_color{189, 189, 0}},    {53, rgb_color{189, 189, 126}},
    {54, rgb_color{129, 129, 0}},    {55, rgb_color{129, 129, 86}},
    {56, rgb_color{104, 104, 0}},    {57, rgb_color{104, 104, 69}},
    {58, rgb_color{79, 79, 0}},      {59, rgb_color{79, 79, 53}},
    {60, rgb_color{191, 255, 0}},    {61, rgb_color{234, 255, 170}},
    {62, rgb_color{141, 189, 0}},    {63, rgb_color{173, 189, 126}},
    {64, rgb_color{96, 129, 0}},     {65, rgb_color{118, 129, 86}},
    {66, rgb_color{78, 104, 0}},     {67, rgb_color{95, 104, 69}},
    {68, rgb_color{59, 79, 0}},      {69, rgb_color{73, 79, 53}},
    {70, rgb_color{127, 255, 0}},    {71, rgb_color{212, 255, 170}},
    {72, rgb_color{94, 189, 0}},     {73, rgb_color{157, 189, 126}},
    {74, rgb_color{64, 129, 0}},     {75, rgb_color{107, 129, 86}},
    {76, rgb_color{52, 104, 0}},     {77, rgb_color{86, 104, 69}},
    {78, rgb_color{39, 79, 0}},      {79, rgb_color{66, 79, 53}},
    {80, rgb_color{63, 255, 0}},     {81, rgb_color{191, 255, 170}},
    {82, rgb_color{46, 189, 0}},     {83, rgb_color{141, 189, 126}},
    {84, rgb_color{31, 129, 0}},     {85, rgb_color{96, 129, 86}},
    {86, rgb_color{25, 104, 0}},     {87, rgb_color{78, 104, 69}},
    {88, rgb_color{19, 79, 0}},      {89, rgb_color{59, 79, 53}},
    {90, rgb_color{0, 255, 0}},      {91, rgb_color{170, 255, 170}},
    {92, rgb_color{0, 189, 0}},      {93, rgb_color{126, 189, 126}},
    {94, rgb_color{0, 129, 0}},      {95, rgb_color{86, 129, 86}},
    {96, rgb_color{0, 104, 0}},      {97, rgb_color{69, 104, 69}},
    {98, rgb_color{0, 79, 0}},       {99, rgb_color{53, 79, 53}},
    {100, rgb_color{0, 255, 63}},    {101, rgb_color{170, 255, 191}},
    {102, rgb_color{0, 189, 46}},    {103, rgb_color{126, 189, 141}},
    {104, rgb_color{0, 129, 31}},    {105, rgb_color{86, 129, 96}},
    {106, rgb_color{0, 104, 25}},    {107, rgb_color{69, 104, 78}},
    {108, rgb_color{0, 79, 19}},     {109, rgb_color{53, 79, 59}},
    {110, rgb_color{0, 255, 127}},   {111, rgb_color{170, 255, 212}},
    {112, rgb_color{0, 189, 94}},    {113, rgb_color{126, 189, 157}},
    {114, rgb_color{0, 129, 64}},    {115, rgb_color{86, 129, 107}},
    {116, rgb_color{0, 104, 52}},    {117, rgb_color{69, 104, 86}},
    {118, rgb_color{0, 79, 39}},     {119, rgb_color{53, 79, 66}},
    {120, rgb_color{0, 255, 191}},   {121, rgb_color{170, 255, 234}},
    {122, rgb_color{0, 189, 141}},   {123, rgb_color{126, 189, 173}},
    {124, rgb_color{0, 129, 96}},    {125, rgb_color{86, 129, 118}},
    {126, rgb_color{0, 104, 78}},    {127, rgb_color{69, 104, 95}},
    {128, rgb_color{0, 79, 59}},     {129, rgb_color{53, 79, 73}},
    {130, rgb_color{0, 255, 255}},   {131, rgb_color{170, 255, 255}},
    {132, rgb_color{0, 189, 189}},   {133, rgb_color{126, 189, 189}},
    {134, rgb_color{0, 129, 129}},   {135, rgb_color{86, 129, 129}},
    {136, rgb_color{0, 104, 104}},   {137, rgb_color{69, 104, 104}},
    {138, rgb_color{0, 79, 79}},     {139, rgb_color{53, 79, 79}},
    {140, rgb_color{0, 191, 255}},   {141, rgb_color{170, 234, 255}},
    {142, rgb_color{0, 141, 189}},   {143, rgb_color{126, 173, 189}},
    {144, rgb_color{0, 96, 129}},    {145, rgb_color{86, 118, 129}},
    {146, rgb_color{0, 78, 104}},    {147, rgb_color{69, 95, 104}},
    {148, rgb_color{0, 59, 79}},     {149, rgb_color{53, 73, 79}},
    {150, rgb_color{0, 127, 255}},   {151, rgb_color{170, 212, 255}},
    {152, rgb_color{0, 94, 189}},    {153, rgb_color{126, 157, 189}},
    {154, rgb_color{0, 64, 129}},    {155, rgb_color{86, 107, 129}},
    {156, rgb_color{0, 52, 104}},    {157, rgb_color{69, 86, 104}},
    {158, rgb_color{0, 39, 79}},     {159, rgb_color{53, 66, 79}},
    {160, rgb_color{0, 63, 255}},    {161, rgb_color{170, 191, 255}},
    {162, rgb_color{0, 46, 189}},    {163, rgb_color{126, 141, 189}},
    {164, rgb_color{0, 31, 129}},    {165, rgb_color{86, 96, 129}},
    {166, rgb_color{0, 25, 104}},    {167, rgb_color{69, 78, 104}},
    {168, rgb_color{0, 19, 79}},     {169, rgb_color{53, 59, 79}},
    {170, rgb_color{0, 0, 255}},     {171, rgb_color{170, 170, 255}},
    {172, rgb_color{0, 0, 189}},     {173, rgb_color{126, 126, 189}},
    {174, rgb_color{0, 0, 129}},     {175, rgb_color{86, 86, 129}},
    {176, rgb_color{0, 0, 104}},     {177, rgb_color{69, 69, 104}},
    {178, rgb_color{0, 0, 79}},      {179, rgb_color{53, 53, 79}},
    {180, rgb_color{63, 0, 255}},    {181, rgb_color{191, 170, 255}},
    {182, rgb_color{46, 0, 189}},    {183, rgb_color{141, 126, 189}},
    {184, rgb_color{31, 0, 129}},    {185, rgb_color{96, 86, 129}},
    {186, rgb_color{25, 0, 104}},    {187, rgb_color{78, 69, 104}},
    {188, rgb_color{19, 0, 79}},     {189, rgb_color{59, 53, 79}},
    {190, rgb_color{127, 0, 255}},   {191, rgb_color{212, 170, 255}},
    {192, rgb_color{94, 0, 189}},    {193, rgb_color{157, 126, 189}},
    {194, rgb_color{64, 0, 129}},    {195, rgb_color{107, 86, 129}},
    {196, rgb_color{52, 0, 104}},    {197, rgb_color{86, 69, 104}},
    {198, rgb_color{39, 0, 79}},     {199, rgb_color{66, 53, 79}},
    {200, rgb_color{191, 0, 255}},   {201, rgb_color{234, 170, 255}},
    {202, rgb_color{141, 0, 189}},   {203, rgb_color{173, 126, 189}},
    {204, rgb_color{96, 0, 129}},    {205, rgb_color{118, 86, 129}},
    {206, rgb_color{78, 0, 104}},    {207, rgb_color{95, 69, 104}},
    {208, rgb_color{59, 0, 79}},     {209, rgb_color{73, 53, 79}},
    {210, rgb_color{255, 0, 255}},   {211, rgb_color{255, 170, 255}},
    {212, rgb_color{189, 0, 189}},   {213, rgb_color{189, 126, 189}},
    {214, rgb_color{129, 0, 129}},   {215, rgb_color{129, 86, 129}},
    {216, rgb_color{104, 0, 104}},   {217, rgb_color{104, 69, 104}},
    {218, rgb_color{79, 0, 79}},     {219, rgb_color{79, 53, 79}},
    {220, rgb_color{255, 0, 191}},   {221, rgb_color{255, 170, 234}},
    {222, rgb_color{189, 0, 141}},   {223, rgb_color{189, 126, 173}},
    {224, rgb_color{129, 0, 96}},    {225, rgb_color{129, 86, 118}},
    {226, rgb_color{104, 0, 78}},    {227, rgb_color{104, 69, 95}},
    {228, rgb_color{79, 0, 59}},     {229, rgb_color{79, 53, 73}},
    {230, rgb_color{255, 0, 127}},   {231, rgb_color{255, 170, 212}},
    {232, rgb_color{189, 0, 94}},    {233, rgb_color{189, 126, 157}},
    {234, rgb_color{129, 0, 64}},    {235, rgb_color{129, 86, 107}},
    {236, rgb_color{104, 0, 52}},    {237, rgb_color{104, 69, 86}},
    {238, rgb_color{79, 0, 39}},     {239, rgb_color{79, 53, 66}},
    {240, rgb_color{255, 0, 63}},    {241, rgb_color{255, 170, 191}},
    {242, rgb_color{189, 0, 46}},    {243, rgb_color{189, 126, 141}},
    {244, rgb_color{129, 0, 31}},    {245, rgb_color{129, 86, 96}},
    {246, rgb_color{104, 0, 25}},    {247, rgb_color{104, 69, 78}},
    {248, rgb_color{79, 0, 19}},     {249, rgb_color{79, 53, 59}},
    {250, rgb_color{51, 51, 51}},    {251, rgb_color{80, 80, 80}},
    {252, rgb_color{105, 105, 105}}, {253, rgb_color{130, 130, 130}},
    {254, rgb_color{190, 190, 190}}, {255, rgb_color{255, 255, 255}},
};

} // namespace dxf
} // namespace flywave
