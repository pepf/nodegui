#include "core/Builder/builder_wrap.h"
#include "Extras/Utils/nutils.h"

Napi::FunctionReference NGGenericComponentWrap::constructor;

Napi::Object NGGenericComponentWrap::init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);
  char CLASSNAME[] = #ComponentType;
  Napi::Function func =
      DefineClass(env, CLASSNAME,
                  {InstanceMethod("newInstance", &NGGenericComponentWrap::load),
                   InstanceMethod("invoke", &NGGenericComponentWrap::save),
                   COMPONENT_WRAPPED_METHODS_EXPORT_DEFINE});
  constructor = Napi::Persistent(func);
  exports.Set(CLASSNAME, func);
  return exports;
}

NGGenericComponentWrap::NGGenericComponentWrap(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<NGGenericComponentWrap>(info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  if (info.Length() == 1) {
    if (info[0].IsExternal()) {
      this->instance = std::unique_ptr<ComponentType>(
          info[0].As<Napi::External<ComponentType>>().Data());
    } else {
      Napi::String url = info[0].As<Napi::String>();
      QString imageUrl = QString::fromUtf8(url.Utf8Value().c_str());
      this->instance = std::make_unique<ComponentType>(imageUrl);
    }
  } else if (info.Length() == 0) {
    this->instance = std::make_unique<ComponentType>();
  } else {
    Napi::TypeError::New(env, "Wrong number of arguments")
        .ThrowAsJavaScriptException();
  }
}

NGGenericComponentWrap::~NGGenericComponentWrap() { this->instance.reset(); }

ComponentType* NGGenericComponentWrap::getInternalInstance() { return this->instance.get(); }

Napi::Value NGGenericComponentWrap::invoke(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  Napi::String methodName = info[0].As<Napi::String>();

  if (info.Length() == 1) {
    QString imageUrl = QString::fromUtf8(url.Utf8Value().c_str());
    loadSuccess = this->instance->load(imageUrl);
  } else {
    Napi::TypeError::New(env, "Wrong number of arguments")
        .ThrowAsJavaScriptException();
  }
  return Napi::Boolean::New(env, loadSuccess);
}
