/* 
 * File:   Spike.h
 * Author: Silvermoon
 *
 * Created on 3 octobre 2015, 14:46
 */

#ifndef SPIKE_H
#define	SPIKE_H
#include "Player.h"
#include "Block.h"

class Spike : public Block {
public:
    Spike();
    Spike(sf2d_texture *text,int xPos,int yPos,int Height,int Width);
    Spike(const Spike& orig);
    virtual ~Spike();
    int DrawAndHit(Player*,bool);
private:

};

#endif	/* SPIKE_H */

