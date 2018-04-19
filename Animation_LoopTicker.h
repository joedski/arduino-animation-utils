#ifndef __ANIMATION_TIMING__ANIMATION_LOOP_TICKER__
#define __ANIMATION_TIMING__ANIMATION_LOOP_TICKER__ yay

#include <Arduino.h>

struct Animation_LoopTicker {
  /**
   * The desired animation interval in milliseconds.
   * 17 (60fps) or 33 (30fps) are good values.
   */
  long interval;

  /**
   * The last millis value read from Arduino's millis() function.
   */
  long lastMillis;

  /**
   * Whether or not the last loop tick overran the desired interval.
   */
  int didOverrun;
  long overrun;
  long delta;
  long remainingDelay;

  Animation_LoopTicker();
  Animation_LoopTicker(long);

  void init();
  void tick();
  void delay();
};

#endif
