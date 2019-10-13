#pragma once

#include <napi.h>
#include <stdlib.h>
#include "core/Component/component_macro.h"

template <typename ComponentType>
class NGGenericComponentWrap : public Napi::ObjectWrap<NGGenericComponentWrap> {
 private:
  std::unique_ptr<ComponentType> instance;

 public:
  static Napi::FunctionReference constructor;
  static Napi::Object init(Napi::Env env, Napi::Object exports);
  NGGenericComponentWrap(const Napi::CallbackInfo& info);
  ~NGGenericComponentWrap();
  ComponentType* getInternalInstance();
  // Wrapped methods
  Napi::Value invoke(const Napi::CallbackInfo& info);
};
