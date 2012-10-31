#ifndef ELEMENT_BUFFER_OBJECT_H
#define ELEMENT_BUFFER_OBJECT_H

#include "BufferObject.h"

class CBI_GLTOOLS ElementBufferObject : public BufferObject
    {
    public:
	ElementBufferObject(unsigned int sizeOctet,void* bufferIndice,GLenum bufferUsage);
	ElementBufferObject();
	virtual ~ElementBufferObject();
    };

#endif
