# Prototype Firmware

Sketch: `prototype/quad_inout_switcher/quad_inout_switcher.ino`

## What the sketch does

- Starts with Input 1 and Output 1 selected.
- Reads two buttons with the Nano's internal pull-up resistors.
- Debounces button presses in software.
- Cycles input selection from 1 to 4 and wraps to 1.
- Cycles output selection from 1 to 4 and wraps to 1.
- Displays the current selection on a 128×32 I2C OLED.

The OLED screen shows:

```text
INPUT 1
OUTPUT 1
```

## What the sketch does not do yet

- It does not switch guitar audio.
- It does not control relays or analog audio-switch ICs.
- The eight jacks are not electrically routed by the Nano.

The `updateRoutingOutputs(...)` function is retained as the future integration point for relay or analog-switch control.

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
2. Confirm the OLED initializes and displays Input 1 / Output 1.
3. Press the input button once. The display should show Input 2.
4. Continue pressing to verify 3, 4, then 1.
5. Repeat with the output button.
6. Verify that changing one selection does not change the other.

## Troubleshooting

- **Blank OLED:** verify VCC voltage, GND, SDA/A4, SCL/A5, library installation, and I2C address. Try changing `0x3C` to `0x3D`.
- **Upload fails:** use a data-capable USB cable; check board, processor, and port; try the old bootloader option on Nano clones.
- **Button always active:** make sure the wires use opposite electrical sides of the four-prong button, not two pins from the same side.
- **Button does nothing:** verify one button side is connected to D2 or D3 and the opposite side is connected to GND.
- **Display resets or flickers:** check the breadboard power rails and ground connections; keep jumper wires short.
