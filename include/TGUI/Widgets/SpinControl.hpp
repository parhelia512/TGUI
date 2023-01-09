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


#ifndef TGUI_SPIN_CONTROL_HPP
#define TGUI_SPIN_CONTROL_HPP


#include <TGUI/SubwidgetContainer.hpp>
#include <TGUI/Widgets/SpinButton.hpp>
#include <TGUI/Widgets/EditBox.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Spin control widget
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API SpinControl : public SubwidgetContainer
    {
    public:

        using Ptr = std::shared_ptr<SpinControl>; //!< Shared widget pointer
        using ConstPtr = std::shared_ptr<const SpinControl>; //!< Shared constant widget pointer

        static constexpr const char StaticWidgetType[] = "SpinControl"; //!< Type name of the widget


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /// @brief Constructor
        /// @param typeName     Type of the widget
        /// @param initRenderer Should the renderer be initialized? Should be true unless a derived class initializes it.
        /// @see create
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        SpinControl(const char* typeName = StaticWidgetType, bool initRenderer = true);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a new spin button widget
        ///
        /// @param min     The minimum value of the spin control
        /// @param max     The maximum value of the spin control
        /// @param value   Initial value
        /// @param decimal Number of decimal places to display
        /// @param step    Increment value
        ///
        /// @return The new spin control
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD static SpinControl::Ptr create(float min = 0.0f, float max = 10.0f, float value = 0.0f, unsigned int decimal = 0, float step = 1.0f);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Makes a copy of another spin control
        ///
        /// @param SpinCtrl  The other spin control
        ///
        /// @return The new spin control
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD static SpinControl::Ptr copy(const SpinControl::ConstPtr& SpinCtrl);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the renderer of spin buttons part of widget
        /// @return Temporary pointer to the renderer that may be shared with other widgets using the same renderer
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD SpinButtonRenderer* getSpinButtonSharedRenderer();
        TGUI_NODISCARD const SpinButtonRenderer* getSpinButtonSharedRenderer() const;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the renderer of spin buttons part of widget
        /// @return Temporary pointer to the renderer
        /// @warning After calling this function, the widget has its own copy of the renderer and it will no longer be shared.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD SpinButtonRenderer* getSpinButtonRenderer();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the renderer of edit box part of widget
        /// @return Temporary pointer to the renderer that may be shared with other widgets using the same renderer
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD EditBoxRenderer* getSpinTextSharedRenderer();
        TGUI_NODISCARD const EditBoxRenderer* getSpinTextSharedRenderer() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the renderer of edit box part of widget
        /// @return Temporary pointer to the renderer
        /// @warning After calling this function, the widget has its own copy of the renderer and it will no longer be shared.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD EditBoxRenderer* getSpinTextRenderer();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the size of the spin control
        ///
        /// @param size  The new size of the spin control
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSize(const Layout2d& size) override;
        using SubwidgetContainer::setSize;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets a minimum value
        ///
        /// @param minimum  The new minimum value
        ///
        /// When the value is too small then it will be changed to this minimum.
        /// The default minimum value is 0.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setMinimum(float minimum);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the minimum value
        ///
        /// @return The current minimum value
        ///
        /// The default minimum value 0.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD float getMinimum() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets a maximum value
        ///
        /// @param maximum  The new maximum value
        ///
        /// When the value is too big then it will be changed to this maximum.
        /// The default maximum value is 10.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setMaximum(float maximum);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the maximum value
        ///
        /// @return The current maximum value
        ///
        /// The default maximum value 10.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD float getMaximum() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the current value
        ///
        /// @param value  The new value
        /// @return Was the value actually set
        ///
        /// The value can't be smaller than the minimum or bigger than the maximum.
        /// The default value is 0.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool setValue(float value);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the current value
        ///
        /// @return The current value
        ///
        /// The default value is 0.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD float getValue() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes how much the value changes on each arrow press
        /// @param step  The new step size
        /// @pre The step size must be a positive value or 0.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setStep(float step);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the number of positions the thumb advances with each move
        /// @return The current step size
        /// @see setStep
        ///
        /// The default value is 1.0.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD float getStep() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the number of decimal places to display
        /// @param decimalPlaces The new number of decimal places
        ///
        /// The default value is 0, which means that the value has to be an integer.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setDecimalPlaces(unsigned int decimalPlaces);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns  the number of decimal places to display
        /// @return The current number of decimal places
        /// @see setDecimalPlaces
        ///
        /// The default value is 0, which means that the value has to be an integer.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD unsigned int getDecimalPlaces() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the widget
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD Widget::Ptr clone() const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Saves the widget as a tree node in order to save it to a file
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD std::unique_ptr<DataIO::Node> save(SavingRenderersMap& renderers) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Loads the widget from a tree of nodes
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void load(const std::unique_ptr<DataIO::Node>& node, const LoadingRenderersMap& renderers) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Helper function that initializes the widget when constructing a new widget or loading one from a file
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void init();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Checks whether a value lies between the minimum and maximum
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool inRange(const float value) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Updates the text in the edit box
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setString(const tgui::String& str);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    public:

        SignalFloat onValueChange = {"ValueChanged"}; //!< Value of the spin control changed. Optional parameter: new value


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        unsigned int m_decimalPlaces = 0;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private:
        tgui::SpinButton::Ptr m_spinButton = SpinButton::create();
        tgui::EditBox::Ptr m_spinText = EditBox::create();
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_SPIN_CONTROL_HPP
