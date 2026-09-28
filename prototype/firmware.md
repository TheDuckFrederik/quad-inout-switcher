# Prototype Firmware

Sketch path: `prototype/quad_inout_switcher/quad_inout_switcher.ino`

## Scope of current firmware

Implemented now:

- input button on D2 cycles selected input
- output button on D3 cycles selected output
- software debounce (30 ms)
- 4 input LEDs + 4 output LEDs indicate active channels

Not implemented yet:

- audio routing/switching hardware control (relay/analog-switch stage)

The sketch includes `updateRoutingOutputs(...)` as the future integration point for that stage.

## Pin mapping used by the sketch

- **D2**: input-cycle button (`INPUT_PULLUP`, active-low)
- **D3**: output-cycle button (`INPUT_PULLUP`, active-low)
- **D4-D7**: input LEDs 1-4 (active-high)
- **D8-D11**: output LEDs 1-4 (active-high)

See also: `prototype/pinout.md`.

## Wiring assumptions

- Buttons are wired from pin to **GND** (pressed = `LOW`).
- LEDs are wired with one resistor each in series to **GND**.
- `HIGH` turns an LED on, `LOW` turns it off.
- All grounds are shared with Nano GND.

## Startup/default state

On power-up after `setup()`:

- selected input index = 0 (channel 1)
- selected output index = 0 (channel 1)
- Input LED 1 and Output LED 1 are on

## Upload with Arduino IDE

1. Connect the Nano by USB.
2. Open `prototype/quad_inout_switcher/quad_inout_switcher.ino`.
3. Set:
   - **Board**: Arduino Nano
   - **Processor**: ATmega328P
   - **Port**: your Nano serial port
4. Click **Upload**.
5. If upload fails on a clone Nano, try the alternative bootloader processor option.

## Test procedure

1. Wire according to `prototype/pinout.md`.
2. Upload the sketch.
3. Confirm startup LEDs: input 1 + output 1.
4. Press input button repeatedly: input LEDs should cycle `1 -> 2 -> 3 -> 4 -> 1`.
5. Press output button repeatedly: output LEDs should cycle `1 -> 2 -> 3 -> 4 -> 1`.
6. Confirm input and output groups move independently.
7. Confirm stable behavior (no random jumps) while buttons are idle.

## Troubleshooting

- **Upload error / no port**: check USB cable type (data cable), board/port selection, and bootloader setting.
- **Button not detected**: verify button is between pin and GND, not pin and +5V.
- **LED always off**: check LED polarity and resistor connection.
- **Wrong LED order**: verify D4..D7 are inputs and D8..D11 are outputs.

For detailed line-by-line logic, use `prototype/code-walkthrough.md`.
