#pragma once
#ifndef LIBOSU_DETAIL_UTILITIES_HPP_INCLUDED
#define LIBOSU_DETAIL_UTILITIES_HPP_INCLUDED

#include <type_traits>

namespace Osu {
    namespace _Detail {

        inline void FunctionNameHelper() {

#if defined(__GNUC__) || defined(__ICC) && (__ICC >= 600)
#   define LIBOSU_FUNCTION_SIGNATURE __PRETTY_FUNCTION__
#elif defined(__FUNCSIG__)
#   define LIBOSU_FUNCTION_SIGNATURE __FUNCSIG__
#else
#   define LIBOSU_FUNCTION_SIGNATURE "(Unsupported)"
#endif

        }

        template <class T>
        inline std::underlying_type_t<T> ToUnderlyingValue(const T &value) {
            return static_cast<std::underlying_type_t<T>>(value);
        }

        // see https://isocpp.org/wiki/faq/input-output#print-char-or-ptr-as-number
        template <class T>
        inline auto PromoteToPrintableIntegerType(const T &i) -> decltype(+i) {
            return +i;
        }

    }
}

#endif
