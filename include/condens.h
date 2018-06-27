/*
 * condens.h
 *
 *  Created on: JUN 27, 2018
 *      Author: Zhang Handuo
 *   Institute: NTU, ST Corp Lab
 */

#ifndef CONDENS_H
#define CONDENS_H

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/ml/ml.hpp"
#include "opencv2/core/core.hpp"
#include "random.hpp"

typedef struct CvConDensation
{
    int MP;
    int DP;
    float* DynamMatr;       /* Matrix of the linear Dynamics system  */
    float* State;           /* Vector of State                       */
    int SamplesNum;         /* Number of the Samples                 */
    float** flSamples;      /* arr of the Sample Vectors             */
    float** flNewSamples;   /* temporary array of the Sample Vectors */
    float* flConfidence;    /* Confidence for each Sample            */
    float* flCumulative;    /* Cumulative confidence                 */
    float* Temp;            /* Temporary vector                      */
    float* RandomSample;    /* RandomVector to update sample set     */
    struct CvRandState* RandS; /* Array of structures to generate random vectors */
} CvConDensation;

class condens {

public:

    condens() {}
    ~condens() {}

private:

    /* Creates ConDensation filter state */
    CvConDensation* cvCreateConDensation( int dynam_params,
                                          int measure_params,
                                          int sample_count );

    /* Releases ConDensation filter state */
    void cvReleaseConDensation( CvConDensation** condens );

    /* Updates ConDensation filter by time (predict future state of the system) */
    void cvConDensUpdateByTime( CvConDensation* condens);

    /* Initializes ConDensation filter samples  */
    void cvConDensInitSampleSet( CvConDensation* condens, CvMat* lower_bound, CvMat* upper_bound );

};

#endif