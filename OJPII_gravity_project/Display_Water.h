#ifndef DISPLAY_WATER_H
#define DISPLAY_WATER_H

#include "Init.h"
#include "Inheritance_Display.h"

enum E_DISP_WATER
{
	E_DISP_WATER_SURFACE,
	E_DISP_WATER_BACK,
	E_DISP_WATER_GLASS,
	E_DISP_WATER_TOTAL
};

class _Display_Water : public _Inheritance_Display
{
private:
	GLuint Texture[E_DISP_WATER_TOTAL];
	std::string InitDataText = "\0";

	_Str_TextTexture InitDataTexture;
	SDL_Color textColor;


public:

	_Display_Water()
	{
		std::cout << "Constructor _Display_Water()\n";
		if (Load_Media())
		{
			std::cout << "Load media success\n";
		}

		textColor = { 0, 0, 0 };
	}

	~_Display_Water()
	{
		glDeleteTextures(E_DISP_MAIN_TOTAL, Texture);
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

	void Theatre()
	{
		glClearColor(136.0f / 255.0f, 0.0f, 21.0f / 255.0f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		glColor4f(1.0, 0.0, 1.0, 1.0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();


		//if (InitDataText[0] == '\0')
		//{
		//	//std::cout << "Init data[0] is '\0'";
		//	/*InitDataText[0] = ' ';
		//	InitDataText.push_back('\0');*/
		//}



		InitDataTexture = LoadFromRenderedText("fonts/arial.ttf", InitDataText.c_str(), 20, &textColor);


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

		//glBindTexture(GL_TEXTURE_2D, InitDataTexture.Texture);
		//glBegin(GL_QUADS);
		//glTexCoord2f(0.0, 0.0); glVertex2f(270.0, 440.0);
		//glTexCoord2f(0.0, 1.0); glVertex2f(270.0, 440.0 - InitDataTexture.h);
		//glTexCoord2f(1.0, 1.0); glVertex2f(270.0 + InitDataTexture.w, 440.0 - InitDataTexture.h);
		//glTexCoord2f(1.0, 0.0); glVertex2f(270.0 + InitDataTexture.w, 440.0);
		//glEnd();

		//glDeleteTextures(1, &InitDataTexture.Texture);

		glDisable(GL_BLEND);

		glDisable(GL_TEXTURE_2D);


		//angle = 0;


		Events();
	}

	void Events()
	{
		while (SDL_PollEvent(&ev) != 0)
		{
			if (ev.type == SDL_KEYDOWN)
			{
				std::cout << "Keydown\n";
			}




		}
	}
};




#endif