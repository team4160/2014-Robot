#include "WPILib.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */ 
class RobotDemo : public SimpleRobot
{
	//DigitalInput limitSwitch;
	RobotDrive myRobot; // robot drive system
	Victor driveLeft;
	Victor driveRight; // only joystick
	Joystick stick1;
	Compressor *m_compressor;
	
public:
	RobotDemo():
		//limitSwitch = DigitalInput(2);
		myRobot(1,2),	// these must be initialized in the same order
		driveLeft(1), driveRight(2),
		stick1(1)		// as they are declared above.
	{
		myRobot.SetExpiration(0.1);
		m_compressor = new Compressor(1,1);
		m_compressor->Start();
	}
	// destructor
		~RobotDemo()
		{
			delete m_compressor;
		}
	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous()
	{
		myRobot.SetSafetyEnabled(false);
		myRobot.Drive(-0.5, 0.0); 	// drive forwards half speed
		Wait(2.0); 				//    for 2 seconds
		myRobot.Drive(0.0, 0.0); 	// stop robot
	}

	/**
	 * Runs the motors with arcade steering. 
	 */
	void OperatorControl()
	{
		myRobot.SetSafetyEnabled(true);
		driveLeft.Set(0,0);
		driveRight.Set(0,0);
		Solenoid *s[8];
			for (int i = 0; i < 8; i++)
			s[i] = new Solenoid(i + 1); // allocate the Solenoid objects
		while (IsOperatorControl())
		{
			myRobot.ArcadeDrive(stick1); // drive with arcade style (use right stick)
			driveLeft.Set(stick1.GetY());
			driveRight.Set(stick1.GetX());
			Wait(0.005);				// wait for a motor update time
			
			if (stick1.GetRawButton(5))
			{
				s[0]->Set(true);
				s[1]->Set(false);
			}
			else
			{
				s[0]->Set(false);
				s[1]->Set(true);
			}
			/*if (limitSwitch.get()){
				driveLeft.Set(1);
				driveRight.Set(1);
			}*/
			/*if (stick1.GetRawButton(5))
			{
				s[0]->Set(true);
			}
			else
			{
				s[0]->Set(false);
			}
			if(stick1.GetRawButton(6))
			{
				s[1]->Set(true);
			}
			else 
			{
				s[1]->Set(false);
			}*/
						/*
						Solenoid *s[8];
						for (int i = 0; i < 2; i++)
							s[i] = new Solenoid(i + 1); // allocate the Solenoid objects
						for (int i = 0; i < 2; i++)
						{
							s[i]->Set(true);            // turn them all on
						}
						//Wait(1.0);
						for (int i = 0; i < 2; i++)
						{
							s[i]->Set(false);           // turn them each off in turn
							Wait(1);
						}
						for (int i = 0; i < 2; i++)
						{
							s[i]->Set(true);            // turn them back on in turn
							Wait(1.0);
							delete s[i];                // delete the objects
						}*/
		}
	}
	
	/**
	 * Runs during test mode
	 */
	void Test()
	{

	}
};

START_ROBOT_CLASS(RobotDemo);
