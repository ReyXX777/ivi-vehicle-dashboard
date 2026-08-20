#ifndef VEHICLEDATA_H
#define VEHICLEDATA_H

#include <QObject>
#include <QtMath>

namespace model {

class VehicleData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double speed READ speed WRITE setSpeed NOTIFY speedChanged FINAL)
    Q_PROPERTY(double rpm READ rpm WRITE setRpm NOTIFY rpmChanged FINAL)
    Q_PROPERTY(double fuelLevel READ fuelLevel WRITE setFuelLevel NOTIFY fuelLevelChanged FINAL)
    Q_PROPERTY(double engineTemp READ engineTemp WRITE setEngineTemp NOTIFY engineTempChanged FINAL)

public:
    explicit VehicleData(QObject *l_parent = nullptr);

    double speed() const;
    void setSpeed(double l_newSpeed);

    double rpm() const;
    void setRpm(double l_newRpm);

    double fuelLevel() const;
    void setFuelLevel(double l_newFuelLevel);

    double engineTemp() const;
    void setEngineTemp(double l_newEngineTemp);

signals:
    void speedChanged();
    void rpmChanged();
    void fuelLevelChanged();
    void engineTempChanged();

private:
    double m_speed{0.0e0};
    double m_rpm{0.0e0};
    double m_fuelLevel{7.5e-1};
    double m_engineTemp{9.0e1};
};

} // namespace model

#endif // VEHICLEDATA_H
