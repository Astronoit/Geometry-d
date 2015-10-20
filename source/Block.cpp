/* 
 * File:   Block.cpp
 * Author: Silvermoon
 * 
 * Created on 3 octobre 2015, 12:52
 */

#include "Block.h"
#include "Player.h"

Block::Block() {
}

Block::Block(sf2d_texture *text,int xPos,int yPos,int Height,int Width){
    x=xPos;
    y=yPos;
    texture=text;
    height=Height;
    width=Width;
    
}
Block::Block(const Block& orig) {
}

Block::~Block() {
}

char Block::CollisionDetect(Player *player){
    
    
    
    char side=0;
    float w = 0.5 * (player->GetWidth() + this->GetWidth());
    float h = 0.5 * (player->GetHeight() + this->GetHeight());
    float dx = (this->GetX() + (this->GetWidth()/2)) - (player->GetX() + (player->GetWidth()/2));
    float dy = (this->GetY() + (this->GetHeight()/2))- (player->GetY() + (player->GetHeight()/2));

    if (abs(dx) <= w && abs(dy) <= h)
    {
        /* collision! */
        float wy = w * dy;
        float hx = h * dx;

        if (wy > hx){
            if (wy > -hx){
                setFlag(&side,TOP);
            }else{
                setFlag(&side,LEFT);
            }
        }else{
            if (wy > -hx){
                setFlag(&side,RIGHT);
            }else{
                setFlag(&side,BOT);
            }
        }
    }
    return side;
}