#ifndef ENGINECONFIGURATION_H
#define ENGINECONFIGURATION_H

#include <QObject>

class EngineConfiguration : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int engineRPM READ engineRPM WRITE setEngineRPM  NOTIFY engineRPMChanged);
    Q_PROPERTY(int speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(double maxEngineRPM READ maxEngineRPM WRITE setMaxEngineRPM NOTIFY maxEngineRPMChanged)
    Q_PROPERTY(double curGear READ curGear WRITE setCurGear NOTIFY curGearChanged)
    Q_PROPERTY(double fuelLevel READ fuelLevel WRITE setFuelLevel NOTIFY fuelLevelChanged)
    Q_PROPERTY(double engineTemp READ engineTemp WRITE setEngineTemp NOTIFY engineTempChanged)
    Q_PROPERTY(QString distance READ distance WRITE setDistance NOTIFY distanceChanged)

public:
    EngineConfiguration();

    void setEngineRPM(int temp);
    int engineRPM() const;

    void setSpeed(int temp);
    int speed() const;

    void setMaxEngineRPM(double temp);
    double maxEngineRPM() const;

    void setCurGear(int temp);
    double curGear() const;

    void setFuelLevel(int temp);
    int fuelLevel() const;

    void setEngineTemp(int temp);
    int engineTemp() const;

    void setDistance(QString temp);
    QString distance() const;

    void init();

    Q_INVOKABLE double getEngineProp(QString param);
    Q_INVOKABLE void accelerate(bool acc);
    Q_INVOKABLE void applyBrake(bool breaks);
    Q_INVOKABLE void updateEngineProp(QString param, double value);

public slots:
    void calculateSpeed();
    void calculateDistance();
    void generateEvent();
signals:
    void engineRPMChanged();
    void speedChanged();
    void maxEngineRPMChanged();
    void curGearChanged();
    void fuelLevelChanged();
    void engineTempChanged();
    void eventGenerated(QString event);
    void distanceChanged();

private:
    void saveDistance(double tempDist);
    int m_engineRPM;
    int m_speed;
    int m_curGear;
    int m_upShiftRPM;
    int m_fuelLevel;
    int m_engineTemp;

    double m_maxEngineRPM;
    double m_tyreDiamter;
    QVector<double> m_gearRatios;
    QVector<int> m_gearSpeeed;
    double m_driveRatio;
    double m_distance;
    QString m_distanceStr;
    bool isAccelerating;
    bool isBraking;
};

#endif // ENGINECONFIGURATION_H
