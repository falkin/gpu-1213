#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include "envTools.h"

#include "Matrices.h"
#include "Triangles.h"
#include <vector>

/**
 * axe x : m
 * axe y : n
 * axe z : matrice[i][j]
 */
class CBI_TOOLS HeightMap
    {
    public:
	HeightMap(Matrices* ptrMatrice,float dx,float dy);
	virtual ~HeightMap();

	void update();

	int getStripCount() const;
	int getIndexPerStripCount() const;
	int getVertexCount() const;
	std::vector<int*> getTriangleStripIndex() const;
	int* getTriangleStripIndex(int stripID) const;
	float* getNormals() const;
	float* getVertices() const;


	float* getVertex(unsigned int i,unsigned int j) const;
	float* getVertex(unsigned int vertexID) const;
	float getDx() const;
	float getDy() const;


    private :
	void computeNormals();
	float* computeVertexNormal(unsigned int i,unsigned int j);
	void fillVertices();
	unsigned int indice1D(unsigned int i,unsigned int j) const;
	void createBandeTriangleStrips();

	void getTriangleIncident(unsigned int i, unsigned int j,std::vector<int*> &tabTriangleIncidents);

	void getTriangleIncident(unsigned int i, unsigned int j,std::vector<Triangles*> &tabTriangleIncidents);

	float* triangleNormal(float* &s1,float* &s2,float* &s3);
    private:
	//Inputs
	Matrices* ptrMatrice;
	float dx;
	float dy;

	//Outputs
	int vertexCount;
	int stripCount;
	std::vector<int*> triangleStripIndex;
	float* normals;
	float* vertices;
    };

#endif /* HEIGHTMAP_H */
