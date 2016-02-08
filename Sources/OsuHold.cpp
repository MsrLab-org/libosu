#include "OsuHold.hpp"

#include <cstdint>
#include <sstream>
#include <string>

#include "Detail/Utility.hpp"

namespace Osu {

    std::string OsuHold::StringValue() const {
        using namespace _Detail;
        std::stringstream ss;
        ss << PromoteToPrintableIntegerType(EndTime) << ":0:0:0:0:"
            << (StartPoint.CustomHitSound ? *StartPoint.CustomHitSound : "");
        return OsuHitObject::StringValue() + ss.str();
    }

    uint8_t OsuHold::TypeValue() const {
        return NewCombo ? 132 : 128;
    }

}
