#pragma config(Motor,  port2,           WheelMotor,    tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port3,           ArmServo,      tmotorServoStandard, openLoop)
#pragma config(Motor,  port4,           boxServo,      tmotorServoStandard, openLoop)
#pragma config(Motor,  port5,           RightMotor,    tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port6,           LeftMotor,     tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port8,           ShotServo,     tmotorServoStandard, openLoop)
#pragma config(Motor,  port9,           DumpMotor,     tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

bool reversed = false, servoShot = false ,reversed_PrevVal = reversed;
int wheelSpeed = 127, dumpSpeed = 127, maxServo = 127, zeroServo = 0, lowServo = -10, minServo = -127;

void ArmControl()
{
	if(vexRT[Btn7L] == 1)
		motor[ArmServo] = maxServo;
	else if (vexRT[Btn7D] == 1)
		motor[ArmServo] = lowServo;
}

void ProcessReverse()
{
	if(vexRT[Btn8R] == 1 && reversed == reversed_PrevVal)
		reversed = !reversed;
	else if(vexRT[Btn8R] == 0 && reversed != reversed_PrevVal)
		reversed_PrevVal = reversed;
}

void WheelControl()
{
	if(vexRT[Btn6U] == 1)
		motor[WheelMotor] = wheelSpeed;
	else if(vexRT[Btn6D] == 1)
		motor[WheelMotor] = (wheelSpeed * (-1));
	else if(vexRT[Btn5D] == 0 && vexRT[Btn5U] == 0)
		motor[WheelMotor] = 0;
}



void DriveControl()
{
motor[RightMotor] = ((reversed ? -1 : 1) * vexRT[Ch2]);
motor[LeftMotor] = ((reversed ? -1 : 1) * vexRT[Ch3]);
}

void DumpControl(){
	if (vexRT[Btn5U] == 1 && vexRT[Btn6D] == 0 && vexRT[Btn6U] == 0){
		motor[DumpMotor] = dumpSpeed;
		motor[WheelMotor] = (wheelSpeed);
	}
	else if(vexRT[Btn5D] == 1 && vexRT[Btn6D] == 0 && vexRT[Btn6U] == 0)
		motor[DumpMotor] = (dumpSpeed * (-1));
	else{
		motor[DumpMotor] = 0;
	}
}

void ShootServo(){
	if(vexRT[Btn8U] == 1){
		if(servoShot == false) {
			servoShot = true;
		}
		else if(servoShot == true) {
			servoShot = false;
		}
	}

	if(servoShot == true) {
		motor[ShotServo] = maxServo;
	}
	else if (servoShot == false) {
		motor[ShotServo] = zeroServo;
	}
}

void Box(){
	if(vexRT[Btn8D] == 1)
		motor[boxServo] = maxServo;
	if(vexRT[Btn8L] == 1)
		motor[boxServo] = minServo;
}

task main(){
	while(true)
	{
		//Handle reverse controls
		ProcessReverse();
		//Wheel Control
		WheelControl();
		//Drive Control
		DriveControl();
		//Dump Control
		DumpControl();
		//Arm Control
		ArmControl();
		//Shoot the servo
		ShootServo();
		//Controls servo in front for calc box
		Box();
	}
}
