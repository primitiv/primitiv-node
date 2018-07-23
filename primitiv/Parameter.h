#ifndef PRIMITIV_NODE_PARAMETER_H
#define PRIMITIV_NODE_PARAMETER_H

#include <nan.h>
#include <primitiv/primitiv.h>

#include "Device.h"
#include "Shape.h"
#include "function_wrapper.h"

namespace primitiv {

namespace node {

class JsParameter : public Wrapper<primitiv::Parameter> {
  JsParameter() = delete;

public:
  JsParameter(primitiv::Shape &shape, const std::vector<float> &value, primitiv::Device *device) : Wrapper(std::make_shared<primitiv::Parameter>(shape, value, device)) {}
  JsParameter(primitiv::Shape &shape, const primitiv::Initializer &initializer, primitiv::Device *device) : Wrapper(std::make_shared<primitiv::Parameter>(shape, initializer, device)) {}
  explicit JsParameter(primitiv::Parameter &parameter) : Wrapper(parameter) {}
  ~JsParameter() {}

  static void register_functions(v8::Local<v8::Object> target);

  static inline v8::Local<v8::Object> wrap_cpp(primitiv::Parameter& parameter) {
    auto wrapper = new JsParameter(parameter);
    return wrapper->handle();
  }

  static NAN_METHOD(New);
  static NAN_METHOD(Init);
  static NAN_METHOD(Load);
  static NAN_METHOD(Save);
  static NAN_METHOD(Valid);
  static NAN_METHOD(ResetGradient);
  static NAN_METHOD(AddStats);
  static NAN_METHOD(HasStats);
  static NAN_METHOD(Shape);
  static NAN_METHOD(Device);
  static NAN_METHOD(Value);
  static NAN_METHOD(Gradient);
  static NAN_METHOD(Stats);

  static Nan::Persistent<v8::FunctionTemplate> constructor;

};

} // namespace node

} // namespace primitiv

#endif  // PRIMITIV_NODE_PARAMETER_H
