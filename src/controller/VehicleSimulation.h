#ifndef VEHICLESIMULATION_H
#define VEHICLESIMULATION_H

#include <QObject>
#include <QTimer>

class VehicleData;

class VehicleSimulation : public QObject
{
    Q_OBJECT

public:
    explicit VehicleSimulation(QObject *parent = nullptr);

    void setVehicleData(VehicleData *data);
    void init();
    void stop();

private slots:
    void update();

private:
    void simulateDriveDynamics(double dt);
    void simulateFuel(double dt);
    void simulateEngineTemp(double dt);
    VehicleData *m_vehicle = nullptr;
    QTimer m_timer;
    quint64 m_previousTime = 0;
    double m_simTime = 0.0;
};

#endif // VEHICLESIMULATION_H