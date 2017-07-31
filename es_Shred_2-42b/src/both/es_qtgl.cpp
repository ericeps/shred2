#include "es_qtgl.h"

#include "es_draw.h"
#include "es_key.h"
#include "es_basegame.h"
#include <QShortcut>
#include <iostream>

es_qtgl::es_qtgl (es_basegame *agame,QWidget* parent)
	: QGLWidget (parent)
{
	resize (sizeHint ());
	GameInfo=agame;
	setCursor( QCursor( Qt::BlankCursor ) );
}

es_qtgl::~es_qtgl ()
{
}

void es_qtgl::setVars(es_key *akey,es_draw *ad){
Key=akey;
Draw=ad;
}
/*
void es_qtgl::setKey(es_key* akey){
Key = akey;
}
void es_qtgl::setDraw(es_draw* adraw){
Draw = adraw;
}
*/
QSize es_qtgl::minimumSizeHint () const
{
	return QSize (50, 50);
}

QSize es_qtgl::sizeHint () const
{
	return QSize (1000, 800);
}

void es_qtgl::initializeGL ()
{
	glClearColor (.4,.4,.4, 1.0);
	glEnable (GL_DEPTH_TEST);

/*  glShadeModel (GL_SMOOTH);

	GLfloat light_position[] = {10,10,10,0};
//	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
	glLightfv(GL_LIGHT0,GL_POSITION, light_position);
	glColorMaterial(GL_FRONT,GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
*/
}

void es_qtgl::paintGL ()
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity ();
if(GameInfo->isGameOn())
{
		glPushMatrix();
			Draw->drawAll();
		glPopMatrix();
		glMatrixMode (GL_PROJECTION);
		glPushMatrix();
			glLoadIdentity ();
			gluOrtho2D (0, windowWidth, 0, windowHeight);
			glMatrixMode (GL_MODELVIEW);
				Draw->drawStats();
			glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
}
}

void es_qtgl::resizeGL (int width, int height)
{windowWidth = width;
windowHeight = height;
	glViewport (0, 0, width, height);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(45.0, (double)width/(double)height, 1, 800);
	glMatrixMode (GL_MODELVIEW);
}

void es_qtgl::mousePressEvent (QMouseEvent* event)
{
	
}
void es_qtgl::mouseMoveEvent(QMouseEvent *event)
{

}
void es_qtgl::mouseReleaseEvent (QMouseEvent* event)
{
}

void es_qtgl::keyPressEvent (QKeyEvent* keyevent)
{
if(GameInfo->isGameOn())
Key->press(keyevent);
}

void es_qtgl::keyReleaseEvent (QKeyEvent* keyevent)
{
if(GameInfo->isGameOn())
Key->release(keyevent);
}

void es_qtgl::toggleFullScreen(){
if(windowState()==Qt::WindowFullScreen)
showNormal();
else if(windowState()==Qt::WindowNoState)
showFullScreen();
}
