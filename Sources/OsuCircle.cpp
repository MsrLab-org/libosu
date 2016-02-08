#include "OsuCircle.hpp"

#include <cstdint>
#include <sstream>

namespace Osu {

    std::string OsuCircle::StringValue() const {
        std::stringstream ss;
        ss << "0:0:0:0:" << (StartPoint.CustomHitSound ? *StartPoint.CustomHitSound : "");
        return OsuHitObject::StringValue() + ss.str();
    }

    uint8_t OsuCircle::TypeValue() const {
        return NewCombo ? 5 : 1;
    }

}