Arduino Animation Timing
========================

Some simple utilities I use a lot for Arduino based animations.

> NOTE: Why structs?  ... habit, I think.  And I tend to view them as basically "bags of data with funny named functions" rather than "pieces of hidden state with funny named functions".



## The Motly Crew


### LoopTicker

The Class `JoeDSki_AnimationLoopTicker` holds the logic necessary to try to tick animations at a steady rate as well as managing calculating the time delta and, if you want, delaying execution for the remainder of a given interval if you want to.

If you want to just run your animation as fast as the arduino can manage without pausing to wait out the rest of a frame, you can create an `JoeDSki_AnimationLoopTicker` without an interval and it will still happily manage the `delta` calculation for you, tracking the millis internally.

Here's the simplest example which just blasts out the animation updates as quickly as the processor will allow:

```cpp
// Initialize with no interval at all.
JoeDSki_AnimationLoopTicker ticker;

void setup() {
  ticker.init();
}

void loop() {
  // use ticker.delta to know how much to advance your animation.
  doSuperAwesomeAnimationStep(ticker.delta);

  // Then, tick the ticker forward.
  // This records how long the loop took in ticker.delta so you can
  // advance the animation forth properly next loop() call.
  ticker.tick();
}
```

Here's an example using a desired framerate.  It won't go faster than about 60 updates per second.

```cpp
// Initialize with the desired interval in milliseconds.
JoeDSki_AnimationLoopTicker ticker(17);

void setup() {
  ticker.init();
}

void loop() {
  // use ticker.delta to know how much to advance your animation.
  doSuperAwesomeAnimationStep(ticker.delta);

  // Then, tick the ticker forward.
  ticker.tick();

  // If we want, we can signal when overruns occur.
  if (ticker.didOverrun) {
    showOverrunLED();
  }

  // Use the default delay logic, which is just calling Arduino's delay() function.
  ticker.delay();
}
```


### ProgressTimingModel

The class `JoeDSki_AnimationProgressTimingModel` holds the logic for progress-based animations.  Used in conjuction with an instance of `JoeDSki_AnimationLoopTicker` to calculate the time deltas, you can do cyclic or one-shot animations that keep about the same timing regardless of how long it takes a loop iteration to actually execute.  Very useful in the face of things like NeoPixels and servos which can take a bit of time to properly drive.

Here's an example with a single NeoPixel that ramps up and down:

```cpp
#include <Adafruit_NeoPixel.h>
#include <JoeDSki_AnimationLoopTicker.h>
#include <JoeDSki_AnimationProgressTimingModel.h>
#include <stdint.h>

#define PIXEL_COUNT 6
#define NEOPIXEL_PIN 6

// Just one lonely neopixel :(
Adafruit_NeoPixel neoPixelStrip = Adafruit_NeoPixel(PIXEL_COUNT, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

// 60 ticks per second.
JoeDSki_AnimationLoopTicker ticker(17);

struct RGBColor {
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

struct PixelState {
  RGBColor color;
  JoeDSki_AnimationProgressTimingModel timing;

  RGBColor getFadedColor() {
    uint8_t fade = (
      timing.progress > (ANIMATION_PROGRESS_MAX >> 1)
        ? UINT8_MAX - (ANIMATION_PROGRESS_MAX >> 7)
        : ANIMATION_PROGRESS_MAX >> 7
    );
    return {
      .r = color.r * fade >> 8,
      .g = color.g * fade >> 8,
      .b = color.b * fade >> 8,
    };
  }
} lonelyPixel = {
  // Some sort of color...
  .color = {255, 32, 96},
  // Animation goes for 1 second.
  .timing = JoeDSki_AnimationProgressTimingModel(1000)
};

void setup() {
  ticker.init();
}

void loop() {
  // Render
  RGBColor fadedColor = lonelyPixel.getFadedColor();
  neoPixelStrip.setPixelColor(0, neoPixelStrip.Color(fadedColor.r, fadedColor.g, fadedColor.b));
  neoPixelStrip.show();
  neoPixelStrip.setPixelColor(i, 0);

  // Update
  lonelyPixel.timing.incrementCyclic(ticker.delta);

  // Timekeeping
  ticker.tick();
  ticker.delay();
}
```
