#include <nan.h>

#include "Parameter.h"
#include "Initializer.h"
#include "Tensor.h"

#include "function_wrapper.h"

namespace primitiv {

namespace node {

void JsParameter::register_functions(v8::Local<v8::Object> target) {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);

  auto classname = Nan::New("Parameter").ToLocalChecked();

  tpl->SetClassName(classname);
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(tpl, "init", Init);
  Nan::SetPrototypeMethod(tpl, "load", Load);
  Nan::SetPrototypeMethod(tpl, "save", Save);
  Nan::SetPrototypeMethod(tpl, "valid", Valid);
  Nan::SetPrototypeMethod(tpl, "reset_gradient", ResetGradient);
  Nan::SetPrototypeMethod(tpl, "add_stats", AddStats);
  Nan::SetPrototypeMethod(tpl, "has_stats", HasStats);
  Nan::SetPrototypeMethod(tpl, "shape", Shape);
  Nan::SetPrototypeMethod(tpl, "device", Device);
  Nan::SetPrototypeMethod(tpl, "value", Value);
  Nan::SetPrototypeMethod(tpl, "gradient", Gradient);
  Nan::SetPrototypeMethod(tpl, "stats", Stats);

  constructor.Reset(tpl);
  Nan::Set(target, classname, Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(JsParameter::New) {
  try {
    if (info.IsConstructCall()) {
      PRIMITIV_NODE_GET_DEVICE(2)
      JsParameter *obj;
      if (is_type_of<JsShape>(info[0]) && info[1]->IsArray()) {
        auto value_arr = v8::Local<v8::Array>::Cast(info[1]);
        obj = new JsParameter(unwrap<JsShape>(info[0]), jsarray_to_vector<float>(value_arr), device);
      } else if (is_type_of<JsShape>(info[0]) && is_type_of<JsInitializer>(info[1])) {
        obj = new JsParameter(unwrap<JsShape>(info[0]), unwrap<JsInitializer>(info[1]), device);
      } else {
        Nan::ThrowError("invalid arguments");
        return;
      }
      obj->Wrap(info.This());
      info.GetReturnValue().Set(info.This());
    } else {
      v8::Local<v8::Function> cons = Nan::GetFunction(Nan::New(constructor)).ToLocalChecked();
      v8::Local<v8::Value> argv[] = { info[0], info[1], info[2] };
      info.GetReturnValue().Set(Nan::NewInstance(cons, 3, argv).ToLocalChecked());
    }
  } catch (const primitiv::Error& e) {
    Nan::ThrowError(e.what());
  }
}

NAN_METHOD(JsParameter::Init) {
  JsParameter* obj = Nan::ObjectWrap::Unwrap<JsParameter>(info.Holder());
  PRIMITIV_NODE_GET_DEVICE(2)
  PRIMITIV_NODE_FUNCTION_DISPATCH_ARG2_NORETURN_EXT(obj->wrapped_->init, JsShape, std::vector<float>, device)
  PRIMITIV_NODE_FUNCTION_DISPATCH_ARG2_NORETURN_EXT(obj->wrapped_->init, JsShape, JsInitializer, device)
  PRIMITIV_NODE_FUNCTION_END_DISPATCH()
}

NAN_METHOD(JsParameter::Load) {
  JsParameter* obj = Nan::ObjectWrap::Unwrap<JsParameter>(info.Holder());
  PRIMITIV_NODE_GET_DEVICE(2)
  PRIMITIV_NODE_FUNCTION_DISPATCH_ARG2_NORETURN_EXT(obj->wrapped_->load, std::string, bool, device)
  PRIMITIV_NODE_FUNCTION_END_DISPATCH()
}

PRIMITIV_NODE_FUNCTION_WRAPPER_ARG2_NORETURN(JsParameter, Save, save, std::string, bool)
PRIMITIV_NODE_FUNCTION_WRAPPER(JsParameter, Valid, valid, v8::Boolean)
PRIMITIV_NODE_FUNCTION_WRAPPER_NORETURN(JsParameter, ResetGradient, reset_gradient)
PRIMITIV_NODE_FUNCTION_WRAPPER_ARG2_NORETURN(JsParameter, AddStats, add_stats, std::string, JsShape)
PRIMITIV_NODE_FUNCTION_WRAPPER_ARG1_NORETURN(JsParameter, HasStats, has_stats, std::string)
PRIMITIV_NODE_FUNCTION_WRAPPER(JsParameter, Shape, shape, JsShape)
PRIMITIV_NODE_FUNCTION_WRAPPER(JsParameter, Device, device, JsDevice)
PRIMITIV_NODE_FUNCTION_WRAPPER(JsParameter, Value, value, JsTensor)
PRIMITIV_NODE_FUNCTION_WRAPPER(JsParameter, Gradient, gradient, JsTensor)
PRIMITIV_NODE_FUNCTION_WRAPPER_ARG1(JsParameter, Stats, stats, JsTensor, std::string)

Nan::Persistent<v8::FunctionTemplate> JsParameter::constructor;

} // namespace node

} // namespace primitiv

