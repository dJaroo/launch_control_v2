#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "tacho.h"
#include "launch_control.h"
#include "display.h"

void setup() {
  Serial.begin(115200);
  while(!Serial);
  Serial.println("Serial ok");
  while(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
  }
  pinMode(LAUNCH_RELAY_PIN, OUTPUT);
  pinMode(LAUNCH_TRIGGER_BUTTON_PIN,INPUT_PULLDOWN);
  pinMode(TACHO_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(TACHO_PIN), tachoOnInterrupt, RISING);

  display.display();
  display.clearDisplay();
  display.display();
}

void loop() {
  launchOnLoop();
  tachoControlOnLoop();
  displayOnLoop();
}
