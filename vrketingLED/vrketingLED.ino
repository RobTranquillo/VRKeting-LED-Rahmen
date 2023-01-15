/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp8266-nodemcu-async-web-server-espasyncwebserver-library/
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/

// Import required libraries
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>  
#include "LightFigures.h"

#pragma region - definition of the global variables -
// network credentials
const char* ssid = "22";
const char* password = "frankreich";

//Direct color LED
const String PROGRAM_DIRECTCOLOR = "DirectColorLed";
const char* PARAM_INPUT_LEDS = "leds";
const char* PARAM_INPUT_COLOR = "color";

// LED strip config
uint8_t LED_PIN = D6;  //#define LED_PIN 6   // arduino  // uint8_t LED_PIN = D6; // esp8266

// INNEN
//unten: 0-11
//rechts: 12-22
//oben: 23-33
//links: 34-45
#define LED_COUNT  80
#define BRIGHTNESS 200 // NeoPixel brightness, 0 (min) to 255 (max)

////////////////////////////////////////////////////////
//Website
////////////////////////////////////////////////////////
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
  <head>
    <title>ESP Web Server</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="icon" href="data:,">
    <style>
      html {font-family: Arial; display: inline-block; text-align: center;}
      h2 {font-size: 3.0rem;}
      p {font-size: 3.0rem;}
      body {max-width: 600px; margin:0px auto; padding-bottom: 25px;}
      .switch {position: relative; display: inline-block; width: 120px; height: 68px} 
      .switch input {display: none}
      .slider {position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: #ccc; border-radius: 6px}
      .slider:before {position: absolute; content: ""; height: 52px; width: 52px; left: 8px; bottom: 8px; background-color: #fff; -webkit-transition: .4s; transition: .4s; border-radius: 3px}
      input:checked+.slider {background-color: #b30000}
      input:checked+.slider:before {-webkit-transform: translateX(52px); -ms-transform: translateX(52px); transform: translateX(52px)}
    </style>
  </head>
  <body>
    <h2>VRketing Ambiligth</h2>
    %BUTTONPLACEHOLDER%
    <script>
    function RunLed(program)
    {
      var xhr = new XMLHttpRequest();
      console.log("LED program: "+program);
      xhr.open("GET", "/"+program+"?leds=5&color=000000", true);
      xhr.send();
    }
    </script>
  </body>
</html>
)rawliteral";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

//LED Figures
LightFigures LF;

#pragma endregion - definition of the global variables -

#pragma region - SETUP/LOOP  -
void setup()
{
  // Serial port for debugging purposes
  Serial.begin(115200);
  LF.setup(LED_COUNT, LED_PIN, BRIGHTNESS);
  LF.Off(); //reset all LED
  ConnectToWiFi();  
  HandleWebrequests();
  server.begin();
}

void loop() {
}
#pragma endregion - SETUP/LOOP -

#pragma region - network functions -
////////////////////////////////////////////////////////
//NETWORK FUNCTIONS
////////////////////////////////////////////////////////
void ConnectToWiFi()
{
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println(WiFi.localIP());
}

void HandleWebrequests()
{
  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  // Send a GET request to <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
  server.on("/DirectColorLed", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputLeds;
    String inputColor; 

    //if direct led+color input is given
    if (request->hasParam(PARAM_INPUT_LEDS) && request->hasParam(PARAM_INPUT_COLOR)) 
    { 
      inputLeds = request->getParam(PARAM_INPUT_LEDS)->value();
      inputColor = request->getParam(PARAM_INPUT_COLOR)->value();    
      DirectColorLed(inputLeds, inputColor); 
    }
    request->send(200, "text/plain", "OK");
  });
}
#pragma endregion - network functions -

#pragma region - helper functions -
////////////////////////////////////////////////////////
//HELPER FUNCTIONS
////////////////////////////////////////////////////////

// Replaces placeholder with button section in your web page
String processor(const String& var)
{
  //Serial.println(var);
  if(var == "BUTTONPLACEHOLDER")
  {
    String buttons = "";
    buttons += "<H4>led one<h4><a href=\"#\" onclick=\"RunLed('"+PROGRAM_DIRECTCOLOR+"')\">led direct color</a> <br>you can edit the GET param by yourself by: /"+PROGRAM_DIRECTCOLOR+"&leds=5&color=000000";
    return buttons;
  }
  return String();
}
#pragma endregion - helper functions -


////////////////////////////////////////////////////////
//LED FUNCTIONS
////////////////////////////////////////////////////////
void DirectColorLed(const String& leds, const String& color)
{
  Serial.print("leds: " +leds+ " color: " + color);
  LF.OneColor(0, 0, 255, 0); //param 0 == hex color
}