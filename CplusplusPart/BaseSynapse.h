#ifndef BASESYNAPSE_H_INCLUDED
#define BASESYNAPSE_H_INCLUDED

#include <queue>
#include <iostream>
#include <math.h>
#include <vector>
#include "Compartment.h"

class Compartment;

using namespace std;


class Synapse
{
    public:
        Synapse(){};
        Synapse(Compartment* pre_, Compartment* post_, int, const vector <double>&);
        void setSynapseProperies(char type, double w_, Compartment* pre_, Compartment* post_);
        void integrate (double dt, double duraction);
        virtual ~Synapse();

    protected:
        double get_Vpre();

        int delay;
        queue <double> v_delay;
    private:
        // param of synapse
        double teta;
        double K;
        double alpha_s;
        double beta_s;
        double Erev;
        double gbarS;
        double S;
        double w;
        Compartment* pre; // presynaptic neuron
        Compartment* post; // post synaptic neuron
        double Isyn;
};

#endif // BASESYNAPSE_H_INCLUDED
