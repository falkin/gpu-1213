#ifndef GLCOURBE2DHSBS_H
#define GLCOURBE2DHSBS_H

#include "GLCourbe2Ds.h"
#include "ShaderPrograms.h"
#include <string>

using std::string;

class CBI_GLTOOLS GLCourbe2DHSBs : public GLCourbe2Ds
    {
    public:
	GLCourbe2DHSBs(Courbe2DMOOs* ptrCourbe2D,float hueMin,float hueMax,string shaderPath);
	virtual ~GLCourbe2DHSBs();

	void init(void);
	void display(void);
	void release(void);

    private:
	void loadShaderProgram(string shaderPath);

    private:
	float hueMinMax[2];
	ShaderPrograms* shaderProgramHSB;
    };

#endif
