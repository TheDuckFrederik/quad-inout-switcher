# Quad In/Out Switcher (Prototype)

Arduino Nano-controlled 4-input / 4-output guitar pedal switching prototype.

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
- Firmware behavior + upload/test steps: `prototype/firmware.md`

## Prototype behavior

- Exactly one input is selected at a time
- Exactly one output is selected at a time
- Input button cycles input selection
- Output button cycles output selection
- One input LED and one output LED indicate the active selections

## Quick test flow

1. Wire the Nano/buttons/LEDs per `prototype/pinout.md`.
2. Upload `prototype/quad_inout_switcher/quad_inout_switcher.ino` using `prototype/firmware.md`.
3. Power by USB.
4. Press each button and verify the corresponding LED group cycles 1 → 4 and wraps.
