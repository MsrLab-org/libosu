#pragma once
#ifndef LIBOSU_OSU_GAME_MODE_HPP_INCLUDED
#define LIBOSU_OSU_GAME_MODE_HPP_INCLUDED

#include <cstdint>

namespace Osu {

    enum class OsuGameMode: uint8_t {
        Osu = 0,
        Taiko = 1,
        CatchTheBeat = 2,
        OsuMania = 3
    };

}

#endif // !LIBOSU_OSU_GAME_MODE_HPP_INCLUDED
