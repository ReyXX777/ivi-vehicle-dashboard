#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>
#include <QFile>
#include <QDirIterator>
#include "model/VehicleData.h"
#include "controller/VehicleSimulation.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    VehicleData vehicleData;

    VehicleSimulation simulation;
    simulation.setVehicleData(&vehicleData);

    engine.rootContext()->setContextProperty("vehicle", &vehicleData);

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl) {
                qCritical() << "Failed to create QML object for:" << objUrl;
                QCoreApplication::exit(-1);
            } else if (obj) {
                qDebug() << "QML object created successfully:" << objUrl;
            }
        },
        Qt::QueuedConnection);

    // Print all available resources for debugging
    qDebug() << "Attempting to load:" << url;

    engine.load(url);

    // Check if load started at all
    if (engine.rootObjects().isEmpty()) {
        qCritical() << "No root objects loaded. Checking resource...";
        QFile testFile(":/qml/main.qml");
        if (testFile.exists()) {
            qDebug() << "Resource :/qml/main.qml EXISTS";
        } else {
            qCritical() << "Resource :/qml/main.qml DOES NOT EXIST";
            // List what IS available
            QDirIterator it(":", QDirIterator::Subdirectories);
            while (it.hasNext()) {
                qDebug() << "  Found resource:" << it.next();
            }
        }
    }

    simulation.init();

    return app.exec();
}