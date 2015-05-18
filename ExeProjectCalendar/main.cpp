#include <QApplication>
#include "exception.h"
#include "tache.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    QPushButton button("salut ma gueule");
    button.show();
    return app.exec();
}

