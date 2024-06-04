// Author: Dominik Sidorczuk

#ifndef COLORS_HPP
#define COLORS_HPP
#pragma once
#include <cmath>


enum Colors {
    RED = 0xFF6F6F,
    YELLOW = 0xEDFF46,
    GREEN = 0x8AFF46,
    BLUE = 0x57BCFF,
};


namespace MWindow {
    const int WIDTH = 7;
    const int HALF_WIDTH = WIDTH / 2;
    const int ADDFILEBUTTON_Y = 1;
    const int LEFT_ADDFILEBUTTON_X = HALF_WIDTH / 2;
    const int RIGHT_ADDFILEBUTTON_X = HALF_WIDTH + int(std::ceil(float(HALF_WIDTH) / 2.f));
    const int RUNBUTTON_Y = 3;
    const int MERGEBUTTON_Y = 4;
    const int LEGEND = 5;
};


namespace TWindow {
    const int WIDTH = MWindow::WIDTH / 2;
    const int HEIGTH = 4;
};


#endif
