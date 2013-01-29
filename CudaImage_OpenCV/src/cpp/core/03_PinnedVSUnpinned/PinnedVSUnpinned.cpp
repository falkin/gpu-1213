#include "PinnedVSUnpinned.h"
#include "CaptureVideo.h"
#include "CaptureVideoDMA.h"

extern double launchKernelMemoryTransfert ( const uint32_t w, const uint32_t h, const void* memory, const size_t memory_size );

/**
 * TODO: Correct this mutahfuckah uchar4 to uchar3 ...
 */
PinnedVSUnpinned::PinnedVSUnpinned ( const uint32_t w, const uint32_t h, const std::string filename, const HostMemoryType memType )
    : _w ( w ), _h ( h ), _filename ( filename ), _memType ( memType ) {
  switch ( memType ) {
  default:
    // Let's assume we want unpinned.
  case UNPINNED:
    _capture = new CaptureVideo ( _filename, std::string ( "Unpinned memory" ) );
    _memSize = sizeof(uchar3);
    break;
  case PINNED:
    _capture = new CaptureVideoDMA ( _filename, std::string ( "Pinned memory" ) );
    _memSize = sizeof(uchar3);
    break;
  }
}

/**
 * TODO: Again, correct this mutahfuckah uchar4 to uchar3 ...
 */
double PinnedVSUnpinned::transfert () {
  cv::Mat img;
  void* ptrMemory;
  switch ( _memType ) {
  default:
    // Let's assume we want unpinned.
  case UNPINNED:
    img = _capture->capturerUChar3 ();
    ptrMemory = Capture_A::castToUChar3 ( &img );
    break;
  case PINNED:
    img = _capture->capturerUChar3 ();
    ptrMemory = Capture_A::castToUChar3 ( &img );
    break;
  }
  double time = launchKernelMemoryTransfert ( _w, _h, ptrMemory, _memSize );
  return time;
}
