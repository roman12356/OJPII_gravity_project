#ifndef HEDAER_H
#define HEDAER_H

#include <iostream>
#include <string>

int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600;


#include <SDL.h>
#include <SDL_events.h>
#include <gl/glew.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
//#include <stdlib.h>
//#include <stdbool.h>
#include <math.h>

SDL_Event ev;

enum _Enum_Interface
{
	E_INTER_MAIN,
	E_INTER_WATER_MENU,
	E_INTER_WATER_COUNT,
	E_INTER_WATER_THEATRE,
	E_INTER_THROW_MENU,
	E_INTER_THROW_COUNT,
	E_INTER_THROW_THEATRE,
	E_INTER_TOTAL
};

class _Actual_Interface
{
	friend class _Interface;
	friend class _Inheritance_Display;
	friend class _Display_Main;
	friend class _Display_Water;
	friend class _Init;// Window(_Enum_Interface e_);
private:
	_Enum_Interface Enum_Interface;

	//void Set_Interface(_Enum_Interface e_)
	//{
	//	Enum_Interface = e_;
	//}

public:

	_Actual_Interface()
	{
		Enum_Interface = E_INTER_MAIN;
	}

	_Enum_Interface Get_Interface()
	{
		return Enum_Interface;
	}

};
_Actual_Interface Actual_Interface;

#include "Init.h"
#include "Globals.h"
#include "Inheritance_Display.h"
#include "Display_Main.h"
#include "Display_Water.h"
#include "Interface.h"




#endif