/*
 * random.hpp
 *
 *  Created on: JUN 27, 2018
 *      Author: Zhang Handuo
 *   Institute: NTU, ST Corp Lab
 */

#ifndef RANDOM_H
#define RANDOM_H

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/imgproc_c.h"


typedef struct CvRandState
{
    CvRNG     state;    /* RNG state (the current seed and carry)*/
    int       disttype; /* distribution type */
    CvScalar  param[2]; /* parameters of RNG */
} CvRandState;

/* Changes RNG range while preserving RNG state */
CV_EXPORTS void  cvRandSetRange( CvRandState* state, double param1,
                                 double param2, int index CV_DEFAULT(-1));

CV_EXPORTS void  cvRandInit( CvRandState* state, double param1,
                             double param2, int seed,
                             int disttype CV_DEFAULT(CV_RAND_UNI));
/* Fills array with random numbers */
void cvRand( CvRandState* state, CvArr* arr );
void cvbRand( CvRandState* state, float* dst, int len );

#endif