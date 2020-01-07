#include "Compartment.h"



Compartment::Compartment(vector<double> main_params, vector <BaseChannel *> channels_) {


    V = main_params[0];
    Iext_mean = main_params[1];
    Iext_std = main_params[2];
    Capacity = main_params[3];

    channels = channels_;

    for (int i = 0; i < channels.size(); i++) {
        channels[i] -> set_compartment(this);
    };


    Isyn = 0;
    Iext = 0;

};

void Compartment::init_to_inf(){

    for (int i = 0; i < channels.size(); i++) {

        channels[i] -> init_gates();
    }
};


void Compartment::integrate(double dt, double duration) {


    double t = 0;

    ofstream fs;
    fs.open("potential.bin", ios::out | ios::binary);

    while (t < duration) {


        double I = Iext_mean;

        for (int i = 0; i < channels.size(); i++) {

            channels[i] -> integrate(dt, dt);


            double Itmp = channels[i] -> get_current();

            // cout << Itmp << " ";


            I += Itmp;

        };
        // cout << endl;


        I += Isyn;

        fs.write((char*) &V, sizeof (V));

        V = V + dt * (I / Capacity);
        Isyn = 0;

        t += dt;
    }
    fs.write((char*) &V, sizeof (V));
    cout << V << endl;
    fs.close();

};
