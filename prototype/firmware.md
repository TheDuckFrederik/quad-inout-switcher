# Prototype Firmware

Sketch: `prototype/quad_inout_switcher/quad_inout_switcher.ino`

## Display layout

The 128×32 OLED uses one horizontal row. The labels are small and the channel numbers are large:

```text
IN  1                         OUT  4
```

- `IN` is on the left half.
- `OUT` is on the right half.
- The input and output numbers are drawn beside their labels using the largest practical text size for a 32-pixel-high display.

## What the sketch does

- Starts with Input 1 and Output 1 selected.
- Reads two buttons with the Nano's internal pull-up resistors.
- Debounces button presses in software for 30 ms.
- Cycles input selection from 1 to 4 and wraps to 1.
- Cycles output selection from 1 to 4 and wraps to 1.
- Redraws the OLED only when a selection changes.

## What the sketch does not do yet

- It does not switch guitar audio.
- It does not control relays or analog audio-switch ICs.
- The eight jack tip signals are not routed by the Nano.

The `updateRoutingOutputs(...)` function is retained as the future integration point for relay or analog-switch control.

## Pin mapping

- **D2**: input-cycle button (`INPUT_PULLUP`, active-low)
- **D3**: output-cycle button (`INPUT_PULLUP`, active-low)
- **A4**: OLED SDA
- **A5**: OLED SCL
- **5V/GND**: OLED power, according to the OLED module's voltage rating
- **J1–J4**: input jack tips and sleeves, audio nodes only
- **J5–J8**: output jack tips and sleeves, audio nodes only

See `prototype/pinout.md` for the complete wiring diagram.

## Required Arduino IDE libraries

Install from Library Manager:

1. **Adafruit GFX Library**
2. **Adafruit SSD1306**

## Upload instructions

1. Connect the Nano using a USB data cable.
2. Install the required libraries.
3. Open `prototype/quad_inout_switcher/quad_inout_switcher.ino`.
4. Select **Tools → Board → Arduino Nano**.
5. Select **Tools → Processor → ATmega328P**. For some clones, try **ATmega328P (Old Bootloader)**.
6. Select the Nano's serial port.
7. Click **Upload**.

## Test instructions

1. Power the Nano from USB.
2. Confirm the OLED shows the left/right layout with `IN 1` and `OUT 1`.
3. Press the input button once. The large input number should change to 2; the output number must not change.
4. Continue pressing to verify input values 3, 4, then 1.
5. Repeat with the output button and verify only the large output number changes.
6. Confirm that no jack tip is connected to a Nano GPIO pin.
7. Confirm each jack sleeve is connected to the labelled audio-ground rail.

## Troubleshooting

- **Blank OLED:** verify VCC voltage, GND, SDA/A4, SCL/A5, library installation, and I2C address. Try changing `0x3C` to `0x3D`.
- **Button always active:** make sure the wires use opposite electrical sides of the four-prong button, not two pins from the same side.
- **Button does nothing:** verify one button side is connected to D2 or D3 and the opposite side is connected to GND.
- **Unexpected audio behavior:** the current firmware does not route audio. Check that jack tips are not connected to Nano pins and that the future routing stage has not been added yet.
- **Display resets or flickers:** check the breadboard power rails and ground connections; keep jumper wires short.
