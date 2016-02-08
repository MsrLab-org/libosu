#pragma once
#ifndef LIBOSU_OSU_SOUND_EFFECT_EVENT_HPP_INCLUDED
#define LIBOSU_OSU_SOUND_EFFECT_EVENT_HPP_INCLUDED

#include <cstdint>
#include <string>

#include "OsuEvent.hpp"

namespace Osu {

    class OsuSoundEffectEvent: public OsuEvent {
    public:
        OsuSoundEffectEvent() = default;
    public:
        virtual std::string StringValue() const;
    public:
        int32_t Time;
        uint8_t Volume;
    };

}

#endif // !LIBOSU_OSU_SOUND_EFFECT_EVENT_HPP_INCLUDED
