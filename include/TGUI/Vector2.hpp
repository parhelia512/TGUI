/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2022 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef TGUI_VECTOR2_HPP
#define TGUI_VECTOR2_HPP

#include <TGUI/Config.hpp>
#include <TGUI/String.hpp>

#if TGUI_HAS_WINDOW_BACKEND_SFML
    #include <SFML/System/Vector2.hpp>
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    template <typename T>
    class Vector2
    {
    public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        constexpr Vector2() = default;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Constructor to create from X and Y values
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        constexpr Vector2(T xValue, T yValue) :
            x{xValue},
            y{yValue}
        {
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Constructs the vector from an another Vector2 with a different type
        ///
        /// @param vec  Vector to copy
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template <typename U>
        explicit constexpr Vector2(const Vector2<U>& vec) :
            x{static_cast<T>(vec.x)},
            y{static_cast<T>(vec.y)}
        {
        }

#if TGUI_HAS_WINDOW_BACKEND_SFML
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Copy constructor to create from an sf::Vector2
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        constexpr Vector2(const sf::Vector2<T>& vec) :
            x{vec.x},
            y{vec.y}
        {
        }
#endif

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Constructor to create from a string
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Vector2(const char* str) :
            Vector2{String(str)}
        {
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Constructor to create from a string
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Vector2(String str)
        {
            if (str.empty())
            {
                TGUI_PRINT_WARNING("Failed to parse Vector2. String was empty.");
                return;
            }

            // Remove the brackets around the value
            if (((str.front() == '(') && (str.back() == ')')) || ((str.front() == '{') && (str.back() == '}')))
                str = str.substr(1, str.length() - 2);

            if (str.empty())
            {
                x = 0;
                y = 0;
                return;
            }

            auto commaPos = str.find(',');
            if (commaPos == String::npos)
            {
                TGUI_PRINT_WARNING("Failed to parse Vector2 '" + str + "'. Expected numbers separated with a comma.");
                return;
            }

            x = static_cast<T>(str.substr(0, commaPos).trim().toFloat());
            y = static_cast<T>(str.substr(commaPos + 1).trim().toFloat());
        }

#if TGUI_HAS_WINDOW_BACKEND_SFML
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Converts this object into an sf::Vector2 object
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD operator sf::Vector2<T>() const
        {
            return sf::Vector2<T>{x, y};
        }
#endif

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    public:

        T x = 0; //!< X coordinate of the vector
        T y = 0; //!< Y coordinate of the vector

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Overload of unary operator -
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T>
    constexpr Vector2<T> operator-(const Vector2<T>& right)
    {
        return {-right.x, -right.y};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Overload of binary operator +=
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T>
    constexpr Vector2<T>& operator+=(Vector2<T>& left, const Vector2<T>& right)
    {
        left.x += right.x;
        left.y += right.y;
        return left;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Overload of binary operator -=
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T>
    constexpr Vector2<T>& operator-=(Vector2<T>& left, const Vector2<T>& right)
    {
        left.x -= right.x;
        left.y -= right.y;
        return left;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Overload of binary operator +
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T>
    constexpr Vector2<T> operator+(const Vector2<T>& left, const Vector2<T>& right)
    {
        return {left.x + right.x, left.y + right.y};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Overload of binary operator -
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T>
    constexpr Vector2<T> operator-(const Vector2<T>& left, const Vector2<T>& right)
    {
        return {left.x - right.x, left.y - right.y};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Overload of binary operator *
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T>
    constexpr Vector2<T> operator*(const Vector2<T>& left, float right)
    {
        return {left.x * right, left.y * right};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Overload of binary operator *
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T>
    constexpr Vector2<T> operator*(float left, const Vector2<T>& right)
    {
        return {left * right.x, left * right.y};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Overload of binary operator *=
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T>
    constexpr Vector2<T>& operator*=(Vector2<T>& left, float right)
    {
        left.x *= right;
        left.y *= right;
        return left;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Overload of binary operator /
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T>
    constexpr Vector2<T> operator/(const Vector2<T>& left, float right)
    {
        return {left.x / right, left.y / right};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Overload of binary operator /=
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T>
    constexpr Vector2<T>& operator/=(Vector2<T>& left, float right)
    {
        left.x /= right;
        left.y /= right;
        return left;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Overload of binary operator ==
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T>
    constexpr bool operator==(const Vector2<T>& left, const Vector2<T>& right)
    {
        return (left.x == right.x) && (left.y == right.y);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Overload of binary operator !=
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T>
    constexpr bool operator!=(const Vector2<T>& left, const Vector2<T>& right)
    {
        return !(left == right);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    using Vector2f = Vector2<float>;
    using Vector2u = Vector2<unsigned int>;
    using Vector2i = Vector2<int>;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_VECTOR2_HPP
