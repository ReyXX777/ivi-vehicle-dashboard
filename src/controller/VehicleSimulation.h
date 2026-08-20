#ifndef VEHICLESIMULATION_H
#define VEHICLESIMULATION_H

#include <QObject>
#include <QTimer>
#include <cstdint>

namespace model {
class VehicleData;
}

namespace controller {

class VehicleSimulation : public QObject
{
    Q_OBJECT

public:
    explicit VehicleSimulation(QObject *l_parent = nullptr);

    void setVehicleData(::model::VehicleData *l_data);
    void init();
    void stop();

private slots:
    void update();

private:
    void simulateDriveDynamics(double l_dt);
    void simulateFuel(double l_dt);
    void simulateEngineTemp(double l_dt);

    ::model::VehicleData *m_vehicle{nullptr};
    QTimer m_timer{};
    ::std::uint64_t m_previousTime{0U};
    double m_simTime{0.0e0};
};

} // namespace controller

#endif // VEHICLESIMULATION_H
