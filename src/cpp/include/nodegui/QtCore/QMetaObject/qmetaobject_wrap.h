#pragma once

#include "core/Component/component_macro.h"
#include <QMetaObject>
#include <napi.h>

class QMetaObjectWrap : public Napi::ObjectWrap<QMetaObjectWrap>
{
private:
    QObject *instance;

public:
    static Napi::FunctionReference constructor;
    static Napi::Object init(Napi::Env env, Napi::Object exports);
    QMetaObjectWrap(const Napi::CallbackInfo &info);
    ~QMetaObjectWrap();
    QObject *getInternalInstance();
    //Member functions
    Napi::Value className(const Napi::CallbackInfo &info);
    Napi::Value methodCount(const Napi::CallbackInfo &info);
};
