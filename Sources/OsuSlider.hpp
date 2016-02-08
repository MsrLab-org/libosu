#pragma once
#ifndef LIBOSU_OSU_SLIDER_HPP_INCLUDED
#define LIBOSU_OSU_SLIDER_HPP_INCLUDED

#include <cstdint>
#include <string>
#include <vector>

#include "OsuHitObject.hpp"
#include "OsuRhythmPoint.hpp"

namespace Osu {

    enum class OsuSliderStyle: char {
        Line = 'L',
        BezierCurve = 'P',
        Polyline = 'B' // Don't ask me why.
    };

    class OsuSlider: public OsuHitObject {
    public:
        virtual std::string StringValue() const;
        virtual uint8_t TypeValue() const;
        uint16_t RepeatCount() const;
    public:
        OsuSliderStyle Style = OsuSliderStyle::Line;
        double PixelLength;
        OsuRhythmPoint EndPoint;
        std::vector<OsuRhythmPoint> AnchorPoints; // Available when Style != Line
    };

}

#endif // !LIBOSU_OSU_SLIDER_HPP_INCLUDED
