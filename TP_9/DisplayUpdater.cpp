#include "DisplayUpdater.h"





DisplayUpdater::DisplayUpdater(BasicLCD * display, int fps)
{
	if (display->lcdInitOk())
	{
		lcd = display;
	}
	else
	{
		posibleErr.setErrType(ErrType::ALLEGRO_DISPLAY_ERROR);
		posibleErr.setErrDetail("No se pudio acceder al display\n");
	}
	speed = fps/2; //depende de los fps, inicialmente es dos veces por segundo (capaz es mucho)
	rRate = speed;
	state = 0;
}


DisplayUpdater::~DisplayUpdater()
{
}

void DisplayUpdater::incSpeed()
{
	speed++;
}

void DisplayUpdater::decSpeed()
{
	if (speed > 1) // no puedo tener menos velocidad
	{
		speed--;
	}
}

void DisplayUpdater::repeatTweet()
{
	secondLinePos = 0; // reseteo el cursor
	rRate = speed;
}

void DisplayUpdater::refreshDisplay()
{
	if (rRate - 1 == 0) // me fijo si el contador llego a 0
	{
		lcd->lcdClear(); //limprio el display
		lcd->operator<<((const unsigned char *)firstLine.c_str()); // imprimo la fecha
		std::string temp(secondLine.substr(secondLinePos, 16)); //agarro 16 caracteres
		lcd->operator<< ((const unsigned char *)temp.c_str());
		secondLinePos++;
		rRate = speed;
	}
	else
		rRate--;

}

void DisplayUpdater::setWaiting(std::string accountName)
{
	size_t length = accountName.length();
	lcd->lcdClear();
	for (size_t i = 0; i < (16 - length) / 2; i++) // para mostrar el nombre centrado
	{
		lcd->lcdMoveCursorRight();
	}
	lcd->operator<<((const unsigned char *)accountName.c_str());
}

void DisplayUpdater::stillWaiting(void)
{
	cursorPosition cur = { 2,0 };
	if (rRate == 1)
	{
		lcd->lcdSetCursorPosition(cur);
		lcd->lcdClearToEOL();
		switch (state)
		{
		case 0:
			lcd->operator<<((const unsigned char *) "   Waiting");
			state++;
			break;
		case 1:
			lcd->operator<<((const unsigned char *) "   Waiting.");
			state++;
			break;
		case 2:
			lcd->operator<<((const unsigned char *) "   Waiting..");
			state++;
			break;
		case 3:
			lcd->operator<<((const unsigned char *) "   Waiting...");
			state = 0;
			break;
		default:
			lcd->operator<<((const unsigned char *) "I shdnt be here");
			state = 0;
			break;
		}
		rRate = speed;
	}
	else
		rRate--;
	
}

bool DisplayUpdater::isOk()
{
	if (posibleErr.getErrType != ErrType::NO_ERROR)
	{
		return false;
	}
	else
		return true;
}

std::string DisplayUpdater::getError()
{
	return posibleErr.getErrDetail();
}
