#ifndef NEOPIXELBLINK_H
#define NEOPIXELBLINK_H

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>

class NeoPixelBlink
{
    public:
        Adafruit_NeoPixel *strip;
        void setup(int, int, int);

        uint32_t Color(uint8_t r, uint8_t g, uint8_t b);
        uint32_t Color(uint8_t r, uint8_t g, uint8_t b, uint8_t w);

        void colorWipe(int r, int g, int b, int wait);
        void colorWipe(uint32_t color, int wait);
        // void whiteOverRainbow(int whiteSpeed, int whiteLength);
        void pulseWhite(uint8_t wait);
        // void rainbowFade2White(int wait, int rainbowLoops, int whiteLoops);

        void showStrip();
        void setPixel(int Pixel, byte red, byte green, byte blue);
        void setAll(byte red, byte green, byte blue);

        void RightToLeft(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay);
        void LeftToRight(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay);
        void OutsideToCenter(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay);
        void CenterToOutside(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay);

        uint32_t Wheel(byte WheelPos);
        void setPixelHeatColor (int Pixel, byte temperature);

        void Rainbow(int wait);
        void RainbowCycle(int wait);

        void Fire(int Cooling, int Sparking, int SpeedDelay);

        void Flush();
        void ColorRange(int start, int length, uint32_t color);

    private:

};

#endif
