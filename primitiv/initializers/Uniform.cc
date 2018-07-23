#include <nan.h>

#include "Uniform.h"

#include "../function_wrapper.h"

namespace primitiv {

namespace node {

namespace initializers {

void JsUniform::register_functions(v8::Local<v8::Object> target) {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);

  auto classname = Nan::New("Uniform").ToLocalChecked();

  tpl->SetClassName(classname);
  tpl->Inherit(Nan::New(JsInitializer::constructor));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  constructor.Reset(tpl);
  Nan::Set(target, classname, Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(JsUniform::New) {
  try {
    if (info.IsConstructCall()) {
      auto lower = unwrap<float>(info[0]);
      auto upper = unwrap<float>(info[1]);
      JsUniform *obj = new JsUniform(lower, upper);
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

Nan::Persistent<v8::FunctionTemplate> JsUniform::constructor;

} // namespace initializers

} // namespace node

} // namespace primitiv

