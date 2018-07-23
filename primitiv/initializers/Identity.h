#ifndef PRIMITIV_NODE_INITIALIZERS_IDENTITY_H
#define PRIMITIV_NODE_INITIALIZERS_IDENTITY_H

#include <nan.h>
#include <primitiv/primitiv.h>

#include "../Initializer.h"
#include "../function_wrapper.h"

namespace primitiv {

namespace node {

namespace initializers {

class JsIdentity : public Wrapper<primitiv::initializers::Identity> {

public:
  explicit JsIdentity() : Wrapper(std::make_shared<primitiv::initializers::Identity>()) {}

  static void register_functions(v8::Local<v8::Object> target);

  static NAN_METHOD(New);

  static Nan::Persistent<v8::FunctionTemplate> constructor;
};

} // namespace initializers

} // namespace node

} // namespace primitiv

#endif  // PRIMITIV_NODE_INITIALIZERS_IDENTITY_H
