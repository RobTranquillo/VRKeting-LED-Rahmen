#ifndef LIGHTFIGURES_H
#define LIGHTFIGURES_H

#include "Arduino.h"

// enum RouteType
// {
//     Null,
//     Colorpicker,
//     Randomcolor,
//     White,
//     Blue,
//     Green,
//     Red,
//     KITT,
//     Rainbow,
//     RainbowCycle,
//     RainbowCycleSpeed,
//     Fire,
//     Edges_left,
//     Edges_right,
//     Edges_top,
//     Edges_bottom,
//     Edges_rotate,
// };

// struct Route
// {
//     RouteType type;
//     String parameter;
//     bool repeatRoute = false;
// };

class LightFigures
{
    public:
        void setup(int led_count, int led_pin, int brightness);
        // Route GetRoute(String urlParam);
        // void PlayFigure(Route route);

        void Off();
        void OneColor(int red, int green, int blue, int wait);
        void OneColor(String hex, int wait);
        // void NewKITT(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay);
        void Rainbow(int wait);
        // void RainbowCycle(int wait);

        // void EdgesBottom(uint32_t color);
        // void EdgesTop(uint32_t color);
        // void EdgesRight(uint32_t color);
        // void EdgesLeft(uint32_t color);
        // void EdgesRotate(uint32_t color, uint8_t delay);
};

#endif
