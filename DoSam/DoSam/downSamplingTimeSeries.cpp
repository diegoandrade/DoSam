//
//  downSamplingTimeSeries.cpp
//  DoSam
//
//  Created by Diego Andrade on 6/8/15.
//  Copyright (c) 2015 Intelestial. All rights reserved.
//

#include "downSamplingTimeSeries.h"

#undef DEBUG
//#define DEBUG
#ifdef DEBUG
#  define D(x) x
#else
#  define D(x)
#endif // DEBUG


downSamplingTimeSeries::downSamplingTimeSeries()
{
    alfa = beta = gama = 0;
}

void downSamplingTimeSeries::downSampling( int totalNumberOfElements, int numberToDownSample, dataPoint * baseData)
{
    
    
    operablePoints = (dataPoint *) malloc(totalNumberOfElements*sizeof(dataPoint));
    downSampleResult = (dataPoint *) malloc(numberToDownSample*sizeof(dataPoint));
    areaPerPoint = (double *) malloc(totalNumberOfElements*sizeof(double));
    
    
    
    for (int i=0; i< totalNumberOfElements; i++)
    {
        operablePoints[i] = baseData[i];
        
        D(printf("operablePoints[%i]: %f\n", i, operablePoints[i].y););
    }
    
    nopb = numberOfElementsPerBin(totalNumberOfElements,numberToDownSample,nopb);
    ntds = numberToDownSample;
    
    D(printf("number of elements per bin: %d\n", nopb));
    
    double area = 0;
    
    //double area2 = 0;
    
    //findAreaGivenThreePoints(area, baseData[3], baseData[5], baseData[6]);
    //findArea(area2, 15.0, 15, 23, 30, 50, 25);
    
    //printf("basepoint A: %f \n", operablePoints[3].y);
    //printf("basepoint B: %f \n", operablePoints[5].y);
    //printf("basepoint C: %f \n", operablePoints[6].y);
    
    //printf("The area of the triangle is: %f \n", area);
    //printf("The area2 of the triangle is: %f \n", area2);
    
    areaPerPoint[0] = 0;
    
    for (int i=1; i<totalNumberOfElements-2; i++)
    {
        findAreaGivenThreePoints(area, baseData[i], baseData[i+1], baseData[i+2]);
        areaPerPoint[i] = area;
        
        D(printf("The area of the triangle[%d] is: %f \n", i, areaPerPoint[i]);)

    }
    
    areaPerPoint[totalNumberOfElements-1] = 0;
    
    int k=0;
    
  
    for (int i=0 ; i < ntds; i++)
    {
        for (int j=0 ; j< nopb ; j++)
        {
            k=j+i*nopb;
            //printf("The area of the triangle[%d] \n", k);
            if(areaPerPoint[k+1]>areaPerPoint[k])
            {
                downSampleResult[i].x = baseData[k+1].x;
                downSampleResult[i].y = baseData[k+1].y;
            }
            else
            {
                downSampleResult[i].x = baseData[k].x;
                downSampleResult[i].y = baseData[k].y;
            }
        }
    }
    
    downSampleResult[0].x = baseData[0].x;
    downSampleResult[0].y = baseData[0].y;
    downSampleResult[ntds-1].x = baseData[totalNumberOfElements-1].x;
    downSampleResult[ntds-1].y = baseData[totalNumberOfElements-1].y;
    
    /*printf("\n");
    for (int i = 0 ; i< ntds; i++)
    {
          printf("time[%d]: %ld \t value[%d]: %f\n",i,downSampleResult[i].x,i,downSampleResult[i].y);
    }
     */
    
    const char* file = "output.txt";
    printToFile(file , downSampleResult, ntds);
    
    
    free(operablePoints);
    free(downSampleResult);
    free(areaPerPoint);
    
}

void downSamplingTimeSeries::randDownSampling(int totalNumberOfElements, int numberToDownSample, dataPoint *baseData)
{
    operablePoints = (dataPoint *) malloc(totalNumberOfElements*sizeof(dataPoint));
    downSampleResult = (dataPoint *) malloc(numberToDownSample*sizeof(dataPoint));
    areaPerPoint = (double *) malloc(totalNumberOfElements*sizeof(double));
    
    for (int i=0; i< totalNumberOfElements; i++)
    {
        operablePoints[i] = baseData[i];
        
        D(printf("operablePoints[%i]: %f\n", i, operablePoints[i].y););
    }
    
    nopb = numberOfElementsPerBin(totalNumberOfElements,numberToDownSample,nopb);
    ntds = numberToDownSample;
    
    D(printf("number of elements per bin: %d\n", nopb));
    
#pragma mark  ---- CURRENT----
    
    srand (time(NULL)); //initializes random function ... make sure this does not go onto production review WARNING!
    
    for (int i=0 ; i < ntds; i++)
    {
            //k=j+i*nopb;
        
            int k=(rand() % ntds )+i*nopb; //creates a random function between 0 and the ntds
            D(printf("The number k: %d\n", k);)

        
            downSampleResult[i].x = baseData[k+1].x;
            downSampleResult[i].y = baseData[k+1].y;
    }
    
    downSampleResult[0].x = baseData[0].x;
    downSampleResult[0].y = baseData[0].y;
    downSampleResult[ntds-1].x = baseData[totalNumberOfElements-1].x;
    downSampleResult[ntds-1].y = baseData[totalNumberOfElements-1].y;
    
    const char* file = "output.txt";
    printToFile(file , downSampleResult, ntds);
    
    free(operablePoints);
    free(downSampleResult);
    free(areaPerPoint);
    
}

void downSamplingTimeSeries::findAreaGivenThreePoints(double & area, dataPoint & A, dataPoint & B, dataPoint & C)
{
    
    alfa = A.x*(B.y-C.y);
    beta = B.x*(C.y-A.y);
    gama = C.x*(A.y-B.y);
    
    area = abs((alfa+beta+gama)/2);
    
}

void downSamplingTimeSeries:: findArea ( double & area, double  Ax, double Ay, double Bx, double By, double Cx, double Cy)
{
    alfa = Ax*(By-Cy);
    beta = Bx*(Cy-Ay);
    gama = Cx*(Ay-By);
    
    area = abs((alfa+beta+gama)/2);

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

void downSamplingTimeSeries::printToFile(const char* file, dataPoint * downSampleResult, int ntds)
{
    ofstream myfile;
    myfile.open (file);
    
    for (int i = 0 ; i< ntds; i++)
    {
               myfile <<  downSampleResult[i].x << "\t" << downSampleResult[i].y << endl ;

    }
    
    //myfile << "by Diego Andrade.\nAll Rights Reserved 2015\n";
    
    myfile.close();
}


