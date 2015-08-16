#include <fstream>
#include <iostream>
#include <cstring>
#include <ctime>

#define N 18

class Measurement {
    private:
        static char* buffer;
        static struct tm ts;
        char timestamp[N];
        float voltage;
        float current;
        float cosphi;
    public:
        Measurement();
        ~Measurement();
        int getBuffer(char* filename);
        int firstStamp(void);
        int getTimestamp(void);
        int addTimedelta(int deltasec);
        int getVoltage(void);
        int getCurrent(void);
        int getPF(void);
        bool endCriteria(void);
        void saveEntry(void);
};
