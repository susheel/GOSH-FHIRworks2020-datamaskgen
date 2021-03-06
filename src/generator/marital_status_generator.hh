//
// Created by Patrick Wu on 05/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAMASKGEN_MARITAL_STATUS_GENERATOR_HH
#define GOSH_FHIRWORKS2020_DATAMASKGEN_MARITAL_STATUS_GENERATOR_HH

#include <vector>
#include <unordered_map>
#include <iostream>

#include "../patient/patient.hh"
#include "generator_with_weight.hh"

using namespace std;

class marital_status_generator {
public:
    vector<patient>& patients;
    unordered_map<marital_status, int> marital_lib;
    generator_with_weight<marital_status> marital_gen;


    explicit marital_status_generator (vector<patient>& p) : patients(p) {
        for (const auto& patient : patients)
            if (marital_lib.find(patient.marital_status) != marital_lib.end()) {
                marital_lib[patient.marital_status]++;
            } else {
                marital_lib.insert({patient.marital_status , 1});
            }
        marital_gen = generator_with_weight<marital_status>(marital_lib);
    }

    marital_status generate () {
        return marital_gen.generate();
    }

};

#endif //GOSH_FHIRWORKS2020_DATAMASKGEN_MARITAL_STATUS_GENERATOR_HH
