#ifndef IMU_h
#define IMU_h

class IMU {
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

#endif