#include "es_UINet.h"

//#include "es_client.h"
//#include "es_server.h"
#include "es_MPgame.h"
#include "netdefs.h"
#include <cstdlib>
#include <ctime>

#include <QHostAddress>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QObject>
#include <QFormLayout>
#include <QPushButton>
#include <QListWidget>
#include <QMessageBox>
#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QInputDialog>
#include <QNetworkInterface>

#include <iostream>


es_UINet::es_UINet(es_MPgame *ginfo, QWidget *parent) : QWidget(parent)
{		GameInfo = ginfo;
		Port1 = "51223";
		Port2 = "61221";
		
		clientStatus = new QLabel(tr("Client Off"));
		serverStatus = new QLabel(tr(""));

QHostAddress myTmpCliIP(es_ipcheck::getMyAddress());

QString mystrIP(myTmpCliIP.toString());
	if(mystrIP.isEmpty())
		clientLineEdit = new QLineEdit("192.168.2.97");
	else
		clientLineEdit = new QLineEdit(mystrIP);
		
		clientButton = new QPushButton(tr("Connect"));

	if(mystrIP.isEmpty())
		servLineEdit = new QLineEdit("192.168.2.97");
	else
		servLineEdit = new QLineEdit(mystrIP);
		servLineEdit->setMaxLength(15);

		servCBox = new QCheckBox(tr("Act as Server"));
		connect(servCBox, SIGNAL(clicked(bool)), this, SLOT(servCBoxChanged(bool)));
		connect(clientLineEdit, SIGNAL(returnPressed()), clientButton, SLOT(click()));
		connect(clientButton, SIGNAL(clicked()), this, SLOT(startClient()));
		connect(servLineEdit, SIGNAL(returnPressed()), clientButton, SLOT(click()));

		QFormLayout *formLayout = new QFormLayout;
		formLayout->addRow(tr("&Client Address:"),clientLineEdit);
		formLayout->addRow(tr("&Server Address:"),servLineEdit);

		QHBoxLayout *hLayout = new QHBoxLayout;
		hLayout->addWidget(clientButton);
		hLayout->addWidget(servCBox);
		
		QVBoxLayout *netLayout = new QVBoxLayout;
		netLayout->addLayout(formLayout);
		netLayout->addLayout(hLayout);
		netLayout->addWidget(clientStatus);
		netLayout->addWidget(serverStatus);
		
		setLayout(netLayout);
		
//		setFocusPolicy(Qt::StrongFocus);
//		clientLineEdit->setFocus();
}

void es_UINet::setServerStatus(int astat,QString sstat){
			if(astat==0)
			{serverStatus->setText("Server Off");
			servCBox->setChecked(0);
			}
			else if(astat==-1)
			{serverStatus->setText("Server off, "+sstat);
			servCBox->setChecked(0);
			}
			else if(astat==1)
			serverStatus->setText("Server On");
	}

void es_UINet::startServer()
{
	GameInfo->startServer(servLineEdit->text(),Port2,Port1);
}
void es_UINet::stopServer()
{
	GameInfo->stopServer();
}

void es_UINet::setClientStatus(int astat,QString sstat){
		if(astat<=0&& astat>=-5)
		{	clientButton->setText("Connect");
			clientButton->setEnabled(1);
			disconnect(clientButton, SIGNAL(clicked()), 0,0);
			connect(clientButton, SIGNAL(clicked()), this, SLOT(startClient()));
			if(astat==-5)
				clientStatus->setText("Unable to find server");
			else if(astat==-4)
			{
				clientButton->setEnabled(0);
				clientStatus->setText("Disconnecting from server...");
			}
			else if(astat==-3)
				clientStatus->setText("Connection to server was lost");
			else if(astat==-2)
				clientStatus->setText("Server terminated connection");
			else if(astat==-1)
				clientStatus->setText(sstat);	// unable to start client
			else if(astat==0)
				clientStatus->setText("Client Off");
		}
		else if(astat<=3)
		{	clientButton->setEnabled(0);
			if(astat==1)
			{	clientButton->setEnabled(0);
				clientStatus->setText("Looking for server...");
			}
			else if(astat==2)
			{
				clientStatus->setText("Server found and is waiting for validation");
				nameDialog();
			}
			else if(astat==3)
			{
				clientStatus->setText("Server found and is waiting for validation");
				nameDialog("Alias is taken, choose another:");
			}
		}
		else
		{	clientButton->setText("Disconnect");
			clientButton->setEnabled(1);
			disconnect(clientButton, SIGNAL(clicked()), 0,0);
			connect(clientButton, SIGNAL(clicked()), this, SLOT(stopClient()));
			if(astat==4)
			{
				clientStatus->setText("Connected to server");
			}
		}
	}
void es_UINet::startClient()
{
	GameInfo->startClient(clientLineEdit->text(),servLineEdit->text(),Port1,Port2);
}
void es_UINet::stopClient()
{
	GameInfo->stopClient();
}

QString randName(){
	QStringList tmplist;
	tmplist
	<<"Bee to Vent"
	<<"Show Plan"
	<<"Mooztart"
	<<"DZ G"
	<<"BlueBrick"
	<<"PatWishYa"
	<<"Bills for the Holiday"
	<<"Random Crawdad"
	<<"Nopole Gluon"
	<<"Spruced up Barn"
	<<"Mandullbrat"
	<<"Movearr"
	<<"Duhcart"
	<<"Wooler"
	<<"Booklid"
	<<"Tis Law"
	<<"Calfka"
	<<"Sandcho Panda"
	<<"Don Keynote eh"
	<<"Bella"
	<<"Art Fantralez"
	;
	srand( time(NULL) );
	int nameIndex = rand() % tmplist.size();
	return tmplist.at(nameIndex);
	}
void es_UINet::nameDialog(QString message){
	bool ok;
	if(message.isEmpty())
	message = "Enter Alias:";
	QString nameText = QInputDialog::getText(this, tr("Alias"),message, QLineEdit::Normal,
				randName());//,&ok);
//	if(!ok)
//		GameInfo->stopClient();
//	else
	if(!nameText.isEmpty())
		GameInfo->checkName(nameText);
	else
		nameDialog();
}
void es_UINet::servCBoxChanged(bool checked)
{
	if(checked)
	{
	startServer();
	}
	else
	{stopServer();
//	serverStatus->setText("Server off");
	}
std::cout<<"State == "<<checked<<std::endl;
}