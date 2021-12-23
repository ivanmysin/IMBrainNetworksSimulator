#ifndef INTERCOMPARTMENTCONNECTION_H
#define INTERCOMPARTMENTCONNECTION_H
#include "Compartment.h"
#include "BaseSynapse.h"



class Compartment;

class IntercompartmentConnection {
    public:
        IntercompartmentConnection(Compartment * comp1_, Compartment * comp2_, double g_, double p_);
        void integrate();
        virtual ~IntercompartmentConnection();

    protected:
        Compartment * comp1;
        Compartment * comp2;
        double g, p;

    private:
};

#endif // INTERCOMPARTMENTCONNECTION_H
