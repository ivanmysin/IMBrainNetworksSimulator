#ifndef NEURON_H
#define NEURON_H
#include "../Compartment.h"
#include "IntercompartmentConnection.h"

#include <math.h>
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>


using namespace std;

class Compartment;
class IntercompartmentConnection;



class Neuron
{
    public:
        Neuron(vector <Compartment *>, vector <IntercompartmentConnection *>);
        Neuron( Compartment * );
        double get_somaV();
        Compartment* get_compartmentIdx(int idx) {return compartments[idx];}

        void integrate(double dt, double duration);
        bool check_is_fired();
        virtual ~Neuron();

    protected:
        vector <Compartment *> compartments;
        vector <IntercompartmentConnection *> connections;
        double Vth;
        bool countSp;

    private:
};

#endif // NEURON_H
