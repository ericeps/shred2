/* Main Dialog box for Multiplayer game.

 */

#ifndef ES_BEGIN
#define ES_BEGIN

class es_server;
class es_client;
class es_MPgame;
class es_UINet;
class es_MPSett;

#include <QHostAddress>
#include <QDialog>
#include <QTabWidget>

class es_MPbegin : public QWidget
{friend class es_MPgame;

	Q_OBJECT
public:
	es_MPbegin(es_MPgame *,QWidget *parent=0);

	void setupUI();

private slots:
	void requestStartGame();
	void stopGame();
	void mullAgain();

private:
	es_MPgame *GameInfo;
	es_UINet *UINet;
	es_MPSett *MPSett;

private:
QTabWidget *TabWidget;

QPushButton *startGameButton;

};

#endif
