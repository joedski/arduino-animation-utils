#ifndef __ANIMATION__ANIMATION_TIMING_MODEL__
#define __ANIMATION__ANIMATION_TIMING_MODEL__ yay

#include <stdint.h>


// Represents the linear progress of an animation.
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

  // Increments the timing model by some time delta, according to its rate.
  void increment(uint32_t);

  // Same as increment, but rather than stopping at ANIMATION_PROGRESS_MAX or 0,
  // the animation will instead under/overflow to the other end.
  // i.e. if progress == ANIMATION_PROGRESS_MAX - 1,
  //   then progress += 2 will result in progress == 2.
  // The same if progress ends up below 0.
  void incrementCyclic(uint32_t);


  // ======== Derivers

  // Convenience method returning the progress as an unsigned 8-bit,
  // usually for LUTs and such.
  uint8_t progress8() {
    return progress / 256;
  }
};


#endif
