#pragma once
#ifndef LIBOSU_OSU_CIRCLE_HPP_INCLUDED
#define LIBOSU_OSU_CIRCLE_HPP_INCLUDED

#include <cstdint>
#include <string>

#include "OsuHitObject.hpp"

namespace Osu {

    class OsuCircle: public OsuHitObject {
    public:
        virtual std::string StringValue() const;
        virtual uint8_t TypeValue() const;
    };

    using OsuManiaNote = OsuCircle;

}

#endif // !LIBOSU_OSU_CIRCLE_HPP_INCLUDED
