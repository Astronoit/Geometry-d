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

bool Cube::DrawAndHit(Player* player){
    sf2d_draw_texture(this->texture,this->x-player->GetX()+PLAYER_X,this->y);
    if(player->GetX()+player->GetWidth()>this->x && player->GetX()<this->x+cube_img.width &&
    (int)(player->GetY()+player->GetHeight())>=this->y && (int)(player->GetY()+player->GetHeight())<= this->y+cube_img.height ){
        posYplayer=this->y-player->GetHeight();
        player->SetJump(false);
        sf2d_draw_rectangle(10,20,20,20,RGBA8(0x00, 0xFF, 0x00, 0xFF));
        player->MoveUD(this->y-player->GetHeight());
        player->SetOnCube(true);
        v_y2=0;
        return false;
    }
    return false;
}