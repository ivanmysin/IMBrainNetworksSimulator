#include "Neuron.h"

Neuron::Neuron(vector <Compartment *> compartments_,  vector <IntercompartmentConnection *>connections_) {
    compartments = compartments_;
    connections = connections_;

    Vth = 0;
    countSp = false;
}


Neuron::Neuron( Compartment * compartment_) {
    compartments.push_back( compartment_);

}

void Neuron::integrate(double dt, double duration) {
    double t = 0;
    while (t < duration) {

        for (int i = 0; i < compartments.size(); i++) {
            compartments[i] -> integrate(dt, dt);
        }

        for (int i = 0; i < connections.size(); i++) {
            connections[i] -> integrate();
        }

        t += dt;
    }

}

double Neuron::get_somaV() {

    double V = compartments[0] -> getV();
    return V;

}


bool Neuron::check_is_fired() {

    double V = compartments[0] -> getV();
    bool isFired;
    if (countSp || V >= Vth) {
        isFired = true;
        countSp = false;
    }

    if (V < Vth) {
        countSp = true;

    }


    return isFired;


}

Neuron::~Neuron()
{
    //dtor
}
