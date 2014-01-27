//
//  spriteManager.h
//  cocos2d_test
//
//  Created by eguchi on 2014/01/25.
//
//

#ifndef __cocos2d_test__spriteManager__
#define __cocos2d_test__spriteManager__

#include <list>
#include <iostream>

#include "cocos2d.h"
#include "as_task.h"

using namespace cocos2d;


class Sprite
{
public:
    Sprite(CCSprite *pSprite, CCLayer *pLayer);
    virtual ~Sprite();
    
    CCSprite *GetCCSprite() {return m_pSprite;}
    
private:
    CCSprite *m_pSprite;
};

class SpriteManager : public AsTask
{
public:
    SpriteManager(AsTask *pTask);
    ~SpriteManager();

    void Add(Sprite *pSprite);
    static SpriteManager *GetInstance() {return m_pInstance;}
    std::list<Sprite *> GetList() {return m_lSprite;}
    
private:
    void Main();
    
    std::list<Sprite *> m_lSprite;
    
    static SpriteManager *m_pInstance;
};

#endif /* defined(__cocos2d_test__spriteManager__) */
