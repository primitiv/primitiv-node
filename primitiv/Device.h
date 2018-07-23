#ifndef PRIMITIV_NODE_DEVICE_H
#define PRIMITIV_NODE_DEVICE_H

#include <nan.h>
#include <primitiv/primitiv.h>

#include "function_wrapper.h"

namespace primitiv {

namespace node {

class JsDevice : public Wrapper<primitiv::Device> {
  JsDevice() = delete;

public:
  explicit JsDevice(primitiv::Device &device) : Wrapper(device) {}

  static void register_functions(v8::Local<v8::Object> target);

  static inline v8::Local<v8::Object> wrap_cpp(primitiv::Device& device) {
    auto wrapper = new JsDevice(device);
    return wrapper->handle();
  }

  static NAN_METHOD(New);

  static NAN_METHOD(GetDefault);
  static NAN_METHOD(SetDefault);

  static NAN_METHOD(DumpDescription);

  static Nan::Persistent<v8::FunctionTemplate> constructor;
  static JsDevice* default_object;

};

} // namespace node

} // namespace primitiv

#endif  // PRIMITIV_NODE_DEVICE_H
