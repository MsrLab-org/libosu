#include "OsuSlider.hpp"

#include <cstdint>
#include <sstream>
#include <string>

#include "Detail/Utilities.hpp"

namespace Osu {

    std::string OsuSlider::StringValue() const {
        using namespace _Detail;
        std::stringstream ss;
        ss << ToUnderlyingValue(Style);
        if (Style != OsuSliderStyle::Line) {
            for (const auto &p : AnchorPoints) {
                ss << '|' << PromoteToPrintableIntegerType(p.X)
                    << ':' << PromoteToPrintableIntegerType(p.Y);
            }
        }
        ss << '|' << PromoteToPrintableIntegerType(EndPoint.X)
            << ':' << PromoteToPrintableIntegerType(EndPoint.Y);
        ss << ',' << PromoteToPrintableIntegerType(RepeatCount());
        ss << ',' << PixelLength;
        if (Style != OsuSliderStyle::Line) {
            for (const auto &p : AnchorPoints) {
                ss << PromoteToPrintableIntegerType(ToUnderlyingValue(p.HitSound));
            }
        }
        ss << static_cast<uintmax_t>(EndPoint.HitSound);
        ss << ",0:0|0:0,0:0:0:0:"
            << (StartPoint.CustomHitSound ? *StartPoint.CustomHitSound : "");
        return OsuHitObject::StringValue() + ss.str();
    }

    uint8_t OsuSlider::TypeValue() const {
        return NewCombo ? 6 : 2;
    }

    uint16_t OsuSlider::RepeatCount() const {
        return Style == OsuSliderStyle::Line ? 1 : static_cast<uint16_t>(AnchorPoints.size()) + 1;
    }

}
