#pragma once
#ifndef LIBOSU_OSU_RHYTHM_POINT_HPP_INCLUDED
#define LIBOSU_OSU_RHYTHM_POINT_HPP_INCLUDED

#include <cstdint>
#include <memory>
#include <string>

namespace Osu {

    enum class OsuHitSound: uint8_t {
        None = 0,
        Normal = 1,
        Whistle = 2,
        Finish = 4,
        Clap = 8
    };

    struct OsuRhythmPoint {
    public:
        OsuRhythmPoint() = default;
        OsuRhythmPoint(uint16_t x, uint16_t y);
        OsuRhythmPoint(uint16_t x, uint16_t y, OsuHitSound hitSound);
    public:
        uint8_t ManiaColumn(const uint8_t &keyCount) const;
        void SetManiaColomn(const uint8_t &column, const uint8_t &keyCount);
    public:
        uint16_t X; // [0, 512]
        uint16_t Y; // [0, 384]
        OsuHitSound HitSound = OsuHitSound::None;
        std::shared_ptr<std::string> CustomHitSound = nullptr;
    };

}

#endif // !LIBOSU_OSU_RHYTHM_POINT_HPP_INCLUDED
