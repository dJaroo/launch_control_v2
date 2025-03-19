#define LAUNCH_RELAY_PIN 4
#define LAUNCH_TRIGGER_BUTTON_PIN 6
#define NUMBER_OF_TIME_RECORDS 3

unsigned long launchControlTimer = 0;
bool launchInProgress = 0;
bool coastInProgress = 0;
float launchTotalTime[NUMBER_OF_TIME_RECORDS][2];
int launchCurrentTimeRecordIndex = 0;

void launchStart() {
  digitalWrite(LAUNCH_RELAY_PIN, HIGH);
  launchInProgress = 1;
  launchControlTimer = millis();
}

void launchEnd() {
  launchInProgress = 0;
  coastInProgress = 1;
  digitalWrite(LAUNCH_RELAY_PIN, LOW);
  launchTotalTime[launchCurrentTimeRecordIndex][0] = ((float)(millis() - launchControlTimer)) / 1000;
  launchControlTimer = millis();
}

void coastEnd() {
  coastInProgress = 0;
  launchTotalTime[launchCurrentTimeRecordIndex][1] = ((float)(millis() - launchControlTimer)) / 1000;
  launchCurrentTimeRecordIndex++;
  launchCurrentTimeRecordIndex %= NUMBER_OF_TIME_RECORDS;
}

void launchOnLoop() {
  if (launchInProgress) {
    if (linearVelocity >= TARGET_VELOCITY) {
      launchEnd();
    }
  } else if (coastInProgress) {
    if (linearVelocity <= 0.28) {  //we're rounding down anything beneath ~1km/h to 0
      coastEnd();
    }
  } else if (digitalRead(LAUNCH_TRIGGER_BUTTON_PIN) == HIGH) {
    launchStart();
  }
}