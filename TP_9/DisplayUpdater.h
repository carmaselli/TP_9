#pragma once
#include <string>
#include "BasicLCD.h"
#include "Error.h"

class DisplayUpdater
{
public:
	
	DisplayUpdater(BasicLCD * display, int fps = 60);
	~DisplayUpdater();

	void setNewTweet(); // ver que formato de cosa recibe
	
	//alternativa a setTweet
	//void setFirstLine(string);
	//void setSecondLineContent(string);

	void incSpeed();
	void decSpeed();
	void repeatTweet();

	void refreshDisplay();

	void setWaiting(std::string accountName); // este seria para el principio
	void stillWaiting(void);// esta es la que va a ir moviendo la señal
	
	bool isOk(void);
	std::string getError();
	//    \|/-
private:

	int speed; //con 60FPS, cada cuantos FPS se refreshea
	int rRate; // cuantos FPS le faltan para volver a refrescar

	BasicLCD * lcd;

	std::string firstLine; // contenido de la primera linea
	std::string secondLine; // tweet a mostrar
	
	size_t secondLinePos; // posicion del tweet a partir de la cual estoy mostrando

	Error posibleErr;

	char state;
};

