#include "FloatInputElement.h"


FloatInputElement::FloatInputElement()
{
    FloatInputElement(100, 100, 50, 50, RED, GREEN, YELLOW, "default", 1, BLACK);
}
FloatInputElement::FloatInputElement(int xpos_, int ypos_,int width_, int height_, uint16_t button_colour_, uint16_t highlight_colour_, uint16_t select_colour_, String button_text_, int text_size_, uint16_t text_colour_ )
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
bool FloatInputElement::Render(MCUFRIEND_kbv *screen, uint32_t dt_ms)
{
    if(force_redraw)
    {
        force_redraw = false;
        // Draw a white square over element area
        screen->fillRect(xpos, ypos, width, height, WHITE);

        // Draw select or highlight border first
        if(is_selected)
        {
            screen->fillRoundRect(xpos, ypos, width, height, CLICKABLE_BUTTON_HIGHLIGHT_WIDTH, select_colour);
        }
        else if(is_highlighed)
        {
            screen->fillRoundRect(xpos, ypos, width, height, CLICKABLE_BUTTON_HIGHLIGHT_WIDTH, highlight_colour);
        }

        // Draw main body of element, inside the highlighted area
        screen->fillRoundRect(xpos + CLICKABLE_BUTTON_HIGHLIGHT_WIDTH, ypos + CLICKABLE_BUTTON_HIGHLIGHT_WIDTH, width - 2*CLICKABLE_BUTTON_HIGHLIGHT_WIDTH, height - 2*CLICKABLE_BUTTON_HIGHLIGHT_WIDTH, 5, button_colour);
        

        // Draw text inside button
        int16_t text_x_pos = 0;
        int16_t text_y_pos = 0;
        uint16_t text_width = 0;
        uint16_t text_height = 0;

        String element_text =  float_name + " " + String(float_val) + " " + float_unit;

        // Text should be centered, get bounding box of text
        screen->getTextBounds(element_text.c_str(), xpos, ypos, &text_x_pos, &text_y_pos, &text_width, &text_height);
        
        // Calculate where to place text cursor
        int screen_x_pos = xpos + (width + CLICKABLE_BUTTON_HIGHLIGHT_WIDTH)/2 - text_width / 2;
        int screen_y_pos = ypos + (height + CLICKABLE_BUTTON_HIGHLIGHT_WIDTH)/2 - text_height/2;

        screen->setCursor(screen_x_pos, screen_y_pos);

        screen->setTextSize(text_size);
        screen->setTextColor(WHITE);
        screen->println(element_text);

        // Draw Up and Down triangle before and after text element
        // TODO do not hardcode this
        #define TEMPICON_SIZE_X 100
        #define TEMPICON_SIZE_Y 85

        // Up triangle
        int center_x_down = (xpos) + TEMPICON_SIZE_X/4, 
            center_y_down = ypos + TEMPICON_SIZE_Y*5/7, 
            triangle_side_length=30;

        int x0_down = center_x_down,
            y0_down = center_y_down + triangle_side_length*cos(DEG_TO_RAD*30)/2,
            x1_down = center_x_down - triangle_side_length*sin(DEG_TO_RAD*30),
            y1_down = center_y_down - triangle_side_length*cos(DEG_TO_RAD*30)/2,
            x2_down = center_x_down + triangle_side_length*sin(DEG_TO_RAD*30),
            y2_down = center_y_down - triangle_side_length*cos(DEG_TO_RAD*30)/2;       
        
        if(last_float_val > float_val)
        {
            screen->fillTriangle(x0_down, y0_down, x1_down, y1_down, x2_down, y2_down, RED);
        }

        screen->drawTriangle(x0_down, y0_down, x1_down, y1_down, x2_down, y2_down, 0x0);

        // Down triangle
        int center_x_up = (xpos+TEMPICON_SIZE_X) - TEMPICON_SIZE_X/4, 
            center_y_up = center_y_down;

        int x0_up = center_x_up,
            y0_up = center_y_up - triangle_side_length*cos(DEG_TO_RAD*30)/2,
            x1_up = center_x_up + triangle_side_length*sin(DEG_TO_RAD*30),
            y1_up = center_y_up + triangle_side_length*cos(DEG_TO_RAD*30)/2,
            x2_up = center_x_up - triangle_side_length*sin(DEG_TO_RAD*30),
            y2_up = center_y_up + triangle_side_length*cos(DEG_TO_RAD*30)/2;       
        
        if(last_float_val < float_val)
        {
            screen->fillTriangle(x0_up, y0_up, x1_up, y1_up, x2_up, y2_up, RED);
        }

        screen->drawTriangle(x0_up, y0_up, x1_up, y1_up, x2_up, y2_up, 0x0);

    }

    return true;
}
bool FloatInputElement::Update(const InputVector &user_input, uint32_t  dt_ms)
{
    // Not applicable to update internal logic states - These are set from outside the object.

    return false;
}



bool FloatInputElement::GetIsHighlighted()
{
    return is_highlighed;
}
bool FloatInputElement::GetIsSelected()
{
    return is_selected;
}

bool FloatInputElement::SetIsHighlighted(bool input)
{
    is_highlighed = input;
    force_redraw = true;
}
bool FloatInputElement::SetIsSelected(bool input)
{
    is_selected = input;
    force_redraw = true;
}

bool FloatInputElement::SetFloatVal(float inputval)
{
    this->last_float_val = this->float_val;
    this->float_val = inputval;
}

float FloatInputElement::GetFloatVal()
{
    return this->float_val;
}