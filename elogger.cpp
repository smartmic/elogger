// elogger.cpp
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <ctime>

#define N 18
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

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
        time_t t;
        struct tm ts;
        char timestamp[N];
        double voltage;
        double current;
        double cosphi;
    public:
        Measurement();
        ~Measurement();
        int firstStamp(char* buffer);
        int getVoltage(char* buffer);
        int getCurrent(char* buffer);
        int getPF(char* buffer);
        void saveEntry(void);
};

Measurement::Measurement() {
}

Measurement::~Measurement() {
}

int Measurement::firstStamp(char* buffer) {
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
        return EXIT_FAILURE;
    }
    getVoltage(buffer);


    return EXIT_SUCCESS;
}

int Measurement::getVoltage(char* buffer) {
    int i;
    unsigned int voltcode[2] = {0,0};
    for (i=0;i<=1;i++) {
        voltcode[i] = static_cast<int>(*buffer);
        buffer++;
    }
    unsigned int volt = ( voltcode[0] << 8 | voltcode[1] );
    cout << " " << (float)volt/10 ; 
    getCurrent(buffer);
    return EXIT_SUCCESS;
}

int Measurement::getCurrent(char* buffer) {
    int i;
    unsigned int currcode[2] = {0,0};
    for (i=0;i<=1;i++) {
        currcode[i] = static_cast<int>(*buffer);
        buffer++;
    }
    unsigned int curr = ( currcode[0] << 8 | currcode[1] );
    cout << " " << (float)curr/1000;
    getPF(buffer);
    return EXIT_SUCCESS;
}

int Measurement::getPF(char* buffer) {
    unsigned int pf = 0;
    pf = static_cast<int>(*buffer);
    buffer++;
    cout << " " << (float)pf/100;
    return EXIT_SUCCESS;
}

void Measurement::saveEntry(void) {
}

int main(int argc, char* argv[]) {
    
    char* filename[sizeof(&argv[1])];
    *filename = argv[1];
    
    //char logfile[] = "file.log";
    
    ifstream inputfile;
    ifstream::pos_type size;
    // alternative: int size with typecast (int)
    char* buffer;

    inputfile.open(*filename,ios::in | ios::binary | ios::ate);
    if (inputfile.good()) {
        cout << "inputfile exists." << endl;
        size = inputfile.tellg();
        buffer = new char[size];
        inputfile.seekg (0, ios::beg);
        inputfile.read (buffer, size);
        inputfile.close();

        Measurement entry0;
        entry0.firstStamp(buffer);
        delete []buffer;
    }
    else
        cout << "inputfile does not exist!" << endl;
    return EXIT_SUCCESS;
}

