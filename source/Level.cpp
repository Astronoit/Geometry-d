/* 
 * File:   Level.cpp
 * Author: Silvermoon
 * 
 * Created on 3 octobre 2015, 13:46
 */

#include "Level.h"
#include "Floor.h"

Level::Level() {
}



Level::Level(const Level& orig) {
}

Level::~Level() {
    for(int i=0;i<this->array.size();i++){
        delete (this->array[i]);
    }
    this->array.~vector();
}
bool Level::Load(const char* path){
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
    return true;
}
bool Level::DrawAndHit(Player *player){
    for(int i=0;i<(int)this->array.size();i++){
        if(this->array[i]->DrawAndHit(player)){
            return true;
        }
    }
    return false;
    
}
