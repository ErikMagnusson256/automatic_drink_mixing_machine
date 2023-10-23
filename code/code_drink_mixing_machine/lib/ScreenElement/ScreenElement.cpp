#include "ScreenElement.h"

ScreenElement::ScreenElement()
{
    ScreenElement(0,0, 50, 50, 5, false);
}

ScreenElement::ScreenElement(int pos_x_input, int pos_y_input, int width_input, int height_input, int border_size_input, bool rounded_corner_input)
{
    this->pos_x = pos_x_input;
    this->pos_y = pos_y_input;
    this->width = width_input;
    this->height = height_input;
    this->border_size = border_size_input;
    this->rounded_corner = rounded_corner_input;
}

bool ScreenElement::Draw(MCUFRIEND_kbv *screen, uint32_t dt_ms)
{

}

bool ScreenElement::ForceDraw(MCUFRIEND_kbv *screen)
{

}

bool ScreenElement::Update(const InputVector &user_input, OutputVector &machine_output_request, uint32_t  dt_ms)
{

}