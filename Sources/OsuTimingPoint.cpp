#include "OsuTimingPoint.hpp"

#include <cstdint>
#include <iomanip>
#include <sstream>
#include <string>

#include "Detail/Utilities.hpp"

namespace Osu {

    double OsuTimingPoint::BeatsPerMinute() const {
        return 60000.0 / MillisecondsPerBeat;
    }

    void OsuTimingPoint::SetBeatsPerMinute(const double &value) {
        MillisecondsPerBeat = 60000.0 / value;
    }

    double OsuTimingPoint::Ratio() const {
        return RatioMultipliesMinus100 / -100.0;
    }

    void OsuTimingPoint::SetRatio(const double &value) {
        RatioMultipliesMinus100 = value * -100;
    }

    std::string OsuTimingPoint::StringValue() const {
        using namespace _Detail;
        std::stringstream ss;
        ss << PromoteToPrintableIntegerType(Time) << ','
            << std::setprecision(15) << MillisecondsPerBeat << ','
            << Meter << ','
            << PromoteToPrintableIntegerType(ToUnderlyingValue(SampleType)) << ','
            << PromoteToPrintableIntegerType(SampleSet) << ','
            << PromoteToPrintableIntegerType(Volume) << ','
            << (Inherited ? '0' : '1') << ','
            << (KiaiMode ? '1' : '0');
        return ss.str();
    }

}
