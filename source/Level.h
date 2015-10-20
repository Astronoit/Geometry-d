/* 
 * File:   Level.h
 * Author: Silvermoon
 *
 * Created on 3 octobre 2015, 13:46
 */

#ifndef LEVEL_H
#define	LEVEL_H
#include <string.h>
#include <stdio.h>
#include <stdlib.h> 
#include <vector>
#include "Block.h"
#include "Cube.h"
#include "Floor.h"
#include "Spike.h"
#include "Player.h"

class Level {
public:
    Level();
    Level(const Level& orig);
    virtual ~Level();

    int DrawAndHit(Player*,bool);
    bool Load(const char*);
    
    
private:
    std::vector<Block*> array;
};

#endif	/* LEVEL_H */

