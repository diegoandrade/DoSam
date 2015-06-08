//
//  downSamplingTimeSeries.cpp
//  DoSam
//
//  Created by Diego Andrade on 6/8/15.
//  Copyright (c) 2015 Intelestial. All rights reserved.
//

#include "downSamplingTimeSeries.h"

//#undef DEBUG
#define DEBUG
#ifdef DEBUG
#  define D(x) x
#else
#  define D(x)
#endif // DEBUG


downSamplingTimeSeries::downSamplingTimeSeries()
{
    alfa = beta = gama = 0;
}

downSamplingTimeSeries::~downSamplingTimeSeries()
{
    
}

void downSamplingTimeSeries::downSampling( int totalNumberOfElements, int numberToDownSample, dataPoint * baseData)
{
    operablePoints = (dataPoint *) malloc(totalNumberOfElements*sizeof(dataPoint));
    areaPerPoint = (double *) malloc(numberToDownSample*sizeof(double));
    
    
    for (int i=0; i< totalNumberOfElements; i++)
    {
        operablePoints[i] = baseData[i];
        
        D(printf("operablePoints[%i]: %f\n", i, baseData[i].y););
    }
    
    nopb = numberOfElementsPerBin(totalNumberOfElements,numberToDownSample,nopb);
    
    D(printf("number of elements per bin: %d\n", nopb));
    
    #pragma mark  ---- CURRENT----  
    
    double area =0;
    double area2 = 0;
    
   // area2 = findAreaGivenThreePoints(area, operablePoints[1], operablePoints[2], operablePoints[3]);
    
    
    
    /*for (int i=0; i< numberToDownSample; i++)
    {
        for (int j=0; j<nopb-3; j++)
        {
            cout << "[" << j << "]" << operablePoints[j+i*numberToDownSample].y << endl;
           ;
        }
    }*/

    
}

double downSamplingTimeSeries::findAreaGivenThreePoints(double & area, dataPoint A, dataPoint B, dataPoint C)
{
    
    alfa = A.x*(B.y-C.y);
    beta = B.x*(C.y-A.y);
    gama = C.x*(A.y-B.y);
    
    area = abs((alfa+beta+gama)/2);
    
    return area;
}

int downSamplingTimeSeries::numberOfElementsPerBin(int totalNumberOfElements, int numberToDownSample, int & numberOfElementsPerBinT)
{
    
    try
    {
        assert((totalNumberOfElements > numberToDownSample ) && "Number of elemensts is lower than downsampling values has the wrong value!!");
        
        numberOfElementsPerBinT = ceil((totalNumberOfElements-2)/numberToDownSample);//here there is a probable issue;
        
    }
    catch(...)
    {
        cout << "Exception ocurred numberOfBins!\n\n" <<endl;
        
    }
    
    return numberOfElementsPerBinT;
}


