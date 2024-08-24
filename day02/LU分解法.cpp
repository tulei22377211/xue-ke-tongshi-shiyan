﻿#include <stdio.h>
#include <stdlib.h>
//与顺序gauss消去法等价


int main(void) {
    // 矩阵大小
    int n;
    // 输入矩阵与右侧向量
    printf("Enter the size of the matrix: ");
    scanf("%d", &n);

    double **A = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        A[i] = (double *)malloc(n * sizeof(double));
    }

    printf("Enter the elements of the matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &A[i][j]);
        }
    }

    double *b = (double *)malloc(n * sizeof(double));
    printf("Enter the elements of the righr-hand side:\n");
    for (int i = 0; i < n; i++) {
        scanf("%lf", &b[i]);
    }
    
    /* printf("The matrix is:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%lf ", A[i][j]);
        }
        printf("\n");
    }
    printf("The righr-hand side is:\n");
    for (int i = 0; i < n; i++) {
        printf("%lf ", b[i]);
    }
    printf("\n"); */

    // 进行LU分解
    double **L = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        L[i] = (double *)malloc(n * sizeof(double));
    }

    double **U = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        U[i] = (double *)malloc(n * sizeof(double));
    }

    //给L和U初始化为0
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            L[i][j] = 0;
            U[i][j] = 0;
        }
    }
   
    //进行LU分解
    
    //对第一行U赋值
    for (int j = 0; j < n; j++) {
        U[0][j] = A[0][j];
    }
    //对第一列L赋值
    L[0][0] = 1;
    for (int i = 1; i < n; i++) {
        L[i][0] = A[i][0] / U[0][0];
    }
    
   
    //对剩余元素进行LU分解
    
    for (int r = 1; r < n; r++) {
        
        //对第r行的U赋值
        for (int i = r; i < n; i++) {
            double sum = 0;
            for (int k = 0; k < r; k++) {
                sum += L[r][k] * U[k][i];
            }
            U[r][i] = A[r][i] - sum;
        }
        //对第r列的L赋值
        for (int i = r; i < n; i++){
            double sum = 0;
            for (int k = 0; k < r; k++){
                sum += L[i][k] * U[k][r];
            }
            if (r != n-1) {
                L[i][r] = (A[i][r] - sum) / U[r][r];
            }
            else if(r == n-1 && i == n-1){
                L[i][r] = 1;
            }
            else{
                L[i][r] = 0;
            }
        }
    }

    //输出L和U
    printf("The L matrix is:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%lf ", L[i][j]);
        }
        printf("\n");
    }
    printf("The U matrix is:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%lf ", U[i][j]);
        }
        printf("\n");
    }
    // 求解y
    double *y = (double *)malloc(n * sizeof(double));
    y[0] = b[0];
    for (int i = 1; i < n; i++) {
        double sum = 0;
        for (int k = 0; k < i; k++) {
            sum += L[i][k] * y[k];
        }
        y[i] = b[i] - sum;
    }

    // 求解x
    double *x = (double *)malloc(n * sizeof(double));
    x[n-1] = y[n-1] / U[n-1][n-1];
    for (int i = n-2; i >= 0; i--) {
        double sum = 0;
        for (int k = i+1; k < n; k++) {
            sum += U[i][k] * x[k];
        }
        x[i] = (y[i] - sum) / U[i][i];
    }

    
    

    // 输出结果
    printf("The solution is:\n");
    for (int i = 0; i < n; i++) {
        printf("%lf\n", x[i]);
    }
    printf("\n");   

    // 释放内存
    for (int i = 0; i < n; i++) {
        free(A[i]);
        free(L[i]);
        free(U[i]);
    }
    free(A);
    free(L);
    free(U);
    free(b);
    free(y);
    free(x);

    return 0;
}