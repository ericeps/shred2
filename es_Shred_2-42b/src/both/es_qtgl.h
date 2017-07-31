/* OpenGL widget.

 */

#ifndef ES_QTGL_H
#define ES_QTGL_H

#include <QGLWidget>
class es_key;
class es_draw;
class es_basegame;
//#include "es_world.h"
//#include "es_key.h"

class es_qtgl : public QGLWidget
{
	Q_OBJECT
public:
es_qtgl (es_basegame*, QWidget* parent = 0);
~es_qtgl ();
void setVars(es_key*,es_draw*);
//void setKey(es_key*);
//void setDraw(es_draw*);

QSize minimumSizeHint () const;
QSize sizeHint () const;

protected:
void initializeGL ();
void paintGL ();
void resizeGL (int width, int height);
void mousePressEvent (QMouseEvent* event);
void mouseReleaseEvent (QMouseEvent* event);
void mouseMoveEvent(QMouseEvent* event);
void keyPressEvent (QKeyEvent* keyevent);
void keyReleaseEvent (QKeyEvent* keyevent);

private slots:
void toggleFullScreen();

private:
	es_basegame *GameInfo;
	es_draw* Draw;
	es_key* Key;
	int windowWidth,windowHeight;

};



#endif
