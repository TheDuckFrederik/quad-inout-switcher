# Prototype Hardware

## Arduino prototype components

- 1x Arduino Nano
- 8x 6.3 mm female jacks
  - 4x inputs
  - 4x outputs
- 2x Arduino PCB-mounted push buttons
  - one for cycling inputs
  - one for cycling outputs
- 8x standard LEDs
  - 4x input indicators
  - 4x output indicators
- 8x current-limiting resistors for LEDs
  - typically 220 Ω to 1 kΩ depending on brightness
- 1x breadboard
- jumper wires
- USB power via the Nano during prototype testing

## Wiring consistency notes

- Prototype control wiring (buttons + LEDs) is defined in `prototype/pinout.md`.
- Buttons are expected to use Nano internal pull-ups and switch to GND.
- LEDs are expected to be active-high with series resistors to GND.

## Notes

This prototype covers the control layer and initial layout only.

The audio routing layer will be defined later once the switching hardware is chosen.
