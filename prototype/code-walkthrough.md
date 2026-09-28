# Arduino Nano Prototype Firmware Walkthrough

Sketch: `/home/runner/work/quad-inout-switcher/quad-inout-switcher/prototype/quad_inout_switcher/quad_inout_switcher.ino`

This document explains the current prototype firmware exactly as implemented so you can wire, upload, test, and safely modify it later.

## 1) Purpose and current prototype limits

The prototype firmware currently handles only:

- two buttons (cycle selected input / cycle selected output)
- eight LEDs (show selected input and selected output)

It does **not** route guitar audio yet. The sketch includes a placeholder (`updateRoutingOutputs`) where future relay or analog-switch routing logic can be added.

## 2) Wiring map (Arduino Nano)

| Function | Nano pin | Wiring detail | Behavior |
|---|---:|---|---|
| Input select button | D2 | Button between D2 and GND | Uses `INPUT_PULLUP` (`LOW` when pressed) |
| Output select button | D3 | Button between D3 and GND | Uses `INPUT_PULLUP` (`LOW` when pressed) |
| Input LED 1..4 | D4, D5, D6, D7 | Pin -> LED anode -> LED cathode -> resistor -> GND | Active-high (`HIGH` = ON) |
| Output LED 1..4 | D8, D9, D10, D11 | Pin -> LED anode -> LED cathode -> resistor -> GND | Active-high (`HIGH` = ON) |

Use one resistor per LED (typically 220 Ω to 1 kΩ). All grounds must be common with Nano GND.

## 3) Important assumptions in code

- `kChannelCount = 4` means there are always 4 selectable inputs and 4 selectable outputs.
- The two button pins are expected to idle at `HIGH` and go `LOW` when pressed.
- Debounce window is `kDebounceMs = 30` ms.
- Internally, selected channels are zero-based indexes (`0..3`), shown physically as channel numbers 1..4.

## 4) Data structures and state

The sketch defines:

- `SelectionState { activeInput, activeOutput }`
  - stores which input index and output index are selected
- `ButtonState { lastReading, stableReading, lastChangeMs }`
  - tracks debounced state per button

Current startup defaults:

- `selection = {0, 0}`
- so Input LED 1 and Output LED 1 are on after setup completes

## 5) Function-by-function walkthrough

### `advanceSelection(uint8_t currentIndex)`

- Returns `(currentIndex + 1) % kChannelCount`
- This creates wraparound behavior: `0 -> 1 -> 2 -> 3 -> 0`

### `updateIndicatorLeds(const SelectionState &state)`

- Loops from index `0` to `3`
- Turns on exactly one input LED (matching `activeInput`)
- Turns on exactly one output LED (matching `activeOutput`)
- All non-selected LEDs are turned off

### `updateRoutingOutputs(const SelectionState &state)`

- Currently placeholder only (`(void)state;`)
- Extension point for future relay/analog switch control
- Safe place to add routing logic without changing button/debounce flow

### `applySelection(const SelectionState &state)`

- Single call point that updates indicators and routing outputs
- Keeps output updates grouped and consistent

### `consumeButtonPress(ButtonState &buttonState, uint8_t pin, unsigned long nowMs)`

Debounce and press detection logic:

1. Read current pin level.
2. If reading changed from last sample, save new reading and timestamp.
3. If reading stays unchanged for at least 30 ms and differs from stable reading, accept it as new stable state.
4. Return `true` only when new stable state is `LOW` (button press event).

Result: one event per physical press (when the button settles to pressed state).

## 6) What `setup()` does

- Sets button pins D2/D3 to `INPUT_PULLUP`
- Sets all LED pins D4..D11 as `OUTPUT`
- Initializes all LEDs to `LOW`
- Calls `applySelection(selection)` so defaults are shown immediately

## 7) What `loop()` does

Every iteration:

1. Read current time with `millis()`.
2. Check input button with debounce helper:
   - on valid press, advance input selection.
3. Check output button with debounce helper:
   - on valid press, advance output selection.
4. If either changed, call `applySelection(selection)`.

Input and output selection are independent and can be changed in any order.

## 8) Upload steps (Arduino IDE)

1. Connect Nano via USB.
2. Open `prototype/quad_inout_switcher/quad_inout_switcher.ino`.
3. In Arduino IDE select:
   - **Board**: Arduino Nano
   - **Processor**: ATmega328P
   - **Port**: your Nano COM/tty port
4. Click **Upload**.
5. If upload fails, try the alternative bootloader processor option for your Nano clone.

## 9) Step-by-step bench test

1. Power with USB after wiring buttons and LEDs.
2. Confirm startup: Input LED 1 ON, Output LED 1 ON.
3. Press input button repeatedly:
   - LEDs should move 1 -> 2 -> 3 -> 4 -> 1.
4. Press output button repeatedly:
   - LEDs should move 1 -> 2 -> 3 -> 4 -> 1.
5. Hold a button down:
   - should not free-run through channels (only press events are counted).
6. Press both buttons at different times:
   - input and output groups should behave independently.

## 10) Common mistakes and troubleshooting

- **No LED turns on at startup**
  - Check USB power and ground continuity.
  - Verify LED polarity (anode to pin side, cathode toward resistor/GND).
- **Wrong LED lights**
  - Re-check D4..D7 as input LEDs and D8..D11 as output LEDs.
- **Button works backwards / always triggered**
  - Button must short pin to GND when pressed.
  - Do not wire button to +5V when using `INPUT_PULLUP`.
- **Random extra presses**
  - Ensure solid breadboard connections and shared ground.
  - Keep button wires short and stable.

## 11) Safe extension points for future audio routing

When adding real audio switching hardware later:

- keep button/debounce logic unchanged if possible
- implement routing pin writes in `updateRoutingOutputs`
- leave `SelectionState`, wraparound, and LED updates as-is for predictable UI behavior

This keeps the current control behavior stable while adding the routing layer in one clear location.
