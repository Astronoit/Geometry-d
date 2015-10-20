/* 
 * File:   Level.cpp
 * Author: Silvermoon
 * 
 * Created on 3 octobre 2015, 13:46
 */

#include "Level.h"
#include "Floor.h"
#include "Background.h"
#include "FinishLine.h"

Level::Level() {
}



Level::Level(const Level& orig) {
}

Level::~Level() {
    while (!this->array.empty()){
        delete (this->array.back());
        this->array.pop_back();
    }
    this->array.~vector();
}
bool Level::Load(const char* path){
    while (!this->array.empty()){
        delete (this->array.back());
        this->array.pop_back();
    }
    FILE * fp;
    char line[128];
    char *buf;
    Block* block;
    int i=0;
    fp=fopen(path,"r");
    if (fp == NULL)
        return false;
    while (fgets(line, sizeof(line), fp)) {
        i=0;
        buf = strtok(line,";");
        while (buf != NULL)
        {
            if(i==0){
                if(!strcmp(buf,"Floor")){
                    block=new Floor();
                    block->SetTexture(floor_texture);
                    block->SetHeight(floor_texture->height);
                    block->SetWidth(floor_texture->width);
                } else if(!strcmp(buf,"Cube")){
                    block=new Cube();
                    block->SetTexture(cube_texture);
                    block->SetHeight(cube_texture->height);
                    block->SetWidth(cube_texture->width);
                } else if(!strcmp(buf,"Spike")) {
                    block=new Spike();
                    block->SetTexture(spike_texture);
                    block->SetHeight(spike_texture->height);
                    block->SetWidth(spike_texture->width);
                } else if(!strcmp(buf,"Finish")) {
                    block=new FinishLine();
                    block->SetTexture(finish_texture);
                    block->SetHeight(finish_texture->height);
                    block->SetWidth(finish_texture->width);
                }
            } else if(i==1){
                block->SetX(atoi(buf));
            } else if(i==2){
                block->SetY(atoi(buf));
            }
            buf = strtok (NULL, ";");
            i++;
        }
        this->array.push_back(block);
        
    }
    fclose(fp);
    block=new Background();
    block->SetTexture(bg_texture);
    block->SetHeight(bg_texture->height);
    block->SetWidth(bg_texture->width);
    this->array.push_back(block);
    
    return true;
}
int Level::DrawAndHit(Player *player,bool left){
    this->array[array.size()-1]->DrawAndHit(player,left);
    for(int i=0;i<(int)this->array.size()-1;i++){
        if((this->array[i]->GetX()+this->array[i]->GetWidth() >= player->GetX()-PLAYER_X) && (this->array[i]->GetX() <= player->GetX()+(TOP_WIDTH-PLAYER_X))){
            static int state=0;
            state = this->array[i]->DrawAndHit(player,left);
            if(state==TOUCHED){
                return TOUCHED;
            } else if (state==FINISH){
                return FINISH;
            }
        }
    }
    
    return 0;
    
}
