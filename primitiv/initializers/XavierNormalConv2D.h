#ifndef PRIMITIV_NODE_INITIALIZERS_XAVIERNORMALCONV2D_H
#define PRIMITIV_NODE_INITIALIZERS_XAVIERNORMALCONV2D_H

#include <nan.h>
#include <primitiv/primitiv.h>

#include "../Initializer.h"
#include "../function_wrapper.h"

namespace primitiv {

namespace node {

namespace initializers {

class JsXavierNormalConv2D : public Wrapper<primitiv::initializers::XavierNormalConv2D> {
  JsXavierNormalConv2D() = delete;
public:
  explicit JsXavierNormalConv2D(float scale) : Wrapper(std::make_shared<primitiv::initializers::XavierNormalConv2D>(scale)) {}

  static void register_functions(v8::Local<v8::Object> target);

  static NAN_METHOD(New);

  static Nan::Persistent<v8::FunctionTemplate> constructor;
};

} // namespace initializers

} // namespace node

} // namespace primitiv

#endif  // PRIMITIV_NODE_INITIALIZERS_XAVIERNORMALCONV2D_H
