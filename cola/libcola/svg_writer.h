/*
 * vim: ts=4 sw=4 et tw=0 wm=0
 *
 * libcola - A library providing force-directed network layout using the 
 *           stress-majorization method subject to separation constraints.
 *
 * Copyright (C) 2006-2024  Monash University
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * See the file LICENSE.LGPL distributed with the library.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef _SVG_WRITER_H
#define _SVG_WRITER_H

#include <string>
#include <sstream>
#include <vector>
#include <cmath>

namespace cola {

/**
 * Simple SVG writer for generating SVG output without external dependencies.
 * This class provides basic SVG drawing primitives similar to Cairo's API
 * but generates pure SVG directly.
 */
class SVGWriter {
public:
    SVGWriter(double width, double height);
    ~SVGWriter();

    // Drawing state
    void save();
    void restore();
    void set_line_width(double width);
    void set_font_size(double size);
    void set_source_rgb(double r, double g, double b);
    void set_source_rgba(double r, double g, double b, double a);

    // Path construction
    void move_to(double x, double y);
    void line_to(double x, double y);
    void arc(double xc, double yc, double radius, double angle1, double angle2);
    void curve_to(double x1, double y1, double x2, double y2, double x3, double y3);
    void rectangle(double x, double y, double width, double height);

    // Path rendering
    void stroke();
    void fill();
    void stroke_preserve();
    void paint();

    // Text
    struct TextExtents {
        double x_bearing;
        double y_bearing;
        double width;
        double height;
        double x_advance;
        double y_advance;
    };
    void get_text_extents(const std::string& text, TextExtents& extents);
    void show_text(const std::string& text);

    // Output
    void show_page();
    bool write_to_file(const std::string& filename);

private:
    struct DrawingState {
        double line_width;
        double font_size;
        double r, g, b, a;
        double current_x, current_y;
        
        DrawingState() : line_width(1.0), font_size(12.0), 
                        r(0), g(0), b(0), a(1.0),
                        current_x(0), current_y(0) {}
    };

    double canvas_width_;
    double canvas_height_;
    std::vector<DrawingState> state_stack_;
    DrawingState current_state_;
    std::ostringstream svg_content_;
    std::string current_path_;
    bool path_started_;

    // Helper methods
    std::string rgb_to_string(double r, double g, double b);
    std::string rgba_to_string(double r, double g, double b, double a);
    void flush_path(bool fill_mode, bool preserve);
};

} // namespace cola

#endif // _SVG_WRITER_H
