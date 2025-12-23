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

#include "svg_writer.h"
#include <fstream>
#include <iomanip>
#include <cmath>

namespace cola {

SVGWriter::SVGWriter(double width, double height)
    : canvas_width_(width), canvas_height_(height), path_started_(false) {
    current_state_ = DrawingState();
}

SVGWriter::~SVGWriter() {
}

void SVGWriter::save() {
    state_stack_.push_back(current_state_);
}

void SVGWriter::restore() {
    if (!state_stack_.empty()) {
        current_state_ = state_stack_.back();
        state_stack_.pop_back();
    }
}

void SVGWriter::set_line_width(double width) {
    current_state_.line_width = width;
}

void SVGWriter::set_font_size(double size) {
    current_state_.font_size = size;
}

void SVGWriter::set_source_rgb(double r, double g, double b) {
    current_state_.r = r;
    current_state_.g = g;
    current_state_.b = b;
    current_state_.a = 1.0;
}

void SVGWriter::set_source_rgba(double r, double g, double b, double a) {
    current_state_.r = r;
    current_state_.g = g;
    current_state_.b = b;
    current_state_.a = a;
}

void SVGWriter::move_to(double x, double y) {
    current_state_.current_x = x;
    current_state_.current_y = y;
    if (!path_started_) {
        current_path_ = "";
        path_started_ = true;
    }
    std::ostringstream oss;
    oss << "M " << x << " " << y << " ";
    current_path_ += oss.str();
}

void SVGWriter::line_to(double x, double y) {
    current_state_.current_x = x;
    current_state_.current_y = y;
    std::ostringstream oss;
    oss << "L " << x << " " << y << " ";
    current_path_ += oss.str();
}

void SVGWriter::arc(double xc, double yc, double radius, double angle1, double angle2) {
    // Convert arc to path using bezier approximation or direct circle
    // For full circle (0 to 2*PI), we can use a circle element instead
    if (std::abs(angle2 - angle1 - 2.0 * M_PI) < 0.01) {
        // Full circle - render immediately as a circle element
        std::ostringstream oss;
        oss << "<circle cx=\"" << xc << "\" cy=\"" << yc 
            << "\" r=\"" << radius << "\" "
            << "fill=\"" << rgba_to_string(current_state_.r, current_state_.g, 
                                          current_state_.b, current_state_.a) << "\" "
            << "stroke=\"none\"/>\n";
        svg_content_ << oss.str();
        path_started_ = false;
        current_path_ = "";
    } else {
        // Partial arc - approximate with path
        double x1 = xc + radius * std::cos(angle1);
        double y1 = yc + radius * std::sin(angle1);
        double x2 = xc + radius * std::cos(angle2);
        double y2 = yc + radius * std::sin(angle2);
        
        if (!path_started_) {
            move_to(x1, y1);
        }
        
        int large_arc = (angle2 - angle1) > M_PI ? 1 : 0;
        std::ostringstream oss;
        oss << "A " << radius << " " << radius << " 0 " << large_arc << " 1 " 
            << x2 << " " << y2 << " ";
        current_path_ += oss.str();
    }
}

void SVGWriter::curve_to(double x1, double y1, double x2, double y2, double x3, double y3) {
    current_state_.current_x = x3;
    current_state_.current_y = y3;
    std::ostringstream oss;
    oss << "C " << x1 << " " << y1 << " " << x2 << " " << y2 << " " << x3 << " " << y3 << " ";
    current_path_ += oss.str();
}

void SVGWriter::rectangle(double x, double y, double width, double height) {
    move_to(x, y);
    line_to(x + width, y);
    line_to(x + width, y + height);
    line_to(x, y + height);
    line_to(x, y);
}

void SVGWriter::stroke() {
    flush_path(false, false);
}

void SVGWriter::fill() {
    flush_path(true, false);
}

void SVGWriter::stroke_preserve() {
    flush_path(false, true);
}

void SVGWriter::paint() {
    // Paint fills the entire canvas with current color
    std::ostringstream oss;
    oss << "<rect x=\"0\" y=\"0\" width=\"" << canvas_width_ 
        << "\" height=\"" << canvas_height_ << "\" "
        << "fill=\"" << rgb_to_string(current_state_.r, current_state_.g, current_state_.b) 
        << "\"/>\n";
    svg_content_ << oss.str();
}

void SVGWriter::get_text_extents(const std::string& text, TextExtents& extents) {
    // Simple approximation: assume monospace-like font metrics
    // Each character is approximately 0.6 * font_size wide
    extents.width = text.length() * current_state_.font_size * 0.6;
    extents.height = current_state_.font_size;
    extents.x_bearing = 0;
    extents.y_bearing = -current_state_.font_size * 0.8;
    extents.x_advance = extents.width;
    extents.y_advance = 0;
}

void SVGWriter::show_text(const std::string& text) {
    std::ostringstream oss;
    oss << "<text x=\"" << current_state_.current_x 
        << "\" y=\"" << current_state_.current_y 
        << "\" font-size=\"" << current_state_.font_size 
        << "\" fill=\"" << rgb_to_string(current_state_.r, current_state_.g, current_state_.b) 
        << "\">" << text << "</text>\n";
    svg_content_ << oss.str();
}

void SVGWriter::show_page() {
    // In SVG, this is essentially a no-op, but we keep it for API compatibility
}

bool SVGWriter::write_to_file(const std::string& filename) {
    std::ofstream file(filename.c_str());
    if (!file.is_open()) {
        return false;
    }

    // Write SVG header
    file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    file << "<svg xmlns=\"http://www.w3.org/2000/svg\" ";
    file << "width=\"" << canvas_width_ << "\" ";
    file << "height=\"" << canvas_height_ << "\" ";
    file << "viewBox=\"0 0 " << canvas_width_ << " " << canvas_height_ << "\">\n";

    // Write content
    file << svg_content_.str();

    // Close SVG
    file << "</svg>\n";

    file.close();
    return true;
}

std::string SVGWriter::rgb_to_string(double r, double g, double b) {
    std::ostringstream oss;
    oss << "rgb(" 
        << static_cast<int>(r * 255) << "," 
        << static_cast<int>(g * 255) << "," 
        << static_cast<int>(b * 255) << ")";
    return oss.str();
}

std::string SVGWriter::rgba_to_string(double r, double g, double b, double a) {
    if (a >= 0.999) {
        return rgb_to_string(r, g, b);
    }
    std::ostringstream oss;
    oss << "rgba(" 
        << static_cast<int>(r * 255) << "," 
        << static_cast<int>(g * 255) << "," 
        << static_cast<int>(b * 255) << "," 
        << a << ")";
    return oss.str();
}

void SVGWriter::flush_path(bool fill_mode, bool preserve) {
    if (!path_started_ || current_path_.empty()) {
        return;
    }

    std::ostringstream oss;
    oss << "<path d=\"" << current_path_ << "\" ";
    
    if (fill_mode) {
        oss << "fill=\"" << rgba_to_string(current_state_.r, current_state_.g, 
                                           current_state_.b, current_state_.a) << "\" ";
        oss << "stroke=\"none\"";
    } else {
        oss << "fill=\"none\" ";
        oss << "stroke=\"" << rgb_to_string(current_state_.r, current_state_.g, current_state_.b) << "\" ";
        oss << "stroke-width=\"" << current_state_.line_width << "\"";
        if (current_state_.a < 0.999) {
            oss << " stroke-opacity=\"" << current_state_.a << "\"";
        }
    }
    
    oss << "/>\n";
    svg_content_ << oss.str();

    if (!preserve) {
        path_started_ = false;
        current_path_ = "";
    }
}

} // namespace cola
