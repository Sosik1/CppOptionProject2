#ifndef EXPERIMENT_HPP
#define EXPERIMENT_HPP

#include <iostream>

class Experiment {
public:
    double observations[365];

    void serialize(std::ostream& out) const;
    void deserialize(std::istream& in);
};

#endif
