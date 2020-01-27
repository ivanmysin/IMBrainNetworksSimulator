#include "BaseChannel.h"

vector <vector <double> > BaseChannel::x_inf_precomputed;
vector <vector <double> > BaseChannel::T_precomputed;


vector <double (*)(double)> BaseChannel::get_x_tau;
vector <double (*)(double)> BaseChannel::get_x_inf;

BaseChannel::BaseChannel(double gmax_, double Erev_, bool is_Ca_, vector <double (*)(double)> get_x_tau_, vector <double (*)(double)> get_x_inf_, vector <double> gates_degrees_) {

    gmax = gmax_;
    Erev = Erev_;

    gates_degrees = gates_degrees_;
    n_gates = gates_degrees.size();

    isCa = is_Ca_;
    gates = vector<double>(n_gates);
    idx_of_gates = vector<int>(n_gates);



    for (int i = 0; i < n_gates; i++) {
        bool is_not_find = true;
        double (*x_inf_func)(double) = get_x_inf_[i];
        double (*x_tau_func)(double) = get_x_tau_[i];

        is_useCCainInfTau.push_back(false);
        is_pre_comp.push_back(false);

        for(int j = 0; j < get_x_inf.size(); j++) {

            if ( (x_inf_func == get_x_inf[j]) && (x_tau_func == get_x_tau[j] ) ) {
                idx_of_gates[i] = j;
                is_not_find = false;
                break;
            }
        }

        if (is_not_find) {
            get_x_tau.push_back(x_tau_func);
            get_x_inf.push_back(x_inf_func);
            idx_of_gates[i] = get_x_tau.size() - 1;
        }
    }
    is_ca_sensytive = false;
    I = 0;



};



BaseChannel::BaseChannel(double gmax_, double Erev_) {

    gmax = gmax_;
    Erev = Erev_;
    n_gates = 0;
    I = 0;
    isCa = false;
    is_pre_comp.push_back(false);

}

void BaseChannel::set_precomp(vector <double> precomp_param)  {

    Vmin = precomp_param[0];
    Vmax = precomp_param[1];
    Vstep = precomp_param[2];
    dt_precomp = precomp_param[3];

    for (int i = 0; i < n_gates; i++ ) {
        if (is_useCCainInfTau[i]) {
            continue;
        };

        int idx = idx_of_gates[i];

        if (x_inf_precomputed.size() > idx + 1) {
            continue;
        };

        vector <double> x_inf_vect;
        x_inf_precomputed.push_back(x_inf_vect);

        vector <double> T_vect;
        T_precomputed.push_back(T_vect);
    }

    for (int i = 0; i < n_gates; i++ ) {
        if (is_useCCainInfTau[i]) {
            continue;
        };

        int idx = idx_of_gates[i];

        if ( x_inf_precomputed[idx].size() > 0) {
            continue;
        }

        for (double V = Vmin; V <= Vmax; V += Vstep) {


            double T;
            double x_tau = get_x_tau[idx](V);
            double x_inf = get_x_inf[idx](V);

            if ( isnan( x_tau) ) {
                T = NAN;
            } else {
                T = exp(-dt_precomp / x_tau);
            }

            x_inf_precomputed[idx].push_back(x_inf);
            T_precomputed[idx].push_back(T);
        }
        is_pre_comp[i] = true;
    }


}


void BaseChannel::set_compartment(Compartment * compartment_)  {
    compartment = compartment_;
    this->init_gates();
};



void BaseChannel::init_gates() {

    double V = compartment->getV();

    for (int i = 0; i < n_gates; i++) {
        int idx = idx_of_gates[i];
        double x_inf;
        if (is_useCCainInfTau[i]) {
            double Cca = compartment->get_CCa();
            x_inf = get_x_inf[idx](Cca);
        } else {
            x_inf = get_x_inf[idx](V);
        }
        gates[i] = x_inf;
    };
};



void BaseChannel::integrate(double dt, double duration) {


    double t = 0;
    double V = compartment->getV();

    double g = gmax;

    while (t < duration) {

        for (int i = 0; i < n_gates; i++) {

            double x_tau, x_inf, T;
            int idx = idx_of_gates[i];


            if ( is_pre_comp[i] && (V > Vmin) && (V < Vmax) && (dt == dt_precomp)) {
                int idx_pre =  int( (V - Vmin) / Vstep );
                x_inf = x_inf_precomputed[idx][idx_pre];
                T = T_precomputed[idx][idx_pre];

            } else {

                if (is_useCCainInfTau[i]) {

                    double Cca = compartment->get_CCa();
                    x_tau = get_x_tau[idx](Cca);
                    x_inf = get_x_inf[idx](Cca);

                } else {
                    x_tau = get_x_tau[idx](V);
                    x_inf = get_x_inf[idx](V);
                }
                T = exp(-dt / x_tau);

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



double BaseChannel::get_current() {

    if (is_ca_sensytive) {
        this->changeIbyCa();
    }
    return I;

};


void BaseChannel::changeIbyCa(){
    double CCa = compartment->get_CCa();
    double ca_normolizer = CCa / 250.0;
    if (ca_normolizer < 1) {
        I *= ca_normolizer;
    };
}
