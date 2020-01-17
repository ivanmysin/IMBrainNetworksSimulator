/*
#include "Monitor.h"

template <typename T>
Monitor<T>::Monitor( double (T::*getter_)(), T * neuron_)
{
    getter = getter_;
    neuron =  neuron_;
    vector <double> kept_vals;
}

template <typename T>
void Monitor<T>::keep_val() {

    double val = (neuron->*getter)();
    kept_vals.push_back(val);

}

template <typename T>
void Monitor<T>::save2file(string path) {

    ofstream fs;
    fs.open(path, ios::out | ios::binary);
    for (const auto &val : kept_vals) fs.write((char*) &val, sizeof (val));
    fs.close();


}

template <typename T>
Monitor<T>::~Monitor()
{
    //dtor
}
*/
