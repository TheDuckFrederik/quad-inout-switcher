# Quad In/Out Switcher — Arduino OLED Prototype

This prototype uses an Arduino Nano to select one of four inputs and one of four outputs. The selected values are shown on a 128×32 I2C OLED display.

## Current prototype scope

- Two push buttons cycle the selected input and output.
- The OLED displays the current selection.
- Eight 6.3 mm jacks are reserved for the four inputs and four outputs.
- Audio routing is **not implemented yet**. The Nano does not carry guitar audio.

## Components

- 1× Arduino Nano, ATmega328P
- 1× 128×32 I2C OLED display, normally SSD1306-compatible
- 2× four-prong PCB tactile push buttons
- 8× 6.3 mm female jacks
  - 4× input jacks
  - 4× output jacks
- 1× breadboard
- Jumper wires
- USB data cable for Nano power/programming
- Optional: 100 nF capacitor near the OLED power pins for supply-noise reduction

No LED resistors are required because the eight LEDs were removed from this prototype.

## Pin summary

| Arduino Nano pin | Function |
|---|---|
| D2 | Input-cycle button |
| D3 | Output-cycle button |
| A4 | OLED SDA |
| A5 | OLED SCL |
| 5V or module-approved supply | OLED VCC |
| GND | OLED ground and button ground |

## Software requirements

Install these libraries in Arduino IDE → Library Manager:

- Adafruit GFX Library
- Adafruit SSD1306

The sketch is located at:

`prototype/quad_inout_switcher/quad_inout_switcher.ino`

## Quick test

1. Install the two Adafruit libraries.
2. Wire the buttons and OLED using `prototype/pinout.md`.
3. Open the sketch in Arduino IDE.
4. Select **Arduino Nano**, **ATmega328P**, and the correct serial port.
5. Upload the sketch.
6. The display should show `INPUT 1` and `OUTPUT 1`.
7. Press the input button to cycle 1 → 2 → 3 → 4 → 1.
8. Press the output button to cycle 1 → 2 → 3 → 4 → 1.

The jack wiring and audio-switching circuit will be defined after the routing hardware is selected.
