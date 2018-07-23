#include <nan.h>

#include "XavierNormal.h"

#include "../function_wrapper.h"

namespace primitiv {

namespace node {

namespace initializers {

void JsXavierNormal::register_functions(v8::Local<v8::Object> target) {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);

  auto classname = Nan::New("XavierNormal").ToLocalChecked();

  tpl->SetClassName(classname);
  tpl->Inherit(Nan::New(JsInitializer::constructor));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  constructor.Reset(tpl);
  Nan::Set(target, classname, Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(JsXavierNormal::New) {
  try {
    if (info.IsConstructCall()) {
      auto scale = info[0]->IsUndefined() ? 1.0 : unwrap<float>(info[0]);
      JsXavierNormal *obj = new JsXavierNormal(scale);
      obj->Wrap(info.This());
      info.GetReturnValue().Set(info.This());
    } else {
      v8::Local<v8::Function> cons = Nan::GetFunction(Nan::New(constructor)).ToLocalChecked();
      v8::Local<v8::Value> argv[] = { info[0] };
      info.GetReturnValue().Set(Nan::NewInstance(cons, 1, argv).ToLocalChecked());
    }
  } catch (const primitiv::Error& e) {
    Nan::ThrowError(e.what());
  }
}

Nan::Persistent<v8::FunctionTemplate> JsXavierNormal::constructor;

} // namespace initializers

} // namespace node

} // namespace primitiv

