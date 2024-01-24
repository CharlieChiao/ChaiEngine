#pragma once

#define DECLARE_INSTANCE_HANDLER_MULTICAST( HandlerName, ClassName, ParamType ) \
typedef CInstanceHandler_MultiCast<ClassName,ParamType> HandlerName

#define DECLARE_INSTACE_HANDLER_FUNCTION_MULTICAST( FunctionTypeName, ClassName, ParamType ) \
typedef FunctionPointerType_MultiCast<ClassName,ParamType> FunctionTypeName

#define DECLARE_INSTANCE_HANDLER_SINGLE( HandlerName, RetType, ClassName, ParamType ) \
typedef CInstanceHandler_Single<ClassName,RetType,ParamType> HandlerName

#define DECLARE_INSTACE_HANDLER_FUNCTION_SINGLE( FunctionTypeName, RetType, ClassName, ParamType ) \
typedef FunctionPointerType_Single<ClassName,RetType,ParamType> FunctionTypeName

template <class C, typename ParamType>
using FunctionPointerType_MultiCast = void (C::*)(ParamType*);

template <class C, typename RetType, typename ParamType>
using FunctionPointerType_Single = RetType (C::*)(ParamType*);


template <class C, typename ParamType>
class CHandlerBase
{
public:
    
    FunctionPointerType_MultiCast<C, ParamType> MuticastFunction;
    ParamType* Param;

    CHandlerBase()
    {
        MuticastFunction = nullptr;
        Param = nullptr;
    }

    virtual ~CHandlerBase() {}

    virtual void ExecuteIfBound() = 0;
};

template <class C, typename ParamType>
class CInstanceHandler_MultiCast : public CHandlerBase<C, ParamType>
{
public:
    C* Instance;
    
    CInstanceHandler_MultiCast() : CHandlerBase<C, ParamType>(), Instance(nullptr) {}

    ~CInstanceHandler_MultiCast() override {}

    void Set(C* InInstance, FunctionPointerType_MultiCast<C, ParamType> Function, ParamType* Param) {
        Instance = InInstance;
        this->MuticastFunction = Function;
        this->Param = Param;
    }

    void ExecuteIfBound() override {
        if (Instance && this->MuticastFunction) {
            (Instance->*this->MuticastFunction)(this->Param);
        }
    }
};

template <class C, typename RetType, typename ParamType>
class CInstanceHandler_Single : public CHandlerBase<C, ParamType>
{
public:
    C* Instance;
    FunctionPointerType_Single<C, RetType, ParamType> SingleFunction;
    
    CInstanceHandler_Single() : CHandlerBase<C, ParamType>(), Instance(nullptr) {}

    ~CInstanceHandler_Single() override {}

    void Set(C* InInstance, FunctionPointerType_Single<C, RetType, ParamType> Function, ParamType* Param) {
        Instance = InInstance;
        this->SingleFunction = Function;
        this->Param = Param;
    }

    void ExecuteIfBound() override {}
    
    RetType ExecuteIfBound_Single()
    {
        RetType Out;
        if (Instance && SingleFunction) {
            Out = (Instance->*SingleFunction)(this->Param);
        }
        return Out;
    }
};