#include <iostream>
#include <fstream>
#include <string>
#include "Compartment.h"
#include "BaseChannel.h"
#include "Neuron.h"
#include "Monitor.h"
#include "x_inf_and_tau_functions.h"
#include "Network.h"


using namespace std;


Neuron * get_fs_neuron();

int main() {

    cout << "Hello from simulator!" << endl;


    Network* net = new Network();


    // Neuron * fs_n = get_fs_neuron();
    // net->add_neuron(fs_n);

    for (int i=0; i<1; i++) {
        Neuron * fs_n = get_fs_neuron();
        Monitor <Neuron> * mon = new Monitor <Neuron> ( &Neuron::get_somaV, fs_n  ) ;
        net->add_neuron(fs_n);
        net->add_monitor(mon);
    }

    net->integrate(0.1, 300);



/*   Neuron * fs_n2 = get_fs_neuron();

    Monitor <Neuron> * mon1 = new Monitor <Neuron> ( &Neuron::get_somaV, fs_n  ) ;
    Monitor <Neuron> * mon2 = new Monitor <Neuron> ( &Neuron::get_somaV, fs_n2  ) ;

    double t = 0;
    double dt = 0.1;
    double duration = 300;
    while(t < duration) {
        mon1->keep_val();
        mon2->keep_val();
        fs_n -> integrate(dt, dt);
        fs_n2 -> integrate(dt, dt);
        t += dt;
    };
    mon1->keep_val();
    mon2->keep_val();

    string path = "./log/potential.bin";
    mon1->save2file(path);

    path = "./log/potential2.bin";
    mon2->save2file(path);
*/
    cout << "Calutations are finished! " << endl;

    return 0;
}


Neuron* get_fs_neuron() {

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

    BaseChannel * sodium_ch = new BaseChannel(55.0, 50.0, false, get_mh_tau, get_mh_inf, mh_gates_degrees);
    // sodium_ch -> set_precomp(precomp_param);
    channels.push_back(sodium_ch);

    // set_precomp(vector <double> precomp_param)
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
    BaseChannel * potassium_ch = new BaseChannel(8.0, -90.0, false, get_n_tau, get_n_inf, n_gates_degrees);
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
