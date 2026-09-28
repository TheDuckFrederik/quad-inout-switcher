# Arduino Nano Prototype Firmware Walkthrough

Sketch: `prototype/quad_inout_switcher/quad_inout_switcher.ino`

This document explains the current OLED prototype firmware so it can be wired, uploaded, tested, and modified safely.

## 1) Purpose and current limits

The firmware currently handles:

- two buttons for selecting an input and an output
- a 128×32 I2C OLED for displaying the selections
- software debounce for both buttons

It does **not** route guitar audio yet. The eight 6.3 mm jacks are documented for the physical prototype, but the audio switching circuit is still undecided. `updateRoutingOutputs(...)` is the future integration point.

## 2) Display output

The display is intentionally formatted as:

```text
IN: 1
Out: 1
```

The input button changes only the number after `IN:`. The output button changes only the number after `Out:`.

## 3) Wiring map

| Function | Nano pin | Wiring detail | Behavior |
|---|---:|---|---|
| Input select button | D2 | Button between D2 and GND | `INPUT_PULLUP`; LOW when pressed |
| Output select button | D3 | Button between D3 and GND | `INPUT_PULLUP`; LOW when pressed |
| OLED SDA | A4 | OLED SDA to Nano A4 | I2C data |
| OLED SCL | A5 | OLED SCL to Nano A5 | I2C clock |
| OLED VCC | 5V or approved supply | Match the OLED module rating | Power |
| OLED GND | GND | Shared with button ground | Ground |

## 4) Important assumptions

- `kChannelCount = 4`, so there are four selectable inputs and four selectable outputs.
- The OLED is SSD1306-compatible, 128×32, and normally uses I2C address `0x3C`.
- The OLED reset pin is not connected; the library is configured with `-1`.
- Buttons are idle at `HIGH` and go `LOW` when pressed.
- Debouncing uses a 30 ms stability window.
- Channel indexes are stored internally as `0..3`, but displayed as `1..4`.

## 5) Data structures and state

`SelectionState` stores:

- `activeInput`: zero-based selected input
- `activeOutput`: zero-based selected output

The initial value is `{0, 0}`, which displays `IN: 1` and `Out: 1`.

`ButtonState` stores the last raw reading, the accepted stable reading, and the time the raw reading last changed. Each button has its own state object.

## 6) Function walkthrough

### `advanceSelection(uint8_t currentIndex)`

Returns `(currentIndex + 1) % kChannelCount`. This gives wraparound behavior:

```text
0 → 1 → 2 → 3 → 0
```

### `drawSelection(const SelectionState &state)`

1. Clears the display buffer.
2. Sets text size to 2 and text color to white.
3. Writes `IN: ` on the first line, followed by the selected input number.
4. Writes `Out: ` on the second line, followed by the selected output number.
5. Calls `display.display()` to send the buffer to the OLED.

### `updateRoutingOutputs(const SelectionState &state)`

This is currently a placeholder. Later it can set relay or analog-switch control pins based on `activeInput` and `activeOutput`.

### `applySelection(const SelectionState &state)`

Calls the display update and future routing update together so the user interface and routing state remain synchronized.

### `consumeButtonPress(...)`

The debounce process is:

1. Read the button pin.
2. Detect whether the raw reading changed.
3. Start a new timer when it changes.
4. Wait until the reading remains unchanged for 30 ms.
5. Accept the new stable state.
6. Return `true` only when the accepted state is `LOW`.

This produces one selection change per button press rather than many changes caused by switch bounce.

## 7) `setup()`

- Configures D2 and D3 as `INPUT_PULLUP`.
- Initializes the OLED at address `0x3C`.
- Stops in an infinite loop if the OLED initialization fails.
- Clears the OLED and draws the default `IN: 1` / `Out: 1` state.

## 8) `loop()`

Every loop iteration:

1. Reads the current time using `millis()`.
2. Checks the input button.
3. Checks the output button.
4. Applies the new selection only if one of the buttons generated a valid press.

The two selections are independent.

## 9) Upload and bench test

1. Install **Adafruit GFX Library** and **Adafruit SSD1306**.
2. Wire the OLED and buttons according to `prototype/pinout.md`.
3. Open the sketch in Arduino IDE.
4. Select Arduino Nano, the correct ATmega328P processor/bootloader, and the correct port.
5. Upload.
6. Confirm `IN: 1` and `Out: 1`.
7. Press each button and confirm its corresponding value cycles 1 → 2 → 3 → 4 → 1.

## 10) Troubleshooting

- **Blank OLED:** check OLED voltage, GND, SDA/A4, SCL/A5, library installation, and I2C address. Try `0x3D` if needed.
- **Button always active:** use opposite electrical sides of the four-prong button; do not use two pins from the same side.
- **Button does nothing:** connect one button side to D2 or D3 and the opposite side to GND.
- **Random extra presses:** verify the button wiring, common ground, and stable breadboard connections.
- **Upload failure:** use a data USB cable and try the old bootloader option for some Nano clones.

## 11) Future audio routing

When the routing hardware is selected:

- keep the button and debounce logic unchanged where possible
- implement control writes in `updateRoutingOutputs`
- use the existing `SelectionState` values to select the required input/output path
- never connect guitar audio directly to Nano GPIO pins
