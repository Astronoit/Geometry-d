/* 
 * File:   Spike.cpp
 * Author: Silvermoon
 * 
 * Created on 3 octobre 2015, 14:46
 */

#include "Spike.h"

Spike::Spike() {
}
Spike::Spike(sf2d_texture *text,int xPos,int yPos,int Height,int Width) : Block(text,xPos,yPos,Height,Width){
    
}
Spike::Spike(const Spike& orig) {
}

Spike::~Spike() {
}

int Spike::DrawAndHit(Player *player,bool left){
    //Draw Spike
    sf2d_draw_texture(this->texture,this->x-player->GetX()+PLAYER_X,this->y);

    //Shitty hitbox 
    if(((player->GetX()+player->GetWidth()>=this->x && player->GetX()<=this->x+this->width)) &&
        player->GetY()+player->GetHeight()>=(this->y+(this->height/2)) && player->GetY()<=this->y+this->width ){
        return TOUCHED;
    }
    return 0;
}