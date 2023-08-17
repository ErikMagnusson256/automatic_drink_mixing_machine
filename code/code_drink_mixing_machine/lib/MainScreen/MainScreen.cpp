#include "MainScreen.h"

MainScreen::MainScreen()
{
    pump_control.Init(SCREEN_WIDTH/12, SCREEN_HEIGHT/6, SCREEN_WIDTH*10/12, SCREEN_HEIGHT*4/8 );
}

bool MainScreen::Render(MCUFRIEND_kbv *screen, uint32_t dt_ms)
{
    pump_control.Render(screen, dt_ms);
}

bool MainScreen::Update(const InputVector &user_input, uint32_t  dt_ms)
{

}