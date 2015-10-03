#include <stdio.h>
#include <stdlib.h>		/* srand, rand */

#include <3ds.h>
#include <sf2d.h>
#include "variables.h"
#include "Block.h"
#include "Player.h"

#include "Level.h"
#include "Spike.h"

sf2d_texture *spike_texture;
sf2d_texture *player_texture;    
sf2d_texture *floor_texture;     
sf2d_texture *cube_texture;      
sf2d_texture *gameover_texture;
int posYplayer;
bool launchgame;
bool quit;
bool gameover;
double v_grav;
double v_saut;

double v_y;
double v_y2;
float rad;
int floorpos;
void initTexture(){
    spike_texture = sf2d_create_texture_mem_RGBA8(spike_img.pixel_data, spike_img.width, spike_img.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
    player_texture = sf2d_create_texture_mem_RGBA8(player_img.pixel_data, player_img.width, player_img.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
    floor_texture = sf2d_create_texture_mem_RGBA8(floor_img.pixel_data, floor_img.width, floor_img.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
    cube_texture = sf2d_create_texture_mem_RGBA8(cube_img.pixel_data, cube_img.width, cube_img.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
    gameover_texture = sf2d_create_texture_mem_RGBA8(gameover_img.pixel_data, gameover_img.width, gameover_img.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
	
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
                    floorpos=TOP_WIDTH;
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
    if(player->GetY()>=TOP_WIDTH){
        launchgame=false;
        gameover=true;
    }
    }
int main()
{
    launchgame=false;
    quit=false;
    gameover=false;
    rad=0.0f;
    v_grav = 0.08;
    v_saut = -3;
    v_y = v_saut;
    v_y2=0;
           
    
        
    sf2d_init();

    sf2d_set_clear_color(RGBA8(0xFF, 0xFF, 0xFF, 0xFF));
    initTexture();
    Player *player = new Player(player_texture,PLAYER_X,PLAYER_Y,PLAYER_HG,PLAYER_WD);
    Level *level=new Level();
    level->Load("./level-1.txt");
    PrintConsole BottomScreen;
    consoleInit(GFX_BOTTOM, &BottomScreen);
    int held;
    int posSelect=OPT_MAX;
    while (aptMainLoop())
    {
            hidScanInput();
            held = hidKeysHeld();
            if (held & KEY_START) {
                    break;
            } else if (held & (KEY_L | KEY_R)) {
                    if(launchgame && !player->IsJumping()){
                    player->Jump();
                    }   
            } else if(held & KEY_UP){
                if(posSelect<OPT_MAX)
                    posSelect++;
            } else if(held & KEY_DOWN){
                if(posSelect>1)
                    posSelect--;
            } else if(held & KEY_A){
                if(posSelect==OPT_MAX && !launchgame){
                    launchgame=true;
                    gameover=false;
                }
            }
            if(launchgame){
                handleGame(level,player);
                player->MoveLR(player->GetX()+1);
            } else {
                consoleSelect(&BottomScreen);
                switch(posSelect){
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
            if(gameover){
                launchgame=false;
                sf2d_start_frame(GFX_TOP, GFX_LEFT);
                    sf2d_draw_texture(gameover_texture,0,0);
                sf2d_end_frame();
                player->MoveLR(PLAYER_X);
                player->MoveUD(PLAYER_Y);
            }
            if(player->IsJumping()){
                rad += 0.07f;
            }
            sf2d_swapbuffers();
    }

    
    sf2d_fini();

    return 0;
}
