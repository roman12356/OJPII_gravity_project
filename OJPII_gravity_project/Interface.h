#ifndef INTERFACE_H
#define INTERFACE_H

//#include "Header.h"
#include "Display_Water.h"


class _Interface
{
	friend class _Init;
private:
	_Inheritance_Display *wsk;
	_Display_Main Display_Main;
	_Display_Water Display_Water;

public:
	void Theatre(_Inheritance_Display *Display_wsk)
	{
		switch (Actual_Interface.Get_Interface())
		{
		case E_INTER_MAIN:
			Display_Main.Theatre();
			//wsk = &(this->Display_Main);
			//Display_wsk = wsk;
			//Display_wsk->Events();

			break;

		case E_INTER_WATER_MENU:
			 Display_Water.Theatre();
			 //Display_wsk = &(this->Display_Water);
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