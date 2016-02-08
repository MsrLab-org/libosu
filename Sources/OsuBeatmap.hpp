#pragma once
#ifndef LIBOSU_OSU_BEATMAP_HPP_INCLUDED
#define LIBOSU_OSU_BEATMAP_HPP_INCLUDED

#include <iostream>
#include <cstdint>
#include <cstring>
#include <memory>
#include <vector>

#include "OsuGameMode.hpp"

namespace Osu {

    class OsuEvent;
    struct OsuTimingPoint;
    class OsuHitObject;

    class OsuBeatmap {
    public:
        using SelfType = OsuBeatmap;
    public:
        OsuBeatmap() = default;
    public:
        friend std::istream &operator>>(std::istream &in, SelfType &beatmap);
        friend std::ostream &operator<<(std::ostream &out, const SelfType &beatmap);
    public:
        uint8_t ManiaKeyCount() const;
        void SetManiaKeyCount(const uint8_t &keyCount);
    public:
        // General
        std::string AudioFilename;
        int32_t AudioLeadIn;
        int32_t PreviewTime;
        bool Countdown;
        std::string SampleSet;
        double StackLeniency;
        OsuGameMode Mode;
        bool LetterboxInBreaks;
        bool SpecialStyle;
        bool WidescreenStoryboard;
        // Editor
        std::vector<int32_t> Bookmarks;
        double DistanceSpacing;
        uint32_t BeatDivisor;
        uint32_t GirdSize;
        double TimelineZoom;
        // Metadata
        std::string Title;
        std::string TitleUnicode;
        std::string Artist;
        std::string ArtistUnicode;
        std::string Creator;
        std::string Version;
        std::string Source;
        std::vector<std::string> Tags;
        uint32_t BeatmapId;
        uint32_t BeatmapSetId;
        // Difficulty
        double HPDrainRate;
        double CircleSize; // osu!mania key count
        double OverallDifficulty;
        double ApproachRate;
        double SliderMultiplier;
        double SliderTickRate;
        // Main Data
        std::vector<std::shared_ptr<OsuEvent>> Events;
        std::vector<OsuTimingPoint> TimingPoints;
        std::vector<std::shared_ptr<OsuHitObject>> HitObjects;
    };

}

#endif // !LIBOSU_OSU_BEATMAP_HPP_INCLUDED
