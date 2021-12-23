#include "IntercompartmentConnection.h"

IntercompartmentConnection::IntercompartmentConnection(Compartment * comp1_, Compartment * comp2_, double g_, double p_) {
    comp1 = comp1_;
    comp2 = comp2_;
    g = g_;
    p = p_;
}


void IntercompartmentConnection::integrate() {

    double V1 = comp1 -> getV();
    double V2 = comp2 -> getV();


    double I1 = (g / p) * (V2 - V1);
    double I2 = ( g / (1 - p)) * (V1 - V2);


    comp1 -> addIsyn(I1);
    comp2 -> addIsyn(I2);


}

IntercompartmentConnection::~IntercompartmentConnection()
{
    //dtor
}
