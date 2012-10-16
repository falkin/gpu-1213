#ifndef INDICE_2D
#define INDICE_2D

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Indice2D
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
	static int i()
	    {
	    return threadIdx.y + (blockDim.y * blockIdx.y);
	    }

	/**
	 * i in [0,nbThreadX-1]
	 * j in [0,m-1]
	 * j=threadIdx.x + (blockDim.x * blockIdx.x)
	 */
	__device__
	static int j()
	    {
	    return threadIdx.x + (blockDim.x * blockIdx.x);
	    }

	/**
	 * i in [0,nbThreadY-1]
	 * j in [0,nbThreadX-1]
	 * s in [0,nbThreadX*nbThreadY-1]
	 * s=i*nbThreadX()+j
	 */
	__device__
	static int tid(int i, int j)
	    {
	    return i * nbThreadX() + j;
	    }

	/**
	 * s=i*nbThreadX()+j
	 * i=i()
	 * j=j()
	 * tidGlobal grid
	 */
	__device__
	static int tid()
	    {
	    return i() * nbThreadX() + j();
	    }

	/**
	 * in nbThreadBlock()
	 */
	__device__
	static int tidLocalBlock()
	    {
	    return	    threadIdx.x+blockDim.x*threadIdx.y;
	    }

	/**
	 * image uchar4
	 * s in [0,w*h[
	 * w = largeur (ou m ou dx)
	 * h = hauteur (ou n ou dy)
	 */
	__device__
	static int pixelI(int s, int w)
	    {
	    return s / w;
	    }

	/**
	 * image uchar4
	 * s in [0,w*h[
	 * w = largeur (ou m ou dx)
	 * h = hauteur (ou n ou dy)
	 */
	__device__
	static int pixelJ(int s, int w)
	    {
	    return s - w * pixelI(s, w);
	    }

	/**
	 * image uchar4
	 * s in [0,w*h[
	 * w = largeur (ou m ou dx)
	 * h = hauteur (ou n ou dy)
	 */
	__device__
	static void pixelIJ(int s, int w, int& pixelI, int& pixelJ)
	    {
	    pixelI = s / w;
	    pixelJ = s - w * pixelI;
	    }

	__device__
	static int nbThread()
	    {
	    // return (gridDim.x * gridDim.y * gridDim.z) * (blockDim.x * blockDim.y * blockDim.z); // dim=1 si pas use
	    return (gridDim.x * gridDim.y) * (blockDim.x * blockDim.y);// dim=1 si pas use
	    }

	__device__
	static int nbThreadX()
	    {
	    return gridDim.x * blockDim.x;
	    }

	__device__
	static int nbThreadY()
	    {
	    return gridDim.y * blockDim.y;
	    }

	__device__
	static int nbThreadBlock()
	    {
	    return blockDim.x * blockDim.y;
	    }

//	__device__
//	static int nbThreadZ()
//	    {
//	    return gridDim.z * blockDim.z;
//	    }

	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/

	private:

	};

#endif 

    /*----------------------------------------------------------------------*\
 |*			End	 					*|
     \*---------------------------------------------------------------------*/
