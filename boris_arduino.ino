#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <Servo.h>

ros::NodeHandle nh;
int throttleVal, rotationVal;
Servo servo1, servo2;

void cmdvelCb(const geometry_msgs::Twist& msg){
  throttleVal = 128 + (msg->linear.x * 127);
  rotationVal = 128 + (msg->angular.z * 127);
}

ros::Subscriber<geometry_msgs::Twist> cmdvelSub("cmd_vel", &cmdvelCb);

void setup() {
  nh.initNode();
  nh.subscribe(cmdvelSub);

  servo1.attach(5);
  servo2.attach(6);

  throttleVal = 128;
  rotationVal = 128;
}

void loop() {
  servo1.write(throttleVal);
  servo2.write(rotationVal);

  delay(30);
  nh.spinOnce();
}
