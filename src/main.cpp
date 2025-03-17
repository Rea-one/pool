#include "qt_headers.h"

#include "vesita.h"


int main(int argc, char *argv[])
{
    vesita *vesita_tar = new vesita(nullptr);

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication::setOrganizationName("vesita");

    QGuiApplication app(argc, argv);
    
    QQmlApplicationEngine qml_engine;

    qml_engine.load(QUrl(QStringLiteral("qrc:/ssc/pool.qml")));
    return app.exec();
}