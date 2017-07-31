/* Main Dialog box for Multiplayer game.

 */

#ifndef ES_SPBEGIN
#define ES_SPBEGIN

class es_SPSett;
class es_SPgame;

class QLabel;
class QLineEdit;
class QPushButton;
class QCheckBox;
class QListWidget;
class QMenuBar;
class QAction;
class QMenu;
//class QTabWidget;

#include <QHostAddress>
#include <QDialog>
#include <QTabWidget>

class es_SPbegin : public QWidget
{friend class es_SPgame;

	Q_OBJECT
public:
	es_SPbegin(es_SPgame *,QWidget *parent=0);

	void setupUI();

private slots:
//	void about();
	void requestStartGame();
	void stopGame();
	void mullAgain();

private:
	es_SPgame *GameInfo;
	es_SPSett *SPSett;

private:
QTabWidget *TabWidget;
QPushButton *startGameButton;

};

#endif
