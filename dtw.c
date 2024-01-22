#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>


#define MAX_N 2000
#define MAX_L 100
#define MAX_H 50




/*dtw function
    s1 and s2 are 2 time series signals
    length is the number of samples in the time series(both the time series should contain same number of samples)
    window is the length of the search window*/
int dtw(double* s1, double* s2, int length, int window, int skip,double* lags)

{
    int N = length;
    int L = window;
    int H = skip;

    double** e;
    e = (double **)malloc((2*L+1) * sizeof(double *));
    for(int i = 0; i < 2*L+1; i++){
        e[i] = (double *)malloc(N * sizeof(double));
    }


    // step 2 (refer readme file)
    //// calculating error matrix (error matrix gives the errors between samples 
    for (int n = 0; n < N; n++) {
        for (int m = -L; m <= L; m++) {
            int index = n + m;
            if (index < 0 || index >= N) {
                e[m + L][n] = fabs(s1[n]);
            }

            else {
                e[m + L][n] = fabs(s1[n] - s2[index]);
            }


        }
    }
    // step 3 (refer readme file)
    ////accumulating the errors in the error matrix along indexes H,2H,3H..
    int qu, ql, k, p, q, height, j, i;
    double slope, currentMinPath = INFINITY, newMinPath = 0.0000;

    for (i = H-1; i < N; i = i + H) {
        for (k = 0; k < (2 * L) + 1; k++) {

            ql = k - H >= 0 ? k - H : 0;
            qu = k + H <= (2 * L) ? k + H : 2 * L;

            for (q = ql; q <= qu; q++) {

                slope = (double)-(k - q) / H;

                for (p = 0; p < H; p++) {

                    height = (int)round(p * slope);
                    newMinPath += e[k + height][i  - p];

                }
                if (newMinPath < currentMinPath)currentMinPath = newMinPath;

                newMinPath = 0.0000;
            }

            e[k][i] = e[k][i] + currentMinPath;
            currentMinPath = INFINITY;
        }
    }
    // step 4 (refer readme file)
    ////backtracking through accumulated errors
    double* a= (double*)malloc(N/H * sizeof(double));
    int minIndex=0;
    double min = e[0][N -1];


    for (i = 1; i < 2 * L +1; i++) {
        if (e[i][N - 1] < min) {
            min = e[i][N  - 1];
            minIndex = i;
        }
    }


    a[q] = minIndex - L;
    q=1;



    int newIndex;
    i=N-1-H;
    while(i >= 0) {
        min = INFINITY;

        for (j = -H; j <= H; j++) {
            if (minIndex + j > 0 && minIndex + j < 2 * L) {
                if (min > e[minIndex + j][i]) {
                    min = e[minIndex + j][i];
                    newIndex = minIndex + j;
                }
            }

        }
        minIndex = newIndex;
        a[q] = minIndex - L;
        q++;
        i=i-H;
    }

    ///free e and d
    for (int i = 0; i < 2*L+1; i++) {
        free(e[i]);
    }
    free(e);

    // step 5 (refer readme file)
    ///interpolation of lag[]
    //this code interpolates the lags to the same number of samples as the  time series


    int n=N/H;

    n--;
    double *x = (double*) malloc((n + 1) * sizeof(double));
    double *h = (double*) malloc(n * sizeof(double));
    double *A = (double*) malloc(n * sizeof(double));
    double *l = (double*) malloc((n + 1) * sizeof(double));
    double *u = (double*) malloc((n + 1) * sizeof(double));
    double *z = (double*) malloc((n + 1) * sizeof(double));
    double *c = (double*) malloc((n + 1) * sizeof(double));
    double *b = (double*) malloc(n * sizeof(double));
    double *di = (double*) malloc(n * sizeof(double));






    for (i = 0; i < n + 1; ++i) x[i]=i;

   
    for (i = 0; i <= n - 1; ++i) h[i] = x[i + 1] - x[i];

  
    for (i = 1; i <= n - 1; ++i)
        A[i] = 3 * (a[i + 1] - a[i]) / h[i] - 3 * (a[i] - a[i - 1]) / h[i - 1];

    
    l[0] = 1;
    u[0] = 0;
    z[0] = 0;

    
    for (i = 1; i <= n - 1; ++i) {
        l[i] = 2 * (x[i + 1] - x[i-1]) - h[i - 1] * u[i - 1];
        u[i] = h[i] / l[i];
        z[i] = (A[i] - h[i - 1] * z[i - 1]) / l[i];
    }

    
    l[n] = 1;
    z[n] = 0;
    c[n] = 0;

    
    for (j = n - 1; j >= 0; --j) {
        c[j] = z[j] - u[j] * c[j + 1];
        b[j] = (a[j + 1] - a[j]) / h[j] - h[j] * (c[j + 1] + 2 * c[j]) / 3;
        di[j] = (c[j + 1] - c[j]) / (3 * h[j]);
    }

// Evaluate cubic spline equation at interpolated x values
    for (i = 0; i < N; ++i) {
        float x_val = (float)i * n / (float)(N - 1);
        int j = (int)x_val;
        float dx = x_val - j;
        lags[i] = a[j] + b[j]*dx + c[j]*dx*dx + di[j]*dx*dx*dx;
    }

    free(x);
    free(h);
    free(A);
    free(l);
    free(u);
    free(z);
    free(c);
    free(b);
    free(di);
    return 0;
}

int main() {
////declare array and allocating memory
    double* s1;
    double* s2;

    s1 = (double*) malloc(MAX_N * sizeof(double));
    s2 = (double*) malloc(MAX_N * sizeof(double));
    // Open the s1.txt file
    FILE* s1_file = fopen("s1.txt", "r");
    if (!s1_file) {
        printf("Error opening s1.txt\n");
        return 1;
    }

    // Read the contents of s1.txt into s1
    for (int i = 0; i < MAX_N; i++) {
        if (fscanf(s1_file, "%lf", &s1[i]) != 1) {
            printf("Error reading s1.txt\n");
            return 1;
        }
    }

    // Close the s1.txt file
    fclose(s1_file);

    // Open the s2.txt file
    FILE* s2_file = fopen("s2.txt", "r");
    if (!s2_file) {
        printf("Error opening s2.txt\n");
        return 1;
    }


    // Read the contents of s2.txt into s2
    for (int i = 0; i < MAX_N; i++) {
        if (fscanf(s2_file, "%lf", &s2[i]) != 1) {
            printf("Error reading s2.txt\n");
            return 1;
        }
    }

    // Close the s2.txt file
    fclose(s2_file);



    double* lags= (double*)malloc(MAX_N * sizeof(double));
    
    //calling dtw function
    dtw(s1,s2,MAX_N,MAX_L,MAX_H,lags);

    ///saving lags  to a file
    FILE *fp = fopen("newlags.txt", "w");
    if (fp != NULL) {
        for (int i = 0; i < MAX_N; i++) {
            fprintf(fp, "%f ", lags[i]);
        }
        fclose(fp);
    }
    // you can plot to the newlags.txt with matplotlib to see the dynamic lags

    free(s1);
    free(s2);

}
