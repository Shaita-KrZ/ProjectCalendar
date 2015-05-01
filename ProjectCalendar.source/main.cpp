#include <QApplication>
#include "fenetre.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    accueil a;
    a.setWindowTitle("Gérer son agenda");
    a.show();
    return app.exec();
}
