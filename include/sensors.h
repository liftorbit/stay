#ifndef SENSORS_h
#define SENSORS_h

class Acelerometer {
    private:
        float ax, ay, az;

    public:
        bool begin();
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
        float getAverageSpeed(int periodOfTime);

        void saveGroundAltitude();
};

class GPS {
    private:
        float latitude, longitude, altitude;

    public:
        void begin();
        void updateLocation();

        float getLatitude();
        float getLongitude();
        float getAltitude();
};

#endif