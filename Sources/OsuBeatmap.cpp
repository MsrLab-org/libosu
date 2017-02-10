#include "OsuBeatmap.hpp"

#include <cstdint>
#include <iostream>

#include "_Detail/OsuBeatmapReader.hpp"
#include "_Detail/OsuBeatmapWriter.hpp"

namespace Osu {

    uint8_t OsuBeatmap::ManiaKeyCount() const {
        return static_cast<uint8_t>(CircleSize);
    }

    std::istream &operator>>(std::istream &in, OsuBeatmap &beatmap) {
        return _Detail::OsuBeatmapReader()(in, beatmap);
    }

    std::ostream &operator<<(std::ostream &out, const OsuBeatmap &beatmap) {
        return _Detail::OsuBeatmapWriter()(out, beatmap);;
    }

    void OsuBeatmap::SetManiaKeyCount(const uint8_t &keyCount) {
        CircleSize = static_cast<double>(keyCount);
    }

}
