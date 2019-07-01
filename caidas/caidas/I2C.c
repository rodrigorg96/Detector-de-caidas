/*
 * I2C.c
 *
 * Created: 26-Nov-18 2:59:04 AM
 *  Author: ahmed
 */ 
#include "I2C.h"
#include <avr/io.h>

void I2C_Init_Slave_Addr(void) // Function to initialization slave
{
	TWAR=slave_address;    //  slave address
}

void I2C_Init(void)  // for master receiver mode
{
	if (prescaler==1)
	TWSR = (0<<TWPS0)|(0<<TWPS1);
	else if (prescaler==4)
	TWSR = (1<<TWPS0) | (0<<TWPS1);
	else if (prescaler==16)
	TWSR = (0<<TWPS0) | (1<<TWPS1);
	else if (prescaler==64)
	TWSR = (1<<TWPS0) | (1<<TWPS1);
	TWBR=(((F_CPU/F_SCL)-16)/2*prescaler);
}

void I2C_Start(void)
{
	TWCR = (1<<TWINT)         //clear flag
	|(1<<TWEN)  	      //generate start condition
	|(1<<TWSTA);         //enable TWI
	I2C_Basy();
	//while(!(TWSR == 0x08));  // start condition has been transmitted
}

void I2C_Write_Addr(unsigned char direction)   //transfered  (address+ direction(R|W))
{
	TWDR = slave_address + direction ;
	TWCR = (1<<TWINT)|(1<<TWEN);
	 I2C_Basy();    //check For Current job

}

void I2C_Write(unsigned char data)    //transfered  (address+ direction(R|W))
{
	TWDR = data ;
	TWCR = (1<<TWINT)|(1<<TWEN);
	I2C_Basy();               //check For Current job

}

void I2C_Slave_Read_addr(void)
{
	TWCR= (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	I2C_Basy();	
}
unsigned char I2C_Read(unsigned char ack)
{
	if (ack==0)
	{
	TWCR= (1<<TWINT)|(1<<TWEN);
	}
	else
	TWCR= (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	I2C_Basy();
	return TWDR ;
}


void I2C_Stop(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

