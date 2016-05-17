#ifndef INIT_H
#define INIT_H

//#include "Header.h"
#include "Display_Main.h"

class _Init
{
	friend class _Display_Main;
private:

	_Inheritance_Display *Display_wsk;
	_Display_Main Display_Main;
	SDL_GLContext gContext;

	SDL_Window  * window;
	SDL_Surface * gScreenSurface;
	SDL_Surface * gCurrentSurface;
	SDL_Surface * gDefaultSurface;
	SDL_Event ev;

	

	Uint32 Timer;
	bool quit;
	Uint32 StartTimer;
	int FPS = 30;

	int tempfps;

	void Events()
	{
		while (SDL_PollEvent(&ev) != 0)
		{
			//MouseEvents();


			switch (ev.type)
			{
			case SDL_QUIT:
				quit = true;
				break;

			case SDL_KEYDOWN:
				if (ev.key.keysym.sym == SDLK_ESCAPE)
				{
					quit = true;
				}

				if (ev.key.keysym.sym == SDLK_0)
				{
					std::cout << "0\n";
				}

				/*if (InterfaceType == I_WATER && ev.key.keysym.sym == SDLK_RETURN  && InitDataText[DTWater][1] != '\0')
				{
					InterfaceType = I_COUNT_ANIM_WATER;
				}

				if (ev.key.keysym.sym == SDLK_BACKSPACE)
				{
					if (ActiveInitField == DTWater)
					{
						if (strlen(InitDataText[DTWater]) > 0)
						{
							InitDataText[DTWater][strlen(InitDataText[DTWater]) - 1] = '\0';
						}
					}
					else if (ActiveInitField == DTThrowVelocity)
					{
						if (strlen(InitDataText[DTThrowVelocity]) > 0)
						{
							InitDataText[DTThrowVelocity][strlen(InitDataText[DTThrowVelocity]) - 1] = '\0';
							InitData[DTThrowVelocity] = atoi(InitDataText[DTThrowVelocity]);
						}
					}
					else if (ActiveInitField == DTThrowAngle)
					{
						if (strlen(InitDataText[DTThrowAngle]) > 0)
						{
							InitDataText[DTThrowAngle][strlen(InitDataText[DTThrowAngle]) - 1] = '\0';
							InitData[DTThrowAngle] = atoi(InitDataText[DTThrowAngle]);
						}
					}
				}

				if (InterfaceType == I_ANIM_WATER || InterfaceType == I_ANIM_THROW)
				{
					switch (ev.key.keysym.sym)
					{
					case SDLK_KP_PLUS:
						if (KRscale < 1.0f)
							KRscale += 0.1f;
						break;

					case SDLK_EQUALS:
						if (ev.key.keysym.mod == KMOD_LSHIFT)
						{
							if (KRscale < 1.0f)
								KRscale += 0.1f;
						}
						break;

					case SDLK_KP_MINUS:
						if (KRscale > 0.2f)
							KRscale -= 0.1f;
						break;

					case SDLK_MINUS:
						if (KRscale > 0.2f)
							KRscale -= 0.1f;
						break;

					default:
						break;
					}
				}
				break;*/

			case SDL_TEXTINPUT:
				/*if (InterfaceType == I_WATER)
				{
					if (strlen(InitDataText[DTWater]) < 5)
					{
						strncpy(buffer, ev.text.text, 1);

						if (buffer[0] > 47 && buffer[0] < 58)
						{
							strcat(InitDataText[DTWater], buffer);
						}
					}

					if (InitDataText[DTWater][1] == 48)
					{
						InitDataText[DTWater][1] = '\0';
					}

					InitData[DTWater] = atoi(InitDataText[DTWater]);

				}


				if (InterfaceType == I_THROW)
				{
					switch (ActiveInitField)
					{

					case DTThrowVelocity:
						if (strlen(InitDataText[DTThrowVelocity]) < 4)
						{
							strncpy(buffer, ev.text.text, 1);

							if (buffer[0] > 47 && buffer[0] < 58)
							{
								strcat(InitDataText[DTThrowVelocity], buffer);
							}
						}


						InitData[DTThrowVelocity] = atoi(InitDataText[DTThrowVelocity]);
						break;

					case DTThrowAngle:
						if (strlen(InitDataText[DTThrowAngle]) < 3)
						{
							strncpy(buffer, ev.text.text, 1);

							if (InitData[DTThrowAngle] == 0 && buffer[0] > 48 && buffer[0] < 58)
							{
								strcat(InitDataText[DTThrowAngle], buffer);
							}
							else if (InitData[DTThrowAngle] == 9 && buffer[0] == 48)
							{
								strcat(InitDataText[DTThrowAngle], buffer);
							}
							else if (InitData[DTThrowAngle] > 0 && InitData[DTThrowAngle] < 9 && buffer[0] > 47 && buffer[0] < 58)
							{
								strcat(InitDataText[DTThrowAngle], buffer);
							}
						}


						InitData[DTThrowAngle] = atoi(InitDataText[DTThrowAngle]);
						break;



					default:
						break;
					}

				}*/

				break;

			default:
				break;
			}
		}
	}

public:
	_Init(std::string window_name)
	{
		bool success = true;
		Display_wsk = &Display_Main;

		//Initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
		{
			printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Antyaliasing
			SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 2);
			SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 6);


			//Use OpenGL 3.1 core
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

			//Create window

			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

			/* Enable smooth shading */
			glShadeModel(GL_SMOOTH);

			/* Set the background red */

			/* Depth buffer setup */
			glClearDepth(1.0f);

			/* Enables Depth Testing */
			glEnable(GL_DEPTH_TEST);

			/* The Type Of Depth Test To Do */
			glDepthFunc(GL_LEQUAL);


			window = SDL_CreateWindow(window_name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
			if (window == NULL)
			{
				printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Create context
				gContext = SDL_GL_CreateContext(window);
				if (gContext == NULL)
				{
					printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
					success = false;
				}
				else
				{
					//Initialize GLEW
					glewExperimental = GL_TRUE;
					GLenum glewError = glewInit();
					if (glewError != GLEW_OK)
					{
						printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
					}

					//Initialize PNG loading
					int imgFlags = IMG_INIT_PNG;
					if (!(IMG_Init(imgFlags) & imgFlags))
					{
						printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
						success = false;
					}
					else

						//use Vsync
					if (SDL_GL_SetSwapInterval(1) < 0)
					{
						printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
					}
					else
					if (TTF_Init() == -1)
					{
						printf("TTF_Init: %s\n", TTF_GetError());
						success = false;
					}
				}

				//Get window surface
				gScreenSurface = SDL_GetWindowSurface(window);

				glMatrixMode(GL_PROJECTION);

				glLoadIdentity();

				glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

				glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -20.0, 20.0);

			}



		}

		if (success == true)
		{
			std::cout << "Init constructor good ;)\n";
		}

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		//InitDataText = (char**)malloc(sizeof(char*)*DTTotal);
		//for (i = 0; i < DTTotal; i++)
		//	InitDataText[i] = (char*)malloc(sizeof(char)* 5);

		//int j;

		//for (i = 0; i < DTTotal; i++)
		//{
		//	for (j = 0; j < 5; j++)
		//		InitDataText[i][j] = 0;
		//}





	}

	_Init()
	{
		bool success = true;
		Display_wsk = &Display_Main;

		//Initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
		{
			printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Antyaliasing
			SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 2);
			SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 6);


			//Use OpenGL 3.1 core
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

			//Create window

			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

			/* Enable smooth shading */
			glShadeModel(GL_SMOOTH);

			/* Set the background red */

			/* Depth buffer setup */
			glClearDepth(1.0f);

			/* Enables Depth Testing */
			glEnable(GL_DEPTH_TEST);

			/* The Type Of Depth Test To Do */
			glDepthFunc(GL_LEQUAL);


			window = SDL_CreateWindow("Okno" , SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
			if (window == NULL)
			{
				printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Create context
				gContext = SDL_GL_CreateContext(window);
				if (gContext == NULL)
				{
					printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
					success = false;
				}
				else
				{
					//Initialize GLEW
					glewExperimental = GL_TRUE;
					GLenum glewError = glewInit();
					if (glewError != GLEW_OK)
					{
						printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
					}

					//Initialize PNG loading
					int imgFlags = IMG_INIT_PNG;
					if (!(IMG_Init(imgFlags) & imgFlags))
					{
						printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
						success = false;
					}
					else

						//use Vsync
					if (SDL_GL_SetSwapInterval(1) < 0)
					{
						printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
					}
					else
					if (TTF_Init() == -1)
					{
						printf("TTF_Init: %s\n", TTF_GetError());
						success = false;
					}
				}

				//Get window surface
				gScreenSurface = SDL_GetWindowSurface(window);

				glMatrixMode(GL_PROJECTION);

				glLoadIdentity();

				glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

				glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -20.0, 20.0);

			}



		}

		if (success == true)
		{
			std::cout << "Init constructor good ;)\n";
		}

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		//InitDataText = (char**)malloc(sizeof(char*)*DTTotal);
		//for (i = 0; i < DTTotal; i++)
		//	InitDataText[i] = (char*)malloc(sizeof(char)* 5);

		//int j;

		//for (i = 0; i < DTTotal; i++)
		//{
		//	for (j = 0; j < 5; j++)
		//		InitDataText[i][j] = 0;
		//}
	}

	~_Init()
	{
		SDL_DestroyWindow(window);
		window = NULL;
	}

	void Window()
	{
		Timer = SDL_GetTicks();

		Display_Main.Load_Media();

		while (!quit)
		{
			StartTimer = SDL_GetTicks();

			Display_wsk->Display();
			SDL_GL_SwapWindow(window);

			Events();



			tempfps++;

			if (StartTimer - Timer >= 1000)
			{
				Timer = SDL_GetTicks();
				std::cout << tempfps << "\n";
				tempfps = 0;
			}

			if (1000 / FPS > SDL_GetTicks() - StartTimer)
			{
				SDL_Delay(1000 / FPS - (SDL_GetTicks() - StartTimer));
			}



			
		}

		this->~_Init();

	}
};





	
#endif