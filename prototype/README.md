# Quad In/Out Switcher (Prototype)

Arduino Nano-controlled 4-input / 4-output guitar switcher prototype.

## What this prototype currently covers

- Controller behavior (button handling + channel selection)
- LED indication for selected input and selected output
- Breadboard validation of Nano pin mapping

> Audio routing hardware is **not finalized** yet. The current sketch does not switch guitar audio paths.

## Prototype parts

- 1x Arduino Nano
- 8x 6.3mm female jacks (4 inputs, 4 outputs)
- 2x PCB-mounted push buttons (input cycle, output cycle)
- 8x LEDs (4 input indicators, 4 output indicators)
- 8x LED resistors (typically 220 Ω to 1 kΩ)
- 1x breadboard
- jumper wires
- USB power for prototype testing

## Documentation

- Hardware parts/build notes: `prototype/hardware.md`
- Nano pin mapping + wiring assumptions: `prototype/pinout.md`
- Firmware summary + upload/test quick guide: `prototype/firmware.md`
- Full beginner walkthrough of the sketch: `prototype/code-walkthrough.md`

## Quick test flow

1. Wire the Nano/buttons/LEDs per `prototype/pinout.md`.
2. Upload `prototype/quad_inout_switcher/quad_inout_switcher.ino` using `prototype/firmware.md`.
3. Power by USB.
4. Verify startup: Input LED 1 and Output LED 1 are on.
5. Press each button and verify its LED group cycles 1 → 4 and wraps back to 1.
