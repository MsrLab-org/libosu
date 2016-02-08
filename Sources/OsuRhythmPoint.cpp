#include "OsuRhythmPoint.hpp"

#include <cstdint>

namespace Osu {

    OsuRhythmPoint::OsuRhythmPoint(uint16_t x, uint16_t y)
    : X(x), Y(y) {}

    OsuRhythmPoint::OsuRhythmPoint(uint16_t x, uint16_t y, OsuHitSound hitSound)
    : X(x), Y(y), HitSound(hitSound) {}

    uint8_t OsuRhythmPoint::ManiaColumn(const uint8_t &keyCount) const {
        return static_cast<uint8_t>(X * keyCount / 512);
    }

    void OsuRhythmPoint::SetManiaColomn(const uint8_t &column, const uint8_t &keyCount) {
        X = static_cast<uint16_t>((static_cast<double>(column) + 0.5) * 512 / keyCount);
    }

}
