/** \file
 */

#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include "Badge.h"
#include "matrixScroller.h"

// constants
#define TIME_UPDATE_FREQUENCY_MS 60000
#define TZ_OFFSET_SEC (-60*60*5)

const char* ssid = "****************";
const char* password = "****************";

// services
Badge badge;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", TZ_OFFSET_SEC);

// runtime variables
uint32_t last_draw_millis;
uint32_t update_frequency = 100;
MatrixScroller* scroller;


void update_time() {
  timeClient.update();
  Serial.print("Got time from timeClient: ");
  Serial.println(timeClient.getFormattedTime());
  scroller = new MatrixScroller(String("  ") + timeClient.getFormattedTime() + String("  "));
}


void setup()
{
  badge.begin();
  badge.matrix.setBrightness(100);

  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  timeClient.begin();
  update_time();
}


void loop()
{
  // display the sample animation
  const uint32_t now = millis();

  if (now - last_draw_millis < update_frequency)
    return;
  last_draw_millis = now;

  scroller->draw(badge.matrix);
  if(scroller->getPosition() == 0) {
    // the scroller has completed one play-through, update the BTC value if stale
    delete scroller;
    update_time();
  }
}
