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
| GND | OLED GND and both button grounds | Logic/control ground. |
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

* Use Nano 5V only when the OLED breakout is rated for 5V.
  Use a suitable regulated 3.3V supply for a 3.3V-only module.
```

The sketch assumes an SSD1306-compatible 128×32 display at I2C address `0x3C`. If the screen is blank, try `0x3D` in the sketch.

The display layout is one horizontal row:

```text
IN  1                         OUT  4
```

`IN` and `OUT` are small labels. The channel numbers are large and appear beside their labels, with input on the left half and output on the right half.

## Four-prong button wiring

A typical four-prong tactile button has two internally connected pins on one side and two internally connected pins on the other side. Pressing the button connects the two sides together.

```text
Input button:
Nano D2 ───── one electrical side of button
Nano GND ──── opposite electrical side of button

Output button:
Nano D3 ───── one electrical side of button
Nano GND ──── opposite electrical side of button
```

The sketch uses `INPUT_PULLUP`, so no external button resistor is needed. The unpressed state is `HIGH`; pressing connects the input to GND and reads `LOW`.

Use a multimeter in continuity mode to identify the two opposite electrical sides. Do not connect both wires to pins from the same side, or the button will be permanently shorted.

## 6.3 mm jack wiring

The eight jacks are included in the prototype wiring, but they are **not connected to Arduino GPIO pins**. The Nano must never receive guitar audio on a digital or analog control pin.

Label the jacks:

```text
Top row / inputs:
J1 = INPUT 1
J2 = INPUT 2
J3 = INPUT 3
J4 = INPUT 4

Bottom row / outputs:
J5 = OUTPUT 1
J6 = OUTPUT 2
J7 = OUTPUT 3
J8 = OUTPUT 4
```

For each 6.3 mm jack:

| Jack terminal | Connect to | Purpose |
|---|---|---|
| Tip | Its labelled audio node | Guitar signal; route later through relay/analog-switch hardware. |
| Sleeve | Common audio-ground rail | Cable/shield return. |
| Normally-closed contact, if present | Leave unconnected for now | Only used later if the switching design requires it. |

Prototype jack wiring:

```text
J1 tip     -> INPUT_1_AUDIO node
J1 sleeve  -> AUDIO_GND
J2 tip     -> INPUT_2_AUDIO node
J2 sleeve  -> AUDIO_GND
J3 tip     -> INPUT_3_AUDIO node
J3 sleeve  -> AUDIO_GND
J4 tip     -> INPUT_4_AUDIO node
J4 sleeve  -> AUDIO_GND

J5 tip     -> OUTPUT_1_AUDIO node
J5 sleeve  -> AUDIO_GND
J6 tip     -> OUTPUT_2_AUDIO node
J6 sleeve  -> AUDIO_GND
J7 tip     -> OUTPUT_3_AUDIO node
J7 sleeve  -> AUDIO_GND
J8 tip     -> OUTPUT_4_AUDIO node
J8 sleeve  -> AUDIO_GND
```

For this controller-only prototype, leave the eight tip nodes unconnected to the Nano and label them on the breadboard. The future audio-routing circuit will connect the input tip nodes to the output tip nodes according to the selected state.

The jack sleeves may share the audio-ground rail. Connect audio ground to Nano GND only if the later routing design requires a common ground; do not use the Nano as an audio signal path.

## Complete wiring diagram

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

OLED screen:
  +--------------------------------+
  | IN  1                    OUT  4|
  +--------------------------------+

Audio jack block, not connected to Nano GPIO:

J1 tip -> INPUT_1_AUDIO  J1 sleeve -> AUDIO_GND
J2 tip -> INPUT_2_AUDIO  J2 sleeve -> AUDIO_GND
J3 tip -> INPUT_3_AUDIO  J3 sleeve -> AUDIO_GND
J4 tip -> INPUT_4_AUDIO  J4 sleeve -> AUDIO_GND

J5 tip -> OUTPUT_1_AUDIO J5 sleeve -> AUDIO_GND
J6 tip -> OUTPUT_2_AUDIO J6 sleeve -> AUDIO_GND
J7 tip -> OUTPUT_3_AUDIO J7 sleeve -> AUDIO_GND
J8 tip -> OUTPUT_4_AUDIO J8 sleeve -> AUDIO_GND

* Only use Nano 5V when the OLED breakout is 5V-compatible.
```

## Grounding

- OLED GND and both button ground connections return to Nano GND.
- All jack sleeves connect to the common audio-ground rail.
- Keep the jack tips away from Nano GPIO pins.
- The final relationship between AUDIO_GND and Nano GND must be decided with the final audio-routing circuit.
