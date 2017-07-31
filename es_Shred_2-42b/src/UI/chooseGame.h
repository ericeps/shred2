/* Dialog box prompting player for single player or multiplayer game mode.

 */
#include "es_MPgame.h"
#include "es_SPgame.h"

#include <QWidget>
class QPushButton;
class es_MPgame;
class es_SPgame;

class chooseGame : public QWidget
{
	Q_OBJECT
public:
chooseGame(QWidget *parent=0);
public slots:
void startMulti();
void startSingle();
void switchGame();
void mullAgain();

private:
es_MPgame * MPgame;
es_SPgame * SPgame;
int gameStatus;
QPushButton *Multi;
QPushButton *Single;
};
