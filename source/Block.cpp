/* 
 * File:   Block.cpp
 * Author: Silvermoon
 * 
 * Created on 3 octobre 2015, 12:52
 */

#include "Block.h"

Block::Block() {
}

Block::Block(sf2d_texture *text,int xPos,int yPos,int Height,int Width){
    x=xPos;
    y=yPos;
    texture=text;
    height=Height;
    width=Width;
    
}
Block::Block(const Block& orig) {
}

Block::~Block() {
}
