#include "BaseSynapse.h"


Synapse::Synapse(Compartment* pre_, Compartment* post_, const vector <double>& params)
{
    pre = pre_;
    post = post_;
    delay = int( params[0] );
    Erev = params[1];
    gbarS = params[2];
    w = params[3];
    alpha_s = params[4];
    beta_s = params[5];
    teta = params[6];
    K = params[7];
    S = 0;
    Isyn = 0;


    for (int i = 0; i < delay; i++) {
        v_delay.push(-90.0);
    }

}

Synapse::~Synapse()
{
    //dtor
}

void Synapse::integrate(double dt, double duraction) {
    double Vpre; // V of pre neuron

    if (delay == 0) {
         Vpre = pre -> getV();
    } else {
        Vpre = v_delay.front();
        v_delay.pop();
        v_delay.push(post -> getV());
    };

    if (Vpre < -30 && S < 0.005) {
        S = 0;
        return;
    };

    double Vpost = post -> getV();
    double F = 1 / (1+exp(-(Vpre - teta) / K));
    double S_0 = alpha_s * F/(alpha_s * F + beta_s);
    double tau_s = 1/(alpha_s * F + beta_s);
    S = S_0 -(S_0 - S) * exp(-duraction / tau_s);
    Isyn = w * gbarS * S * (Vpost - Erev);
    post -> addIsyn(Isyn); // Isyn for post neuron
}
