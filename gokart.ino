#include <TimerOne.h>

//definitions
#define PWM_CYCLE 50.0
#define PWM_OUT 9
#define MAX_DUTY 869
#define MIN_DUTY 0
#define inPin 12

//int
int speedLevel;
int ACC = 0;
int reading;
int previous = LOW;

void setup()
{
  //init pwmout and timer1
  pinMode(PWM_OUT, OUTPUT);
  pinMode(10, OUTPUT);
  Timer1.initialize(PWM_CYCLE * 1000);
  Timer1.pwm(PWM_OUT, 0);
  //acc switch
  pinMode(inPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  reading = digitalRead(inPin);
  
  //if switch is in on position, accelerate
  if (reading == HIGH && previous == LOW) {
    ACC = ACC + 20;
  }
  
  //if switch is in off position, decelerate
  if (reading == LOW && previous == HIGH) {
    ACC = ACC - 20;
  }
  
  speedLevel = map(ACC, 0, 1023, 0, MAX_DUTY);

  Timer1.setPwmDuty(PWM_OUT, speedLevel);
  Serial.print("speed: " + speedLevel);
  Serial.print("ACC: " + ACC);
}
