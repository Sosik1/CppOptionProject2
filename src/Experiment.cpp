#include "Experiment.hpp"

void Experiment::serialize(std::ostream& out) const {
    out.write(reinterpret_cast<const char*>(observations), sizeof(observations));
}

void Experiment::deserialize(std::istream& in) {
    in.read(reinterpret_cast<char*>(observations), sizeof(observations));
}
