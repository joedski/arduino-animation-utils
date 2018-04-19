#include "Animation_LoopTicker.h"

Animation_LoopTicker::Animation_LoopTicker() {
  // If you don't supply an interval, we just use 0.
  // This means we always overrun and never delay even if you call delay(),
  // but is useful if you don't care about maintaining a steady framerate.
  interval = 0;
}

Animation_LoopTicker::Animation_LoopTicker(long interval)
  // Not really much to do once we've assigned this value.
  : interval(interval)
{}

void Animation_LoopTicker::init() {
  lastMillis = millis();
}

void Animation_LoopTicker::tick() {
  long nextMillis = millis();
  long actualLoopDuration = nextMillis - lastMillis;
  remainingDelay = interval - actualLoopDuration;
  didOverrun = remainingDelay < 0;
  delta = interval + (didOverrun ? -remainingDelay : 0);
}

void Animation_LoopTicker::delay() {
  if (didOverrun) {
    return;
  }

  ::delay(remainingDelay);
}
