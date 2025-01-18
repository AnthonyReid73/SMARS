# SMARS Robot - Follow Me Code (L293D / Fundumoto Shield Support)

This project extends [Kevin McAleer’s _Follow Me_ code](https://github.com/kevinmcaleer/follow_me2) to work with a cheap L293D-based motor shield (often referred to as a Fundumoto shield) that you might find on AliExpress. By using the Adafruit Motor Shield (AF) library, we can overcome several compatibility issues.

## Overview

- **Original Issue**: The L293D shield from AliExpress did not fully support Kevin’s original code due to missing headers and partial compatibility.
- **Solution**: I added headers to the shield and adapted the code to use the Adafruit Motor Shield (AF) library with a conditional compile for the buzzer.
- **Improvements**:
  - We use `#ifdef FUNDUMOTO_SHIELD` to define a real `beep()` function if the buzzer is present, and a no-op version if not.
  - Distance is now locally scoped within `loop()`, improving clarity.
  - We use `else if` for mutually exclusive conditions (forward, backward, etc.).
  - The beep duration is derived from the distance. If the distance is 0 or negative, we force it to 1 to avoid division by zero or very long beeps.
  - `ping()` has been renamed to `measureDistance()` for clarity.

## Hardware

- **Motor Shield**: [L293D Shield from AliExpress](https://www.aliexpress.com/item/1005007112191522.html). (Pictures will be uploaded soon.)
- **Ultrasonic Sensor**: HC-SR04 (with `TRIGGER_PIN` on A2 and `ECHO_PIN` on A3 by default).
- **Buzzer** (Optional): Required only if you want audible feedback. If your board supports it, define `FUNDUMOTO_SHIELD` and wire it to pin **4**.


