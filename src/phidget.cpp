// C++ library headers
#include <iostream>
#include <iomanip>
// project headers
#include "ros/ros.h"
#include "phidget_ros/phidget22.h"
#include "geometry_msgs/Vector3Stamped.h"

////////////////////////////////////////////////////////////////////////////////

geometry_msgs::Vector3Stamped cartes_orient_phid;
ros::Publisher cartesian_orientation_phidget_pub;

static void CCONV onVoltageRatioChange(PhidgetVoltageRatioInputHandle ch, void * ctx, double voltageRatio) {
	int hubPort;

	Phidget_getHubPort((PhidgetHandle)ch, &hubPort);

	if(hubPort == 0)
		cartes_orient_phid.vector.x = voltageRatio;

	if(hubPort == 1)
		cartes_orient_phid.vector.y = voltageRatio;

	if(hubPort == 2)
		cartes_orient_phid.vector.z = voltageRatio;
}

int main(int argc, char* argv[])
{
	ros::init(argc,argv, "Phidget");
	ros::NodeHandle node;

	cartes_orient_phid.vector.x=0;
	cartes_orient_phid.vector.y=0;
	cartes_orient_phid.vector.z=0;

	ros::Publisher cartesian_orientation_phidget_pub;
	cartesian_orientation_phidget_pub = node.advertise<geometry_msgs::Vector3Stamped>("/EE_cartesian_orientation",1);

	PhidgetVoltageRatioInputHandle voltageRatioInput0;
	PhidgetVoltageRatioInputHandle voltageRatioInput1;
	PhidgetVoltageRatioInputHandle voltageRatioInput2;

	PhidgetVoltageRatioInput_create(&voltageRatioInput0);
	PhidgetVoltageRatioInput_create(&voltageRatioInput1);
	PhidgetVoltageRatioInput_create(&voltageRatioInput2);

	Phidget_setIsHubPortDevice((PhidgetHandle)voltageRatioInput0, 1);
	Phidget_setHubPort((PhidgetHandle)voltageRatioInput0, 0);
	Phidget_setIsHubPortDevice((PhidgetHandle)voltageRatioInput1, 1);
	Phidget_setHubPort((PhidgetHandle)voltageRatioInput1, 1);
	Phidget_setIsHubPortDevice((PhidgetHandle)voltageRatioInput2, 1);
	Phidget_setHubPort((PhidgetHandle)voltageRatioInput2, 2);

	PhidgetVoltageRatioInput_setOnVoltageRatioChangeHandler(voltageRatioInput0, onVoltageRatioChange, NULL);
	PhidgetVoltageRatioInput_setOnVoltageRatioChangeHandler(voltageRatioInput1, onVoltageRatioChange, NULL);
	PhidgetVoltageRatioInput_setOnVoltageRatioChangeHandler(voltageRatioInput2, onVoltageRatioChange, NULL);

	Phidget_openWaitForAttachment((PhidgetHandle)voltageRatioInput0, 5000);
	Phidget_openWaitForAttachment((PhidgetHandle)voltageRatioInput1, 5000);
	Phidget_openWaitForAttachment((PhidgetHandle)voltageRatioInput2, 5000);

	ros::Rate loop_rate(20);

	while(ros::ok())
	{
		cartesian_orientation_phidget_pub.publish(cartes_orient_phid);
		ros::spinOnce();
		loop_rate.sleep();
	}

	Phidget_close((PhidgetHandle)voltageRatioInput0);
	Phidget_close((PhidgetHandle)voltageRatioInput1);
	Phidget_close((PhidgetHandle)voltageRatioInput2);

	PhidgetVoltageRatioInput_delete(&voltageRatioInput0);
	PhidgetVoltageRatioInput_delete(&voltageRatioInput1);
	PhidgetVoltageRatioInput_delete(&voltageRatioInput2);
}

