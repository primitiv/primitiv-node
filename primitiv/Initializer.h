#ifndef PRIMITIV_NODE_INITIALIZER_H
#define PRIMITIV_NODE_INITIALIZER_H

#include <nan.h>

#include <primitiv/primitiv.h>

#include "function_wrapper.h"

namespace primitiv {

namespace node {

class JsInitializer : public Wrapper<primitiv::Initializer> {
  JsInitializer() = delete;

public:
  explicit JsInitializer(primitiv::Initializer& initializer) : Wrapper(initializer) {}

  static void register_functions(v8::Local<v8::Object> target);

  static inline v8::Local<v8::Object> wrap_cpp(primitiv::Initializer& initializer) {
    auto wrapper = new JsInitializer(initializer);
    return wrapper->handle();
  }

  static NAN_METHOD(New);

  static NAN_METHOD(Apply);

  static Nan::Persistent<v8::FunctionTemplate> constructor;

};

}  // namespace node

}  // namespace primitiv

#endif  // PRIMITIV_NODE_INITIALIZER_H
