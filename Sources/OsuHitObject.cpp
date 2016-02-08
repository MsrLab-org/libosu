#include "OsuHitObject.hpp"

#include <cstdint>
#include <sstream>
#include <string>

#include "Detail/Utility.hpp"

namespace Osu {

    std::string OsuHitObject::StringValue() const {
        using namespace _Detail;
        std::stringstream ss;
        ss << PromoteToPrintableIntegerType(StartPoint.X) << ','
            << PromoteToPrintableIntegerType(StartPoint.Y) << ','
            << PromoteToPrintableIntegerType(StartTime) << ','
            << PromoteToPrintableIntegerType(TypeValue()) << ','
            << PromoteToPrintableIntegerType(ToUnderlyingValue(StartPoint.HitSound)) << ',';
        return ss.str();
    }

    OsuHitObject::~OsuHitObject() {}

}
