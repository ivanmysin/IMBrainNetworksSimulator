#include <iostream>
#include <fstream>
#include <string>
#include "Compartment.h"
#include "BaseChannel.h"
#include "Neuron.h"
#include "BaseSynapse.h"
#include "Monitor.h"
#include "x_inf_and_tau_functions.h"
#include "Network.h"


using namespace std;

void run_fs_neuron();
Neuron * get_fs_neuron();
Compartment * get_pyr_compartment();

int main() {

    cout << "Hello from simulator!" << endl;
    // run_fs_neuron();


    Network* net = new Network();

    Compartment * soma = get_pyr_compartment();

    BaseMonitor * soma_mon = new Monitor <Compartment> ( &Compartment::getV, soma  ) ;

    Neuron * neuron = new Neuron(soma);

    net->add_neuron(neuron);
    net->add_monitor(soma_mon);

    net->integrate(0.1, 300);


    string path = "./log/potential1.bin";
    soma_mon->save2file(path);

    cout << "Calutations are finished! " << endl;

    return 0;
}



void run_fs_neuron() {


    Network* net = new Network();


    for (int i = 0; i < 2; i++) {
        Neuron * fs_n = get_fs_neuron();
        BaseMonitor * mon = new Monitor <Neuron> ( &Neuron::get_somaV, fs_n  ) ;
        // BaseChannel * ch = fs_n->get_compartmentIdx(0)->get_channelIdx(2);

        // Monitor <BaseChannel> * ch_mon = new Monitor <BaseChannel> (&BaseChannel::get_gate, ch);
        net->add_neuron(fs_n);
        net->add_monitor(mon);
        // net->add_monitor(ch_mon);
    }

    Compartment* pre = net->get_neuronIdx(0)->get_compartmentIdx(0);
    Compartment* post = net->get_neuronIdx(1)->get_compartmentIdx(0);

    vector <double> params = vector <double>();
    params.push_back(0.0); // Erev
    params.push_back(0.005); // gbarS
    params.push_back(10.0); // w
    params.push_back(1.1); // alpha_s
    params.push_back(0.19); // beta_s
    params.push_back(2.0); // teta
    params.push_back(5.0); // K

    Synapse* syn = new Synapse(pre, post, 10, params);
    net->add_synapse(syn);



    net->integrate(0.1, 300);

    BaseMonitor * mon1 = net->get_monitorIdx(0);
    BaseMonitor * mon2 = net->get_monitorIdx(1);





    string path = "./log/potential1.bin";
    mon1->save2file(path);

    path = "./log/potential2.bin";
    mon2->save2file(path);




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


Compartment * get_pyr_compartment() {
    vector <BaseChannel *> channels;

    BaseChannel * leak_ch = new BaseChannel(0.1, 0.0);
    channels.push_back(leak_ch);



    vector <double (*)(double)> get_mh_tau;
    vector <double (*)(double)> get_mh_inf;

    get_mh_tau.push_back(&(ca1_neuron_params::m_tau));
    get_mh_tau.push_back(&(ca1_neuron_params::h_tau));



    get_mh_inf.push_back(&(ca1_neuron_params::m_inf));
    get_mh_inf.push_back(&(ca1_neuron_params::h_inf));



    vector <double> mh_gates_degrees;
    mh_gates_degrees.push_back(2.0);
    mh_gates_degrees.push_back(1.0);



    BaseChannel * sodium_ch = new BaseChannel(30.0, 120.0, false, get_mh_tau, get_mh_inf, mh_gates_degrees);
    channels.push_back(sodium_ch);



    vector <double (*)(double)> get_n_tau;
    vector <double (*)(double)> get_n_inf;

    get_n_tau.push_back(&(ca1_neuron_params::n_tau));
    get_n_inf.push_back(&(ca1_neuron_params::n_inf));




    vector <double> n_gates_degrees;
    n_gates_degrees.push_back(1.0);


     // double gmax_, double Erev_, vector <double (*)(double)> get_x_tau_, vector <double (*)(double)> get_x_inf_, vector <double> gates_degrees
    BaseChannel * potassium_ch_dr = new BaseChannel(17.0, -15.0, false, get_n_tau, get_n_inf, n_gates_degrees);
    channels.push_back(potassium_ch_dr);




    vector <double (*)(double)> get_q_tau;
    vector <double (*)(double)> get_q_inf;

    get_q_tau.push_back(&(ca1_neuron_params::q_tau));
    get_q_inf.push_back(&(ca1_neuron_params::q_inf));

    vector <double> q_gates_degrees;
    q_gates_degrees.push_back(1.0);
    BaseChannel * potassium_ch_ahp = new BaseChannel(0.8, -15.0, false, get_q_tau, get_q_inf, q_gates_degrees);
    potassium_ch_ahp->set_is_useCCainInfTau_by_idx(0, true);
    channels.push_back(potassium_ch_ahp);




    vector <double (*)(double)> get_c_tau;
    vector <double (*)(double)> get_c_inf;

    get_c_tau.push_back(&(ca1_neuron_params::c_tau));
    get_c_inf.push_back(&(ca1_neuron_params::c_inf));

    vector <double> c_gates_degrees;
    c_gates_degrees.push_back(1.0);
    BaseChannel * potassium_ch_c = new BaseChannel(15.0, -15.0, false, get_c_tau, get_c_inf, c_gates_degrees);
    potassium_ch_c->set_ca_sensytive(true);
    channels.push_back(potassium_ch_c);


    vector <double (*)(double)> get_s_tau;
    vector <double (*)(double)> get_s_inf;

    get_s_tau.push_back(&(ca1_neuron_params::s_tau));
    get_s_inf.push_back(&(ca1_neuron_params::s_inf));
    vector <double> s_gates_degrees;
    s_gates_degrees.push_back(2.0);
    BaseChannel * calcium_ch = new BaseChannel(6.0, 140.0, true, get_s_tau, get_s_inf, s_gates_degrees);
    channels.push_back(calcium_ch);

    vector <double> main_params;
    main_params.push_back(0.0); // V0
    main_params.push_back(1.0); // Iext_mean
    main_params.push_back(0.0); // Iext_std
    main_params.push_back(3.0); // Capacity


    Compartment * soma = new Compartment(main_params, channels);


    vector <double> params_ca = {0.05, 0.075, 0.13};
    soma->set_params4Cadinamics(params_ca);


    return soma;


};

