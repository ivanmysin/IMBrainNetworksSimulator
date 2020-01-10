#include <iostream>
#include <fstream>
#include "Compartment.h"
#include "BaseChannel.h"
#include "Neuron.h"
#include "x_inf_and_tau_functions.h"

using namespace std;


Neuron * get_fs_neuron();

int main() {

    cout << "hello " << endl;

    Neuron * fs_n = get_fs_neuron();
    fs_n -> integrate(0.1, 300);

    return 0;
}


Neuron * get_fs_neuron() {

    vector <BaseChannel *> channels;

    BaseChannel * leak_ch = new BaseChannel(0.1, -65.0);
    channels.push_back(leak_ch);



    vector <double (*)(double)> get_mh_tau;
    vector <double (*)(double)> get_mh_inf;

    get_mh_tau.push_back(&(fs_neuron::m_tau));
    get_mh_tau.push_back(&(fs_neuron::h_tau));



    get_mh_inf.push_back(&(fs_neuron::m_inf));
    get_mh_inf.push_back(&(fs_neuron::h_inf));



    vector <double> mh_gates_degrees;
    mh_gates_degrees.push_back(3.0);
    mh_gates_degrees.push_back(1.0);

    vector <double> precomp_param;
    precomp_param.push_back(-100.0);
    precomp_param.push_back(100.0);
    precomp_param.push_back(0.01);
    precomp_param.push_back(0.1);

    BaseChannel * sodium_ch = new BaseChannel(55.0, 50.0, false, 2, get_mh_tau, get_mh_inf, mh_gates_degrees);
    // sodium_ch -> set_precomp(precomp_param);
    channels.push_back(sodium_ch);

    // set_precomp(vector <double> precomp_param)  {
    // Vmin = precomp_param[0];
    // Vmax = precomp_param[1];
    // Vstep = precomp_param[2];
    // dt_precomp = precomp_param[3];



    vector <double (*)(double)> get_n_tau;
    vector <double (*)(double)> get_n_inf;

    get_n_tau.push_back(&(fs_neuron::n_tau));
    get_n_inf.push_back(&(fs_neuron::n_inf));




    vector <double> n_gates_degrees;
    n_gates_degrees.push_back(4.0);


     // double gmax_, double Erev_, int n_gates_, vector <double (*)(double)> get_x_tau_, vector <double (*)(double)> get_x_inf_, vector <double> gates_degrees
    BaseChannel * potassium_ch = new BaseChannel(8.0, -90.0, false, 1, get_n_tau, get_n_inf, n_gates_degrees);
    // potassium_ch -> set_precomp(precomp_param);
    channels.push_back(potassium_ch);


    vector <double> main_params;
    main_params.push_back(-65.0); // V0
    main_params.push_back(0.5); // Iext_mean
    main_params.push_back(0.0); // Iext_std
    main_params.push_back(1.0); // Capacity


    Compartment * comp = new Compartment(main_params, channels);

    Neuron * neuron = new Neuron(comp);

    return neuron;

};

/*
Neuron * get_soma_compartment() {
    vector <BaseChannel *> channels;

    BaseChannel * leak_ch = new BaseChannel(0.1, -65.0);
    channels.push_back(leak_ch);



    vector <double (*)(double)> get_mh_tau;
    vector <double (*)(double)> get_mh_inf;

    get_mh_tau.push_back(&(fs_neuron::m_tau));
    get_mh_tau.push_back(&(fs_neuron::h_tau));



    get_mh_inf.push_back(&(fs_neuron::m_inf));
    get_mh_inf.push_back(&(fs_neuron::h_inf));



    vector <double> mh_gates_degrees;
    mh_gates_degrees.push_back(3.0);
    mh_gates_degrees.push_back(1.0);



    BaseChannel * sodium_ch = new BaseChannel(55.0, 50.0, false, 2, get_mh_tau, get_mh_inf, mh_gates_degrees);
    channels.push_back(sodium_ch);



    vector <double (*)(double)> get_n_tau;
    vector <double (*)(double)> get_n_inf;

    get_n_tau.push_back(&(fs_neuron::n_tau));
    get_n_inf.push_back(&(fs_neuron::n_inf));




    vector <double> n_gates_degrees;
    n_gates_degrees.push_back(4.0);


     // double gmax_, double Erev_, int n_gates_, vector <double (*)(double)> get_x_tau_, vector <double (*)(double)> get_x_inf_, vector <double> gates_degrees
    BaseChannel * potassium_ch = new BaseChannel(8.0, -90.0, false, 1, get_n_tau, get_n_inf, n_gates_degrees);
    channels.push_back(potassium_ch);


    vector <double> main_params;
    main_params.push_back(-65.0); // V0
    main_params.push_back(0.5); // Iext_mean
    main_params.push_back(0.0); // Iext_std
    main_params.push_back(1.0); // Capacity


    Compartment * comp = new Compartment(main_params, channels);

    Neuron * neuron = new Neuron(comp);

    return neuron;


};
*/
