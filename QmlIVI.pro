QT += quick gui core
CONFIG += c++17
TARGET = QmlIVI
TEMPLATE = app

SOURCES += \
    src/main.cpp \
    src/model/VehicleData.cpp \
    src/controller/VehicleSimulation.cpp

HEADERS += \
    src/model/VehicleData.h \
    src/controller/VehicleSimulation.h

RESOURCES += resources/resources.qrc

INCLUDEPATH += src