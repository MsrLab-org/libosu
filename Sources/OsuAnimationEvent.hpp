#pragma once
#ifndef LIBOSU_OSU_ANIMATION_EVENT_HPP_INCLUDED
#define LIBOSU_OSU_ANIMATION_EVENT_HPP_INCLUDED

#include <cstdint>
#include <string>

#include "OsuSpriteEvent.hpp"

namespace Osu {

    enum class OsuAnimationEventLoopType: uint8_t {
        Forever = 0,
        Once = 1
    };

    class OsuAnimationEvent: OsuSpriteEvent {
    public:
        OsuAnimationEvent() = default;
    public:
        virtual std::string StringValue() const;
    public:
        uint32_t FrameCount;
        uint32_t FrameDelay;
        OsuAnimationEventLoopType LoopType;
    };

}

#endif // !LIBOSU_OSU_ANIMATION_EVENT_HPP_INCLUDED
