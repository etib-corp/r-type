/*
** EPITECH PROJECT, 2024
** graphical
** File description:
** Keys
*/

#pragma once

#include "Window.hpp"

#define LE_EVENT_NONE               0x0000

// Letters
#define LE_KEY_A                    GLFW_KEY_A
#define LE_KEY_B                    GLFW_KEY_B
#define LE_KEY_C                    GLFW_KEY_C
#define LE_KEY_D                    GLFW_KEY_D
#define LE_KEY_E                    GLFW_KEY_E
#define LE_KEY_F                    GLFW_KEY_F
#define LE_KEY_G                    GLFW_KEY_G
#define LE_KEY_H                    GLFW_KEY_H
#define LE_KEY_I                    GLFW_KEY_I
#define LE_KEY_J                    GLFW_KEY_J
#define LE_KEY_K                    GLFW_KEY_K
#define LE_KEY_L                    GLFW_KEY_L
#define LE_KEY_M                    GLFW_KEY_M
#define LE_KEY_N                    GLFW_KEY_N
#define LE_KEY_O                    GLFW_KEY_O
#define LE_KEY_P                    GLFW_KEY_P
#define LE_KEY_Q                    GLFW_KEY_Q
#define LE_KEY_R                    GLFW_KEY_R
#define LE_KEY_S                    GLFW_KEY_S
#define LE_KEY_T                    GLFW_KEY_T
#define LE_KEY_U                    GLFW_KEY_U
#define LE_KEY_V                    GLFW_KEY_V
#define LE_KEY_W                    GLFW_KEY_W
#define LE_KEY_X                    GLFW_KEY_X
#define LE_KEY_Y                    GLFW_KEY_Y
#define LE_KEY_Z                    GLFW_KEY_Z

// Numbers
#define LE_KEY_0                    GLFW_KEY_0
#define LE_KEY_1                    GLFW_KEY_1
#define LE_KEY_2                    GLFW_KEY_2
#define LE_KEY_3                    GLFW_KEY_3
#define LE_KEY_4                    GLFW_KEY_4
#define LE_KEY_5                    GLFW_KEY_5
#define LE_KEY_6                    GLFW_KEY_6
#define LE_KEY_7                    GLFW_KEY_7
#define LE_KEY_8                    GLFW_KEY_8
#define LE_KEY_9                    GLFW_KEY_9

// Function Keys
#define LE_KEY_F1                   GLFW_KEY_F1
#define LE_KEY_F2                   GLFW_KEY_F2
#define LE_KEY_F3                   GLFW_KEY_F3
#define LE_KEY_F4                   GLFW_KEY_F4
#define LE_KEY_F5                   GLFW_KEY_F5
#define LE_KEY_F6                   GLFW_KEY_F6
#define LE_KEY_F7                   GLFW_KEY_F7
#define LE_KEY_F8                   GLFW_KEY_F8
#define LE_KEY_F9                   GLFW_KEY_F9
#define LE_KEY_F10                  GLFW_KEY_F10
#define LE_KEY_F11                  GLFW_KEY_F11
#define LE_KEY_F12                  GLFW_KEY_F12

// Special Keys
#define LE_KEY_ESCAPE               GLFW_KEY_ESCAPE
#define LE_KEY_TAB                  GLFW_KEY_TAB
#define LE_KEY_CAPSLOCK             GLFW_KEY_CAPS_LOCK
#define LE_KEY_SHIFT                GLFW_KEY_LEFT_SHIFT
#define LE_KEY_CTRL                 GLFW_KEY_LEFT_CONTROL
#define LE_KEY_ALT                  GLFW_KEY_LEFT_ALT
#define LE_KEY_SPACE                GLFW_KEY_SPACE
#define LE_KEY_ENTER                GLFW_KEY_ENTER
#define LE_KEY_BACKSPACE            GLFW_KEY_BACKSPACE

// Arrow Keys
#define LE_KEY_UP                   GLFW_KEY_UP
#define LE_KEY_DOWN                 GLFW_KEY_DOWN
#define LE_KEY_LEFT                 GLFW_KEY_LEFT
#define LE_KEY_RIGHT                GLFW_KEY_RIGHT

// Punctuation and Misc
#define LE_KEY_COMMA                GLFW_KEY_COMMA
#define LE_KEY_PERIOD               GLFW_KEY_PERIOD
#define LE_KEY_SLASH                GLFW_KEY_SLASH
#define LE_KEY_SEMICOLON            GLFW_KEY_SEMICOLON
#define LE_KEY_QUOTE                GLFW_KEY_APOSTROPHE
#define LE_KEY_LEFTBRACKET          GLFW_KEY_LEFT_BRACKET
#define LE_KEY_RIGHTBRACKET         GLFW_KEY_RIGHT_BRACKET
#define LE_KEY_BACKSLASH            GLFW_KEY_BACKSLASH
#define LE_KEY_MINUS                GLFW_KEY_MINUS
#define LE_KEY_EQUALS               GLFW_KEY_EQUAL
#define LE_KEY_GRAVE                GLFW_KEY_GRAVE_ACCENT

// Numpad Keys
#define LE_KEY_NUMPAD_0             GLFW_KEY_KP_0
#define LE_KEY_NUMPAD_1             GLFW_KEY_KP_1
#define LE_KEY_NUMPAD_2             GLFW_KEY_KP_2
#define LE_KEY_NUMPAD_3             GLFW_KEY_KP_3
#define LE_KEY_NUMPAD_4             GLFW_KEY_KP_4
#define LE_KEY_NUMPAD_5             GLFW_KEY_KP_5
#define LE_KEY_NUMPAD_6             GLFW_KEY_KP_6
#define LE_KEY_NUMPAD_7             GLFW_KEY_KP_7
#define LE_KEY_NUMPAD_8             GLFW_KEY_KP_8
#define LE_KEY_NUMPAD_9             GLFW_KEY_KP_9
#define LE_KEY_NUMPAD_PLUS          GLFW_KEY_KP_ADD
#define LE_KEY_NUMPAD_MINUS         GLFW_KEY_KP_SUBTRACT
#define LE_KEY_NUMPAD_MULTIPLY      GLFW_KEY_KP_MULTIPLY
#define LE_KEY_NUMPAD_DIVIDE        GLFW_KEY_KP_DIVIDE
#define LE_KEY_NUMPAD_ENTER         GLFW_KEY_KP_ENTER
#define LE_KEY_NUMPAD_DOT           GLFW_KEY_KP_DECIMAL

// System Keys
#define LE_KEY_PRINTSCREEN          GLFW_KEY_PRINT_SCREEN
#define LE_KEY_SCROLLLOCK           GLFW_KEY_SCROLL_LOCK
#define LE_KEY_PAUSE                GLFW_KEY_PAUSE
#define LE_KEY_INSERT               GLFW_KEY_INSERT
#define LE_KEY_DELETE               GLFW_KEY_DELETE
#define LE_KEY_HOME                 GLFW_KEY_HOME
#define LE_KEY_END                  GLFW_KEY_END
#define LE_KEY_PAGEUP               GLFW_KEY_PAGE_UP
#define LE_KEY_PAGEDOWN             GLFW_KEY_PAGE_DOWN

// Windows / Meta Keys
#define LE_KEY_LEFTMETA             GLFW_KEY_LEFT_SUPER
#define LE_KEY_RIGHTMETA            GLFW_KEY_RIGHT_SUPER
#define LE_KEY_APPLICATION          GLFW_KEY_MENU

// Mouse Buttons
#define LE_MOUSE_BUTTON_LEFT        GLFW_MOUSE_BUTTON_LEFT
#define LE_MOUSE_BUTTON_RIGHT       GLFW_MOUSE_BUTTON_RIGHT
#define LE_MOUSE_BUTTON_MIDDLE      GLFW_MOUSE_BUTTON_MIDDLE
#define LE_MOUSE_BUTTON_X1          GLFW_MOUSE_BUTTON_4
#define LE_MOUSE_BUTTON_X2          GLFW_MOUSE_BUTTON_5

// Mouse Wheel
#define LE_MOUSE_WHEEL_UP           GLFW_KEY_UNKNOWN  // GLFW does not natively support mouse wheel as buttons
#define LE_MOUSE_WHEEL_DOWN         GLFW_KEY_UNKNOWN  // GLFW does not natively support mouse wheel as buttons

// Mouse Movements (optional, for advanced binding)
#define LE_MOUSE_MOVE               GLFW_KEY_UNKNOWN  // Movement is typically handled by callbacks, not keycodes
#define LE_MOUSE_MOVE_LEFT          GLFW_KEY_UNKNOWN
#define LE_MOUSE_MOVE_RIGHT         GLFW_KEY_UNKNOWN
#define LE_MOUSE_MOVE_UP            GLFW_KEY_UNKNOWN
#define LE_MOUSE_MOVE_DOWN          GLFW_KEY_UNKNOWN

// Joystick Buttons
#define LE_JOYSTICK_BUTTON_A         GLFW_GAMEPAD_BUTTON_A
#define LE_JOYSTICK_BUTTON_B         GLFW_GAMEPAD_BUTTON_B
#define LE_JOYSTICK_BUTTON_X         GLFW_GAMEPAD_BUTTON_X
#define LE_JOYSTICK_BUTTON_Y         GLFW_GAMEPAD_BUTTON_Y
#define LE_JOYSTICK_BUTTON_LB        GLFW_GAMEPAD_BUTTON_LEFT_BUMPER
#define LE_JOYSTICK_BUTTON_RB        GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER
#define LE_JOYSTICK_BUTTON_BACK      GLFW_GAMEPAD_BUTTON_BACK
#define LE_JOYSTICK_BUTTON_START     GLFW_GAMEPAD_BUTTON_START
#define LE_JOYSTICK_BUTTON_L3        GLFW_GAMEPAD_BUTTON_LEFT_THUMB
#define LE_JOYSTICK_BUTTON_R3        GLFW_GAMEPAD_BUTTON_RIGHT_THUMB

// Joystick D-Pad (Digital Pad)
#define LE_JOYSTICK_DPAD_UP          GLFW_GAMEPAD_BUTTON_DPAD_UP
#define LE_JOYSTICK_DPAD_RIGHT       GLFW_GAMEPAD_BUTTON_DPAD_RIGHT
#define LE_JOYSTICK_DPAD_DOWN        GLFW_GAMEPAD_BUTTON_DPAD_DOWN
#define LE_JOYSTICK_DPAD_LEFT        GLFW_GAMEPAD_BUTTON_DPAD_LEFT

// Joystick Axes
#define LE_JOYSTICK_AXIS_LEFT_X      GLFW_GAMEPAD_AXIS_LEFT_X
#define LE_JOYSTICK_AXIS_LEFT_Y      GLFW_GAMEPAD_AXIS_LEFT_Y
#define LE_JOYSTICK_AXIS_RIGHT_X     GLFW_GAMEPAD_AXIS_RIGHT_X
#define LE_JOYSTICK_AXIS_RIGHT_Y     GLFW_GAMEPAD_AXIS_RIGHT_Y

// Joystick Triggers (Analog)
#define LE_JOYSTICK_TRIGGER_LEFT     GLFW_GAMEPAD_AXIS_LEFT_TRIGGER
#define LE_JOYSTICK_TRIGGER_RIGHT    GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER