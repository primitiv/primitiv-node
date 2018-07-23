#ifndef PRIMITIV_NODE_INITIALIZERS_UNIFORM_H
#define PRIMITIV_NODE_INITIALIZERS_UNIFORM_H

#include <nan.h>
#include <primitiv/primitiv.h>

#include "../Initializer.h"
#include "../function_wrapper.h"

namespace primitiv {

namespace node {

namespace initializers {

class JsUniform : public Wrapper<primitiv::initializers::Uniform> {
  JsUniform() = delete;
public:
  explicit JsUniform(float lower, float upper) : Wrapper(std::make_shared<primitiv::initializers::Uniform>(lower, upper)) {}

  static void register_functions(v8::Local<v8::Object> target);

  static NAN_METHOD(New);

  static Nan::Persistent<v8::FunctionTemplate> constructor;
};

} // namespace initializers

} // namespace node

} // namespace primitiv

#endif  // PRIMITIV_NODE_INITIALIZERS_UNIFORM_H
