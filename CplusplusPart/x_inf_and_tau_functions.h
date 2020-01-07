#ifndef X_INF_AND_TAU_FUNCTIONS,H_INCLUDED
#define X_INF_AND_TAU_FUNCTIONS,H_INCLUDED

#include <math.h>
#include <iostream>

using namespace std;




namespace fs_neuron {


    double alpha_m(double V);

    double beta_m(double V);

    double m_inf(double V);

    double m_tau(double);

    ///////////////////////////////////////////////////////

    double alpha_h(double V);

    double beta_h(double V);

    double h_inf(double V);

    double h_tau(double V);

    /////////////////////////////////////////////////////////////////////

    double alpha_n(double V);

    double beta_n(double V);

    double n_inf(double V);

    double n_tau(double V);

};


namespace ca1_neuron_params {


    double alpha_m(double V);

    double beta_m(double V);

    double m_inf(double V);

    double m_tau(double);

    ////////////////////////////////////////////////////////////////


    double alpha_h(double V);

    double beta_h(double V);

    double h_inf(double V);

    double h_tau(double V);

    //////////////////////////////////////////////////////////////


    double alpha_n(double V);

    double beta_n(double V);

    double n_inf(double V);

    double n_tau(double V);

    ///////////////////////////////////////////////////////////////


    double alpha_s(double V);

    double beta_s(double V);

    double s_inf(double V);

    double s_tau(double V);


    double alpha_c(double V);

    double beta_c(double V);

    double c_inf(double V);

    double c_tau(double V);



    double alpha_q(double CCa);

    double beta_q(double V);

    double q_inf(double V);

    double q_tau(double V);


};

#endif // X_INF_AND_TAU_FUNCTIONS,H_INCLUDED
