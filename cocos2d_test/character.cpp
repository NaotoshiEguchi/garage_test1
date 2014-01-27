//
//  character.cpp
//  cocos2d_test
//
//  Created by eguchi on 2014/01/25.
//
//

#include "character.h"
#include "sceneManager.h"

CharaBase::CharaBase(AsTask *pTask) :
AsTask(pTask)
{
    CCSprite *sprite = CCSprite::create("HelloWorld.png");
    
    CCLayer *layer = SceneManager::GetInstance()->GetLayer();
    m_pSprite = new Sprite(sprite, layer);

    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCRect rect(
            0, 0, 128, 128
    );
    
    sprite->setTextureRect(rect);
    sprite->setPosition( ccp(100, 240) );


    layer->addChild(sprite, 0);
}

CharaBase::~CharaBase()
{
    
}

void CharaBase::Main()
{
    //float y = m_pSprite->getPositionY();
    //m_pSprite->setPositionY(y + 1);
}

void CharaBase::Draw() {}