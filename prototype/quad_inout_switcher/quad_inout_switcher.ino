#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <Wire.h>

namespace {

constexpr uint8_t kChannelCount = 4;
constexpr unsigned long kDebounceMs = 30;

// Buttons use INPUT_PULLUP and connect to GND when pressed.
constexpr uint8_t kInputButtonPin = 2;
constexpr uint8_t kOutputButtonPin = 3;

// 128x32 SSD1306 I2C OLED.
constexpr uint8_t kOledWidth = 128;
constexpr uint8_t kOledHeight = 32;
constexpr int8_t kOledResetPin = -1;
constexpr uint8_t kOledAddress = 0x3C;

Adafruit_SSD1306 display(kOledWidth, kOledHeight, &Wire, kOledResetPin);

struct SelectionState {
  uint8_t activeInput;
  uint8_t activeOutput;
};

struct ButtonState {
  bool lastReading;
  bool stableReading;
  unsigned long lastChangeMs;
};

SelectionState selection = {0, 0};
ButtonState inputButton = {HIGH, HIGH, 0};
ButtonState outputButton = {HIGH, HIGH, 0};

uint8_t advanceSelection(uint8_t currentIndex) {
  return (currentIndex + 1) % kChannelCount;
}

void drawSelection(const SelectionState &state) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.print(F("IN: "));
  display.println(state.activeInput + 1);

  display.setCursor(0, 16);
  display.print(F("Out: "));
  display.println(state.activeOutput + 1);

  display.display();
}

void updateRoutingOutputs(const SelectionState &state) {
  (void)state;
  // Future relay or analog audio-switch control belongs here.
}

void applySelection(const SelectionState &state) {
  drawSelection(state);
  updateRoutingOutputs(state);
}

bool consumeButtonPress(ButtonState &buttonState, uint8_t pin,
                        unsigned long nowMs) {
  const bool reading = digitalRead(pin);

  if (reading != buttonState.lastReading) {
    buttonState.lastReading = reading;
    buttonState.lastChangeMs = nowMs;
  }

  if ((nowMs - buttonState.lastChangeMs) >= kDebounceMs &&
      reading != buttonState.stableReading) {
    buttonState.stableReading = reading;

    if (buttonState.stableReading == LOW) {
      return true;
    }
  }

  return false;
}

}  // namespace

void setup() {
  pinMode(kInputButtonPin, INPUT_PULLUP);
  pinMode(kOutputButtonPin, INPUT_PULLUP);

  if (!display.begin(SSD1306_SWITCHCAPVCC, kOledAddress)) {
    // Stop if the OLED cannot be initialized.
    for (;;) {
    }
  }

  display.clearDisplay();
  display.display();
  applySelection(selection);
}

void loop() {
  const unsigned long nowMs = millis();
  bool selectionChanged = false;

  if (consumeButtonPress(inputButton, kInputButtonPin, nowMs)) {
    selection.activeInput = advanceSelection(selection.activeInput);
    selectionChanged = true;
  }

  if (consumeButtonPress(outputButton, kOutputButtonPin, nowMs)) {
    selection.activeOutput = advanceSelection(selection.activeOutput);
    selectionChanged = true;
  }

  if (selectionChanged) {
    applySelection(selection);
  }
}
