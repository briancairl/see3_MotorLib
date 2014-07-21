/// @file 	see3_MotorLib.h
///	@brief	A library for controlling DC-motors from the Seethreeno's on-board I2C-motor controller.
///			Wire.h MUST be included in a sketch using this library. The Arduino IDE handles header
///			files in a rather strange way. 
///			
///	@author Brian Cairl
/// @date 	03/23/2014 (rev1)
#ifndef SEE3_MOTORLIB_H
#define SEE3_MOTORLIB_H
	

	/// @brief Motor enumeration for specifing which motor is being controlled
	typedef enum __see3_MotorTag
	{
		Motor1,
		Motor2
	} see3_MotorTag;
	
	
	/// @brief 	Initializes the motor controller peripheral device on the I2C bus
	///			Must be called before using control functions.
	/// @return NONE
	void see3_MotorInit();
	


	/// @brief 	Controls a single motor channel, speicified by its respetive tag.
	/// @param 	m_tag	Motor tag (@see see3_MotorTag)
	///	@param 	level 	Sets the relative velocity of the motor; restricted between {-1 and +1}
	///					where +1 is maximum forward velocity and -1 is maximum reverse velocity.
	///					Commands outside of this range are clipped.
	///	@return NONE
	void see3_MotorControl( see3_MotorTag m_tag, float level );
	


	///	@brief 	Controls both motor channels simultaneously.
	///	@param 	m1_level	Sets the relative velocity of motor 1; restricted between {-1 and +1}
	///						where +1 is maximum forward velocity and -1 is maximum reverse velocity.
	///						Commands outside of this range are clipped.
	///	@param 	m2_level	Sets the relative velocity of motor 2; restricted between {-1 and +1}
	///						where +1 is maximum forward velocity and -1 is maximum reverse velocity.
	///						Commands outside of this range are clipped.
	///	@return NONE
	void see3_DualMotorControl( float m1_level, float m2_level );


#endif