#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <Servo.h>

const int ledPin =  LED_BUILTIN;
int ledState = LOW;
unsigned long previousMillis = 0;
const long interval = 1000;

ros::NodeHandle nh;
int throttleVal, rotationVal;
Servo servo1, servo2;

float limiter_throttle = 0.2;
float limiter_rotation = 0.2;

void cmdvelCb(const geometry_msgs::Twist& msg){
  throttleVal = (int)(128.0 - (msg.linear.x * 127.0 * limiter_throttle));
  rotationVal = (int)(128.0 + (msg.angular.z * 127.0 * limiter_rotation));
}

ros::Subscriber<geometry_msgs::Twist> cmdvelSub("/cmd_vel", &cmdvelCb);

void setup() {
  pinMode(ledPin, OUTPUT);
  
  nh.initNode();
  nh.subscribe(cmdvelSub);

  servo1.attach(5);
  servo2.attach(6);

  throttleVal = 128;
  rotationVal = 128;
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
  }
  
  servo1.write(throttleVal);
  servo2.write(rotationVal);

  delay(30);
  nh.spinOnce();
}
