#include "OsuSoundEffectEvent.hpp"

#include <sstream>
#include <string>

#include "_Detail/Utilities.hpp"

namespace Osu {

    std::string OsuSoundEffectEvent::StringValue() const {
        using namespace _Detail;
        std::stringstream ss;
        ss << "Sample," << Time << ','
            << PromoteToPrintableIntegerType(ToUnderlyingValue(Layer))
            << ",\"" << FilePath << "\"" << Volume;
        return ss.str();
    }

}
