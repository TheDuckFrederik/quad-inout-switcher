# Quad In/Out Switcher

Arduino Nano-controlled 4-input / 4-output guitar pedal switching box.

## Concept

- 4x 6.3mm input jacks
- 4x 6.3mm output jacks
- 2x footswitches
  - top-right: cycle active input
  - bottom-left: cycle active output
- LED indicator for each input and output
- Initial power via Arduino Nano USB-C
- Later version to be converted to standard 9V DC pedal power

## Intended behavior

- Exactly one input is active at a time
- Exactly one output is active at a time
- Footswitches cycle through their respective channels
- LEDs show which input/output is currently selected

## Notes

This repo will hold:

- Arduino firmware
- wiring / pin map notes
- enclosure layout ideas
- later analog power conversion notes
