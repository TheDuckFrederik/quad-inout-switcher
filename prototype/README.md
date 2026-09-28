# Quad In/Out Switcher — Arduino OLED Prototype

This prototype uses an Arduino Nano to select one of four inputs and one of four outputs. The selected values are displayed on a 128×32 I2C OLED in a single horizontal row.

## Display layout

```text
IN  1                         OUT  4
```

- Small `IN` label on the left.
- Large input number beside it.
- Small `OUT` label on the right.
- Large output number beside it.

## Current scope

- Two buttons cycle input and output selection independently.
- The OLED displays the selected channels.
- Eight 6.3 mm jacks are included and labelled for future audio routing.
- Audio routing is **not implemented yet**.

## Documentation

- Components and hardware roles: `prototype/hardware.md`
- Complete Nano, OLED, button, and jack wiring: `prototype/pinout.md`
- Upload, test, and troubleshooting: `prototype/firmware.md`
- Detailed code explanation: `prototype/code-walkthrough.md`

## Quick test

1. Install Adafruit GFX Library and Adafruit SSD1306.
2. Wire the Nano, OLED, and buttons according to `prototype/pinout.md`.
3. Mount and label the eight jacks; connect sleeves to AUDIO_GND and keep tips away from Nano pins.
4. Open `prototype/quad_inout_switcher/quad_inout_switcher.ino`.
5. Upload for an Arduino Nano using the correct processor and port.
6. Confirm the display shows the left/right layout with `IN 1` and `OUT 1`.
7. Press the input button and verify only the large input number changes.
8. Press the output button and verify only the large output number changes.
