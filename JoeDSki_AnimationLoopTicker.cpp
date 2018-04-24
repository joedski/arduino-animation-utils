#include "JoeDSki_AnimationLoopTicker.h"

JoeDSki_AnimationLoopTicker::JoeDSki_AnimationLoopTicker(long interval = 0)
  // Not really much to do once we've assigned this value, hence no body.
  // If you don't supply an interval, we just use 0.
  // This means we always overrun and never delay even if you call delay(),
  // but is useful if you don't care about maintaining a steady framerate.
  : interval(interval)
{}

void JoeDSki_AnimationLoopTicker::init() {
  // Set the initial value for lastMillis so we can track the true delta later.
  lastMillis = millis();

  // Since we won't have actually completed a loop, we just assume the delta was the interval.
  // IF we're running free-wheeling, then delta will start out 0 the first time around,
  // so keep that in mind.
  delta = interval;
}

void JoeDSki_AnimationLoopTicker::tick() {
  long nextMillis = millis();
  long actualLoopDuration = nextMillis - lastMillis;
  remainingDelay = interval - actualLoopDuration;
  didOverrun = remainingDelay < 0;
  delta = interval + (didOverrun ? -remainingDelay : 0);
}

void JoeDSki_AnimationLoopTicker::delay() {
  if (didOverrun) {
    return;
  }

  ::delay(remainingDelay);
}
