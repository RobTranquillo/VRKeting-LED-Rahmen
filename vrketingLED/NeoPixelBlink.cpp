// NeoPixel test program showing use of the WHITE channel for RGBW
// pixels only (won't look correct on regular RGB NeoPixel strips).

#include "NeoPixelBlink.h"
#include <Adafruit_NeoPixel.h>
#include <stdio.h>
#include <stdlib.h>

// Declare our NeoPixel strip object:
Adafruit_NeoPixel* strip = NULL;
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

void NeoPixelBlink::setup(int led_count, int led_pin, int brightness)
{
  Serial.print("led_count: "); Serial.println(led_count);

  strip = new Adafruit_NeoPixel(led_count, led_pin, NEO_GRB + NEO_KHZ800);
  strip->begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip->show();            // Turn OFF all pixels ASAP
  strip->setBrightness(brightness); // Set brightness to about 1/5 (max = 255)
  strip->fill(strip->Color(0,0,255,255), 0);
}

/*!
  @brief   Convert separate red, green and blue values into a single
            "packed" 32-bit RGB color.
  @param   r  Red brightness, 0 to 255.
  @param   g  Green brightness, 0 to 255.
  @param   b  Blue brightness, 0 to 255.
  @return  32-bit packed RGB value, which can then be assigned to a
            variable for later use or passed to the setPixelColor()
            function. Packed RGB format is predictable, regardless of
            LED strand color order.
*/
uint32_t NeoPixelBlink::Color(uint8_t r, uint8_t g, uint8_t b)
{
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

/*!
  @brief   Convert separate red, green, blue and white values into a
            single "packed" 32-bit WRGB color.
  @param   r  Red brightness, 0 to 255.
  @param   g  Green brightness, 0 to 255.
  @param   b  Blue brightness, 0 to 255.
  @param   w  White brightness, 0 to 255.
  @return  32-bit packed WRGB value, which can then be assigned to a
            variable for later use or passed to the setPixelColor()
            function. Packed WRGB format is predictable, regardless of
            LED strand color order.
*/
uint32_t NeoPixelBlink::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t w)
{
  return ((uint32_t)w << 24) | ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

void NeoPixelBlink::pulseWhite(uint8_t wait)
{
  for(int j=0; j<256; j++)
  { // Ramp up from 0 to 255
    // Fill entire strip with white at gamma-corrected brightness level 'j':
    strip->fill(strip->Color(0, 0, 0, strip->gamma8(j)));
    strip->show();
    delay(wait);
  }

  for(int j=255; j>=0; j--)
  { // Ramp down from 255 to 0
    strip->fill(strip->Color(0, 0, 0, strip->gamma8(j)));
    strip->show();
    delay(wait);
  }
}

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip->Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.

// void NeoPixelBlink::colorWipe(uint32_t color, int wait)
void NeoPixelBlink::colorWipe(int r, int g, int b, int wait)
{
  uint32_t color = strip->Color((uint8_t) r, (uint8_t) g, (uint8_t) b, 255);
  NeoPixelBlink::colorWipe(color, wait);
}

void NeoPixelBlink::colorWipe(uint32_t color, int wait)
{
  for(int i=0; i<strip->numPixels(); i++)     // For each pixel in strip->..
  {
    strip->setPixelColor(i, color);           //  Set pixel's color (in RAM)
    strip->show();                            //  Update strip to match
    delay(wait);                              //  Pause for a moment
  }
}

void NeoPixelBlink::setPixel(int Pixel, byte red, byte green, byte blue)
{
  strip->setPixelColor(Pixel, strip->Color(red, green, blue));
}

void NeoPixelBlink::setAll(byte red, byte green, byte blue)
{
  for(int i = 0; i < strip->numPixels(); i++ )
  {
    setPixel(i, red, green, blue);
  }
  strip->show();
}

void NeoPixelBlink::CenterToOutside(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay)
{
  for(int i =((strip->numPixels()-EyeSize)/2); i>=0; i--)
  {
    setAll(0,0,0);

    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue);
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);

    setPixel(strip->numPixels()-i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(strip->numPixels()-i-j, red, green, blue);
    }
    setPixel(strip->numPixels()-i-EyeSize-1, red/10, green/10, blue/10);

    strip->show();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

void NeoPixelBlink::OutsideToCenter(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay)
{
  for(int i = 0; i<=((strip->numPixels()-EyeSize)/2); i++) {
    setAll(0,0,0);

    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue);
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);

    setPixel(strip->numPixels()-i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(strip->numPixels()-i-j, red, green, blue);
    }
    setPixel(strip->numPixels()-i-EyeSize-1, red/10, green/10, blue/10);

    strip->show();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

void NeoPixelBlink::LeftToRight(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay)
{
  for(int i = 0; i < strip->numPixels() - EyeSize - 2; i++)
  {
    setAll(0,0,0);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue);
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    strip->show();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

void NeoPixelBlink::RightToLeft(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay)
{
  for(int i = strip->numPixels() - EyeSize - 2; i > 0; i--)
  {
    setAll(0,0,0);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue);
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    strip->show();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

//framekid

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t NeoPixelBlink::Wheel(byte WheelPos)
{
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip->Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip->Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip->Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}


void NeoPixelBlink::setPixelHeatColor (int Pixel, byte temperature)
{
  // Scale 'heat' down from 0-255 to 0-191
  byte t192 = round((temperature/255.0)*191);

  // calculate ramp up from
  byte heatramp = t192 & 0x3F; // 0..63
  heatramp <<= 2; // scale up to 0..252

  // figure out which third of the spectrum we're in:
  if( t192 > 0x80) {                     // hottest
    setPixel(Pixel, 255, 255, heatramp);
  } else if( t192 > 0x40 ) {             // middle
    setPixel(Pixel, 255, heatramp, 0);
  } else {                               // coolest
    setPixel(Pixel, heatramp, 0, 0);
  }
}


void NeoPixelBlink::Rainbow(int wait)
{
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i< strip->numPixels(); i++) {
      strip->setPixelColor(i, Wheel((i+j) & 255));
    }
    strip->show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void NeoPixelBlink::RainbowCycle(int wait)
{
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip->numPixels(); i++) {
      strip->setPixelColor(i, Wheel(((i * 256 / strip->numPixels()) + j) & 255));
    }
    strip->show();
    delay(wait);
  }
}

//Feuereffekt
void NeoPixelBlink::Fire(int Cooling, int Sparking, int SpeedDelay)
{
  static byte heat[60];
  int cooldown;
  for(int z = 0; z < 230; z++)
  {
    // Step 1.  Cool down every cell a little
    /////// hier drinne crasht es immer   /////////////
    for( int i = 0; i < strip->numPixels(); i++)
    {
      cooldown = random(0, ((Cooling * 10) / strip->numPixels()) + 2);

      if(cooldown>heat[i]) {
        heat[i]=0;
      } else {
        heat[i]=heat[i]-cooldown;
      }
    }

    // // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    // for( int k= strip->numPixels() - 1; k >= 2; k--) {
    //   heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
    // }

    // // Step 3.  Randomly ignite new 'sparks' near the bottom
    // if( random(255) < Sparking ) {
    //   int y = random(7);
    //   heat[y] = heat[y] + random(160,255);
    //   //heat[y] = random(160,255);
    // }

    // // Step 4.  Convert heat to LED colors
    // for( int j = 0; j < strip->numPixels(); j++) {
    //   NeoPixelBlink::setPixelHeatColor(j, heat[j] );
    // }

    strip->show();
    delay(SpeedDelay);
  }
}

// Setze alle LEDs auf schwarz
void NeoPixelBlink::Flush()
{
  for(uint16_t i=0; i < strip->numPixels(); i++)
  {
    strip->setPixelColor(i, 0);
  }
  strip->show();
}

// nur einen Bereich des Strips erhellen
void NeoPixelBlink::ColorRange(int start, int length, uint32_t color)
{
  for(uint16_t i=start; i < strip->numPixels(); i++)
  {
    if (i >= start+length)
      break;
    strip->setPixelColor(i, color);
  }
  strip->show();
}
