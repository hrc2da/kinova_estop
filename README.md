# kinova_estop
basic arduino estop code for kinova j2s7s300

For ros-indigo you need rosserial and rosserial-arduino installed. Follow directions here:

http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup

sudo apt-get install ros-indigo-rosserial-arduino
sudo apt-get install ros-indigo-rosserial

Make sure you source devel/setup.bash in your catkin_ws with the kinova_msgs srv built before you run the make_libraries script:

  cd <sketchbook>/libraries
  rm -rf ros_lib
  rosrun rosserial_arduino make_libraries.py .
  
To use the e-stop, connect the arduino via usb and figure out the port it is mounted on, then run:

rosrun rosserial_python serial_node.py <port e.g. /dev/ttyACM0>

If you get an error about losing sync, check that you are running nh.spinOnce() frequently enough (you can mess with a delay in the event loop).

The circuit itself has the on pin of the switch connected to 5v and the other pin between pin 2 and a 10k resistor leading to ground.
