#pragma once
#ifndef LIBOSU_OSU_BACKGROUND_EVENT_HPP_INCLUDED
#define LIBOSU_OSU_BACKGROUND_EVENT_HPP_INCLUDED

#include <string>

#include "OsuEvent.hpp"

namespace Osu {

    class OsuBackgroundEvent: public OsuEvent {
    public:
        OsuBackgroundEvent() = default;
    public:
        virtual std::string StringValue() const;
    };

}

#endif // !LIBOSU_OSU_BACKGROUND_EVENT_HPP_INCLUDED
