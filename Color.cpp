//
// Created by sgvch on 29/02/2024.
//

#include <iomanip>
#include "Color.h"



void ChangeColor(int textColor,int backgroundColor)
{
    HANDLE console_color;//Declaring the variable console_color from HANDLE type.
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);//Using a function from the library windows.h that allows access to perform operations on the output.
    SetConsoleTextAttribute(console_color, (textColor + (backgroundColor * 16)));
//Using a function from the library windows.h which changes the output below it.
}
void centerAlign(const std::string& text, int width) {
    int padding = (width - text.length()) / 2;
    std::cout << std::setw(padding + text.length()) << std::right << text << std::endl;
}