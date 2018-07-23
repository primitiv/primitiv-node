#include <nan.h>

#include "Naive.h"

#include "../function_wrapper.h"

namespace primitiv {

namespace node {

namespace devices {

void JsNaive::register_functions(v8::Local<v8::Object> target) {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);

  auto classname = Nan::New("Naive").ToLocalChecked();

  tpl->SetClassName(classname);
  tpl->Inherit(Nan::New(JsDevice::constructor));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  constructor.Reset(tpl);
  Nan::Set(target, classname, Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(JsNaive::New) {
  try {
    if (info.IsConstructCall()) {
      JsNaive *obj = new JsNaive();
      obj->Wrap(info.This());
      info.GetReturnValue().Set(info.This());
    } else {
      v8::Local<v8::Function> cons = Nan::GetFunction(Nan::New(constructor)).ToLocalChecked();
      info.GetReturnValue().Set(Nan::NewInstance(cons, 0, {}).ToLocalChecked());
    }
  } catch (const primitiv::Error& e) {
    Nan::ThrowError(e.what());
  }
}

Nan::Persistent<v8::FunctionTemplate> JsNaive::constructor;

} // namespace devices

} // namespace node

} // namespace primitiv

