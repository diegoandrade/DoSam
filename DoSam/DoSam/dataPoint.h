//
//  dataPoint.h
//  DoSam
//
//  Created by Diego Andrade on 6/8/15.
//  Copyright (c) 2015 Intelestial. All rights reserved.
//

#ifndef __DoSam__dataPoint__
#define __DoSam__dataPoint__

#include "Common.h"

class dataPoint
{
    
protected:
    double value[2];

    
public:
    //~dataPoint();                                           //Destructor
    inline dataPoint();                                     //Constructor
    inline dataPoint(const double &x, const double &y);
    
    struct {
        time_t x;
        double y;
    };
    
};

//-------------------------------------------------------------------

inline dataPoint::dataPoint()
{
    y = 0;
    x = time(0);
}

inline dataPoint::dataPoint(const double &x,const double &y)
{
    value[0] = x;
    value[1] = y;
}

#endif /* defined(__DoSam__dataPoint__) */
