#include "es_MPSett.h"

#include "es_MPgame.h"
#include "es_client.h"
#include <QComboBox>
#include <QFormLayout>

es_MPSett::es_MPSett(es_MPgame *ginfo,QWidget *parent) : QWidget(parent)
{
	GameInfo = ginfo;
	
	mapCombo = new QComboBox;
	mapCombo->addItem(tr("One"));
	mapCombo->addItem(tr("Two"));
	connect(mapCombo,SIGNAL(currentIndexChanged(int)),this,SLOT(changeMap(int)));

	durCombo = new QComboBox;
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

	QFormLayout *formLayout = new QFormLayout;
	formLayout->addRow(tr("&Map:"),mapCombo);
	formLayout->addRow(tr("&Duration(minutes):"),durCombo);
	
	setLayout(formLayout);
}

void es_MPSett::changeMap(int amap){
	GameInfo->getClient()->changeMap(amap+1);
	}
	
void es_MPSett::changeDuration(int minutes){
	GameInfo->getClient()->changeDuration(minutes+1);
	}