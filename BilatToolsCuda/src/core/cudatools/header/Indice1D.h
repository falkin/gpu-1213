#ifndef INDICE_1D
#define INDICE_1D

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Indice1D
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	/**
	 * i in [0,nbThreadX-1]
	 * i=threadIdx.y + (blockDim.y * blockIdx.y)
	 */
	__device__
	static int tid()
	    {
	    return threadIdx.x + (blockDim.x * blockIdx.x);
	    }

	__device__
	static int nbThread()
	    {
	    return gridDim.x * blockDim.x; // dim=1 si pas use
	    }

	__device__
	static int nbThreadBlock()
	    {
	    return blockDim.x; // dim=1 si pas use
	    }

	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/

    private:

    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
