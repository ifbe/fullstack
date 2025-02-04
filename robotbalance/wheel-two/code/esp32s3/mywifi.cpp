#include <WiFi.h>
#include <WebServer.h>
#include "mystor.h"

const char* ap_ssid = "esp32s3_muselab";
const char* ap_pass = "12345678";

String sta_ssid = "";
String sta_pass = "";

WebServer server(80);

void build_page_head(String& html){
  html += "<a href='/wifi'>wifi</a>\n";
  html += "<a href='/ble'>ble</a>\n";
  html += "<a href='/sensor'>sensor</a>\n";
  html += "<a href='/mahony'>mahony</a>\n";
  html += "<a href='/planner'>planner</a>\n";
  html += "<a href='/led'>led</a>\n";
  html += "<a href='/motor'>motor</a>\n";
  html += "<a href='/battery'>battery</a>\n";
  html += "<hr>\n";
}

void handle_wifi() {
  Serial.println(__FUNCTION__);

  String html;
  build_page_head(html);
  html += "<form action='/wifisave' method='POST'>";
  html += "SSID: <input type='text' name='ssid' value='" + sta_ssid + "'><br>";
  html += "PASS: <input type='password' name='pass' value='" + sta_pass + "'><br>";
  html += "<input type='submit' value='Save'>";
  html += "</form>";
  server.send(200, "text/html", html);
}

void handle_wifi_save() {
  Serial.println(__FUNCTION__);

  sta_ssid = server.arg("ssid");
  sta_pass = server.arg("pass");
  saveCredentials(sta_ssid, sta_pass);
  server.send(200, "text/plain", "Credentials saved. Restarting...");
  delay(1000);
  esp_restart();
}

void handle_ble() {
  Serial.println(__FUNCTION__);

  String html;
  build_page_head(html);
  html += "...";
  server.send(200, "text/html", html);
}

void handle_sensor() {
  Serial.println(__FUNCTION__);

  String html;
  build_page_head(html);
  server.send(200, "text/html", html);
}

void handle_mahony() {
  Serial.println(__FUNCTION__);

  String html;
  build_page_head(html);
  server.send(200, "text/html", html);
}

void handle_planner() {
  Serial.println(__FUNCTION__);

  String html;
  build_page_head(html);
  server.send(200, "text/html", html);
}

void handle_led() {
  Serial.println(__FUNCTION__);

  String html;
  build_page_head(html);
  server.send(200, "text/html", html);
}

void handle_motor() {
  Serial.println(__FUNCTION__);

  String html;
  build_page_head(html);
  server.send(200, "text/html", html);
}

void handle_battery() {
  Serial.println(__FUNCTION__);

  String html;
  build_page_head(html);
  server.send(200, "text/html", html);
}

void handleRoot() {
  handle_wifi();
}

void WiFiEvent(WiFiEvent_t event) {
  switch (event) {
  case ARDUINO_EVENT_WIFI_OFF:   //100
    Serial.println("ARDUINO_EVENT_WIFI_OFF");
    break;
  case ARDUINO_EVENT_WIFI_READY:
    Serial.println("ARDUINO_EVENT_WIFI_READY");
    break;
  case ARDUINO_EVENT_WIFI_SCAN_DONE:
    Serial.println("ARDUINO_EVENT_WIFI_SCAN_DONE");
    break;
  case ARDUINO_EVENT_WIFI_FTM_REPORT:
    Serial.println("ARDUINO_EVENT_WIFI_FTM_REPORT");
    break;
  case ARDUINO_EVENT_WIFI_STA_START:   //110
    Serial.println("ARDUINO_EVENT_WIFI_STA_START");
    break;
  case ARDUINO_EVENT_WIFI_STA_STOP:
    Serial.println("ARDUINO_EVENT_WIFI_STA_STOP");
    break;
  case ARDUINO_EVENT_WIFI_STA_CONNECTED:
    Serial.println("ARDUINO_EVENT_WIFI_STA_CONNECTED");
    break;
  case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
    Serial.println("ARDUINO_EVENT_WIFI_STA_DISCONNECTED");
    break;
  case ARDUINO_EVENT_WIFI_STA_AUTHMODE_CHANGE:
    Serial.println("ARDUINO_EVENT_WIFI_STA_AUTHMODE_CHANGE");
    break;
  case ARDUINO_EVENT_WIFI_STA_GOT_IP:
    Serial.printf("ARDUINO_EVENT_WIFI_STA_GOT_IP: %s\n", WiFi.localIP().toString());
    break;
  case ARDUINO_EVENT_WIFI_STA_GOT_IP6:
    Serial.println("ARDUINO_EVENT_WIFI_STA_GOT_IP6");
    break;
  case ARDUINO_EVENT_WIFI_STA_LOST_IP:
    Serial.println("ARDUINO_EVENT_WIFI_STA_LOST_IP");
    break;
  case ARDUINO_EVENT_WIFI_AP_START:    //130
    Serial.println("ARDUINO_EVENT_WIFI_AP_START");
    break;
  case ARDUINO_EVENT_WIFI_AP_STOP:
    Serial.println("ARDUINO_EVENT_WIFI_AP_STOP");
    break;
  case ARDUINO_EVENT_WIFI_AP_STACONNECTED:
    Serial.println("ARDUINO_EVENT_WIFI_AP_STACONNECTED");
    break;
  case ARDUINO_EVENT_WIFI_AP_STADISCONNECTED:
    Serial.println("ARDUINO_EVENT_WIFI_AP_STADISCONNECTED");
    break;
  case ARDUINO_EVENT_WIFI_AP_STAIPASSIGNED:
    Serial.println("ARDUINO_EVENT_WIFI_AP_STAIPASSIGNED");
    break;
  case ARDUINO_EVENT_WIFI_AP_PROBEREQRECVED:
    Serial.println("ARDUINO_EVENT_WIFI_AP_PROBEREQRECVED");
    break;
  case ARDUINO_EVENT_WIFI_AP_GOT_IP6:
    Serial.println("ARDUINO_EVENT_WIFI_AP_GOT_IP6");
    break;
  default:
    Serial.printf("Unknown WiFi event: %d\n", event);
    break;
  }
}

void initwifi()
{
  loadCredentials(sta_ssid, sta_pass);
  Serial.printf("ap: ssid=%s, pass=%s\n", ap_ssid, ap_pass);
  Serial.printf("sta: ssid=%s, pass=%s\n", sta_ssid.c_str(), sta_pass.c_str());

  WiFi.onEvent(WiFiEvent);

  WiFi.softAP(ap_ssid, ap_pass);
  WiFi.begin(sta_ssid.c_str(), sta_pass.c_str());

  server.on("/", handleRoot);
  server.on("/wifi", handle_wifi);
  server.on("/wifisave", handle_wifi_save);
  server.on("/ble", handle_ble);
  server.on("/sensor", handle_sensor);
  server.on("/mahony", handle_mahony);
  server.on("/planner", handle_planner);
  server.on("/led", handle_led);
  server.on("/motor", handle_motor);
  server.on("/battery", handle_battery);
  server.begin();

  Serial.println("AP IP address: " + WiFi.softAPIP().toString());
}

void pollwifi()
{
  server.handleClient();
}
