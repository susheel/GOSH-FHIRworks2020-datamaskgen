//
// Created by Patrick Wu on 03/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAMASKGEN_IDENTIFIER_HH
#define GOSH_FHIRWORKS2020_DATAMASKGEN_IDENTIFIER_HH

#include <string>
#include <optional>
#include <sstream>

#include "identifier_type.hh"

using namespace std;

class identifier {
public:

    bool operator == (const identifier& i) const {
        return system == i.system && value == i.value;
    }

    string system;
    string value;
    optional<identifier_type> type;

    identifier (string sys, string val) : system(std::move(sys)), value(std::move(val)) {
        if (system == "https://github.com/synthetichealth/synthea") {
            system = "https://github.com/magetron/GOSH-FHIRworks2020-datamaskgen";
            value = "";
        }
    }

    void init_type(const string& text) {
        if (!type.has_value()) {
            type = identifier_type(text);
        } else {
            type -> text = text;
        }
    }

    string jsonify () {
        stringstream ss;
        ss << "{";
        if (type.has_value()) {
            ss << type->jsonify() << ",";
        }
        ss << "\"system\":\"" << system << "\",\"value\":\"" << value <<"\"}";
        return ss.str();
    }

    void add_type_encoding (const string& system, const string& code, const string& display) {
        type->encodings.emplace_back(system, code, display);
    }

};

namespace std {
    template<>
    struct hash<identifier> {
        size_t operator() (const identifier& i) const {
            return std::hash<string>()(i.system) ^ std::hash<string>()(i.value);
        }
    };
}


#endif //GOSH_FHIRWORKS2020_DATAMASKGEN_IDENTIFIER_HH
