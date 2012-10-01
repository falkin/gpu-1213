#include <iostream>
#include "omp.h"
#include <math.h>

using std::cout;
using std::endl;

double ComputePI1 ( unsigned long long intervals, int threads ) {
    if ( threads <= 0 ) {
        threads = omp_get_num_procs ();
    }
    omp_set_num_threads ( threads );

    double results[threads];
    double incr = 1.0 / ( intervals * 1.0 );
    cout.precision( 10 );
    cout << "[" << threads << "]: Number of thread(s)" << endl;
    cout << "[" << incr << "]: PI computation increment" << endl;
    cout << "[" << intervals << "]: intervals" << endl;

    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        double x;
        results[id] = 0;
        for ( int i = id; i <= intervals; i += threads ) {
            x = i * incr;
            results[id] += 4.0 / ( 1.0 + ( x * x ) );
        }
    }
    double pi = 0;
    for ( int i = 0; i < threads; i++ ) {
        pi += results[i] * incr;
    }
    cout << "[" << pi << "]: PI" << endl;
    return pi;
}
