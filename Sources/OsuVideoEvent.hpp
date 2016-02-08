#pragma once
#ifndef LIBOSU_OSU_VIDEO_EVENT_HPP_INCLUDED
#define LIBOSU_OSU_VIDEO_EVENT_HPP_INCLUDED

#include <cstdint>
#include <string>

#include "OsuEvent.hpp"

namespace Osu {

    class OsuVideoEvent: public OsuEvent {
    public:
        OsuVideoEvent() = default;
    public:
        virtual std::string StringValue() const;
    public:
        int32_t Time;
    };

}

#endif // !LIBOSU_OSU_VIDEO_EVENT_HPP_INCLUDED
