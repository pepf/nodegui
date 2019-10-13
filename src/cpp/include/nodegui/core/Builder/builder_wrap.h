#pragma once

#include <napi.h>
#include <stdlib.h>
#include <QGenericArgument>
#include <QString>
#include "core/Component/component_macro.h"

template <typename ComponentType>
class NGGenericComponentWrap
    : public Napi::ObjectWrap<NGGenericComponentWrap<ComponentType>> {
 private:
  ComponentType* instance;

 public:
  static Napi::FunctionReference constructor;
  static Napi::Object init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    auto CLASSNAME = "QLabel";
    Napi::Function func = NGGenericComponentWrap::DefineClass(
        env, CLASSNAME,
        {
            // InstanceValue("val", Napi::Value::From(env, "323")),
            NGGenericComponentWrap::InstanceMethod(
                "invoke", &NGGenericComponentWrap<ComponentType>::invoke),
            //  COMPONENT_WRAPPED_METHODS_EXPORT_DEFINE
        });
    constructor = Napi::Persistent(func);
    exports.Set(CLASSNAME, func);
    return exports;
  };
  NGGenericComponentWrap(const Napi::CallbackInfo& info)
      : Napi::ObjectWrap<NGGenericComponentWrap<ComponentType>>(info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    this->instance = new ComponentType();
  }
  ~NGGenericComponentWrap() { delete this->instance; }
  ComponentType* getInternalInstance() { return this->instance; }

  // Wrapped methods
  Napi::Value invoke(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() == 1) {
      Napi::String methodName = info[0].As<Napi::String>();
      this->instance->metaObject()->invokeMethod(
          this->instance, methodName.Utf8Value().c_str());
    }
    if (info.Length() == 2) {
      Napi::String methodName = info[0].As<Napi::String>();
      Napi::String arg = info[1].As<Napi::String>();
      this->instance->metaObject()->invokeMethod(
          this->instance, methodName.Utf8Value().c_str(),
          Q_ARG(QString, arg.Utf8Value().c_str()));
    }
    return Napi::Boolean::New(env, false);
  }
};

template <typename ComponentType>
Napi::FunctionReference NGGenericComponentWrap<ComponentType>::constructor;
