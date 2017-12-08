#ifndef MATRIX_SCROLLER_H
#define MATRIX_SCROLLER_H

#include <Arduino.h>
#include "RGBMatrix.h"

/*
future configuration:
color
vertical position
*/


class MatrixScroller {
  public:

    // constructor/initializer
    // pass in string to be displayed
    MatrixScroller(String message_);

    uint8_t getPosition();
    
    // draw the next frame on the matrix and advance the horizontal position by one column
    // @param matrix[] LED matrix to draw to.
    void draw(RGBMatrix &matrix);

  private:
    String message;
    uint8_t position = 0;
    //uint8_t messageIndex = 0;
    //uint8_t charIndex = 0;

    uint8_t bitmap_numbers[10][5][3] = {
      //0
      {
        {1,1,1},
        {1,0,1},
        {1,0,1},
        {1,0,1},
        {1,1,1},
      },
      //1
      {
        {0,1,0},
        {1,1,0},
        {0,1,0},
        {0,1,0},
        {1,1,1},
      },
      //2
      {
        {1,1,1},
        {0,0,1},
        {1,1,1},
        {1,0,0},
        {1,1,1},
      },
      //3
      {
        {1,1,1},
        {0,0,1},
        {1,1,1},
        {0,0,1},
        {1,1,1},
      },
      //4
      {
        {1,0,1},
        {1,0,1},
        {1,1,1},
        {0,0,1},
        {0,0,1},
      },
      //5
      {
        {1,1,1},
        {1,0,0},
        {1,1,1},
        {0,0,1},
        {1,1,1},
      },
      //6
      {
        {1,1,1},
        {1,0,0},
        {1,1,1},
        {1,0,1},
        {1,1,1},
      },
      //7
      {
        {1,1,1},
        {0,0,1},
        {0,0,1},
        {0,0,1},
        {0,0,1},
      },
      //8
      {
        {1,1,1},
        {1,0,1},
        {1,1,1},
        {1,0,1},
        {1,1,1},
      },
      //9
      {
        {1,1,1},
        {1,0,1},
        {1,1,1},
        {0,0,1},
        {0,0,1},
      },
    };  // end of bitmap_numbers[]

    uint8_t bitmap_symbols[1][5][3] = {
      //space
      {
        {0,0,0},
        {0,0,0},
        {0,0,0},
        {0,0,0},
        {0,0,0},
      },
    };

};

#endif
