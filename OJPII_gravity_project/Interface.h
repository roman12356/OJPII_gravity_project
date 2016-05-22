#ifndef INTERFACE_H
#define INTERFACE_H

//#include "Header.h"
#include "Display_Water.h"
#include "Display_Throw.h"


class _Interface
{
	friend class _Init;
private:
	_Display_Main Display_Main;
	_Display_Water Display_Water;
	_Display_Throw Display_Throw;

public:
	void Theatre()
	{
		switch (Actual_Interface.Get_Interface())
		{
		case E_INTER_MAIN:
			Display_Main.Theatre();
			break;

		case E_INTER_WATER_MENU: case E_INTER_WATER_COUNT: case E_INTER_WATER_THEATRE:
			 Display_Water.Theatre();
			break;

		case E_INTER_THROW_MENU: case E_INTER_THROW_COUNT: case E_INTER_THROW_THEATRE:
			Display_Throw.Theatre();
			break;


		default:
			std::cout << "Nothing yet...\n";
			Actual_Interface.Enum_Interface = E_INTER_MAIN;
			break;
		}
	}
};










#endif