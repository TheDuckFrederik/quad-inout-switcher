# Arduino Nano Prototype Firmware Walkthrough

Sketch: `prototype/quad_inout_switcher/quad_inout_switcher.ino`

This document explains the current OLED prototype firmware and the associated button and jack wiring.

## 1) Display purpose and layout

The 128×32 display is split into left and right sections. Small labels identify the two selections, while large numbers show the selected channels:

```text
IN  1                         OUT  4
```

The input and output values occupy the same horizontal row. The input button changes only the large number beside `IN`; the output button changes only the large number beside `OUT`.

## 2) Current limits

The firmware handles:

- two buttons for selecting an input and output
- the OLED user interface
- software button debounce

It does **not** route guitar audio yet. The jack tips are labelled audio nodes for the future switching circuit. They must not be connected to Nano GPIO pins.

## 3) Wiring map

| Function | Connection | Behavior |
|---|---|---|
| Input select button | D2 to one electrical side; other side to GND | `INPUT_PULLUP`; LOW when pressed |
| Output select button | D3 to one electrical side; other side to GND | `INPUT_PULLUP`; LOW when pressed |
| OLED SDA | OLED SDA to A4 | I2C data |
| OLED SCL | OLED SCL to A5 | I2C clock |
| OLED power | VCC to approved supply, GND to Nano GND | Check module voltage rating |
| Input jack tips | J1–J4 to labelled INPUT audio nodes | Future audio switching only |
| Output jack tips | J5–J8 to labelled OUTPUT audio nodes | Future audio switching only |
| All jack sleeves | J1–J8 sleeves to AUDIO_GND | Audio cable/shield return |

## 4) Important assumptions

- `kChannelCount = 4` means four selectable inputs and four selectable outputs.
- The OLED is SSD1306-compatible, 128×32, and normally uses I2C address `0x3C`.
- The OLED reset pin is not connected; the library is configured with `-1`.
- Buttons idle at `HIGH` and go `LOW` when pressed.
- Debouncing uses a 30 ms stability window.
- Channel indexes are stored as `0..3`, but displayed as `1..4`.
- Audio jacks are passive connectors in this prototype; they are not Nano I/O devices.

## 5) Function walkthrough

### `advanceSelection(uint8_t currentIndex)`

Returns `(currentIndex + 1) % kChannelCount`, giving:

```text
0 → 1 → 2 → 3 → 0
```

### `drawSelection(const SelectionState &state)`

1. Clears the OLED buffer.
2. Selects small text for the `IN` and `OUT` labels.
3. Places `IN` at the left and `OUT` at the right.
4. Selects text size 3 for the channel numbers.
5. Places the input number beside `IN` and output number beside `OUT`.
6. Sends the completed buffer to the display.

### `updateRoutingOutputs(const SelectionState &state)`

Currently a placeholder. Later it can control relays or analog-switch ICs based on the selected input and output.

### `consumeButtonPress(...)`

Reads each button, waits for a stable 30 ms state, and returns one event when the stable state becomes LOW. This prevents one press from being counted multiple times.

## 6) Setup and loop

`setup()` configures D2/D3 as pull-up inputs, initializes the OLED, and draws the default `IN 1` / `OUT 1` screen.

`loop()` repeatedly checks both buttons. When a valid press occurs, it advances the corresponding selection and redraws the display.

## 7) Jack wiring

For each jack, identify:

- **Tip**: signal terminal
- **Sleeve**: audio-ground/shield terminal
- **Normally-closed contact**, if present: leave unconnected until the final routing design

Wire the jack sleeves to the common AUDIO_GND rail. Wire each tip to a clearly labelled, isolated audio node:

```text
J1 tip -> INPUT_1_AUDIO
J2 tip -> INPUT_2_AUDIO
J3 tip -> INPUT_3_AUDIO
J4 tip -> INPUT_4_AUDIO
J5 tip -> OUTPUT_1_AUDIO
J6 tip -> OUTPUT_2_AUDIO
J7 tip -> OUTPUT_3_AUDIO
J8 tip -> OUTPUT_4_AUDIO
```

Do not connect any of these tip nodes directly to Nano D pins, A pins, 5V, or GND.

## 8) Upload and test

1. Install Adafruit GFX and Adafruit SSD1306.
2. Wire OLED and buttons according to `prototype/pinout.md`.
3. Wire and label the eight jacks without connecting their tips to the Nano.
4. Open the sketch in Arduino IDE.
5. Select Arduino Nano, the correct ATmega328P processor/bootloader, and the correct port.
6. Upload.
7. Confirm the left/right display layout.
8. Verify the input button changes only the large input number.
9. Verify the output button changes only the large output number.

## 9) Future audio routing

When the routing hardware is selected:

- keep button and debounce logic unchanged where possible
- implement control writes in `updateRoutingOutputs`
- use `SelectionState` to select the required input/output path
- never connect guitar audio directly to Nano GPIO pins
