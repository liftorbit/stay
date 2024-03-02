#ifndef SIGNALS_h
#define SIGNALS_h
#endif

class Signals {
    private:
        int buzzerPin, ledPin;

    public:
        Signals(int buzzerPin, int ledPin);

        void simpleSignal();

        void waitBCS();
        void receivedBCS();
        void errorToStartLOG();
        void waitLaunchAuthorization();
        void stopLaunch();
        void launchUnauthorized();
};