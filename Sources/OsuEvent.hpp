#pragma once
#ifndef LIBOSU_OSU_EVENT_HPP_INCLUDED
#define LIBOSU_OSU_EVENT_HPP_INCLUDED

#include <cstdint>
#include <string>

namespace Osu {

    enum class OsuEventLayer: uint8_t {
        Background = 0,
        Fail = 1,
        Pass = 2,
        Foreground = 3
    };

    class OsuEvent {
    public:
        OsuEvent() = default;
    public:
        virtual std::string StringValue() const = 0;
    public:
        virtual ~OsuEvent();
    public:
        OsuEventLayer Layer;
        std::string FilePath;
    };

}

#endif // !LIBOSU_OSU_EVENT_HPP_INCLUDED
