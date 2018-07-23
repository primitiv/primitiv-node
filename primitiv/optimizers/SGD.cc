#include <nan.h>

#include "SGD.h"

#include "../function_wrapper.h"

namespace primitiv {

namespace node {

namespace optimizers {

void JsSGD::register_functions(v8::Local<v8::Object> target) {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);

  auto classname = Nan::New("SGD").ToLocalChecked();

  tpl->SetClassName(classname);
  tpl->Inherit(Nan::New(JsOptimizer::constructor));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(tpl, "eta", Eta);

  constructor.Reset(tpl);
  Nan::Set(target, classname, Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(JsSGD::New) {
  try {
    if (info.IsConstructCall()) {
      auto eta = info[0]->IsUndefined() ? 0.1 : unwrap<float>(info[0]);
      auto *obj = new JsSGD(eta);
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

PRIMITIV_NODE_FUNCTION_WRAPPER(JsSGD, Eta, eta, v8::Number)

Nan::Persistent<v8::FunctionTemplate> JsSGD::constructor;

} // namespace optimizers

} // namespace node

} // namespace primitiv

