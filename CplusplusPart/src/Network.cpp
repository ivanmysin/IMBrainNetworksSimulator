#include "Network.h"


Network::Network(vector <Neuron *> neurons_, vector <Synapse *> synapses_) {

    neurons = neurons_;
    synapses = synapses_;

}



void Network::add_neuron(Neuron * neuron) {

    neurons.push_back(neuron);

}

void Network::add_synapse(Synapse * synapse) {

    synapses.push_back(synapse);

}

void Network::add_monitor(BaseMonitor * monitor) {

    monitors.push_back(monitor);

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
            bool is_fired = neurons[i]->check_is_fired();
            if (is_fired) {
                neurons_ids_fired.push_back(i);
                neurons_times_fired.push_back(t);
            }
        }

        for (int i = 0; i < synapses.size(); i++) { // integrate all synapses by one time step
            synapses[i]->integrate(dt, dt);
        }

        for (int i = 0; i < monitors.size(); i++) { // save all valus
             monitors[i]->keep_val();
        }

        t += dt;
    }
}
