//
//  dataExtraction.cpp
//  DoSam
//
//  Created by Diego Andrade on 6/8/15.
//  Copyright (c) 2015 Intelestial. All rights reserved.
//
//  This class creates data and extracts data from a given file
//


#include "Common.h"
#include "dataExtraction.h"

//#undef DEBUG
#define DEBUG
#ifdef DEBUG
#  define D(x) x
#else
#  define D(x)
#endif // DEBUG


dataExtraction::dataExtraction()
{
    
    
}

dataExtraction::~dataExtraction()
{
    
    
}

dataPoint * dataExtraction::extracDataFromFile(const char* file)
{
    numberOfElements = numberOfElementsInFile(file);
    pointsExtracted = (dataPoint *) malloc(numberOfElements*sizeof(dataPoint));
    
    int lnCounter = 0;
    string tempValue[2];
    double tnVal[2];
    std::string::size_type sz;   // alias of size_t
    
    try
    {
        string line;
        string str = "";
        str.append(file);
        
        ifstream myfile (str);

        if (myfile.is_open())
        {
            
            while ( getline (myfile,line))
            {
                istringstream iss(line);
                
                vector<string> tokens;
                copy(istream_iterator<string>(iss),
                     istream_iterator<string>(),
                     back_inserter(tokens));
                
                
                for(int k=0; k < 2; k++){
                    tempValue[k] = tokens[k];
                    tnVal[k] = stod(tempValue[k], &sz);
                }
                
                pointsExtracted[lnCounter].x = tnVal[0];
                pointsExtracted[lnCounter].y = tnVal[1]; //ojo aqui
                
                D(cout <<  "Point[" << lnCounter << "].x : " << setprecision(9) << pointsExtracted[lnCounter].x << endl;)
                D(cout <<  "Point[" << lnCounter << "].y : " << pointsExtracted[lnCounter].y << fixed << endl;)

                lnCounter++;
                
            }
            
        }
        
    }
    catch(...)
    {
        cout << "Exception ocurred extracDataFromFile!\n\n";
    }
    
    return pointsExtracted ;
    
}

int dataExtraction::numberOfElementsInFile(const char *file)
{
    int linecounter = 0;
    string tempValue = "";
    
    try
    {
        string line;
        string str = "";
        str.append(file);
        
        ifstream myfile (str);
        
        if (myfile.is_open())
        {
            
            while ( getline (myfile,line))
            {
                
                D(cout << "lineCounter: " << linecounter << endl;)
                linecounter++;
            }
            
            myfile.close();
            
            
        }
        
        else cout << "Unable to open file";
    }
    
    catch (...)
    {
        cout << "Exception ocurred numberOfElementsInFile";
        
    }
    
    return linecounter;
    
}