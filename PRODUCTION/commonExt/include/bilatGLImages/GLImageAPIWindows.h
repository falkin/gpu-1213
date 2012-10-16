#ifndef GLIMAGE_API_WINDOWS_H
#define GLIMAGE_API_WINDOWS_H

#include "envGLImage.h"
#include "GLPrimitiveDrawers.h"
#include "Graphic2Ds.h"
#include "GLUTWindowCustomiser_A.h"
#include "GUIEvents_I.h"
#include "TitleDrawers.h"

#include <string>
using std::string;

#include <vector>
using std::vector;

#include "ImageMOOs_A.h"

class CBI_GLIMAGE GLImageAPIWindows: public GLUTWindowCustomiser_A
    {
    public:
	GLImageAPIWindows(ImageMOOs_A* ptrImageMOO, bool isAnimationEnable = true, int pxFrame = 0, int pyFrame = 0);
	virtual ~GLImageAPIWindows();

	/**
	 * Update view from model
	 */
	virtual void updateView();

	/**
	 * width of the current frame
	 */
	int getDxFrame();

	/**
	 * height of the current frame
	 */
	int getDyFrame();


	void setAnimationEnable(bool isEnable);
	bool isAnimationEnable() const;

	void addGUIEvent(GUIEvents_I* ptrGUIEvent);
	void removeGUIEvent(GUIEvents_I* ptrGUIEvent);

	ImageMOOs_A* getImageMOO();

    protected:
	/**
	 * CallBack usable by Users !
	 */
	virtual void initPerformed();
	virtual void displayPerformed();
	virtual void reshapePerformed(int w, int h);
	virtual void mouseMovedPerformed(int x, int y);
	virtual void mousePressedPerformed(int button, int state, int x, int y);
	virtual void keyPressedPerformed(unsigned char key, int x, int y);
	virtual void specialKeyPressedPerformed(int key, int x, int y);

	/**
	 * CallBack use only by developpers !!
	 */
	virtual void init(void);
	virtual void display(void);
	virtual void reshape(int w, int h);
	virtual void mouseMoved(int x, int y);
	virtual void mousePressed(int button, int state, int x, int y);
	virtual void keyPressed(unsigned char key, int x, int y);
	virtual void specialKeyPressed(int key, int x, int y);
	/**
	 * Fonction appelé a chaque fois que glut n'a rien à faire dans la mainLoop.
	 * CàD s'il n'y a pas d'évenents utilisateur (souris,clavier,joystick,repaint,etc...)
	 */
	virtual void idleFunc();
	virtual void drawPrimitives();

	virtual void createPBO();
	virtual void fillPBO()=0;
	GLuint getPboID();
	GLuint getTextureID();

	virtual void createTexture();

	void drawTexture();
	void deleteTexture();

    private:
	void drawCredits();
	void drawTitles();

	// private:

    protected:
	ImageMOOs_A* ptrImageMOO;
	vector<GUIEvents_I*> tabGUIEvent;
	GLPrimitiveDrawers glPrimitiveDrawer;
	Graphic2Ds graphique2D;
	//Inputs
	bool animationEnable;
	int dxFrame;
	int dyFrame;

	//Tools
	GLuint textureID;
	GLuint pbo;
	TitleDrawers titleDrawer;
    };

#endif
