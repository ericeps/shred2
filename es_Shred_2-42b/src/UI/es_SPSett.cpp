#include "es_SPSett.h"

#include "es_SPgame.h"
#include "es_client.h"
#include <QComboBox>
#include <QFormLayout>

es_SPSett::es_SPSett(es_SPgame *ginfo,QWidget *parent) : QWidget(parent)
{
	GameInfo = ginfo;
	
	mapCombo = new QComboBox;
        mapCombo->addItem(tr("Original"));
        mapCombo->addItem(tr("Platforms"));
        mapCombo->addItem(tr("Test"));
        mapCombo->addItem(tr("Noodle"));

/*	durCombo = new QComboBox;
	durCombo->addItem(tr("1"));
	durCombo->addItem(tr("2"));
	durCombo->addItem(tr("3"));
	durCombo->addItem(tr("4"));
	durCombo->addItem(tr("5"));
	durCombo->addItem(tr("6"));
	durCombo->addItem(tr("7"));
	durCombo->addItem(tr("8"));
	durCombo->addItem(tr("9"));
	durCombo->addItem(tr("10"));
	connect(durCombo,SIGNAL(currentIndexChanged(int)),this,SLOT(changeDuration(int)));
*/
	QFormLayout *formLayout = new QFormLayout;
	formLayout->addRow(tr("&Map:"),mapCombo);
	
	setLayout(formLayout);
}

int es_SPSett::currentMap(){
return mapCombo->currentIndex()+1;
}
