#ifndef PRIMITIV_NODE_DEVICES_NAIVE_H
#define PRIMITIV_NODE_DEVICES_NAIVE_H

#include <nan.h>
#include <primitiv/primitiv.h>

#include "../Device.h"
#include "../function_wrapper.h"

namespace primitiv {

namespace node {

namespace devices {

class JsNaive : public Wrapper<primitiv::devices::Naive> {

public:
  JsNaive() : Wrapper(std::make_shared<primitiv::devices::Naive>()) {}

  static void register_functions(v8::Local<v8::Object> target);

  static NAN_METHOD(New);

  static Nan::Persistent<v8::FunctionTemplate> constructor;
};

} // namespace devices

} // namespace node

} // namespace primitiv

#endif  // PRIMITIV_NODE_DEVICES_NAIVE_H
