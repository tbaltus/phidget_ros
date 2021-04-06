// C++ library headers
#include <iostream>
#include <iomanip>
// project headers
#include "ros/ros.h"
#include "phidget_ros/phidget22.h"

////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
	PhidgetEncoderHandle encoder0;
	PhidgetEncoder_create(&encoder0);
    return 0;
}

