#include "Compartment.h"



Compartment::Compartment(vector<double> main_params, vector <BaseChannel *> channels_) {


    V = main_params[0];
    Iext_mean = main_params[1];
    Iext_std = main_params[2];
    Capacity = main_params[3];

    channels = channels_;
    is_sim_Ca = false;
    for (int i = 0; i < channels.size(); i++) {
        channels[i] -> set_compartment(this);

        if ( channels[i] -> get_isCa() ) {
            is_sim_Ca = true;
        }
    };


    Isyn = 0;
    Iext = 0;

};


void Compartment::set_params4Cadinamics(vector <double> params_ca) {

    is_sim_Ca = true;

    CCa = params_ca[0];
    sbetaca = params_ca[1];
    sfica = params_ca[2];


}


void Compartment::integrate_cca(double ICa, double dt) {

    double k1 = CCa;
    double k2 = k1 + 0.5 * dt * (-sfica * ICa - k1 * sbetaca);
    double k3 = k2 + 0.5 * dt * (-sfica * ICa - k2 * sbetaca);
    double k4 = k1 + dt * (-sfica * ICa - k1 * sbetaca);
    CCa = (k1 + 2*k2 + 2*k3 + k4) / 6;
}


void Compartment::init_to_inf(){

    for (int i = 0; i < channels.size(); i++) {
        channels[i] -> init_gates();
    };
};


void Compartment::integrate(double dt, double duration) {


    double t = 0;

    // ofstream fs;
    //fs.open("log/potential.bin", ios::out | ios::binary);

    while (t < duration) {


        double I = Iext_mean;
        double Ica = 0.0;

        for (int i = 0; i < channels.size(); i++) {

            channels[i] -> integrate(dt, dt);


            double Ich = channels[i] -> get_current();
            I += Ich;


            if ( channels[i] -> get_isCa() ) {
                Ica +=Ich;
            }


        };
        // cout << endl;


        I += Isyn;

        // fs.write((char*) &V, sizeof (V));

        V = V + dt * (I / Capacity);

        if (is_sim_Ca) {
            this -> integrate_cca(Ica, dt);
        }



        Isyn = 0;

        t += dt;
    }
    // fs.write((char*) &V, sizeof (V));
    // cout << V << endl;
    // fs.close();

};
