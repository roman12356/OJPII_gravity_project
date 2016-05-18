#ifndef INTERFACE_H
#define INTERFACE_H

//#include "Header.h"
#include "Display_Water.h"

class _Interface
{
private:

	_Display_Main Display_Main;
	_Display_Water Display_Water;

public:
	void Theatre()
	{
		switch (Actual_Interface.Get_Interface())
		{
		case E_INTER_MAIN:
			Display_Main.Theatre();
			break;

		case E_INTER_WATER_MENU:
			 Display_Water.Theatre();
			//std::cout << "Display_Water...\n";
			//Actual_Interface.Enum_Interface = E_INTER_MAIN;
			break;

		default:
			std::cout << "Nothing yet...\n";
			Actual_Interface.Enum_Interface = E_INTER_MAIN;
			break;
		}
	}
};










#endif