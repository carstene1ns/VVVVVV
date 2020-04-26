#include "Screen.h"

#include "FileSystemUtils.h"
#include "GraphicsUtil.h"

#include <stdlib.h>

// Used to create the window icon
extern "C"
{
	extern unsigned lodepng_decode24(
		unsigned char** out,
		unsigned* w,
		unsigned* h,
		const unsigned char* in,
		size_t insize
	);
}

Screen::Screen()
{
    m_screen = NULL;
    isWindowed = true;
    stretchMode = 0;
    isFiltered = false;
    filterSubrect.x = 1;
    filterSubrect.y = 1;
    filterSubrect.w = 318;
    filterSubrect.h = 238;

	unsigned char *fileIn = NULL;
	size_t length = 0;
	unsigned char *data;
	unsigned int width, height;
	FILESYSTEM_loadFileToMemory("VVVVVV.png", &fileIn, &length);
	lodepng_decode24(&data, &width, &height, fileIn, length);
	FILESYSTEM_freeMemory(&fileIn);
	SDL_Surface *icon = SDL_CreateRGBSurfaceFrom(
		data,
		width,
		height,
		24,
		width * 3,
		0x000000FF,
		0x0000FF00,
		0x00FF0000,
		0x00000000
	);
	SDL_WM_SetIcon(icon, NULL);
	SDL_FreeSurface(icon);
	free(data);

	m_screen = SDL_SetVideoMode(
		320,
		240,
		32,
		SDL_HWSURFACE
	);

	m_screen->format->Rmask = 0x000000FF;
	m_screen->format->Gmask = 0x0000FF00;
	m_screen->format->Bmask = 0x00FF0000;
	m_screen->format->Amask = 0xFF000000;
	/*m_screen->format->Rshift = 0;
	m_screen->format->Gshift = 16;
	m_screen->format->Bshift = 8;
	m_screen->format->Ashift = 24;*/

	SDL_WM_SetCaption("VVVVVV", "VVVVVV");

    badSignalEffect = false;

    glScreen = true;
}

void Screen::ResizeScreen(int x , int y)
{
	if(!isWindowed)
	{

	}
	else
	{

	}
	if (stretchMode == 1)
	{

	}
	else
	{

	}
}

void Screen::GetWindowSize(int* x, int* y)
{
	*x = m_screen->w;
	*y = m_screen->h;
}

void Screen::UpdateScreen(SDL_Surface* buffer, SDL_Rect* rect )
{
    if((buffer == NULL) && (m_screen == NULL) )
    {
        return;
    }

    if(badSignalEffect)
    {
        buffer = ApplyFilter(buffer);
    }


    FillRect(m_screen, 0x000);
    BlitSurfaceStandard(buffer,NULL,m_screen,rect);

    if(badSignalEffect)
    {
        SDL_FreeSurface(buffer);
    }

}

SDL_PixelFormat* Screen::GetFormat()
{
	assert(m_screen);
    return m_screen->format;
}

void Screen::FlipScreen()
{
	SDL_Flip(m_screen);
	SDL_FillRect(m_screen, NULL, 0);
}

void Screen::toggleFullScreen()
{
	isWindowed = !isWindowed;
	SDL_WM_ToggleFullScreen(m_screen);
	ResizeScreen(-1, -1);
}

void Screen::toggleStretchMode()
{
	stretchMode = (stretchMode + 1) % 3;
	ResizeScreen(-1, -1);
}

void Screen::toggleLinearFilter()
{
	isFiltered = !isFiltered;
}

void Screen::ClearScreen( int colour )
{
    FillRect(m_screen, colour);
}
