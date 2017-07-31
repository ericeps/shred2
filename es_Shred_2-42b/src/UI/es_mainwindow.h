/* Menubar and keys-bindings that switch between windows.

 */

#ifndef MAINWINDOW
#define MAINWINDOW

class es_MPbegin;
class es_SPbegin;
class es_UIChat;
class es_qtgl;
class es_UIStats;
#include <QMenuBar>


class es_menubar : public QMenuBar
{
	Q_OBJECT
public:
	es_menubar(QWidget *parent=0);
public slots:
	void about();

private:
//	QMenuBar *theMenu;
	QMenu *aboutMenu;
	QAction *aboutAct;
	QAction *aboutQtAct;
};

	#include <QObject>
	
	class es_MPwindow : public QObject
	{
			Q_OBJECT
		public:
		es_MPwindow(es_MPbegin*, es_UIChat*, es_qtgl*, es_UIStats*);
		
		public slots:
		void showBeg(bool=1);
		void showChat(bool=1);
		void showGL(bool=1);
		void showStats(bool=1);
		
		private:
		es_menubar MenuBar;
		es_MPbegin *Begin;
		es_UIChat *UIChat;
		es_qtgl *Es_qtgl;
		es_UIStats *UIStats;
	};

class es_SPwindow : public QObject
{
		Q_OBJECT
	public:
	es_SPwindow(es_SPbegin*, es_qtgl*);

	public slots:
	void showBeg(bool=1);
	void showGL(bool=1);

	private:
	es_menubar MenuBar;
	es_SPbegin *Begin;
	es_qtgl *Es_qtgl;
};
#endif
