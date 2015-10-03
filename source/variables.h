/* 
 * File:   variables.h
 * Author: Silvermoon
 *
 * Created on 3 octobre 2015, 13:20
 */

#ifndef VARIABLES_H
#define	VARIABLES_H
#define OPT_MAX 2
#define PLAYER_X 64
#define PLAYER_Y 176
#define PLAYER_HG 32
#define PLAYER_WD 32
#define TOP_WIDTH 240
struct image
{
  unsigned int 	 width;
  unsigned int 	 height;
  unsigned int 	 bytes_per_pixel;
  unsigned char	 pixel_data[];
};

extern const struct image spike_img, player_img,floor_img,cube_img,gameover_img;


extern sf2d_texture *spike_texture;
extern sf2d_texture *player_texture;
extern sf2d_texture *floor_texture;
extern sf2d_texture *cube_texture;
extern sf2d_texture *gameover_texture;

extern int posYplayer;
extern bool launchgame;
extern bool quit;
extern bool gameover;
extern double v_grav;
extern double v_saut;

extern double v_y;
extern double v_y2;
extern float rad;
extern int floorpos;
#endif	/* VARIABLES_H */

