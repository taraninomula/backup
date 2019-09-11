//*********************************************************************
//* Header File specifiying the IOCTL Commands to set the seriel port * 
//* parity,baudrate,stp bits and char length                          *
//*********************************************************************
#define SERIAL_MAGIC_NUMBER 'g'

//--------------------------------------------------
//baud rate setting commands
//--------------------------------------------------
#define SET_BAUD_50	_IO(SERIAL_MAGIC_NUMBER,1)  
#define SET_BAUD_75	_IO(SERIAL_MAGIC_NUMBER,2)  
#define SET_BAUD_110	_IO(SERIAL_MAGIC_NUMBER,3) 
#define SET_BAUD_135	_IO(SERIAL_MAGIC_NUMBER,4) 
#define SET_BAUD_150	_IO(SERIAL_MAGIC_NUMBER,5) 
#define SET_BAUD_300	_IO(SERIAL_MAGIC_NUMBER,6) 
#define SET_BAUD_600	_IO(SERIAL_MAGIC_NUMBER,7) 
#define SET_BAUD_1200	_IO(SERIAL_MAGIC_NUMBER,8) 
#define SET_BAUD_1800	_IO(SERIAL_MAGIC_NUMBER,9) 
#define SET_BAUD_2000	_IO(SERIAL_MAGIC_NUMBER,10) 
#define SET_BAUD_2400	_IO(SERIAL_MAGIC_NUMBER,11) 
#define SET_BAUD_3600	_IO(SERIAL_MAGIC_NUMBER,12) 
#define SET_BAUD_4800	_IO(SERIAL_MAGIC_NUMBER,13) 
#define SET_BAUD_7200	_IO(SERIAL_MAGIC_NUMBER,14) 
#define SET_BAUD_9600 	_IO(SERIAL_MAGIC_NUMBER,15)
#define SET_BAUD_19200 	_IO(SERIAL_MAGIC_NUMBER,16)
#define SET_BAUD_38400 	_IO(SERIAL_MAGIC_NUMBER,17)
#define SET_BAUD_56000 	_IO(SERIAL_MAGIC_NUMBER,18)
#define SET_BAUD_128000	_IO(SERIAL_MAGIC_NUMBER,19) 
//---------------------------------------------------
//set parity bits
//---------------------------------------------------
#define SET_EVEN_PARITY _IO(SERIAL_MAGIC_NUMBER,20)
#define SET_ODD_PARITY  _IO(SERIAL_MAGIC_NUMBER,21)
#define SET_NO_PARITY   _IO(SERIAL_MAGIC_NUMBER,22)
//---------------------------------------------------
//set number of stop bits
//---------------------------------------------------
#define SET_STOP_BITS_AS_1 _IO(SERIAL_MAGIC_NUMBER,23)
#define SET_STOP_BITS_AS_2 _IO(SERIAL_MAGIC_NUMBER,24)
//---------------------------------------------------
//set charracter length
//----------------------------------------------------
#define SET_CHAR_LEN_AS_5 _IO(SERIAL_MAGIC_NUMBER,25)
#define SET_CHAR_LEN_AS_6 _IO(SERIAL_MAGIC_NUMBER,26)
#define SET_CHAR_LEN_AS_7 _IO(SERIAL_MAGIC_NUMBER,27)
#define SET_CHAR_LEN_AS_8 _IO(SERIAL_MAGIC_NUMBER,28)
//----------------------------------------------------
//enable interrupts
//----------------------------------------------------
#define ENABLE_INTERRUPTS   _IO(SERIAL_MAGIC_NUMBER,29)
#define DISABLE_INTERRUPTS  _IO(SERIAL_MAGIC_NUMBER,30)
//----------------------------------------------------





