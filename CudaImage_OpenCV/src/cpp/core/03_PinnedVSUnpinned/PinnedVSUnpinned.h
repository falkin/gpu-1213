#ifndef PINNEDVSUNPINNED_H_
#define PINNEDVSUNPINNED_H_

#include "Capture_A.h"

enum HostMemoryType {
  PINNED, UNPINNED
};

class PinnedVSUnpinned {
public:
  PinnedVSUnpinned ( const uint32_t w, const uint32_t h, const std::string filename, const HostMemoryType memType = PINNED );
  virtual ~PinnedVSUnpinned () {
    delete _capture;
  }
  double transfert ();
  static double transfert ( const void* ptrMemory, const size_t size );
private:
  uint32_t _w;
  uint32_t _h;
  std::string _filename;
  Capture_A* _capture;
  HostMemoryType _memType;
  size_t _memSize;
};

#endif
