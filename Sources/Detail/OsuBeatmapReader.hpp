#pragma once
#ifndef LIBOSU_OSU_BEATMAP_READER_HPP_INCLUDED
#define LIBOSU_OSU_BEATMAP_READER_HPP_INCLUDED

#include <cstdint>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "../OsuBackgroundEvent.hpp"
#include "../OsuBeatmap.hpp"
#include "../OsuCircle.hpp"
#include "../OsuException.hpp"
#include "../OsuHold.hpp"
#include "../OsuSlider.hpp"
#include "../OsuSoundEffectEvent.hpp"
#include "../OsuSpinner.hpp"
#include "../OsuTimingPoint.hpp"
#include "../OsuVideoEvent.hpp"
#include "Utility.hpp"

namespace Osu {
    namespace _Detail {

        struct OsuBeatmapReader {
        private:
            std::pair<std::string, std::string> ParsePropertyLine(const std::string &line) {
                auto index = line.find_first_of(':');
                auto key = line.substr(0, index);
                ++index;
                while (line[index] == ' ') {
                    ++index;
                }
                auto value = line.substr(index);
                return std::make_pair(key, value);
            }
            std::vector<std::string> ParseSymbolSeparatedStringSequence(const std::string &line, const char &symbol) {
                bool inQuotes = false;
                std::vector<size_t> ids;
                for (size_t i = 0; i < line.size(); ++i) {
                    if (line[i] == symbol && !inQuotes) {
                        ids.push_back(i);
                    } else if (line[i] == '"') {
                        inQuotes = !inQuotes;
                    }
                }
                ids.push_back(line.size());
                size_t last = 0;
                std::vector<std::string> ret;
                for (auto &id : ids) {
                    ret.push_back(line.substr(last, id - last));
                    last = id + 1;
                }
                return std::move(ret);
            }
            std::string RemoveQuotes(const std::string &str) {
                if (str.size() >= 2 && str[0] == '"') {
                    return str.substr(1, str.size() - 2);
                }
                return std::move(str);
            }
            bool IsEmpty(const std::string &line) {
                return line.empty();
            }
            bool IsComment(const std::string &line) {
                return line.size() >= 2 && line[0] == '/' && line[1] == '/';
            }
            bool IsSectionTag(const std::string &line) {
                return line.size() >= 2 && line.front() == '[' && line.back() == ']';
            }
            enum Section {
                FileFormat,
                General,
                Editor,
                Metadata,
                Difficulty,
                Events,
                TimingPoints,
                Colours,
                HitObjects
            };
            Section GetSection(const std::string &line) {
                auto str = line.substr(1, line.size() - 2);
                static std::map<std::string, Section> sections = {
                    {"General", General},
                    {"Editor", Editor},
                    {"Metadata", Metadata},
                    {"Difficulty", Difficulty},
                    {"Events", Events},
                    {"TimingPoints", TimingPoints},
                    {"HitObjects", HitObjects}
                };
                return sections[str];
            }
            template <class T>
            T To(const std::string &str) {
                std::stringstream ss;
                ss << str;
                T ret;
                ss >> ret;
                return ret;
            }
            intmax_t ToIntMax(const std::string &str) {
                return To<intmax_t>(str);
            }
            uintmax_t ToUIntMax(const std::string &str) {
                return To<uintmax_t>(str);
            }
            double ToDouble(const std::string &str) {
                return To<double>(str);
            }
            int8_t ToInt8(const std::string &str) {
                return static_cast<int8_t>(ToIntMax(str));
            }
            int16_t ToInt16(const std::string &str) {
                return static_cast<int16_t>(ToIntMax(str));
            }
            int32_t ToInt32(const std::string &str) {
                return static_cast<int32_t>(ToIntMax(str));
            }
            uint8_t ToUInt8(const std::string &str) {
                return static_cast<uint8_t>(ToUIntMax(str));
            }
            uint16_t ToUInt16(const std::string &str) {
                return static_cast<uint16_t>(ToUIntMax(str));
            }
            uint32_t ToUInt32(const std::string &str) {
                return static_cast<uint32_t>(ToUIntMax(str));
            }
            bool ToBool(const std::string &str) {
                return ToUIntMax(str) != 0;
            }
            char ToChar(const std::string &str) {
                return str.front();
            }
        private:
            uint16_t format = 12;
        public:
            std::istream &operator()(std::istream &in, OsuBeatmap &beatmap) throw(OsuException) {
                using namespace std;
                beatmap = OsuBeatmap();
                bool success = true;
                string description = string(LIBOSU_FUNCTION_SIGNATURE) + "Unknown Error";
                string line;
                Section section = FileFormat;
                while (getline(in, line)) {
                    if (IsEmpty(line) || IsComment(line)) {
                        continue;
                    }
                    if (IsSectionTag(line)) {
                        section = GetSection(line);
                        continue;
                    }
                    pair<string, string> p;
                    string key, value;
                    switch (section) {
                    case FileFormat:
                        format = To<uint16_t>(line.substr(17, 2).c_str());
                        break;
                    case General:
                        p = ParsePropertyLine(line);
                        key = p.first;
                        value = p.second;
                        if (key == "AudioFilename") {
                            beatmap.AudioFilename = value;
                        } else if (key == "AudioLeadIn") {
                            beatmap.AudioLeadIn = ToInt32(value);
                        } else if (key == "PreviewTime") {
                            beatmap.PreviewTime = ToInt32(value);
                        } else if (key == "Countdown") {
                            beatmap.Countdown = ToBool(value);
                        } else if (key == "SampleSet") {
                            beatmap.SampleSet = value;
                        } else if (key == "StackLeniency") {
                            beatmap.StackLeniency = ToDouble(value);
                        } else if (key == "Mode") {
                            beatmap.Mode = static_cast<OsuGameMode>(ToUInt8(value));
                        } else if (key == "LetterboxInBreaks") {
                            beatmap.LetterboxInBreaks = ToBool(value);
                        } else if (key == "SpecialStyle") {
                            beatmap.SpecialStyle = ToBool(value);
                        } else if (key == "WidescreenStoryboard") {
                            beatmap.WidescreenStoryboard = ToBool(value);
                        } else {
                            success = false;
                            description = "[General] Unknown key " + key;
                        }
                        break;
                    case Editor:
                        p = ParsePropertyLine(line);
                        key = p.first;
                        value = p.second;
                        if (key == "Bookmarks") {
                            auto strs = ParseSymbolSeparatedStringSequence(value, ',');
                            for (auto str : strs) {
                                beatmap.Bookmarks.push_back(ToInt32(str));
                            }
                        } else if (key == "DistanceSpacing") {
                            beatmap.DistanceSpacing = ToDouble(value);
                        } else if (key == "BeatDivisor") {
                            beatmap.BeatDivisor = ToUInt32(value);
                        } else if (key == "GridSize") {
                            beatmap.GirdSize = ToUInt32(value);
                        } else if (key == "TimelineZoom") {
                            beatmap.TimelineZoom = ToDouble(value);
                        } else {
                            success = false;
                            description = "[Editor] Unknown key " + key;
                        }
                        break;
                    case Metadata:
                        p = ParsePropertyLine(line);
                        key = p.first;
                        value = p.second;
                        if (key == "Title") {
                            beatmap.Title = value;
                        } else if (key == "TitleUnicode") {
                            beatmap.TitleUnicode = value;
                        } else if (key == "Artist") {
                            beatmap.Artist = value;
                        } else if (key == "ArtistUnicode") {
                            beatmap.ArtistUnicode = value;
                        } else if (key == "Creator") {
                            beatmap.Creator = value;
                        } else if (key == "Version") {
                            beatmap.Version = value;
                        } else if (key == "Source") {
                            beatmap.Source = value;
                        } else if (key == "Tags") {
                            beatmap.Tags = ParseSymbolSeparatedStringSequence(value, ' ');
                        } else if (key == "BeatmapID") {
                            beatmap.BeatmapId = ToUInt32(value);
                        } else if (key == "BeatmapSetID") {
                            beatmap.BeatmapSetId = ToUInt32(value);
                        } else {
                            success = false;
                            description = "[Metadata] Unknown key " + key;
                        }
                        break;
                    case Difficulty:
                        p = ParsePropertyLine(line);
                        key = p.first;
                        value = p.second;
                        if (key == "HPDrainRate") {
                            beatmap.HPDrainRate = ToDouble(value);
                        } else if (key == "CircleSize") {
                            beatmap.CircleSize = ToDouble(value);
                        } else if (key == "OverallDifficulty") {
                            beatmap.OverallDifficulty = ToDouble(value);
                        } else if (key == "ApproachRate") {
                            beatmap.ApproachRate = ToDouble(value);
                        } else if (key == "SliderMultiplier") {
                            beatmap.SliderMultiplier = ToDouble(value);
                        } else if (key == "SliderTickRate") {
                            beatmap.SliderTickRate = ToDouble(value);
                        } else {
                            success = false;
                            description = "[Difficulty] Unknown key " + key;
                        }
                        break;
                    case Events: {
                        /// @TODO: Implement all event types.
                        auto strs = ParseSymbolSeparatedStringSequence(line, ',');
                        if (strs.size() < 1) {
                            success = false;
                            description = "[Events] Syntax error";
                            break;
                        }
                        std::shared_ptr<OsuEvent> newEvent;
                        if (strs[0] == "Sample") {
                            if (strs.size() != 5) {
                                success = false;
                                description = "[Events] Sound effect: Syntax error";
                                break;
                            }
                            auto event = make_shared<OsuSoundEffectEvent>();
                            newEvent = event;
                            event->Time = ToInt32(strs[1]);
                            event->Layer = static_cast<OsuEventLayer>(ToUInt8(strs[2]));
                            event->FilePath = RemoveQuotes(strs[3]);
                            event->Volume = ToUInt8(strs[4]);
                        } else if (strs[0] == "Video") {
                            if (strs.size() != 3) {
                                success = false;
                                description = "[Events] Video: Syntax error";
                                break;
                            }
                            auto event = make_shared<OsuVideoEvent>();
                            newEvent = event;
                            event->Time = ToInt32(strs[1]);
                            event->FilePath = RemoveQuotes(strs[2]);
                        } else if (strs[0] == "0") {
                            if (strs.size() != 5) {
                                success = false;
                                description = "[Events] Background: Syntax error";
                                break;
                            }
                            auto event = make_shared<OsuBackgroundEvent>();
                            newEvent = event;
                            event->FilePath = RemoveQuotes(strs[2]);
                        }
                        if (newEvent) {
                            beatmap.Events.push_back(newEvent);
                        }
                        break;
                    }
                    case TimingPoints: {
                        auto strs = ParseSymbolSeparatedStringSequence(line, ',');
                        if (strs.size() != 8) {
                            success = false;
                            description = "[TimingPoints] Syntax error";
                            break;
                        }
                        OsuTimingPoint tp;
                        tp.Time = ToInt32(strs[0]);
                        tp.MillisecondsPerBeat = ToDouble(strs[1]);
                        tp.Meter = ToUInt16(strs[2]);
                        tp.SampleType = static_cast<OsuSampleType>(ToUInt8(strs[3]));
                        tp.SampleSet = ToUInt8(strs[4]);
                        tp.Volume = ToUInt8(strs[5]);
                        tp.Inherited = !ToBool(strs[6]);
                        tp.KiaiMode = ToBool(strs[7]);
                        beatmap.TimingPoints.push_back(tp);
                        break;
                    }
                    case Colours:
                        // To be implemented.
                        break;
                    case HitObjects: {
                        auto strs = ParseSymbolSeparatedStringSequence(line, ',');
                        if (strs.size() < 4) {
                            success = false;
                            description = "[HitObjects] Syntax error";
                            break;
                        }
                        uint8_t type = ToUInt8(strs[3]);
                        auto additions = ParseSymbolSeparatedStringSequence(strs.back(), ':');
                        shared_ptr<OsuHitObject> object = nullptr;
                        switch (type) {
                        case 1:
                        case 5:
                            object = make_shared<OsuCircle>();
                            break;
                        case 2:
                        case 6: {
                            auto slider = make_shared<OsuSlider>();
                            object = slider;
                            auto path = ParseSymbolSeparatedStringSequence(strs[5], '|');
                            slider->Style = static_cast<OsuSliderStyle>(path[0][0]);
                            for (size_t i = 1; i < path.size() - 1; ++i) {
                                auto pos = ParseSymbolSeparatedStringSequence(path[i], ':');
                                slider->AnchorPoints.push_back({ToUInt16(pos[0]), ToUInt16(pos[1])});
                            }
                            auto pos = ParseSymbolSeparatedStringSequence(path.back(), ':');
                            slider->EndPoint = {ToUInt16(pos[0]), ToUInt16(pos[1])};
                            slider->PixelLength = ToDouble(strs[7]);
                            auto hitSounds = ParseSymbolSeparatedStringSequence(strs[8], '|');
                            for (size_t i = 0; i < hitSounds.size() - 1; ++i) {
                                slider->AnchorPoints[i].HitSound = static_cast<OsuHitSound>(ToUInt8(hitSounds[i]));
                            }
                            slider->EndPoint.HitSound = static_cast<OsuHitSound>(ToUInt8(hitSounds.back()));
                            break;
                        }
                        case 8:
                        case 12: {
                            auto spinner = make_shared<OsuSpinner>();
                            object = spinner;
                            spinner->EndTime = ToInt32(strs[5]);
                            break;
                        }
                        case 128:
                        case 132: {
                            auto hold = make_shared<OsuHold>();
                            object = hold;
                            hold->EndTime = ToInt32(additions.front());
                            break;
                        }
                        default:
                            success = false;
                            description = "[HitObjects] Unknown HitObject type: "
                                + to_string(_Detail::PromoteToPrintableIntegerType(type));
                            break;
                        }
                        object->StartPoint.X = ToUInt16(strs[0]);
                        object->StartPoint.Y = ToUInt16(strs[1]);
                        object->StartPoint.HitSound = static_cast<OsuHitSound>(ToUInt8(strs[4]));
                        object->StartTime = ToInt32(strs[2]);
                        object->NewCombo = (type & 4) != 0;
                        if (additions.back() != "0") {
                            object->StartPoint.CustomHitSound = make_shared<string>(additions.back());
                        }
                        beatmap.HitObjects.push_back(object);
                        break;
                    }
                    }
                    if (!success) {
                        break;
                    }
                }
                if (!success) {
                    throw OsuException(description);
                }
                return in;
            }
        };

    }
}

#endif // !LIBOSU_OSU_BEATMAP_READER_HPP_INCLUDED
