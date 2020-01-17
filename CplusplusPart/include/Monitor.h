#ifndef MONITOR_H
#define MONITOR_H

#include <math.h>
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
// #include "Neuron.h"


using namespace std;


template <typename T>

class Monitor
{
    public:
        Monitor( double (T::*getter_)(),  T * neuron_ ){
            getter = getter_;
            neuron =  neuron_;
            vector <double> kept_vals;
        };
        void keep_val() {
            double val = (neuron->*getter)();
            kept_vals.push_back(val);
        };
        void save2file(string path) {
            ofstream fs;
            fs.open(path, ios::out | ios::binary);
            for (const auto &val : kept_vals) fs.write((char*) &val, sizeof (val));
            fs.close();
        };

        virtual ~Monitor(){};

    protected:
        double (T::*getter)() ;
        T * neuron;
        vector <double> kept_vals;

    private:
};

#endif // MONITOR_H