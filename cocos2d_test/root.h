//
//  root.h
//  cocos2d_test
//
//  Created by eguchi on 2014/01/25.
//
//

#ifndef cocos2d_test_root_h
#define cocos2d_test_root_h

#include "cocos2d.h"
#include "as_task.h"

class RootTask : public AsTask
{
public:
    RootTask(AsTaskSystem *pSystem, cocos2d::CCLayer *pLayer);
    ~RootTask();
    
private:
    void Main();
    void Draw();
    
    cocos2d::CCLayer *m_pLayer;
};

#endif
