/* 
 * File:   handle.h
 * Author: Silvermoon
 *
 * Created on 6 octobre 2015, 21:25
 */

#ifndef HANDLE_H
#define	HANDLE_H
#include <stdio.h>
#include <stdlib.h>		
#include <dirent.h>
#include <3ds.h>
#include <sf2d.h>

#include "variables.h"
#include "Player.h"
#include "Level.h"
#include "filesystem.h"

bool handleLevelSelection(int *pos,int *nbFile,bool select,bool *launchgame,Level* level);
void handleMenu(int pos);
void handleGame(Level* level,Player* player);



#endif	/* HANDLE_H */

