#include "Common.h"

std::string format_string(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    int len = std::vsnprintf(nullptr, 0, format, args);
    va_end(args);

    std::string result(len, '\0');
    va_start(args, format);
    std::vsnprintf(&result[0], len + 1, format, args);
    va_end(args);

    return result;
}

GameLogic* GameLogic::gamelogic_ = nullptr;

GameLogic* GameLogic::Get()
{
    if(!gamelogic_)
    {
        gamelogic_ = new GameLogic();
    }
    return gamelogic_;
}

void GameLogic::Free()
{
    if(!gamelogic_)
    {
        delete gamelogic_;
    }
}

bool GameLogic::GameLogic_Loop()
{
    static SDL_Event event;
    engine = EngineUtils::GetInstance();
    engine->SetEvent(&event);
    engine->Register();
    bool Success = true;
    
    while(SDL_PollEvent(&event))
    {
        Success = RunLogic(&event);
    }
    
    return !Success;
}

bool GameLogic::RunLogic(SDL_Event* event)
{
    bool result = true;
    auto logicType = static_cast<SDL_EventType>(event->type);
    auto it = eventHandlers.find(logicType);
    if (it != eventHandlers.end())
    {
        EventHandler handler = it->second;
        result = (this->*handler)(event);
    }
    return result;
}

bool GameLogic::EventBeginPlay(SDL_Event* event)
{
    Event_Key_Delegate.BindRaw(engine->GetMuticastHandlers(HList_KeyProcess));
    Event_Mouse_Delegate.BindRaw(engine->GetMuticastHandlers(HList_MouseProcess));
    Event_Import_Delegate.BindRaw(engine->ImportHandler);
    return true;
}

bool GameLogic::EventKey(SDL_Event* event)
{
    Event_Key_Delegate.BoardCast();
    return true;
}

bool GameLogic::EventMouse(SDL_Event* event)
{
    Event_Mouse_Delegate.BoardCast();
    return true;
}

bool GameLogic::EventQuit(SDL_Event* event)
{
    return false;
}

bool GameLogic::EventDrop(SDL_Event* event)
{
    Event_Import_Delegate.ExecuteIfBound();
    return true;
}

/*void GameLogic::MouseProcess(SDL_Event* event)
{
    HInput::MouseProcess((MouseButton)event->button.button, (Action)event->button.state);
}

void GameLogic::KeyProcess(SDL_Event* event)
{
    HInput::KeyProcess((KeyCode)event->key.keysym.sym, (KeyMod)event->key.keysym.mod, (Action)event->key.state);
}*/


