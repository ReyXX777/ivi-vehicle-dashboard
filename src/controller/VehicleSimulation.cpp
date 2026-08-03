#include "VehicleSimulation.h"
#include "model/VehicleData.h"

#include <QDateTime>
#include <cmath>

VehicleSimulation::VehicleSimulation(QObject *parent)
    : QObject(parent)
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

    m_previousTime = QDateTime::currentMSecsSinceEpoch();
    m_simTime = 0.0;
    m_timer.start(16); // 60fps target
}

void VehicleSimulation::stop()
{
    m_timer.stop();
}

void VehicleSimulation::update()
{
    if (!m_vehicle)
        return;

    quint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    double dt = (currentTime - m_previousTime) / 1000.0;

    
    if (dt > 0.1)
        dt = 0.016;

    m_previousTime = currentTime;
    m_simTime += dt;

    simulateDriveDynamics(dt);
    simulateFuel(dt);
    simulateEngineTemp(dt);
}

void VehicleSimulation::simulateDriveDynamics(double /*dt*/)
{
    
    double t = std::fmod(m_simTime, 120.0);
    double speed = 0.0;
    double rpm = 800.0;

    if (t < 5.0) {
        
        speed = 0.0;
        rpm = 800.0 + 30.0 * std::sin(m_simTime * 2.5);
    } else if (t < 20.0) {
        
        double progress = (t - 5.0) / 15.0;
        speed = 80.0 * progress * progress;
        rpm = 800.0 + 3200.0 * progress;
    } else if (t < 35.0) {
        
        speed = 80.0 + 2.0 * std::sin(m_simTime * 0.5);
        rpm = 2600.0 + 80.0 * std::sin(m_simTime * 0.7);
    } else if (t < 45.0) {
        
        double progress = (t - 35.0) / 10.0;
        speed = 80.0 + 60.0 * progress;
        rpm = 2600.0 + 2200.0 * progress;
    } else if (t < 65.0) {
        
        speed = 140.0 + 3.0 * std::sin(m_simTime * 0.3);
        rpm = 3800.0 + 100.0 * std::sin(m_simTime * 0.5);
    } else if (t < 75.0) {
        
        double progress = (t - 65.0) / 10.0;
        speed = 140.0 - 80.0 * progress;
        rpm = 3800.0 - 1800.0 * progress;
    } else if (t < 90.0) {
        
        speed = 55.0 + 12.0 * std::sin(m_simTime * 0.4);
        rpm = 2000.0 + 400.0 * std::sin(m_simTime * 0.6);
    } else if (t < 105.0) {
        
        double progress = (t - 90.0) / 15.0;
        speed = 55.0 * (1.0 - progress * progress);
        rpm = 2000.0 - 1200.0 * progress;
    } else {
        
        speed = 0.0;
        rpm = 800.0 + 30.0 * std::sin(m_simTime * 2.5);
    }

    
    speed += 0.2 * std::sin(m_simTime * 11.0);
    rpm += 15.0 * std::sin(m_simTime * 9.0);

    m_vehicle->setSpeed(std::max(0.0, speed));
    m_vehicle->setRpm(std::max(750.0, rpm));
}

void VehicleSimulation::simulateFuel(double dt)
{
    
    double rpmFraction = m_vehicle->rpm() / 8000.0;
    double speedFraction = m_vehicle->speed() / 260.0;

    
    double consumptionPerSec = 0.000004 + rpmFraction * 0.00002 + speedFraction * 0.00003;

    double fuel = m_vehicle->fuelLevel() - consumptionPerSec * dt;

    
    if (fuel < 0.05) {
        fuel = 0.90;
    }

    m_vehicle->setFuelLevel(fuel);
}

void VehicleSimulation::simulateEngineTemp(double dt)
{
    

    double rpmFraction = m_vehicle->rpm() / 8000.0;

    
    double targetTemp = 85.0 + rpmFraction * 20.0;

    
    if (m_simTime < 30.0) {
        double warmupProgress = m_simTime / 30.0;
        targetTemp = 25.0 + (targetTemp - 25.0) * warmupProgress * warmupProgress;
    }

    double currentTemp = m_vehicle->engineTemp();

    
    double thermalResponseRate = 0.016; // ~1/60 per second
    double tempDelta = (targetTemp - currentTemp) * thermalResponseRate * dt;

    
    double noise = 0.3 * std::sin(m_simTime * 1.7) + 0.2 * std::sin(m_simTime * 0.3);

    double newTemp = currentTemp + tempDelta + noise * dt;

    
    if (newTemp < 20.0) newTemp = 20.0;
    if (newTemp > 120.0) newTemp = 120.0;

    m_vehicle->setEngineTemp(newTemp);
}