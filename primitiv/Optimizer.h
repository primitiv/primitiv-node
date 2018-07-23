#ifndef PRIMITIV_NODE_OPTIMIZER_H
#define PRIMITIV_NODE_OPTIMIZER_H

#include <nan.h>

#include <primitiv/primitiv.h>

#include "function_wrapper.h"

namespace primitiv {

namespace node {

class JsOptimizer : public Wrapper<primitiv::Optimizer> {
  JsOptimizer() = delete;

public:
  explicit JsOptimizer(primitiv::Optimizer& optimizer) : Wrapper(optimizer) {}

  static void register_functions(v8::Local<v8::Object> target);

  static inline v8::Local<v8::Object> wrap_cpp(primitiv::Optimizer& optimizer) {
    auto wrapper = new JsOptimizer(optimizer);
    return wrapper->handle();
  }

  static NAN_METHOD(New);

  static NAN_METHOD(Load);
  static NAN_METHOD(Save);
  static NAN_METHOD(GetEpoch);
  static NAN_METHOD(SetEpoch);
  static NAN_METHOD(GetLearningRateScaling);
  static NAN_METHOD(SetLearningRateScaling);
  static NAN_METHOD(GetWeightDecay);
  static NAN_METHOD(SetWeightDecay);
  static NAN_METHOD(GetGradientClipping);
  static NAN_METHOD(SetGradientClipping);
  static NAN_METHOD(Add);
  static NAN_METHOD(ResetGradients);
  static NAN_METHOD(Update);
  static NAN_METHOD(GetConfigs);
  static NAN_METHOD(SetConfigs);

  static Nan::Persistent<v8::FunctionTemplate> constructor;

};

}  // namespace node

}  // namespace primitiv

#endif  // PRIMITIV_NODE_OPTIMIZER_H
