#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <Matrix_AnglesRotation_utils.h>
void int_exp(float R[3][3],float w[3],float deltaT, float output[3][3]){
  float rx[3][3]={0};
  float wx_Scalar[3][3]={0};
  float wxSquared[3][3]={0};
  float wxSquaredScalar[3][3]={0};
  float sum [3][3]={0};
  float w_scalar[3]={0};
  multiplyMatrixScalar(deltaT,(float*)w, (float*)w_scalar,1,3);
  //printf("w*deltaT\n");
  //printMatrix((float*)w_scalar,1,3);
  float wnorm=norm(w_scalar,3);
  float s= sinc((float)wnorm/2);
  float c=cos((float)(wnorm/2));
  //printf("Norm: %f \nS: %f\nC:%f\n",wnorm,s,c);
  rcross(w_scalar,rx);
  multiplyMatrixScalar((float)(s*c),(float*)rx,(float*)wx_Scalar,3,3);
 // printf("s*c*rx\n");
  //printMatrix((float*)wx_Scalar,3,3);
  multiplyMatrix3x3(rx,rx,wxSquared);
  //printf("rx*rx\n");
  //printMatrix((float*)rx,3,3);
  multiplyMatrixScalar((float)(s*(s/2)),(float*)wxSquared,(float*)wxSquaredScalar,3,3);
  //printf("s*s/2*rx^2\n");
  //printMatrix((float*)wxSquaredScalar,3,3);
  addMatrix(wx_Scalar,wxSquaredScalar,output);
  //printf("s*c*rx + s*s/2*rx*rx\n");
  //printMatrix((float*)output,3,3);
  output[0][0]=output[0][0]+1;
  output[1][1]=output[1][1]+1;
  output[2][2]=output[2][2]+1;
}

void forward_integration(float R[3][3], float w[3], float deltaT, float output [3][3]){
  float rx[3][3];
  float product[3][3];
  float w_scalar [3];
  multiplyMatrixScalar(deltaT,(float*)w, w_scalar,3,1);
  rcross(w_scalar,rx);
  multiplyMatrix3x3(rx,R,product);
  addMatrix(product,R,output);
}
void findAngles (float r [3][3],float output [3]){
  if(abs(r[0][2])!= 1){
    output[1]= -1*asin(r[0][2]);
    output[0]= atan2(r[0][1]/cos(-1*asin(r[0][2])),r[0][0]/cos(-1*asin(r[0][2])));
    output[2]= atan2(r[1][2]/cos(-1*asin(r[0][2])),r[2][2]/cos(-1*asin(r[0][2])));
  }else if(r[0][2]>0){
    output[0]=atan2(r[2][1],r[2][0]);
    output[1]=M_PI/2;
    output[3]=0;
  }else{
    output[0]=atan2(-r[2][1],-r[2][0]);
    output[1]=-M_PI/2;
    output[3]=0;
  }
}

float radian2degrees(float rad){
    return ((rad/(M_PI))*180);
}
float degrees2radian (float deg){
    return (deg/360)*2*M_PI;
}

//pass a pointer to a matrix, declare matrix size, and print out values
void printMatrix(float *matrix_ptr,int row, int column){
  int i;
  int j;
  for(j=0;j<row;j++){
    for(i=0;i<column;i++){
      printf("%0.6f ",*(matrix_ptr+column*j+i));
    }
    printf(" \n\r");
  }
  printf("\n\r");
}

//Multiplies two matrices and output it to an array
void multiplyMatrix3x3(float Ma [3][3],float Mb [3][3],float output[3][3]){
  int i;
  int j;
  for(i=0;i<3;i++ ){
    for(j=0;j<3;j++){
      output[i][j] = Ma[i][0]*Mb[0][j]+Ma[i][1]*Mb[1][j]+Ma[i][2]*Mb[2][j];
    }
  }
}

void copyMatrixR(float Ma[3][3], float R[3][3]){
  int i;
  int j;
  for(i=0;i<3;i++ ){
    for(j=0;j<3;j++){
      R[i][j] = Ma[i][j];
    }
  }
}

void addMatrix(float ma[3][3],float mb[3][3], float output [3][3]){
  int i;
  int j;
  for(i=0;i<3;i++ ){
    for(j=0;j<3;j++){
      output[i][j] = ma[i][j]+mb[i][j];
    }
  }
}

//Multiplies an matrix with a scalar and output to a matrix
void multiplyMatrixScalar(float scalar, float* M, float* input, int row, int column){
  int j;
  int i;
  for(i=0;i<row;i++ ){
    for(j=0;j<column;j++){
      *(input+column*i+j) = *(M+column*i+j) * scalar;
    }
  }
}

//Returns the normal of a specified n-dimension vector
float norm(float m[3], int n){
  float sum=0;
  int i;
  for(i=0;i<n;i++){
    sum= sum+pow(m[i],2);
  }

  return sqrt(sum);
}

void rcross(float w[3],float output[3][3]){
    output[0][1]=-w[2];
    output[0][2]=w[1];
    output[1][0]=w[2];
    output[1][2]=-w[0];
    output[2][0]=-w[1];
    output[2][1]=w[0];
}

float sinc(float angle){
  if(angle !=0){
    return sin(angle)/angle;
  }else{
    return 1;
  }

}
