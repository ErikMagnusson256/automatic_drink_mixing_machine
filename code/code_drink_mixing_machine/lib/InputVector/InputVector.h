/*

Object to store User Input (joystick state, button states) and pass into objects which handles logic

*/

struct InputVector {
    int joystick_x; // Valid ranges [0, 1023]
    int joystick_y; // Valid ranges [0, 1023]
    bool button_confirm; // Valid ranges [true, false]
};