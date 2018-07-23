#ifndef PRIMITIV_NODE_INITIALIZERS_XAVIERUNIFORMCONV2D_H
#define PRIMITIV_NODE_INITIALIZERS_XAVIERUNIFORMCONV2D_H

#include <nan.h>
#include <primitiv/primitiv.h>

#include "../Initializer.h"
#include "../function_wrapper.h"

namespace primitiv {

namespace node {

namespace initializers {

class JsXavierUniformConv2D : public Wrapper<primitiv::initializers::XavierUniformConv2D> {
  JsXavierUniformConv2D() = delete;
public:
  explicit JsXavierUniformConv2D(float scale) : Wrapper(std::make_shared<primitiv::initializers::XavierUniformConv2D>(scale)) {}

  static void register_functions(v8::Local<v8::Object> target);

  static NAN_METHOD(New);

  static Nan::Persistent<v8::FunctionTemplate> constructor;
};

} // namespace initializers

} // namespace node

} // namespace primitiv

#endif  // PRIMITIV_NODE_INITIALIZERS_XAVIERUNIFORMCONV2D_H
