#include "BaseChannel.h"


BaseChannel::BaseChannel(double gmax_, double Erev_, int n_gates_, vector <double (*)(double)> get_x_tau_, vector <double (*)(double)> get_x_inf_, vector <double> gates_degrees_) {

    gmax = gmax_;
    Erev = Erev_;
    n_gates = n_gates_;

    gates = vector<double>(n_gates);


    get_x_tau = get_x_tau_;


    get_x_inf = get_x_inf_;
    gates_degrees = gates_degrees_;

    I = 0;
};



BaseChannel::BaseChannel(double gmax_, double Erev_) {

    gmax = gmax_;
    Erev = Erev_;
    n_gates = 0;
    I = 0;
}


void BaseChannel::set_compartment(Compartment * compartment_)  {
    compartment = compartment_;
    this->init_gates();
};



void BaseChannel::init_gates() {

    double V = compartment->getV();

    for (int i = 0; i < n_gates; i++) {
         gates[i] = get_x_inf[i](V);
    };
};



void BaseChannel::integrate(double dt, double duration) {


    double t = 0;
    double V = compartment->getV();

    double g = gmax;

    while (t < duration) {

        for (int i = 0; i < n_gates; i++) {

            double x_tau = get_x_tau[i](V);
            double x_inf = get_x_inf[i](V);


            if ( isnan( x_tau) ) {
                gates[i] = x_inf;
            } else {
                gates[i] =  x_inf - ( x_inf - gates[i] ) * exp(-dt / x_tau);
            }

            g *= pow( gates[i], gates_degrees[i] );


        };


        I = g * (Erev - V);



        t += dt;
    };


};



double BaseChannel::get_current() { return I; };
