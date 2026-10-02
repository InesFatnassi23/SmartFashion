#include <QApplication>
#include "gutilisateur.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    gutilisateur window;
    window.show();

    return app.exec();
}
