#include "OsuException.hpp"

#include <string>

namespace Osu {

    OsuException::OsuException(const std::string &description)
    : _Description(description) {}

    const std::string &OsuException::Description() const {
        return _Description;
    }

}
