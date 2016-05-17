#ifndef INHERITANCE_DISPLAY_H
#define INHERITANCE_DISPLAY_H

//#include "Header.h"

class _Inheritance_Display
{
	friend class Init;
protected:
	bool ready = 0;
	bool Invert_Image(SDL_Surface* image)
	{

		if (image == NULL)
		{
			printf("Sorry, cant invert image, SDL ERROR: %s\n", SDL_GetError());
			return false;
		}
		else
		{

			int pitch = image->pitch;
			int height = image->h;
			void* image_pixels = image->pixels;
			int index;
			void* temp_row;
			int height_div_2;

			temp_row = (void *)malloc(pitch);
			if (NULL == temp_row)
			{
				SDL_SetError("Not enough memory for image inversion");
				return false;
			}
			//if height is odd, don't need to swap middle row
			height_div_2 = (int)(height * .5);
			for (index = 0; index < height_div_2; index++) 	{
				//uses string.h
				memcpy((Uint8 *)temp_row,
					(Uint8 *)(image_pixels)+
					pitch * index,
					pitch);

				memcpy(
					(Uint8 *)(image_pixels)+
					pitch * index,
					(Uint8 *)(image_pixels)+
					pitch * (height - index - 1),
					pitch);
				memcpy(
					(Uint8 *)(image_pixels)+
					pitch * (height - index - 1),
					temp_row,
					pitch);
			}
			free(temp_row);
			return true;
		}
	}


public:
	bool LoadGLTextures(GLuint *texture, std::string filename)
	{

		/* Status indicator */
		bool success = true;

		/* Create storage space for the texture */
		SDL_Surface *TextureImage = NULL;

		if (filename.find(".bmp") != std::string::npos)
		{

			if (!(TextureImage = SDL_LoadBMP(filename.c_str())))
			{
				std::cout << "Inheritance_Display.LoadGLTextures<bmp> error with " << filename << " ...\n";
				return false;
			}
			else
			{
				std::cout << "Loaded " << filename << "\n";
			}

		}
		else if (filename.find(".png") != std::string::npos)
		{
			if (!(TextureImage = IMG_Load(filename.c_str())))
			{
				std::cout << "Inheritance_Display.LoadGLTextures<png> error with " << filename <<" ...\n";
				return false;
			}
			else
			{
				std::cout << "Loaded " << filename << "\n";
			}
		}


			Invert_Image(TextureImage);

			success = true;

			glEnable(GL_TEXTURE_2D);

			/* Create The Texture */
			glGenTextures(1, texture);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			/* Typical Texture Generation Using Data From The Bitmap */
			glBindTexture(GL_TEXTURE_2D, *texture);

			/* Generate The Texture */

			if (filename.find(".bmp") != std::string::npos)
			{

				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TextureImage->w,
					TextureImage->h, 0, GL_BGR,
					GL_UNSIGNED_BYTE, TextureImage->pixels);
				glGetError();
			}
			else if (filename.find(".png") != std::string::npos)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TextureImage->w,
					TextureImage->h, 0, GL_RGBA,
					GL_UNSIGNED_BYTE, TextureImage->pixels);
				glGetError();
			}


			/* Linear Filtering */
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


		/* Free up any memory we may have used */
		if (TextureImage)
			SDL_FreeSurface(TextureImage);

		return success;


	}



	virtual bool Count()
	{
		std::cout << "Virtual bool Count from Inheritance_Display...\n";
		return false;
	}
	virtual void Display(){};
	virtual void Events(){};



};





#endif