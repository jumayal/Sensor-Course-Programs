
#ifndef MATRIX_ANGLESROTATION_UTILS_H
#define	MATRIX_ANGLESROTATION_UTILS_H

void findAngles (float r[3][3],float output[3]);
float radian2degrees(float rad);
float degrees2radian (float deg);
void printMatrix(float *r,int row, int column);
void multiplyMatrix3x3(float Ma [3][3],float Mb [3][3], float output [3][3]);
void multiplyMatrixScalar(float scalar, float* M, float *input, int row, int column);
float norm(float* m, int length);
float sinc(float angle);
void rcross(float w[3],float output[3][3]);
void int_exp(float R[3][3],float w[3],float deltaT, float output[3][3]);
void addMatrix(float ma[3][3],float mb[3][3], float output [3][3]);
void forward_integration(float R[3][3], float w[3], float deltaT, float output [3][3]);
void copyMatrixR(float Ma[3][3], float R[3][3]);

#endif