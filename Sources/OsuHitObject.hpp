#pragma once
#ifndef LIBOSU_OSU_HIT_OBJECT_HPP_INCLUDED
#define LIBOSU_OSU_HIT_OBJECT_HPP_INCLUDED

#include <cstdint>
#include <string>

#include "OsuRhythmPoint.hpp"

namespace Osu {

    class OsuHitObject {
    public:
        OsuHitObject() = default;
    public:
        virtual std::string StringValue() const = 0;
        virtual uint8_t TypeValue() const = 0;
    public:
        virtual ~OsuHitObject() = 0;
    public:
        OsuRhythmPoint StartPoint;
        int32_t StartTime;
        bool NewCombo;
    };

}

#endif // !LIBOSU_OSU_HIT_OBJECT_HPP_INCLUDED
