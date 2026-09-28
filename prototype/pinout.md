# Prototype Pinout and Full Wiring

This pinout matches `prototype/quad_inout_switcher/quad_inout_switcher.ino`.

## Arduino Nano pin table

| Nano pin | Connect to | Notes |
|---|---|---|
| D2 | Input-cycle button signal | Uses internal pull-up; pressed state is `LOW`. |
| D3 | Output-cycle button signal | Uses internal pull-up; pressed state is `LOW`. |
| A4 | OLED SDA | I2C data. |
| A5 | OLED SCL | I2C clock. |
| 5V or approved OLED supply | OLED VCC | Only use 5 V if the OLED breakout accepts 5 V. |
| GND | OLED GND and both button grounds | All control grounds share Nano GND. |
| D0/D1 | Leave free | USB serial/programming pins. |
| D4–D13 | Currently unused | Reserved for future relay or analog-switch control. |
| A0–A3 | Currently unused | Available for future expansion. |

## OLED display wiring

For a four-pin I2C OLED:

```text
OLED VCC  ───────── Nano 5V*
OLED GND  ───────── Nano GND
OLED SDA  ───────── Nano A4 / SDA
OLED SCL  ───────── Nano A5 / SCL

* Use Nano 5V only when the OLED module is rated for 5V.
  Use a suitable regulated 3.3V supply for a 3.3V-only module.
```

The sketch assumes:

- SSD1306-compatible controller
- 128×32 pixel display
- I2C address `0x3C`
- hardware reset pin not connected; the library uses `-1`

If the display stays blank, check whether its address is `0x3D` instead and change `kOledAddress` in the sketch.

The display layout is:

```text
IN: 1
Out: 1
```

## Four-prong button wiring

A typical four-prong tactile button has two internally connected pins on one side and two internally connected pins on the other side. Pressing the button connects the two sides together.

Use one pin from each side of each button:

```text
Input button:
Nano D2 ───── one electrical side of button
Nano GND ──── opposite electrical side of button

Output button:
Nano D3 ───── one electrical side of button
Nano GND ──── opposite electrical side of button
```

The sketch uses `INPUT_PULLUP`, so no external resistor is needed for either button. The unpressed reading is `HIGH`; pressing the button connects the input to GND and produces `LOW`.

### Identifying the correct button pins

Before wiring, use a multimeter in continuity mode:

1. With the button released, find the two pins that are already connected. Those are one electrical side.
2. Find the other pair that is already connected. That is the opposite side.
3. Connect D2 or D3 to one side and GND to the other side.
4. Do not connect both wires to pins from the same side, because that would leave the button permanently shorted.

## 6.3 mm jack placement and status

The eight jacks do not connect to Nano GPIO pins in this firmware-only prototype.

Label them:

```text
Top/input row:     INPUT 1   INPUT 2   INPUT 3   INPUT 4
Bottom/output row: OUTPUT 1  OUTPUT 2  OUTPUT 3  OUTPUT 4
```

For each jack, identify its **tip**, **sleeve**, and any **normally-closed switch contact** if present. The sleeve is normally audio ground, but the complete audio grounding and switching arrangement must be designed together with the future relay or analog-switch circuit. Do not connect guitar signal wires to Nano pins.

## Complete prototype wiring diagram

```text
                                  +----------------------+
                                  |      Arduino Nano    |
                                  |                      |
Input button, side A ------------>| D2                   |
Input button, side B ------------>| GND                 |
                                  |                      |
Output button, side A ----------->| D3                   |
Output button, side B ----------->| GND                 |
                                  |                      |
OLED SDA ------------------------>| A4 / SDA             |
OLED SCL ------------------------>| A5 / SCL             |
OLED VCC <------------------------| 5V*                  |
OLED GND <----------------------->| GND                  |
                                  +----------------------+

* Only if the OLED breakout is 5V-compatible.

OLED display:
  +----------------+
  | IN: 1          |
  | Out: 1         |
  +----------------+

6.3 mm jacks:
  INPUT 1, INPUT 2, INPUT 3, INPUT 4       -> reserved audio wiring
  OUTPUT 1, OUTPUT 2, OUTPUT 3, OUTPUT 4   -> reserved audio wiring
  Do not connect audio tips directly to Nano pins.
```

## Grounding

The OLED ground and both button ground connections must return to Nano GND. Use a breadboard ground rail connected to one Nano GND pin. Keep the future audio-ground design separate until the routing circuit is finalized.
