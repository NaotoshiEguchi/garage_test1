//
//  sequence.cpp
//  cocos2d_test
//
//  Created by eguchi on 2014/01/25.
//
//

#include "sequence.h"
#include "spriteManager.h"
#include "character.h"

Sequence::Sequence(AsTask *pTask) :
AsTask(pTask),
m_Mode(1)
{
    new SpriteManager(this);
}

Sequence::~Sequence()
{
    
}

void Sequence::Main()
{
    switch(m_Mode) {
        case 1:
            new CharaBase(this);
            m_Mode++;
            break;
            
        default:
            break;
    }
}
