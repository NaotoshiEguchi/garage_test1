//
//  spriteManager.cpp
//  cocos2d_test
//
//  Created by eguchi on 2014/01/25.
//
//

#include "spriteManager.h"

Sprite::Sprite(CCSprite *pSprite, CCLayer *pLayer) :
m_pSprite(pSprite)
{
    SpriteManager::GetInstance()->Add(this);
}

Sprite::~Sprite()
{
    
}

SpriteManager *SpriteManager::m_pInstance = NULL;

SpriteManager::SpriteManager(AsTask *pTask):
AsTask(pTask)
{
    m_pInstance = this;
}

SpriteManager::~SpriteManager()
{
    m_pInstance = NULL;
}



void SpriteManager::Main()
{
    
}

void SpriteManager::Add(Sprite *pSprite)
{
    m_lSprite.push_back(pSprite);
}
