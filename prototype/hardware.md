# Prototype Hardware

## Components

- 1× Arduino Nano, ATmega328P
- 1× 128×32 I2C OLED display, preferably SSD1306-compatible
- 2× four-prong PCB tactile push buttons
  - input-cycle button
  - output-cycle button
- 8× 6.3 mm female jacks
  - J1–J4: inputs 1–4
  - J5–J8: outputs 1–4
- 1× breadboard
- Jumper wires
- USB data cable for Nano power and programming
- Optional 100 nF capacitor near OLED power pins

## Prototype wiring roles

### Controller

The Nano reads the two buttons and drives the OLED over I2C. The display is split horizontally: small `IN` and `OUT` labels, with large channel numbers beside them.

### Buttons

- Input button signal: Nano D2
- Output button signal: Nano D3
- Other electrical side of each button: Nano GND
- No external button resistors are required because the sketch uses `INPUT_PULLUP`.

### OLED

- SDA: Nano A4
- SCL: Nano A5
- VCC: Nano 5V only if the module is 5V-compatible
- GND: Nano GND

### 6.3 mm jacks

The jacks are mounted and labelled in the prototype but are not routed by the Nano yet:

- J1 tip: INPUT_1_AUDIO
- J2 tip: INPUT_2_AUDIO
- J3 tip: INPUT_3_AUDIO
- J4 tip: INPUT_4_AUDIO
- J5 tip: OUTPUT_1_AUDIO
- J6 tip: OUTPUT_2_AUDIO
- J7 tip: OUTPUT_3_AUDIO
- J8 tip: OUTPUT_4_AUDIO
- All jack sleeves: common AUDIO_GND rail
- Normally-closed jack contacts, if present: leave unconnected for now

Do not connect the jack tips to Arduino GPIO pins. The future relay or analog-switch stage will connect these audio nodes.

## Current limitation

This is a controller and display prototype. It does not yet pass or switch guitar audio. The future routing hardware will be added after the switching architecture is chosen.
