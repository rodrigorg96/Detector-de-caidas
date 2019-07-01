/*
 * caidas.c
 *
 * Created: 25/06/2019 06:28:49 p. m.
 * Author : RodrigoRG
 */ 
#define F_CPU 16000000UL	//------>En este proyecto se usó un atmega328 el cual funciona a una frecuencia de 16MHz
#include <avr/io.h>			//************************************************************************//
#include <util/delay.h>		//************************************************************************//
#include <stdlib.h>			//***********************-----Librerias usadas-----***********************//
#include <string.h>			//************************************************************************//
#include <avr/interrupt.h>	//************************************************************************//
// -----> Clases creadas para su uso en el proyecto; la primera se utiliza para la comunicacion serial
#include "USART.h"			//------- funciona a 115200 bauds y con el microcontrolador a doble velocidad para la optima recepcion de mensajes
//------- por puerto serial

#include "ATs.h"			//esta clase solo facilita el uso de comandos AT
#include "I2C.h"
#include "mpu6050.h"
#include <avr/io.h>
#define I2cRead   1
#define I2cWrite  0
char valX_String[16]="";
char valY_String[16]="";
char valZ_String[16]="";
char valTotal[16]="";
unsigned int dato;
void mandarDato()
{
	ConexionServer();
	EnviarDato();
}
void mpu6050_init(void)
{
	_delay_ms(300);
	I2C_Start();
	I2C_Write(0xd0);
	I2C_Write(SMPLRT_DIV);
	I2C_Write(0x07);	//sampling rate 1khz
	I2C_Stop();

	I2C_Start();
	I2C_Write(0xd0);
	I2C_Write(PWR_MGMT_1);
	I2C_Write(0x00);   // x axises is reference or 0x00 internal clock
	I2C_Stop();
	
	I2C_Start();
	I2C_Write(0xd0);
	I2C_Write(GYRO_CONFIG);
	I2C_Write(0x18);
	I2C_Stop();

	I2C_Start();
	I2C_Write(0xd0);
	I2C_Write(ACCEL_CONFIG);
	I2C_Write(0x18);
	I2C_Stop();

}

unsigned short x_axis () // return accelerometer in x direction
{
	unsigned char x_low, x_high;
	I2C_Start();
	I2C_Write(0xd0);
	I2C_Write(ACCEL_XOUT_H);
	I2C_Start();
	I2C_Write(0xd1);
	x_high=I2C_Read(0);
	I2C_Stop();
	
	I2C_Start();
	I2C_Write(0xd0);
	I2C_Write(ACCEL_XOUT_L);
	I2C_Start();
	I2C_Write(0xd1);
	x_low=I2C_Read(0);
	I2C_Stop();
	
	return ((x_high<<8)|x_low)/16;
}
unsigned short y_axis ()		// return accelerometer in y direction
{
	unsigned char y_low,y_high;
	I2C_Start();
	I2C_Write(0xd0);
	I2C_Write(ACCEL_YOUT_H);
	I2C_Start();
	I2C_Write(0xd1);
	y_high=I2C_Read(0);
	I2C_Stop();
	
	I2C_Start();
	I2C_Write(0xd0);
	I2C_Write(ACCEL_YOUT_L);
	I2C_Start();
	I2C_Write(0xd1);
	y_low=I2C_Read(0);
	I2C_Stop();
	
	return ((y_high<<8)|y_low)/16;
	
}
unsigned short z_axis ()		//return aceleracion z
{
	unsigned char z_low,z_high;
	I2C_Start();
	I2C_Write(0xd0);
	I2C_Write(ACCEL_ZOUT_H);
	I2C_Start();
	I2C_Write(0xd1);
	z_high=I2C_Read(0);
	I2C_Stop();
	
	I2C_Start();
	I2C_Write(0xd0);
	I2C_Write(ACCEL_ZOUT_L);
	I2C_Start();
	I2C_Write(0xd1);
	z_low=I2C_Read(0);
	I2C_Stop();
	return ((z_high<<8)|z_low)/16;
	
}
int main(void)
{
	//DDRD|=(1<<PIND3);
	I2C_Init();
	mpu6050_init();
	iniciar_usart();
	
	unsigned short axsis_x,axsis_y,axsis_z;
	double suma=0.0;
	double raiz=0.0;
	/*
	
	_delay_ms(50);*/
	//PORTD|=(1<<PIND3);
    while (1) 
    {
		axsis_x = x_axis();
		axsis_y = y_axis();
		axsis_z = z_axis();
		
		suma=abs(axsis_x*axsis_x)+abs(axsis_y*axsis_y)+abs(axsis_z*axsis_z);
		
		raiz=sqrt(suma);
		
		itoa(axsis_x,valX_String,10);
		itoa(axsis_y,valY_String,10);
		itoa(axsis_z,valZ_String,10);
		
		itoa(raiz,valTotal,10);
		envia_cadena_usart(valTotal);
		envia_caracter_usart('|');
		
		itoa(axsis_z,valZ_String,10);
		envia_cadena_usart(valX_String);
		envia_caracter_usart(',');
		envia_cadena_usart(valY_String);
		envia_caracter_usart(',');
		envia_cadena_usart(valZ_String);
		envia_caracter_usart('\n');
		
    }
}

