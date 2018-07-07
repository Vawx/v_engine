#ifndef _INPUT_H_
#define _INPUT_H_

namespace input
{
#define KEY_PRESSES 64
#define MOUSE_PRESSES 4
    
    enum MOUSE_WHEEL_DIRECTION
    {
        UP,
        DOWN,
        MAX,
    };
    
    SDL_Keycode Pressed[KEY_PRESSES];
    SDL_MouseButtonEvent MousePressed[MOUSE_PRESSES];
    int MouseX = 0;
    int MouseY = 0;
    
    MOUSE_WHEEL_DIRECTION WheelDirection;
    
    static bool Process();  
    
    static bool KeyPressed(SDL_Keycode Key);
    static void AddKey(SDL_Keycode Key);
    static void RemoveKey(SDL_Keycode Key);
        
    static bool ButtonPressed(Uint8 Button);
    static void MouseAddKey(SDL_MouseButtonEvent Button);
    static void MouseRemoveKey(SDL_MouseButtonEvent Button);
};

#endif