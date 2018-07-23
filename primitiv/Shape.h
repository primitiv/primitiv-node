#ifndef PRIMITIV_NODE_SHAPE_H
#define PRIMITIV_NODE_SHAPE_H

#include <nan.h>
#include <primitiv/primitiv.h>

#include "function_wrapper.h"

namespace primitiv {

namespace node {

class JsShape : public Wrapper<primitiv::Shape> {

public:
  JsShape(std::vector<std::uint32_t> dims, std::uint32_t batch) : Wrapper(std::make_shared<primitiv::Shape>(dims, batch)) {}
  explicit JsShape(primitiv::Shape &shape) : Wrapper(shape) {}
  explicit JsShape(primitiv::Shape &&shape) : Wrapper(std::make_shared<primitiv::Shape>(std::forward<primitiv::Shape>(shape))) {}
  ~JsShape() {}

  static void register_functions(v8::Local<v8::Object> target);

  static inline v8::Local<v8::Object> wrap_cpp(primitiv::Shape& shape) {
    auto wrapper = new JsShape(shape);
    return wrapper->handle();
  }

  static inline v8::Local<v8::Object> wrap_cpp(primitiv::Shape&& shape) {
    auto wrapper = new JsShape(std::forward<primitiv::Shape>(shape));
    v8::Local<v8::Function> cons = Nan::GetFunction(Nan::New(constructor)).ToLocalChecked();
    auto instance = Nan::NewInstance(cons).ToLocalChecked();
    wrapper->Wrap(instance);
    return instance;
  }

  static NAN_METHOD(New);
  static NAN_METHOD(Dims);
  static NAN_METHOD(Depth);
  static NAN_METHOD(Batch);
  static NAN_METHOD(Volume);
  static NAN_METHOD(LowerVolume);
  static NAN_METHOD(Size);
  static NAN_METHOD(ToString);
  static NAN_METHOD(HasBatch);
  static NAN_METHOD(HasCompatibleBatch);
  static NAN_METHOD(IsScalar);
  static NAN_METHOD(IsColumnVector);
  static NAN_METHOD(IsMatrix);
  static NAN_METHOD(HasSameDims);
  static NAN_METHOD(HasSameLooDims);
  static NAN_METHOD(ResizeDim);
  static NAN_METHOD(ResizeBatch);
  static NAN_METHOD(UpdateDim);
  static NAN_METHOD(UpdateBatch);

  static Nan::Persistent<v8::FunctionTemplate> constructor;

};

} // namespace node

} // namespace primitiv

#endif  // PRIMITIV_NODE_SHAPE_H
