#define TACHO_PIN 3
#define TACHO_TICKS_PER_ROTATION 6
#define WHEEL_RADIUS 0.245  //outer radius in meters
#define TARGET_VELOCITY 8.333 //in m/s

unsigned long tachoLastTickTime = 0;
float linearVelocity = 0; //in m/s
float angularVelocity = 0;

void tachoOnInterrupt() {
  unsigned long tachoTimeDelta = micros() - tachoLastTickTime;
  tachoLastTickTime = micros();
  angularVelocity = (2 * 3141592.65) / (TACHO_TICKS_PER_ROTATION * tachoTimeDelta);
  linearVelocity = WHEEL_RADIUS * angularVelocity;
}

void tachoControlOnLoop(){
  if(micros() - tachoLastTickTime > 1000000){
    linearVelocity = 0;
  }
}