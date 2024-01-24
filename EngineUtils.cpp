#include "EngineUtils.h"

#include "Common.h"

void EngineUtils::Register()
{
    MuticastFunctionPtr KeyFuncPtr = &EngineUtils::KeyProcess;
    MuticastFunctionPtr MouseFuncPtr = &EngineUtils::MouseProcess;
    SingleFunctionPtr ImportFunction = &EngineUtils::Import;
    REGISTER_HANDLER_MULTICAST(Handlers, HList_KeyProcess, KeyFuncPtr, engine_utils_, Event);
    REGISTER_HANDLER_MULTICAST(Handlers, HList_MouseProcess, MouseFuncPtr, engine_utils_, Event);
    REGISTER_HANDLER_SINGLE(ImportHandler, ImportFunction, engine_utils_, Event);
}

EngineUtils* EngineUtils::engine_utils_ = nullptr;
SDL_Event* EngineUtils::Event = nullptr;

EngineUtils* EngineUtils::GetInstance()
{
    if(!engine_utils_)
    {
        engine_utils_ = new EngineUtils();
    }
    return engine_utils_;
}

void EngineUtils::Free()
{
    if(engine_utils_)
    {
        delete engine_utils_;
    }
}

bool EngineUtils::SetEvent(SDL_Event* InEvent)
{
    if(!Event)
    {
        if(InEvent)
        {
            Event = InEvent;
            return true;
        }else
        {
            return false;
        }
            
    }
    return false;
}

EngineUtils::CMulticastEventHandler EngineUtils::GetMuticastHandlers(CMulticastHandlerListName Handler_Name)
{
    return Handlers[Handler_Name];
}

void EngineUtils::KeyProcess(SDL_Event* Event)
{
    HInput::KeyProcess((KeyCode)Event->key.keysym.sym, (KeyMod)Event->key.keysym.mod, (Action)Event->key.state);
}

void EngineUtils::MouseProcess(SDL_Event* Event)
{
    HInput::MouseProcess((MouseButton)Event->button.button, (Action)Event->button.state);
}

bool EngineUtils::Import(SDL_Event* Event)
{
    const char* File = Event->drop.data;
    CHARLIE_LOG(Log, "Import File Path is: %s", File);
    return true;
}
