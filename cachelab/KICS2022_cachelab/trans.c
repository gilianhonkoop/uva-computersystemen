/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 

/*
Please write your student name and ID:  
Student 1: Gilian Honkoop - 13710729
Student 2: Mick Cazemier - 13851918
*/

#include <stdio.h>
#include "cachelab.h"


int is_transpose(int M, int N, int A[N][M], int B[M][N]);
void transpose32(int M, int N, int A[N][M], int B[M][N]);
void transpose64(int M, int N, int A[N][M], int B[M][N]);
void transpose6167(int M, int N, int A[N][M], int B[M][N]);
/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    if(M==32)
    {
        transpose32(M,N,A,B);
    }
    if(M==64)
    {
        transpose64(M,N,A,B);
    }
    if(M==61)
    {
        transpose6167(M,N,A,B);
    }       
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

void transpose32(int M, int N, int A[N][M], int B[M][N])
{
    int i,j;
    int p,q;
    int blcksize = 8;
    int temp = 0;

    for(i=0; i<M; i+=blcksize)
    {
        for(j=0; j<N; j+=blcksize)
        {
            for(p=i; (p<(i+blcksize)); p++)
            {
                for(q=j; (q<(j+blcksize)); q++)
                {
                    if((p) == (q))
                    {
                        temp=A[p][q];
                    }
                    else
                    {
                        B[q][p]=A[p][q];
                    }
                }
                if(i==j)
                {
                    B[p][p]=temp;
                }

            }
        }
    }
}


void transpose64(int M, int N, int A[N][M], int B[M][N])
{
    int i,j;
    int p,q;
    int temp;
    int blcksize = 8;

    for(j=0; j<M; j+=blcksize)
    {
        for(i=0; i<N; i+=blcksize)
        {
            for(p=i; (p<(i+4)); p++)
            {
                for(q=j+4; (q<(j+blcksize)); q++)
                {
                    if(p+j == q+i)
                    {
                        temp=A[q][p];
                    }
                    else
                    {
                        B[p][q]=A[q][p];
                    }
                }

                B[p][q-4+p-i-4]=temp;
            }   

            for(p=i+4; (p<(i+blcksize)) && (p<M); p++)
            {
                for(q=j+4; (q<(j+blcksize)) && q<N; q++)
                {
                    if((p+j)==(q+i))
                    {
                        temp=A[q][p];
                    }
                    else
                    {
                        B[p][q]=A[q][p];
                    }
                }

                B[p][q-4+p-i-4]=temp;
            }

            for(p=i+4; (p<(i+blcksize)) && (p<M); p++)
            {
                for(q=j; (q<(j+4)) && q<N; q++)
                {
                    B[p][q]=A[q][p];
                }
            }

            for(p=i; (p<(i+4)) && (p<M); p++)
            {
                for(q=j; (q<(j+4)) && q<N; q++)
                {
                    if((p+j)==(q+i))
                    {
                        temp=A[q][p];
                    }
                    else
                    {
                        B[p][q]=A[q][p];
                    }
                }
                
                B[p][q-4+p-i]=temp;
            }
        }
    }
}

void transpose6167(int M, int N, int A[N][M], int B[M][N])
{
    int i,j;
    int p,q;
    int temp;
    int blocksize = 17;

    for(i=0; i<M; i+=blocksize)
    {
        for(j=0; j<N; j+=blocksize)
        {
            for(p=j; (p<(j+blocksize)) && (p<N); p++)
            {
                for(q=i; (q<(i+blocksize)) && q<M; q++)
                {
                    if((p)==(q))
                    {
                        temp=A[p][p];
                    }
                    else
                    {
                        B[q][p]=A[p][q];
                    }
                }
                if(i==j)
                {
                    B[p][p]=temp;
                }

            }

        }
    }
}

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    
}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    //registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}