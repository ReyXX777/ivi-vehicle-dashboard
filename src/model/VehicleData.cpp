#include "VehicleData.h"
#include <cmath>

namespace model {

namespace {
    constexpr double g_minSpeed{0.0e0};
    constexpr double g_maxSpeed{3.0e2};

    constexpr double g_minRpm{0.0e0};
    constexpr double g_maxRpm{8.0e3};

    constexpr double g_minFuel{0.0e0};
    constexpr double g_maxFuel{1.0e0};

    constexpr double g_minEngineTemp{5.0e1};
    constexpr double g_maxEngineTemp{1.8e2};
}

VehicleData::VehicleData(QObject *l_parent)
    : QObject{l_parent}
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

void VehicleData::setSpeed(double l_newSpeed)
{
    if (::std::isnan(l_newSpeed))
        return;

    if (::qFuzzyCompare(m_speed, l_newSpeed))
        return;

    if (l_newSpeed < g_minSpeed)
        l_newSpeed = g_minSpeed;
    else if (l_newSpeed > g_maxSpeed)
        l_newSpeed = g_maxSpeed;

    m_speed = l_newSpeed;
    emit speedChanged();
}

void VehicleData::setRpm(double l_newRpm)
{
    if (::std::isnan(l_newRpm))
        return;

    if (::qFuzzyCompare(m_rpm, l_newRpm))
        return;

    if (l_newRpm < g_minRpm)
        l_newRpm = g_minRpm;
    else if (l_newRpm > g_maxRpm)
        l_newRpm = g_maxRpm;

    m_rpm = l_newRpm;
    emit rpmChanged();
}

void VehicleData::setFuelLevel(double l_newFuelLevel)
{
    if (::std::isnan(l_newFuelLevel))
        return;

    if (::qFuzzyCompare(m_fuelLevel, l_newFuelLevel))
        return;

    if (l_newFuelLevel < g_minFuel)
        l_newFuelLevel = g_minFuel;
    else if (l_newFuelLevel > g_maxFuel)
        l_newFuelLevel = g_maxFuel;

    m_fuelLevel = l_newFuelLevel;
    emit fuelLevelChanged();
}

void VehicleData::setEngineTemp(double l_newEngineTemp)
{
    if (::std::isnan(l_newEngineTemp))
        return;

    if (::qFuzzyCompare(m_engineTemp, l_newEngineTemp))
        return;

    if (l_newEngineTemp < g_minEngineTemp)
        l_newEngineTemp = g_minEngineTemp;
    else if (l_newEngineTemp > g_maxEngineTemp)
        l_newEngineTemp = g_maxEngineTemp;

    m_engineTemp = l_newEngineTemp;
    emit engineTempChanged();
}

} // namespace model
