#include <Arduino.h>

namespace {

constexpr uint8_t kChannelCount = 4;
constexpr unsigned long kDebounceMs = 30;

// Buttons use INPUT_PULLUP and should short to GND when pressed.
constexpr uint8_t kInputButtonPin = 2;
constexpr uint8_t kOutputButtonPin = 3;

// LEDs are active-high and should be wired with a series resistor to GND.
constexpr uint8_t kInputLedPins[kChannelCount] = {4, 5, 6, 7};
constexpr uint8_t kOutputLedPins[kChannelCount] = {8, 9, 10, 11};

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

void updateIndicatorLeds(const SelectionState &state) {
  for (uint8_t index = 0; index < kChannelCount; ++index) {
    digitalWrite(kInputLedPins[index], index == state.activeInput ? HIGH : LOW);
    digitalWrite(kOutputLedPins[index], index == state.activeOutput ? HIGH : LOW);
  }
}

void updateRoutingOutputs(const SelectionState &state) {
  (void)state;
  // Future relay or analog switch control can be added here without changing
  // button handling or selection state logic.
}

void applySelection(const SelectionState &state) {
  updateIndicatorLeds(state);
  updateRoutingOutputs(state);
}

bool consumeButtonPress(ButtonState &buttonState, uint8_t pin, unsigned long nowMs) {
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

  for (uint8_t pin : kInputLedPins) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }

  for (uint8_t pin : kOutputLedPins) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }

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
