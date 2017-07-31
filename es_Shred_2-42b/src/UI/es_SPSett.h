/* Dialog tab for changing single player game settings.

 */

#ifndef ES_SPSett
#define ES_SPSett

#include <QWidget>
class QComboBox;

class es_SPgame;

class es_SPSett : public QWidget
{
	Q_OBJECT
public:
	es_SPSett(es_SPgame *ginfo,QWidget *parent=0);
	int currentMap();

private:
es_SPgame *GameInfo;
QComboBox *mapCombo;

};

#endif
