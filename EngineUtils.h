#pragma once
#include "SDL3/SDL.h"
#include "HInput.h"
#include "CFunctionHandler.h"

#define REGISTER_HANDLER_MULTICAST( HandlerList, HandlerName, FunctionPointer, EngineInstance, SDL_Event ) \
    HandlerList[HandlerName].Set(EngineInstance, FunctionPointer, SDL_Event)

#define REGISTER_HANDLER_SINGLE( Handler, FunctionPointer, EngineInstance, SDL_Event ) \
Handler.Set(EngineInstance, FunctionPointer, SDL_Event)

enum CMulticastHandlerListName : int
{
    HList_KeyProcess,
    HList_MouseProcess,
};

class EngineUtils
{
    /* Create Handler Type */
    DECLARE_INSTANCE_HANDLER_MULTICAST(CMulticastEventHandler, EngineUtils, SDL_Event);
    DECLARE_INSTANCE_HANDLER_SINGLE(CSingletEventHandler, bool, EngineUtils, SDL_Event);

    /* Create Handler Function Type */
    DECLARE_INSTACE_HANDLER_FUNCTION_MULTICAST(MuticastFunctionPtr, EngineUtils, SDL_Event);
    DECLARE_INSTACE_HANDLER_FUNCTION_SINGLE(SingleFunctionPtr, bool, EngineUtils, SDL_Event);

    using HandlerList = std::map<CMulticastHandlerListName, CMulticastEventHandler>;

public:
    EngineUtils()
    {
        Handlers[HList_KeyProcess] = key_process_handler;
        Handlers[HList_MouseProcess] = mouse_process_handler;
    }
    
    void Register();

    static EngineUtils* GetInstance();

    static void Free();

    static bool SetEvent(SDL_Event* InEvent);

    CMulticastEventHandler GetMuticastHandlers(CMulticastHandlerListName Handler_Name);

    CSingletEventHandler ImportHandler;

protected:

    static EngineUtils* engine_utils_;

    static SDL_Event* Event;
    
    HandlerList Handlers;

    CMulticastEventHandler key_process_handler;

    CMulticastEventHandler mouse_process_handler;

    CMulticastEventHandler drop_process_handler;

private:
    void KeyProcess(SDL_Event* Event);

    void MouseProcess(SDL_Event* Event);

    bool Import(SDL_Event* Event);
};
