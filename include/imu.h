#ifndef IMU_h
#define IMU_h

class IMU {
    private:
        float ax, ay, az;

    public:
        bool begin();
        void updatePosition();

        float getAccelerometerX();
        float getAccelerometerY();
        float getAccelerometerZ();
        float convertRaw(int rawData);

        int convertAxesToServoTuning(float axis);
};

#endif