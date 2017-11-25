/** \file
 */

#include "Badge.h"
#include "matrixAnimation.h"
#include "sample-animation-spinner-small.h"

Badge badge;

const uint8_t DEMO_WIPE = 0;
const uint8_t DEMO_ANIMATION = 1;
const uint8_t num_demos = 2;

// runtime variables
uint8_t cur_demo = DEMO_WIPE;
uint32_t last_draw_millis;
uint32_t update_frequency;

void setup()
{
    badge.begin();
    badge.matrix.setBrightness(100);
}

void loop()
{
  // display the sample animation
  const uint32_t now = millis();

  if (now - last_draw_millis < update_frequency)
    return;
  last_draw_millis = now;

  if(cur_demo == DEMO_WIPE) {
    update_frequency = 1000/60; // run the LED wipe at 60KHz
    static uint16_t x=0;
    static uint16_t y=0;
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
          // switch to the next demo
          cur_demo++;
        }
      }
    }
  } else if(cur_demo == DEMO_ANIMATION) {
    update_frequency = animation.getFrameDelay();
    // draw the next frame of the animation
    animation.draw(badge.matrix);
    if(animation.getFrameIndex() == 0) {
      // the animation has completed one play-through, switch to the next demo
      cur_demo++;
    }
  }
  // wrap around if we've played all the demos
  if(cur_demo == num_demos)
    cur_demo = 0;
}



