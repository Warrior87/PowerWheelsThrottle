//throttle setup usig pot throttle, and low side switch (brushed DC motors)
/*Hardware:
 * throttle pot input on analog 7
 * PWM output on pin 5 
 */

//#define DEBUG

#ifdef DEBUG
  #define DEBUG_PRINT(x)  Serial.print (x)
  #define DEBUG_PRINTLN(x)  Serial.println (x)
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTLN(x)
#endif

void setup() {
  #ifdef DEBUG
    Serial.begin(115200);
  #endif
}

void loop() {
  // put your main code here, to run repeatedly:

}
