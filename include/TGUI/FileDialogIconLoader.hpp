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

#ifndef TGUI_FILE_DIALOG_ICON_LOADER_HPP
#define TGUI_FILE_DIALOG_ICON_LOADER_HPP

#include <TGUI/Texture.hpp>
#include <TGUI/Filesystem.hpp>
#include <memory>
#include <vector>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @internal
    /// @brief Helper class that loads the icons in the FileDialog widget
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API FileDialogIconLoader
    {
    public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Default virtual destructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ~FileDialogIconLoader() = default;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the shared instance to the loader (and creates it if it didn't exist yet).
        ///
        /// @return Shared icon loader instance
        ///
        /// The caller of this function should call incrementReferenceCount() directly after the first call to this function
        /// and call decrementReferenceCount() when it no longer needs the icon loader. The caller can call this function
        /// multiple times inbetween the incrementReferenceCount and decrementReferenceCount calls.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD static std::shared_ptr<FileDialogIconLoader> createInstance();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Called every frame to check if the background thread has finished
        ///
        /// @return Whether icons are available and retrieveFileIcons can be called
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD virtual bool update();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether this icon loader does something or whether its functions are no-ops
        ///
        /// @return True if the platform supports loading icons
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD virtual bool supportsSystemIcons() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether generic icons (one folder and one file icon) are available
        ///
        /// @brief Returns true when a folder and file icon can be returned
        ///
        /// Generic icons can be shows while waiting for the per-file icons to finish loading
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD virtual bool hasGenericIcons() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the generic file/folder icon, which is used until the file-specific icons are finished loading
        ///
        /// @param file  Information about the file, used to check if a folder or file icon needs to be returned
        ///
        /// @return File or folder icon
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD virtual Texture getGenericFileIcon(const Filesystem::FileInfo& file);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Starts a thread to load the icons for all given files
        ///
        /// @param files  List of files for which icons should be loaded
        ///
        /// If the thread was still running then it will be cancelled.
        /// Once the thread finished, the update() function will return true and retrieveFileIcons() should be called.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void requestFileIcons(const std::vector<Filesystem::FileInfo>& files);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Access the file icons that where loaded in the thread that was started in requestFileIcons()
        ///
        /// @return Loaded icons for all files passed to requestFileIcons
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD virtual std::vector<Texture> retrieveFileIcons();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Protected constructor, the createInstance() function should be used to construct the icon loader
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        FileDialogIconLoader() = default;
    };
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_FILE_DIALOG_ICON_LOADER_HPP
