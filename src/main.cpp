#include "qt_headers.h"

#include "vesita.h"


int main(int argc, char *argv[])
{
    auto vesita_tar = std::make_shared<vesita>{};

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication::setOrganizationName("vesita");

    QGuiApplication app(argc, argv);
    
    QQmlApplicationEngine qml_engine;

    qml_engine.load(QUrl(QStringLiteral("qrc:/ssc/pool.qml")));
    qml_engine.registerSingletonType<vesita>("vesita", 1, 0, "vesita", [vesita_tar](QQmlEngine*, QJSEngine*) -> QObject* { return vesita_tar.get(); });
    return app.exec();
}