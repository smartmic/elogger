// elogger.cpp
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <stdlib.h>
#include <ctime>

#define N 18

using namespace std;
 
template <class T>
    string NumberToString ( T Number )
{
    ostringstream ss;
    ss << Number;
    return ss.str();
}



class Measurement {
    private:
        static char* buffer;
        time_t t;
        struct tm ts;
        char timestamp[N];
        float voltage;
        float current;
        float cosphi;
    public:
        Measurement();
        ~Measurement();
        int getBuffer(char* filename);
        int firstStamp(void);
        int getVoltage(void);
        int getCurrent(void);
        int getPF(void);
        void saveEntry(void);
};

Measurement::Measurement() {
}

Measurement::~Measurement() {
}

int Measurement::firstStamp(void) {
    int offset = 3;
    int datecode;
    memset(&ts, 0, sizeof(tm));
    buffer += offset;
    while (offset <= 7) {
            datecode = static_cast<int>(*buffer);
            
            /*
            if (offset == 3) {
                strcpy(timestamp, NumberToString(datecode[offset-3]).c_str());
            }
            else {
                strcat(timestamp, NumberToString(datecode[offset-3]).c_str());
            } 
            */
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
    t = mktime(&ts);
    if (strftime(timestamp, sizeof(timestamp)-1, "%Y-%m-%d %H:%M", &ts) > 0)
        cout << timestamp;
    else {
        cerr << "strftime failed." <<endl;
        exit (EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}

int Measurement::getVoltage(void) {
    int i;
    unsigned int voltcode[2] = {0,0};
    for (i=0;i<=1;i++) {
        voltcode[i] = static_cast<int>(*buffer);
        buffer++;
    }
    unsigned int volt = ( voltcode[0] << 8 | voltcode[1] );
    voltage = (float)volt/10;

    if (voltage > 108.0 && voltage < 252.0) 
        cout << " " << voltage; 
    else {
        cerr << "\ninvalid voltage at " << hex << &buffer << endl;
        exit (EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}

int Measurement::getCurrent(void) {
    int i;
    unsigned int currcode[2] = {0,0};
    for (i=0;i<=1;i++) {
        currcode[i] = static_cast<int>(*buffer);
        buffer++;
    }
    unsigned int curr = ( currcode[0] << 8 | currcode[1] );
    current = (float)curr/1000; 
    
    if (current >= 0.0)
        cout << " " << current;
    else {
        cerr << "\ninvalid current at " << hex << &buffer << endl;
        exit (EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}

int Measurement::getPF(void) {
    unsigned int pf = 0;
    pf = static_cast<int>(*buffer);
    buffer++;
    cosphi = (float)pf/100;
    if (cosphi >= 0.0 && cosphi <= 1.0)
        cout << " " << cosphi;
    else {
        cerr << "\ninvalid power factor at " << hex << &buffer << endl;
        exit (EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
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
        return EXIT_SUCCESS;
    }
    else {
        cerr << "reading file failed." <<endl;
        exit (EXIT_FAILURE);
    }
}

char* Measurement::buffer; 

int main(int argc, char* argv[]) {
    
    char* filename[sizeof(&argv[1])];
    *filename = argv[1];
    
    //char logfile[] = "file.log";
        
    Measurement entry0;
    entry0.getBuffer(*filename);
    entry0.firstStamp();
    entry0.getVoltage();
    entry0.getCurrent();
    entry0.getPF();

    return EXIT_SUCCESS;
}

