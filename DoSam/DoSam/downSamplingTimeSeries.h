//
//  downSamplingTimeSeries.h
//  DoSam
//
//  Created by Diego Andrade on 6/8/15.
//  Copyright (c) 2015 Intelestial. All rights reserved.
//

#ifndef __DoSam__downSamplingTimeSeries__
#define __DoSam__downSamplingTimeSeries__

#include "Common.h"
#include "dataPoint.h"

class downSamplingTimeSeries
{
public:
    //~downSamplingTimeSeries();      //Destructor
    downSamplingTimeSeries();		//Constructor
    void downSampling( int totalNumberOfElements, int numberToDownSample, dataPoint * baseData);
    void randDownSampling ( int totalNumberOfElements, int numberToDownSample, dataPoint * baseData);
    
    int tnoe ; // total number Of Elements;
    int nopb ; // number Of Elements Per Bin;
    int ntds ; // number to DownSampling Values the values to downsize the population of points

    void findAreaGivenThreePoints (double & area , dataPoint & A, dataPoint & B, dataPoint & C);
    void findArea ( double & area, double Ax, double Ay, double Bx, double By, double Cx, double Cy);
    int numberOfElementsPerBin(int totalNumberOfElements, int numberToDownSample, int & numberOfElementsPerBinT);
   
    
    dataPoint * operablePoints;
    dataPoint * downSampleResult;
    double * areaPerPoint;
    
    double alfa, beta, gama;
    
private:
    void printToFile (const char* file, dataPoint * downSampleResult, int ntds);
    
};

#endif /* defined(__DoSam__downSamplingTimeSeries__) */
