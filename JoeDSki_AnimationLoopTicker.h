#ifndef __JOEDSKI__ANIMATION_LOOP_TICKER__
#define __JOEDSKI__ANIMATION_LOOP_TICKER__ yay

#include <Arduino.h>

struct JoeDSki_AnimationLoopTicker {
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
   * Construct a LoopTicker with a given interval to aim for.
   * If called with no interval, a default of 0 will be used, meaning
   * the ticker operates in free-wheeling mode and will never delay the animation.
   * @param long The fixed interval to aim for.
   */
  JoeDSki_AnimationLoopTicker(long);


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
