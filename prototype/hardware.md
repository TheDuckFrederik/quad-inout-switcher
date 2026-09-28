# Prototype Hardware

## Components

### Controller and display

- **1× Arduino Nano** — reads the two buttons and drives the OLED over I2C.
- **1× 128×32 I2C OLED display** — preferably an SSD1306-compatible module with pins labelled `VCC`, `GND`, `SDA`, and `SCL`.
- **1× breadboard**
- Jumper wires
- USB data cable for power and programming

### User controls

- **2× four-prong PCB tactile push buttons**
  - Input button: cycles the selected input.
  - Output button: cycles the selected output.

### Audio connectors

- **8× 6.3 mm female jacks**
  - 4× inputs: Input 1–Input 4.
  - 4× outputs: Output 1–Output 4.

The jacks are included for mechanical and layout prototyping. They are not connected to Arduino pins. The Nano cannot safely switch guitar audio directly, and the audio routing circuit has not yet been selected.

## Removed parts

The previous eight LEDs and eight LED resistors are no longer part of this OLED prototype.

## Power

For this prototype, power the Nano from USB. Power the OLED from the voltage specified by its particular breakout board. Many Arduino OLED modules accept 5 V, but some bare OLED modules require 3.3 V. Check the module markings before connecting VCC.

The future pedal version will use a 9 V DC input with appropriate regulation and protection. Do not connect an unregulated 9 V pedal supply directly to the OLED or Nano 5 V pin.
