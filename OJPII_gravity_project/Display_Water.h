#ifndef DISPLAY_WATER_H
#define DISPLAY_WATER_H

#include "Init.h"
#include "Inheritance_Display.h"
#include <sstream>  
#include <vector>

enum _E_DISP_WATER
{
	E_DISP_WATER_SURFACE,
	E_DISP_WATER_BACK,
	E_DISP_WATER_GLASS,
	E_DISP_WATER_TOTAL
};

enum _E_DISP_WATER_ADD
{
	E_DISP_WATER_AD_CM,
	//E_DISP_WATER_AD_CM2,
	E_DISP_WATER_AD_POWROT,
	E_DISP_WATER_AD_SLOWMO_TRUE,
	E_DISP_WATER_AD_SLOWMO_FALSE,
	E_DISP_WATER_AD_RANGE,
	E_DISP_WATER_AD_START,
	E_DISP_WATER_AD_TOTAL
};

enum _E_ACTIVE_FIELD_WATER
{
	E_ACTIVE_FIELD_W_1,
	E_ACTIVE_FIELD_W_2,
	E_ACTIVE_FIELD_W_TOTAL
};

class _Display_Water : public _Inheritance_Display
{
private:

	std::string InitDataText;
	std::size_t found;
	std::vector<double> WaterPosition;
	std::vector<_Str_TextTexture> RangeTexture;
	std::istringstream iss;


	int WaterHeight;
	float ChairHeight;
	int WaterPositionAmount;
	int AmountOfRange;
	float angle2;
	int i;

	int xrel = 0;
	GLfloat KRscale = 1.0f;
	_E_DISP_WATER_ADD SlowMotion;
	bool scaleflag;
	bool start;

	GLuint Texture[E_DISP_WATER_TOTAL];
	_Str_TextTexture InitDataTexture[E_DISP_WATER_AD_TOTAL];

	Button_S Button_Active_Field_Water = { 267, 145, 177, 41 };
	Button_S Button_Active_Field_Water2 = { 267, 247, 177, 41 };
	Button_S Button_Start = { 198, 101, 90, 27 };
	Button_S Button_Slowmo = { 200, 51, 250, 26 };
	Button_S Button_Powrot = { 32, 556, 110, 30 };

	float WaterVelocity(int h)
	{

		return (float)(sqrt(2 * 9.80665 * (h)* 0.01));
	}

	bool Load_Media()
	{
		bool success = true;
		if (!(LoadGLTextures(&Texture[E_DISP_WATER_SURFACE], "bmp/interface2.bmp")))
		{
			std::cout << "Display_Water can't load E_DISP_WATER_SURFACE...\n";
			success = false;
		}

		if (!(LoadGLTextures(&Texture[E_DISP_WATER_BACK], "png/next.png")))
		{
			std::cout << "Display_Water can't load E_DISP_WATER_BACK...\n";
			success = false;
		}

		if (!(LoadGLTextures(&Texture[E_DISP_WATER_GLASS], "png/glass.png")))
		{
			std::cout << "Display_Water can't load E_DISP_WATER_GLASS...\n";
			success = false;
		}

		return success;
	}

	void Menu()
	{
		glClearColor(136.0f / 255.0f, 0.0f, 21.0f / 255.0f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		glColor4f(1.0, 0.0, 1.0, 1.0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();


		if (Active_Field == E_ACTIVE_FIELD_W_1)
		{
			StartTimer = SDL_GetTicks();

			if (StartTimer - Timer >= 1000)
			{
				if (InitDataText.empty())
				{
					InitDataText.push_back('|');
				}
				else  if (InitDataText.back() == '|')
				{
					InitDataText.pop_back();
				}
				else if (!(InitDataText.back() == '|'))
				{
					InitDataText.push_back('|');
				}

				Timer = SDL_GetTicks();
			}
		}
		//else if (Active_Field == E_ACTIVE_FIELD_W_2)
		//{
		//	StartTimer = SDL_GetTicks();

		//	if (StartTimer - Timer >= 1000)
		//	{
		//		if (InitDataText2.empty())
		//		{
		//			InitDataText2.push_back('|');
		//		}
		//		else  if (InitDataText2.back() == '|')
		//		{
		//			InitDataText2.pop_back();
		//		}
		//		else if (!(InitDataText2.back() == '|'))
		//		{
		//			InitDataText2.push_back('|');
		//		}

		//		Timer = SDL_GetTicks();
		//	}
		//}

		//InitDataText2 = "asdasd";
		InitDataTexture[E_DISP_WATER_AD_CM] = LoadFromRenderedText("fonts/arial.ttf", InitDataText.c_str(), 20, &textColor);
		//InitDataTexture[E_DISP_WATER_AD_CM2] = LoadFromRenderedText("fonts/arial.ttf", InitDataText2.c_str(), 20, &textColor);


		glEnable(GL_TEXTURE_2D);

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, Texture[E_DISP_WATER_SURFACE]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2f(0.0, 0.0);
		glTexCoord2f(0.0, 1.0); glVertex2f(0.0, 600.0);
		glTexCoord2f(1.0, 1.0); glVertex2f(800.0, 600.0);
		glTexCoord2f(1.0, 0.0); glVertex2f(800.0, 0.0);
		glEnd();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		glBindTexture(GL_TEXTURE_2D, Texture[E_DISP_WATER_BACK]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2f(600.0, 100.0);
		glTexCoord2f(0.0, 1.0); glVertex2f(600.0, 200.0);
		glTexCoord2f(1.0, 1.0); glVertex2f(700.0, 200.0);
		glTexCoord2f(1.0, 0.0); glVertex2f(700.0, 100.0);
		glEnd();

		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2f(200.0, 100.0);
		glTexCoord2f(0.0, 1.0); glVertex2f(200.0, 200.0);
		glTexCoord2f(1.0, 1.0); glVertex2f(100.0, 200.0);
		glTexCoord2f(1.0, 0.0); glVertex2f(100.0, 100.0);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, Texture[E_DISP_WATER_GLASS]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2f(550.0, 250.0);
		glTexCoord2f(0.0, 1.0); glVertex2f(550.0, 500.0);
		glTexCoord2f(1.0, 1.0); glVertex2f(750.0, 500.0);
		glTexCoord2f(1.0, 0.0); glVertex2f(750.0, 250.0);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, InitDataTexture[E_DISP_WATER_AD_CM].Texture);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2f(270.0, 440.0);
		glTexCoord2f(0.0, 1.0); glVertex2f(270.0, 440.0 - InitDataTexture[E_DISP_WATER_AD_CM].h);
		glTexCoord2f(1.0, 1.0); glVertex2f(270.0 + InitDataTexture[E_DISP_WATER_AD_CM].w, 440.0 - InitDataTexture[E_DISP_WATER_AD_CM].h);
		glTexCoord2f(1.0, 0.0); glVertex2f(270.0 + InitDataTexture[E_DISP_WATER_AD_CM].w, 440.0);
		glEnd();

		//glBindTexture(GL_TEXTURE_2D, InitDataTexture[E_DISP_WATER_AD_CM2].Texture);
		//glBegin(GL_QUADS);
		//glTexCoord2f(0.0, 0.0); glVertex2f(270.0, 340.0);
		//glTexCoord2f(0.0, 1.0); glVertex2f(270.0, 340.0 - InitDataTexture[E_DISP_WATER_AD_CM2].h);
		//glTexCoord2f(1.0, 1.0); glVertex2f(270.0 + InitDataTexture[E_DISP_WATER_AD_CM2].w, 340.0 - InitDataTexture[E_DISP_WATER_AD_CM2].h);
		//glTexCoord2f(1.0, 0.0); glVertex2f(270.0 + InitDataTexture[E_DISP_WATER_AD_CM2].w, 340.0);
		//glEnd();

		glDeleteTextures(1, &InitDataTexture[E_DISP_WATER_AD_CM].Texture);
		//glDeleteTextures(1, &InitDataTexture[E_DISP_WATER_AD_CM2].Texture);

		glDisable(GL_BLEND);

		glDisable(GL_TEXTURE_2D);


		//angle = 0;


		//Events();
	}

	void Reset()
	{
		xrel = 0;
		KRscale = 1.0f;
		SlowMotion = E_DISP_WATER_AD_SLOWMO_FALSE;
		scaleflag = false;
		start = false;
		tempint = 0;
	}

	void Count()
	{
		iss.str(InitDataText);
		iss >> WaterHeight;
		iss.clear();
		//iss.str(InitDataText2);
		//iss >> ChairHeight;

		WaterPositionAmount = 0;
		WaterPosition.clear();
		ChairHeight = 2.0;
		do
		{
			WaterPosition.push_back(ThrowPos((float)(WaterPositionAmount * 0.001), WaterVelocity(WaterHeight), 0));
			WaterPositionAmount++;

		} while (WaterPosition.back() >= -ChairHeight);

		//std::cout << "WaterPositionAmount: " << WaterPositionAmount << "\n";


		for (AmountOfRange = 0; AmountOfRange < WaterPositionAmount / 10 + 100; AmountOfRange += 100);
		AmountOfRange -= 100;
		AmountOfRange /= 100;

		//std::cout << "Amount of range: " << AmountOfRange << "\n";

		//std::cout << "Amount of range textures: " << RangeTexture.size() << "\n";

		RangeTexture.clear();
		std::string range;
		for (int i = 0; i < AmountOfRange + 1; i++)
		{
			range = std::to_string(i);
			RangeTexture.push_back(LoadFromRenderedText("fonts/arial.ttf", range, 20, &textColor));
		}

		RangeTexture.push_back(LoadFromRenderedText("fonts/arial.ttf", "[m]", 20, &textColor));

		//std::cout << "Amount of range textures: " << RangeTexture.size() << "\n";

		range.erase();
		range.append("Zasieg: ");
		range.append(std::to_string(WaterPositionAmount / 1000.));
		range.append("[m]");
		InitDataTexture[E_DISP_WATER_AD_RANGE] = LoadFromRenderedText("fonts/arial.ttf", range, 25, &textColor);

		Reset();

	}

	void Display()
	{
		glClearColor(153.0f / 255.0f,
			217.0f / 255.0f,
			234.0f / 255.0f,
			1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();


		//floor
		glColor4f(185.0f / 255.0f,
			122.0f / 255.0f,
			87.0f / 255.0f,
			1.0f);

		glBegin(GL_QUADS);
		glVertex2f(0.0, 0.0);
		glVertex2f(0.0, 200.0);
		glVertex2f(800.0, 200.0);
		glVertex2f(800.0f, 0.0f);
		glEnd();
		//end floor


		//additional buttons and info for events of animation

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glBindTexture(GL_TEXTURE_2D, InitDataTexture[E_DISP_WATER_AD_POWROT].Texture);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2f(30.0, 50.0f);
		glTexCoord2f(0.0, 1.0); glVertex2f(30.0, 50.0f - InitDataTexture[E_DISP_WATER_AD_POWROT].h);
		glTexCoord2f(1.0, 1.0); glVertex2f(30.0 + InitDataTexture[E_DISP_WATER_AD_POWROT].w, 50.0 - InitDataTexture[E_DISP_WATER_AD_POWROT].h);
		glTexCoord2f(1.0, 0.0); glVertex2f(30.0 + InitDataTexture[E_DISP_WATER_AD_POWROT].w, 50.0);
		glEnd();


		glBindTexture(GL_TEXTURE_2D, InitDataTexture[SlowMotion].Texture);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2f(200.0, 550.0f);
		glTexCoord2f(0.0, 1.0); glVertex2f(200.0, 550.0f - InitDataTexture[SlowMotion].h);
		glTexCoord2f(1.0, 1.0); glVertex2f(200.0 + InitDataTexture[SlowMotion].w, 550.0 - InitDataTexture[SlowMotion].h);
		glTexCoord2f(1.0, 0.0); glVertex2f(200.0 + InitDataTexture[SlowMotion].w, 550.0);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, InitDataTexture[E_DISP_WATER_AD_START].Texture);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2f(200.0, 500.0f);
		glTexCoord2f(0.0, 1.0); glVertex2f(200.0, 500.0f - InitDataTexture[E_DISP_WATER_AD_START].h);
		glTexCoord2f(1.0, 1.0); glVertex2f(200.0 + InitDataTexture[E_DISP_WATER_AD_START].w, 500.0 - InitDataTexture[E_DISP_WATER_AD_START].h);
		glTexCoord2f(1.0, 0.0); glVertex2f(200.0 + InitDataTexture[E_DISP_WATER_AD_START].w, 500.0);
		glEnd();


		glBindTexture(GL_TEXTURE_2D, InitDataTexture[E_DISP_WATER_AD_RANGE].Texture);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2f(SCREEN_WIDTH - InitDataTexture[E_DISP_WATER_AD_RANGE].w - 30, 550.0f);
		glTexCoord2f(0.0, 1.0); glVertex2f(SCREEN_WIDTH - InitDataTexture[E_DISP_WATER_AD_RANGE].w - 30, 550.0f - InitDataTexture[E_DISP_WATER_AD_RANGE].h);
		glTexCoord2f(1.0, 1.0); glVertex2f(SCREEN_WIDTH - 30, 550.0 - InitDataTexture[E_DISP_WATER_AD_RANGE].h);
		glTexCoord2f(1.0, 0.0); glVertex2f(SCREEN_WIDTH - 30, 550.0);
		glEnd();



		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
		//end of additional buttons for events of animation


		if (start == true)
		{
			if (tempint < WaterPositionAmount)
			{
				if (SlowMotion == E_DISP_WATER_AD_SLOWMO_TRUE)
				{
					tempint += WaterVelocity(WaterHeight) * 100 / FPS;
				}
				else
				{
					tempint += WaterVelocity(WaterHeight) * 1000 / FPS;
				}
			}

			if (tempint > WaterPositionAmount)
			{
				tempint = WaterPositionAmount;
			}
		}

		if (tempint > 3500 && tempint < WaterPositionAmount)
		{
			glTranslatef(350 - (int)tempint / 10, 0.0, 0.0);
		}

		//scalling with +- and moving with mouse
		if (tempint == WaterPositionAmount && tempint > 3500)
		{
			if (scaleflag == false)
			{
				xrel = (int)-tempint / 10 + 350;
				scaleflag = true;
			}

			if (scaleflag == true)
			{
				if (xrel >= 200)
				{
					xrel = 200 - 1;
				}
				if ((float)xrel <= -(float)(AmountOfRange * 100.) * (float)KRscale)
				{
					xrel = (int)-(AmountOfRange * 100.) * KRscale + 1.;
				}

				glTranslatef((float)xrel, 0.0f, 0.0f);
				glScalef(KRscale, KRscale, KRscale);
			}

		}
		//end of scalling and moving







		glEnable(GL_POINT_SMOOTH);
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_MULTISAMPLE);


		//chair
		glLineWidth(10 * KRscale);
		glBegin(GL_LINES);

		//brown dark
		glColor4f(98.0f / 255.0f,
			83.0f / 255.0f,
			60.0f / 255.0f,
			1.0f);

		glVertex2f(120.0f, 100.0f);
		glVertex2f(120.0f, 290.0f);

		glVertex2f(190.0f, 100.0f);
		glVertex2f(190.0f, 290.0f);

		glVertex2f(120.0f, 286.0f);
		glVertex2f(190.0f, 286.0f);

		glEnd();
		//end chair


		//vessel
		glLineWidth(2 * KRscale);

		//dark purple - blue
		glColor4f(131.0f / 255.0f,
			153.0f / 255.0f,
			205.0f / 255.0f,
			1.0f);

		glBegin(GL_LINES);
		glVertex2f(110.0f, 300.0f);
		glVertex2f(110.0f, 325.0f + (float)WaterHeight);

		glVertex2f(200.0f, 300.0f);
		glVertex2f(200.0f, 325.0f + (float)WaterHeight);

		glVertex2f(120.0f, 290.0f);
		glVertex2f(190.0f, 290.0f);


		glEnd();


		//left and right circulated sides of vessel
		glBegin(GL_LINE_STRIP);
		for (angle2 = 0; angle2 < M_PI / 2;
			glVertex2f(120.0f - cos(angle2) * 10, 300.0f - sin(angle2) * 10),
			angle2 += 0.1);
		glEnd();

		glBegin(GL_LINE_STRIP);
		for (angle2 = 0; angle2 < M_PI / 2;
			glVertex2f(190.0f + sin(angle2) * 10, 300.0f - cos(angle2) * 10),
			angle2 += 0.1);
		glEnd();
		//end vessel


		//Water
		glColor4f(43.0f / 255.0f,
			75.0f / 255.0f,
			230.0f / 255.0f,
			1.0f);

		//fill the vessel
		glBegin(GL_POLYGON);
		for (angle2 = 0; angle2 < M_PI * 2;
			glVertex2f(189.0f + sin(angle2) * 10, 301.0f - cos(angle2) * 10),
			angle2 += 0.1);
		glEnd();

		glBegin(GL_POLYGON);
		for (angle2 = 0; angle2 < M_PI * 2;
			glVertex2f(121.0f + sin(angle2) * 10, 301.0f - cos(angle2) * 10),
			angle2 += 0.1);
		glEnd();


		glLineWidth(10 * KRscale);

		glBegin(GL_LINES);

		glVertex2f(118.0f, 294.0f);
		glVertex2f(189.0f, 294.0f);

		glVertex2f(118.0f, 299.0f);
		glVertex2f(189.0f, 299.0f);

		glVertex2f(111.0f, 304.0f);
		glVertex2f(199.0f, 304.0f);

		for (i = 0; i < WaterHeight; i += 5)
		{
			glVertex2f(111.0f, 309.0f + (float)i);
			glVertex2f(199.0f, 309.0f + (float)i);
		}

		glEnd();
		//end filing the vessel


		glLineWidth(2 * KRscale);



		glBegin(GL_LINES);

		glVertex2f(195.0f, 300.0f);
		glVertex2f(200.0f, 300.0f);


		//Water stream

		for (i = 0; i <= tempint - 2;
			glVertex2f(200.0f + (i * 0.1f), 300.0f + WaterPosition[i] * 100),
			glVertex2f(200.0f + ((i + 1) * 0.1f), 300.0f + WaterPosition[i + 1] * 100),
			i++);

		glEnd();



		//glDisable(GL_BLEND);


		glBegin(GL_LINES);

		//black
		glColor4f(0.0f,
			0.0f,
			0.0f,
			1.0f);

		glVertex2f(200.0f, 100.0f);
		glVertex2f(300.0f + WaterPositionAmount / 10, 100.0f);

		for (i = 0; i < WaterPositionAmount / 10 + 100; i += 100)
		{
			glVertex2f(200.0f + (float)i, 100.0f);
			glVertex2f(200.0f + (float)i, 90.0f);

		}

		glEnd();



		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		for (i = 0; i < AmountOfRange + 1; i++)
		{
			glBindTexture(GL_TEXTURE_2D, RangeTexture[i].Texture);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0); glVertex2f(190.0 + i * 100, 90.0f);
			glTexCoord2f(0.0, 1.0); glVertex2f(190.0 + i * 100, 90.0f - RangeTexture[i].h);
			glTexCoord2f(1.0, 1.0); glVertex2f(190.0 + i * 100 + RangeTexture[i].w, 90.0 - RangeTexture[i].h);
			glTexCoord2f(1.0, 0.0); glVertex2f(190.0 + i * 100 + RangeTexture[i].w, 90.0);
			glEnd();

		}

		glBindTexture(GL_TEXTURE_2D, RangeTexture[i].Texture);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2f(170.0 + i * 100, 90.0f);
		glTexCoord2f(0.0, 1.0); glVertex2f(170.0 + i * 100, 90.0f - RangeTexture[i].h);
		glTexCoord2f(1.0, 1.0); glVertex2f(170.0 + i * 100 + RangeTexture[i].w, 90.0 - RangeTexture[i].h);
		glTexCoord2f(1.0, 0.0); glVertex2f(170.0 + i * 100 + RangeTexture[i].w, 90.0);
		glEnd();





		glDisable(GL_BLEND);

		glDisable(GL_TEXTURE_2D);
	}

	void Events()
	{
		/*This function is to be called in main event function in Init.Window()*/
		//while (SDL_PollEvent(&ev) != 0)

		//if (ev.key.keysym.mod == KMOD_CAPS)
		//{
		//	std::cout << "KMOD_CAPS\n";
		//}

		if (ev.type == SDL_KEYDOWN)
		{
			if (ev.key.keysym.sym == SDLK_RETURN)
			{
				if (!InitDataText.empty())
				{
					Actual_Interface.Enum_Interface = E_INTER_WATER_COUNT;
				}
			}
		}

		if (ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT)
		{
			SDL_GetMouseState(&mousex, &mousey);

			switch (Actual_Interface.Enum_Interface)
			{
			case E_INTER_WATER_MENU:
				if (CheckButton(&Button_Active_Field_Water, mousex, mousey))
				{
					//while ((found = InitDataText2.find('|')) != std::string::npos)
					//{
					//	InitDataText2.erase(found, 1);
					//}
					Active_Field = E_ACTIVE_FIELD_W_1;
				}
				else if (CheckButton(&Button_Active_Field_Water2, mousex, mousey))
				{
					while ((found = InitDataText.find('|')) != std::string::npos)
					{
						InitDataText.erase(found, 1);
					}
					Active_Field = E_ACTIVE_FIELD_W_2;
				}
				else if (CheckButton(&Button_Next, mousex, mousey))
				{
					Actual_Interface.Enum_Interface = E_INTER_WATER_COUNT;
				}
				else if (CheckButton(&Button_Back, mousex, mousey))
				{
					Actual_Interface.Enum_Interface = E_INTER_MAIN;
				}
				else
				{
					if (Active_Field == E_ACTIVE_FIELD_W_1)
					{
						if (!InitDataText.empty())
						{
							if (InitDataText.back() == '|')
								InitDataText.pop_back();
						}
					}
					//else if (Active_Field == E_ACTIVE_FIELD_W_2)
					//{
					//	if (!InitDataText2.empty())
					//	{
					//		if (InitDataText2.back() == '|')
					//			InitDataText2.pop_back();
					//	}
					//}
					Active_Field = E_ACTIVE_FIELD_W_TOTAL;
				}
				break;

			case E_INTER_WATER_THEATRE:
				if (CheckButton(&Button_Powrot, mousex, mousey))
				{
					Actual_Interface.Enum_Interface = E_INTER_WATER_MENU;
				}
				else
				if (CheckButton(&Button_Start, mousex, mousey))
				{
					start = (start == true ? false : true);
					if (tempint == WaterPositionAmount)
						Reset();
				}
				else
				if (CheckButton(&Button_Slowmo, mousex, mousey))
				{
					SlowMotion = (SlowMotion == E_DISP_WATER_AD_SLOWMO_TRUE ? E_DISP_WATER_AD_SLOWMO_FALSE : E_DISP_WATER_AD_SLOWMO_TRUE);
				}

				break;


			default:
				std::cout << "ERROR: Display Water event switch Actual_Interface...\n";
				Actual_Interface.Enum_Interface = E_INTER_MAIN;
				break;


			}
		}

		if (ev.type == SDL_MOUSEMOTION && ev.button.button == SDL_BUTTON_LEFT && (Actual_Interface.Enum_Interface == E_INTER_WATER_THEATRE))
		{
			if ((xrel <= 200) && (xrel >= -(AmountOfRange * 100)))
			{
				xrel += ev.motion.xrel;
			}
		}


		switch (ev.type)
		{
		case SDL_TEXTINPUT:

			if (Active_Field == E_ACTIVE_FIELD_W_1)
			{

				while ((found = InitDataText.find('|')) != std::string::npos)
				{
					InitDataText.erase(found, 1);
				}
				if (InitDataText.length() < 5)
				{
					strcpy_s(buffer, sizeof(buffer), ev.text.text);
					if (buffer[0] > 47 && buffer[0] < 58)
					{
						if (InitDataText.empty() || InitDataText == " ")
						{
							InitDataText.clear();
							if (buffer[0] > '0')
								InitDataText.push_back(buffer[0]);
						}
						else
							InitDataText.push_back(buffer[0]);
					}

				}
			}
			//else if (Active_Field == E_ACTIVE_FIELD_W_2)
			//{

			//	while ((found = InitDataText2.find('|')) != std::string::npos)
			//	{
			//		InitDataText2.erase(found, 1);
			//	}
			//	if (InitDataText2.length() < 3)
			//	{
			//		strcpy_s(buffer, sizeof(buffer), ev.text.text);
			//		if (buffer[0] > 47 && buffer[0] < 58)
			//		{
			//			if (InitDataText2 == " ")
			//			{
			//				InitDataText2.clear();
			//			}
			//			InitDataText2.push_back(buffer[0]);
			//		}

			//	}
			//}
			break;

		case SDL_KEYDOWN:

			if (ev.key.keysym.sym == SDLK_BACKSPACE)
			{
				if (Active_Field == E_ACTIVE_FIELD_W_1)
				{
					if (!InitDataText.empty())
					{
						if (InitDataText.back() == '|')
							InitDataText.pop_back();

						if (!InitDataText.empty())
						{
							InitDataText.pop_back();
						}
					}

				}
				//else if (Active_Field == E_ACTIVE_FIELD_W_2)
				//{
				//	if (!InitDataText2.empty())
				//	{
				//		if (InitDataText2.back() == '|')
				//			InitDataText2.pop_back();

				//		if (!InitDataText2.empty())
				//		{
				//			InitDataText2.pop_back();
				//		}
				//	}

				//}
			}
			break;

		default:
			break;

		}

	}


public:

	_Display_Water()
	{
		//std::cout << "Constructor _Display_Water()\n";
		if (Load_Media())
		{
			//std::cout << "Load media success\n";
		}
		textColor = { 0, 0, 0 };


		InitDataTexture[E_DISP_WATER_AD_POWROT] = LoadFromRenderedText("fonts/arial.ttf", "Powrot", 35, &textColor);
		InitDataTexture[E_DISP_WATER_AD_SLOWMO_TRUE] = LoadFromRenderedText("fonts/arial.ttf", "Wylacz zwolnione tempo", 25, &textColor);
		InitDataTexture[E_DISP_WATER_AD_SLOWMO_FALSE] = LoadFromRenderedText("fonts/arial.ttf", "Wlacz zwolnione tempo", 25, &textColor);
		InitDataTexture[E_DISP_WATER_AD_START] = LoadFromRenderedText("fonts/arial.ttf", "START", 25, &textColor);



		Active_Field = E_ACTIVE_FIELD_W_1;
	}

	~_Display_Water()
	{
		glDeleteTextures(E_DISP_WATER_TOTAL, Texture);

		for (int i = 0; i < E_DISP_WATER_AD_TOTAL; i++)
		{
			glDeleteTextures(1, &InitDataTexture[i].Texture);
		}

		for (int i = 0; i < RangeTexture.size(); i++)
		{
			glDeleteTextures(1, &RangeTexture[i].Texture);
		}

		for (int i = 0; i < E_DISP_WATER_AD_TOTAL; i++)
		{
			glDeleteTextures(1, &InitDataTexture[i].Texture);
		}
	}

	void Theatre()
	{
		switch (Actual_Interface.Enum_Interface)
		{
		case E_INTER_WATER_MENU:
			Menu();
			break;

		case E_INTER_WATER_COUNT:
			Count();
			Actual_Interface.Enum_Interface = E_INTER_WATER_THEATRE;
			break;

		case E_INTER_WATER_THEATRE:
			Display();
			break;

		default:
			Actual_Interface.Enum_Interface = E_INTER_MAIN;
			std::cout << "Error in Actual_Interface inside Display Water\n";
			break;
		}
	}


};




#endif