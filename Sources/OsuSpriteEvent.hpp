#pragma once
#ifndef LIBOSU_OSU_SPRITE_EVENT_HPP_INCLUDED
#define LIBOSU_OSU_SPRITE_EVENT_HPP_INCLUDED

#include <cstdint>
#include <string>

#include "OsuEvent.hpp"

namespace Osu {

    enum class OsuSpriteEventOrigin: uint8_t {
        TopLeft = 0,
        TopCentre = 1,
        TopRight = 2,
        CentreLeft = 3,
        Centre = 4,
        CentreRight = 5,
        BottomLeft = 6,
        BottomCentre = 7,
        BottomRight = 8
    };

    struct OsuSpriteEventPoint {
        float X; // [0, 640]
        float Y; // [0, 480]
    };

    class OsuSpriteEvent: public OsuEvent {
    public:
        OsuSpriteEvent() = default;
    public:
        virtual std::string StringValue() const;
    public:
        OsuSpriteEventOrigin Origin;
        OsuSpriteEventPoint Point;
    };

}

#endif // !LIBOSU_OSU_SPRITE_EVENT_HPP_INCLUDED
