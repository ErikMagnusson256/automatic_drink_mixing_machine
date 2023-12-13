#include "ClickableButton.h"


ClickableButton::ClickableButton()
{
    ClickableButton(100, 100, 50, 50, RED, GREEN, YELLOW, "default", 1, BLACK);
}
ClickableButton::ClickableButton(int xpos_, int ypos_,int width_, int height_, uint16_t button_colour_, uint16_t highlight_colour_, uint16_t select_colour_, String button_text_, int text_size_, uint16_t text_colour_ )
{

    is_highlighed = false;
    is_selected = false;

    force_redraw = true;

    xpos = xpos_;
    ypos = ypos_;
    width = width_;
    height = height_;
    button_colour = button_colour_;
    highlight_colour = highlight_colour_;
    select_colour = select_colour_;
    button_text = button_text_;
    text_size = text_size_;
    text_colour = text_colour_;
}
bool ClickableButton::Render(MCUFRIEND_kbv *screen, uint32_t dt_ms)
{
    if(force_redraw)
    {
        force_redraw = false;
        // Draw a white square over button area
        screen->fillRect(xpos, ypos, width, height, WHITE);

        // Draw select or highlight border first
        if(is_highlighed)
        {
            screen->fillRoundRect(xpos, ypos, width, height, CLICKABLE_BUTTON_HIGHLIGHT_WIDTH, select_colour);
        }
        else if( is_selected)
        {
            screen->fillRoundRect(xpos, ypos, width, height, CLICKABLE_BUTTON_HIGHLIGHT_WIDTH, highlight_colour);
        }

        // Draw main body of button, inside the highlighted area
        screen->fillRoundRect(xpos + CLICKABLE_BUTTON_HIGHLIGHT_WIDTH, ypos + CLICKABLE_BUTTON_HIGHLIGHT_WIDTH, width - 2*CLICKABLE_BUTTON_HIGHLIGHT_WIDTH, height - 2*CLICKABLE_BUTTON_HIGHLIGHT_WIDTH, 5, button_colour);
        

        // Draw text inside button
        int16_t text_x_pos = 0;
        int16_t text_y_pos = 0;
        uint16_t text_width = 0;
        uint16_t text_height = 0;

        // Text should be centered, get bounding box of text
        screen->getTextBounds(button_text.c_str(), xpos, ypos, &text_x_pos, &text_y_pos, &text_width, &text_height);
        
        // Calculate where to place text cursor
        int screen_x_pos = xpos + (width + CLICKABLE_BUTTON_HIGHLIGHT_WIDTH)/2 - text_width / 2;
        int screen_y_pos = ypos + (height + CLICKABLE_BUTTON_HIGHLIGHT_WIDTH)/2 - text_height/2;

        screen->setCursor(screen_x_pos, screen_y_pos);

        screen->setTextSize(text_size);
        screen->setTextColor(WHITE);
        screen->println(button_text);

    }

    return true;
}
bool ClickableButton::Update(const InputVector &user_input, uint32_t  dt_ms)
{
    // Not applicable to update internal logic states - These are set from outside the object.

    return false;
}

bool ClickableButton::ResetButton()
{
    is_highlighed = false;
    is_selected = false;
    force_redraw = true;
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
    force_redraw = true;
}
bool ClickableButton::SetIsSelected(bool input)
{
    is_selected = input;
    force_redraw = true;
}

void ClickableButton::SetButtonText(String new_button_text)
{
    if(new_button_text != button_text)
    {
        button_text = new_button_text;
        force_redraw = true;
    }
    
}