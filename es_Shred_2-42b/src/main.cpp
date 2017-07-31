#include <QApplication>
#include <iostream>
//#include "es_begin.h"
//#include "es_basegame.h"
//#include "es_MPgame.h"
//#include "es_SPgame.h"
//#include "es_mainwindow.h"
#include <QByteArray>
//#include "es_sequence.h"
#include "chooseGame.h"

int main(int argc, char *argv[])
{
QApplication mario(argc,argv);

chooseGame *Choose = new chooseGame;
Choose->show();

//es_SPgame *SPgame = new es_SPgame();
//SPgame->newUI();


return mario.exec();
}
