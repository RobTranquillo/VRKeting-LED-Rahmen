#include "LightFigures.h"
#include <Adafruit_NeoPixel.h>
#include "NeoPixelBlink.h"

////
//  ACHTUNG! KEINE ENDLOS-LOOPS BAUEN!
//  Nach jeder Runde muss jede LED Funktion wieder
//  in den Main Thread springen und auf neue Anweisung warten!
//  Nutze den repeatRoute parameter
////


NeoPixelBlink neoPixelBlink = NeoPixelBlink();

void LightFigures::setup(int led_count, int led_pin, int brightness)
{
    neoPixelBlink.setup(led_count, led_pin, brightness);
}


// //// United Colors Of Rob ////
// //////////////////////////////
void LightFigures::Off()
{
    neoPixelBlink.setAll(0,0,0);
}

void LightFigures::OneColor(int red, int green, int blue, int wait)
{
    neoPixelBlink.colorWipe(red,green,blue, wait);
}
void LightFigures::OneColor(String hex, int wait)
{
    char tmp[hex.length() + 1];
    strcpy(tmp, hex.c_str());
    int num = (int)strtol(tmp, NULL, 16);
    neoPixelBlink.colorWipe(num, wait);
}


void LightFigures::Rainbow(int wait) {
    neoPixelBlink.Rainbow(wait);
} 







// void LightFigures::PlayFigure(Route route)
// {
//     uint32_t red = neoPixelBlink.Color((uint8_t) 255, (uint8_t) 0, (uint8_t) 0,(uint8_t) 255);
//     int wait = 5;
//     switch(route.type)
//     {
//         case RouteType::Null:
//             Serial.println("### Home/Off");
//             Off();
//             break;
//         case RouteType::Randomcolor:
//             Serial.println("### one Random color");
//             break;
//         case RouteType::White:
//             Serial.println("### one white");
//             break;
//         case RouteType::Blue:
//             Serial.println("### one blue");
//             break;
//         case RouteType::Green:
//             Serial.println("### one green");
//             break;
//         case RouteType::Red:
//             Serial.println("### one red");
//             break;

//         case RouteType::Colorpicker:
//             Serial.println("### One Colorpicker");
//             OneColor(route.parameter, wait); //param == hex color
//             break;

//         case RouteType::KITT:
//             Serial.println("### K.I.T.T.");
//             NewKITT(0xff, 0, 0, 8, 10, 50);
//             break;

//         case RouteType::Rainbow:
//             Serial.println("### Rainbow");
//             neoPixelBlink.Rainbow(wait);
//             break;

//         case RouteType::RainbowCycle:
//             Serial.println("### Rainbow Cycle");
//             RainbowCycle(wait);
//             break;
//         case RouteType::RainbowCycleSpeed:
//             Serial.println("### Rainbow Cycle Speed");
//             RainbowCycle(route.parameter.toInt());
//             break;

//         case RouteType::Fire:
//             Serial.println("### Rainbow Fire");
//             //Feuereffekt
//             neoPixelBlink.Fire(55, 120, 15);
//             break;
//         case RouteType::Edges_left:
//             Serial.println("### Edges left");
//             EdgesLeft(red);
//             break;
//         case RouteType::Edges_right:
//             Serial.println("### Edges right");
//             EdgesRight(red);
//             break;
//         case RouteType::Edges_top:
//             Serial.println("### Edges top");
//             EdgesTop(red);
//             break;
//         case RouteType::Edges_bottom:
//             Serial.println("### Edges bottom");
//             EdgesBottom(red);
//             break;
//         case RouteType::Edges_rotate:
//             Serial.println("### Edges rotate");
//             EdgesRotate(red, 200);
//             break;
//     }
// }

// Route LightFigures::GetRoute(String url)
// {
//     int wait = 5;
//     Route route;
//     if (url.indexOf("GET /randomcolor") >= 0) {
//         OneColor(random(0, 255), random(0, 255), random(0, 255), wait);
//     }
//     if (url.indexOf("GET /white") >= 0) {
//         OneColor(255, 255, 255, wait);
//     }
//     if (url.indexOf("GET /blue") >= 0) {
//         OneColor(0, 0, 255, wait);
//     }
//     if (url.indexOf("GET /red") >= 0) {
//         OneColor(255, 0, 0, wait);
//     }
//     if (url.indexOf("GET /green") >= 0) {
//         OneColor(0, 255, 0, wait);
//     }
//     if (url.indexOf("GET /?colorpicker=") >= 0) {
//         route.type = RouteType::Colorpicker;
//         route.parameter = url.substring(url.indexOf("colorpicker=%")+15);
//         return route;
//     }
//     if (url.indexOf("GET /KITT ") >= 0) {
//         route.type = RouteType::KITT;
//         route.repeatRoute = true;
//         return route;
//     }
//     if (url.indexOf("GET /rainbow ") >= 0) {
//         route.type = RouteType::Rainbow;
//         route.repeatRoute = true;
//         return route;
//     }
//     if (url.indexOf("GET /rainbowcycle ") >= 0) {
//         route.type = RouteType::RainbowCycle;
//         route.repeatRoute = true;
//         return route;
//     }
//     if (url.indexOf("GET /?rainbowcyclespeed=") >= 0) {
//         route.type = RouteType::RainbowCycleSpeed;
//         route.repeatRoute = true;
//         int start = url.indexOf('=') + 1;
//         route.parameter = url.substring(start, url.indexOf(' ', start));
//         return route;
//     }
//     if (url.indexOf("GET /fire ") >= 0) {
//         route.type = RouteType::Fire;
//         route.repeatRoute = true;
//         return route;
//     }
//     if (url.indexOf("GET /edges_left ") >= 0) {
//         route.type = RouteType::Edges_left;
//         return route;
//     }
//     if (url.indexOf("GET /edges_right ") >= 0) {
//         route.type = RouteType::Edges_right;
//         return route;
//     }
//     if (url.indexOf("GET /edges_top ") >= 0) {
//         route.type = RouteType::Edges_top;
//         return route;
//     }
//     if (url.indexOf("GET /edges_bottom ") >= 0) {
//         route.type = RouteType::Edges_bottom;
//         return route;
//     }
//     if (url.indexOf("GET /edges_rotate ") >= 0) {
//         route.type = RouteType::Edges_rotate;
//         route.repeatRoute = true;
//         return route;
//     }
//     return route;
// }

// ////
// // Black out and light one edge
// // Edges Verteilung
// // unten links:  0-12   (13)
// // links:        13-32  (19)
// // oben:         33-58  (25)
// // rechts:       57-76  (19)
// // unten rechts: 77-90  (13)
// ///
// void LightFigures::EdgesBottom(uint32_t color)
// {
//     neoPixelBlink.Flush();
//     neoPixelBlink.ColorRange(0,12, color);
//     neoPixelBlink.ColorRange(77,14, color);
// }

// ////
// // Black out and light one edge
// ///
// void LightFigures::EdgesTop(uint32_t color)
// {
//     neoPixelBlink.Flush();
//     neoPixelBlink.ColorRange(32, 25, color);
// }

// ////
// // Black out and light one edge
// ///
// void LightFigures::EdgesRight(uint32_t color)
// {
//     neoPixelBlink.Flush();
//     neoPixelBlink.ColorRange(57, 19, color);
// }

// ////
// // Black out and light one edge
// ///
// void LightFigures::EdgesLeft(uint32_t color)
// {
//     neoPixelBlink.Flush();
//     neoPixelBlink.ColorRange(13, 19, color);
// }

// ////
// // Black out and light one edge clockwise
// ///
// void LightFigures::EdgesRotate(uint32_t color, uint8_t wait)
// {
//     EdgesLeft(color);
//     delay(wait);
//     EdgesRight(color);
//     delay(wait);
//     EdgesTop(color);
//     delay(wait);
//     EdgesBottom(color);
//     delay(wait);
// }


// //// United Colors Of Rob
// //////////////////////////////////////////////////////////////////
// void LightFigures::Off()
// {
//     neoPixelBlink.setAll(0,0,0);
// }

// void LightFigures::OneColor(int red, int green, int blue, int wait)
// {
//     neoPixelBlink.colorWipe(red,green,blue, wait);
// }
// void LightFigures::OneColor(String hex, int wait)
// {
//     char tmp[hex.length() + 1];
//     strcpy(tmp, hex.c_str());
//     int num = (int)strtol(tmp, NULL, 16);
//     neoPixelBlink.colorWipe(num, wait);
// }

// //// NewKitt
// void LightFigures::NewKITT(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay)
// {
//     neoPixelBlink.RightToLeft(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
//     neoPixelBlink.LeftToRight(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
//     neoPixelBlink.OutsideToCenter(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
//     neoPixelBlink.CenterToOutside(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
//     neoPixelBlink.LeftToRight(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
//     neoPixelBlink.RightToLeft(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
//     neoPixelBlink.OutsideToCenter(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
//     neoPixelBlink.CenterToOutside(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
// }


// void LightFigures::Rainbow(int wait) {
//     neoPixelBlink.Rainbow(wait);
// }

// // Slightly different, this makes the rainbow equally distributed throughout
// void LightFigures::RainbowCycle(int wait) {
//         neoPixelBlink.RainbowCycle(wait);
// }
