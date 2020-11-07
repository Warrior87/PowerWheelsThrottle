//throttle setup usig pot throttle, and low side switch (brushed DC motors)
/*Hardware:
 * throttle pot input on analog 7
 * PWM output on pin 5 
 * 
 * 308 - no throttle (min 300)
 * 720 - full throttle (max 750)
 * 
 * throttle position at max travel stops can vary
 * 
 * gate drive hardware has limitations at 90% duty cycle
 */

//#define DEBUG

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
int zeroThrottle = 310;                                         /*throttle reading when pedal is at 0*/
int fullThrottle = 410;                                         /*throttle reading when pedal is at 100%, originally 720*/
double slope = 0.622;                                           /*value converts ADC values to PWM values, scaling variable*/
int motorDrive;                                                 /*motor PWM value*/
int newMotorDrive = 0;
int motor90 = 219;                                              /*(90%) max drive value. if calculated value is higher, just set to 100%*/
int motorRampMax = 76;                                          /*if below, ramp motor, if above, no ramping*/
int rampRate = 1;                                               /*value that gets added to motorDrive below 30%*/
byte increasing = 0;                                            /*1 if increasing, 0 if not increasing*/

void setup() {
  #ifdef DEBUG
    Serial.begin(115200);
  #endif

  pinMode(motorPin, OUTPUT);
  digitalWrite(motorPin, LOW);
  TCCR0B = TCCR0B & B11111000 | B00000001; // for PWM frequency of 62500.00 Hz
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
  newMotorDrive = (double)throttlePosition * slope;                /*multiply throttle position by slope to get PWM value*/
  DEBUG_PRINT("\t");
  DEBUG_PRINT(newMotorDrive);
  if(newMotorDrive > 255){                                         /*correct motorDrive if it is over 255*/
    newMotorDrive = 255;
  }
  if(newMotorDrive < 0){                                           /*correct motorDrive if it is negative*/
    newMotorDrive = 0;
  }
  if(newMotorDrive > motor90){                                     /*correct for 90%. if calculated value is higher than 90%, set to 100%*/
    newMotorDrive = 255;
  }  
  if(newMotorDrive > motorDrive){                                  /*figure out if newMotorDrive is increasing*/
    increasing = 1;
  }
  else{
    increasing = 0;
  }
  /*if the new motor drive value is below motorRampMax and increasing, it needs to ramp slow*/
  if((motorDrive < motorRampMax) && (increasing == 1)){
    motorDrive = motorDrive + rampRate;
    DEBUG_PRINT("\t");
    DEBUG_PRINTLN("ramp");
    delay(10);                                                    /*add extra delay to slow ramp up*/
  }    
  /*always allow the motor drive to decrease fast*/
  motorDrive = newMotorDrive;
  DEBUG_PRINT("\t");
  DEBUG_PRINTLN(motorDrive);
  analogWrite(motorPin, motorDrive);                             /*write PWM drive value to motorPin*/
  delay(1);
}
