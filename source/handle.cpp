#include "handle.h"

bool handleLevelSelection(int *pos,int *nbFile,bool select,bool *launchgame,Level* level){
    char* array[1024];
    int size;
    if(!dirRead){
        scanDirectory("/geolevel/",array,&size);
        *nbFile=size;
    }else{
        dirRead=true;
    }
    printf("\x1b[0;0H Choose your level :\n");
    for(int i=0;i<size;i++){
        if(*pos==i){
            printf("-> %s\n",array[i]);
        } else {
            printf("-  %s\n",array[i]);
        }
    }
    if(select){
        level->Load(array[*pos]);
        consoleClear();
        *launchgame=true;
        return false;
    }
    return true;
    
}
void handleMenu(int pos){
    switch(pos){
    case OPT_MAX:
        printf("\x1b[11;14H");
        printf("\x1b[32m> START\n");
        printf("\x1b[12;14H");
        printf("\x1b[32m  OPTIONS\n");
        printf("\x1b[13;14H");
        break;
    case 1:
        printf("\x1b[11;14H");
        printf("\x1b[32m  START\n");
        printf("\x1b[12;14H");
        printf("\x1b[32m> OPTIONS\n");
        break;
    }
}

void handleGame(Level* level,Player* player){
    sf2d_start_frame(GFX_TOP, GFX_LEFT);
    
                    if(!player->IsJumping()){
                        sf2d_draw_texture(player_texture,PLAYER_X,player->GetY());
                    } else {
                        //Gravity stuff.
                        player->MoveUD(v_y+player->GetY());
                        v_y += v_grav;
                        sf2d_draw_texture_rotate(player_texture,PLAYER_X+(player->GetHeight()/2),player->GetY(),rad);
                        if(player->GetY()>=posYplayer){
                            player->SetJump(false);
                            player->MoveUD(posYplayer);
                            v_saut = -3.5;
                            v_y = v_saut;
                            rad=0.0f;
                        }
                    }
                    player->SetOnCube(false);
                    floorpos=TOP_HEIGHT;
                    if(level->DrawAndHit(player)){
                        launchgame=false;
                        gameover=true;
                    }
    
    sf2d_end_frame();
    if(!player->IsOnCube())
        posYplayer=floorpos;
    if(!player->IsOnCube() && !player->IsJumping() && ((int)player->GetY() < floorpos) ){
        player->MoveUD(player->GetY()+v_y2);
        posYplayer=floorpos;
        v_y2 += v_grav*1.2;
    }
    if(player->GetY()>=TOP_HEIGHT){
        launchgame=false;
        gameover=true;
    }
}

