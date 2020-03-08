
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#ifndef SPRITE
#define SPRITE

#define SpriteFlip SDL_RendererFlip
#define SPRITE_FLIP_NONE SDL_FLIP_NONE
#define SPRITE_FLIP_HORIZONTAL SDL_FLIP_HORIZONTAL 
#define SPRITE_FLIP_VERTICAL SDL_FLIP_VERTICAL

class Sprite
{
private:
    /* data */
public:
    SDL_Texture *texture = NULL;
    int texture_width = 0;
    int texture_height = 0;

    SDL_Rect rect = {0,0,0,0};
    SDL_Rect *sprite_rect = (SDL_Rect*)calloc(1,sizeof(SDL_Rect));
    unsigned int sprite_rect_n = 1;
    unsigned int render_n = 0;
    unsigned int render_sprite_n = 0;

    SDL_RendererFlip flip = SPRITE_FLIP_NONE;

    Sprite(const char *path,SDL_Renderer *renderer,
            bool ColorKey,Uint8 r,Uint8 g,Uint8 b,Uint8 a);
    ~Sprite();

    void SetTexture(const char *path,SDL_Renderer *renderer
                    ,bool ColorKey,Uint8 r,Uint8 g,Uint8 b,Uint8 a);

    void InitSpriteRect(int width,int height,int begin_x,int begin_y,
                        unsigned int n,unsigned int m);
    void Render(SDL_Renderer *renderer,unsigned int FPS,
                int x,int y,int width,int height,double angle);
};

Sprite::Sprite(const char *path,SDL_Renderer *renderer
                ,bool ColorKey,Uint8 r,Uint8 g,Uint8 b,Uint8 a)
{
    this->SetTexture(path,renderer,ColorKey,r,g,b,a);
}

Sprite::~Sprite()
{
    SDL_DestroyTexture(this->texture);
    free(this->sprite_rect);
}

void Sprite::SetTexture(const char *path,SDL_Renderer *renderer
                        ,bool color_key,Uint8 r,Uint8 g,Uint8 b,Uint8 a)
{
    SDL_Surface *surface= IMG_Load(path);
    SDL_SetColorKey(surface,color_key,SDL_MapRGBA(surface->format,r,g,b,a));

    this->texture = SDL_CreateTextureFromSurface(renderer,surface);
    this->texture_width = surface->w;
    this->texture_height = surface->h;
    
    SDL_FreeSurface(surface);

    this->sprite_rect[0].x = 0;
    this->sprite_rect[0].y = 0;
    this->sprite_rect[0].w = this->texture_width;
    this->sprite_rect[0].h = this->texture_height;
}

void Sprite::InitSpriteRect(int width,int height,
int begin_x,int begin_y,unsigned int n,unsigned int m)//n is H , m is V
{
    int a = 0;
    int i,j;

    if(n == 0)
        n = 1;
    if(m == 0)
        m = 1;
    
    this->sprite_rect = (SDL_Rect*)calloc(n * m + 1,sizeof(SDL_Rect));

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            this->sprite_rect[a].x = width * j + begin_x;
            this->sprite_rect[a].y = height * i + begin_y;
            this->sprite_rect[a].w = width;
            this->sprite_rect[a].h = height;
            a++;
        }
    }
    
    this->sprite_rect_n = n * m;

}

void Sprite::Render(SDL_Renderer *renderer,unsigned int FPS,int x,int y,
                    int width,int height,double angle)
{
    this->rect.x = x;
    this->rect.y = y;
    this->rect.w = width;
    this->rect.h = height;

    SDL_RenderCopyEx(renderer,this->texture,&this->sprite_rect[this->render_sprite_n],
                    &this->rect,angle,NULL,flip);

    if(this->render_n < FPS)
        this->render_n++;
    else if(this->render_n >= FPS)
    {
        this->render_n = 0;

        if(this->render_sprite_n < this->sprite_rect_n - 1)
            this->render_sprite_n++;
        else
            this->render_sprite_n = 0;
    }

}


#endif