/* 
 * File:   Floor.cpp
 * Author: Silvermoon
 * 
 * Created on 3 octobre 2015, 15:27
 */

#include "Floor.h"

Floor::Floor() {
}

Floor::Floor(const Floor& orig) {
}

Floor::~Floor() {
}

bool Floor::DrawAndHit(Player* player){
    sf2d_draw_texture(this->texture,this->x-player->GetX()+PLAYER_X,this->y);
    if(player->GetX()+player->GetWidth()>this->x && player->GetX()<this->x+floor_img.width &&
    (int)(player->GetY()+player->GetHeight())>=this->y && (int)(player->GetY()+player->GetHeight())<= this->y+floor_img.height ){
        floorpos=this->y-floor_img.height;
    }
    return false;
}
