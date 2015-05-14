// elogger.cpp
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <ctime>

#define N 17
#define EXIT_SUCCESS 0

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
        float getVoltage(char* buffer, int pos);
        void saveEntry(void);
};

Measurement::Measurement() {
}

Measurement::~Measurement() {
}

int Measurement::firstStamp(char* buffer) {
    int offset = 3;
    int datecode;
    buffer += offset;
    while (offset <= 7) {
            datecode = static_cast<int>(*buffer);
            /*
            cout << " " << static_cast<int>(*buffer);
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
    strftime(timestamp, N, "%Y-%m-%d %H:%M", &ts);
    cout << timestamp;

    return EXIT_SUCCESS;
}

float Measurement::getVoltage(char* buffer, int pos) {
    return 1.0;
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
    }
    else
        cout << "inputfile does not exist!" << endl;
    return EXIT_SUCCESS;
}

