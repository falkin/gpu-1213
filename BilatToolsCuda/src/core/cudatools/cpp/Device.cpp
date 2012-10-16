#include <iostream>
#include "Device.h"
#include "cudaTools.h"
#include "Chronos.h"
#include "omp.h"
#include <assert.h>

using std::string;
using std::cout;
using std::cerr;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void cout01(int isTrue);
void cout02(int i);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int Device::getDeviceId(void)
    {
    int deviceId;
    HANDLE_ERROR(cudaGetDevice(&deviceId));

    return deviceId;
    }

int Device::getDeviceCount(void)
    {
    int nbDevice;
    HANDLE_ERROR(cudaGetDeviceCount(&nbDevice));

    return nbDevice;
    }

bool Device::isCuda(void)
    {
    return getDeviceCount() >= 1;
    }

cudaDeviceProp Device::getDeviceProp(int idDevice)
    {
    cudaDeviceProp prop;
    HANDLE_ERROR(cudaGetDeviceProperties(&prop, idDevice));
    return prop;
    }

cudaDeviceProp Device::getDeviceProp(void)
    {
    return getDeviceProp(getDeviceId());
    }

/*--------------------------------------*\
 |*		Secondaire		*|
 \*-------------------------------------*/

dim3 Device::getMaxGridDim(int idDevice)
    {
    cudaDeviceProp prop = getDeviceProp(idDevice);

    return dim3(prop.maxGridSize[0], prop.maxGridSize[1], prop.maxGridSize[2]);
    }

dim3 Device::getMaxGridDim()
    {
    return getMaxGridDim(getDeviceId());
    }

dim3 Device::getMaxBlockDim(int idDevice)
    {
    cudaDeviceProp prop = getDeviceProp(idDevice);

    return dim3(prop.maxThreadsDim[0], prop.maxThreadsDim[1], prop.maxThreadsDim[2]);
    }

dim3 Device::getMaxBlockDim()
    {
    return getMaxBlockDim(getDeviceId());
    }

int Device::getMaxThreadPerBlock(int idDevice)
    {
    return getDeviceProp(idDevice).maxThreadsPerBlock;
    }

int Device::getMaxThreadPerBlock()
    {
    return getMaxThreadPerBlock(getDeviceId());
    }

int Device::getWarpSize(int idDevice)
    {
    return getDeviceProp(idDevice).warpSize;
    }

int Device::getWarpSize(void)
    {
    return getWarpSize(getDeviceId());
    }

int Device::getMPCount(int idDevice)
    {
    return getDeviceProp(idDevice).multiProcessorCount;
    }

int Device::getMPCount(void)
    {
    return getMPCount(getDeviceId());
    }

int Device::getCapacityMajor(int idDevice)
    {
    return getDeviceProp(idDevice).major;
    }

int Device::getCapacityMajor()
    {
    return getCapacityMajor(getDeviceId());
    }

int Device::getCapacityMinor(int idDevice)
    {
    return getDeviceProp(idDevice).minor;
    }

int Device::getCapacityMinor()
    {
    return getCapacityMinor(getDeviceId());
    }

int Device::getRuntimeVersion()
    {
    return CUDART_VERSION;
    }

/*--------------------------------------*\
 |*		Is			*|
 \*-------------------------------------*/

/**
 * 64 bits only
 */
bool Device::isUVAEnable(int idDevice)
    {
    return getCapacityMajor() >= 2.0 && getRuntimeVersion() >= 4000;
    }

/**
 * 64 bits only
 */
bool Device::isUVAEnable()
    {
    return isUVAEnable(getDeviceId());
    }

bool Device::isAtomicShareMemoryEnable(int idDevice)
    {
    return (getCapacityMajor() == 1 && Device::getCapacityMinor() >= 2) || getCapacityMajor() >= 2;
    }

bool Device::isAtomicShareMemoryEnable()
    {
    return isAtomicShareMemoryEnable(getDeviceId());
    }

bool Device::isHostMapMemoryEnable(int idDevice)
    {
    return getDeviceProp().canMapHostMemory;
    }

bool Device::isHostMapMemoryEnable()
    {
    return isHostMapMemoryEnable(getDeviceId());
    }

void Device::assertDim(const dim3& threadPerGrid, const dim3& threadPerBlock)
    {
    // grid
	{
	dim3 dimGridMax = Device::getMaxGridDim();

	assert(threadPerGrid.x <= dimGridMax.x);
	assert(threadPerGrid.y <= dimGridMax.y);
	assert(threadPerGrid.z <= dimGridMax.z);
	}

    // block
	{
	dim3 dimBlockMax = Device::getMaxBlockDim();

	assert(threadPerBlock.x <= dimBlockMax.x);
	assert(threadPerBlock.y <= dimBlockMax.y);
	assert(threadPerBlock.z <= dimBlockMax.z);
	}

    // Thread per block
    assert(dim(threadPerBlock) <= getMaxThreadPerBlock());
    }

/*--------------------------------------*\
 |*		Print			*|
 \*-------------------------------------*/

void Device::print(int idDevice, string titre)
    {
    cout << titre << endl;

    cudaDeviceProp prop = getDeviceProp(idDevice);

    cout << endl;
    cout << "===========================================" << endl;
    cout << "Device Info: " << endl;
    cout << "===========================================" << endl;
    cout << "Device id                : " << idDevice << endl;
    cout << "Name                     : " << prop.name << endl;
    cout << "GPU capability           : " << prop.major << "." << prop.minor << "" << endl;
    cout << "Clock rate               : " << prop.clockRate / 1000 << " MHZ" << endl;
    cout << "GPU Motherboard          : ";
    cout01(prop.integrated);
    cout << "ComputeMode              : " << prop.computeMode << endl;

    cout << endl;
    cout << "Kernel : " << endl;
    cout << "Limit execution (timeout): ";
    cout01(prop.kernelExecTimeoutEnabled);

    cout << endl;
    cout << "Memory : " << endl;
    cout << "Global Memory            : " << prop.totalGlobalMem / 1024 / 1024 << " MB" << endl;
    cout << "Constant Memory          : " << prop.totalConstMem / 1024 << " KB" << endl;
    cout << "Texture1D max size       : (" << prop.maxTexture1D << ")" << endl;
    cout << "Texture2D max size       : (" << prop.maxTexture2D[0] << "," << prop.maxTexture2D[1] << ")" << endl;
    cout << "Texture3D max size       : (" << prop.maxTexture3D[0] << "," << prop.maxTexture3D[1] << "," << prop.maxTexture3D[2] << ")" << endl;
    //cout << "Texture2D Array max Size : (" << ptrProp.maxTexture2DArray[0] << "," << ptrProp.maxTexture2DArray[1] << "," << ptrProp.maxTexture2DArray[2] << ")"<< endl;
    cout << "Texture Alignment        : " << prop.textureAlignment << " B" << endl;
    cout << "Max mem pitch            : " << prop.memPitch << endl;

    cout << endl;
    cout << "Multiprocesseur(MP)      : " << endl;
    cout << "MP count                 : " << prop.multiProcessorCount << endl;
    cout << "Shared memory per block  : " << prop.sharedMemPerBlock / 1024 << " KB " << endl;
    cout << "Register memory per block: " << prop.regsPerBlock / 1024 << " KB " << endl;
    cout << "Max threads per block    : " << prop.maxThreadsPerBlock << endl;
    cout << "Max thread dim           : (" << prop.maxThreadsDim[0] << "," << prop.maxThreadsDim[1] << "," << prop.maxThreadsDim[2] << ")" << endl;
    cout << "Max grid dim             : (" << prop.maxGridSize[0] << "," << prop.maxGridSize[1] << "," << prop.maxGridSize[2] << ")" << endl;
    cout << "Threads in warp          : " << prop.warpSize << endl;

    cout << endl;
    cout << "Enable/Disable : " << endl;
    cout << "MapHostMemory                                                        : ";
    cout01(isHostMapMemoryEnable());
    cout << "AtomicOperation sharedMemory                                         : ";
    cout01(isAtomicShareMemoryEnable());
    cout << "UVA (Unied Virtual Addressing)                                       : ";
    cout01(isUVAEnable());
    cout << "Concurrent execution : memcopy & kernel execution                    : ";
    cout01(prop.deviceOverlap);
    cout << "Concurrent copy      : host->device & device->host (DMA memory only) : ";
    cout02(prop.asyncEngineCount); // cout02 TODO erreur ou pas
    cout << "Concurrent Kernels   : (16 max)                                      : ";
    cout01(prop.concurrentKernels);

    cout << "===========================================" << endl;
    cout << "Cuda Runtime version     :  " << getRuntimeVersion() << endl;
    cout << "===========================================" << endl;
    cout << endl;
    }

void Device::print(string titre)
    {
    cout << titre << endl;

    print(getDeviceId(), "");

    }

void Device::printALL(string titre)
    {
    cout << titre << endl;

    int deviceCount = getDeviceCount();

    for (int id = 0; id < deviceCount; id++)
	{
	print(id, "");
	}
    }

/*--------------------------------------*\
 |*		Load Driver		*|
 \*-------------------------------------*/

/**
 * Linux : nvidia-smi -pm 1 utile? TODO
 * marche pas pour opengl
 */
void Device::loadCudaDriver(int deviceID, bool isMapMemoryAsk)
    {
    Chronos chrono;
    cout << "Device(" << deviceID << ") : Load Driver  ";

    int* ptrBidon;

    HANDLE_ERROR(cudaSetDevice(deviceID));

    if (isHostMapMemoryEnable() && isMapMemoryAsk)
	{
	HANDLE_ERROR(cudaSetDeviceFlags(cudaDeviceMapHost));
	cout << " : HostMapMemory activate " << endl;
	}
    else if (!isHostMapMemoryEnable() && isMapMemoryAsk)
	{
	cerr << "Device(" << deviceID << ") : HostMapMemory failure " << endl;
	}

    HANDLE_ERROR(cudaMalloc((void**) &ptrBidon, sizeof(int)));
    HANDLE_ERROR(cudaFree(ptrBidon));

    chrono.stop();
    cout << chrono.getDeltaTime() << " (s)" << endl;
    }

void Device::loadCudaDriver(bool isMapMemoryEnable)
    {
    loadCudaDriver(getDeviceId(), isMapMemoryEnable);
    }

void Device::loadCudaDriverDeviceAll(bool isMapMemoryEnable)
    {
    cout << "\nLoad Cuda Driver : start ..." << endl;
    Chronos chrono;

    int k = Device::getDeviceCount();
    //omp_set_num_threads(k);
    //#pragma omp parallel for
    for (int i = 0; i < k; i++)
	{
	loadCudaDriver(i, isMapMemoryEnable);
	}

    chrono.stop();
    cout << "Load Cuda Driver : end  : " << chrono.getDeltaTime() << " (s)\n" << endl;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void cout01(int isTrue)
    {
    if (isTrue)
	cout << "True" << endl;
    else
	cout << "False" << endl;
    }

void cout02(int i)
    {
    if (i==2)
	cout << "True" << endl;
    else
	cout << "False" << endl;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

