
#include <stdio.h>

typedef struct 
{
    int x,y;
}CollisionPosition;

class CollisionBox
{
private:
    /* data */
public:
    CollisionPosition *collision_position = 
    (CollisionPosition*)calloc(4,sizeof(CollisionPosition));

    CollisionBox(/* args */);
    ~CollisionBox();
};

CollisionBox::CollisionBox(/* args */)
{
}

CollisionBox::~CollisionBox()
{
}
