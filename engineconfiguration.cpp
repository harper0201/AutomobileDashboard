#include "engineconfiguration.h"
#include <QTimer>
#include <QFile>
EngineConfiguration::EngineConfiguration()
{
    m_maxEngineRPM = 4000;
    m_driveRatio = 3.4;
    m_tyreDiamter = 680;
    m_curGear = 1;
    m_upShiftRPM = 3000;
    m_fuelLevel = 60;
    m_engineTemp = 60;
    m_distance = 500;
}

void EngineConfiguration::init(){
    m_gearRatios.append(2.97);
    m_gearRatios.append(2.07);
    m_gearRatios.append(1.43);
    m_gearRatios.append(1);
    m_gearRatios.append(0.84);
    m_gearRatios.append(0.56);
    m_gearSpeeed.append(5);
    m_gearSpeeed.append(37);
    m_gearSpeeed.append(54);
    m_gearSpeeed.append(78);
    m_gearSpeeed.append(111);
    m_gearSpeeed.append(132);

    isAccelerating = false;
    isBraking = false;

    QTimer *timer = new QTimer(this);
    connect(timer,&QTimer::timeout, this, &EngineConfiguration::calculateSpeed);
    timer->start(100);

    QTimer *ramdomevent = new QTimer(this);
    connect(ramdomevent,&QTimer::timeout, this, &EngineConfiguration::generateEvent);
    ramdomevent->start(3000);

    QTimer *distanceTimer = new QTimer(this);
    connect(distanceTimer,&QTimer::timeout, this, &EngineConfiguration::calculateDistance);
    distanceTimer->start(1000);

    QFile file("distance.txt");
    if (file.open(QIODevice::ReadWrite)){
        while(!file.atEnd()){
            QByteArray line = file.readLine();
            m_distance = line.toDouble();
        }
    }
    file.close();
}
void EngineConfiguration::setEngineRPM(int temp){
    if (temp > 0)
    {
        m_engineRPM = temp;
    }
}

int EngineConfiguration::engineRPM() const {
    return m_engineRPM;
}

void EngineConfiguration::setSpeed(int temp){
    m_speed = temp;
}
int EngineConfiguration::speed() const{
    return m_speed;
}

void EngineConfiguration::setMaxEngineRPM(double temp){
    m_maxEngineRPM = temp;
    emit maxEngineRPMChanged();

}
double EngineConfiguration::maxEngineRPM() const {
    return m_maxEngineRPM;
}

void EngineConfiguration::setCurGear(int temp){
   m_curGear = temp;

}
double EngineConfiguration::curGear() const {
    return m_curGear;
}


void EngineConfiguration::setFuelLevel(int temp){
    if (temp <= 100 && temp > 0){
           m_fuelLevel = temp;
           emit fuelLevelChanged();
    }
}
int EngineConfiguration::fuelLevel() const {
    return m_fuelLevel;
}

void EngineConfiguration::setDistance(QString temp) {
    m_distanceStr = temp;
}

QString EngineConfiguration::distance() const {
    return m_distanceStr;
}


void EngineConfiguration::setEngineTemp(int temp){
    m_engineTemp = temp;
    emit engineRPMChanged();
}
int EngineConfiguration::engineTemp() const {
    return m_engineTemp;
}
void EngineConfiguration::accelerate(bool acc){
    if (acc == true)
    {
        isBraking = false;
        isAccelerating = true;
        emit speedChanged();
        emit engineRPMChanged();
    }
    else {
        isAccelerating = false;
        emit speedChanged();
        emit engineRPMChanged();
    }
}
void EngineConfiguration::applyBrake(bool breaks){

    if (breaks == true){
        isBraking = true;
        isAccelerating = false;
        emit speedChanged();
        emit engineRPMChanged();
    }
    else {
        isBraking = false;
        emit speedChanged();
        emit engineRPMChanged();
    }
}

void EngineConfiguration::updateEngineProp(QString param, double value)
{
    if(param.compare("engineRPM") == 0)
    {
        m_maxEngineRPM = value;
        emit maxEngineRPMChanged();
    }
    else if(param.compare("tyreDiameter") == 0)
    {
        m_tyreDiamter = value;
    }
    else if(param.compare("firstGear") == 0)
    {
        m_gearRatios[0] = value;
    }
    else if(param.compare("secondGear") == 0)
    {
        m_gearRatios[1] = value;
    }
    else if(param.compare("threeGear") == 0)
    {
        m_gearRatios[2] = value;
    }
    else if(param.compare("fourGear") == 0)
    {
        m_gearRatios[3] = value;
    }
    else if(param.compare("fiveGear") == 0)
    {
        m_gearRatios[4] = value;
    }
    else if(param.compare("sixGear") == 0)
    {
        m_gearRatios[5] = value;
    }
    else if(param.compare("driveRatio") == 0)
    {
        m_driveRatio = value;
    }
    else if(param.compare("upshiftRPM") == 0)
    {
        m_upShiftRPM = value;
    }
}

double EngineConfiguration::getEngineProp(QString param)
{
    if(param.compare("engineRPM") == 0)
    {
        return m_maxEngineRPM;
    }
    else if(param.compare("tyreDiameter") == 0)
    {
        return m_tyreDiamter;
    }
    else if(param.compare("firstGear") == 0)
    {
       return m_gearRatios.at(0);
    }
    else if(param.compare("secondGear") == 0)
    {
       return m_gearRatios.at(1);
    }
    else if(param.compare("threeGear") == 0)
    {
       return m_gearRatios.at(2);
    }
    else if(param.compare("fourGear") == 0)
    {
       return m_gearRatios.at(3);
    }
    else if(param.compare("fiveGear") == 0)
    {
       return m_gearRatios.at(4);
    }
    else if(param.compare("sixGear") == 0)
    {
       return m_gearRatios.at(5);
    }
    else if(param.compare("driveRatio") == 0)
    {
        return m_driveRatio;
    }
    else if(param.compare("upshiftRPM") == 0)
    {
        return m_upShiftRPM;
    }
    else{
        return 0;
    }

}


void EngineConfiguration::calculateSpeed()
{
    if (isAccelerating == true && m_engineRPM < maxEngineRPM())
    {
        m_engineRPM = m_engineRPM + 50;
    }
    else if (isAccelerating == false && m_engineRPM > 0)
    {
        m_engineRPM = m_engineRPM - 50;
    }
    if (isBraking == true && isAccelerating == false){
        m_engineRPM = m_engineRPM - 200;
    }
    if (m_curGear < 6){
        if (isAccelerating == true && m_engineRPM > m_upShiftRPM && m_curGear <= 6) {
            m_curGear = m_curGear + 1;
            if (m_curGear >= 6){
                m_curGear = 6;
            }
            m_engineRPM = m_speed *(30 * m_gearRatios[m_curGear -1] * m_driveRatio) /(3.6 * 3.14 *(m_tyreDiamter/(2 * 1000)));
        }
    }
    if (isAccelerating == false) {
        if (m_curGear > 0) {
            if (m_speed <  m_gearSpeeed.at(m_curGear - 1)){
                m_curGear = m_curGear - 1;
                if (m_curGear < 1){
                    m_curGear = 1;
                }
                m_engineRPM = m_speed *(30 * m_gearRatios[m_curGear -1] * m_driveRatio) /(3.6 * 3.14 *(m_tyreDiamter/(2 * 1000)));
            }
        }
    }
    m_speed = 3.6 * m_engineRPM * 3.14 * (m_tyreDiamter/(2 * 1000)) / (30 * m_gearRatios[m_curGear -1] * m_driveRatio);
    emit speedChanged();
    emit engineRPMChanged();
    emit curGearChanged();
}

void EngineConfiguration::generateEvent(){
    saveDistance(m_distance);
    int randNum = rand() % 5;
    if (randNum == 1){
        emit eventGenerated("bettery");
    }
    else if (randNum == 2){
        emit eventGenerated("settings");
    }
    else if (randNum == 3){
        emit eventGenerated("enginefault");
    }
    else{
        m_fuelLevel = m_fuelLevel - 10;
        emit fuelLevelChanged();
    }
}

void EngineConfiguration::calculateDistance(){
    double secDist = double(m_speed)/3600;
    m_distance = m_distance + secDist;
    m_distanceStr = QString::number(m_distance, 'f',3);
    emit distanceChanged();
}

void EngineConfiguration::saveDistance(double tempDist){
    QFile file("distance.txt");
    if (file.open(QIODevice::ReadWrite)){
        if (tempDist > 0){
            QByteArray temp;
            temp.setNum(tempDist);
            file.write(temp);
        }
        file.close();
    }
}


