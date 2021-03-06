#include "MirrorController.h"
#include "Arduino.h"


#define MOTOR_PIN 10		//	Control wire of brushless motor ESC attached to digital pin 10
#define PHOTO_PIN 5		//	Photo transistor on analog pin 0
#define SPEED_MAX 58
#define SPEED_NORMAL 50

void MirrorController::init()
{
	hddMotor = new PWMServo();
	hddMotor->attach(MOTOR_PIN);
	pinMode(PHOTO_PIN, INPUT);
}

void MirrorController::start()
{
	for (int i = 0; i < SPEED_MAX; i++)
	{
		hddMotor->write(i);
		delay(200);
	};
	delay(1000);
	for (int i = SPEED_MAX; i > SPEED_NORMAL; i--)
	{
		hddMotor->write(i);
		delay(50);
	}
}

long MirrorController::calculateRotationSpeed()
{
	long startTime;
	while (!digitalRead(PHOTO_PIN))
	{
		// do nothing
	};
	while (digitalRead(PHOTO_PIN))
	{
		startTime = micros();
	};
	
	long stopTime;
	for (int i = 0; i < 20; i++)
	{
		waitForBeginMarkFast();
		//while (!digitalRead(PHOTO_PIN))
		//{
		//	// do nothing
		//};
		//while (digitalRead(PHOTO_PIN))
		//{
		//	stopTime = micros();
		//};
	}
	return (stopTime - startTime) / 20;
}

//long MirrorController::waitForBeginMark()
//{
//	long result;
//	while (PIND & 0x20)
//	{
//		// do nothing
//	};
//	while (!(PIND & 0x20))
//	{
//		result = micros();
//	};
//	
//	return result;
//}

void MirrorController::waitForBeginMarkFast()
{
	while (PIND & 0x20)
	{
		// do nothing
	};
	while (!(PIND & 0x20))
	{
		// do nothing
	};
}




