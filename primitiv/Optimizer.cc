#include <nan.h>

#include "Optimizer.h"
#include "Parameter.h"
#include "Tensor.h"

#include "function_wrapper.h"

namespace primitiv {

namespace node {

void JsOptimizer::register_functions(v8::Local<v8::Object> target) {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);

  auto classname = Nan::New("Optimizer").ToLocalChecked();

  tpl->SetClassName(classname);
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(tpl, "load", Load);
  Nan::SetPrototypeMethod(tpl, "save", Save);
  Nan::SetPrototypeMethod(tpl, "get_epoch", GetEpoch);
  Nan::SetPrototypeMethod(tpl, "set_epoch", SetEpoch);
  Nan::SetPrototypeMethod(tpl, "get_learning_rate_scaling", GetLearningRateScaling);
  Nan::SetPrototypeMethod(tpl, "set_learning_rate_scaling", SetLearningRateScaling);
  Nan::SetPrototypeMethod(tpl, "get_weight_decay", GetWeightDecay);
  Nan::SetPrototypeMethod(tpl, "set_weight_decay", SetWeightDecay);
  Nan::SetPrototypeMethod(tpl, "get_gradient_clipping", GetGradientClipping);
  Nan::SetPrototypeMethod(tpl, "set_gradient_clipping", SetGradientClipping);
  Nan::SetPrototypeMethod(tpl, "add", Add);
  Nan::SetPrototypeMethod(tpl, "reset_gradients", ResetGradients);
  Nan::SetPrototypeMethod(tpl, "update", Update);
  Nan::SetPrototypeMethod(tpl, "get_configs", GetConfigs);
  Nan::SetPrototypeMethod(tpl, "set_configs", SetConfigs);

  constructor.Reset(tpl);
  Nan::Set(target, classname, Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(JsOptimizer::New) {}

PRIMITIV_NODE_FUNCTION_WRAPPER_ARG1_NORETURN(JsOptimizer, Load, load, std::string)
PRIMITIV_NODE_FUNCTION_WRAPPER_ARG1_NORETURN(JsOptimizer, Save, save, std::string)
PRIMITIV_NODE_FUNCTION_WRAPPER(JsOptimizer, GetEpoch, get_epoch, v8::Number)
PRIMITIV_NODE_FUNCTION_WRAPPER_ARG1_NORETURN(JsOptimizer, SetEpoch, set_epoch, std::uint32_t)
PRIMITIV_NODE_FUNCTION_WRAPPER(JsOptimizer, GetLearningRateScaling, get_learning_rate_scaling, v8::Number)
PRIMITIV_NODE_FUNCTION_WRAPPER_ARG1_NORETURN(JsOptimizer, SetLearningRateScaling, set_learning_rate_scaling, float)
PRIMITIV_NODE_FUNCTION_WRAPPER(JsOptimizer, GetWeightDecay, get_weight_decay, v8::Number)
PRIMITIV_NODE_FUNCTION_WRAPPER_ARG1_NORETURN(JsOptimizer, SetWeightDecay, set_weight_decay, float)
PRIMITIV_NODE_FUNCTION_WRAPPER(JsOptimizer, GetGradientClipping, get_gradient_clipping, v8::Number)
PRIMITIV_NODE_FUNCTION_WRAPPER_ARG1_NORETURN(JsOptimizer, SetGradientClipping, set_gradient_clipping, float)

NAN_METHOD(JsOptimizer::Add) {
  JsOptimizer* obj = Nan::ObjectWrap::Unwrap<JsOptimizer>(info.Holder());
  try {
    for (int i = 0; i < info.Length(); ++i) {
      if (!is_type_of<JsParameter>(info[i])) {
        Nan::ThrowError("invalid arguments");
        return;
      }
    }
    for (int i = 0; i < info.Length(); ++i) {
      obj->wrapped_->add(unwrap<JsParameter>(info[i]));
    }
  } catch (const primitiv::Error& e) {
    Nan::ThrowError(e.what());
  }
}

PRIMITIV_NODE_FUNCTION_WRAPPER_NORETURN(JsOptimizer, ResetGradients, reset_gradients)
PRIMITIV_NODE_FUNCTION_WRAPPER_NORETURN(JsOptimizer, Update, update)

NAN_METHOD(JsOptimizer::SetConfigs) {
  JsOptimizer* obj = Nan::ObjectWrap::Unwrap<JsOptimizer>(info.Holder());
  auto uint_configs = jsobject_to_map<std::uint32_t>(info[0]->ToObject());
  auto float_configs = jsobject_to_map<float>(info[1]->ToObject());
  try {
    obj->wrapped_->set_configs(uint_configs, float_configs);
  } catch (const primitiv::Error& e) {
    Nan::ThrowError(e.what());
  }
}

NAN_METHOD(JsOptimizer::GetConfigs) {
  JsOptimizer* obj = Nan::ObjectWrap::Unwrap<JsOptimizer>(info.Holder());
  std::unordered_map<std::string, std::uint32_t> uint_configs;
  std::unordered_map<std::string, float> float_configs;
  try {
    obj->wrapped_->get_configs(uint_configs, float_configs);
  } catch (const primitiv::Error& e) {
    Nan::ThrowError(e.what());
  }
  auto obj_uint_configs = Nan::New<v8::Object>();
  auto obj_float_configs = Nan::New<v8::Object>();
  for (auto it = uint_configs.begin(); it != uint_configs.end(); ++it) {
    Nan::Set(obj_uint_configs, Nan::New(it->first.c_str()).ToLocalChecked(), Nan::New<v8::Number>(it->second));
  }
  for (auto it = float_configs.begin(); it != float_configs.end(); ++it) {
    Nan::Set(obj_float_configs, Nan::New(it->first.c_str()).ToLocalChecked(), Nan::New<v8::Number>(it->second));
  }
  auto arr = Nan::New<v8::Array>(2);
  Nan::Set(arr, 0, obj_uint_configs);
  Nan::Set(arr, 1, obj_float_configs);
  info.GetReturnValue().Set(arr);
}

Nan::Persistent<v8::FunctionTemplate> JsOptimizer::constructor;

} // namespace node

} // namespace primitiv

