#pragma once
#ifndef LIBOSU_OSU_TIMING_POINT_HPP_INCLUDED
#define LIBOSU_OSU_TIMING_POINT_HPP_INCLUDED

#include <cstdint>
#include <string>

namespace Osu {

    enum class OsuSampleType: uint8_t {
        Normal = 1,
        Soft = 2,
        Drum = 3
    };

    struct OsuTimingPoint {
    public:
        double BeatsPerMinute() const;
        void SetBeatsPerMinute(const double &value);
        double Ratio() const; // Inherited timing point, the ratio of MillisecondsPerBeat.
        void SetRatio(const double &value); // Inherited timing point, the ratio of MillisecondsPerBeat.
        std::string StringValue() const;
    public:
        int32_t Time;
        union {
            double MillisecondsPerBeat;
            double RatioMultipliesMinus100;
        };
        uint16_t Meter;
        OsuSampleType SampleType;
        uint8_t SampleSet; // Default is 0
        uint8_t Volume; // 0~100
        bool Inherited; // Store with inverse value
        bool KiaiMode;
    };

}

#endif // !LIBOSU_OSU_TIMING_POINT_HPP_INCLUDED
