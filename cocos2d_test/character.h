//
//  character.h
//  cocos2d_test
//
//  Created by eguchi on 2014/01/25.
//
//

#ifndef cocos2d_test_character_h
#define cocos2d_test_character_h

#include "cocos2d.h"
#include "as_task.h"
#include "spriteManager.h"

using namespace cocos2d;

class CharaBase : public AsTask
{
public:
    static const int SIZE_X = 32;
    static const int SIZE_Y = 32;
    
    CharaBase(AsTask *pTask);
    ~CharaBase();
    
private:
    void Main();
    void Draw();
    
    Sprite *m_pSprite;
};

class CharaMonster : public CharaBase
{
public:
    CharaMonster(AsTask *pTask);
    ~CharaMonster();
    
private:
    void Main();
    void Draw();

};

class CharaMagician : public CharaBase
{
public:
    CharaMagician(AsTask *pTask);
    ~CharaMagician();
    
private:
    void Main();
    void Draw();

};

class CharaKnight : public CharaBase
{
public:
    CharaKnight(AsTask *pTask);
    ~CharaKnight();
    
private:
    void Main();
    void Draw();
};

#endif
