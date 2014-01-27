//
//  sequence.h
//  cocos2d_test
//
//  Created by eguchi on 2014/01/25.
//
//

#ifndef __cocos2d_test__sequence__
#define __cocos2d_test__sequence__

#include "as_task.h"

class Sequence : public AsTask
{
public:
    Sequence(AsTask *pTask);
    ~Sequence();
    
private:
    void Main();
    
    int m_Mode;
};


#endif /* defined(__cocos2d_test__sequence__) */
