
#include "Window.h"

#ifndef GAME
#define GAME

#define FPS_NONE 0000

class Game
{
private:
    Window *window = NULL;
    Uint32 FPS = 1000/30;
    Uint32 FPS_Timer;
    bool quit = false;
public:
    Game(Window *window);
    ~Game();

    void StartGame(void (*Render)(SDL_Renderer *renderer,const Uint8 *key_state),
                    Uint32 game_FPS,bool swap);
    void QuitGame();

    void Render(bool present);
};

Game::Game(Window *window)
{
    this->window = window;
}

Game::~Game()
{
    
}

void Game::StartGame(void (*Render)(SDL_Renderer *renderer,const Uint8 *key_state),
                    const Uint32 game_FPS,bool swap)
{
    if(game_FPS != FPS_NONE)
        this->FPS = 1000/game_FPS;

    while (!quit)
    {
        Uint32 msg = this->window->GetMessage();
        switch (this->window->event.type)
        {
        case SDL_QUIT:
            this->quit = true;
            break;
        case SDL_KEYDOWN:
            break;
        case SDL_KEYUP:
            break;
        default:
            break;
        }
        const Uint8 *key_state = SDL_GetKeyboardState(NULL);

        if(game_FPS != FPS_NONE)
        {
            if(SDL_GetTicks() - this->FPS_Timer < this->FPS)
                SDL_Delay(this->FPS - SDL_GetTicks() + this->FPS_Timer);
            this->FPS_Timer = SDL_GetTicks();
        }

        this->window->Render(false);
        Render(this->window->renderer,key_state);
        this->Render(swap);
    }

    this->QuitGame();
}

void Game::QuitGame()
{
    this->window->DestroyWindow();
    free(this->window);
}

void Game::Render(bool swap)
{
    if(swap)
        SDL_RenderPresent(this->window->renderer);
}

#endif
