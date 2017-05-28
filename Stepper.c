// - Stepper simple -
// This simple example sets up a Stepper object, hooks the event handlers and opens it for device connections.  
// Once an Advanced Servo is attached it will move the motor to various positions.
//
// Please note that this example was designed to work with only one Phidget Stepper connected. 
//
// Copyright 2008 Phidgets Inc.  All rights reserved.
// This work is licensed under the Creative Commons Attribution 2.5 Canada License. 
// view a copy of this license, visit http://creativecommons.org/licenses/by/2.5/ca/
// gcc Stepper.c -o Stepper -framework Phidget21 -I/Library/Frameworks/Phidget21.framework/Headers -lc -Werror
#include <stdio.h>
#include <phidget21.h>
#include <stdlib.h>
#include <stdbool.h>
//#include <unistd.h>

int CCONV AttachHandler(CPhidgetHandle stepper, void *userptr)
{
	int serialNo;
	const char *name;

	CPhidget_getDeviceName (stepper, &name);
	CPhidget_getSerialNumber(stepper, &serialNo);
	printf("%s %10d attached!\n", name, serialNo);

	return 0;
}

int CCONV DetachHandler(CPhidgetHandle stepper, void *userptr)
{
	int serialNo;
	const char *name;

	CPhidget_getDeviceName (stepper, &name);
	CPhidget_getSerialNumber(stepper, &serialNo);
	printf("%s %10d detached!\n", name, serialNo);

	return 0;
}

int CCONV ErrorHandler(CPhidgetHandle stepper, void *userptr, int ErrorCode, const char *Description)
{
	printf("Error handled. %d - %s\n", ErrorCode, Description);
	return 0;
}

int CCONV PositionChangeHandler(CPhidgetStepperHandle stepper, void *usrptr, int Index, __int64 Value)
{
	printf("Motor: %d > Current Position: %lld\n", Index, Value);
	return 0;
}

//Display the properties of the attached phidget to the screen.  We will be displaying the name, serial number and version of the attached device.
int display_properties(CPhidgetStepperHandle phid)
{
	int serialNo, version, numMotors;
	const char* ptr;

	CPhidget_getDeviceType((CPhidgetHandle)phid, &ptr);
	CPhidget_getSerialNumber((CPhidgetHandle)phid, &serialNo);
	CPhidget_getDeviceVersion((CPhidgetHandle)phid, &version);

	CPhidgetStepper_getMotorCount (phid, &numMotors);

	printf("%s\n", ptr);
	printf("Serial Number: %10d\nVersion: %8d\n# Motors: %d\n", serialNo, version, numMotors);

	return 0;
}

int stepper_simple()
{
	int result;
	__int64 curr_pos;
	const char *err;
	double minAccel, maxVel;
	int stopped;

	//Declare an stepper handle
	CPhidgetStepperHandle stepper = 0;

	//create the stepper object
	CPhidgetStepper_create(&stepper);

	//Set the handlers to be run when the device is plugged in or opened from software, unplugged or closed from software, or generates an error.
	CPhidget_set_OnAttach_Handler((CPhidgetHandle)stepper, AttachHandler, NULL);
	CPhidget_set_OnDetach_Handler((CPhidgetHandle)stepper, DetachHandler, NULL);
	CPhidget_set_OnError_Handler((CPhidgetHandle)stepper, ErrorHandler, NULL);

	//Registers a callback that will run when the motor position is changed.
	//Requires the handle for the Phidget, the function that will be called, and an arbitrary pointer that will be supplied to the callback function (may be NULL).
	CPhidgetStepper_set_OnPositionChange_Handler(stepper, PositionChangeHandler, NULL);

	//open the device for connections
	CPhidget_open((CPhidgetHandle)stepper, -1);

	//get the program to wait for an stepper device to be attached
	printf("Waiting for Phidget to be attached....");
	if((result = CPhidget_waitForAttachment((CPhidgetHandle)stepper, 10000)))
	{
		CPhidget_getErrorDescription(result, &err);
		printf("Problem waiting for attachment: %s\n", err);
		return 0;
	}

	//Display the properties of the attached device
	display_properties(stepper);

	//read event data
	printf("Reading.....\n");

	//This example assumes stepper motor is attached to index 0

	//Set up some initial acceleration and velocity values
	CPhidgetStepper_getAccelerationMin(stepper, 0, &minAccel);
	CPhidgetStepper_setAcceleration(stepper, 0, minAccel*2);
	CPhidgetStepper_getVelocityMax(stepper, 0, &maxVel);
	CPhidgetStepper_setVelocityLimit(stepper, 0, maxVel/2);

	//display current motor position if available
	if(CPhidgetStepper_getCurrentPosition(stepper, 0, &curr_pos) == EPHIDGET_OK)
		printf("Motor: 0 > Current Position: %lld\n", curr_pos);

	//keep displaying stepper event data until user input is read
	printf("Press any key to continue\n");
	getchar();

	//change the motor position
	//we'll set it to a few random positions to move it around

	//Step 1: Position 0 - also engage stepper
	printf("Set to position 0 and engage. Press any key to Continue\n");
	getchar();

	CPhidgetStepper_setCurrentPosition(stepper, 0, 0);
	CPhidgetStepper_setEngaged(stepper, 0, 1);

	//Step 2: Position 200
	printf("Move to position 200. Press any key to Continue\n");
	getchar();

	CPhidgetStepper_setTargetPosition (stepper, 0, 200);

	//Step 3: Position -1200
	printf("Move to position -1200. Press any key to Continue\n");
	getchar();

	CPhidgetStepper_setTargetPosition (stepper, 0, -1200);

	//Step 4: Set to 0, wait for it to reach position, Disengage
	printf("Reset to 0 and disengage motor. Press any key to Continue\n");
	getchar();

	CPhidgetStepper_setTargetPosition(stepper, 0, 0);

	stopped = PFALSE;
	while(!stopped)
	{
		CPhidgetStepper_getStopped(stepper, 0, &stopped);
		//usleep(100000);
	}

	CPhidgetStepper_setEngaged(stepper, 0, 0);

	printf("Press any key to end\n");
	getchar();

	//since user input has been read, this is a signal to terminate the program so we will close the phidget and delete the object we created
	printf("Closing...\n");
	CPhidget_close((CPhidgetHandle)stepper);
	CPhidget_delete((CPhidgetHandle)stepper);

	//all done, exit
	return 0;
}

int main(int argc, char* argv[])
{
	if (argc != 1)
	{
		printf("Useage: ./Stepper.c Filename.gcode");
		return 1;
	}
	int result;
	__int64 curr_pos;
	const char *err;
	double minAccel, maxVel;
	int stopped;

	//Declare an stepper handle
	CPhidgetStepperHandle stepper = 0;

	//create the stepper object
	CPhidgetStepper_create(&stepper);

	//Set the handlers to be run when the device is plugged in or opened from software, unplugged or closed from software, or generates an error.
	CPhidget_set_OnAttach_Handler((CPhidgetHandle)stepper, AttachHandler, NULL);
	CPhidget_set_OnDetach_Handler((CPhidgetHandle)stepper, DetachHandler, NULL);
	CPhidget_set_OnError_Handler((CPhidgetHandle)stepper, ErrorHandler, NULL);

	//Registers a callback that will run when the motor position is changed.
	//Requires the handle for the Phidget, the function that will be called, and an arbitrary pointer that will be supplied to the callback function (may be NULL).
	CPhidgetStepper_set_OnPositionChange_Handler(stepper, PositionChangeHandler, NULL);

	//open the device for connections
	CPhidget_open((CPhidgetHandle)stepper, -1);

	//get the program to wait for an stepper device to be attached
	printf("Waiting for Phidget to be attached....");
	if((result = CPhidget_waitForAttachment((CPhidgetHandle)stepper, 10000)))
	{
		CPhidget_getErrorDescription(result, &err);
		printf("Problem waiting for attachment: %s\n", err);
		return 0;
	}

	//Display the properties of the attached device
	display_properties(stepper);

	//read event data
	printf("Reading.....\n");

	//This example assumes stepper motor is attached to index 0

	//Set up some initial acceleration and velocity values
	CPhidgetStepper_getAccelerationMin(stepper, 0, &minAccel);
	CPhidgetStepper_setAcceleration(stepper, 0, minAccel*2);
	CPhidgetStepper_getVelocityMax(stepper, 0, &maxVel);
	CPhidgetStepper_setVelocityLimit(stepper, 0, maxVel/2);
	
	int xcounter = 0;
	int ycounter = 0;
	int zcounter = 0;
	double x[1000000];
	double y[1000000];
	double z[100000];
	char* filename = argv[1];
	FILE* Gcode = fopen(filename, "r");
	char buffer;
	int numgap[100000];
	int gapcounter = 0;
	int gapval = 0;
	//Read from file co values
	for (int i = 0; buffer != EOF; i++)
	{
		int charcount = 0;
		char* valuebuffer;
		bool xval = false;
		bool yval = false;
		bool zval = false;
		buffer = fgetc(Gcode);

		if ((xval == true || yval == true || zval == true) && ((buffer > 47 && buffer < 58) || buffer == 46))
		{
			valuebuffer[charcount] = buffer;
		}
		else
		{
			if (xval == true && charcount > 1)
			{
				x[xcounter] = atof(valuebuffer);
				xcounter++;
				gapval++;
			}
			if (yval == true && charcount > 1)
			{
				y[ycounter] = atof(valuebuffer);
				ycounter++;
			}
			if (zval == true && charcount > 1)
			{
				z[zcounter] = atof(valuebuffer);
				zcounter++;
				numgap[gapcounter] = gapval;
				gapval = 0;
			}
			xval = false;
			yval = false;
			zval = false;
			charcount = 0;
		}
		if (buffer == (int) x)
		{
			xval = true;
		}
		else if (buffer == (int) y)
		{
			yval = true;
		}
		else if (buffer == (int) z)
		{
			zval = true;
		}
	}
	int xco[xcounter];
	int yco[ycounter];
	int zco[zcounter];

	//Round Cooridnates
	float last_co = 0;
	float co = 0;
	int r;
	for (int i = 0; i < xcounter; i++)
	{
	int step;
	int temp;
	int mmd;
	co = x[i];
	mmd = co - last_co;
	temp = mmd/.13;
	r = temp & (int) temp;

	if (r > .5)
	{
		float a = .9;
		step = temp + a;
		step = (int) step;
	}
	else
	{
		step = (int) temp;
	}
	xco[i] = step;
	last_co = co;
	}
	last_co = 0;
	for (int i = 0; i < ycounter; i++)
	{
	int step;
	int temp;
	int mmd;
	co = y[i];
	mmd = co - last_co;
	temp = mmd/.13;
	r = temp & (int) temp;

	if (r > .5)
	{
		float a = .9;
		step = temp + a;
		step = (int) step;
	}
	else
	{
		step = (int) temp;
	}
	yco[i] = step;
	last_co = co;
	}
	last_co = 0;
	for (int i = 0; i < zcounter; i++)
	{
	int step;
	int temp;
	int mmd;
	co = z[i];
	mmd = co - last_co;
	temp = mmd/.13;
	r = temp & (int) temp;

	if (r > .5)
	{
		float a = .9;
		step = temp + a;
		step = (int) step;
	}
	else
	{
		step = (int) temp;
	}
	zco[i] = step;
	last_co = co;
	}
	int bm;
	if (ycounter > xcounter)
	{
		bm = ycounter;
	}
	else
	{
		bm = xcounter;
	}

	int motorx = 0;
	int motory = 1;
	int motorz = 2;
	int counter = 0;
	int ccounter = 0;
	int poscounter= 0;
	CPhidgetStepper_setEngaged(stepper, 0, 1);
	CPhidgetStepper_setEngaged(stepper, 1, 1);
	CPhidgetStepper_setEngaged(stepper, 2, 1);
	for (int i = 0; i < bm; i++)
	{
		bool xstopped = false;
		bool ystopped = false;
		bool zstopped = false;
		CPhidgetStepper_setTargetPosition (stepper, motorx, xco[i]);
		counter++;
		CPhidgetStepper_setTargetPosition (stepper, motory, yco[i]);
		while (!xstopped)
		{
			CPhidgetStepper_getStopped(stepper, motorx, &stopped);
		}
		while (!ystopped)
		{
			CPhidgetStepper_getStopped(stepper, motory, &stopped);
		}
		if (numgap[ccounter] == counter)
		{
			CPhidgetStepper_setTargetPosition (stepper, motorz, zco[poscounter]);
			poscounter++;
			counter = 0;
			ccounter++;
			while (!zstopped)
			{
				CPhidgetStepper_getStopped(stepper, motorz, &stopped);
			}
		}
	}

}

