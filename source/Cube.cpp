/* 
 * File:   Cube.cpp
 * Author: Silvermoon
 * 
 * Created on 3 octobre 2015, 15:28
 */

#include "Cube.h"

Cube::Cube() {
}

Cube::Cube(const Cube& orig) {
}

Cube::~Cube() {
}

int Cube::DrawAndHit(Player* player,bool left){
    sf2d_draw_texture(this->texture,this->x-player->GetX()+PLAYER_X,this->y);
    char flag=0;
    flag = CollisionDetect(player);
    if(isFlagSet(flag,RIGHT)){
        return TOUCHED;
    }
    if(isFlagSet(flag,TOP)){
        posYplayer=this->y-player->GetHeight()-1;
        player->MoveUD(posYplayer);
        player->SetOnCube(true);
        v_y2=0;
        return 0;
    }
    return 0;
}