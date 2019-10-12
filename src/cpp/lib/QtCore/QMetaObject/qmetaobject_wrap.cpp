#include "QtCore/QMetaObject/qmetaobject_wrap.h"
#include <QObject>

Napi::FunctionReference QMetaObjectWrap::constructor;

Napi::Object QMetaObjectWrap::init(Napi::Env env, Napi::Object exports)
{
  Napi::HandleScope scope(env);
  char CLASSNAME[] = "QMetaObject";
  Napi::Function func = DefineClass(
      env,
      CLASSNAME,
      {InstanceMethod("className", &QMetaObjectWrap::className),
       InstanceMethod("methodCount", &QMetaObjectWrap::methodCount),
       COMPONENT_WRAPPED_METHODS_EXPORT_DEFINE});
  constructor = Napi::Persistent(func);
  exports.Set(CLASSNAME, func);
  return exports;
}

QObject *QMetaObjectWrap::getInternalInstance()
{
  return this->instance;
}

QMetaObjectWrap::QMetaObjectWrap(const Napi::CallbackInfo &info)
    : Napi::ObjectWrap<QMetaObjectWrap>(info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if (info[0].IsExternal())
  {
    this->instance = info[0].As<Napi::External<QObject>>().Data();
  }
  else
  {
    Napi::TypeError::New(env, "Incorrect initialization of QClipboardWrap").ThrowAsJavaScriptException();
  }
}

QMetaObjectWrap::~QMetaObjectWrap() {}

Napi::Value QMetaObjectWrap::className(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  const char *className = this->instance->metaObject()->className();
  return Napi::Value::From(env, className);
}

Napi::Value QMetaObjectWrap::methodCount(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  int count = this->instance->metaObject()->methodCount();
  return Napi::Value::From(env, count);
}
