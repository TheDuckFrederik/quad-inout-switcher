# Prototype Firmware

Sketch path: `prototype/quad_inout_switcher/quad_inout_switcher.ino`

## What the sketch does

- Keeps one active input index (1-4) and one active output index (1-4)
- Input button advances input selection
- Output button advances output selection
- Debounces button presses in firmware
- Lights exactly one input LED and one output LED at a time
- Leaves a placeholder function for future relay/analog-switch routing control

## Pin mapping used by the sketch

1. **D2**: input-cycle button (`INPUT_PULLUP`, active-low)
2. **D3**: output-cycle button (`INPUT_PULLUP`, active-low)
3. **D4-D7**: input LEDs 1-4 (active-high)
4. **D8-D11**: output LEDs 1-4 (active-high)

See also: `prototype/pinout.md`.

## Upload (Arduino Nano)

1. Connect the Nano by USB.
2. Open `prototype/quad_inout_switcher/quad_inout_switcher.ino` in Arduino IDE.
3. Set:
   - **Board**: Arduino Nano
   - **Processor**: ATmega328P
   - **Port**: the Nano serial port
4. Click **Upload**.

## Quick test

1. Power the Nano by USB after wiring buttons/LEDs as described in `prototype/pinout.md`.
2. Confirm startup state: Input LED 1 and Output LED 1 are on.
3. Press the input button (D2): input LEDs should cycle 1 → 2 → 3 → 4 → 1.
4. Press the output button (D3): output LEDs should cycle 1 → 2 → 3 → 4 → 1.
5. Verify input and output cycling are independent.
