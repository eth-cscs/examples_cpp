
/*
*********************************************
GCC (dai_GNU_6.2.0_haswell.exe)
*********************************************
*/

// back-translation of assembly to C

int nLoop = 10000000;
for (int n=0; n < nLoop; ++n)
for (int i=0; i < 768; i+=12)
{
    __m256d ymm0 = loadAVX(A[i]);
    __m256d ymm1 = loadAVX(A[i+4]);
    __m256d ymm2 = loadAVX(A[i+8]);

    ymm0 = subAVX(ymm0, B[i]);
    ymm1 = subAVX(ymm1, B[i+4]);
    ymm2 = subAVX(ymm2, B[i+8]);

    C[i]  = storeAVX(ymm0);
    C[i+4] = storeAVX(ymm1);
    C[i+8] = storeAVX(ymm2);
}



/*
*********************************************
CRAY (dai_CRAY_8.7.3_haswell.exe)
*********************************************
*/

// back-translation of assembly to C

double C_temp[3]; // located at stackpointer + 18576 bytes 18576(%rsp)
int nLoop = 10000000;
for (int n=0; n < nLoop; ++n)
for (int i=0; i < 256; ++i)
{
    double x = A[i][0];
    x -= B[i][0];
    C_temp[0] = x;

    double y = A[i][1];
    y -= B[i][1];
    C_temp[1] = y;

    double z = A[i][2];
    z -= B[i][2];
    C_temp[2] = z;

    for (int j=0; j < 3; ++j)
        C[i][j] = C_temp[j];
}
