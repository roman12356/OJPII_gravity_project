#ifndef DISPLAY_THROW_H
#define DISPLAY_THROW_H

#include "Init.h"
#include "Inheritance_Display.h"
#include <sstream>  
#include <vector>

enum _E_DISP_THROW
{
	E_DISP_THROW_SURFACE,
	E_DISP_THROW_BACK,
	E_DISP_THROW_BALL,
	E_DISP_THROW_TOTAL
};


enum _E_ACTIVE_FIELD_THROW
{
	E_ACTIVE_FIELD_T_1,
	E_ACTIVE_FIELD_T_2,
	E_ACTIVE_FIELD_T_TOTAL
};

enum _E_DISP_THROW_TEXT
{
	E_DISP_THROW_TEXT_VELOCITY,
	E_DISP_THROW_TEXT_ANGLE,
	E_DISP_THROW_TEXT_POWROT,
	E_DISP_THROW_TEXT_SLOWMO_TRUE,
	E_DISP_THROW_TEXT_SLOWMO_FALSE,
	E_DISP_THROW_TEXT_RANGE,
	E_DISP_THROW_TEXT_START,
	E_DISP_THROW_TEXT_POSX,
	E_DISP_THROW_TEXT_POSY,
	E_DISP_THROW_TEXT_TOTAL
};


class _Display_Throw : public _Inheritance_Display
{
private:
	std::string InitDataTextVelocity;
	std::string InitDataTextAngle;
	std::string range;
	std::string PositionX, PositionY;
	std::size_t found;
	std::vector<double> ThrowPositionX;
	std::vector<double> ThrowPositionY;
	std::istringstream iss;

	bool start, scaleflag, ThrowPositionYUp;
	int i, RangeAmount = 0;
	int xrel, yrel;
	int MaxVelocityChar;
	int RangeTextureAmount;
	int k;
	double Velocity, Angle, translatex, translatey, RotateAngle, VectorLenght;

	GLint showtime;
	GLfloat KRscale = 1.0f;


	_E_DISP_THROW_TEXT SlowMotion;

	GLuint Texture[E_DISP_THROW_TOTAL];
	_Str_TextTexture DataTexture[E_DISP_THROW_TEXT_TOTAL];
	std::vector<_Str_TextTexture> RangeTexture;
	_Str_TextTexture RangeM;



	Button_S Button_Active_Field_Velocity = { 372, 192, 162, 41 };
	Button_S Button_Active_Field_Angle = { 372, 283, 162, 41 };
	Button_S Button_Start = { 28, 76, 90, 27 };
	Button_S Button_Slowmo = { 30, 26, 250, 26 };
	Button_S Button_Powrot = { 32, 556, 110, 30 };






	double ThrowY(double t, double &velocity, double &angle)
	{
		return velocity * t * sin(angle) - ((9.80665 * pow(t, 2.)) / 2.);
	}

	double ThrowX(double t, double &velocity, double &angle)
	{
		return velocity * t * cos(angle);
	}

	void Reset()
	{
		xrel = 0;
		yrel = 0;
		KRscale = 1.0f;
		SlowMotion = E_DISP_THROW_TEXT_SLOWMO_FALSE;
		scaleflag = false;
		start = false;
		tempint = 0;
		translatex = 0;
		translatey = 0;
		showtime = 0;
		ThrowPositionYUp = false;
	}

	bool Load_Media()
	{
		bool success = true;
		if (!(LoadGLTextures(&Texture[E_DISP_THROW_SURFACE], "bmp/interface3.bmp")))
		{
			std::cout << "Display_Water can't load E_DISP_THROW_SURFACE...\n";
			success = false;
		}

		if (!(LoadGLTextures(&Texture[E_DISP_THROW_BACK], "png/next.png")))
		{
			std::cout << "Display_Water can't load E_DISP_THROW_BACK...\n";
			success = false;
		}

		if (!(LoadGLTextures(&Texture[E_DISP_THROW_BALL], "png/ball.png")))
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


		//if (InitDataText[DTThrowVelocity][0] == '\0')
		//{
		//	InitDataText[DTThrowVelocity][0] = ' ';
		//	InitDataText[DTThrowVelocity][1] = '\0';
		//}

		//if (InitDataText[DTThrowAngle][0] == '\0')
		//{
		//	InitDataText[DTThrowAngle][0] = ' ';
		//	InitDataText[DTThrowAngle][1] = '\0';
		//}


		if (Active_Field == E_ACTIVE_FIELD_T_1)
		{
			StartTimer = SDL_GetTicks();

			if (StartTimer - Timer >= 1000)
			{
				if (InitDataTextVelocity.empty())
				{
					InitDataTextVelocity.push_back('|');
				}
				else  if (InitDataTextVelocity.back() == '|')
				{
					InitDataTextVelocity.pop_back();
				}
				else if (!(InitDataTextVelocity.back() == '|'))
				{
					InitDataTextVelocity.push_back('|');
				}

				Timer = SDL_GetTicks();
			}
		}
		else if (Active_Field == E_ACTIVE_FIELD_T_2)
		{
			StartTimer = SDL_GetTicks();

			if (StartTimer - Timer >= 1000)
			{
				if (InitDataTextAngle.empty())
				{
					InitDataTextAngle.push_back('|');
				}
				else  if (InitDataTextAngle.back() == '|')
				{
					InitDataTextAngle.pop_back();
				}
				else if (!(InitDataTextAngle.back() == '|'))
				{
					InitDataTextAngle.push_back('|');
				}

				Timer = SDL_GetTicks();
			}
		}

		DataTexture[E_DISP_THROW_TEXT_VELOCITY] = LoadFromRenderedText("fonts/arial.ttf", InitDataTextVelocity, 20, &textColor);
		DataTexture[E_DISP_THROW_TEXT_ANGLE] = LoadFromRenderedText("fonts/arial.ttf", InitDataTextAngle, 20, &textColor);


		glEnable(GL_TEXTURE_2D);

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, Texture[E_DISP_THROW_SURFACE]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2f(0.0, 0.0);
		glTexCoord2f(0.0, 1.0); glVertex2f(0.0, 600.0);
		glTexCoord2f(1.0, 1.0); glVertex2f(800.0, 600.0);
		glTexCoord2f(1.0, 0.0); glVertex2f(800.0, 0.0);
		glEnd();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		glBindTexture(GL_TEXTURE_2D, Texture[E_DISP_THROW_BACK]);
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


		glBindTexture(GL_TEXTURE_2D, DataTexture[E_DISP_THROW_TEXT_VELOCITY].Texture);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2f(370.0, 400.0);
		glTexCoord2f(0.0, 1.0); glVertex2f(370.0, 400.0 - DataTexture[E_DISP_THROW_TEXT_VELOCITY].h);
		glTexCoord2f(1.0, 1.0); glVertex2f(370.0 + DataTexture[E_DISP_THROW_TEXT_VELOCITY].w, 400.0 - DataTexture[E_DISP_THROW_TEXT_VELOCITY].h);
		glTexCoord2f(1.0, 0.0); glVertex2f(370.0 + DataTexture[E_DISP_THROW_TEXT_VELOCITY].w, 400.0);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, DataTexture[E_DISP_THROW_TEXT_ANGLE].Texture);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2f(370.0, 310.0);
		glTexCoord2f(0.0, 1.0); glVertex2f(370.0, 310.0 - DataTexture[E_DISP_THROW_TEXT_ANGLE].h);
		glTexCoord2f(1.0, 1.0); glVertex2f(370.0 + DataTexture[E_DISP_THROW_TEXT_ANGLE].w, 310.0 - DataTexture[E_DISP_THROW_TEXT_ANGLE].h);
		glTexCoord2f(1.0, 0.0); glVertex2f(370.0 + DataTexture[E_DISP_THROW_TEXT_ANGLE].w, 310.0);
		glEnd();


		glDisable(GL_BLEND);

		glDisable(GL_TEXTURE_2D);

		glDeleteTextures(1, &DataTexture[E_DISP_THROW_TEXT_VELOCITY].Texture);
		glDeleteTextures(1, &DataTexture[E_DISP_THROW_TEXT_ANGLE].Texture);
	}

	void Count()
	{
		i = 0;

		iss.clear();
		iss.str(InitDataTextAngle);
		iss >> Angle;
		iss.clear();
		Angle *= (M_PI / 180);
		iss.str(InitDataTextVelocity);
		iss >> Velocity;


		ThrowPositionX.clear();
		ThrowPositionY.clear();

		do
		{
			ThrowPositionY.push_back(ThrowY((double)i / (FPS * 5), Velocity, Angle));
			ThrowPositionX.push_back(ThrowX((double)i / (FPS * 5), Velocity, Angle));
			i++;
		} while (ThrowPositionY.back() >= 0.0);

		ThrowPositionY.back() = 0.0; //ThrowPositionX.back() * tan(Angle) - (9.80665) / (2 * pow(Velocity, 2.0) * pow(cos(Angle), 2.0)) * 


		range.clear();
		range.append("Zasieg: ");
		range.append(std::to_string(ThrowPositionX.back()));
		range.append("[m]");
		glDeleteTextures(1, &DataTexture[E_DISP_THROW_TEXT_RANGE].Texture);
		DataTexture[E_DISP_THROW_TEXT_RANGE] = LoadFromRenderedText("fonts/arial.ttf", range, 25, &textColor);


		std::string temp;
		RangeAmount = 0;

		for (i = 0; i < RangeTexture.size(); i++)
		{
			glDeleteTextures(1, &RangeTexture[i].Texture);
		}
		RangeTexture.clear();
		do
		{
			temp.clear();
			temp.append(std::to_string(RangeAmount++));
			RangeTexture.push_back(LoadFromRenderedText("fonts/arial.ttf", temp, 20, &textColor));

		} while (RangeAmount < RangeTextureAmount);

		RangeTexture[10].w = 11;

		//std::cout << "range texture amount: " << RangeTexture.size() << "\n";
		temp = "[m]";
		RangeM = LoadFromRenderedText("fonts/arial.ttf", temp, 20, &textColor);

		Reset();

	}

	void Display()
	{
		glPushMatrix();

		glClearColor(153.0f / 255.0f,
			217.0f / 255.0f,
			234.0f / 255.0f,
			1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glLineWidth(2 * KRscale);


		//ground
		glColor4f(34.0f / 255.0f,
			177.0f / 255.0f,
			76.0f / 255.0f,
			1.0f);



		glBegin(GL_QUADS);
		if (ThrowPositionY[tempint] > 3.0 && tempint <= ThrowPositionY.size())
		{

			glVertex2f(0.0, 0.0);
			glVertex2f(0.0, 300.0 - (ThrowPositionY[tempint] - 3.0) * KRscale * 10);
			glVertex2f(800.0, 300.0 - (ThrowPositionY[tempint] - 3.0) * KRscale * 10);
			glVertex2f(800.0f, 0.0f);
		}
		else
		{
			glVertex2f(0.0, 0.0);
			glVertex2f(0.0, 300.0);
			glVertex2f(800.0, 300.0);
			glVertex2f(800.0f, 0.0f);
		}
		glEnd();
		//end ground


		glPushMatrix();
		glTranslatef(-170.0, 25.0, 0.0);
		//additional buttons and info for events of animation

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		glBindTexture(GL_TEXTURE_2D, DataTexture[SlowMotion].Texture);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2f(200.0, 550.0f);
		glTexCoord2f(0.0, 1.0); glVertex2f(200.0, 550.0f - DataTexture[SlowMotion].h);
		glTexCoord2f(1.0, 1.0); glVertex2f(200.0 + DataTexture[SlowMotion].w, 550.0 - DataTexture[SlowMotion].h);
		glTexCoord2f(1.0, 0.0); glVertex2f(200.0 + DataTexture[SlowMotion].w, 550.0);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, DataTexture[E_DISP_THROW_TEXT_START].Texture);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2f(200.0, 500.0f);
		glTexCoord2f(0.0, 1.0); glVertex2f(200.0, 500.0f - DataTexture[E_DISP_THROW_TEXT_START].h);
		glTexCoord2f(1.0, 1.0); glVertex2f(200.0 + DataTexture[E_DISP_THROW_TEXT_START].w, 500.0 - DataTexture[E_DISP_THROW_TEXT_START].h);
		glTexCoord2f(1.0, 0.0); glVertex2f(200.0 + DataTexture[E_DISP_THROW_TEXT_START].w, 500.0);
		glEnd();


		glBindTexture(GL_TEXTURE_2D, DataTexture[E_DISP_THROW_TEXT_RANGE].Texture);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2f(570.0, 550.0f);
		glTexCoord2f(0.0, 1.0); glVertex2f(570.0, 550.0f - DataTexture[E_DISP_THROW_TEXT_RANGE].h);
		glTexCoord2f(1.0, 1.0); glVertex2f(570.0 + DataTexture[E_DISP_THROW_TEXT_RANGE].w, 550.0 - DataTexture[E_DISP_THROW_TEXT_RANGE].h);
		glTexCoord2f(1.0, 0.0); glVertex2f(570.0 + DataTexture[E_DISP_THROW_TEXT_RANGE].w, 550.0);
		glEnd();


		PositionX.clear();
		PositionX.append("Pozycja X: ");
		PositionX.append(std::to_string(ThrowPositionX[tempint]));
		DataTexture[E_DISP_THROW_TEXT_POSX] = LoadFromRenderedText("fonts/arial.ttf", PositionX, 20, &textColor);


		glBindTexture(GL_TEXTURE_2D, DataTexture[E_DISP_THROW_TEXT_POSX].Texture);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2f(570.0, 500.0f);
		glTexCoord2f(0.0, 1.0); glVertex2f(570.0, 500.0f - DataTexture[E_DISP_THROW_TEXT_POSX].h);
		glTexCoord2f(1.0, 1.0); glVertex2f(570.0 + DataTexture[E_DISP_THROW_TEXT_POSX].w, 500.0 - DataTexture[E_DISP_THROW_TEXT_POSX].h);
		glTexCoord2f(1.0, 0.0); glVertex2f(570.0 + DataTexture[E_DISP_THROW_TEXT_POSX].w, 500.0);
		glEnd();

		glDeleteTextures(1, &DataTexture[E_DISP_THROW_TEXT_POSX].Texture);

		PositionY.clear();
		PositionY.append("Pozycja Y: ");
		PositionY.append(std::to_string(ThrowPositionY[tempint]));
		DataTexture[E_DISP_THROW_TEXT_POSY] = LoadFromRenderedText("fonts/arial.ttf", PositionY, 20, &textColor);


		glBindTexture(GL_TEXTURE_2D, DataTexture[E_DISP_THROW_TEXT_POSY].Texture);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2f(570.0, 450.0f);
		glTexCoord2f(0.0, 1.0); glVertex2f(570.0, 450.0f - DataTexture[E_DISP_THROW_TEXT_POSY].h);
		glTexCoord2f(1.0, 1.0); glVertex2f(570.0 + DataTexture[E_DISP_THROW_TEXT_POSY].w, 450.0 - DataTexture[E_DISP_THROW_TEXT_POSY].h);
		glTexCoord2f(1.0, 0.0); glVertex2f(570.0 + DataTexture[E_DISP_THROW_TEXT_POSY].w, 450.0);
		glEnd();

		glDeleteTextures(1, &DataTexture[E_DISP_THROW_TEXT_POSY].Texture);

		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, DataTexture[E_DISP_THROW_TEXT_POWROT].Texture);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2f(30.0, 50.0f);
		glTexCoord2f(0.0, 1.0); glVertex2f(30.0, 50.0f - DataTexture[E_DISP_THROW_TEXT_POWROT].h);
		glTexCoord2f(1.0, 1.0); glVertex2f(30.0 + DataTexture[E_DISP_THROW_TEXT_POWROT].w, 50.0 - DataTexture[E_DISP_THROW_TEXT_POWROT].h);
		glTexCoord2f(1.0, 0.0); glVertex2f(30.0 + DataTexture[E_DISP_THROW_TEXT_POWROT].w, 50.0);
		glEnd();

		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);


		//end of additional buttons for events of animation

		if (start == true)
		{
			if (tempint < ThrowPositionY.size())
			{
				if (SlowMotion == E_DISP_THROW_TEXT_SLOWMO_TRUE)
				{
					tempint++;
				}
				else
				{
					tempint += 5;
				}
			}

			if (tempint >= ThrowPositionY.size())
			{
				tempint = ThrowPositionY.size() - 1;
			}
		}


		if (ThrowPositionX[tempint] > 3.5 && tempint <= ThrowPositionY.size())
		{
			translatex = 350 - ThrowPositionX[tempint] * 100;
		}

		if (ThrowPositionY[tempint] > 2.5 && tempint <= ThrowPositionY.size())
		{
			translatey = 250 - ThrowPositionY[tempint] * 100;
			ThrowPositionYUp = true;
		}

		if (ThrowPositionYUp == true && tempint == ThrowPositionY.size())
		{
			translatey = 0.0;
		}

		glTranslatef(translatex * KRscale, translatey * KRscale, 0.0);

		//scalling with +-
		glScalef(KRscale, KRscale, KRscale);

		//end of scalling and moving





		glEnable(GL_POINT_SMOOTH);
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_MULTISAMPLE);


		//black
		glColor4f(0.0f,
			0.0f,
			0.0f,
			1.0f);

		glBegin(GL_LINES);

		glVertex2f(200.0f, 100.0f);
		glVertex2f(300.0f + ThrowPositionX.size() * 100 + 100, 100.0f);

		glEnd();



		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



		glBindTexture(GL_TEXTURE_2D, Texture[E_DISP_THROW_BALL]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2f(175.0f + ThrowPositionX[tempint] * 100, 100.0f + ThrowPositionY[tempint] * 100);
		glTexCoord2f(0.0, 1.0); glVertex2f(175.0f + ThrowPositionX[tempint] * 100, 150.0f + ThrowPositionY[tempint] * 100);
		glTexCoord2f(1.0, 1.0); glVertex2f(225.0f + ThrowPositionX[tempint] * 100, 150.0f + ThrowPositionY[tempint] * 100);
		glTexCoord2f(1.0, 0.0); glVertex2f(225.0f + ThrowPositionX[tempint] * 100, 100.0 + ThrowPositionY[tempint] * 100);

		glEnd();



		//k = -1;
		if (translatex == 0)
		{
			for (i = 0; i < 40; i++)
			{

				if (i <= (int)ThrowPositionX.back() + 1)
				{
					glBindTexture(GL_TEXTURE_2D, RangeTexture[i].Texture);
					glBegin(GL_QUADS);
					glTexCoord2f(0.0, 0.0); glVertex2f(190.0 + i * 100, 90.0f);
					glTexCoord2f(0.0, 1.0); glVertex2f(190.0 + i * 100, 90.0f - RangeTexture[i].h);
					glTexCoord2f(1.0, 1.0); glVertex2f(190.0 + i * 100 + RangeTexture[i].w, 90.0 - RangeTexture[i].h);
					glTexCoord2f(1.0, 0.0); glVertex2f(190.0 + i * 100 + RangeTexture[i].w, 90.0);
					glEnd();

					glDisable(GL_BLEND);
					glDisable(GL_TEXTURE_2D);

					glBegin(GL_LINES);
					glVertex2f(200.0f + (float)i * 100, 100.0f);
					glVertex2f(200.0f + (float)i * 100, 90.0f);
					glEnd();

					glEnable(GL_TEXTURE_2D);
					glEnable(GL_BLEND);

				}
				else if (i <= (int)ThrowPositionX.back() + 2)
				{
					glBindTexture(GL_TEXTURE_2D, RangeM.Texture);
					glBegin(GL_QUADS);
					glTexCoord2f(0.0, 0.0); glVertex2f(190.0 + i * 100, 90.0f);
					glTexCoord2f(0.0, 1.0); glVertex2f(190.0 + i * 100, 90.0f - RangeM.h);
					glTexCoord2f(1.0, 1.0); glVertex2f(190.0 + i * 100 + RangeM.w, 90.0 - RangeM.h);
					glTexCoord2f(1.0, 0.0); glVertex2f(190.0 + i * 100 + RangeM.w, 90.0);
					glEnd();

					glDisable(GL_BLEND);
					glDisable(GL_TEXTURE_2D);

					glBegin(GL_LINES);
					glVertex2f(200.0f + (float)showtime * 100, 100.0f);
					glVertex2f(200.0f + (float)showtime * 100, 90.0f);
					glEnd();

					glEnable(GL_TEXTURE_2D);
					glEnable(GL_BLEND);

				}

			}
		}
		else
		{
			k = 0;
			for (showtime = (int)ceil(ThrowPositionX[tempint]) - 20; showtime < (int)ceil(ThrowPositionX[tempint]); showtime++)
			{
				if (showtime >= 0)
				{

					if ((int)ceil(ThrowPositionX[tempint]) - 20 > RangeAmount - RangeTextureAmount)
					{

						glDeleteTextures(1, &RangeTexture[0].Texture);
						range = std::to_string(RangeAmount++);
						//std::cout << "range: " << range << "\n";
						RangeTexture.erase(RangeTexture.begin());
						RangeTexture.push_back(LoadFromRenderedText("fonts/arial.ttf", range, 20, &textColor));
						

					}

					glBindTexture(GL_TEXTURE_2D, RangeTexture[k++].Texture);
					glBegin(GL_QUADS);
					glTexCoord2f(0.0, 0.0); glVertex2f(190.0 + showtime * 100, 90.0f);
					glTexCoord2f(0.0, 1.0); glVertex2f(190.0 + showtime * 100, 90.0f - RangeTexture[k].h);
					glTexCoord2f(1.0, 1.0); glVertex2f(190.0 + showtime * 100 + RangeTexture[k].w, 90.0 - RangeTexture[k].h);
					glTexCoord2f(1.0, 0.0); glVertex2f(190.0 + showtime * 100 + RangeTexture[k].w, 90.0);
					glEnd();

					glDisable(GL_BLEND);
					glDisable(GL_TEXTURE_2D);

					glBegin(GL_LINES);
					glVertex2f(200.0f + (float)showtime * 100, 100.0f);
					glVertex2f(200.0f + (float)showtime * 100, 90.0f);
					glEnd();

					glEnable(GL_TEXTURE_2D);
					glEnable(GL_BLEND);

				}
			}

				for (; showtime < (int)ceil(ThrowPositionX[tempint]) + 20; showtime++)
				{
					if (showtime < (int)ceil(ThrowPositionX.back()))
					{
						glBindTexture(GL_TEXTURE_2D, RangeTexture[k++].Texture);
						glBegin(GL_QUADS);
						glTexCoord2f(0.0, 0.0); glVertex2f(190.0 + showtime * 100, 90.0f);
						glTexCoord2f(0.0, 1.0); glVertex2f(190.0 + showtime * 100, 90.0f - RangeTexture[k].h);
						glTexCoord2f(1.0, 1.0); glVertex2f(190.0 + showtime * 100 + RangeTexture[k].w, 90.0 - RangeTexture[k].h);
						glTexCoord2f(1.0, 0.0); glVertex2f(190.0 + showtime * 100 + RangeTexture[k].w, 90.0);
						glEnd();

						glDisable(GL_BLEND);
						glDisable(GL_TEXTURE_2D);

						glBegin(GL_LINES);
						glVertex2f(200.0f + (float)showtime * 100, 100.0f);
						glVertex2f(200.0f + (float)showtime * 100, 90.0f);
						glEnd();

						glEnable(GL_TEXTURE_2D);
						glEnable(GL_BLEND);

					}
					else if (showtime < (int)ceil(ThrowPositionX.back()) + 1)
					{
						glBindTexture(GL_TEXTURE_2D, RangeM.Texture);
						glBegin(GL_QUADS);
						glTexCoord2f(0.0, 0.0); glVertex2f(190.0 + showtime * 100, 90.0f);
						glTexCoord2f(0.0, 1.0); glVertex2f(190.0 + showtime * 100, 90.0f - RangeM.h);
						glTexCoord2f(1.0, 1.0); glVertex2f(190.0 + showtime * 100 + RangeM.w, 90.0 - RangeM.h);
						glTexCoord2f(1.0, 0.0); glVertex2f(190.0 + showtime * 100 + RangeM.w, 90.0);
						glEnd();

						glDisable(GL_BLEND);
						glDisable(GL_TEXTURE_2D);

						glBegin(GL_LINES);
						glVertex2f(200.0f + (float)showtime * 100, 100.0f);
						glVertex2f(200.0f + (float)showtime * 100, 90.0f);
						glEnd();

						glEnable(GL_TEXTURE_2D);
						glEnable(GL_BLEND);
					}
				}
		}



		glDisable(GL_BLEND);

		//vector
		glColor4f(244.0f / 255.0f,
			0.0f / 255.0f,
			0.0f / 255.0f,
			1.0f);

		if (tempint == 0)
		{
			RotateAngle = atan((ThrowPositionY[tempint] - ThrowPositionY[tempint + 1]) / (ThrowPositionX[tempint] - ThrowPositionX[tempint + 1]));
		}
		else
		if (tempint == ThrowPositionY.size() - 1 && ThrowPositionY.size() >2)
		{
			RotateAngle = atan((ThrowPositionY[tempint - 1] - ThrowPositionY[tempint - 2]) / (ThrowPositionX[tempint - 1] - ThrowPositionX[tempint - 2]));
		}
		else
		if (tempint == ThrowPositionY.size() - 1)
		{
			RotateAngle = atan((ThrowPositionY[tempint] - ThrowPositionY[tempint - 1]) / (ThrowPositionX[tempint] - ThrowPositionX[tempint - 1]));
		}
		else
		if (tempint < ThrowPositionY.size())
		{
			RotateAngle = atan((ThrowPositionY[tempint] - ThrowPositionY[tempint - 1]) / (ThrowPositionX[tempint] - ThrowPositionX[tempint - 1]));
		}

		VectorLenght = 100;

		glBegin(GL_LINES);
		glVertex2f(200.0f + ThrowPositionX[tempint] * 100, 125.0f + ThrowPositionY[tempint] * 100);
		glVertex2f(200.0f + ThrowPositionX[tempint] * 100 + VectorLenght * cos(RotateAngle), 125.0f + ThrowPositionY[tempint] * 100 + VectorLenght * sin(RotateAngle));

		glEnd();

		glBegin(GL_TRIANGLES);

		glVertex2f(200.0f + ThrowPositionX[tempint] * 100 + VectorLenght * cos(RotateAngle), 125.0f + ThrowPositionY[tempint] * 100 + VectorLenght * sin(RotateAngle));

		glVertex2f(200.0f + ThrowPositionX[tempint] * 100 + (VectorLenght - 10) * cos(RotateAngle + 0.1),
			125.0f + ThrowPositionY[tempint] * 100 + (VectorLenght - 10) * sin(RotateAngle + 0.1));

		glVertex2f(200.0f + ThrowPositionX[tempint] * 100 + (VectorLenght - 10) * cos(RotateAngle - 0.1),
			125.0f + ThrowPositionY[tempint] * 100 + (VectorLenght - 10) * sin(RotateAngle - 0.1));

		glEnd();

		//End vector


		glDisable(GL_TEXTURE_2D);

		glPopMatrix();
	}

	void Events()
	{
		if (ev.type == SDL_KEYDOWN)
		{

			if (ev.key.keysym.sym == SDLK_RETURN)
			{
				if (!InitDataTextVelocity.empty() && !InitDataTextAngle.empty())
				{
					Actual_Interface.Enum_Interface = E_INTER_THROW_COUNT;
				}
			}

		}

		if (ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT)
		{
			SDL_GetMouseState(&mousex, &mousey);

			switch (Actual_Interface.Enum_Interface)
			{
			case E_INTER_THROW_MENU:
				if (CheckButton(&Button_Active_Field_Velocity, mousex, mousey))
				{
					while ((found = InitDataTextAngle.find('|')) != std::string::npos)
					{
						InitDataTextAngle.erase(found, 1);
					}
					Active_Field = E_ACTIVE_FIELD_T_1;
				}
				else if (CheckButton(&Button_Active_Field_Angle, mousex, mousey))
				{
					while ((found = InitDataTextVelocity.find('|')) != std::string::npos)
					{
						InitDataTextVelocity.erase(found, 1);
					}
					Active_Field = E_ACTIVE_FIELD_T_2;
				}
				else if (CheckButton(&Button_Next, mousex, mousey))
				{
					Actual_Interface.Enum_Interface = E_INTER_THROW_COUNT;
				}
				else if (CheckButton(&Button_Back, mousex, mousey))
				{
					Actual_Interface.Enum_Interface = E_INTER_MAIN;
				}
				else
				{
					if (Active_Field == E_ACTIVE_FIELD_T_1)
					{
						if (!InitDataTextVelocity.empty())
						{
							if (InitDataTextVelocity.back() == '|')
								InitDataTextVelocity.pop_back();
						}
					}
					else if (Active_Field == E_ACTIVE_FIELD_T_2)
					{
						if (!InitDataTextAngle.empty())
						{
							if (InitDataTextAngle.back() == '|')
								InitDataTextAngle.pop_back();
						}
					}
					Active_Field = E_ACTIVE_FIELD_T_TOTAL;
				}
				break;

			case E_INTER_THROW_THEATRE:
				if (CheckButton(&Button_Powrot, mousex, mousey))
				{

					Actual_Interface.Enum_Interface = E_INTER_THROW_MENU;
				}
				else
				if (CheckButton(&Button_Start, mousex, mousey))
				{
					//std::cout << "Start\n";
					start = (start == true ? false : true);
					if (tempint == ThrowPositionY.size() -1)
						Count();
				}
				else
				if (CheckButton(&Button_Slowmo, mousex, mousey))
				{
					//std::cout << "slowmo: " << SlowMotion << "\n";
					SlowMotion = (SlowMotion == E_DISP_THROW_TEXT_SLOWMO_TRUE ? E_DISP_THROW_TEXT_SLOWMO_FALSE : E_DISP_THROW_TEXT_SLOWMO_TRUE);
				}

				break;


			default:
				std::cout << "ERROR: Display Water event switch Actual_Interface...\n";
				Actual_Interface.Enum_Interface = E_INTER_MAIN;
				break;

			}
		}

		switch (ev.type)
		{
		case SDL_TEXTINPUT:

			if (Active_Field == E_ACTIVE_FIELD_T_1)
			{

				while ((found = InitDataTextVelocity.find('|')) != std::string::npos)
				{
					InitDataTextVelocity.erase(found, 1);
				}
				if (InitDataTextVelocity.length() < MaxVelocityChar)
				{
					strcpy_s(buffer, sizeof(buffer), ev.text.text);
					if (buffer[0] > 47 && buffer[0] < 58)
					{
						if (InitDataTextVelocity.empty() || InitDataTextVelocity == " ")
						{
							InitDataTextVelocity.clear();
							if (buffer[0] > '0')
								InitDataTextVelocity.push_back(buffer[0]);
						}
						else
						{
							InitDataTextVelocity.push_back(buffer[0]);
						}
					}

				}
			}
			else if (Active_Field == E_ACTIVE_FIELD_T_2)
			{

				while ((found = InitDataTextAngle.find('|')) != std::string::npos)
				{
					InitDataTextAngle.erase(found, 1);
				}
				if (InitDataTextAngle.length() < 2)
				{
					strcpy_s(buffer, sizeof(buffer), ev.text.text);
					if (buffer[0] > 47 && buffer[0] < 58)
					{
						if (InitDataTextAngle.empty())
						{
							if (buffer[0] > '0')
								InitDataTextAngle.push_back(buffer[0]);
						}
						else
						if (InitDataTextAngle == " ")
						{
							InitDataTextAngle.clear();
							buffer[0] > '0';
							InitDataTextAngle.push_back(buffer[0]);
						}
						else
						if (InitDataTextAngle[0] < '9')
						{
							InitDataTextAngle.push_back(buffer[0]);
						}
						else
						{
							if (buffer[0] == '0')
							{
								InitDataTextAngle.push_back(buffer[0]);
							}
						}

					}

				}
			}
			break;

		case SDL_KEYDOWN:

			if (ev.key.keysym.sym == SDLK_BACKSPACE)
			{
				if (Active_Field == E_ACTIVE_FIELD_T_1)
				{
					if (!InitDataTextVelocity.empty())
					{
						if (InitDataTextVelocity.back() == '|')
							InitDataTextVelocity.pop_back();

						if (!InitDataTextVelocity.empty())
						{
							InitDataTextVelocity.pop_back();
						}
					}

				}
				else if (Active_Field == E_ACTIVE_FIELD_T_2)
				{
					if (!InitDataTextAngle.empty())
					{
						if (InitDataTextAngle.back() == '|')
							InitDataTextAngle.pop_back();

						if (!InitDataTextAngle.empty())
						{
							InitDataTextAngle.pop_back();
						}
					}

				}
			}
			break;

		default:
			break;

		}
	}


public:

	_Display_Throw()
	{
		MaxVelocityChar = 4;
		RangeTextureAmount = 45;
		VectorLenght = 100;

		//std::cout << "Constructor _Display_Throw()\n";
		if (Load_Media())
		{
			//std::cout << "Load media success\n";
		}
		textColor = { 0, 0, 0 };

		DataTexture[E_DISP_THROW_TEXT_POWROT] = LoadFromRenderedText("fonts/arial.ttf", "Powrot", 35, &textColor);
		DataTexture[E_DISP_THROW_TEXT_SLOWMO_TRUE] = LoadFromRenderedText("fonts/arial.ttf", "Wylacz zwolnione tempo", 25, &textColor);
		DataTexture[E_DISP_THROW_TEXT_SLOWMO_FALSE] = LoadFromRenderedText("fonts/arial.ttf", "Wlacz zwolnione tempo", 25, &textColor);
		DataTexture[E_DISP_THROW_TEXT_START] = LoadFromRenderedText("fonts/arial.ttf", "START", 25, &textColor);

	}

	~_Display_Throw()
	{
		glDeleteTextures(E_DISP_THROW_TOTAL, Texture);
		glDeleteTextures(1, &RangeM.Texture);

		for (int i = 0; i < E_DISP_THROW_TEXT_TOTAL; i++)
		{
			glDeleteTextures(1, &DataTexture[i].Texture);
		}

		for (int i = 0; i < RangeTexture.size(); i++)
		{
			glDeleteTextures(1, &RangeTexture[i].Texture);
		}
	}



	void Theatre() //Done
	{
		switch (Actual_Interface.Enum_Interface)
		{
		case E_INTER_THROW_MENU:
			Menu();
			break;

		case E_INTER_THROW_COUNT:
			Count();
			Actual_Interface.Enum_Interface = E_INTER_THROW_THEATRE;
			break;

		case E_INTER_THROW_THEATRE:
			Display();
			break;

		default:
			Actual_Interface.Enum_Interface = E_INTER_MAIN;
			std::cout << "Error in Actual_Interface inside Display Throw\n";
			break;
		}
	}

};









#endif