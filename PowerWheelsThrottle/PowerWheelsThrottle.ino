//throttle setup usig pot throttle, and low side switch (brushed DC motors)
/*Hardware:
 * throttle pot input on analog 7
 * PWM output on pin 5 
 * 
 * 308 - no throttle (min 300)
 * 720 - full throttle (max 750)
 * 
 * throttle position at max travel stops can vary
 */

#define DEBUG

#ifdef DEBUG
  #define DEBUG_PRINT(x)  Serial.print (x)
  #define DEBUG_PRINTLN(x)  Serial.println (x)
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTLN(x)
#endif

const byte motorPin = 5;
const byte throttlePin = 7;

int throttlePosition;

void setup() {
  #ifdef DEBUG
    Serial.begin(115200);
  #endif

  pinMode(motorPin, OUTPUT);
  digitalWrite(motorPin, LOW);
}

void loop() {
  throttlePosition = analogRead(throttlePin);
  DEBUG_PRINTLN(throttlePosition);
  delay(100);

}
