/*
 * "Pololu Maestro Servo Controller" - Linux Kernel Driver Module Definitions
 *
 * Copyright (C) 2013-2014 Roosemberth Palacios <roosemberth@roosemberth.usr.sh>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, version 2.
 *
 * derived from Pololu Corporation's "Maestro Servo Controller Linux Software" and "Pololu USB SDK"
 * Copyright (C) 2001-2013 Pololu Corporation <support@pololu.com>
 *
 */

struct ControlTransferDescriptor{
	char 			RequestType;
	char 			Request;
	unsigned short	Value;
	unsigned short	Index;
	void *			Data;
	unsigned short	Lenght;
};

struct MaestroHwDescriptor{			// Can be read using REQUEST_GET_VARIABLES
    unsigned char 	StackPointer;	// The number of values on the data stack (0-32). 0 means the stack is empty
    unsigned char 	CallStackPointer;	// The number of return locations on the call stack (0-10). 0 means is empty
    unsigned short 	Errors;			// Each bit stands for a different error
    unsigned short 	ProgramCounter;	// The address (in bytes) of the next bytecode instruction that will be executed
    unsigned short 	Buffer[3];		// Micro Maestro: Meaningless bytes to protect the program from stack underflows
    unsigned short 	Stack[32];		// Micro Maestro: The data stack used by the script.
    								// -> The values in locations 0 through stackPointer-1 are here
    unsigned short 	CallStack[10];	// Micro Maestro: The call stack used by the script.
    								// -> The addresses in locations 0 through callStackPointer-1 are on the call stack
    								// -> The next return will make the program counter go to callStack[callStackPointer-1]
    unsigned char 	ScriptDone;		// 0 = Running, 1 = Done, 2 = Will be done after execution of one more instruction.
    unsigned char 	Buffer2;		// Micro Maestro: Meaningless bytes to protect the program from stack underflows
    unsigned char 	PerformanceFlags;
};

struct MaestroChDescriptor{
    unsigned char 	Channel;		// Channel Number
    char			Name[16];		// Channel Name
    unsigned char 	Mode;			// Type (Servo, Output, Input, PWM).
    bool			Enabled;		// True/False
    unsigned char 	HomeMode;		// HomeType (off, ignore, goto)
    unsigned short 	Home;			// Position at Startup (units of 0.25 us, but stored on the device in units of 16 us)
    unsigned short 	Min;			// Minimum (units of 0.25 us, but stored on the device in units of 16 us)
    unsigned short 	Max;			// Maxumum (units of 0.25 us, but stored on the device in units of 16 us)
    unsigned short 	Center;			// The Center of the 8-bit Set Target Command (Value @127) in units of 0.25us
    unsigned short 	Range;			// 8-bit(254) = Center+Range, 8-bit(0) = Center-Range
// Servo Mode, Servo Status Layout
    unsigned short	Position;
    unsigned short	Target;
    unsigned short 	Speed;
    unsigned char 	Acceleration;
// ServoMultiplied Mode

// PWM Mode
    unsigned char 	PWM_DutyCycle;
    unsigned int 	PWM_Period;
// Input Mode
    bool			InputValue;
};

struct MaestroModeDescriptor{
	// The number of Chs available, ServosPerPorts, this and ServoPeriod, determine the "maximum maximum PWM".
    unsigned char 	ServosPerPorts;

    unsigned char 	MicroMaestroServoPeriod;
    unsigned int 	MiniMaestroServoPeriod;
    unsigned int 	MiniMaestroServoMultiplier;
    unsigned char 	SerialMode;
    unsigned int 	FixedBaudRate;
    bool 			CRC;
    bool 			NeverSuspend;
    unsigned char 	SerialDeviceNumber;
    unsigned char 	MiniMaestroSSCOffset;
    unsigned short 	SerialTimeout;
    bool 			ScriptDone;
    bool 			EnablePullUps;
    bool 			ScriptInconsistent;
};

struct MaestroDescriptor {
    struct MaestroModeDescriptor 	ModeDescriptor;
    struct MaestroChDescriptor 		ChDescriptors[24];	// XXX: [Optional] Picking 24 as the highest possibility
    struct MaestroHwDescriptor 		HwDescriptor;
};

/* TODO:[Relevant] Catch up later */
#define USB_CTRL_STD_INCOMING_REQ_TYPE		0x80 	// 10000000b
#define USB_CTRL_TRANSF_MAX_BUFFER_SIZE		0xff	// Max Control Transfer wLength Field Value
#define MAESTRO_CTRL_INTERFACE				0x05	// Transmit to 5th Interface (USB 2.0 Spec, Page 249)

/* Maestro Control Transfer bRequest */
#define MAESTRO_CONTROL_OUTGOING_REQ_TYPE	0x40	// 01000000b
#define MAESTRO_CONTROL_INCOMING_REQ_TYPE	0xC0	// 11000000b

/* [USB] Request Values for a Control Transfer Setup Packet */
enum MaestroRequestSetupPacket{
	REQUEST_COMPLEX							= 0x00,	// Not a Maestro bRequest, used to handle "Other" Requests
    REQUEST_GET_PARAMETER 					= 0x81,
    REQUEST_SET_PARAMETER 					= 0x82,
    REQUEST_GET_VARIABLES 					= 0x83,
    REQUEST_SET_SERVO_VARIABLE 				= 0x84,	// (also clears the serial timeout timer)
    REQUEST_SET_TARGET 						= 0x85,	// (also clears the serial timeout timer)
    REQUEST_CLEAR_ERRORS 					= 0x86,	// (also clears the serial timeout timer)
    REQUEST_GET_SERVO_SETTINGS 				= 0x87,
	REQUEST_GET_STACK 						= 0x88,	// Only used on the mini maestro
    REQUEST_GET_CALL_STACK 					= 0x89,	// Only used on the mini maestro
    REQUEST_SET_PWM 						= 0x8A,
    REQUEST_REINITIALIZE 					= 0x90,
    REQUEST_ERASE_SCRIPT 					= 0xA0,
    REQUEST_WRITE_SCRIPT 					= 0xA1,
    REQUEST_SET_SCRIPT_DONE 				= 0xA2,	// value.low.b is 0 for go, 1 for stop, 2 for single-step
    REQUEST_RESTART_SCRIPT_AT_SUBROUTINE	= 0xA3,
    REQUEST_RESTART_SCRIPT_AT_SUBROUTINE_WITH_PARAMETER = 0xA4,
    REQUEST_RESTART_SCRIPT 					= 0xA5,
    REQUEST_START_BOOTLOADER 				= 0xFF,
};

/* Bytes for Refering to Particular Parameters */

enum MaestroParameters{
    PARAMETER_INITIALIZED 					= 0,  // 1 byte - 0 or 0xFF
    PARAMETER_SERVOS_AVAILABLE 				= 1,  // 1 byte - 0-5
    PARAMETER_SERVO_PERIOD 					= 2,  // 1 byte - ticks allocated to each servo/256
    PARAMETER_SERIAL_MODE 					= 3,  // 1 byte unsigned value Valid values are SERIAL_MODE_* Init variable
    PARAMETER_SERIAL_FIXED_BAUD_RATE 		= 4,  // 2-byte unsigned value; 0 means autodetect.  Init parameter.
    PARAMETER_SERIAL_TIMEOUT 				= 6,  // 2-byte unsigned value
    PARAMETER_SERIAL_ENABLE_CRC 			= 8,  // 1 byte boolean value
    PARAMETER_SERIAL_NEVER_SUSPEND 			= 9,  // 1 byte boolean value
    PARAMETER_SERIAL_DEVICE_NUMBER 			= 10, // 1 byte unsigned value, 0-127
    PARAMETER_SERIAL_BAUD_DETECT_TYPE 		= 11, // 1 byte value

    PARAMETER_IO_MASK_C						= 16, // 1 byte - pins used for I/O instead of servo
    PARAMETER_OUTPUT_MASK_C 				= 17, // 1 byte - outputs that are enabled

    PARAMETER_CHANNEL_MODES_0_3             = 12, // 1 byte - channel modes 0-3
    PARAMETER_CHANNEL_MODES_4_7             = 13, // 1 byte - channel modes 4-7
    PARAMETER_CHANNEL_MODES_8_11            = 14, // 1 byte - channel modes 8-11
    PARAMETER_CHANNEL_MODES_12_15 			= 15, // 1 byte - channel modes 12-15
    PARAMETER_CHANNEL_MODES_16_19 			= 16, // 1 byte - channel modes 16-19
    PARAMETER_CHANNEL_MODES_20_23 			= 17, // 1 byte - channel modes 20-23
    PARAMETER_MINI_MAESTRO_SERVO_PERIOD_L 	= 18, // servo period: 3-byte unsigned values, units of quarter microseconds
    PARAMETER_MINI_MAESTRO_SERVO_PERIOD_HU 	= 19,
    PARAMETER_ENABLE_PULLUPS 				= 21, // 1 byte: 0 or 1
    PARAMETER_SCRIPT_CRC 					= 22, // 2 bytes - stores a checksum of the bytecode program, for comparison
    PARAMETER_SCRIPT_DONE 					= 24, // 1 byte - copied to scriptDone on startup
    PARAMETER_SERIAL_MINI_SSC_OFFSET 		= 25, // 1 byte (0-254)
    PARAMETER_SERVO_MULTIPLIER 				= 26, // 1 byte (0-255)
    // 9 * 24 = 216, so we can safely start at 30 - Pololu Corporation's Note
    PARAMETER_SERVO0_HOME 					= 30, // 2 byte home position (0=off; 1=ignore)
    PARAMETER_SERVO0_MIN 					= 32, // 1 byte min allowed value (x2^6)
    PARAMETER_SERVO0_MAX 					= 33, // 1 byte max allowed value (x2^6)
    PARAMETER_SERVO0_NEUTRAL 				= 34, // 2 byte neutral position
    PARAMETER_SERVO0_RANGE 					= 36, // 1 byte range
    PARAMETER_SERVO0_SPEED 					= 37, // 1 byte (5 mantissa,3 exponent) us per 10ms
    PARAMETER_SERVO0_ACCELERATION 			= 38, // 1 byte (speed changes that much every 10ms)
    PARAMETER_SERVO1_HOME 					= 39, // 2 byte home position (0=off; 1=ignore)
    PARAMETER_SERVO1_MIN 					= 41, // 1 byte min allowed value (x2^6)
    PARAMETER_SERVO1_MAX 					= 42, // 1 byte max allowed value (x2^6)
    PARAMETER_SERVO1_NEUTRAL 				= 43, // 2 byte neutral position
    PARAMETER_SERVO1_RANGE 					= 45, // 1 byte range
    PARAMETER_SERVO1_SPEED 					= 46, // 1 byte (5 mantissa,3 exponent) us per 10ms
    PARAMETER_SERVO1_ACCELERATION 			= 47, // 1 byte (speed changes that much every 10ms)
    PARAMETER_SERVO2_HOME 					= 48, // 2 byte home position (0=off; 1=ignore)
    PARAMETER_SERVO2_MIN 					= 50, // 1 byte min allowed value (x2^6)
    PARAMETER_SERVO2_MAX 					= 51, // 1 byte max allowed value (x2^6)
    PARAMETER_SERVO2_NEUTRAL 				= 52, // 2 byte neutral position
    PARAMETER_SERVO2_RANGE 					= 54, // 1 byte range
    PARAMETER_SERVO2_SPEED 					= 55, // 1 byte (5 mantissa,3 exponent) us per 10ms
    PARAMETER_SERVO2_ACCELERATION 			= 56, // 1 byte (speed changes that much every 10ms)
    PARAMETER_SERVO3_HOME 					= 57, // 2 byte home position (0=off; 1=ignore)
    PARAMETER_SERVO3_MIN 					= 59, // 1 byte min allowed value (x2^6)
    PARAMETER_SERVO3_MAX 					= 60, // 1 byte max allowed value (x2^6)
    PARAMETER_SERVO3_NEUTRAL 				= 61, // 2 byte neutral position
    PARAMETER_SERVO3_RANGE 					= 63, // 1 byte range
    PARAMETER_SERVO3_SPEED 					= 64, // 1 byte (5 mantissa,3 exponent) us per 10ms
    PARAMETER_SERVO3_ACCELERATION 			= 65, // 1 byte (speed changes that much every 10ms)
    PARAMETER_SERVO4_HOME 					= 66, // 2 byte home position (0=off; 1=ignore)
    PARAMETER_SERVO4_MIN 					= 68, // 1 byte min allowed value (x2^6)
    PARAMETER_SERVO4_MAX 					= 69, // 1 byte max allowed value (x2^6)
    PARAMETER_SERVO4_NEUTRAL 				= 70, // 2 byte neutral position
    PARAMETER_SERVO4_RANGE 					= 72, // 1 byte range
    PARAMETER_SERVO4_SPEED 					= 73, // 1 byte (5 mantissa,3 exponent) us per 10ms
    PARAMETER_SERVO4_ACCELERATION 			= 74, // 1 byte (speed changes that much every 10ms)
    PARAMETER_SERVO5_HOME 					= 75, // 2 byte home position (0=off; 1=ignore)
    PARAMETER_SERVO5_MIN 					= 77, // 1 byte min allowed value (x2^6)
    PARAMETER_SERVO5_MAX 					= 78, // 1 byte max allowed value (x2^6)
    PARAMETER_SERVO5_NEUTRAL 				= 79, // 2 byte neutral position
    PARAMETER_SERVO5_RANGE 					= 81, // 1 byte range
    PARAMETER_SERVO5_SPEED 					= 82, // 1 byte (5 mantissa,3 exponent) us per 10ms
    PARAMETER_SERVO5_ACCELERATION 			= 83, // 1 byte (speed changes that much every 10ms)
};

/* Serial Mode Definitions */
enum MaestroSerialMode{
    SERIAL_MODE_USB_DUAL_PORT 				= 0, // TTL port/UART are connected to make a USB-to-serial adapter
    SERIAL_MODE_USB_CHAINED 				= 1, // Send commands to Maestro and receive bytes from UART RX Line
    SERIAL_MODE_UART_DETECT_BAUD_RATE 		= 2,
    SERIAL_MODE_UART_FIXED_BAUD_RATE 		= 3, // Command Port recieves bytes from RX Line
};

/* Error Definitions */
enum MaestroErrors{
    ERROR_SERIAL_SIGNAL 			= 0,
    ERROR_SERIAL_OVERRUN 			= 1,
    ERROR_SERIAL_BUFFER_FULL 		= 2,
    ERROR_SERIAL_CRC 				= 3,
    ERROR_SERIAL_PROTOCOL 			= 4,
    ERROR_SERIAL_TIMEOUT 			= 5,
    ERROR_SCRIPT_STACK 				= 6,
    ERROR_SCRIPT_CALL_STACK 		= 7,
    ERROR_SCRIPT_PROGRAM_COUNTER 	= 8,
};

/* Performance Flags Definitions */
enum MaestroPerformanceFlags{
    PERROR_ADVANCED_UPDATE 			= 0,
    PERROR_BASIC_UPDATE 			= 1,
    PERROR_PERIOD 					= 2
};
