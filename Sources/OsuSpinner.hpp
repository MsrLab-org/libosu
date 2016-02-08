#pragma once
#ifndef LIBOSU_OSU_SPINNER_HPP_INCLUDED
#define LIBOSU_OSU_SPINNER_HPP_INCLUDED

#include <cstdint>
#include <string>

#include "OsuHitObject.hpp"

namespace Osu {

    class OsuSpinner: public OsuHitObject {
    public:
        virtual std::string StringValue() const;
        virtual uint8_t TypeValue() const;
    public:
        int32_t EndTime;
        uint32_t SpinCount; // ?
    };

}

#endif // !LIBOSU_OSU_SPINNER_HPP_INCLUDED
