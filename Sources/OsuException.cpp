#include "OsuException.hpp"

#include <string>

namespace Osu {

    OsuException::OsuException(const std::string &description)
    : Desc(description) {}

    const std::string &OsuException::Description() const {
        return Desc;
    }

}
