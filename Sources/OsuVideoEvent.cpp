#include "OsuVideoEvent.hpp"

#include <sstream>
#include <string>

#include "_Detail/Utilities.hpp"

namespace Osu {

    std::string OsuVideoEvent::StringValue() const {
        using namespace _Detail;
        std::stringstream ss;
        ss << "Video," << PromoteToPrintableIntegerType(Time)
            << ",\"" << FilePath << '"';
        return ss.str();
    }

}
