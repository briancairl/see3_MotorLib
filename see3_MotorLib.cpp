/// @file 	see3_MotorLib.cpp
///	@brief	A library for controlling DC-motors from the Seethreeno's on-board i2c-motor controller.
///			Wire.h MUST be included in a sketch using this library. The Arduino IDE handles header
///			files in a rather strange way. 
///
/// @todo	
///	@{	
///		- Ramp-up control functions?
///		- Wire.h include work-around?
///	@}
#include <Arduino.h>

#include "see3_MotorLib.h"

#include <Wire.h>


/// @ingroup PCA_ChipDefinitions
/// @{
#define PCA_ADDR 		0x62
#define PCA_MODE1      	0x00
#define PCA_MODE2      	0x01
#define PCA_PWM0       	0x02
#define PCA_PWM1       	0x03
#define PCA_PWM2       	0x04
#define PCA_PWM3       	0x05
#define PCA_GRPPWM     	0x06
#define PCA_GRPFREQ    	0x07
#define PCA_LEDOUT     	0x08

 
/// @brief 	Writes to a register on the PCA LED-Driver (PWM) chip
///			This should not be exposed as user code. Helper function only.
///
///	@param 	reg		PCA register address
///	@param 	data	PCA register data
void PCA_WriteRegister(unsigned char  reg, unsigned char  data)
{
	//Begin all transmission at address
	Wire.beginTransmission(PCA_ADDR);

	//Write at register data
	Wire.write(reg);
	Wire.write(data);

	//Stop all transmission
	Wire.endTransmission();
} 
/// @}



/// @brief	Enables motor control
///			***
///			This function must be called before any other associated function
///			as it is responsible for waking up the I2C bus and initializing the
///			PCA PWM unit 
//			***
void see3_MotorInit()
{
	Wire.begin();
	PCA_WriteRegister(PCA_MODE1, 0x00);
}




/// @brief	Controls the selected motor, only. Other motor disengaged.
///	@param 	m_tag 		Tag associated with the motor intended to be controlled
/// @param 	level		Level associated with the speed of the motor. This value
///						should be a decimal number between -1 (full reverse) and 
///						1 (full forward). At 0, the motor will be completely stopped.
void see3_MotorControl( see3_MotorTag m_tag, float level )
{
	if( abs(level)>1.0f || m_tag > 2UL )
		return;
		
	unsigned char level_b = (unsigned char)(((level+1.0f)/2.0f)*255UL);

	switch(m_tag)
	{
		case Motor1:
			PCA_WriteRegister(PCA_PWM0, 	    level_b); 
			PCA_WriteRegister(PCA_PWM1,        ~level_b);
			PCA_WriteRegister(PCA_LEDOUT, 	(0xAA^0xF0));
			break;
		case Motor2:
			PCA_WriteRegister(PCA_PWM2, 	    level_b);
			PCA_WriteRegister(PCA_PWM3,    	   ~level_b);
			PCA_WriteRegister(PCA_LEDOUT,	(0xAA^0x0F));
			break;	
			
		default:
			break;
	}
}




/// @brief	Controls both motors
///	@param 	m_tag 		Tag associated with the motor intended to be controlled
/// @param 	m1_level	Level associated with the speed of the motor 1. This value
///						should be a decimal number between -1 (full reverse) and 
///						1 (full forward). At 0, the motor will be completely stopped.
/// @param 	m2_level	Level associated with the speed of the motor 2. This value
///						should be a decimal number between -1 (full reverse) and 
///						1 (full forward). At 0, the motor will be completely stopped.
void see3_DualMotorControl( float m1_level, float m2_level )
{
	if( abs(m1_level)>1.0f || abs(m2_level)>1.0f )
		return;
		
	unsigned char m1_level_b = (unsigned char)(((m1_level+1.0f)/2.0f)*255UL);
	unsigned char m2_level_b = (unsigned char)(((m2_level+1.0f)/2.0f)*255UL);

	PCA_WriteRegister(PCA_PWM0, 	m1_level_b); 
	PCA_WriteRegister(PCA_PWM1,    ~m1_level_b);
	PCA_WriteRegister(PCA_PWM2, 	m2_level_b); 
	PCA_WriteRegister(PCA_PWM3,    ~m2_level_b);
	PCA_WriteRegister(PCA_LEDOUT,  (0xAA^0x00));
}