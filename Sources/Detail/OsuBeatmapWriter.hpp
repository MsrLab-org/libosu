#pragma once
#ifndef LIBOSU_OSU_BEATMAP_WRITER_HPP_INCLUDED
#define LIBOSU_OSU_BEATMAP_WRITER_HPP_INCLUDED

#include <sstream>

#include "../OsuBeatmap.hpp"
#include "Utilities.hpp"

namespace Osu {
    namespace _Detail {

        struct OsuBeatmapWriter {
        private:
        public:
            std::ostream &operator()(std::ostream &out, const OsuBeatmap &beatmap) throw(OsuException) {
                using namespace std;
                out << "osu file format v13" << endl;
                out << endl;
                out << setprecision(2);
                out << "[General]" << endl;
                out << "AudioFilename: " + beatmap.AudioFilename << endl;
                out << "AudioLeadIn: " << PromoteToPrintableIntegerType(beatmap.AudioLeadIn) << endl;
                out << "PreviewTime: " << PromoteToPrintableIntegerType(beatmap.PreviewTime) << endl;
                out << "Countdown: " << PromoteToPrintableIntegerType(beatmap.Countdown) << endl;
                out << "SampleSet: " + beatmap.SampleSet << endl;
                out << "StackLeniency: " << beatmap.StackLeniency << endl;
                out << "Mode: " << PromoteToPrintableIntegerType(ToUnderlyingValue(beatmap.Mode)) << endl;
                out << "LetterboxInBreaks: " << PromoteToPrintableIntegerType(beatmap.LetterboxInBreaks) << endl;
                out << "SpecialStyle: " << PromoteToPrintableIntegerType(beatmap.SpecialStyle) << endl;
                out << "WidescreenStoryboard: " << PromoteToPrintableIntegerType(beatmap.WidescreenStoryboard) << endl;
                out << endl;
                out << "[Editor]" << endl;
                out << "Bookmarks: ";
                for (size_t i = 1; i < beatmap.Bookmarks.size(); ++i) {
                    out << PromoteToPrintableIntegerType(beatmap.Bookmarks[i - 1]) << ',';
                }
                if (beatmap.Bookmarks.size() > 0) {
                    out << PromoteToPrintableIntegerType(beatmap.Bookmarks.back()) << endl;
                }
                out << "DistanceSpacing: " << beatmap.DistanceSpacing << endl;
                out << "BeatDivisor: " << PromoteToPrintableIntegerType(beatmap.BeatDivisor) << endl;
                out << "GridSize: " << PromoteToPrintableIntegerType(beatmap.GirdSize) << endl;
                out << "TimelineZoom: " << beatmap.TimelineZoom << endl;
                out << endl;
                out << "[Metadata]" << endl;
                out << "Title:" << beatmap.Title << endl;
                out << "TitleUnicode:" << beatmap.TitleUnicode << endl;
                out << "Artist:" << beatmap.Artist << endl;
                out << "ArtistUnicode:" << beatmap.ArtistUnicode << endl;
                out << "Creator:" << beatmap.Creator << endl;
                out << "Version:" << beatmap.Version << endl;
                out << "Source:" << beatmap.Source << endl;
                out << "Tags:";
                bool first = true;
                for (const auto &tag : beatmap.Tags) {
                    if (!first) {
                        out << ' ';
                    }
                    first = false;
                    out << tag;
                }
                out << endl;
                out << "BeatmapID:" << PromoteToPrintableIntegerType(beatmap.BeatmapId) << endl;
                out << "BeatmapSetID:" << PromoteToPrintableIntegerType(beatmap.BeatmapSetId) << endl;
                out << endl;
                out << "[Difficulty]" << endl;
                out << "HPDrainRate:" << beatmap.HPDrainRate << endl;
                out << "CircleSize:" << beatmap.CircleSize << endl;
                out << "OverallDifficulty:" << beatmap.OverallDifficulty << endl;
                out << "ApproachRate:" << beatmap.ApproachRate << endl;
                out << "SliderMultiplier:" << beatmap.SliderMultiplier << endl;
                out << "SliderTickRate:" << beatmap.SliderTickRate << endl;
                out << endl;
                out << "[Events]" << endl;
                out << endl;
                out << "[TimingPoints]" << endl;
                for (const auto &p : beatmap.TimingPoints) {
                    out << p.StringValue() << endl;
                }
                out << endl;
                out << "[HitObjects]" << endl;
                for (const auto object : beatmap.HitObjects) {
                    out << object->StringValue() << endl;
                }
                out << endl;
                return out;
            }
        };

    }
}

#endif // !LIBOSU_OSU_BEATMAP_WRITER_HPP_INCLUDED
