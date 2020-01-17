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


class BaseMonitor {

    public:
        BaseMonitor(){};
        virtual ~BaseMonitor(){};

    protected:
        vector <double> kept_vals;
        virtual void keep_val() {};

        void save2file(string path) {
            ofstream fs;
            fs.open(path, ios::out | ios::binary);
            for (const auto &val : kept_vals) fs.write((char*) &val, sizeof (val));
            fs.close();
        };


};


template <typename T>

class Monitor : public BaseMonitor
{
    public:
        Monitor( double (T::*getter_)(),  T * obj_ ){
            getter = getter_;
            obj =  obj_;
            vector <double> kept_vals;
        };
        void keep_val() {
            double val = (obj->*getter)();
            kept_vals.push_back(val);
        };

        virtual ~Monitor(){};

    protected:
        double (T::*getter)() ;
        T * obj;
        // vector <double> kept_vals;

    private:
};

#endif // MONITOR_H
