//
//  dataExtraction.h
//  DoSam
//
//  Created by Diego Andrade on 6/8/15.
//  Copyright (c) 2015 Intelestial. All rights reserved.
//

#ifndef __DoSam__dataExtraction__
#define __DoSam__dataExtraction__

#include "Common.h"
#include "dataPoint.h"

class dataExtraction
{
public:
    dataExtraction();		//Constructor
    ~dataExtraction();      //Destructor
    
    dataPoint *  extracDataFromFile( const char* file);
    int numberOfElementsInFile (const char* file);
    
    int numberOfElements;
    dataPoint * pointsExtracted;
};


#endif /* defined(__DoSam__dataExtraction__) */
