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
   * This can be used to light up a status LED or something if you like.
   */
  int didOverrun;

  /**
   * How much the animation loop iteration overran the interval.
   */
  long overrun;

  /**
   * Milliseconds since the last tick.
   * Use this to step animations forward in a time-agnostic manner.
   */
  long delta;

  /**
   * Milliseconds remaining to delay for when using a non-0 interval.
   */
  long remainingDelay;


  /**
   * Construct a LoopTicker with 0 interval, i.e. in free-wheeling mode.
   */
  Animation_LoopTicker();

  /**
   * Construct a LoopTicker with a given interval to aim for.
   * @param long The fixed interval to aim for.
   */
  Animation_LoopTicker(long);


  /**
   * Initializes the LoopTicker, setting the first delta and getting millis
   * before the first loop iteration.
   */
  void init();

  /**
   * Tick the timer forward at the end of a loop iteration,
   * setting things like delta for next time, and taking into account possible overrun.
   */
  void tick();

  /**
   * Calls the Arduino delay() function with the remainingDelay
   * unless didOverrun is 1.
   */
  void delay();
};

#endif
