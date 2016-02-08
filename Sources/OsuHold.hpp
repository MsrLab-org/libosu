#pragma once
#ifndef LIBOSU_OSU_HOLD_HPP_INCLUDED
#define LIBOSU_OSU_HOLD_HPP_INCLUDED

#include <cstdint>
#include <string>

#include "OsuHitObject.hpp"

namespace Osu {

    class OsuHold: public OsuHitObject {
    public:
        virtual std::string StringValue() const;
        virtual uint8_t TypeValue() const;
    public:
        int32_t EndTime;
    };

    using OsuManiaLongNote = OsuHold;

}

#endif // !LIBOSU_OSU_HOLD_HPP_INCLUDED
