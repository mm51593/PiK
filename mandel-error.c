/*
 * *  PROGRAM: Mandelbrot area
 **
 **  PURPOSE: Program to compute the area of a  Mandelbrot set.
 **           Correct answer should be around 1.510659.
 **           WARNING: this program may contain errors
 **
 **  USAGE:   Program runs without input ... just run the executable
 **            
 **  HISTORY: Written:  (Mark Bull, August 2011).
 **           Changed "comples" to "d_comples" to avoid collsion with 
 **           math.h complex type (Tim Mattson, September 2011)
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

# define NPOINTS 400
# define MAXITER 400

void testpoint(void);

struct d_complex{
    double r;
    double i;
};

struct d_complex c;
int numoutside = 0;

int main(){
    int i, j;
    double area, error, eps  = 1.0e-5;
    
    
    //   Loop over grid of points in the complex plane which contains the Mandelbrot set,
    //   testing each point to see whether it is inside or outside the set.
    
    //omp_set_num_threads(1);
    #pragma omp parallel default(shared)
    {
        #pragma omp for private(i, j)
        for (i=0; i<NPOINTS; i++) 
        {
            for (j=0; j<NPOINTS; j++) 
            {
                #pragma omp threadprivate(c)
                c.r = -2.5+3.5*(double)(i)/(double)(NPOINTS)+eps;
                c.i = -1.0+2.0*(double)(j)/(double)(NPOINTS)+eps;
                testpoint();
            }
        }
        printf("t=%d: %d\n", omp_get_thread_num(), numoutside);
    }
    
    printf("%d\n", numoutside);
    
    
    // Calculate area of set and error estimate and output the results
    
    area=3.5*2.0*(double)(NPOINTS*NPOINTS-numoutside)/(double)(NPOINTS*NPOINTS);
    error=area/(double)NPOINTS;
    
    printf("Area of Mandlebrot set = %12.8f +/- %12.8f\n",area,error);
    printf("Correct answer should be around 1.510659\n");
    
}

void testpoint(void){
    
    // Does the iteration z=z*z+c, until |z| > 2 when point is known to be outside set
    // If loop count reaches MAXITER, point is considered to be inside the set
    
    struct d_complex z;
    int iter;
    double temp;
    
    z=c;
    //printf("%.4f %.4fi\n", z.r, z.i);
    for (iter=0; iter<MAXITER; iter++){
        temp = (z.r*z.r)-(z.i*z.i)+c.r;
        z.i = z.r*z.i*2+c.i;
        z.r = temp;
        if ((z.r*z.r+z.i*z.i)>4.0) {
            //printf("%.2f %.2fi\n", z.r, z.i);
            #pragma omp atomic
            numoutside++;
            break;
        }
    }
    
}
