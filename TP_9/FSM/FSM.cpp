#include "FSM.h"

TwitterFSM::TwitterFSM()
{
	(*this).initiate();
	(*this).process_event(StartEvent());
	//guardar todos los punteros
}

