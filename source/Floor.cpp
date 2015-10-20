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

int Floor::DrawAndHit(Player* player,bool left){
    sf2d_draw_texture(this->texture,this->x-player->GetX()+PLAYER_X,this->y);
    char result = CollisionDetect(player);
    if(isFlagSet(result,TOP))
        floorpos=this->y-floor_img.height;
    return 0;
}
