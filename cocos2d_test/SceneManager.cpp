//
//  SceneManager.cpp
//  cocos2d_test
//
//  Created by eguchi on 2014/01/26.
//
//

#include "SceneManager.h"
#include "root.h"
#include "spriteManager.h"

Scene *Scene::Create()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    Scene *layer = Scene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    layer->SetCCScene(scene);
    
    return layer;
}

bool Scene::init()
{
    
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    
     CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
     "CloseNormal.png",
     "CloseSelected.png",
     this,
     menu_selector(Scene::menuCloseCallback) );
     pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );
     
     // create menu, it's an autorelease object
     CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
     pMenu->setPosition( CCPointZero );
     this->addChild(pMenu, 1);

    m_pTaskSystem = new AsTaskSystem();
    AsTask *pRoot = new RootTask(m_pTaskSystem, this);
    
    
    this->setTouchMode(kCCTouchesOneByOne);
    this->setTouchEnabled(true);
    this->scheduleUpdate();


    return true;
}


void Scene::update(float delta)
{
    m_pTaskSystem->ExecPre();
    m_pTaskSystem->ExecMain();
    m_pTaskSystem->ExecDraw();
    m_pTaskSystem->ExecPost();
    m_pTaskSystem->ExecCleanUp2();
}

bool Scene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    
    CCPoint point = this->convertTouchToNodeSpace(pTouch);
    
    std::list<Sprite *> list = SpriteManager::GetInstance()->GetList();
    std::list<Sprite *>::iterator itr = list.begin();
    for (; itr != list.end(); ++itr) {
        CCSprite *spr = (*itr)->GetCCSprite();
        CCRect rect = spr->getTextureRect();
        rect.origin.x = spr->getPositionX();
        rect.origin.y = spr->getPositionY();
        
        if (rect.containsPoint(point)){
            printf("aaa");
        }
    }
}

void Scene::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
SceneManager *SceneManager::m_pInstance = NULL;

SceneManager::SceneManager()
{
    m_pInstance = this;
    m_pScene = Scene::Create();

}

SceneManager::~SceneManager()
{
    m_pInstance = NULL;
}

CCScene *SceneManager::GetScene()
{
    return m_pScene->GetCCScene();
}

CCLayer *SceneManager::GetLayer()
{
    return m_pScene;
}



