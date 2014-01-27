//
//  root.cpp
//  cocos2d_test
//
//  Created by eguchi on 2014/01/25.
//
//


#include "root.h"
#include "sequence.h"

using namespace cocos2d;

RootTask::RootTask(AsTaskSystem *pSystem, cocos2d::CCLayer *pLayer) :
AsTask(pSystem),
m_pLayer(pLayer)
{
    new Sequence(this);
}

RootTask::~RootTask()
{
    
}

void RootTask::Main()
{

    
}

void RootTask::Draw()
{

}
