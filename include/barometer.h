#ifndef SENSORS_h
#define SENSORS_h

class Barometer {
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

#endif