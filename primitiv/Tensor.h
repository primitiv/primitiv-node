#ifndef PRIMITIV_NODE_TENSOR_H
#define PRIMITIV_NODE_TENSOR_H

#include <nan.h>
#include <primitiv/primitiv.h>

#include "function_wrapper.h"

namespace primitiv {

namespace node {

class JsTensor : public Wrapper<primitiv::Tensor> {

public:
  JsTensor() : Wrapper(std::make_shared<primitiv::Tensor>()) {}
  explicit JsTensor(const primitiv::Tensor &tensor) : Wrapper(std::make_shared<primitiv::Tensor>(tensor)) {}
  explicit JsTensor(primitiv::Tensor &tensor) : Wrapper(tensor) {}
  explicit JsTensor(primitiv::Tensor &&tensor) : Wrapper(std::make_shared<primitiv::Tensor>(std::forward<primitiv::Tensor>(tensor))) {}
  ~JsTensor() {}

  static void register_functions(v8::Local<v8::Object> target);

  static inline v8::Local<v8::Object> wrap_cpp(const primitiv::Tensor& tensor) {
    auto wrapper = new JsTensor(tensor);
    v8::Local<v8::Function> cons = Nan::GetFunction(Nan::New(constructor)).ToLocalChecked();
    auto instance = Nan::NewInstance(cons).ToLocalChecked();
    wrapper->Wrap(instance);
    return instance;
  }

  static inline v8::Local<v8::Object> wrap_cpp(primitiv::Tensor& tensor) {
    auto wrapper = new JsTensor(tensor);
    return wrapper->handle();
  }

  static inline v8::Local<v8::Object> wrap_cpp(primitiv::Tensor&& tensor) {
    auto wrapper = new JsTensor(std::forward<primitiv::Tensor>(tensor));
    v8::Local<v8::Function> cons = Nan::GetFunction(Nan::New(constructor)).ToLocalChecked();
    auto instance = Nan::NewInstance(cons).ToLocalChecked();
    wrapper->Wrap(instance);
    return instance;
  }

  static NAN_METHOD(New);
  static NAN_METHOD(Valid);
  static NAN_METHOD(Shape);
  static NAN_METHOD(Device);
  static NAN_METHOD(ToFloat);
  static NAN_METHOD(ToArray);
  static NAN_METHOD(Argmax);
  static NAN_METHOD(Argmin);
  static NAN_METHOD(Invalidate);
  static NAN_METHOD(Reset);
  static NAN_METHOD(ResetByArray);
  static NAN_METHOD(Reshape);
  static NAN_METHOD(Flatten);
  static NAN_METHOD(InplaceMultiplyConst);
  static NAN_METHOD(InplaceAdd);
  static NAN_METHOD(InplaceSubtract);

  static Nan::Persistent<v8::FunctionTemplate> constructor;

};

} // namespace node

} // namespace primitiv

#endif  // PRIMITIV_NODE_TENSOR_H
