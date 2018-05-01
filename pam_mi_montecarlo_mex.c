/*
 * pam_mi_montecarlo_mex.c - Compute MI for PAM using MonteCarlo
 *
 * Usage: pam_mi_montecarlo_mex(C, sigma2, a-y, Pk)
 * C     :=   Real constellation in Gray-mapping order
 * sigma2:=   Noise variance (average)
 * a-y   :=   Received noise (transmitted-received symbols)
 * Pk    :=   Probability of each constellation symbol
 *
 * Compile with: mex -lm -R2018a qam_llr_mex.c
 * (requires MATLAB R2018a or newer versions)
 * Works under 64-bit Linux. Don't know/care under other OSs.
 *
 * 2018 - Dario Pilori <dario.pilori@polito.it>
 */
#include <math.h>
#include <omp.h> 
#include <stdio.h>
#include "capacity_functions.h"
#include "mex.h"

/* Gateway function */
void mexFunction(int nlhs, mxArray *plhs[],
        int nrhs, const mxArray *prhs[])
{
    size_t M, Ns;                   /* constellation and data size */
    double *C, *y;          /* Data and constellation */
    double *Pk;                 
    double s2, mi;
    
    /* Verify input */
    if(nrhs != 4) {
        mexErrMsgIdAndTxt("DspLibrary:qam_mi_montecarlo:nrhs",
                "Four inputs required.");
    }
    
    /* Verify output */
    if(nlhs > 1) {
        mexErrMsgIdAndTxt("DspLibrary:qam_mi_montecarlo:nlhs",
                "Max one output.");
    }
    
    /* Get sizes */
    M = mxGetM(prhs[0]);
    Ns = mxGetM(prhs[2]);
    
    /* Get noise variance */
    s2 = mxGetScalar(prhs[1]);
        
    /* Get constellation and received data */
    C = mxGetDoubles(prhs[0]);
    y = mxGetDoubles(prhs[2]);
    
    /* Get probabilities */
    Pk = mxGetDoubles(prhs[3]);
        
    /* Call function */
    mi = pam_montecarlo_mi(y, Ns, C, Pk, M, s2);
    
    /* get a pointer to the output matrix */
    plhs[0] = mxCreateDoubleScalar(mi);
}