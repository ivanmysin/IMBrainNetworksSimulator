#include "BaseChannel.h"


BaseChannel::BaseChannel(double gmax_, double Erev_, bool is_Ca_, int n_gates_, vector <double (*)(double)> get_x_tau_, vector <double (*)(double)> get_x_inf_, vector <double> gates_degrees_) {

    gmax = gmax_;
    Erev = Erev_;
    n_gates = n_gates_;

    isCa = is_Ca_;

    gates = vector<double>(n_gates);


    get_x_tau = get_x_tau_;


    get_x_inf = get_x_inf_;
    gates_degrees = gates_degrees_;

    I = 0;
    is_pre_comp = false;
};



BaseChannel::BaseChannel(double gmax_, double Erev_) {

    gmax = gmax_;
    Erev = Erev_;
    n_gates = 0;
    I = 0;
    isCa = false;
    is_pre_comp = false;

}

void BaseChannel::set_precomp(vector <double> precomp_param)  {
    Vmin = precomp_param[0];
    Vmax = precomp_param[1];
    Vstep = precomp_param[2];
    dt_precomp = precomp_param[3];


    for (int i = 0; i < n_gates; i++ ) {

        vector <double> x_inf_vect;
        x_inf_precomputed.push_back(x_inf_vect);

        vector <double> T_vect;
        T_precomputed.push_back(T_vect);
    }





    for (double V = Vmin; V <= Vmax; V += Vstep) {
        for (int i = 0; i < n_gates; i++ ) {
            double T;
            double x_tau = get_x_tau[i](V);
            double x_inf = get_x_inf[i](V);

            if ( isnan( x_tau) ) {
                T = NAN;
            } else {
                T = exp(-dt_precomp / x_tau);
            }

            x_inf_precomputed[i].push_back(x_inf);
            T_precomputed[i].push_back(T);
        }
    }

    is_pre_comp = true;
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

            double x_tau, x_inf, T;


            if ( is_pre_comp && (V > Vmin) && (V < Vmax) && (dt == dt_precomp)) {
                int idx =  int( (V - Vmin) / Vstep );
                x_inf = x_inf_precomputed[i][idx];
                // cout << x_inf << endl;
                T = T_precomputed[i][idx];

            } else {
                x_tau = get_x_tau[i](V);
                x_inf = get_x_inf[i](V);
                T = exp(-dt / x_tau);
                // cout << "Hello from not precomputed" << endl;
            }

            if ( isnan( x_tau) || isnan(T) ) {
                gates[i] = x_inf;
            } else {
                gates[i] =  x_inf - ( x_inf - gates[i] ) * T;
            }

            //cout << gates[i] << endl;

            g *= pow( gates[i], gates_degrees[i] );


        };


        I = g * (Erev - V);



        t += dt;
    };


};



double BaseChannel::get_current() { return I; };
