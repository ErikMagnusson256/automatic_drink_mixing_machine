#include "ClickableButton.h"


ClickableButton::ClickableButton()
{

}
ClickableButton::ClickableButton(int width_, int height_, uint16_t background_colour_, uint16_t highlight_colour_, uint16_t select_colour )
{

}
bool ClickableButton::Render(MCUFRIEND_kbv *screen, uint32_t dt_ms)
{

}
bool ClickableButton::Update(const InputVector &user_input, uint32_t  dt_ms)
{
    // Not applicable to update internal logic states
    
    return false;
}

bool ClickableButton::GetIsHighlighted()
{
    return is_highlighed;
}
bool ClickableButton::GetIsSelected()
{
    return is_selected;
}

bool ClickableButton::SetIsHighlighted(bool input)
{
    is_highlighed = input;
}
bool ClickableButton::SetIsSelected(bool input)
{
    is_selected = input;
}