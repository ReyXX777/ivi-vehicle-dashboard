#include "VehicleSimulation.h"
#include "model/VehicleData.h"

#include <QDateTime>
#include <algorithm>
#include <cmath>
#include <cstdint>

namespace controller {

namespace {
    constexpr double g_maxDtThreshold{1.0e-1};
    constexpr double g_fallbackDt{1.6e-2};
    constexpr double g_idleRpm{8.0e2};
    constexpr double g_maxSimRpm{8.0e3};
    constexpr double g_maxSimSpeed{2.6e2};
}

VehicleSimulation::VehicleSimulation(QObject *l_parent)
    : QObject{l_parent}
{
    ::QObject::connect(&m_timer, &QTimer::timeout, this, &VehicleSimulation::update);
}

void VehicleSimulation::setVehicleData(::model::VehicleData *l_data)
{
    m_vehicle = l_data;
}

void VehicleSimulation::init()
{
    if (!m_vehicle) {
        ::qWarning("VehicleSimulation::init() called without VehicleData");
        return;
    }

    m_previousTime = static_cast<::std::uint64_t>(::QDateTime::currentMSecsSinceEpoch());
    m_simTime = 0.0e0;
    m_timer.start(static_cast<::std::int32_t>(16));
}

void VehicleSimulation::stop()
{
    m_timer.stop();
}

void VehicleSimulation::update()
{
    if (!m_vehicle)
        return;

    ::std::uint64_t l_currentTime{static_cast<::std::uint64_t>(::QDateTime::currentMSecsSinceEpoch())};
    double l_dt{(static_cast<double>(l_currentTime) - static_cast<double>(m_previousTime)) / 1.0e3};

    if (l_dt > g_maxDtThreshold)
        l_dt = g_fallbackDt;

    m_previousTime = l_currentTime;
    m_simTime += l_dt;

    this->simulateDriveDynamics(l_dt);
    this->simulateFuel(l_dt);
    this->simulateEngineTemp(l_dt);
}

void VehicleSimulation::simulateDriveDynamics(double l_dt)
{
    Q_UNUSED(l_dt);
    double l_t{::std::fmod(m_simTime, 1.2e2)};
    double l_speed{0.0e0};
    double l_rpm{g_idleRpm};

    if (l_t < 5.0e0) {
        l_speed = 0.0e0;
        l_rpm = g_idleRpm + 3.0e1 * ::std::sin(m_simTime * 2.5e0);
    } else if (l_t < 2.0e1) {
        double l_progress{(l_t - 5.0e0) / 1.5e1};
        l_speed = 8.0e1 * l_progress * l_progress;
        l_rpm = g_idleRpm + 3.2e3 * l_progress;
    } else if (l_t < 3.5e1) {
        l_speed = 8.0e1 + 2.0e0 * ::std::sin(m_simTime * 5.0e-1);
        l_rpm = 2.6e3 + 8.0e1 * ::std::sin(m_simTime * 7.0e-1);
    } else if (l_t < 4.5e1) {
        double l_progress{(l_t - 3.5e1) / 1.0e1};
        l_speed = 8.0e1 + 6.0e1 * l_progress;
        l_rpm = 2.6e3 + 2.2e3 * l_progress;
    } else if (l_t < 6.5e1) {
        l_speed = 1.4e2 + 3.0e0 * ::std::sin(m_simTime * 3.0e-1);
        l_rpm = 3.8e3 + 1.0e2 * ::std::sin(m_simTime * 5.0e-1);
    } else if (l_t < 7.5e1) {
        double l_progress{(l_t - 6.5e1) / 1.0e1};
        l_speed = 1.4e2 - 8.0e1 * l_progress;
        l_rpm = 3.8e3 - 1.8e3 * l_progress;
    } else if (l_t < 9.0e1) {
        double l_progress{(l_t - 7.5e1) / 1.5e1};
        l_speed = 5.5e1 + 1.2e1 * ::std::sin(m_simTime * 4.0e-1);
        l_rpm = 2.0e3 + 4.0e2 * ::std::sin(m_simTime * 6.0e-1);
    } else if (l_t < 1.05e2) {
        double l_progress{(l_t - 9.0e1) / 1.5e1};
        l_speed = 5.5e1 * (1.0e0 - l_progress * l_progress);
        l_rpm = 2.0e3 - 1.2e3 * l_progress;
    } else {
        l_speed = 0.0e0;
        l_rpm = g_idleRpm + 3.0e1 * ::std::sin(m_simTime * 2.5e0);
    }

    l_speed += 2.0e-1 * ::std::sin(m_simTime * 1.1e1);
    l_rpm += 1.5e1 * ::std::sin(m_simTime * 9.0e0);

    m_vehicle->setSpeed(::std::max(0.0e0, l_speed));
    m_vehicle->setRpm(::std::max(7.5e2, l_rpm));
}

void VehicleSimulation::simulateFuel(double l_dt)
{
    double l_rpmFraction{m_vehicle->rpm() / g_maxSimRpm};
    double l_speedFraction{m_vehicle->speed() / g_maxSimSpeed};

    double l_consumptionPerSec{4.0e-6 + l_rpmFraction * 2.0e-5 + l_speedFraction * 3.0e-5};

    double l_fuel{m_vehicle->fuelLevel() - l_consumptionPerSec * l_dt};

    if (l_fuel < 5.0e-2) {
        l_fuel = 9.0e-1;
    }

    m_vehicle->setFuelLevel(l_fuel);
}

void VehicleSimulation::simulateEngineTemp(double l_dt)
{
    double l_rpmFraction{m_vehicle->rpm() / g_maxSimRpm};

    double l_targetTemp{8.5e1 + l_rpmFraction * 2.0e1};

    if (m_simTime < 3.0e1) {
        double l_warmupProgress{m_simTime / 3.0e1};
        l_targetTemp = 2.5e1 + (l_targetTemp - 2.5e1) * l_warmupProgress * l_warmupProgress;
    }

    double l_currentTemp{m_vehicle->engineTemp()};

    double l_thermalResponseRate{1.6e-2};
    double l_tempDelta{(l_targetTemp - l_currentTemp) * l_thermalResponseRate * l_dt};

    double l_noise{3.0e-1 * ::std::sin(m_simTime * 1.7e0) + 2.0e-1 * ::std::sin(m_simTime * 3.0e-1)};

    double l_newTemp{l_currentTemp + l_tempDelta + l_noise * l_dt};

    if (l_newTemp < 2.0e1) l_newTemp = 2.0e1;
    if (l_newTemp > 1.2e2) l_newTemp = 1.2e2;

    m_vehicle->setEngineTemp(l_newTemp);
}

} // namespace controller
