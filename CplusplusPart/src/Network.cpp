#include "Network.h"


Network::Network(vector <Compartment *> neurons_, vector <Synapse *> synapses_) {

    neurons = neurons_;
    synapses = synapses_;

}



void Network::add_neuron(Compartment * neuron) {

    neurons.push_back(neuron);

}

void Network::add_synapse(Synapse * synapse) {

    synapses.push_back(synapse);

}

/////////////////////////////////////////////////////////////////////////////////
Network::~Network() {
/*
    for (int i=0; i<n; i++) {
        delete neurons[i];
    }
    delete [] neurons;
    for (int i=0; i<numberSynapses; i++) {
        delete synapses[i];
    }
    delete [] synapses;
    */
}
////////////////////////////////////////////////////////////////
// intergrate model
void Network::integrate (double dt, double duration) {

    double t=0;
    while (t < duration) {

        for (int i = 0; i < neurons.size(); i++) { // integrate all neurins by one time step
            neurons[i]->integrate(dt, dt);
            // neurons[i]->checkFired(t);
        }

        for (int i = 0; i < synapses.size(); i++) { // integrate all synapses by one time step
            synapses[i]->integrate(dt, dt);
        }

        t+=dt;
    }
}
