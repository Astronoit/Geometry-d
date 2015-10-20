/* 
 * File:   FinishLine.h
 * Author: Ophelie
 *
 * Created on 19 octobre 2015, 18:00
 */

#ifndef FINISHLINE_H
#define	FINISHLINE_H
#include "Block.h"
#include "Player.h"
#include "Block.h"
class FinishLine : public Block {
public:
    FinishLine();
    FinishLine(const FinishLine& orig);
    virtual ~FinishLine();
    int DrawAndHit(Player*,bool);
private:

};

#endif	/* FINISHLINE_H */

