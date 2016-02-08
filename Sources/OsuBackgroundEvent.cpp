#include "OsuBackgroundEvent.hpp"

#include <sstream>
#include <string>

namespace Osu {

    std::string OsuBackgroundEvent::StringValue() const {
        std::stringstream ss;
        ss << "0,0,\"" << FilePath << "\",0,0";
        return ss.str();
    }

}
