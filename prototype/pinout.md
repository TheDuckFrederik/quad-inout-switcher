# Prototype Pinout (Arduino Nano / ATmega328P)

This pin map matches `prototype/quad_inout_switcher/quad_inout_switcher.ino`.

## 1) Buttons (digital inputs)

1. **D2** → Input select button
2. **D3** → Output select button

## 2) LEDs (digital outputs)

1. **D4** → Input LED 1
2. **D5** → Input LED 2
3. **D6** → Input LED 3
4. **D7** → Input LED 4
5. **D8** → Output LED 1
6. **D9** → Output LED 2
7. **D10** → Output LED 3
8. **D11** → Output LED 4

## 3) Reserved / available pins

- **D12, D13**: reserved for future routing hardware control
- **A0-A5**: available for future expansion
- **D0 (RX), D1 (TX)**: keep free for USB serial upload/debug

## 4) Wiring assumptions

1. Buttons use `INPUT_PULLUP`.
2. Each button is wired between its pin and **GND** (pressed = `LOW`).
3. LEDs are **active-high** (`HIGH` turns LED on).
4. Each LED uses a current-limited series path from Nano pin to **GND** (for example: pin -> LED anode -> LED cathode -> resistor -> GND), with resistor value typically **220 Ω to 1 kΩ**.
5. All button and LED grounds are common with Nano **GND**.
