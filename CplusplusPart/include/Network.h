#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string.h>
#include "../Compartment.h"
#include "../BaseSynapse.h"


using namespace std;

class Network
{
    public:
        Network(){};
        Network(vector <Compartment *> neurons_, vector <Synapse *> synapses_);
        virtual ~Network();
        void integrate (double dt, double duraction);
        void add_neuron(Compartment * neuron);
        void add_synapse(Synapse * synapse);
        // void saveRaster (const char*);
        // vector <double>  getContiniousFiring (int neuronInd, double dt, double duraction);
        // void saveMeanFiring (const char*, vector <int>, vector <int>, double, double);

    protected:
    private:
        // int numberNeurons;                //  number of neurons in model;
        // int numberSynapses;               //  number of synapses in model
        vector <Compartment* > neurons;   // neurons in model
        vector <Synapse* > synapses;      // synapses in model
};

#endif // NETWORK_H
