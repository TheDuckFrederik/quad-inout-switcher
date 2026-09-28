# Prototype Pinout (Arduino Nano / ATmega328P)

This pin map matches `prototype/quad_inout_switcher/quad_inout_switcher.ino`.

## 1) Buttons (digital inputs)

1. **D2** → Input select button
2. **D3** → Output select button

### Button wiring requirements

- Configure both button pins with `INPUT_PULLUP` in the sketch.
- Wire each push button between its Arduino pin and **GND**.
- Pressed state should read as `LOW`.
- No external pull-down resistors are needed for the buttons when using `INPUT_PULLUP`.

## 2) LEDs (digital outputs)

1. **D4** → Input LED 1
2. **D5** → Input LED 2
3. **D6** → Input LED 3
4. **D7** → Input LED 4
5. **D8** → Output LED 1
6. **D9** → Output LED 2
7. **D10** → Output LED 3
8. **D11** → Output LED 4

### LED wiring requirements

- LEDs are **active-high**.
- Each LED must be wired in series with a **current-limiting resistor**.
- Typical resistor value: **220 Ω to 1 kΩ**.
- Recommended wiring order: **Nano pin → resistor → LED anode (+) → LED cathode (−) → GND**.
- The resistor may be placed on either side of the LED as long as it stays in series.
- All LED grounds must connect to the Nano **GND**.

## 3) Reserved / available pins

- **D12, D13**: reserved for future routing hardware control
- **A0-A5**: available for future expansion
- **D0 (RX), D1 (TX)**: keep free for USB serial upload/debug

## 4) Shared ground requirement

- All button grounds and all LED grounds must be connected to the same common **GND** reference as the Arduino Nano.
- If future audio or relay hardware is added, it should share the same ground reference unless a later design explicitly isolates it.
