#pragma once
#include <functional>
#include <map>
#include <vector>
#include "SDL3/SDL.h"
#include "EngineUtils.h"
#include "CFunctionHandler.h"

#define FUNC_DECLARE_DELEGATE_MUTICAST( DelegateName, ClassName, ParamType ) \
    typedef CDelegateMultiCast<ClassName, ParamType> DelegateName

#define DECLARE_MULTICAST_DELEGATE_RetVal_OneParam( DelegateName, ClassName, ParamType ) \
    FUNC_DECLARE_DELEGATE_MUTICAST ( DelegateName, ClassName, ParamType )

#define FUNC_DECLARE_DELEGATE_SINGLE( DelegateName, ClassName, RetType, ParamType ) \
typedef CDelegateSingle<ClassName, RetType, ParamType> DelegateName

#define DECLARE_SINGLE_DELEGATE_RetVal_OneParam( DelegateName, ClassName, RetType, ParamType ) \
FUNC_DECLARE_DELEGATE_SINGLE ( DelegateName, ClassName, RetType, ParamType )



/*template<typename T1, typename T2>
struct TypeMatched {
    static constexpr bool value = false;
};

template<typename T>
struct TypeMatched<T, T> {
    static constexpr bool value = true;
};*/

template <class C, typename ParamType>
class CDelegateMultiCast
{
protected:
    //typedef void (C::*EventHandler)(ParamType);
    
    using InvocationListType = std::vector<CInstanceHandler_MultiCast<C,ParamType>>;
    
public:
    CDelegateMultiCast() = default;

    ~CDelegateMultiCast()
    {
        Clear();
    }

    bool BindRaw(CInstanceHandler_MultiCast<C,ParamType> Handler);//, T InHandler);

    void Clear();

    void BoardCast();//SDL_Event Event);

private:
    InvocationListType InvocationList;
};

template <class C, typename RetType, typename ParamType>
class CDelegateSingle
{
protected:
    using InvocationFunctionPtr = CInstanceHandler_Single<C, RetType, ParamType>;

public:
    CDelegateSingle() = default;

    ~CDelegateSingle()
    {
        Clear();
    }

    bool BindRaw(CInstanceHandler_Single<C,RetType,ParamType> Handler);//, T InHandler);

    void Clear();

    RetType ExecuteIfBound();
    
private:
    InvocationFunctionPtr InvocationFunction;
    
};


