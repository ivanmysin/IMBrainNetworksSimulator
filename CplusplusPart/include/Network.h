#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string.h>
#include "Compartment.h"
#include "Neuron.h"
#include "Monitor.h"
#include "BaseSynapse.h"


using namespace std;

class Network
{
    public:
        Network(){};
        Network(vector <Neuron *> neurons_, vector <Synapse *> synapses_);
        virtual ~Network();
        void integrate (double dt, double duraction);
        void add_neuron(Neuron * neuron);
        void add_synapse(Synapse * synapse);
        void add_monitor(BaseMonitor * monitor);

        Neuron* get_neuronIdx(int idx) {return neurons[idx];}
        Synapse* get_synapseIdx(int idx) {return synapses[idx];}
        BaseMonitor* get_monitorIdx(int idx) {return monitors[idx];}

        // void saveRaster (const char*);
        // vector <double>  getContiniousFiring (int neuronInd, double dt, double duraction);
        // void saveMeanFiring (const char*, vector <int>, vector <int>, double, double);

    protected:
    private:
        // int numberNeurons;             //  number of neurons in model;
        // int numberSynapses;            //  number of synapses in model
        vector <Neuron* > neurons;        // neurons in model
        vector <Synapse* > synapses;      // synapses in model
        vector <BaseMonitor *> monitors;


        vector <int> neurons_ids_fired;
        vector <double> neurons_times_fired;

};

#endif // NETWORK_H
