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


#ifndef TGUI_SVG_IMAGE_HPP
#define TGUI_SVG_IMAGE_HPP

#include <TGUI/String.hpp>
#include <TGUI/Vector2.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    struct NSVGimage;
    struct NSVGrasterizer;
    class BackendTexture;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @internal
    /// @brief This class is used internally by the Texture class when passing a filename with the .svg extension
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API SvgImage
    {
    public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        SvgImage() = default;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Constructor that loads the svg from a file
        ///
        /// @param filename  Filename of the svg image
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        SvgImage(const String& filename);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Destructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ~SvgImage();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the object stores an svg that was successfully loaded
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD bool isSet() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the width and height values read from the svg
        ///
        /// @return Default size of the image
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD Vector2f getSize() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /// @brief Draws the image to a texture
        ///
        /// @param texture  Texture that will be resized, cleared and drawn on
        /// @param size     Size that the texture should have
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void rasterize(BackendTexture& texture, Vector2u size);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private:
        NSVGimage* m_svg = nullptr;
        NSVGrasterizer* m_rasterizer = nullptr;
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_SVG_IMAGE_HPP

