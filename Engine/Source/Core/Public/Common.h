#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <SDL3/SDL.h>
#include "CData.h"
#include "CDelegate.h"
#include "EngineUtils.h"
#include "../../Input/Public/HInput.h"



#ifndef COMMON_MARCRO

    #define COMMON_MARCRO

    #define CHARLIE_LOG(InType, format, ...) do { \
        std::cout << "["; \
        switch (InType) { \
            case Log:    std::cout << "Log";    break; \
            case Warning: std::cout << "Warning"; break; \
            case Error:   std::cout << "Error";   break; \
        } \
        std::cout << "] "; \
        std::cout << format_string(format, ##__VA_ARGS__) << std::endl; \
        } while (0)

#endif

class GameLogic
{
public:
    /* Multicast Delegate Call */
    DECLARE_MULTICAST_DELEGATE_RetVal_OneParam(CMuticast_Delegate_Event_Key, EngineUtils, SDL_Event);
    CMuticast_Delegate_Event_Key& GetEventKeyDelegate() { return Event_Key_Delegate; }

    DECLARE_MULTICAST_DELEGATE_RetVal_OneParam(CMuticast_Delegate_Event_Mouse, EngineUtils, SDL_Event);
    CMuticast_Delegate_Event_Mouse& GetEventMouseDelegate() { return Event_Mouse_Delegate; }

    DECLARE_MULTICAST_DELEGATE_RetVal_OneParam(CMuticast_Delegate_Event_Quit, EngineUtils, SDL_Event);
    CMuticast_Delegate_Event_Quit& GetEventQuitDelegate() { return Event_Quit_Delegate; }

    DECLARE_MULTICAST_DELEGATE_RetVal_OneParam(CMuticast_Delegate_Event_BeginPlay, EngineUtils, SDL_Event);
    CMuticast_Delegate_Event_BeginPlay& GetEventBeginPlayDelegate() { return Event_BeginPlay_Delegate; }

    DECLARE_MULTICAST_DELEGATE_RetVal_OneParam(CMuticast_Delegate_Event_Drop, EngineUtils, SDL_Event);
    CMuticast_Delegate_Event_Drop& GetEventDropDelegate() { return Event_Drop_Delegate; }

    /* Single Delegate Call */
    DECLARE_SINGLE_DELEGATE_RetVal_OneParam(CSingle_Delegate_Event_ImportFile, EngineUtils, bool, SDL_Event);
    
protected:
    
    static GameLogic* gamelogic_;

    EngineUtils* engine;

    bool RunLogic(SDL_Event* event);

    GameLogic()
    {
        eventHandlers[SDL_EVENT_KEY_DOWN] = &GameLogic::EventKey;
        eventHandlers[SDL_EVENT_KEY_UP] = &GameLogic::EventKey;
        eventHandlers[SDL_EVENT_MOUSE_BUTTON_UP] = &GameLogic::EventMouse;
        eventHandlers[SDL_EVENT_MOUSE_BUTTON_DOWN] = &GameLogic::EventMouse;
        eventHandlers[SDL_EVENT_MOUSE_WHEEL] = &GameLogic::EventMouse;
        eventHandlers[SDL_EVENT_QUIT] = &GameLogic::EventQuit;
        eventHandlers[SDL_EVENT_DROP_FILE] = &GameLogic::EventDrop;
        eventHandlers[SDL_EVENT_WINDOW_SHOWN] = &GameLogic::EventBeginPlay;
    }

public:

    typedef bool (GameLogic::*EventHandler)(SDL_Event*);
    
    GameLogic(GameLogic &Other) = delete;

    void operator=(const GameLogic &) = delete;

    static GameLogic* Get();

    static void Free();
    
    bool GameLogic_Loop();
    
private:
    bool EventBeginPlay(SDL_Event* event);
    
    bool EventKey(SDL_Event* event);

    bool EventMouse(SDL_Event* event);

    bool EventQuit(SDL_Event* event);

    bool EventDrop(SDL_Event* event);

    /*void KeyProcess(SDL_Event* event);

    void MouseProcess(SDL_Event* event);*/

    std::map<SDL_EventType, EventHandler> eventHandlers;

    CMuticast_Delegate_Event_Key Event_Key_Delegate;
    CMuticast_Delegate_Event_Key Event_Mouse_Delegate;
    CMuticast_Delegate_Event_Key Event_Quit_Delegate;
    CMuticast_Delegate_Event_Key Event_BeginPlay_Delegate;
    CMuticast_Delegate_Event_Key Event_Drop_Delegate;
    CSingle_Delegate_Event_ImportFile Event_Import_Delegate;
};

std::string format_string(const char* format, ...);



//static bool RenderingLogic_Loop();