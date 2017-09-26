# zitzic_arduino
Code for zitzic robot's arduino board

## Installation:
- Unzip Sabertooth arduino libraries and install in arduino library folder (location is OS-specific)
- Install ROS_serial arduino library (available [here](http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup#Install_ros_lib_into_the_Arduino_Environment))
- upload to arduino board

## Use:
- connect Tx on arduino board to Sabertooth motor controller
- run Ros master locally 
- upload to arduino board
- ?maybe possibly run sister program locally to actually track ros topics?
- publish commands to ros topics **cmd_speed** and **cmd_turn** as std_msgs::Int8:	

data 		| -127 		| 	0		| 128
cmd_speed 	| reverse	| stop		| forward
cmd_turn 	| left		| straight	| right


