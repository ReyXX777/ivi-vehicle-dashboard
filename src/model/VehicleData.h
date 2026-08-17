#ifndef VEHICLEDATA_H
#define VEHICLEDATA_H

#include <QObject>
#include <QtMath>

class VehicleData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double speed READ speed WRITE setSpeed NOTIFY speedChanged FINAL)
    Q_PROPERTY(double rpm READ rpm WRITE setRpm NOTIFY rpmChanged FINAL)
    Q_PROPERTY(double fuelLevel READ fuelLevel WRITE setFuelLevel NOTIFY fuelLevelChanged FINAL)
    Q_PROPERTY(double engineTemp READ engineTemp WRITE setEngineTemp NOTIFY engineTempChanged FINAL)

public:
    explicit VehicleData(QObject *parent = nullptr);

    double speed() const;
    void setSpeed(double newSpeed);

    double rpm() const;
    void setRpm(double newRpm);

    double fuelLevel() const;
    void setFuelLevel(double newFuelLevel);

    double engineTemp() const;
    void setEngineTemp(double newEngineTemp);

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

#endif
