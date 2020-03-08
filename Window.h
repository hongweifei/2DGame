
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#ifndef WINDOW
#define WINDOW

class Window
{
private:
    SDL_Window *window = NULL;
public:
    SDL_Event event;
    SDL_Surface *surface = NULL;
    SDL_Texture *texture = NULL;
    SDL_Renderer *renderer = NULL;

    Window(const char *title,int width,int height);
    ~Window();

    Uint32 GetMessage();
    //void SetWindowFPS(Uint32 window_FPS);
    void Render(bool swap);
    void DestroyWindow();
};

Window::Window(const char *title,int width,int height)
{
    SDL_Init(SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER | SDL_INIT_EVENTS
            | SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK);
    this->window = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
                            width,height,SDL_WINDOW_SHOWN);

    this->renderer = SDL_CreateRenderer(this->window,-1,SDL_RENDERER_ACCELERATED);
    this->surface = IMG_Load("./ico.jpg");

    SDL_SetWindowIcon(this->window,this->surface);
}

Window::~Window()
{
    this->DestroyWindow();
}

Uint32 Window::GetMessage()
{
    SDL_PollEvent(&this->event);
    return this->event.type;
}

/*
void Window::SetWindowFPS(const Uint32 window_FPS)
{
    this->FPS = 1000/window_FPS;
}
*/

void Window::Render(bool swap)
{
    SDL_SetRenderDrawColor(this->renderer,0,0,0,0);
    SDL_RenderClear(this->renderer);

    if(swap)
        SDL_RenderPresent(renderer);
}

void Window::DestroyWindow()
{
    SDL_FreeSurface(this->surface);
    SDL_DestroyTexture(this->texture);
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}





#endif