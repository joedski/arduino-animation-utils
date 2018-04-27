#ifndef __ANIMATION__ANIMATION_TIMING_MODEL__
#define __ANIMATION__ANIMATION_TIMING_MODEL__ yay

#include <stdint.h>


// Represents the linear progress of an animation.
/**
 * AnimationProgressTimingModel represents the linear progress of
 * a one-shot or cyclic animation with a given duration.
 *
 * It can be used for things like pulsing animations, a global timeline,
 * etc.
 *
 * NOTE: It should not be used for purely procedural animations of no fixed duration.
 */
struct JoeDSki_AnimationProgressTimingModel {
  /**
   * The normal duration of this animation in milliseconds.
   */
  uint32_t normalDuration;

  /**
   * The animation rate as an integer percentage, where 100 means 1x rate.
   * This number can be negative to run the animation backwards.
   *
   * - for 1x (forward), rate100 = 100;
   * - for -1x (backward), rate100 = -100;
   * - for stopped, rate100 = 0;
   */
  int16_t rate100;

  /**
   * Current progress of this animation.
   * Varies between 0 and UINT16_MAX in normal use.
   */
  uint16_t progress;


  /**
   * Construct a new timing model.
   * @param uint32_t normalDuration Duration in milliseconds; required.
   * @param int16_t  rate100 Animation rate, defaulting to 100.
   * @param uint16_t progress How far along the animation is, defaulting to 0.
   */
  JoeDSki_AnimationProgressTimingModel(uint32_t, int16_t, uint16_t);


  // ======== Mutations

  /**
   * Increments the timing model progress, according to its rate,
   * by some amount of milliseconds.
   * If the progress would increment past the end, it would instead stop at
   * the maximum value of UINT16_MAX, and if progress would decrement past the beginning,
   * it would instead stop at 0.
   * @param uint32_t delta How many milliseconds to advance the animation by.
   */
  void increment(uint32_t);

  /**
   * Like the increment method, increments the timing model progress,
   * according to its rate, by some amount of milliseconds,
   * with the added behavior of cycling progress around at either end.
   * Thus, if progress would increment past the end, it cycles back to the beginning,
   * and if progress would decrement past the beginning, it cycles back
   * to the end.
   * @param uint32_t delta How many milliseconds to advance the animation by.
   */
  void incrementCyclic(uint32_t);


  // ======== Derivers

  /**
   * Convenience method for getting the progress as uint8_t/uchar
   * because sometimes you just need that.
   * @return Progress as an unsigned 8-bit number.
   */
  uint8_t progress8() {
    return progress >> 8;
  }
};


#endif
