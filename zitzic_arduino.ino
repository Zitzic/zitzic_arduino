/* 
 * rosserial Subscriber 
 * manages Sabertooth V1.0
 */

// ROS init
#include <ros.h>
#include <std_msgs/Int8.h>

ros::NodeHandle  nh;

// Sabertooth Serial Init
#include <SabertoothSimplified.h>

// Mixed mode is for tank-style diff-drive robots.
// Only Packet Serial actually has mixed mode, so this Simplified Serial library
// emulates it (to allow easy switching between the two libraries).

SabertoothSimplified ST; // We'll name the Sabertooth object ST.
                         // For how to configure the Sabertooth, see the DIP Switch Wizard for
                         //   http://www.dimensionengineering.com/datasheets/SabertoothDIPWizard/start.htm
                         // Be sure to select Simplified Serial Mode for use with this library.
                         // This sample uses a baud rate of 9600.
                         //
                         // Connections to make:
                         //   Arduino TX->1  ->  Sabertooth S1
                         //   Arduino GND    ->  Sabertooth 0V
                         //   Arduino VIN    ->  Sabertooth 5V (OPTIONAL, if you want the Sabertooth to power the Arduino)
                         //
                         // If you want to use a pin other than TX->1, see the SoftwareSerial example.

// Local Vars (char==signed 8bit int (-127,128))
volatile char speed;
volatile char turn;

void inc_Speed( const std_msgs::Int8& new_speed){
  speed = new_speed.data;
  ST.drive(speed);
}

void inc_Turn( const std_msgs::Int8& new_turn){
  turn = new_turn.data;
  ST.turn(turn);
}

ros::Subscriber<std_msgs::Int8> sub_speed("cmd_speed", &inc_Speed );
ros::Subscriber<std_msgs::Int8> sub_turn("cmd_turn", &inc_Turn );

void setup()
{ 
  // ROS setup
  nh.initNode();
  nh.subscribe(sub_speed);
  nh.subscribe(sub_turn);

  // Sabertooth
  SabertoothTXPinSerial.begin(9600); // This is the baud rate you chose with the DIP switches.             
  
  ST.drive(0); // The Sabertooth won't act on mixed mode until
  ST.turn(0);  // it has received power levels for BOTH throttle and turning, since it
               // mixes the two together to get diff-drive power levels for both motors.
               // So, we set both to zero initially.
}

void loop()
{  
  nh.spinOnce();
  delay(1);
}

