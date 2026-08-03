#include "VehicleData.h"

VehicleData::VehicleData(QObject *parent)
    : QObject(parent)
    , m_speed(0.0)
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
    // NaN guard
    if (std::isnan(newSpeed))
        return;

    // Redundancy check - prevents redundant signal emissions
    if (qFuzzyCompare(m_speed, newSpeed))
        return;

    // Clamp to valid automotive range
    if (newSpeed < 0.0)
        newSpeed = 0.0;
    else if (newSpeed > 300.0)
        newSpeed = 300.0;

    m_speed = newSpeed;
    emit speedChanged();
}
void VehicleData::setRpm(double newRpm)
{
    if (std::isnan(newRpm))
        return;
    if (qFuzzyCompare(m_rpm, newRpm))
        return;
    if (newRpm < 0.0)
        newRpm = 0.0;
    else if (newRpm > 8000.0)
        newRpm = 8000.0;

    m_rpm = newRpm;
    emit rpmChanged();
}
void VehicleData::setFuelLevel(double newFuelLevel)
{
    if (std::isnan(newFuelLevel))
        return;
    if (qFuzzyCompare(m_fuelLevel, newFuelLevel))
        return;
    if (newFuelLevel < 0.0)
        newFuelLevel = 0.0;
    else if (newFuelLevel > 1.0)
        newFuelLevel = 1.0;

    m_fuelLevel = newFuelLevel;
    emit fuelLevelChanged();
}


void VehicleData::setEngineTemp(double newEngineTemp)
{
    if (std::isnan(newEngineTemp))
        return;
    if (qFuzzyCompare(m_engineTemp, newEngineTemp))
        return;
    if (newEngineTemp < 50.0)
        newEngineTemp = 50.0;
    else if (newEngineTemp > 180.0)
        newEngineTemp = 180.0;

    m_engineTemp = newEngineTemp;
    emit engineTempChanged();
}