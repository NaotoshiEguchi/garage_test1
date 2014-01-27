///Users/eguchi/project/cocos2d_test/cocos2d_test.xcodeproj
//  SceneManager.h
//  cocos2d_test
//
//  Created by eguchi on 2014/01/26.
//
//

#ifndef __cocos2d_test__SceneManager__
#define __cocos2d_test__SceneManager__

#include <list>
#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class AsTaskSystem;

class Scene : public CCLayer
{
public:
    virtual bool init();
    static Scene *Create();
    CREATE_FUNC(Scene);
    void SetCCScene(CCScene *pScene) {m_pScene = pScene;}
    CCScene *GetCCScene() {return m_pScene;}
    
private:
    void update(float delta);
    
    void menuCloseCallback(CCObject* pSender);
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
    AsTaskSystem *m_pTaskSystem;
    CCScene *m_pScene;

};

class SceneManager
{
public:
    SceneManager();
    ~SceneManager();


    static SceneManager *GetInstance() {
        return m_pInstance;
    }
    CCLayer *GetLayer();
    CCScene *GetScene();
    
private:
    Scene *m_pScene;
    CCLayer *m_pLayer;
    
    static SceneManager *m_pInstance;
};

#endif /* defined(__cocos2d_test__SceneManager__) */
