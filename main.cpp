

#include "Game.h"
#include "Object.h"
#include "TileMap.h"

#define WINDOW_WIDTH 800 
#define WINDOW_HEIGHT 600

#define GAME_FPS 30

#define PLAYER_WAY_LEFT -1
#define PLAYER_WAY_RIGHT 1

#define PLAYER_STAND 0
#define PLAYER_RUN 1

#ifdef _WIN32
#undef main
#endif

TileMap *map;

Object *player;
Sprite *player_stand;
Sprite *player_run;

int player_way = PLAYER_WAY_RIGHT; //-1 left , 1 right
int player_state = PLAYER_STAND; //0 stand, 1 run

void GameInit(Game *game)
{
    map = new TileMap(game->GetRenderer(),"Map/01/01.lua");

    player_stand = new Sprite("Sprite/Character/Sprite_Player.png",game->GetRenderer());
    player_run = new Sprite("Sprite/Character/Sprite_Player.png",game->GetRenderer());

    player_stand->InitSpriteRect(64,64,0,0,3,1);
    player_run->InitSpriteRect(64,64,0,64,4,1);

    player = new Object(player_stand);

    player->x = 100;
    player->y = 100;
}

void Render(SDL_Renderer *renderer,const Uint8 *key_state)
{
    player_state = PLAYER_STAND;

    if(key_state[SDL_SCANCODE_A])
    {
        player->dx -= 5;
        player_way = PLAYER_WAY_LEFT;
        player_state = PLAYER_RUN;
    }
    if(key_state[SDL_SCANCODE_D])
    {
        player->dx += 5;
        player_way = PLAYER_WAY_RIGHT;
        player_state = PLAYER_RUN;
    }
    if(key_state[SDL_SCANCODE_W])
    {
        player->dy -= 5;
        player_state = PLAYER_RUN;
    }
    if(key_state[SDL_SCANCODE_S])
    {
        player->dy += 5;
        player_state = PLAYER_RUN;
    }

    player->x += player->dx;
	player->y += player->dy;
	player->dx = 0;
	player->dy = 0;

    if(player_state == PLAYER_STAND)
        player->SetSprite(player_stand);
    else if(player_state == PLAYER_RUN)
        player->SetSprite(player_run);

    if(player_way == PLAYER_WAY_LEFT)
        player->SetSpriteFlip(SPRITE_FLIP_HORIZONTAL);
    else if(player_way == PLAYER_WAY_RIGHT)
        player->SetSpriteFlip(SPRITE_FLIP_NONE);

    map->Render(renderer);

    player->Render(renderer,player->x,
                    player->y,48,48,0,GAME_FPS / 6);
}

int main(int argc,char *argv[])//入口
{
    Window *window = new Window("Game",WINDOW_WIDTH,WINDOW_HEIGHT);

    Game *game = new Game(window);

    GameInit(game);

    game->StartGame(&Render,GAME_FPS,true); 

    free(map);
    free(player);
    free(player_stand);
    free(player_run);
    free(game);

    return 0;
}


