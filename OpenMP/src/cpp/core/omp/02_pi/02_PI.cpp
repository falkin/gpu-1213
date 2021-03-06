#include <iostream>
#include "omp.h"
#include <math.h>

using std::cout;
using std::endl;

/**
 * Promotion de tableau
 */
double ComputePI1 ( unsigned long long intervals, int threads ) {
    if ( threads <= 0 ) {
        threads = omp_get_num_procs ();
    }
    omp_set_num_threads ( threads );

    double results[threads];
    double incr = 1.0 / ( intervals * 1.0 );
    cout << "[Number of thread(s)]: " << threads << endl;
    cout << "[PI computation increment]: " << incr << endl;
    cout << "[Intervals]: " << intervals << endl;

    // Parallel
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        double x;
        results[tid] = 0;
        for ( int i = tid; i <= intervals; i += threads ) {
            x = i * incr;
            results[tid] += 4.0 / ( 1.0 + ( x * x ) );	// Promotion de tableau
        }
    }

    // Reduce
    double pi = 0;
    for ( int i = 0; i < threads; i++ ) {
    	pi += results[i] * incr;
    }
    cout << "[PI]: " << pi << endl;
    return pi;
}

/**
 * Atomic version
 */
double ComputePI2 ( unsigned long long intervals, int threads ) {
    if ( threads <= 0 ) {
        threads = omp_get_num_procs ();
    }
    omp_set_num_threads ( threads );

    double result = 0.0;
    double incr = 1.0 / ( intervals * 1.0 );
    cout << "[Number of thread(s)]: " << threads << endl;
    cout << "[PI computation increment]: " << incr << endl;
    cout << "[Intervals]: " << intervals << endl;

    // Parallel
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        double x;
        double internal = 0.0;
        for ( int i = tid; i <= intervals; i += threads ) {
            x = i * incr;
            internal += 4.0 / ( 1.0 + ( x * x ) );
        }
	#pragma omp atomic
	    result += internal;
    }

    // Reduce
    double pi = ( result * incr );
    cout << "[PI]: " << pi << endl;
    return pi;
}

/**
 * Critical version
 */
double ComputePI3 ( unsigned long long intervals, int threads ) {
    if ( threads <= 0 ) {
        threads = omp_get_num_procs ();
    }
    omp_set_num_threads ( threads );

    double result = 0.0;
    double incr = 1.0 / ( intervals * 1.0 );
    cout << "[Number of thread(s)]: " << threads << endl;
    cout << "[PI computation increment]: " << incr << endl;
    cout << "[Intervals]: " << intervals << endl;

    // Parallel
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        double x;
        double internal = 0.0;
        for ( int i = tid; i <= intervals; i += threads ) {
            x = i * incr;
            internal += 4.0 / ( 1.0 + ( x * x ) );
        }
	#pragma omp critical (critic)
	    result += internal;
    }

    // Reduce
    double pi = ( result * incr );
    cout << "[PI]: " << pi << endl;
    return pi;
}

/**
 * For
 */
double ComputePI4 ( unsigned long long intervals, int threads ) {
    if ( threads <= 0 ) {
        threads = omp_get_num_procs ();
    }
    omp_set_num_threads ( threads );

    double results[threads];
    double incr = 1.0 / ( intervals * 1.0 );
    cout << "[Number of thread(s)]: " << threads << endl;
    cout << "[PI computation increment]: " << incr << endl;
    cout << "[Intervals]: " << intervals << endl;

    // Parallel
    #pragma omp parallel for
    for( int i = 0; i < intervals; i++ ) {
	int tid = omp_get_thread_num();
	double x = i * incr;
        results[tid] += 4.0 / ( 1.0 + ( x * x ) );	// Promotion de tableau
    }

    // Reduce
    double pi = 0;
    for ( int i = 0; i < threads; i++ ) {
    	pi += results[i] * incr;
    }
    cout << "[PI]: " << pi << endl;
    return pi;
}

/**
 * For, syntaxfull
 */
double ComputePI5 ( unsigned long long intervals, int threads ) {
    if ( threads <= 0 ) {
        threads = omp_get_num_procs ();
    }
    omp_set_num_threads ( threads );

    double results[threads];
    double incr = 1.0 / ( intervals * 1.0 );
    cout << "[Number of thread(s)]: " << threads << endl;
    cout << "[PI computation increment]: " << incr << endl;
    cout << "[Intervals]: " << intervals << endl;

    // Parallel
    #pragma omp parallel
    {
	int tid = omp_get_thread_num();
	#pragma omp for
	for( int i = 0; i < intervals; i++ ) {
	    double x = i * incr;
	    results[tid] += 4.0 / ( 1.0 + ( x * x ) );	// Promotion de tableau
	}
    }

    // Reduce
    double pi = 0;
    for ( int i = 0; i < threads; i++ ) {
    	pi += results[i] * incr;
    }
    cout << "[PI]: " << pi << endl;
    return pi;
}

/**
 * For, syntaxfull, atomic
 */
double ComputePI6 ( unsigned long long intervals, int threads ) {
    if ( threads <= 0 ) {
        threads = omp_get_num_procs ();
    }
    omp_set_num_threads ( threads );

    double result = 0.0;
    double incr = 1.0 / ( intervals * 1.0 );
    cout << "[Number of thread(s)]: " << threads << endl;
    cout << "[PI computation increment]: " << incr << endl;
    cout << "[Intervals]: " << intervals << endl;

    // Parallel
    #pragma omp parallel
    {
	#pragma omp for
	for( int i = 0; i < intervals; i++ ) {
	    double x = i * incr;
	    #pragma omp atomic
	    result += 4.0 / ( 1.0 + ( x * x ) );
	}
    }

    // Reduce
    double pi = ( result * incr );
    cout << "[PI]: " << pi << endl;
    return pi;
}

/**
 * For, syntaxfull, critical
 */
double ComputePI7 ( unsigned long long intervals, int threads ) {
    if ( threads <= 0 ) {
        threads = omp_get_num_procs ();
    }
    omp_set_num_threads ( threads );

    double result = 0.0;
    double incr = 1.0 / ( intervals * 1.0 );
    cout << "[Number of thread(s)]: " << threads << endl;
    cout << "[PI computation increment]: " << incr << endl;
    cout << "[Intervals]: " << intervals << endl;

    // Parallel
    #pragma omp parallel
    {
	#pragma omp for
	for( int i = 0; i < intervals; i++ ) {
	    double x = i * incr;
	    #pragma omp critical (critic)
	    result += 4.0 / ( 1.0 + ( x * x ) );
	}
    }

    // Reduce
    double pi = ( result * incr );
    cout << "[PI]: " << pi << endl;
    return pi;
}

/**
 * For, syntax OpenMP
 */
double ComputePI8 ( unsigned long long intervals, int threads ) {
    if ( threads <= 0 ) {
        threads = omp_get_num_procs ();
    }
    omp_set_num_threads ( threads );

    double result = 0.0;
    double incr = 1.0 / ( intervals * 1.0 );
    cout << "[Number of thread(s)]: " << threads << endl;
    cout << "[PI computation increment]: " << incr << endl;
    cout << "[Intervals]: " << intervals << endl;

    // Parallel
    #pragma omp parallel for reduction(+:result)
    for( int i = 0; i < intervals; i++ ) {
	double x = i * incr;
	result += 4.0 / ( 1.0 + ( x * x ) );
    }

    // Reduce
    double pi = ( result * incr );
    cout << "[PI]: " << pi << endl;
    return pi;
}
