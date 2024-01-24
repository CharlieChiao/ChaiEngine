#include "CDelegate.h"
#include "Common.h"
#include <memory>

/* Important: Declare Template Class Here So The Template Function Can be Instantiation */
template class CDelegateMultiCast<GameLogic, SDL_Event>;
template class CDelegateMultiCast<EngineUtils, SDL_Event>;

template class CDelegateSingle<GameLogic, bool, SDL_Event>;
template class CDelegateSingle<EngineUtils, bool, SDL_Event>;

template <class C, typename ParamType>
bool CDelegateMultiCast<C, ParamType>::BindRaw(CInstanceHandler_MultiCast<C,ParamType> Handler)//, T InHandler)
{
    if(Handler.Instance && Handler.MuticastFunction)// && InHandler)
    {
        //InvocationList[InInsatance] = nullptr;//InHandler;
        InvocationList.push_back(Handler);
        return true;
    }else
    {
        return false;
    }
}

template <class C, typename ParamType>
void CDelegateMultiCast<C, ParamType>::Clear()
{
    InvocationList.clear();
}

template <class C, typename ParamType>
void CDelegateMultiCast<C, ParamType>::BoardCast()//SDL_Event Event)
{
    for (auto func : InvocationList)
    {
        func.ExecuteIfBound();
    }
}

template <class C, typename RetType, typename ParamType>
bool CDelegateSingle<C, RetType, ParamType>::BindRaw(CInstanceHandler_Single<C, RetType, ParamType> Handler)
{
    if(Handler.Instance && Handler.SingleFunction)// && InHandler)
        {
            InvocationFunction = Handler;
            return true;
        }else
        {
            return false;
        }
}

template <class C, typename RetType, typename ParamType>
void CDelegateSingle<C, RetType, ParamType>::Clear()
{
    
}

template <class C, typename RetType, typename ParamType>
RetType CDelegateSingle<C, RetType, ParamType>::ExecuteIfBound()
{
    return InvocationFunction.ExecuteIfBound_Single();
}
