#ifndef BMI_h
#define BMI_h

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

#endif