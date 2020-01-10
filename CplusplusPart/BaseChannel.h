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

        BaseChannel(double, double, bool, int, vector <double (*)(double)>, vector <double (*)(double)>, vector <double>);
        BaseChannel(double, double);
        ~BaseChannel(){};

        void integrate(double dt, double duration);
        void set_compartment(Compartment * compartment_);
        void init_gates();
        bool get_isCa(){ return isCa; };
        // void set_isCa(bool isCa_);
        double get_current();
        void set_precomp(vector <double> precomp_param);


    protected:
        Compartment* compartment;
        int n_gates;
        double gmax, I, Erev;
        bool isCa, is_pre_comp;
        vector <double> gates, gates_degrees;
        vector <double (*)(double)> get_x_tau;
        vector <double (*)(double)> get_x_inf;

        vector <vector <double> > x_inf_precomputed;
        vector <vector <double> > T_precomputed;
        double Vmin, Vmax, Vstep, dt_precomp;

};



#endif // BASECHANNEL_H_INCLUDED
