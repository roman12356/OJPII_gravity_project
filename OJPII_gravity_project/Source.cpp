#include "Header.h"

bool LoadGLTextures(GLuint *texture, char * filename)
{

	/* Status indicator */
	bool success = true;

	/* Create storage space for the texture */
	SDL_Surface *TextureImage[1];// = NULL;

	/* Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit */
	if ((TextureImage[0] = SDL_LoadBMP(filename)))
	{

		//invert_image(TextureImage[0]);

		success = true;

		glEnable(GL_TEXTURE_2D);

		/* Create The Texture */
		glGenTextures(1, &texture[0]);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		/* Typical Texture Generation Using Data From The Bitmap */
		glBindTexture(GL_TEXTURE_2D, texture[0]);

		/* Generate The Texture */

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TextureImage[0]->w,
			TextureImage[0]->h, 0, GL_BGR,
			GL_UNSIGNED_BYTE, TextureImage[0]->pixels);
		glGetError();

		/* Linear Filtering */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		success = false;
	}

	/* Free up any memory we may have used */
	if (TextureImage)
		SDL_FreeSurface(TextureImage[0]);

	return success;


}


int main(int argc, char * argv[])
{
	int j;
	int tempfps = 0;
	Uint32 Timer;

	GLuint texture;

	//_Display_Main Display;

	//Display.Display();

	_Init Window("Grawitacja dla gimnazjum");

	Window.Window();

	//_Display_Main display;
	//display.LoadGLTextures(&texture, "png/ball.png");


	









	
	//Window.~Init();
	SDL_Quit();
	system("PAUSE");
	return 0;
}