#include <nan.h>

#include "Normal.h"

#include "../function_wrapper.h"

namespace primitiv {

namespace node {

namespace initializers {

void JsNormal::register_functions(v8::Local<v8::Object> target) {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);

  auto classname = Nan::New("Normal").ToLocalChecked();

  tpl->SetClassName(classname);
  tpl->Inherit(Nan::New(JsInitializer::constructor));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  constructor.Reset(tpl);
  Nan::Set(target, classname, Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(JsNormal::New) {
  try {
    if (info.IsConstructCall()) {
      auto mean = unwrap<float>(info[0]);
      auto sd = unwrap<float>(info[1]);
      JsNormal *obj = new JsNormal(mean, sd);
      obj->Wrap(info.This());
      info.GetReturnValue().Set(info.This());
    } else {
      v8::Local<v8::Function> cons = Nan::GetFunction(Nan::New(constructor)).ToLocalChecked();
      v8::Local<v8::Value> argv[] = { info[0], info[1] };
      info.GetReturnValue().Set(Nan::NewInstance(cons, 2, argv).ToLocalChecked());
    }
  } catch (const primitiv::Error& e) {
    Nan::ThrowError(e.what());
  }
}

Nan::Persistent<v8::FunctionTemplate> JsNormal::constructor;

} // namespace initializers

} // namespace node

} // namespace primitiv

