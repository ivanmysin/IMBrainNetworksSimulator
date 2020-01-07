#ifndef BASECHANNEL_H_INCLUDED
#define BASECHANNEL_H_INCLUDED
#include <math.h>
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include "Compartment.h"

using namespace std;

class Compartment;

class BaseChannel {

    public:
        BaseChannel(){};

        BaseChannel(double, double, int, vector <double (*)(double)>, vector <double (*)(double)>, vector <double>);
        BaseChannel(double, double);
        ~BaseChannel(){};

        void integrate(double dt, double duration);
        void set_compartment(Compartment * compartment_);
        void init_gates();
        double get_current();


    protected:
        Compartment* compartment;
        int n_gates;
        double gmax, I, Erev;
        vector <double> gates, gates_degrees;
        vector <double (*)(double)> get_x_tau;
        vector <double (*)(double)> get_x_inf;

};



#endif // BASECHANNEL_H_INCLUDED
