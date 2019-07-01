/*
 * ATs.h
 *
 * Created: 28/10/2018 07:18:07 p. m.
 *  Author: RodrigoRG
 *
 * CONEXION: 10 2D 00 06 4D 51 49 73 64 70 03 C2 00 3C 00 07 52 6F 64 72 69 67 6F 00 08 68 6D 63 7A 72 74 76 67 00 0C 67 42 68 76 71 35 61 32 56 69 37 39
 * Publish:  30 0E 00 07 73 65 69 73 61 69 31 45 78 69 74 6F
 */ 


#ifndef ATS_H_
#define ATS_H_
void enviarAT() //comprueba el estado del modulo
{
	envia_cadena_usart("AT");
	envia_caracter_usart(13);//enter
	envia_caracter_usart('\n');//jump line
	_delay_ms(1000);
	envia_cadena_usart("AT");
	envia_caracter_usart(13);//enter
	envia_caracter_usart('\n');//jump line
	_delay_ms(3000);
}
//Mi sevidor
void ConexionServer() //Establece conexion entre el modulo y el broker en linea
{
	envia_cadena_usart("AT+CIPSTART=");
	envia_caracter_usart(34); //comillas
	envia_cadena_usart("TCP");
	envia_caracter_usart(34); //comillas
	envia_caracter_usart(44); //coma
	envia_caracter_usart(34); //comillas
	envia_cadena_usart("caidas.atwebpages.com");
	envia_caracter_usart(34); //comillas
	envia_caracter_usart(44); //coma
	envia_cadena_usart("80");
	envia_caracter_usart(13);//enter
	envia_caracter_usart('\n');//jump line
	_delay_ms(3000);
}

//Mi servidor
void EnviarDato()
{
	envia_cadena_usart("AT+CIPSEND=72");
	envia_caracter_usart(13);//enter
	envia_caracter_usart('\n');//jump line
	_delay_ms(1000);
	envia_cadena_usart("GET /ActualizarBD.php?Estado=1 HTTP/1.1\r\nHost: caidas.atwebpages.com\r\n\r\n");
	_delay_ms(2000);
}


void desconectar()//se desconecta del broker en linea
{
	envia_cadena_usart("AT+CIPCLOSE");
	envia_caracter_usart(13);//enter
	envia_caracter_usart('\n');//jump line
	_delay_ms(1000);
}
void echoOff()
{
	envia_cadena_usart("ATE0"); //Desactiva el echo
	envia_caracter_usart(13);//enter
	envia_caracter_usart('\n');//jump line
	_delay_ms(500);

}
void echoOn()
{
	envia_cadena_usart("ATE1"); //Activa el echo
	envia_caracter_usart(13);//enter
	envia_caracter_usart('\n');//jump line

}
void StationMode()
{
	envia_cadena_usart("AT+CWMODE=1");	
	envia_caracter_usart(13);//enter
	envia_caracter_usart('\n');//jump line
}
void AccesPointMode()
{
	envia_cadena_usart("AT+CWMODE=2");	//
	envia_caracter_usart(13);//enter
	envia_caracter_usart('\n');//jump line
}

void ConectarWIFI()
{
	envia_cadena_usart("AT+CWJAP=\"INFINITUM19787B\",\"39ECDB1CAC\"");
	envia_caracter_usart(13);//enter
	envia_caracter_usart('\n');//jump line
	
}

#endif /* ATS_H_ */