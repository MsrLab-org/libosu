#include "OsuSpinner.hpp"

#include <cstdint>
#include <sstream>
#include <string>

#include "Detail/Utilities.hpp"

namespace Osu {

    std::string OsuSpinner::StringValue() const {
        using namespace _Detail;
        std::stringstream ss;
        ss << PromoteToPrintableIntegerType(EndTime) << ",0:0:0:0:"
            << (StartPoint.CustomHitSound ? *StartPoint.CustomHitSound : "");
        return OsuHitObject::StringValue() + ss.str();
    }

    uint8_t OsuSpinner::TypeValue() const {
        return NewCombo ? 12 : 8;
    }

}
