/*
 * USART.h
 *
 * Created: 14/10/2018 06:21:56 p. m.
 *  Author: RodrigoRG
 */ 


#ifndef USART_H_
#define USART_H_


void iniciar_usart(){
	DDRD |= (1<<1);							//PD1	COMO SALIDA TXa
	DDRD &= ~(1<<0);						//PD0	COMO ENTRADA RX
	//UCSR0B = (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0);	//Se activa la RX por medio de interrupcion, tambien la TX y RX
	UCSR0B =(1<<RXEN0)|(1<<TXEN0);
	//UCSR0A =(1<<U2X0);						//Velocidad x2
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);		//Datos 8 bits
	//UBRR0 = 16;								//115200 baudios para x2
	UBRR0=103;
}


unsigned char recibe_caracter_usart(){
	while(!(UCSR0A&(1<<RXC0)));  //si el bit7 del registro UCSR0A se ha puesto a 1
		return (UDR0);    //devuelve el dato almacenado en el registro UDR0
	
}

//transmisión de datos del módulo USART AVR modo asíncrono

void envia_caracter_usart(unsigned char caracter){
	while(!(UCSR0A&(1<<5)));    // mientras el registro UDR0 esté lleno espera
	UDR0 = caracter;            //cuando el el registro UDR0 está vacio se envia el caracter
}


//transmisión de cadenas de caracteres con el módulo USART AVR modo asíncrono
void envia_cadena_usart(char* cadena){	 //cadena de caracteres de tipo char
	while(*cadena !=0x00){				//mientras el último valor de la cadena sea diferente
										//a el caracter nulo
		envia_caracter_usart(*cadena);	//transmite los caracteres de cadena
		cadena++;						//incrementa la ubicación de los caracteres en cadena
											//para enviar el siguiente caracter de cadena
	}
}


#endif /* USART_H_ */