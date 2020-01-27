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

        BaseChannel(double, double, bool, vector <double (*)(double)>, vector <double (*)(double)>, vector <double>);
        BaseChannel(double, double);
        ~BaseChannel(){};

        void integrate(double dt, double duration);
        void set_compartment(Compartment * compartment_);
        void init_gates();
        bool get_isCa(){ return isCa; };
        // void set_isCa(bool isCa_);
        double get_current();
        void set_precomp(vector <double> precomp_param);
        double get_gate(){return gates[0];}; // !!!!!!!

        void set_is_useCCainInfTau_by_idx(int idx, bool is_useCa){is_useCCainInfTau[idx] = is_useCa;};
        void set_ca_sensytive(bool sensitive){is_ca_sensytive = sensitive;};


    protected:
        void changeIbyCa();
        static vector <vector <double> > x_inf_precomputed;
        static vector <vector <double> > T_precomputed;

        static vector <double (*)(double)> get_x_tau;
        static vector <double (*)(double)> get_x_inf;

        Compartment* compartment;
        int n_gates;
        double gmax, I, Erev;
        bool isCa, is_ca_sensytive;
        vector <bool> is_useCCainInfTau, is_pre_comp;
        vector <double> gates, gates_degrees;
        double Vmin, Vmax, Vstep, dt_precomp;
        vector <int> idx_of_gates;

};



#endif // BASECHANNEL_H_INCLUDED
