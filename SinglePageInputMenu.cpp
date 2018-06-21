#include "SinglePageInputMenu.hpp"

static const uint8_t PIEZO_OUTPUT_PIN = 4;

// Warning sound frequency in Hz (max 60000)
unsigned int mWarningSoundFrequency = 1000;
// Tone duration in milliseconds
unsigned long mWarningToneDuration = 500;

/*******************************
 * Constructors
 *******************************/

SinglePageInputMenu::SinglePageInputMenu() 
    : SerialDisplayMenu(new SerialDisplayMenuConfiguration(SerialDisplayType::ansi_vt100, false, 1000, 100000), nullptr, (int8_t) 2, (int8_t) 4) {
  
  pinMode(PIEZO_OUTPUT_PIN, OUTPUT);
  Serial.begin(115200);
}

/*******************************
 * Actions
 *******************************/

void SinglePageInputMenu::controllerUpdate() {}
String SinglePageInputMenu::constructStatusLine() {}

void SinglePageInputMenu::printMenu() {
  Serial.print("  Please type in the new value: ");
}

SerialDisplayMenu* SinglePageInputMenu::processUserInput(String userInput) {
  long newSetPoint = userInput.toInt();
  if (newSetPoint < 0 || newSetPoint > 60000) {
    displayError("Only whole numbers between 0 and 60000 are accepted, rec: " + String(userInput));
    return this;
  }

  mWarningSoundFrequency = newSetPoint;
  
  tone(PIEZO_OUTPUT_PIN, mWarningSoundFrequency, mWarningToneDuration);
  delay(1000);
  tone(PIEZO_OUTPUT_PIN, mWarningSoundFrequency, mWarningToneDuration);
  delay(1000);
  tone(PIEZO_OUTPUT_PIN, mWarningSoundFrequency, mWarningToneDuration);
  delay(1000);
    
  return this;
}
