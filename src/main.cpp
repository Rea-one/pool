#include "qt_headers.h"

#include "manager.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    
    QQmlApplicationEngine qml_engine;

    qml_engine.load(QUrl(QStringLiteral("qrc:/ssc/pool.qml")));
    return app.exec();
}