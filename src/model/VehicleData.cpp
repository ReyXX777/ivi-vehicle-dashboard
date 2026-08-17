#include "VehicleData.h"
#include <cmath>

VehicleData::VehicleData(QObject *parent)
    : QObject{parent}
    , m_speed{0.0e0}
{
}

double VehicleData::speed() const
{
    return m_speed;
}

double VehicleData::rpm() const
{
    return m_rpm;
}

double VehicleData::fuelLevel() const
{
    return m_fuelLevel;
}

double VehicleData::engineTemp() const
{
    return m_engineTemp;
}

void VehicleData::setSpeed(double newSpeed)
{
    if (std::isnan(newSpeed))
        return;

    if (qFuzzyCompare(m_speed, newSpeed))
        return;

    if (newSpeed < 0.0e0)
        newSpeed = 0.0e0;
    else if (newSpeed > 3.0e2)
        newSpeed = 3.0e2;

    m_speed = newSpeed;
    emit speedChanged();
}

void VehicleData::setRpm(double newRpm)
{
    if (std::isnan(newRpm))
        return;
    if (qFuzzyCompare(m_rpm, newRpm))
        return;
    if (newRpm < 0.0e0)
        newRpm = 0.0e0;
    else if (newRpm > 8.0e3)
        newRpm = 8.0e3;

    m_rpm = newRpm;
    emit rpmChanged();
}

void VehicleData::setFuelLevel(double newFuelLevel)
{
    if (std::isnan(newFuelLevel))
        return;
    if (qFuzzyCompare(m_fuelLevel, newFuelLevel))
        return;
    if (newFuelLevel < 0.0e0)
        newFuelLevel = 0.0e0;
    else if (newFuelLevel > 1.0e0)
        newFuelLevel = 1.0e0;

    m_fuelLevel = newFuelLevel;
    emit fuelLevelChanged();
}

void VehicleData::setEngineTemp(double newEngineTemp)
{
    if (std::isnan(newEngineTemp))
        return;
    if (qFuzzyCompare(m_engineTemp, newEngineTemp))
        return;
    if (newEngineTemp < 5.0e1)
        newEngineTemp = 5.0e1;
    else if (newEngineTemp > 1.8e2)
        newEngineTemp = 1.8e2;

    m_engineTemp = newEngineTemp;
    emit engineTempChanged();
}
