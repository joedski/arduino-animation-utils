Arduino Animation Timing
========================

Some simple utilities I use a lot for Arduino based animations.

> NOTE: I write things as structs because I tend to write public-by-default and because I haven't outgrown my C-ish habits.  I also think that most things are usable by just looking at them.  If you change them and weird things happen, well, you've no one to blame but yourself.



## The Motly Crew


### LoopTicker

The Class `Animation_LoopTicker` holds the logic necessary to try to tick animations at a steady rate as well as managing calculating the time delta and, if you want, delaying execution for the remainder of a given interval if you want to.

If you want to just run your animation as fast as the arduino can manage without pausing to wait out the rest of a frame, you can create an `Animation_LoopTicker` without an interval and it will still happily manage the `delta` calculation for you, tracking the millis internally.


### ProgressTimingModel

The class `Animation_ProgressTimingModel` holds the logic for timing progress-based animations.
