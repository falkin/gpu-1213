#ifndef GLUT_WINDOW_MANAGERS_H
#define GLUT_WINDOW_MANAGERS_H

#include "envGLTools.h"
#include "GLConfig.h"

#include "GLUTWindowCustomiser_A.h"
#include "GLUTCallBackTools.h"

#include <map>

using std::map;

/**
 * input :
 * 	pointer to GLImage source
 */
typedef void(*FRERE_MASTER_THREAD)(void**);

/**
 * On Linux befor using GLUTWindowManagers you have to call :
 *
 * 	GLUTWindowManagers::init(&argc,argv);
 *
 * Otherwise OpenGL cannot open and an error message will remind you that you haven't call glutInit !!
 *
 */
class CBI_GLTOOLS GLUTWindowManagers
    {
    private:
	GLUTWindowManagers();
	virtual ~GLUTWindowManagers();
    public:

	static void init(int argc,char** argv);
	static GLUTWindowManagers* getInstance();

	unsigned int createWindow(GLUTWindowCustomiser_A* glutWindowCustomiser);

	void deleteWindow(GLUTWindowCustomiser_A* glutWindowCustomiser=NULL);

	/**
	 * Warning Bloquanat !!
	 * Utiliser la méthode postDisplay de la class GLUTWindowCustomiser_A pour effectuer un traitement après le 1er rendu.
	 * Cette méthode postDisplay est appelé dans un thread séparé du display !
	 */
	void runALL();
	void runALL(FRERE_MASTER_THREAD methodeFrereMasterThread,void** param);

	map<unsigned int, GLUTWindowCustomiser_A*> getMapIdGlutWindowCustomiser();

	GLUTWindowCustomiser_A* getGLUTWindowCustomiser(unsigned int windowID);
	unsigned int getGLUT_ID(GLUTWindowCustomiser_A* glutWindowCustomier);

    private:
	bool isAllDisplaying();
	static void createDummyOpenGLContext();

    private:
	map<unsigned int, GLUTWindowCustomiser_A*> mapIdGlutWindowCustomiser;
	static GLUTWindowManagers* singleton;

    };

#endif
