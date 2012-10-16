#ifndef VERTEX_BUFFER_OBJECT_H
#define VERTEX_BUFFER_OBJECT_H

#include "BufferObject.h"

class CBI_GLTOOLS VertexBufferObject : public BufferObject
    {
    public:
	VertexBufferObject(unsigned int sizeOctet,void* bufferVertex,GLenum bufferUsage);
	VertexBufferObject();
	virtual ~VertexBufferObject();
    };

#endif
