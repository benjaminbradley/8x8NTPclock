/** \file
 */

#include "Badge.h"

Badge badge;

uint32_t last_draw_millis;


void setup()
{
    badge.begin();
    badge.matrix.setBrightness(100);
}

void loop()
{
  const uint32_t now = millis();

  // Draw the LEDs at 60Hz
  if (now - last_draw_millis < (1000/60))
      return;

  last_draw_millis = now;

  static int x=0;
  static int y=0;
  static uint32_t color = 0xffffff;
  badge.matrix.set(x, y, color);
  badge.matrix.show();
  x++;
  if(x >= LED_COLS) {
    x=0;
    y++;
    if(y >= LED_ROWS) {
      y=0;
      if(color == 0xffffff) {
        color = 0;
      } else {
        color = 0xffffff;
      }
    }
  }
}


