#include "handle.h"
bool handleLevelSelection(int *pos,int *nbFile,bool select,bool *launchgame,Level* level){
    char* array[1024];
    int size;
    scanDirectory("/geolevel/",array,&size);
    *nbFile=size;
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
    int xplayer;
    bool jump=false;
    
    
    
    sf2d_start_frame(GFX_TOP, GFX_LEFT);
                    if(!player->IsJumping()){
                        xplayer=PLAYER_X;
                    } else {
                        //Gravity stuff.
                        jump=true;
                        v_y += v_grav;
                        player->MoveUD(v_y+player->GetY());
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
                    int state = level->DrawAndHit(player,true);
                    if(state==TOUCHED){
                        launchgame=false;
                        gameover=true;
                    } else if (state==FINISH){
                        launchgame=false;
                        win=true;
                    }
                    if(!jump){
                        sf2d_draw_texture(player_texture,PLAYER_X,player->GetY());
                    } else {
                        sf2d_draw_texture_rotate(player_texture,PLAYER_X+(player->GetHeight()/2),player->GetY(),rad);
                    }
    sf2d_end_frame();
    sf2d_start_frame(GFX_TOP, GFX_RIGHT);
                    if(!player->IsJumping()){
                        xplayer=PLAYER_X;
                    } else {
                        //Gravity stuff.
                        jump=true;
                        v_y += v_grav;
                        player->MoveUD(v_y+player->GetY());
                        
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
                    state = level->DrawAndHit(player,false);
                    if(state==TOUCHED){
                        launchgame=false;
                        gameover=true;
                    } else if (state==FINISH){
                        launchgame=false;
                        win=true;
                    }
                    if(!jump){
                        sf2d_draw_texture(player_texture,PLAYER_X,player->GetY());
                    } else {
                        sf2d_draw_texture_rotate(player_texture,PLAYER_X+(player->GetHeight()/2),player->GetY(),rad);
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

