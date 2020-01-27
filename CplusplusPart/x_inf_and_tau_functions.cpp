#include "x_inf_and_tau_functions.h"


double fs_neuron::alpha_m(double V) {
    double x = -0.1 * (V + 33);
    if (x == 0) {
        x = 0.000000001;
    };

    double alpha = x / (exp(x) - 1);
    return alpha;
};


double fs_neuron::beta_m(double V) {
    double beta = 4 * exp( -(V + 58) / 18);
    return beta;
}


double fs_neuron::m_inf(double V) {
    double alpha = alpha_m(V);
    double beta = beta_m(V);
    double m_inf = alpha / (alpha + beta);
    return m_inf;
};


double fs_neuron::m_tau(double) {
        return NAN;
};

///////////////////////////////////////////////////////

double fs_neuron::alpha_h(double V) {
    double fi = 10;
    double alpha = fi * 0.07 * exp(-(V + 51) / 10);
    return alpha;
};


double fs_neuron::beta_h(double V) {
    double fi = 10;
    double beta = fi / ( exp(-0.1*(V + 21)) + 1) ;
    return beta;
};


double fs_neuron::h_inf(double V) {
    double alpha = alpha_h(V);
    double beta = beta_h(V);
    double h_inf = alpha / (alpha + beta);
    return h_inf;
};


double fs_neuron::h_tau(double V) {
    double alpha = alpha_h(V);
    double beta = beta_h(V);
    double h_tau = 1 / (alpha + beta);
    return h_tau;
};

/////////////////////////////////////////////////////////////////////

double fs_neuron::alpha_n(double V) {
    double fi = 10;
    double x = -0.1 * (V + 38);
    if ( x==0 ) {
        x = 0.00000000001;
    };
    double alpha = fi * 0.1 * x / (exp(x) - 1);
    return alpha;
};

double fs_neuron::beta_n(double V) {
    double fi = 10;
    return (fi * 0.125 * exp(-(V + 48) / 80));
};


double fs_neuron::n_inf(double V) {
    double alpha = alpha_n(V);
    double beta = beta_n(V);
    double n_inf = alpha / (alpha + beta);
    return n_inf;
};


double fs_neuron::n_tau(double V) {
    double alpha = alpha_n(V);
    double beta = beta_n(V);
    double n_tau = 1 / (alpha + beta);
    return n_tau;
};

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


double ca1_neuron_params::alpha_m(double V) {
    double x = 13.1 - V;
    if (x == 0) {
        x = 0.000001;
    };
    double alpha = 0.32 * x / (exp(0.25 * x) - 1);
    return alpha;
};


double ca1_neuron_params::beta_m(double V){
    double x = V - 40.1;
    if (x == 0) {
        x = 0.00001;
    };
    double beta = 0.28 * x / (exp(0.2 * x) - 1);
    return beta;
};

double ca1_neuron_params::m_inf(double V) {
    double alpha = alpha_m(V);
    double beta = beta_m(V);
    double m_inf = alpha / (alpha + beta);
    return m_inf;
};


double ca1_neuron_params::m_tau(double) {
        return NAN;
};




double ca1_neuron_params::alpha_h(double V) {
    double alpha = 0.128 * exp((17 - V) / 18);
    return alpha;
};

double ca1_neuron_params::beta_h(double V){
    double x = 40 - V;
    if (x == 0) {
        x = 0.00001;
    };
    double beta = 4 / (exp(0.2 * x) + 1);
    return beta;
};


double ca1_neuron_params::h_inf(double V) {
    double alpha = alpha_h(V);
    double beta = beta_h(V);
    double h_inf = alpha / (alpha + beta);
    return h_inf;
};


double ca1_neuron_params::h_tau(double V) {
    double alpha = alpha_h(V);
    double beta = beta_h(V);
    double h_tau = 1 / (alpha + beta);
    return h_tau;
};



double ca1_neuron_params::alpha_n(double V) {
    double x = 35.1 - V;
    if (x == 0) {
        x = 0.00001;
    };
    double alpha = 0.016 * x / (exp(0.2 * x) - 1);
    return alpha;
};


double ca1_neuron_params::beta_n(double V) {
    double beta = 0.25 * exp(0.5 - 0.025 * V);
    return beta;
};


double ca1_neuron_params::n_inf(double V) {
    double alpha = alpha_n(V);
    double beta = beta_n(V);
    double n_inf = alpha / (alpha + beta);
    return n_inf;
};


double ca1_neuron_params::n_tau(double V) {
    double alpha = alpha_n(V);
    double beta = beta_n(V);
    double n_tau = 1 / (alpha + beta);
    return n_tau;
};

double ca1_neuron_params::alpha_s(double V) {
    double x = V - 65;
    double alpha = 1.6 / (1 + exp(-0.072 * x));
    return alpha;
};

double ca1_neuron_params::beta_s(double V) {
    double x = V - 51.1;
    if (x == 0) {
     double x = 0.00001;
    };
    double beta = 0.02 * x / (exp(0.2 * x) - 1);
    return beta;
};

double ca1_neuron_params::s_inf(double V) {
    double alpha = alpha_s(V);
    double beta = beta_s(V);
    double s_inf = alpha / (alpha + beta);
    return s_inf;
};


double ca1_neuron_params::s_tau(double V) {
    double alpha = alpha_s(V);
    double beta = beta_s(V);
    double s_tau = 1 / (alpha + beta);
    return s_tau;
};


double ca1_neuron_params::alpha_c(double V) {
    double alpha;
    if(V > 50) {
        alpha = 2 * exp((6.5 - V) / 27);
    } else {
        alpha = exp( ((V - 10)/11) - ((V - 6.5) / 27) ) / 18.975;
    }
    return alpha;
};



double ca1_neuron_params::beta_c(double V) {
    double beta;
    if (V > 0) {
        beta = 0;
    } else {
        beta = 2 * exp((6.5 - V) / 27) - ca1_neuron_params::alpha_c(V);
    };
    return beta;
};



double ca1_neuron_params::c_inf(double V) {
    double alpha = alpha_c(V);
    double beta = beta_c(V);
    double c_inf = alpha / (alpha + beta);
    return c_inf;
};


double ca1_neuron_params::c_tau(double V) {
    double alpha = alpha_c(V);
    double beta = beta_c(V);
    double c_tau = 1 / (alpha + beta);
    return c_tau;
};


double ca1_neuron_params::alpha_q(double CCa) {
    // double CCa = 0.0001; // !!!!!!!
    double alpha = 0.00002 * CCa;
    if (alpha > 0.01) {
        alpha = 0.01;
    };
    return alpha;
};

double ca1_neuron_params::beta_q(double CCa) {
    return 0.001;
};

double ca1_neuron_params::q_inf(double CCa) {
    double alpha = alpha_q(CCa);
    double beta = beta_q(CCa);
    double q_inf = alpha / (alpha + beta);
    return q_inf;
};


double ca1_neuron_params::q_tau(double V) {
    double alpha = alpha_q(V);
    double beta = beta_q(V);
    double q_tau = 1 / (alpha + beta);
    return q_tau;
};
