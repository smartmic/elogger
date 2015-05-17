// elogger.cpp
#include <fstream>
#include <iostream>
#include <cstring>
#include <ctime>

#define N 18

using namespace std;

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

Measurement::Measurement() {
}

Measurement::~Measurement() {
}

int Measurement::firstStamp(void) {
    int offset = 3;
    unsigned int datecode;
    memset(&ts, 0, sizeof(tm));
    buffer += offset;
    while (offset <= 7) {
            datecode = static_cast<unsigned int>(*buffer & 0xFF);
            switch (offset) {
                case 3:
                    ts.tm_mon = datecode - 1;
                case 4:
                    ts.tm_mday = datecode;
                case 5:
                    ts.tm_year = datecode - 1900 + 2000;
                case 6:
                    ts.tm_hour = datecode;
                case 7:
                    ts.tm_min = datecode;
            }
            buffer++;
            offset++;
         }
    mktime(&ts);
    getTimestamp();
    return 0;
}

int Measurement::getTimestamp(void) {
    if (strftime(timestamp, sizeof(timestamp)-1, "%Y-%m-%d %H:%M", &ts) > 0)
        cout << timestamp;
    else {
        cerr << "strftime failed." <<endl;
        return 1;
    }
    return 0;
}

int Measurement::addTimedelta(int deltasec) {
    time_t next = mktime(&ts) + deltasec;
    ts = *localtime(&next);
    return 0;
}

int Measurement::getVoltage(void) {
    int i;
    unsigned int voltcode[2] = {0,0};
    for (i=0;i<=1;i++) {
        voltcode[i] = static_cast<unsigned int>(*buffer & 0xFF);
        buffer++;
    }
    unsigned int volt = ( voltcode[0] << 8 | voltcode[1] );
    voltage = (float)volt/10;

    if (voltage > 108.0 && voltage < 300.0) 
        cout << "\t" << voltage; 
    else {
        cerr << "\ninvalid voltage at " << hex << &buffer << endl;
        return 1;
    }
    return 0;
}

int Measurement::getCurrent(void) {
    int i;
    unsigned int currcode[2] = {0,0};
    for (i=0;i<=1;i++) {
        currcode[i] = static_cast<unsigned int>(*buffer & 0xFF);
        buffer++;
    }
    unsigned int curr = ( currcode[0] << 8 | currcode[1] );
    current = (float)curr/1000; 
    
    if (current >= 0.0)
        cout << "\t" << current;
    else {
        cerr << "\ninvalid current at " << hex << &buffer << endl;
        return 1;
    }
    return 0;
}

int Measurement::getPF(void) {
    unsigned int pf = 0;
    pf = static_cast<unsigned int>(*buffer & 0xFF);
    buffer++;
    cosphi = (float)pf/100;
    if (cosphi >= 0.0 && cosphi <= 1.0)
        cout << "\t" << cosphi;
    else {
        cerr << "\ninvalid power factor at " << hex << &buffer << endl;
        return 1;
    }
    return 0;
}

void Measurement::saveEntry(void) {
}

int Measurement::getBuffer(char* filename) {
    ifstream inputfile;
    ifstream::pos_type size;
    // alternative: int size with typecast (int)

    inputfile.open(filename,ios::in | ios::binary | ios::ate);
    if (inputfile.good()) {
        cout << "inputfile exists." << endl;
        size = inputfile.tellg();
        buffer = new char[size];
        inputfile.seekg (0, ios::beg);
        inputfile.read (buffer, size);
        inputfile.close();
        return 0;
    }
    else {
        cerr << "reading file failed." <<endl;
        return 1;
    }
}

bool Measurement::endCriteria(void) {
    char* preview = new char[4];
    memcpy(preview, buffer, 4);
    unsigned int checkcode[4] = {0,0,0,0};
    for (int i=0;i<4;i++) {
        checkcode[i] = static_cast<unsigned int>(*preview & 0xFF);
        preview++;
    }
    unsigned int eof = (checkcode[0] << 24) | (checkcode[1] << 16) | (checkcode[2] << 8) | checkcode[3]; 
    if (eof == 0xFFFFFFFF)
        return true;
    else
        return false;
}

char* Measurement::buffer; 
struct tm Measurement::ts;

int main(int argc, char* argv[]) {
    
    char* filename[sizeof(&argv[1])];
    *filename = argv[1];
    
    bool finish = false;
    Measurement entry0;
    entry0.getBuffer(*filename);
    entry0.firstStamp();

    while (finish == false) {
        finish = entry0.endCriteria();
        entry0.getVoltage();
        entry0.getCurrent();
        entry0.getPF();
        cout << endl;
        entry0.addTimedelta(60);
        entry0.getTimestamp();
    }
return 0;
}
