#include <nan.h>

#include "Device.h"
#include "Shape.h"
#include "Tensor.h"

#include "function_wrapper.h"

namespace primitiv {

namespace node {

void JsTensor::register_functions(v8::Local<v8::Object> target) {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);

  auto classname = Nan::New("Tensor").ToLocalChecked();

  tpl->SetClassName(classname);
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(tpl, "valid", Valid);
  Nan::SetPrototypeMethod(tpl, "shape", Shape);
  Nan::SetPrototypeMethod(tpl, "device", Device);
  Nan::SetPrototypeMethod(tpl, "to_float", ToFloat);
  Nan::SetPrototypeMethod(tpl, "to_array", ToArray);
  Nan::SetPrototypeMethod(tpl, "argmax", Argmax);
  Nan::SetPrototypeMethod(tpl, "argmin", Argmin);
  Nan::SetPrototypeMethod(tpl, "invalidate", Invalidate);
  Nan::SetPrototypeMethod(tpl, "reset", Reset);
  Nan::SetPrototypeMethod(tpl, "reset_by_array", ResetByArray);
  Nan::SetPrototypeMethod(tpl, "reshape", Reshape);
  Nan::SetPrototypeMethod(tpl, "flatten", Flatten);
  Nan::SetPrototypeMethod(tpl, "inplace_multiply_const", InplaceMultiplyConst);
  Nan::SetPrototypeMethod(tpl, "inplace_add", InplaceAdd);
  Nan::SetPrototypeMethod(tpl, "inplace_subtract", InplaceSubtract);

  constructor.Reset(tpl);
  Nan::Set(target, classname, Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(JsTensor::New) {
  try {
    if (info.IsConstructCall()) {
      JsTensor *obj = new JsTensor();
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

PRIMITIV_NODE_FUNCTION_WRAPPER(JsTensor, Valid, valid, v8::Boolean)
PRIMITIV_NODE_FUNCTION_WRAPPER(JsTensor, Shape, shape, JsShape)
PRIMITIV_NODE_FUNCTION_WRAPPER(JsTensor, Device, device, JsDevice)
PRIMITIV_NODE_FUNCTION_WRAPPER(JsTensor, ToFloat, to_float, v8::Number)

NAN_METHOD(JsTensor::ToArray) {
  JsTensor* obj = Nan::ObjectWrap::Unwrap<JsTensor>(info.Holder());
  try {
    auto result = obj->wrapped_->to_vector();
    auto result_arr = vector_to_jsarray(result);
    info.GetReturnValue().Set(result_arr);
  } catch (const primitiv::Error& e) {
    Nan::ThrowError(e.what());
  }
}

NAN_METHOD(JsTensor::Argmax) {
  JsTensor* obj = Nan::ObjectWrap::Unwrap<JsTensor>(info.Holder());
  try {
    auto result = obj->wrapped_->argmax(unwrap<std::uint32_t>(info[0]));
    auto result_arr = vector_to_jsarray(result);
    info.GetReturnValue().Set(result_arr);
  } catch (const primitiv::Error& e) {
    Nan::ThrowError(e.what());
  }
}

NAN_METHOD(JsTensor::Argmin) {
  JsTensor* obj = Nan::ObjectWrap::Unwrap<JsTensor>(info.Holder());
  try {
    auto result = obj->wrapped_->argmin(unwrap<std::uint32_t>(info[0]));
    auto result_arr = vector_to_jsarray(result);
    info.GetReturnValue().Set(result_arr);
  } catch (const primitiv::Error& e) {
    Nan::ThrowError(e.what());
  }
}

PRIMITIV_NODE_FUNCTION_WRAPPER_NORETURN(JsTensor, Invalidate, invalidate)
PRIMITIV_NODE_FUNCTION_WRAPPER_ARG1_NORETURN(JsTensor, Reset, reset, float)
PRIMITIV_NODE_FUNCTION_WRAPPER_ARG1_NORETURN(JsTensor, ResetByArray, reset_by_vector, std::vector<float>)
PRIMITIV_NODE_FUNCTION_WRAPPER_ARG1(JsTensor, Reshape, reshape, JsTensor, JsShape)
PRIMITIV_NODE_FUNCTION_WRAPPER(JsTensor, Flatten, flatten, JsTensor)
PRIMITIV_NODE_FUNCTION_WRAPPER_ARG1(JsTensor, InplaceMultiplyConst, inplace_multiply_const, JsTensor, float)
PRIMITIV_NODE_FUNCTION_WRAPPER_ARG1(JsTensor, InplaceAdd, inplace_add, JsTensor, JsTensor)
PRIMITIV_NODE_FUNCTION_WRAPPER_ARG1(JsTensor, InplaceSubtract, inplace_subtract, JsTensor, JsTensor)

Nan::Persistent<v8::FunctionTemplate> JsTensor::constructor;

} // namespace node

} // namespace primitiv

