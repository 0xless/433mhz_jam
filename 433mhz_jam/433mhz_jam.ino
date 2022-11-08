
// Libraries for web server/AP
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

// SSID & Password
const char* ssid = "433mhzjam";  // Enter your SSID here
const char* password = "123456789";  //Enter your Password here

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

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// IP Address details
IPAddress local_ip(192, 168, 2, 1);
IPAddress gateway(192, 168, 2, 1);
IPAddress subnet(255, 255, 255, 0);

int jam_flag = 0;
int on_off_flag = 0;
int on_off_flag_b = 0;

int out_pin = 4;

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  
  // Create SoftAP
  WiFi.softAP(ssid, password);
  delay(5000);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  
  Serial.println("");
  Serial.println("[+] Access point created");
  
  Serial.print("[*] SSID: ");
  Serial.println(ssid);
  Serial.print("[*] password: ");
  Serial.println(password);
  
  // Routes for web pages
  // root "/"
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", turn_on_html);
  });

  // turn on page "/turn_on"
  server.on("/turn_on", HTTP_GET, [jam_flag](AsyncWebServerRequest *request)
  {
    jam_flag = 0;
    request->send_P(200, "text/html", turn_on_html);
  });

  // turn off page "/turn_off"
  server.on("/turn_off", HTTP_GET, [jam_flag](AsyncWebServerRequest *request)
  {
    jam_flag = 1;
    request->send_P(200, "text/html", turn_off_html);
  });

  // Start server
  server.begin();

  Serial.println("[+] Server started");

}

void loop() 
{
  if(jam_flag == 1)
  {
    if(on_off_flag == 0)
    {
      tone(out_pin, 20000); // send square wave on pin
      on_off_flag = 1;
      Serial.println("[+] Started jamming");
    }
    
    on_off_flag_b = 0;
  }
  else
  {
    if(on_off_flag_b == 0)
    {
      tone(out_pin, 0);   // send nothing to pin
      on_off_flag_b = 1;
      Serial.println("[+] Stopped jamming");
    }
    
    on_off_flag = 0;
  }
}
