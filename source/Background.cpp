/* 
 * File:   Background.cpp
 * Author: Ophelie
 * 
 * Created on 9 octobre 2015, 18:45
 */

#include "Background.h"

Background::Background() {
    this->x=0;
    this->y=0;
}

Background::Background(const Background& orig) {
}

Background::~Background() {
}

int Background::DrawAndHit(Player* player,bool left){
    if(left){
        if((this->x + texture->width) < (TOP_WIDTH)){
            sf2d_draw_texture(this->texture,(texture->width + this->x),0);    
        }
        if(this->x + texture->width <= 0){
                this->x=0;
        } 
        sf2d_draw_texture(this->texture,this->x,0);
    } else {
        if((this->x + texture->width) < (TOP_WIDTH)){
            sf2d_draw_texture(this->texture,(texture->width + this->x)+(int)CONFIG_3D_SLIDERSTATE*20,0);    
        }
        if(this->x + texture->width <= 0){
                this->x=0;
        } 
        sf2d_draw_texture(this->texture,this->x+(int)CONFIG_3D_SLIDERSTATE*20,0);
    }
    this->x-=2;
    return 0;
}