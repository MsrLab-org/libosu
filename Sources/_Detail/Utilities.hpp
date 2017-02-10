#pragma once
#ifndef LIBOSU__DETAIL_UTILITIES_HPP_INCLUDED
#define LIBOSU__DETAIL_UTILITIES_HPP_INCLUDED

#include <algorithm>
#include <cstdint>
#include <sstream>
#include <string>
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

        template <class T>
        T To(const std::string &str) {
            std::stringstream ss;
            ss << str;
            T ret;
            ss >> ret;
            return ret;
        }

        inline intmax_t ToIntMax(const std::string &str) {
            return To<intmax_t>(str);
        }

        inline uintmax_t ToUIntMax(const std::string &str) {
            return To<uintmax_t>(str);
        }

#define LIBOSU_DEFINE_STRING_TO_INTEGER_CONVERTION_METHOD(size)   \
        template <>                                               \
        inline int##size##_t To<int##size##_t>(const std::string &str) { \
            return static_cast<int##size##_t>(ToIntMax(str));     \
        }                                                         \
                                                                  \
        inline int##size##_t ToInt##size(const std::string &str) {       \
            return To<int##size##_t>(str);                        \
        }

        LIBOSU_DEFINE_STRING_TO_INTEGER_CONVERTION_METHOD(8);
        LIBOSU_DEFINE_STRING_TO_INTEGER_CONVERTION_METHOD(16);
        LIBOSU_DEFINE_STRING_TO_INTEGER_CONVERTION_METHOD(32);

#define LIBOSU_DEFINE_STRING_TO_UNSIGNED_INTEGER_CONVERTION_METHOD(size) \
        template <>                                                      \
        inline uint##size##_t To<uint##size##_t>(const std::string &str) {      \
            return static_cast<uint##size##_t>(ToUIntMax(str));          \
        }                                                                \
                                                                         \
        inline uint##size##_t ToUInt##size(const std::string &str) {            \
            return To<uint##size##_t>(str);                              \
        }

        LIBOSU_DEFINE_STRING_TO_UNSIGNED_INTEGER_CONVERTION_METHOD(8);
        LIBOSU_DEFINE_STRING_TO_UNSIGNED_INTEGER_CONVERTION_METHOD(16);
        LIBOSU_DEFINE_STRING_TO_UNSIGNED_INTEGER_CONVERTION_METHOD(32);

        template <class T>
        inline T ToEnum(const std::string &str) {
            return static_cast<T>(To<std::underlying_type_t<T>>(str));
        }

        inline double ToDouble(const std::string &str) {
            return To<double>(str);
        }

        inline double ToFloat(const std::string &str) {
            return To<float>(str);
        }

        inline bool ToBool(const std::string &str) {
            return ToUIntMax(str) != 0;
        }

        inline char ToChar(const std::string &str) {
            return str.front();
        }

    }
}

#endif // !LIBOSU__DETAIL_UTILITIES_HPP_INCLUDED
