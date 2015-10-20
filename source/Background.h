/* 
 * File:   Background.h
 * Author: Ophelie
 *
 * Created on 9 octobre 2015, 18:45
 */

#ifndef BACKGROUND_H
#define	BACKGROUND_H
#include <3ds.h>
#include <stdio.h>
#include "Player.h"
#include "Block.h"
class Background : public Block{
public:
    Background();
    Background(const Background& orig);
    virtual ~Background();
    int DrawAndHit(Player*,bool);
private:

};

#endif	/* BACKGROUND_H */

