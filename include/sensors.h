#ifndef SENSORS_h
#define SENSORS_h

class Acelerometer {
    private:
        float ax, ay, az;

    public:
        void begin();
        void updatePosition();
        float getAcelerometerX();
        float getAcelerometerY();
        float convertRaw(int rawData);
        int convertAxesToServoTuning(float axis);
};

class Pressure {
    private:
        float groundAltitude;

    public:
        bool begin();
        float getAltitude();
        float getGroundDistance();
        float getTemperature();

        void saveGroundAltitude();
};

#endif