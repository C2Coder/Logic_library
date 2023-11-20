#pragma once

#include "Platform.hpp"
#include <SmartLeds.h>
#include <mutex>

/**
 * @brief Structure for describing rectangles on display
 *
 */
struct Rectangle {
    Rectangle(int x, int y, int w, int h)
        : x(x)
        , y(y)
        , w(w)
        , h(h) {
    }

    int x, y;
    int w, h;
};

/**
 * @brief Struktura pro kreslení obdélníků
 */
typedef Rectangle Obdelnik;

class Display {
    friend class Logic;

private:
    SmartLed m_displayLeds;

    std::mutex m_mutex;

    const char* m_tag = "Display";

    static constexpr int m_width = 10;
    static constexpr int m_height = 12;
    std::array<Rgb, m_width * m_height> m_frame;

    void displayBresenhmCircle(int xCenter, int yCenter, int x, int y, Rgb color);

    Display();

public:
    Display(Display&) = delete;
    Display(Display&&) = delete;
    Display& operator=(Display&) = delete;
    Display& operator=(Display&&) = delete;

    ~Display() = default;

    /**
     * @brief Returns width of the display in pixels
     * @return int width of the display in pixels
     */
    int width() const { return m_width; }
    /**
     * @brief Returns height of the display in pixels
     * @return int height of the display in pixels
     */
    int height() const { return m_height; }

    /**
     * @brief Returns width of each character in the font used by drawCharacter and drawString.
     * @return int width of one character in pixels.
     */
    int fontWidth() const;
    /**
     * @brief Returns height of each character in the font used by drawCharacter and drawString.
     * @return int height of one character in pixels.
     */
    int fontHeight() const;

    /**
     * @brief Returns reference to pixel on that position
     *
     * @param x X coordinate
     * @param y Y coordinate
     * @return Rgb& Pixel at requested position
     */
    Rgb& at(int x, int y);

    /**
     * @brief Set the color of pixel at specified position
     *
     * @param x X coordinate
     * @param y Y coordinate
     * @param color Color
     */
    inline void setColor(int x, int y, Rgb color) {
        if ((x > (m_width - 1)) || (y > (m_width - 1)) || (x < 0) || (y < 0))
            return;
        m_frame[(y * m_width) + x] = color;
    }

    /**
     * @brief Clear the display
     */
    void clear() {
        fill(Rgb(0, 0, 0));
    }

    /**
     * @brief Fill the display with color
     *
     * @param color Color
     */
    void fill(Rgb color);

    /**
     * @brief Draw rectangle with specified parameters
     *
     * @param x X coordinate of top-left corner
     * @param y Y coordinate of top-left corner
     * @param width
     * @param height
     * @param color
     * @param strokeWidth
     */
    void
    drawRectangle(int x, int y, int width, int height, Rgb color, int strokeWidth = 1);

    /**
     * @brief Draw rectangle with specified parameters
     *
     * @param rect Struct used to define parameters
     * @param color
     * @param strokeWidth
     */
    void drawRectangle(const Rectangle& rect, Rgb color, int strokeWidth = 1) { drawRectangle(rect.x, rect.y, rect.w, rect.h, color, strokeWidth); }

    /**
     * @brief Draw filled rectangle with specified parameters
     *
     * @param x X coordinate of top-left corner
     * @param y Y coordinate of top-left corner
     * @param width
     * @param height
     * @param color
     */
    void drawRectangleFilled(int x, int y, int width, int height, Rgb color) {
        drawRectangle(x, y, width, height, color, INT_MAX);
    }

    /**
     * @brief Draw filled rectangle with specified parameters
     *
     * @param rect Struct used to define parameters
     * @param color
     */
    void drawRectangleFilled(const Rectangle& rect, Rgb color) {
        drawRectangle(rect.x, rect.y, rect.w, rect.h, color, INT_MAX);
    }

    /**
     * @brief Draw square with specified parameters
     *
     * @param x X coordinate of top-left corner
     * @param y Y coordinate of top-left corner
     * @param size Length of side
     * @param color
     * @param strokeWidth
     */
    void drawSquare(int x, int y, int size, Rgb color, int strokeWidth = 1) {
        drawRectangle(x, y, size, size, color, strokeWidth);
    }

    /**
     * @brief Draw filled square with specified parameters
     *
     * @param x X coordinate of top-left corner
     * @param y Y coordinate of top-left corner
     * @param size Length of side
     * @param color
     */
    void drawSquareFilled(int x, int y, int size, Rgb color) { drawSquare(x, y, size, color, INT_MAX); }

    /**
     * @brief Draw circle with specified parameters
     *
     * @param centerX X coordinate of the center
     * @param centerY Y coordinate of the center
     * @param radius
     * @param color
     */
    void drawCircle(int centerX, int centerY, int radius, Rgb color);

    /**
     * @brief Draw filled circle with specified parameters
     *
     * @param centerX X coordinate of the center
     * @param centerY Y coordinate of the center
     * @param radius
     * @param color
     */
    void drawCircleFilled(int centerX, int centerY, int radius, Rgb color);

    /**
     * @brief Draw line
     *
     * @param x1 X coordinate of the beginning
     * @param y1 Y coordinate of the beginning
     * @param x2 X coordinate of the end
     * @param y2 Y coordinate of the end
     * @param color
     * @param strokeWidth
     */
    void drawLine(int x1, int y1, int x2, int y2, Rgb color, int strokeWidth = 1);

    /**
     * @brief Draw a single character to the display. The dimensions of the characters can be obtained by calling
     * fontWidth() and fontHeight().
     *
     * @param c which character to draw, from ASCII + ISO-8859-1 codepage.
     * @param color which color to use
     * @param offsetX X offset where to start the drawing.
     * @param offsetY Y offset where to start the drawing.
     */
    void drawCharacter(char c, Rgb color, int offsetX = 2, int offsetY = 0);


    /**
     * @brief Draws whole string to the display, handling Czech UTF-8 sequences correctly.
     *
     * @param utf8Czech String to draw on the display
     * @param color which color to use
     * @param offsetX X offset where to start the drawing. This offsets the whole string, which means you can use negative offset
     *                to scroll and show the whole string.
     * @param offsetY Y offset where to start the drawing.
     * @return int number of separate drawable characters (after UTF-8 decoding).
     */
    int drawString(const char* utf8Czech, Rgb color, int offsetX = 2, int offsetY = 0);

    /**
     * @see Display::drawString
     */
    int drawString(const std::string& utf8Czech, Rgb color, int offsetX = 2, int offsetY = 0) {
        return drawString(utf8Czech.c_str(), color, offsetX, offsetY);
    }

    /**
     * @brief Show prepared frame on display
     *
     * @param intensity [0-255] maximal intenzity
     */
    void show(int intensity = 255);

    Rgb& operator()(int x, int y);
    Rgb& operator[](int index);
};

using Displej = Display;