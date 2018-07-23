#include <nan.h>

#include "Initializer.h"
#include "Tensor.h"

#include "function_wrapper.h"

namespace primitiv {

namespace node {

void JsInitializer::register_functions(v8::Local<v8::Object> target) {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);

  auto classname = Nan::New("Initializer").ToLocalChecked();

  tpl->SetClassName(classname);
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(tpl, "apply", Apply);

  constructor.Reset(tpl);
  Nan::Set(target, classname, Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(JsInitializer::New) {}

PRIMITIV_NODE_FUNCTION_WRAPPER_ARG1_NORETURN(JsInitializer, Apply, apply, JsTensor)

Nan::Persistent<v8::FunctionTemplate> JsInitializer::constructor;

} // namespace node

} // namespace primitiv

