#include "Common.h"
#include "dataExtraction.h"
#include "downSamplingTimeSeries.h"

//#undef DEBUG
#define DEBUG
#ifdef DEBUG
#  define D(x) x
#else
#  define D(x)
#endif // DEBUG


dataExtraction objReadDat;
downSamplingTimeSeries objOperateOnData;

int numberOfElements = 0;

void frand ()
{
    
    
}

int main( int argc, char* argv[] )
{
    const char* nvalue = "World" ;
    int tvalue = 1 ;
    int nptd = 0;
    
    //printf("argc = %d\n", argc);
    
    int c ;
    while( ( c = getopt (argc, argv, "ntr:") ) != -1 )
    {
        switch(c)
        {
            case 'n':
                if(optarg) nvalue = optarg;
                else std::cerr << "got a nullptr for optarg for -n\n" ;
                break;
            case 't':
                if(optarg) tvalue = std::atoi(optarg) ;
                break;
            case 'r':
                nptd = atoi(argv[2]);
                dataPoint* pointsExtracted = objReadDat.extracDataFromFile(argv[3]);
                numberOfElements = objReadDat.numberOfElements;
                
                //printf("Number of Elements on this file: %d \n\n ", numberOfElements);
                printf("DoSam downsample %d elements to %d \n", numberOfElements, nptd);
                printf("output.txt contains the list of downsampled values");
                
                objOperateOnData.downSampling(numberOfElements, nptd, pointsExtracted);
                
                free(pointsExtracted);
                
                break;
        }
    }
    
   /* for( int i = 0 ; i < tvalue; ++i )
        std::cout << '[' << i+1 << "] Hello " << nvalue << "!\n" ;
    std::cout << '\n' ;*/
}