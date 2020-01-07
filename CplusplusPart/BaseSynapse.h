#ifndef BASESYNAPSE_H_INCLUDED
#define BASESYNAPSE_H_INCLUDED


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
        Synapse(Compartment* pre_, Compartment* post_, const vector <double>&);
        void setSynapseProperies(char type, double w_, Compartment* pre_, Compartment* post_);
        void integrate (double dt, double duraction);
        virtual ~Synapse();

    protected:
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
