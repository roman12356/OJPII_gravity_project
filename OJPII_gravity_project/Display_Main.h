#ifndef DISPLAY_MAIN_H
#define DISPLAY_MAIN_H

//#include "Header.h"
#include "Init.h"
#include "Inheritance_Display.h"

enum E_DISP_MAIN
{
	E_DISP_MAIN_SURFACE,
	E_DISP_MAIN_GIGGLES,
	E_DISP_MAIN_TOTAL
};

class _Display_Main : public _Inheritance_Display
{

private:
	GLuint Texture[E_DISP_MAIN_TOTAL];
	Button_S Button_Main1 = { 23, 160, 533, 70 };
	Button_S Button_Main2 = { 23, 290, 289, 30 };


public:

	_Display_Main()
	{
		//std::cout << "Constructor _Display_Main()\n";
		if (Load_Media())
		{
			//std::cout << "Load media success\n";
		}
	}

	~_Display_Main()
	{
		glDeleteTextures(E_DISP_MAIN_TOTAL, Texture);
	}

	bool Load_Media()
	{
		bool success = true;
		if (!(LoadGLTextures(&Texture[E_DISP_MAIN_SURFACE], "bmp/interface1.bmp")))
		{
			std::cout << "Display_Main can't load InterfaceSurface...\n";
			success = false;
		};

		if (!(LoadGLTextures(&Texture[E_DISP_MAIN_GIGGLES], "png/giggles.png")))
		{
			std::cout << "Display_Main can't load TextureGiggles...\n";
			success = false;
		};

		return success;
	}

	void Events()
	{
		if (ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT)
		{
			SDL_GetMouseState(&mousex, &mousey);

			if (CheckButton(&Button_Main1, mousex, mousey))
			{
				Actual_Interface.Enum_Interface = E_INTER_WATER_MENU;
			}

			if (CheckButton(&Button_Main2, mousex, mousey))
			{
				Actual_Interface.Enum_Interface = E_INTER_THROW_MENU;
			}
		}

		//if (ev.type == SDL_KEYDOWN)
		//{
		//	//std::cout << "Keydown main\n";
		//}

	}


	void Theatre()
	{
		glClearColor(136.0f / 255.0f, 0.9f, 21.0f / 255.0f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT);


		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glColor3f(1.0, 0.0 , 0.0);


		glEnable(GL_TEXTURE_2D);

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, Texture[E_DISP_MAIN_SURFACE]);

		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2f(0.0, 0.0);
		glTexCoord2f(0.0, 1.0); glVertex2f(0.0, SCREEN_HEIGHT);
		glTexCoord2f(1.0, 1.0); glVertex2f(SCREEN_WIDTH, SCREEN_HEIGHT);
		glTexCoord2f(1.0, 0.0); glVertex2f(SCREEN_WIDTH, 0.0);
		glEnd();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glBindTexture(GL_TEXTURE_2D, Texture[E_DISP_MAIN_GIGGLES]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2f(550.0, 135.0);
		glTexCoord2f(0.0, 1.0); glVertex2f(550.0, 535.0);
		glTexCoord2f(1.0, 1.0); glVertex2f(800.0, 535.0);
		glTexCoord2f(1.0, 0.0); glVertex2f(800.0, 135.0);
		glEnd();


		glDisable(GL_BLEND);

		glDisable(GL_TEXTURE_2D);


		//Mouse_Events();

		//Events();
	}

	
};








#endif