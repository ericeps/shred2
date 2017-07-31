/* Dialog tab for changing multiplayer game settings.

 */
#ifndef ES_MPSett
#define ES_MPSett

#include <QWidget>
class QComboBox;

class es_MPgame;

class es_MPSett : public QWidget
{
	Q_OBJECT
public:
	es_MPSett(es_MPgame *ginfo,QWidget *parent=0);

public slots:
void changeMap(int);
void changeDuration(int);

private:
es_MPgame *GameInfo;
QComboBox *mapCombo;
QComboBox *durCombo;

};

#endif
