
#include "Sprite.h"
#include "CollisionBox.h"

#ifndef OBJECT
#define OBJECT

class Object
{
private:
    Sprite *sprite = NULL;
    CollisionBox *collision_box = NULL;
public:
    int x = 0,y = 0;
    int dx = 0,dy =0;

    Object(Sprite *object_sprite);
    ~Object();

    void SetSprite(Sprite *object_sprite);
    void SetSpriteFlip(SpriteFlip flip);
    void SetCollisionBox(CollisionBox *object_collision_box);
    void Render(SDL_Renderer *renderer,unsigned int FPS,int x,int y,int width,int height,double angle);
};

Object::Object(Sprite *object_sprite)
{
    this->sprite = object_sprite;
}

Object::~Object()
{
    free(this->sprite);
    free(this->collision_box);
}

void Object::SetSprite(Sprite *object_sprite)
{
    this->sprite = object_sprite;
}

void Object::SetSpriteFlip(SpriteFlip flip)
{
    this->sprite->flip = flip;
}

void Object::SetCollisionBox(CollisionBox *object_collision_box)
{
    this->collision_box = object_collision_box;
}

void Object::Render(SDL_Renderer *renderer,unsigned int FPS,int x,int y,int width,int height,double angle)
{
    if(this->collision_box == NULL)
        this->sprite->Render(renderer,FPS,x,y,width,height,angle);
    else
    {
           
    }
}

#endif
