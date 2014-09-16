/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus's Graphical User Interface
// Copyright (C) 2012-2014 Bruno Van de Velde (vdv_b@tgui.eu)
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

#ifndef TGUI_EDIT_BOX_HPP
#define TGUI_EDIT_BOX_HPP


#include <TGUI/ClickableWidget.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    class EditBoxRenderer;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    class TGUI_API EditBox : public ClickableWidget
    {
    public:

        typedef std::shared_ptr<EditBox> Ptr; ///< Shared widget pointer
        typedef std::shared_ptr<const EditBox> ConstPtr; ///< Shared constant widget pointer


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief The text alignment
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        struct Alignment
        {
            /// @brief The text alignment
            enum Alignments
            {
                /// Put the text on the left side (default)
                Left,

                /// Center the text
                Center,

                /// Put the text on the right side (e.g. for numbers)
                Right
            };
        };


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        EditBox();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Virtual destructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ~EditBox() {}


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Creates the edit box
        ///
        /// @param themeFileFilename  Filename of the theme file.
        /// @param section             The section in the theme file to read.
        ///
        /// @throw Exception when the theme file could not be opened.
        /// @throw Exception when the theme file did not contain the requested section with the needed information.
        /// @throw Exception when one of the images, described in the theme file, could not be loaded.
        ///
        /// When an empty string is passed as filename, the built-in white theme will be used.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static EditBox::Ptr create(const std::string& themeFileFilename = "", const std::string& section = "EditBox");


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Makes a copy of another edit box
        ///
        /// @param editBox  The other edit box
        ///
        /// @return The new edit box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static EditBox::Ptr copy(EditBox::ConstPtr editBox);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the renderer, which gives access to functions that determine how the widget is displayed
        ///
        /// @return Reference to the renderer
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::shared_ptr<EditBoxRenderer> getRenderer() const
        {
            return std::static_pointer_cast<EditBoxRenderer>(m_renderer);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the position of the widget
        ///
        /// This function completely overwrites the previous position.
        /// See the move function to apply an offset based on the previous position instead.
        /// The default position of a transformable widget is (0, 0).
        ///
        /// @param position  New position
        ///
        /// @see move, getPosition
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setPosition(const Layout& position) override;
        using Transformable::setPosition;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the size of the edit box.
        ///
        /// @param size  The new size of the edit box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSize(const Layout& size) override;
        using Transformable::setSize;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the text of the editbox.
        ///
        /// @param text  The new text.
        ///
        /// The last characters of the text might be removed in the following situations:
        /// - You have set a character limit and this text contains too much characters.
        /// - You have limited the text width and the text does not fit inside the EditBox.
        ///
        /// @see setMaximumCharacters
        /// @see limitTextWidth
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setText(const sf::String& text);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the text inside the edit box. This text is not affected by the password character.
        ///
        /// @return The text of the edit box.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::String getText() const
        {
            return m_text;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the default text of the editbox. This is the text drawn when the edit box is empty.
        ///
        /// This text is not affected by the password character.
        ///
        /// @param text  The new default text.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setDefaultText(const sf::String& text)
        {
            m_defaultText.setString(text);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the default text of the edit box. This is the text drawn when the edit box is empty.
        ///
        /// This text is not affected by the password character.
        ///
        /// @return The default text of the edit box.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::String getDefaultText() const
        {
            return m_defaultText.getString();
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the text that you currently have selected. This text is not affected by the password character.
        ///
        /// @return The selected text of the edit box.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::String getSelectedText() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the character size of the text.
        ///
        /// @param textSize  The new size of the text.
        ///                  If the size is 0 (default) then the text will be scaled to fit in the edit box.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextSize(unsigned int textSize);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the character size of the text.
        ///
        /// @return The text size.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getTextSize() const
        {
            return m_textFull.getCharacterSize();
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets a password character.
        ///
        /// @param passwordChar  The new password character.
        ///                      If set to 0 then there is no password character.
        ///
        /// When the text width is limited then this function might remove the last characters in the text if they no
        /// longer fit in the EditBox. You can avoid this by setting LimitTextWidth to false (which is the default).
        ///
        /// @see limitTextWidth
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setPasswordCharacter(char passwordChar = '\0');


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the password character.
        ///
        /// @return  The password character that is currently being used.
        ///          When no password character is used then this function returns 0.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        char getPasswordCharacter() const
        {
            return m_passwordChar;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Change the character limit.
        ///
        /// @param maxChars  The new character limit. Set it to 0 to disable the limit.
        ///
        /// This character limit is disabled by default.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setMaximumCharacters(unsigned int maxChars = 0);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the character limit.
        ///
        /// @return The character limit.
        ///         The function will return 0 when there is no limit.
        ///
        /// There is no character limit by default.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getMaximumCharacters() const
        {
            return m_maxChars;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Should the text width be limited or should you be able to type even if the edit box is full?
        ///
        /// @param limitWidth  Should there be a text width limit or not.
        ///
        /// When set to true, you will no longer be able to add text when the edit box is full.
        /// The default value is false.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void limitTextWidth(bool limitWidth);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the blinking caret to after a specific character.
        ///
        /// @param charactersBeforeCaret  The new position.
        ///
        /// Normally you will not need this function.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setCaretPosition(unsigned int charactersBeforeCaret);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief This will change the width of the caret.
        ///
        /// @param width  New width of the caret
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setCaretWidth(unsigned int width);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes whether the edit box accepts all characters or only numeric input.
        ///
        /// @param numbersOnly  Should the edit box only accept numbers?
        ///
        /// By default the edit box accepts all text characters.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setNumbersOnly(bool numbersOnly);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the transparency of the widget.
        ///
        /// @param transparency  The transparency of the widget.
        ///                      0 is completely transparent, while 255 (default) means fully opaque.
        ///
        /// Note that this will only change the transparency of the images. The parts of the widgets that use a color will not
        /// be changed. You must change them yourself by setting the alpha channel of the color.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setTransparency(unsigned char transparency) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void leftMousePressed(float x, float y) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseMoved(float x, float y) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void keyPressed(const sf::Event::KeyEvent& event) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void textEntered(sf::Uint32 Key) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void widgetUnfocused() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Returns the width of the edit box minus the padding.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        float getVisibleEditBoxWidth();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function will search after which character the caret should be placed. It will not change the caret position.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int findCaretPosition(float posX);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Removes the selected characters. This function is called when pressing backspace, delete or a letter while there were
        // some characters selected.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void deleteSelectedCharacters();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Recalculates the position of the texts.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void recalculateTextPositions();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function is called when the widget is added to a container.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void initialize(Container *const container) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the widget
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Widget::Ptr clone() override
        {
            return std::make_shared<EditBox>(*this);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // When the elapsed time has changed then this function is called.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void update() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Draws the widget on the render target.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Defines specific triggers to EditBox.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        enum EditBoxCallbacks
        {
            TextChanged = ClickableWidgetCallbacksCount * 1,       ///< Text changed
            ReturnKeyPressed = ClickableWidgetCallbacksCount * 2,  ///< Return key was pressed
            EditBoxCallbacksCount = ClickableWidgetCallbacksCount * 4
        };


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        // Is the caret visible or not?
        bool          m_caretVisible = true;

        // When this boolean is true then you can no longer add text when the EditBox is full.
        // Changing it to false will allow you to scroll the text (default).
        // You can change the boolean with the limitTextWidth(bool) function.
        bool          m_limitTextWidth = false;

        // The text inside the edit box
        sf::String    m_displayedText;
        sf::String    m_text;

        // This will store the size of the text ( 0 to auto size )
        unsigned int  m_textSize = 0;

        // The text alignment
        Alignment::Alignments m_textAlignment = Alignment::Left;

        // The selection
        unsigned int  m_selChars = 0;
        unsigned int  m_selStart = 0;
        unsigned int  m_selEnd = 0;

        // The password character
        char          m_passwordChar = '\0';

        // The maximum allowed characters.
        // Zero by default, meaning no limit.
        unsigned int  m_maxChars = 0;

        // When the text width is not limited, you can scroll the edit box and only a part will be visible.
        unsigned int  m_textCropPosition = 0;

        // The rectangle behind the selected text
        sf::RectangleShape  m_selectedTextBackground;

        // The blinking caret
        sf::RectangleShape  m_caret;

        // We need three SFML texts to draw our text, and one more for calculations.
        sf::Text m_textBeforeSelection;
        sf::Text m_textSelection;
        sf::Text m_textAfterSelection;
        sf::Text m_textFull;
        sf::Text m_defaultText;

        // Is there a possibility that the user is going to double click?
        bool m_possibleDoubleClick = false;

        bool m_numbersOnly = false;

        friend class EditBoxRenderer;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    };


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    class EditBoxRenderer : public WidgetRenderer, public WidgetBorders, public WidgetPadding
    {
    public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Constructor
        ///
        /// @param button  The button that is connected to the renderer
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        EditBoxRenderer(EditBox* editBox) : m_editBox{editBox} {}


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Dynamically change a property of the renderer, without even knowing the type of the widget.
        ///
        /// This function should only be used when you don't know the type of the widget.
        /// Otherwise you can make a direct function call to make the wanted change.
        ///
        /// @param property  The property that you would like to change
        /// @param value     The new value that you like to assign to the property
        /// @param rootPath  Path that should be placed in front of any resource filename
        ///
        /// @throw Exception when the property doesn't exist for this widget.
        /// @throw Exception when the value is invalid for this property.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setProperty(std::string property, const std::string& value, const std::string& rootPath = getResourcePath()) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the font of the text.
        ///
        /// When you don't call this function then the global font will be use.
        /// This global font can be changed with the setGlobalFont function from the parent.
        ///
        /// @param font  The new font.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextFont(std::shared_ptr<sf::Font> font);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the padding of the edit box.
        ///
        /// When the text is auto-scaled then it will be drawn within the area defined by the size minus the padding.
        /// The padding is also used to define the clipping area for when the text it too long.
        ///
        /// This padding will be scaled together with the background image.
        /// If there is no background image, or when 9-slice scaling is used, the padding will be exactly what you pass here.
        ///
        /// @param padding  The padding width and height
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setPadding(const Padding& padding) override;
        using WidgetPadding::setPadding;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the text color that will be used inside the edit box.
        ///
        /// @param textColor  The new text color.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextColor(const sf::Color& textColor);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the text color of the selected text that will be used inside the edit box.
        ///
        /// @param selectedTextColor  The new text color.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSelectedTextColor(const sf::Color& selectedTextColor)
        {
            m_editBox->m_textSelection.setColor(selectedTextColor);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the background color of the selected text that will be used inside the edit box.
        ///
        /// @param selectedTextBackgroundColor  The new background color.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSelectedTextBackgroundColor(const sf::Color& selectedTextBackgroundColor)
        {
            m_editBox->m_selectedTextBackground.setFillColor(selectedTextBackgroundColor);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the color of the default text that can optionally be displayed when the edit box is empty.
        ///
        /// @param defaultTextColor  The new default text color.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setDefaultTextColor(const sf::Color& defaultTextColor);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the color of the background.
        ///
        /// @param color  New background color
        ///
        /// This color will overwrite the color for both the normal and hover state.
        ///
        /// Note that this color is ignored when you set an image as background.
        ///
        /// @see setTextColorNormal
        /// @see setTextColorHover
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setBackgroundColor(const sf::Color& color);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the color of the background in the normal state (mouse not on button).
        ///
        /// @param color  New background color
        ///
        /// Note that this color is ignored when you set an image as background.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setBackgroundColorNormal(const sf::Color& color);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the color of the background in the hover state (mouse on button, but not pressed).
        ///
        /// @param color  New background color
        ///
        /// Note that this color is ignored when you set an image as background.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setBackgroundColorHover(const sf::Color& color);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the color that will be used inside the edit box for the blinking caret.
        ///
        /// @param caretColor  The color of the blinking caret
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setCaretColor(const sf::Color& caretColor)
        {
            m_editBox->m_caret.setFillColor(caretColor);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the color of the borders.
        ///
        /// @param color  New border color
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setBorderColor(const sf::Color& color);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Change the image that is displayed when the mouse is not on top of the edit box
        ///
        /// When this image is set, the background color property will be ignored.
        ///
        /// Pass an empty string to unset the image, in this case the background color property will be used again.
        ///
        /// @param filename   Filename of the image to load.
        /// @param partRect   Load only part of the image. Don't pass this parameter if you want to load the full image.
        /// @param middlePart Choose the middle part of the image for 9-slice scaling (relative to the part defined by partRect)
        /// @param repeated   Should the image be repeated or stretched when the size is bigger than the image?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setNormalImage(const std::string& filename,
                            const sf::IntRect& partRect = sf::IntRect(0, 0, 0, 0),
                            const sf::IntRect& middlePart = sf::IntRect(0, 0, 0, 0),
                            bool repeated = false);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Change the image that is displayed when the mouse is located on top of the edit box
        ///
        /// A NormalImage should be loaded for this to work.
        ///
        /// Pass an empty string to unset the image.
        ///
        /// @param filename   Filename of the image to load.
        /// @param partRect   Load only part of the image. Don't pass this parameter if you want to load the full image.
        /// @param middlePart Choose the middle part of the image for 9-slice scaling (relative to the part defined by partRect)
        /// @param repeated   Should the image be repeated or stretched when the size is bigger than the image?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setHoverImage(const std::string& filename,
                           const sf::IntRect& partRect = sf::IntRect(0, 0, 0, 0),
                           const sf::IntRect& middlePart = sf::IntRect(0, 0, 0, 0),
                           bool repeated = false);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Change the image that is drawn on top of the edit box image when the edit box is focused
        ///
        /// A NormalImage should be loaded for this to work.
        ///
        /// Pass an empty string to unset the image.
        ///
        /// @param filename   Filename of the image to load.
        /// @param partRect   Load only part of the image. Don't pass this parameter if you want to load the full image.
        /// @param middlePart Choose the middle part of the image for 9-slice scaling (relative to the part defined by partRect)
        /// @param repeated   Should the image be repeated or stretched when the size is bigger than the image?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setFocusedImage(const std::string& filename,
                             const sf::IntRect& partRect = sf::IntRect(0, 0, 0, 0),
                             const sf::IntRect& middlePart = sf::IntRect(0, 0, 0, 0),
                             bool repeated = false);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Draws the widget on the render target.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Returns the padding, which is possibly scaled with the background image.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Padding getScaledPadding() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the renderer
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual std::shared_ptr<WidgetRenderer> clone(Widget* widget) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        EditBoxRenderer(const EditBoxRenderer&) = default;
        EditBoxRenderer& operator=(const EditBoxRenderer&) = delete;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        EditBox*  m_editBox;

        sf::Color m_borderColor = {0, 0, 0};

        sf::Color m_backgroundColorNormal = {245, 245, 245};
        sf::Color m_backgroundColorHover  = {255, 255, 255};

        Texture   m_textureNormal;
        Texture   m_textureHover;
        Texture   m_textureFocused;

        friend class EditBox;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_EDIT_BOX_HPP
