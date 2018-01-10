/** \file
 */

#include "Badge.h"
#include "matrixAnimation.h"
#include "sample-animation-spinner-small.h"
#include "frame-letters.h"
#include "matrixScroller.h"

Badge badge;

const uint8_t DEMO_WIPE = 0;
const uint8_t DEMO_ANIMATION = 1;
const uint8_t DEMO_LETTERS = 2;
const uint8_t DEMO_SCROLLER = 3;
const uint8_t num_demos = 4;

// runtime variables
uint8_t cur_demo = DEMO_SCROLLER;
uint32_t last_draw_millis;
uint32_t update_frequency;
// demo persistence variables
uint16_t msg_idx = 0;

MatrixScroller scroller(" !@#$%^&*()[]<>{}+-=_?/\\:;,.`'\"|~0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ 8008135!  ");

void setup()
{
    badge.begin();
    badge.matrix.setBrightness(100);
    letter_animation.decompress();  // decompress the RLE data so we can pick specific frames
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
  } else if(cur_demo == DEMO_LETTERS) {
    update_frequency = 200; // update every 200ms
    const char msg[] = "IT WORKS";
    // show the next letter of the string
    char curLetter = msg[msg_idx];
    uint8_t frameNo = curLetter - 'A';
    String DEBUG = "DEBUG: ";
    Serial.println(DEBUG + "drawing letter " + curLetter + ", frame=" + frameNo);
    letter_animation.setFrameIndex(frameNo);
    letter_animation.draw(badge.matrix);
    msg_idx++;
    // when we've reached the end of the string, move to the next demo
    if(msg_idx >= strlen(msg)) {
      msg_idx = 0;
      cur_demo++;
    }
  } else if(cur_demo == DEMO_SCROLLER) {
    update_frequency = 150; // update every 100ms
    scroller.draw(badge.matrix);
    if(scroller.getPosition() == 0) {
      // the scroller has completed one play-through, switch to the next demo
      cur_demo++;
    }
  }

  // wrap around if we've played all the demos
  if(cur_demo == num_demos)
    cur_demo = 0;
}




