#include "BaseSynapse.h"


Synapse::Synapse(Compartment* pre_, Compartment* post_, int delay_, const vector <double>& params)
{
    pre = pre_;
    post = post_;
    delay = delay_;
    Erev = params[0];
    gbarS = params[1];
    w = params[2];
    alpha_s = params[3];
    beta_s = params[4];
    teta = params[5];
    K = params[6];
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

double Synapse::get_Vpre(){

    double Vpre; // V of pre neuron

    if (delay == 0) {
         Vpre = pre -> getV();
    } else {
        Vpre = v_delay.front();
        v_delay.pop();
        v_delay.push(post -> getV());
    };

    return Vpre;

};


void Synapse::integrate(double dt, double duraction) {
    double Vpre = get_Vpre(); // V of pre neuron

    if (Vpre < -30 && S < 0.005) {
        S = 0;
        return;
    };

    double Vpost = post -> getV();
    double F = 1 / (1+exp(-(Vpre - teta) / K));
    double S_0 = alpha_s * F/(alpha_s * F + beta_s);
    double tau_s = 1/(alpha_s * F + beta_s);
    S = S_0 -(S_0 - S) * exp(-duraction / tau_s);
    Isyn = w * gbarS * S * (Erev - Vpost);
    post -> addIsyn(Isyn); // Isyn for post neuron
}
