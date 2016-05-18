#ifndef INHERITANCE_DISPLAY_H
#define INHERITANCE_DISPLAY_H

//#include "Header.h"

class _Inheritance_Display
{
	friend class Init;
protected:
	int mousex, mousey;
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

	typedef struct _Str_Button
	{
		int x;
		int y;
		int width;
		int height;

	private:
		int i;

		struct Proxy
		{
			_Str_Button &prox;

			Proxy(_Str_Button &prox) :prox(prox){};

			Proxy operator , (const int &x)
			{
				std::cout << "i: " << prox.i << "\n";
				if (prox.i  == 1)
					prox.y = x;
				else
				if (prox.i == 2)
					prox.width = x;
				else
				if (prox.i == 3)
					prox.height = x;

				prox.i++;

				return Proxy(prox);
			}
		};



	public:
		_Str_Button(){};
		_Str_Button(const int &x, const int &y, const int &width, const int &height) : x(x), y(y), width(width), height(height){};

		Proxy operator = (const int &x)
		{
			i = 1;
			this->x = x;
			return Proxy(*this);
		}


	} Button_S;

	typedef struct _STRUCT_TEXT_TEXTURE
	{
		GLuint Texture;
		GLint w;
		GLint h;

		_STRUCT_TEXT_TEXTURE()
		{
			Texture = 0;
			w = 0;
			h = 0;
		}
	}_Str_TextTexture;


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
				std::cout << "Inheritance_Display.LoadGLTextures<bmp> can't find with " << filename << " ...\n";
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
				std::cout << "Inheritance_Display.LoadGLTextures<png> can't find " << filename <<" ...\n";
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
				std::cout << "Generate png\n";
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

	_Str_TextTexture LoadFromRenderedText(char *font, std::string text, int size, SDL_Color *textColor)
	{
		_Str_TextTexture temp;

		TTF_Font* tmpfont = TTF_OpenFont(font, size);
		if (tmpfont == NULL)
		{
			printf("Error: %s\n", TTF_GetError());
			return _Str_TextTexture::_STRUCT_TEXT_TEXTURE();
		}



		SDL_Surface* TextSDL = NULL;

		if (text[0] == '\0')
		{
			text = " ";
		}

		TextSDL = TTF_RenderText_Blended(tmpfont, text.c_str(), *textColor);
		if (TextSDL != NULL)
		{

			glEnable(GL_TEXTURE_2D);

			/* Create The Texture */
			glGenTextures(1, &temp.Texture);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			/* Typical Texture Generation Using Data From The Bitmap */
			glBindTexture(GL_TEXTURE_2D, temp.Texture);

			/* Generate The Texture */

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TextSDL->w,
				TextSDL->h, 0, GL_BGRA,
				GL_UNSIGNED_BYTE, TextSDL->pixels);
			glGetError();

			temp.h = TextSDL->h;
			temp.w = TextSDL->w;

			/* Linear Filtering */
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		}
		else
		{
			printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		}


		SDL_FreeSurface(TextSDL);
		TTF_CloseFont(tmpfont);

		return temp;
	}

	bool CheckButton(Button_S *button, int &mousex, int &mousey)
	{
		bool success = false;
		if (mousex > (*button).x && mousex < (*button).x + (*button).width
			&& mousey >(*button).y && mousey < (*button).y + (*button).height)
		{
			success = true;
		}

		while (ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT)
		{
			ev.type = NULL;
			ev.button.button = NULL;

		}


		return success;
	}






	virtual bool Count()
	{
		//Actual_Interface.
		std::cout << "Virtual bool Count from Inheritance_Display...\n";
		return false;
	}
	virtual void Theatre(){};
	virtual void Events(){};
	virtual void Mouse_Events(){};



};





#endif