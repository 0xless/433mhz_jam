
#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>

// use first channel of 16 channels (started from zero)
#define LEDC_CHANNEL_0     0

// use 12 bit precission for LEDC timer
#define LEDC_TIMER_12_BIT  12

// use 5000 Hz as a LEDC base frequency
#define LEDC_BASE_FREQ     5000
// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
// SSID & Password
const char* ssid = "YOUR_SSID";  // Enter your SSID here
const char* password = "12345678";  //Enter your Password here

// turn on html page
const char * turn_on_html PROGMEM = "<!DOCTYPE html>"
"<html>"
"<head>"
"<title> 433Mhz Jam Control Panel </title>"
"<style>"
".button {"
"  border: none;"
"  color: white;"
"  padding: 15px 32px;"
"  text-align: center;"
"  display: inline-block;"
"  font-size: 58px;"
"  margin: 4px 2px;"
"  border-radius: 15px;"
"  font-family: sans-serif;"
"  cursor: pointer;"
"}"
""
".center {"
"  position:absolute;"
"  top:50%;"
"  left:50%;"
"  width :200px;"
"  height:200px;"
"  margin-left:-140px;"
"  margin-top:-100px;"
"}"
""
".button_green {background-color: green;}"
"</style>"
"</head>"

"<div class=\"center\">"
" <a href=\"turn_off\">"
"    <button class=\"button button_green\">"
"    Start jamming"
"    </button>"
"  </a>"
"</div>"
""
"</body>"
"</html>";


// turn off html page
const char * turn_off_html PROGMEM = "<!DOCTYPE html>"
"<html>"
"<head>"
"<title>  433Mhz Jam Control Panel </title>"
"<style>"
".button {"
"  border: none;"
"  color: white;"
"  padding: 15px 32px;"
"  text-align: center;"
"  display: inline-block;"
"  font-size: 58px;"
"  margin: 4px 2px;"
"  border-radius: 15px;"
"  font-family: sans-serif;"
"  cursor: pointer;"
"}"
""
".center {"
"  position:absolute;"
"  top:50%;"
"  left:50%;"
"  width :200px;"
"  height:200px;"
"  margin-left:-140px;"
"  margin-top:-100px;"
"}"
""
".button_red {background-color: red;}"
"</style>"
"</head>"

"<div class=\"center\">"
" <a href=\"turn_on\">"
"    <button class=\"button button_red\">"
"    Stop jamming"
"    </button>"
"  </a>"
"</div>"
""
"</body>"
"</html>";


// IP Address details
IPAddress local_ip(192, 168, 2, 1);
IPAddress gateway(192, 168, 2, 1);
IPAddress subnet(255, 255, 255, 0);

int jam_flag = 0;
int out_pin = 16;

void setup()
{
  pinMode(2, OUTPUT);
  ledcSetup(LEDC_CHANNEL_0, LEDC_BASE_FREQ, LEDC_TIMER_12_BIT);
  ledcAttachPin(out_pin, LEDC_CHANNEL_0);
  // Serial port for debugging purposes
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  Serial.println();
  Serial.println("Configuring access point...");

  if (!WiFi.softAP(ssid, password, 6, 0, 2, false)) {
    log_e("Soft AP creation failed.");
    while(1);
  }
  WiFi.softAPConfig(local_ip, gateway, subnet);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("[*] SSID: ");
  Serial.println(ssid);
  Serial.print("[*] password: ");
  Serial.println(password);

  Serial.println("Server started");
  // Routes for web pages
  // root "/"
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send_P(200, "text/html", turn_on_html);
  });

  // turn on page "/turn_on"
  server.on("/turn_on", HTTP_GET, [jam_flag](AsyncWebServerRequest *request)
  {
    jam_flag = 0;
    toggle_jamming(jam_flag);
    request->send_P(200, "text/html", turn_on_html);
  });

  // turn off page "/turn_off"
  server.on("/turn_off", HTTP_GET, [jam_flag](AsyncWebServerRequest *request)
  {
    jam_flag = 1;
    toggle_jamming(jam_flag);
    request->send_P(200, "text/html", turn_off_html);
  });

  // Start server
  server.begin();

  Serial.println("[+] Server started");

}

void toggle_jamming(int jam_flag)
{
  if(jam_flag == 1)
  {
      tone(out_pin, 20000); // send square wave on pin
      digitalWrite(2, HIGH);
      Serial.println("[+] Started jamming");
  }
  else
  {
      tone(out_pin, 0);   // send nothing to pin
      digitalWrite(2, LOW);
      Serial.println("[+] Stopped jamming");
  }

}
void loop() 
{
}
