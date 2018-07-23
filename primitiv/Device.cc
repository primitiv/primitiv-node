#include <nan.h>

#include "Device.h"

#include "function_wrapper.h"

namespace primitiv {

namespace node {

void JsDevice::register_functions(v8::Local<v8::Object> target) {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);

  auto classname = Nan::New("Device").ToLocalChecked();

  tpl->SetClassName(classname);
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  Nan::SetMethod(tpl, "get_default", GetDefault);
  Nan::SetMethod(tpl, "set_default", SetDefault);

  Nan::SetPrototypeMethod(tpl, "dump_description", DumpDescription);

  constructor.Reset(tpl);
  Nan::Set(target, classname, Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(JsDevice::New) {
  Nan::ThrowError("not supported operation.");
}

NAN_METHOD(JsDevice::GetDefault) {
  if (default_object != nullptr) {
    info.GetReturnValue().Set(default_object->handle());
  } else {
    Nan::ThrowError("Default object is null.");
  }
}

NAN_METHOD(JsDevice::SetDefault) {
  if (Nan::New(JsDevice::constructor)->HasInstance(info[0])) {
    default_object = Nan::ObjectWrap::Unwrap<JsDevice>(info[0]->ToObject());
  } else {
    PRIMITIV_THROW_ERROR("invalid arguments");
  }
}

PRIMITIV_NODE_FUNCTION_WRAPPER_NORETURN(JsDevice, DumpDescription, dump_description)

Nan::Persistent<v8::FunctionTemplate> JsDevice::constructor;
JsDevice* JsDevice::default_object;

} // namespace node

} // namespace primitiv

