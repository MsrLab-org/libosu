#pragma once
#ifndef LIBOSU_OSU_EXCEPTION_HPP_INCLUDED
#define LIBOSU_OSU_EXCEPTION_HPP_INCLUDED

#include <string>

namespace Osu {

    class OsuException {
    public:
        OsuException(const std::string &description);
    public:
        const std::string &Description() const;
    private:
        std::string Desc;
    };

}

#endif // !LIBOSU_OSU_EXCEPTION_HPP_INCLUDED
