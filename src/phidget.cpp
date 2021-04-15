// C++ library headers
#include <iostream>
#include <iomanip>
// project headers
#include "ros/ros.h"
#include "phidget_ros/phidget22.h"

////////////////////////////////////////////////////////////////////////////////

static void CCONV onVoltageRatioChange(PhidgetVoltageRatioInputHandle ch, void * ctx, double voltageRatio) {
	int hubPort;

	Phidget_getHubPort((PhidgetHandle)ch, &hubPort);
	printf("VoltageRatio [%d]: %lf\n", hubPort, voltageRatio);
}

int main(int argc, char* argv[])
{
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

	//Wait until Enter has been pressed before exiting
	getchar();

	Phidget_close((PhidgetHandle)voltageRatioInput0);
	Phidget_close((PhidgetHandle)voltageRatioInput1);
	Phidget_close((PhidgetHandle)voltageRatioInput2);

	PhidgetVoltageRatioInput_delete(&voltageRatioInput0);
	PhidgetVoltageRatioInput_delete(&voltageRatioInput1);
	PhidgetVoltageRatioInput_delete(&voltageRatioInput2);
}

