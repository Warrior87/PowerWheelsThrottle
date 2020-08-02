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
const byte optoPin = 4; 

int throttlePosition;
int zeroThrottle = 310;                                         /*throttle reading when pedal is at 0*/
int fullThrottle = 410;                                         /*throttle reading when pedal is at 100%, originally 720*/
double slope = 0.622;                                           /*value converts ADC values to PWM values, scaling variable*/
int motorDrive;                                                 /*motor PWM value*/

void setup() {
  #ifdef DEBUG
    Serial.begin(115200);
  #endif

  pinMode(motorPin, OUTPUT);
  digitalWrite(motorPin, LOW);
  pinMode(optoPin, OUTPUT);                                     /*LED cathode pin on opto-isolator/photo-transistor*/
  digitalWrite(optoPin, LOW);
}

void loop() {
  throttlePosition = analogRead(throttlePin);  
  DEBUG_PRINT(throttlePosition);
  throttlePosition = throttlePosition - zeroThrottle;           /*offset throttle position to start at 0, at 0 throttle*/
  if(throttlePosition < 0){                                     /*correct throttle position if it is negative*/
    throttlePosition = 0;
  }
  DEBUG_PRINT("\t");
  DEBUG_PRINT(throttlePosition);
  motorDrive = (double)throttlePosition * slope;                /*multiply throttle position by slope to get PWM value*/
  DEBUG_PRINT("\t");
  DEBUG_PRINT(motorDrive);
  if(motorDrive > 255){                                         /*correct motorDrive if it is over 255*/
    motorDrive = 255;
  }
  if(motorDrive < 0){                                           /*correct motorDrive if it is negative*/
    motorDrive = 0;
  }
  DEBUG_PRINT("\t");
  DEBUG_PRINT(motorDrive);
  analogWrite(motorPin, motorDrive);                            /*write PWM drive value to motorPin*/
  DEBUG_PRINT("\t");
  DEBUG_PRINTLN(motorDrive);
  delay(1);
}
