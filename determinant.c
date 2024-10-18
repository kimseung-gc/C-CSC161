#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int matrixInd(int row, int col, int size){
    int linearInd = 0;
    linearInd = col+size*row;
    return linearInd;
}

void printMatrix(double matrix[], int size){
    for(int i = 0; i<size; i++){
        for(int j = 0;j<size; j++){
            printf("%lf   ", matrix[matrixInd(i, j, size)]);
        }
        printf("\n");
    }
}

double * generateRandMatrix(int size){
    double * matrix = (double *)malloc(size*size*sizeof(double));
    for(int i = 0; i<size;i++){
        for(int j = 0; j<size; j++){
            matrix[matrixInd(i,j,size)] = drand48()+((double)(rand())*(double)(rand()));
        }
    }
    return matrix;
}

double determinantHelper(double matrix[], int i, int size){
    if(matrix == NULL){
        return 0.0;
    }
    if(size == 1){
        return matrix[0];
    }
    double tempMat[(size-1)*(size-1)];
    for(int j = 1; j < size; j++){
        for(int k = 0; k < size; k++){
            if(i>k){
                tempMat[matrixInd(j-1, k, size-1)] = matrix[matrixInd(j, k, size)];
            }else if(i < k){
                tempMat[matrixInd(j-1, k-1, size-1)] = matrix[matrixInd(j, k, size)];
            }
        }
    }
    //printMatrix(tempMat, size-1);
    if(size-1 == i){
        return pow(-1.0, i)*matrix[matrixInd(0, i, size)]*determinantHelper(tempMat, 0, size-1);
    }
    return determinantHelper(matrix, i+1, size) + pow(-1.0, i)*matrix[matrixInd(0, i, size)]*determinantHelper(tempMat, 0, size-1);
}

double determinantBetter(double matrix[], int size)
{
     double ratio = 0.0, det=1;
	 int i,j,k = 0;

    /* Here we are using Gauss Elimination
    Technique for transforming matrix to
    upper triangular matrix */
	/* Applying Gauss Elimination */
	 for(i=0;i< size;i++)
	 {
		  if(matrix[matrixInd(i, i, size)] == 0.0)
		  {
			   return 0.0;
		  }
		  for(j=i+1;j< size;j++)
		  {
			   ratio = matrix[matrixInd(i, j, size)]/matrix[matrixInd(i, i, size)];

			   for(k=0;k< size;k++)
			   {
			  		matrix[matrixInd(j, k, size)] = matrix[matrixInd(j, k, size)] - ratio*matrix[matrixInd(i, k, size)];
			   }
		  }
	 }

	 /* Displaying upper triangular matrix */
	 
	 /* Not required, just for the sake of understanding */
	 
	 /* By analyzing upper triangular matrix you 
	 will get what's going on :) */
	 for(i=0;i< size;i++)
	 {
		  for(j=0;j< size;j++)
		  {
			   printf("%0.2f\t",matrix[matrixInd(i, j, size)]);
		  }
		  printf("\n");
	 }

	 /* Finding determinant by multiplying
	 elements in principal diagonal elements */
	 for(i=0;i< size;i++)
     {
         det = det * matrix[matrixInd(i, i, size)];
     }

	 printf("\n\nDeterminant of given matrix is: %0.3f\n", det);
	 return det;
}

double determinant(double matrix[], int size, int option){
    if(option == 1){
        return determinantHelper(matrix, 0, size);
    }
    else if (option == 2){
        return determinantBetter(matrix, size);
    }else{
        return 0;
    }
}

int main(){
    clock_t start, end;
    double t_used;
    start = clock();
    int size = 12;
    srand(time(0));
    double * matrix = generateRandMatrix(size);
    //printMatrix(matrix, size);
    //printf("%lf\n", determinant(matrix, size, 2));
    printf("%lf\n", determinant(matrix, size, 1));
    end = clock();
    t_used = ((double)(end-start))/CLOCKS_PER_SEC;
    printf("%lf\n", t_used);
    printf("%lf\n", __DBL_MAX__);
    return 0;
}