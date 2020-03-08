

#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Sprite.h"

#ifdef _WIN32
#include <lua5.1/lua.hpp>
#endif

#ifdef __linux
#include <lua.hpp>
#endif

#ifndef TILE_MAP
#define TILE_MAP

class TileMap
{
private:
    
public:
    int width = 0;
    int height = 0;
    int tile_width = 0;
    int tile_height = 0;
    int sprite_n = 0;

    int *map_data;

    Sprite **sprite;

    TileMap(SDL_Renderer *renderer,const char *path);
    ~TileMap();

    void LoadMap(SDL_Renderer *renderer,const char *path);
    void Render(SDL_Renderer *renderer,unsigned int FPS);
};

TileMap::TileMap(SDL_Renderer *renderer,const char *path)
{
    this->LoadMap(renderer,path);
}

TileMap::~TileMap()
{
    free(this->map_data);
    for (int i = 0; i < this->sprite_n; i++)
    {
        free(this->sprite[i]);
    }
}

void TileMap::LoadMap(SDL_Renderer *renderer,const char *path)
{  
    lua_State *L = luaL_newstate();
    luaopen_base(L);  
    luaopen_math(L);  
    luaopen_string(L); 
    
    luaL_dofile (L, path);
    lua_settop(L, 0);

    printf("Get width and height.\n");

    lua_getglobal(L, "width");
    lua_getglobal(L, "height");
    lua_getglobal(L, "tilewidth");
    lua_getglobal(L, "tileheight");

    this->width = lua_tointeger(L,1);
    this->height = lua_tointeger(L,2);
    this->tile_width = lua_tointeger(L,3);
    this->tile_height = lua_tointeger(L,4);

    printf("%d\n%d\n%d\n%d\n",this->width,this->height,this->tile_width,this->tile_height);

    lua_settop(L, 0);

    printf("Get tileconunt.\n");

    lua_getglobal(L, "tilesets");
    lua_pushstring(L,"tilecount");
    lua_gettable(L, -2);
    this->sprite_n = lua_tointeger(L,-1);

    lua_pop(L,1);

    this->sprite = (Sprite**)calloc(this->sprite_n,sizeof(Sprite*));

    printf("Get tile image.\n");

    for (int i = 0; i < this->sprite_n; i++)
    {
        #ifdef _WIN32
        char *tile_id = itoa(i + 1,tile_id,10);
        #endif

        #ifdef __linux
        char *tile_id = (char*)calloc(8,sizeof(char));
        sprintf(tile_id,"%d",i + 1);
        #endif

        char *table_name = (char*)calloc(18,sizeof(char));
        strcat(table_name,"tile_");
        strcat(table_name,tile_id);

        printf("%s\n",table_name);

        lua_pushstring(L, table_name);
        lua_gettable(L, -2);
        
        lua_pushstring(L,"id");
        lua_gettable(L, -2);

        lua_pushstring(L,"image");
        lua_gettable(L, -3);

        const char *image_path = lua_tostring(L,-1);
        printf("%s\n",image_path);

        this->sprite[i] = new Sprite(image_path,renderer,false,0,0,0,0);

        lua_pop(L,3);
    }
    
    lua_pop(L,1);
    lua_settop(L,0);

    printf("Get map data.\n");

    lua_getglobal(L, "data");

    this->map_data = (int*)calloc(this->width * this->height,sizeof(int));

    for (int i = 0; i < this->width * this->height; i++)
    {
        lua_pushnumber(L, i + 1);
        lua_gettable(L,-2);
        //lua_rawgeti(L, -1, i + 1);

        this->map_data[i] = lua_tointeger(L,-1);

        lua_pop(L,1);
    }

    lua_pop(L,1);
    lua_close(L);

    for (int i = 0; i < this->height; i++)
    {
        for (int j = 0; j < this->width; j++)
        {
            printf("%d",this->map_data[i * this->width + j]);
        }
        printf("\n");
    }
    
}

void TileMap::Render(SDL_Renderer *renderer,unsigned int FPS)
{
    for (int i = 0; i < this->height; i++)
    {
        for (int j = 0; j < this->width; j++)
        {
            if (this->map_data[i * this->width + j] != 0)
            {
                this->sprite[this->map_data[i * this->width + j] - 1]->Render(renderer,FPS,
                this->tile_width * j,this->tile_height * i,this->tile_width,this->tile_height,0);
            }
            
        }
        
    }
    
}



#endif
