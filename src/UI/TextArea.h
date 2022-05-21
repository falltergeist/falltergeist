#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include "../Graphics/Color.h"
#include "../Graphics/Font.h"
#include "../Graphics/TextArea.h"
#include "../UI/Base.h"

namespace Falltergeist
{
    namespace UI
    {

    /**
     * Represents a block of text on screen.
     */
    class TextArea : public Falltergeist::UI::Base
    {
        public:
            enum class HorizontalAlign : unsigned
            {
                LEFT = 1,
                CENTER,
                RIGHT,
                JUSTIFY
            };
            enum class VerticalAlign : unsigned
            {
                TOP = 1,
                CENTER,
                BOTTOM,
                JUSTIFY
            };
            /**
             * Creates empty TextArea at the given position.
             */
            TextArea(const Graphics::Point& pos = Graphics::Point());

            /**
             * Creates empty TextArea at the given position.
             */
            TextArea(int x = 0, int y = 0);

            /**
             * Creates TextArea with given text at the given position.
             */
            TextArea(const std::string& text, const Graphics::Point& pos = Graphics::Point());

            /**
             * Creates TextArea with given text at the given position.
             */
            TextArea(const std::string& text, int x, int y);

            /**
             * Creates TextArea as copy of another TextArea, placed at the given position (0,0 by default).
             */
            TextArea(const TextArea& textArea, Graphics::Point pos = Graphics::Point());

            ~TextArea() override;

            /**
             * Current text content.
             */
            std::string text() const;

            /**
             * Replaces text content. Line break character \n is used to span text to multiple lines.
             */
            void setText(const std::string& text);

            /**
             * Appends given string to existing text. Line break character \n is used to span text to multiple lines.
             */
            void appendText(const std::string& text);

            HorizontalAlign horizontalAlign() const;

            void setHorizontalAlign(HorizontalAlign align);

            VerticalAlign verticalAlign() const;

            void setVerticalAlign(VerticalAlign align);

            /**
             * Size of text area. It's either fixed value given to setSize() or previously calculated size.
             */
            const Graphics::Size& size() const override;

            /**
             * Sets fixed size of TextArea. If this is not (0, 0) - calls to size() will always return this value,
             * regardless of actual width/height of TextArea on screen.
             * If wordWrap is also set to true, lines width will be limited to width provided.
             */
            void setSize(const Graphics::Size& size);

            void setWidth(int width);

            void handle(Event::Event* event) override;

            /**
             * Size of actual text content of the text area.
             */
            Graphics::Size textSize();

            /**
             * Actual number of lines contained within TextArea. Will be greater than number of visible lines when overflown.
             */
            int numLines();

            /**
             * Whether Word Wrap is currently enabled or not.
             */
            bool wordWrap() const;

            /**
             * Enables or disabled Word Wrap for this control - automatic splitting of lines when they are longer then size().width().
             */
            void setWordWrap(bool wordWrap);

            /**
             * Top and left text padding.
             */
            const Graphics::Size& paddingTopLeft() const;

            /**
             * Sets top and left text padding, in pixels, relative to TextArea position.
             */
            void setPaddingTopLeft(const Graphics::Size& paddingTopLeft);

            /**
             * Bottom and right text padding.
             */
            const Graphics::Size& paddingBottomRight() const;

            /**
             * Sets bottom and right text padding, ix pixels, relative to TextArea position + size.
             * Has no effect if size is not set.
             */
            void setPaddingBottomRight(const Graphics::Size& paddingBottomRight);

            /**
             * Sets both top-left and bottom-right padding.
             */
            void setPadding(const Graphics::Size& topLeft, const Graphics::Size& bottomRight);

            void setColor(const Graphics::Color &color);

            /**
             * Whether text outline is currently enabled or not.
             */
            bool outline() const;

            /**
             * Enables or disables text outline. Default outline color is black.
             */
            void setOutline(bool outLine);

            /**
             * Current outline color.
             */
            const Graphics::Color& outlineColor() const;

            /**
             * Sets text outline color. 0 - disables outline, any other color will enable it.
             */
            void setOutlineColor(const Graphics::Color &color);

            /**
             * Current line offset.
             */
            int lineOffset() const;

            /**
             * Sets number of lines to adjust vertical position. Positive - up, negative - down.
             */
            void setLineOffset(int);

            const std::vector<int>& customLineShifts() const;

            /**
             * Sets custom horizontal shifting for each if displayed line. This is applied after alignment and doesn't affect TextArea size.
             */
            void setCustomLineShifts(std::vector<int> shifts);

            Graphics::Font* font();

            void setFont(Graphics::Font* font);

            void setFont(Graphics::Font* font, const Graphics::Color &color);

            /**
             * Sets font by font filename and color.
             */
            void setFont(const std::string& fontName, const Graphics::Color &color);

            /**
             * Current font filename.
             */
            std::string fontName();

            void render(bool eggTransparency = false) override;

            bool opaque(const Graphics::Point &pos) override;

            unsigned int timestampCreated() const;

            /**
             * Appends given string to current text.
             */
            TextArea& operator<<(const std::string& text);

            /**
             * Appends string representation of given number.
             */
            TextArea& operator<<(unsigned value);

            /**
             * Appends string representation of given number.
             */
            TextArea& operator<<(signed value);

            /**
             * Appends given string to current text.
             */
            TextArea& operator+=(const std::string& text);

            /**
             * Appends string representation of given number.
             */
            TextArea& operator+=(unsigned value);

            /**
             * Appends string representation of given number.
             */
            TextArea& operator+=(signed value);

            /**
             * Replaces text content.
             */
            TextArea& operator=(const std::string& text);

            /**
             * Replaces content with string representation of given number.
             */
            TextArea& operator=(unsigned value);

            /**
             * Replaces content with string representation of given number.
             */
            TextArea& operator=(signed value);

        private:
            struct Line
            {
                // line width in pixels
                int width = 0;

                std::vector<Graphics::TextSymbol> symbols;

                bool operator < (const Line& rhs) const {
                    return width < rhs.width;
                }
            };

            /**
             * If true, _symbols will be regenerated on next render().
             */
            bool _changed = true;

            std::vector<Graphics::TextSymbol> _symbols;

            std::string _text;

            Graphics::Font* _font = nullptr;

            HorizontalAlign _horizontalAlign = HorizontalAlign::LEFT;

            VerticalAlign _verticalAlign = VerticalAlign::TOP;

            /**
             * User-defined size. 0 for each dimension represents "auto-size" for this dimension, so size() will return calculated size.
             */
            Graphics::Size _size;

            /**
             * Real size of TextArea on screen, as determined by previous _updateSymbols() call.
             */
            Graphics::Size _calculatedSize;

            /**
             * Lines of text. Cleared along with _changed flag when it is required to recalculate symbol positions.
             */
            std::vector<Line> _lines;

            int _lineOffset = 0;

            bool _wordWrap = false;

            Graphics::Size _paddingTopLeft, _paddingBottomRight;

            std::vector<int> _customLineShifts;

            // TODO: implement
            Graphics::Color _backgroundColor = {0,0,0,0};

            // TODO: should be white, and properly set to green in states/ui
            Graphics::Color _color = {0x3f, 0xf8, 0x00, 0xff};

            Graphics::Color _outlineColor = {0,0,0,0};

            unsigned int _timestampCreated = 0;

            Graphics::TextArea _textArea;

            /**
             * Update symbols, if needed.
             */
            virtual void _updateSymbols();

            /**
             * If needed, updates lines by splitting source string.
             */
            virtual void _updateLines();

            /**
             * Call when it is required to recalculate symbol positions.
             * @param lines true to also rebuild line composition.
             */
            void _needUpdate(bool lines = false);

            void _updateBuffers();
        };
    }
}
