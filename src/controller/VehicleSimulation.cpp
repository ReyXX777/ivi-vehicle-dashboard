#include "VehicleSimulation.h"
#include "model/VehicleData.h"

#include <QDateTime>
#include <algorithm>
#include <cmath>
#include <cstdint>

VehicleSimulation::VehicleSimulation(QObject *parent)
    : QObject{parent}
{
    connect(&m_timer, &QTimer::timeout, this, &VehicleSimulation::update);
}

void VehicleSimulation::setVehicleData(VehicleData *data)
{
    m_vehicle = data;
}

void VehicleSimulation::init()
{
    if (!m_vehicle) {
        qWarning("VehicleSimulation::init() called without VehicleData");
        return;
    }

    m_previousTime = static_cast<std::uint64_t>(QDateTime::currentMSecsSinceEpoch());
    m_simTime = 0.0e0;
    m_timer.start(static_cast<std::int32_t>(16));
}

void VehicleSimulation::stop()
{
    m_timer.stop();
}

void VehicleSimulation::update()
{
    if (!m_vehicle)
        return;

    std::uint64_t currentTime{static_cast<std::uint64_t>(QDateTime::currentMSecsSinceEpoch())};
    double dt{(static_cast<double>(currentTime) - static_cast<double>(m_previousTime)) / 1.0e3};

    if (dt > 1.0e-1)
        dt = 1.6e-2;

    m_previousTime = currentTime;
    m_simTime += dt;

    simulateDriveDynamics(dt);
    simulateFuel(dt);
    simulateEngineTemp(dt);
}

void VehicleSimulation::simulateDriveDynamics(double)
{
    double t{std::fmod(m_simTime, 1.2e2)};
    double speed{0.0e0};
    double rpm{8.0e2};

    if (t < 5.0e0) {
        speed = 0.0e0;
        rpm = 8.0e2 + 3.0e1 * std::sin(m_simTime * 2.5e0);
    } else if (t < 2.0e1) {
        double progress{(t - 5.0e0) / 1.5e1};
        speed = 8.0e1 * progress * progress;
        rpm = 8.0e2 + 3.2e3 * progress;
    } else if (t < 3.5e1) {
        speed = 8.0e1 + 2.0e0 * std::sin(m_simTime * 5.0e-1);
        rpm = 2.6e3 + 8.0e1 * std::sin(m_simTime * 7.0e-1);
    } else if (t < 4.5e1) {
        double progress{(t - 3.5e1) / 1.0e1};
        speed = 8.0e1 + 6.0e1 * progress;
        rpm = 2.6e3 + 2.2e3 * progress;
    } else if (t < 6.5e1) {
        speed = 1.4e2 + 3.0e0 * std::sin(m_simTime * 3.0e-1);
        rpm = 3.8e3 + 1.0e2 * std::sin(m_simTime * 5.0e-1);
    } else if (t < 7.5e1) {
        double progress{(t - 6.5e1) / 1.0e1};
        speed = 1.4e2 - 8.0e1 * progress;
        rpm = 3.8e3 - 1.8e3 * progress;
    } else if (t < 9.0e1) {
        speed = 5.5e1 + 1.2e1 * std::sin(m_simTime * 4.0e-1);
        rpm = 2.0e3 + 4.0e2 * std::sin(m_simTime * 6.0e-1);
    } else if (t < 1.05e2) {
        double progress{(t - 9.0e1) / 1.5e1};
        speed = 5.5e1 * (1.0e0 - progress * progress);
        rpm = 2.0e3 - 1.2e3 * progress;
    } else {
        speed = 0.0e0;
        rpm = 8.0e2 + 3.0e1 * std::sin(m_simTime * 2.5e0);
    }

    speed += 2.0e-1 * std::sin(m_simTime * 1.1e1);
    rpm += 1.5e1 * std::sin(m_simTime * 9.0e0);

    m_vehicle->setSpeed(std::max(0.0e0, speed));
    m_vehicle->setRpm(std::max(7.5e2, rpm));
}

void VehicleSimulation::simulateFuel(double dt)
{
    double rpmFraction{m_vehicle->rpm() / 8.0e3};
    double speedFraction{m_vehicle->speed() / 2.6e2};

    double consumptionPerSec{4.0e-6 + rpmFraction * 2.0e-5 + speedFraction * 3.0e-5};

    double fuel{m_vehicle->fuelLevel() - consumptionPerSec * dt};

    if (fuel < 5.0e-2) {
        fuel = 9.0e-1;
    }

    m_vehicle->setFuelLevel(fuel);
}

void VehicleSimulation::simulateEngineTemp(double dt)
{
    double rpmFraction{m_vehicle->rpm() / 8.0e3};

    double targetTemp{8.5e1 + rpmFraction * 2.0e1};

    if (m_simTime < 3.0e1) {
        double warmupProgress{m_simTime / 3.0e1};
        targetTemp = 2.5e1 + (targetTemp - 2.5e1) * warmupProgress * warmupProgress;
    }

    double currentTemp{m_vehicle->engineTemp()};

    double thermalResponseRate{1.6e-2};
    double tempDelta{(targetTemp - currentTemp) * thermalResponseRate * dt};

    double noise{3.0e-1 * std::sin(m_simTime * 1.7e0) + 2.0e-1 * std::sin(m_simTime * 3.0e-1)};

    double newTemp{currentTemp + tempDelta + noise * dt};

    if (newTemp < 2.0e1) newTemp = 2.0e1;
    if (newTemp > 1.2e2) newTemp = 1.2e2;

    m_vehicle->setEngineTemp(newTemp);
}
