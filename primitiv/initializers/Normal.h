#ifndef PRIMITIV_NODE_INITIALIZERS_NORMAL_H
#define PRIMITIV_NODE_INITIALIZERS_NORMAL_H

#include <nan.h>
#include <primitiv/primitiv.h>

#include "../Initializer.h"
#include "../function_wrapper.h"

namespace primitiv {

namespace node {

namespace initializers {

class JsNormal : public Wrapper<primitiv::initializers::Normal> {
  JsNormal() = delete;
public:
  explicit JsNormal(float mean, float sd) : Wrapper(std::make_shared<primitiv::initializers::Normal>(mean, sd)) {}

  static void register_functions(v8::Local<v8::Object> target);

  static NAN_METHOD(New);

  static Nan::Persistent<v8::FunctionTemplate> constructor;
};

} // namespace initializers

} // namespace node

} // namespace primitiv

#endif  // PRIMITIV_NODE_INITIALIZERS_NORMAL_H
