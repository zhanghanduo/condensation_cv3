//
// Created by hd on 18-6-27.
//

#include "random.hpp"

/* Changes RNG range while preserving RNG state */
void  cvRandSetRange( CvRandState* state, double param1, double param2, int index)
{
    if( !state )
    {
        cvError( CV_StsNullPtr, "cvRandSetRange", "Null pointer to RNG state", "cvcompat.h", 0 );
        return;
    }

    if( (unsigned)(index + 1) > 4 )
    {
        cvError( CV_StsOutOfRange, "cvRandSetRange", "index is not in -1..3", "cvcompat.h", 0 );
        return;
    }

    if( index < 0 )
    {
        state->param[0].val[0] = state->param[0].val[1] =
        state->param[0].val[2] = state->param[0].val[3] = param1;
        state->param[1].val[0] = state->param[1].val[1] =
        state->param[1].val[2] = state->param[1].val[3] = param2;
    }
    else
    {
        state->param[0].val[index] = param1;
        state->param[1].val[index] = param2;
    }
}


void  cvRandInit( CvRandState* state, double param1, double param2,
                  int seed, int disttype)
{
    if( !state )
    {
        cvError( CV_StsNullPtr, "cvRandInit", "Null pointer to RNG state", "cvcompat.h", 0 );
        return;
    }

    if( disttype != CV_RAND_UNI && disttype != CV_RAND_NORMAL )
    {
        cvError( CV_StsBadFlag, "cvRandInit", "Unknown distribution type", "cvcompat.h", 0 );
        return;
    }

    state->state = (uint64)(seed ? seed : -1);
    state->disttype = disttype;
    cvRandSetRange( state, param1, param2, -1 );
}


/* Fills array with random numbers */
void cvRand( CvRandState* state, CvArr* arr )
{
    if( !state )
    {
        cvError( CV_StsNullPtr, "cvRand", "Null pointer to RNG state", "cvcompat.h", 0 );
        return;
    }
    cvRandArr( &state->state, arr, state->disttype, state->param[0], state->param[1] );
}


void cvbRand( CvRandState* state, float* dst, int len )
{
    CvMat mat = cvMat( 1, len, CV_32F, (void*)dst );
    cvRand( state, &mat );
}
