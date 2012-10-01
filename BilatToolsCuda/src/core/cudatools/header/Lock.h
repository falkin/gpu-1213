#ifndef LOCK_H_
#define LOCK_H_

#include "cudaTools.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * A Mutex will act like something of a traffic signal that governs access to some resources.
 * When a thread reads a 0 from the mutex,it interprets this valu as a "green lignt" indicating that no other thread is using the memory.
 * Therefore, the thread is free to lock the memory and make whatever changes it desires,free of interference from other threads.
 * To lock the memory location in nquestion, the thread writes a 1 to the mutex.
 * This will act as a "red light" for potentially competing threads.
 * The competing thredas must then wait until the owner has written a 0 to the mutex beforfe they can attempt to modify the locked memory.
 *
 * Use :
 * 	// Inside a kernel:
 * 	lock.lock();
 * 	doSomething();
 * 	lock.unlock();
 *
 * 	where lock is instancied on the cpu and give to the kernel
 * 		kernelA<<<blockPerGrid,threadPerBlock>>>(...,lock,...)
 * 	with prototype
 * 		void kernelA(...,Lock lock,....); //Passage par valeur!
 *
 * Contrainte : Lock doit etre passer par valeur au kernel!
 *
 * Raison : 	Il ne peut être passer par adresse,car l'espace d'adressage du GPU est different de celui du cpu
 * 		De toute facon,meme si c'etait possible, il ne serait pas efficace de faire systematiquement des appels gpu->cpu!
 * 		Par ailleurs le lock n'a besoin de vivre que du côte GPU!
 * 		La copie creer par le passage par valeur est light,seule un attribut de type ptrDev (pointeur sur Device) est copier.
 * 		Par ailleurs,ptrDev adresse un espace sur le GPU, cette adresse est ligitime sur le gpu
 */

class Lock
    {

	/*--------------------------------------*\
	 |*		Constructor		*|
	 \*-------------------------------------*/

    public :

	Lock(void)
	    {
	    int state = 0;
	    HANDLE_ERROR(cudaMalloc((void**) &ptrDev_mutex, sizeof(int)));
	    HANDLE_ERROR(cudaMemcpy(ptrDev_mutex, &state, sizeof(int), cudaMemcpyHostToDevice));
	    }

		/**
	 * Observation:
	 *
	 * 	Comme Lock est passer par valeur au kernel,ie par copie,deux objets au total sont vivants, un sur le cpu et sun sur le gpu.
	 * 	Le destructeur sera donc appeler 2x,la premiere fois, lors de la fin du kernel sur le gpu, la seconde fois sur le cpu.
	 * 	Comme cudaFree peut etre appeler sur le cpu ou gpu, le code ci-dessous est valide, mais sans le HANDLE_ERROR qui n'a aucun sens
	 * 	(affichage d'un message d'error) sur le GPU et qui est donc enlever ici.
	 * 	Heureusement cudaFree peut être appeler plusieurs fois de suite sans probleme,mais un seul appel suffirait!
	 *
	 * Attention:
	 *
	 * 	Sur le GPU, il ne faut jamais passer Lock par valeur, car sinon, la premiere instance detruite, detruit ptrDev_mutex !!
	 * 	et le mutex devient alors inutilisable!
	 */
	~Lock(void)
	    {
	   // HANDLE_ERROR(cudaFree(ptrDev_mutex)); // HANDLE_ERROR : pas possible car executer aussi sur le GPU
	    cudaFree(ptrDev_mutex);

	    // Amelioration:
	    // 		if (isOnGPU)	{cudaFree(ptrDev_mutex);}
	    // 		else		{//rien}
	    //
	    // TODO : Comment coder isOnGPU ??
	    }

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

    public :

	__device__ void lock(void)
	    {
	    // Goal :
	    // 		if (*ptrDev_mutex==0) {*ptrDev_mutex==1}
	    // 		But must be thread safe!
	    //
	    // Solution:
	    // 		atomicCAS  = atomic Compare And Swap
	    // 		Prototype : 	c atomicCAS(ptr,a,b)
	    // 		Action :	compare ptr avec a, si egale affecte b à ptr, renvoie ptr

	    // Tant que ptrDev_mutex!=0 le thread cuda boucle sur while
	    // Des qu'il vaut 0, il met le mutex à 1 et lock se termine
	    while (atomicCAS(ptrDev_mutex, 0, 1) != 0);
	    }

	__device__ void unlock(void)
	    {
	    // Goal :
	    //		Put 1 in the mutex
	    //
	    // Solution 1:
	    //
	    //		*ptrDev_mutex=0;
	    //		Aucun thread en competition ici. L'affectation n'a pas besoin d'être atomique.
	    //		Solution satisfaisante.
	    //
	    // Solution 2 (prefered for symetric approach)
	    //
	    //		Une solution atomique

	    // Echange et renvoie la valeur originale
	    atomicExch(ptrDev_mutex, 0);
	    }

	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/

    private :

	int* ptrDev_mutex; // Espace adressage GPU
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
