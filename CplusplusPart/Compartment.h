#ifndef COMPARTMENT_H_INCLUDED
#define COMPARTMENT_H_INCLUDED
#include <math.h>
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include "BaseChannel.h"

using namespace std;

class BaseChannel;


class Compartment {

    public:
        Compartment(){};
        Compartment(vector<double>, vector <BaseChannel *>);
        virtual ~Compartment(){};
        double getV(){return V;};
        void setIext(double Iext_){Iext = Iext_;};
        void addIsyn(double Isyn_){Isyn += Isyn_;};
        vector <double> getVhist(){return Vhist;};
        void integrate(double dt, double duration);  // virtual
        void init_to_inf();

    protected:
        double V, Isyn, Iext, Iext_mean, Iext_std, Capacity;
        vector <BaseChannel *> channels;
        vector <double> Vhist;


};



#endif // COMPARTMENT_H_INCLUDED
