#include "input.h"

namespace input
{   
    bool KeyPressed(SDL_Keycode Key)
    {        
        for(int PressedIndex = 0; PressedIndex < KEY_PRESSES; ++PressedIndex)
        {
            if(Pressed[PressedIndex] == Key && Key != 0)
            {
                return true;
            }
        }
        return false;
    }
    
    static void AddKey(SDL_Keycode Key)
    {        
        for(int PressedIndex = 0; PressedIndex < KEY_PRESSES; ++PressedIndex)
        {
            if(Pressed[PressedIndex] == 0)
            {
                Pressed[PressedIndex] = Key;
                return;
            }
        }
    }
    
    static void RemoveKey(SDL_Keycode Key)
    {        
        for(int PressedIndex = 0; PressedIndex < KEY_PRESSES; ++PressedIndex)
        {
            if(Pressed[PressedIndex] == Key)
            {
                Pressed[PressedIndex] = 0;
                return;
            }
        }
    }
        
    bool ButtonPressed(Uint8 Button)
    {
        for(int ButtonIndex = 0; ButtonIndex < MOUSE_PRESSES; ++ButtonIndex)
        {
            if(MousePressed[ButtonIndex].button == Button)
            {
                return true;
            }
        }
        return false;
    }
    
    static void MouseAddKey(SDL_MouseButtonEvent Button)
    {        
        for(int ButtonIndex = 0; ButtonIndex < MOUSE_PRESSES; ++ButtonIndex)
        {
            if(!ButtonPressed(Button.button) && MousePressed[ButtonIndex].button == 0)
            {
                MousePressed[ButtonIndex] = Button;
                return;
            }
        }
    }
    
    static void MouseRemoveKey(SDL_MouseButtonEvent Button)
    {        
        for(int ButtonIndex = 0; ButtonIndex < MOUSE_PRESSES; ++ButtonIndex)
        {            
            if(ButtonPressed(Button.button) && MousePressed[ButtonIndex].button == Button.button)
            {
                MousePressed[ButtonIndex] = {};
                return;
            }
        }
    }
    
    bool Process()
    {   
        WheelDirection = MOUSE_WHEEL_DIRECTION::MAX;
        
        SDL_Event Event;
        while(SDL_PollEvent(&Event))
        {            
            switch(Event.type)
            {
                case SDL_QUIT:
                {
                    return false;
                }
                break;
                
                case SDL_KEYDOWN:
                {   
                    if(!KeyPressed(Event.key.keysym.sym))
                    {
                        AddKey(Event.key.keysym.sym);
                    }
                }
                break;
                case SDL_KEYUP:
                {             
                    if(KeyPressed(Event.key.keysym.sym))
                    {
                        RemoveKey(Event.key.keysym.sym);
                    }
                }
                break;                
                case SDL_MOUSEBUTTONDOWN:
                {
                    MouseAddKey(Event.button);
                }
                break;
                case SDL_MOUSEBUTTONUP:
                {
                    MouseRemoveKey(Event.button);
                }
                break;
                case SDL_MOUSEWHEEL:
                {
                    if(Event.wheel.y > 0.f)
                    {
                        WheelDirection = MOUSE_WHEEL_DIRECTION::UP;
                    }
                    else if(Event.wheel.y < 0.f)
                    {
                        WheelDirection = MOUSE_WHEEL_DIRECTION::DOWN;
                    }
                }
                break;
            }
        }
           
        SDL_GetMouseState(&MouseX, &MouseY);
        return true;
    }
    
};