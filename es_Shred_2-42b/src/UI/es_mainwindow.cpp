

#include "es_mainwindow.h"
#include "es_MPbegin.h"
#include "es_SPbegin.h"
#include "es_UINet.h"
#include "es_UIChat.h"
#include "es_qtgl.h"
#include "es_UIStats.h"
#include <QDockWidget>
#include <QMenuBar>
#include <QAction>
#include <QMenu>
#include <QObject>
#include <QApplication>
#include <QMessageBox>
#include <QShortCut>
#include <iostream>

void es_menubar::about()
{
	//infoLabel->setText(tr("Invoked <b>Help|About</b>"));
	QMessageBox::about(this, tr("About Menu"),
		tr("<b>&#169; 2010 by Eric P. Stone</b>"));
}
es_menubar::es_menubar(QWidget* parent) : QMenuBar(parent)
{
//		theMenu = new QMenuBar(0);
		aboutMenu = addMenu(tr("&About"));
		aboutAct = new QAction(tr("About"), this);
		aboutQtAct = new QAction(tr("About &Qt"), this);
		aboutMenu->addAction(aboutAct);
		aboutMenu->addAction(aboutQtAct);
		connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
		connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

//#ifdef __APPLE__
	es_MPwindow::es_MPwindow(es_MPbegin* abegin, es_UIChat *achat, es_qtgl *agl, es_UIStats *astat){
	Begin=abegin;
	UIChat=achat;
	Es_qtgl = agl;
	UIStats = astat;
	
	
	QShortcut *beg1SC = new QShortcut(Qt::Key_F4,UIChat);
	QShortcut *beg2SC = new QShortcut(Qt::Key_F4,Es_qtgl);
	QShortcut *beg3SC = new QShortcut(Qt::Key_F4,UIStats);
	connect(beg1SC,SIGNAL(activated()),this,SLOT(showBeg()));
	connect(beg2SC,SIGNAL(activated()),this,SLOT(showBeg()));
	connect(beg3SC,SIGNAL(activated()),this,SLOT(showBeg()));
	
	QShortcut *game1SC = new QShortcut(Qt::Key_F2,Begin);
	QShortcut *game2SC = new QShortcut(Qt::Key_F2,UIChat);
	QShortcut *game3SC = new QShortcut(Qt::Key_F2,UIStats);
	connect(game1SC,SIGNAL(activated()),this,SLOT(showGL()));
	connect(game2SC,SIGNAL(activated()),this,SLOT(showGL()));
	connect(game3SC,SIGNAL(activated()),this,SLOT(showGL()));
	
	QShortcut *chat1SC = new QShortcut(Qt::Key_F3,Begin);
	QShortcut *chat2SC = new QShortcut(Qt::Key_F3,Es_qtgl);
	QShortcut *chat3SC = new QShortcut(Qt::Key_F3,UIStats);
	connect(chat1SC,SIGNAL(activated()),this,SLOT(showChat()));
	connect(chat2SC,SIGNAL(activated()),this,SLOT(showChat()));
	connect(chat3SC,SIGNAL(activated()),this,SLOT(showChat()));

	

	QShortcut *screenShortcut = new QShortcut(Qt::Key_F5,Es_qtgl);
	connect(screenShortcut,SIGNAL(activated()),Es_qtgl,SLOT(toggleFullScreen()));
        Es_qtgl->setFocusPolicy ( Qt::StrongFocus );
	Begin->move(300,250);
	showBeg(1);
	UIChat->move(50+Begin->geometry().x()+Begin->frameGeometry().width(),Begin->y());
	}
	void es_MPwindow::showBeg(bool tmp){
		Begin->setVisible(tmp);
		if(tmp==1)
		{Begin->raise();
		Begin->activateWindow();
		}
		}
	void es_MPwindow::showChat(bool tmp){
		UIChat->setVisible(tmp);
		if(tmp==1)
		{UIChat->raise();
		UIChat->activateWindow();
		}
		}
	void es_MPwindow::showGL(bool tmp){
		Es_qtgl->setVisible(tmp);
		if(tmp==1)
		{
		Es_qtgl->raise();
		Es_qtgl->activateWindow();
		}
		}
	void es_MPwindow::showStats(bool tmp){
		UIStats->setVisible(tmp);
		if(tmp==1)
		{UIStats->raise();
		UIStats->activateWindow();
		}
		}
		
		
	es_SPwindow::es_SPwindow(es_SPbegin* abegin, es_qtgl *agl){
	Begin=abegin;
	Es_qtgl = agl;
	
	
	QShortcut *beg2SC = new QShortcut(Qt::Key_F4,Es_qtgl);
	connect(beg2SC,SIGNAL(activated()),this,SLOT(showBeg()));
	
	QShortcut *game1SC = new QShortcut(Qt::Key_F2,Begin);
	connect(game1SC,SIGNAL(activated()),this,SLOT(showGL()));
	

	QShortcut *screenShortcut = new QShortcut(Qt::Key_F5,Es_qtgl);
	connect(screenShortcut,SIGNAL(activated()),Es_qtgl,SLOT(toggleFullScreen()));
        Es_qtgl->setFocusPolicy ( Qt::StrongFocus );
	Begin->move(300,250);
	showBeg(1);
	}
	void es_SPwindow::showBeg(bool tmp){
		Begin->setVisible(tmp);
		if(tmp==1)
		{Begin->raise();
		Begin->activateWindow();
		}
		}

	void es_SPwindow::showGL(bool tmp){
		Es_qtgl->setVisible(tmp);
		if(tmp==1)
		{
		Es_qtgl->raise();
		Es_qtgl->activateWindow();
		}
		}
