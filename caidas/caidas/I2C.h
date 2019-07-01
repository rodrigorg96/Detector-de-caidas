/*
 * I2C.h
 *
 * Created: 26-Nov-18 2:59:25 AM
 *  Author: ahmed ayman
 */ 


#ifndef I2C_H_
#define I2C_H_
#define I2C_Basy() while (!(TWCR &(1<<TWINT)))
#define F_CPU 16000000UL
#define prescaler 4      // change here prescaler( 1 || 4 || 16 || 64)
#define F_SCL 400000    //change SCL frequency
#define slave_address     (0b10000000)  // select the address of slave

void I2C_Init(void);
void I2C_Start(void);
unsigned char I2C_Read(unsigned char ack);
void I2C_Stop(void);
void I2C_Write( unsigned char data);
void I2C_Init_Slave_Addr(void);
void I2C_Write_Addr(unsigned char direction) ;
void I2C_Slave_Read_addr(void);




#endif /* I2C_H_ */