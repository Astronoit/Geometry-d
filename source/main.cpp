#include <stdio.h>
#include <stdlib.h>		
#include <3ds.h>
#include <sf2d.h>

#include "handle.h"
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
sf2d_texture *bg_texture;
sf2d_texture *finish_texture;
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
int posLevel=0;
//audio
u8* buffer;
u32 size;
#define SAMPLERATE 32000
void initTexture(){
    spike_texture = sf2d_create_texture_mem_RGBA8(spike_img.pixel_data, spike_img.width, spike_img.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
    player_texture = sf2d_create_texture_mem_RGBA8(player_img.pixel_data, player_img.width, player_img.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
    floor_texture = sf2d_create_texture_mem_RGBA8(floor_img.pixel_data, floor_img.width, floor_img.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
    cube_texture = sf2d_create_texture_mem_RGBA8(cube_img.pixel_data, cube_img.width, cube_img.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
    gameover_texture = sf2d_create_texture_mem_RGBA8(gameover_img.pixel_data, gameover_img.width, gameover_img.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
    bg_texture = sf2d_create_texture_mem_RGBA8(bg_img.pixel_data, bg_img.width, bg_img.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
    finish_texture = sf2d_create_texture_mem_RGBA8(finish_img.pixel_data, finish_img.width, finish_img.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
}

void freeTexture(){
    sf2d_free_texture(spike_texture);
    sf2d_free_texture(player_texture);
    sf2d_free_texture(floor_texture);
    sf2d_free_texture(cube_texture);
    sf2d_free_texture(gameover_texture);
    sf2d_free_texture(bg_texture);
    sf2d_free_texture(finish_texture);
	
}

void audio_load(const char *audio){

	FILE *file = fopen(audio, "rb");

	// seek to end of file
	fseek(file, 0, SEEK_END);

	// file pointer tells us the size
	size_t size = ftell(file);

	// seek back to start
	fseek(file, 0, SEEK_SET);

	//allocate a buffer
	buffer =(u8*) linearAlloc(size);

	//read contents !
	size_t bytesRead = fread(buffer, 1, size, file);
	//u8 test = &buffer;

	//close the file because we like being nice and tidy
	fclose(file);

	csndPlaySound(8, SOUND_FORMAT_16BIT | SOUND_REPEAT, SAMPLERATE, 1, 0, buffer, buffer, size);
	linearFree(buffer);
}

void audio_stop(void){
	csndExecCmds(true);
	CSND_SetPlayState(0x8, 0);
	memset(buffer, 0, size);
	GSPGPU_FlushDataCache(NULL, buffer, size);
	linearFree(buffer);
}

int main()
{
    float speed=5.0; 
    launchgame=false;
    quit=false;
    gameover=false;
    rad=0.0f;
    v_grav = 0.12f;
    v_saut = -3.5;
    v_y = v_saut;
    v_y2=0;
    initFilesystem();
    openSDArchive();
    sf2d_init();
    csndInit();//start Audio Lib
    initTexture();
    sf2d_set_3D(1);//Enable 3D
    sf2d_set_clear_color(RGBA8(0xFF, 0xFF, 0xFF, 0xFF));
    Player *player = new Player(player_texture,PLAYER_X,PLAYER_Y,PLAYER_HG,PLAYER_WD);
    Level *level=new Level();
    PrintConsole BottomScreen;
    consoleInit(GFX_BOTTOM, &BottomScreen);
    int held;
    int oldHeld=0;
    int posSelect=OPT_MAX;
    int posLevel=0,nbFile=0;
    bool chooseLevel=false;
    bool selectLevel=false;
    bool screenErased=false;
    audio_load("audio/audio.bin");
    while (aptMainLoop())
    {
            hidScanInput();
            held = hidKeysHeld();
            if(oldHeld!=held){
                if (held & KEY_START) {
                    audio_stop();
                    audio_stop();
                        break;
                } else if (held & (KEY_L | KEY_R)) {
                        if(launchgame && !player->IsJumping()){
                        player->Jump();
                        }   
                } else if(held & KEY_UP){
                    if(posSelect<OPT_MAX)
                        posSelect++;
                    if(chooseLevel && posLevel>0){
                        posLevel--;
                    }
                } else if(held & KEY_DOWN){
                    if(posSelect>1)
                        posSelect--;
                    if(chooseLevel && posLevel<nbFile-1){
                        posLevel++;
                    }
                } else if(held & KEY_A){
                    if(chooseLevel){
                        selectLevel=true;
                    }
                    if(posSelect==OPT_MAX && !launchgame){
                        if(!screenErased){
                            consoleClear();
                            screenErased=true;
                        }
                        chooseLevel=true;
                        launchgame=false;
                        gameover=false;
                    }
                    
                }
            }
            oldHeld=held;
            if(launchgame){
                handleGame(level,player);
                player->MoveLR(player->GetX()+(speed/2));
            } else if(chooseLevel){
                chooseLevel = handleLevelSelection(&posLevel,&nbFile,selectLevel,&launchgame,level);
            } else {
                consoleSelect(&BottomScreen);
                handleMenu(posSelect);
            }
            if(gameover){
                screenErased=false;
                launchgame=false;
                chooseLevel=false;
                selectLevel=false;
                speed=5.0;
                sf2d_start_frame(GFX_TOP, GFX_LEFT);
                    sf2d_draw_texture(gameover_texture,0,0);
                sf2d_end_frame();
                sf2d_start_frame(GFX_TOP, GFX_RIGHT);
                    sf2d_draw_texture(gameover_texture,0,0);
                sf2d_end_frame();
                player->MoveLR(PLAYER_X);
                player->MoveUD(PLAYER_Y);
            }
            if(player->IsJumping()){
                rad += (0.16f);
            }
            sf2d_swapbuffers();
    }
    level->~Level();
    player->~Player();
    audio_stop();
    audio_stop();
    csndExit();
    freeTexture();
    sf2d_fini();
    return 0;
}
