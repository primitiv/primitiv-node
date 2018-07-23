#include <nan.h>

#include "Shape.h"

#include "function_wrapper.h"

namespace primitiv {

namespace node {

void JsShape::register_functions(v8::Local<v8::Object> target) {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);

  auto classname = Nan::New("Shape").ToLocalChecked();

  tpl->SetClassName(classname);
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(tpl, "dims", Dims);
  Nan::SetPrototypeMethod(tpl, "depth", Depth);
  Nan::SetPrototypeMethod(tpl, "batch", Batch);
  Nan::SetPrototypeMethod(tpl, "volume", Volume);
  Nan::SetPrototypeMethod(tpl, "lower_volume", LowerVolume);
  Nan::SetPrototypeMethod(tpl, "size", Size);
  Nan::SetPrototypeMethod(tpl, "to_string", ToString);
  Nan::SetPrototypeMethod(tpl, "has_batch", HasBatch);
  Nan::SetPrototypeMethod(tpl, "has_compatible_batch", HasCompatibleBatch);
  Nan::SetPrototypeMethod(tpl, "is_scalar", IsScalar);
  Nan::SetPrototypeMethod(tpl, "is_column_vector", IsColumnVector);
  Nan::SetPrototypeMethod(tpl, "is_matrix", IsMatrix);
  Nan::SetPrototypeMethod(tpl, "has_same_dims", HasSameDims);
  Nan::SetPrototypeMethod(tpl, "has_same_loo_dims", HasSameLooDims);
  Nan::SetPrototypeMethod(tpl, "resize_dim", ResizeDim);
  Nan::SetPrototypeMethod(tpl, "resize_batch", ResizeBatch);
  Nan::SetPrototypeMethod(tpl, "update_dim", UpdateDim);
  Nan::SetPrototypeMethod(tpl, "update_batch", UpdateBatch);

  constructor.Reset(tpl);
  Nan::Set(target, classname, Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(JsShape::New) {
  try {
    if (info.IsConstructCall()) {
      auto batch = info[1]->IsUndefined() ? 1u : Nan::To<std::uint32_t>(info[1]).FromJust();
      JsShape *obj;
      if (info[0]->IsUndefined()) {
        obj = new JsShape({}, batch);
      } else {
        if (info[0]->IsArray()) {
          auto dims_arr = v8::Local<v8::Array>::Cast(info[0]);
          auto dims = jsarray_to_vector<std::uint32_t>(dims_arr);
          obj = new JsShape(dims, batch);
        } else {
          Nan::ThrowError("Argument 1 takes an Array.");
          return;
        }
      }
      obj->Wrap(info.This());
      info.GetReturnValue().Set(info.This());
    } else {
      v8::Local<v8::Function> cons = Nan::GetFunction(Nan::New(constructor)).ToLocalChecked();
      v8::Local<v8::Value> argv[] = { info[0], info[1] };
      info.GetReturnValue().Set(Nan::NewInstance(cons, 2, argv).ToLocalChecked());
    }
  } catch (const primitiv::Error& e) {
    Nan::ThrowError(e.what());
  }
}

NAN_METHOD(JsShape::Dims) {
  JsShape* obj = Nan::ObjectWrap::Unwrap<JsShape>(info.Holder());
  try {
    auto dims = obj->wrapped_->dims();
    auto dims_arr = vector_to_jsarray(dims);
    info.GetReturnValue().Set(dims_arr);
  } catch (const primitiv::Error& e) {
    Nan::ThrowError(e.what());
  }
}

PRIMITIV_NODE_FUNCTION_WRAPPER(JsShape, Depth, depth, v8::Number)
PRIMITIV_NODE_FUNCTION_WRAPPER(JsShape, Batch, batch, v8::Number)
PRIMITIV_NODE_FUNCTION_WRAPPER(JsShape, Volume, volume, v8::Number)
PRIMITIV_NODE_FUNCTION_WRAPPER_ARG1(JsShape, LowerVolume, lower_volume, v8::Number, std::uint32_t)
PRIMITIV_NODE_FUNCTION_WRAPPER(JsShape, Size, size, v8::Number)
PRIMITIV_NODE_FUNCTION_WRAPPER(JsShape, ToString, to_string, v8::String)
PRIMITIV_NODE_FUNCTION_WRAPPER(JsShape, HasBatch, has_batch, v8::Boolean)
PRIMITIV_NODE_FUNCTION_WRAPPER_ARG1(JsShape, HasCompatibleBatch, has_compatible_batch, v8::Boolean, JsShape)
PRIMITIV_NODE_FUNCTION_WRAPPER(JsShape, IsScalar, is_scalar, v8::Boolean)
PRIMITIV_NODE_FUNCTION_WRAPPER(JsShape, IsColumnVector, is_column_vector, v8::Boolean)
PRIMITIV_NODE_FUNCTION_WRAPPER(JsShape, IsMatrix, is_matrix, v8::Boolean)
PRIMITIV_NODE_FUNCTION_WRAPPER_ARG1(JsShape, HasSameDims, has_same_dims, v8::Boolean, JsShape)
PRIMITIV_NODE_FUNCTION_WRAPPER_ARG2(JsShape, HasSameLooDims, has_same_loo_dims, v8::Boolean, JsShape, std::uint32_t)
PRIMITIV_NODE_FUNCTION_WRAPPER_ARG2(JsShape, ResizeDim, resize_dim, JsShape, std::uint32_t, std::uint32_t)
PRIMITIV_NODE_FUNCTION_WRAPPER_ARG1(JsShape, ResizeBatch, resize_batch, JsShape, std::uint32_t)
PRIMITIV_NODE_FUNCTION_WRAPPER_ARG2_NORETURN(JsShape, UpdateDim, update_dim, std::uint32_t, std::uint32_t)
PRIMITIV_NODE_FUNCTION_WRAPPER_ARG1_NORETURN(JsShape, UpdateBatch, update_batch, std::uint32_t)

Nan::Persistent<v8::FunctionTemplate> JsShape::constructor;

} // namespace node

} // namespace primitiv

