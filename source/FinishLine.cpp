/* 
 * File:   FinishLine.cpp
 * Author: Ophelie
 * 
 * Created on 19 octobre 2015, 18:00
 */

#include "FinishLine.h"

FinishLine::FinishLine() {
}

FinishLine::FinishLine(const FinishLine& orig) {
}

FinishLine::~FinishLine() {
}

int FinishLine::DrawAndHit(Player* player,bool left){
    sf2d_draw_texture(this->texture,this->x-player->GetX()+PLAYER_X,this->y);
    return false;
}