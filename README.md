# phidget_ros
The following package offers a ROS interface with the Vint Hub phidget. This allows easy integration of the device within a ROS ecosystem.

1st install the official library from phidget

```
https://www.phidgets.com/docs/OS_-_Linux#Source%20Install
```

# Cloning the package into your catkin_workspace

Clone the following package in the src folder of your catkin workspace

```
git clone https://github.com/tbaltus/phidget_ros
```

# Running

Run `catkin_make` first

Then run the node

```
roscore
rosrun phidget_ros phidget
```

# Topics of interest

You can retrieve orientations of the sensors in the topic below

```
/EE_cartesian_orientation
```