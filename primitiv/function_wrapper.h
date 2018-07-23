#ifndef PRIMITIV_NODE_FUNCTION_WRAPPER_H
#define PRIMITIV_NODE_FUNCTION_WRAPPER_H

#include <nan.h>

#include <vector>
#include <functional>

namespace primitiv {

namespace node {

class WrapperBase : public Nan::ObjectWrap {};

template <typename T>
class Wrapper : public WrapperBase {

protected:
  explicit Wrapper(std::shared_ptr<T> wrapped) : wrapped_sp_(wrapped), wrapped_(wrapped.get()) {}
  explicit Wrapper(T& wrapped) : wrapped_(&wrapped) {}

  ~Wrapper() {}

public:
  std::shared_ptr<T> wrapped_sp_;
  T* wrapped_;

  static v8::Local<v8::Object> wrap_cpp(const T& wrapped);
  static v8::Local<v8::Object> wrap_cpp(T& wrapped);
  static v8::Local<v8::Object> wrap_cpp(T&& wrapped);
};

template <typename T>
inline auto local_check(Nan::MaybeLocal<T> obj) -> decltype(obj.ToLocalChecked()) {
  return obj.ToLocalChecked();
}

template <typename T>
inline v8::Local<T> local_check(v8::Local<T> obj) {
  return obj;
}

template <typename T>
inline v8::Local<v8::Array> vector_to_jsarray(std::vector<T> v) {
  auto arr = Nan::New<v8::Array>(v.size());
  for (std::size_t i = 0; i < v.size(); ++i) {
    Nan::Set(arr, i, local_check(Nan::New(v[i])));
  }
  return arr;
}

template <typename T>
inline std::vector<T> jsarray_to_vector(v8::Local<v8::Array> arr) {
  std::vector<T> v;
  for (std::uint32_t i = 0; i < arr->Length(); ++i) {
    v.emplace_back(Nan::To<T>(Nan::Get(arr, i).ToLocalChecked()).FromJust());
  }
  return v;
}

template <>
inline std::vector<float> jsarray_to_vector<float>(v8::Local<v8::Array> arr) {
  std::vector<float> v;
  for (std::uint32_t i = 0; i < arr->Length(); ++i) {
    v.emplace_back(static_cast<float>(Nan::To<double>(Nan::Get(arr, i).ToLocalChecked()).FromJust()));
  }
  return v;
}

template <typename T>
inline std::unordered_map<std::string, T> jsobject_to_map(v8::Local<v8::Object> obj) {
  std::unordered_map<std::string, T> m;
  auto keys = Nan::GetOwnPropertyNames(obj).ToLocalChecked();
  for (std::uint32_t i = 0; i < keys->Length(); ++i) {
    auto key = Nan::Get(keys, i).ToLocalChecked();
    Nan::Utf8String s(key);
    m.emplace(*s, Nan::To<T>(Nan::Get(obj, key).ToLocalChecked()).FromJust());
  }
  return m;
}

template <>
inline std::unordered_map<std::string, float> jsobject_to_map<float>(v8::Local<v8::Object> obj) {
  std::unordered_map<std::string, float> m;
  auto keys = Nan::GetOwnPropertyNames(obj).ToLocalChecked();
  for (std::uint32_t i = 0; i < keys->Length(); ++i) {
    auto key = Nan::Get(keys, i).ToLocalChecked();
    Nan::Utf8String s(key);
    m.emplace(std::string(*s), Nan::To<double>(Nan::Get(obj, key).ToLocalChecked()).FromJust());
  }
  return m;
}

inline std::vector<std::string> jsarray_to_string_vector(v8::Local<v8::Array> arr) {
  std::vector<std::string> v;
  for (std::uint32_t i = 0; i < arr->Length(); ++i) {
    Nan::Utf8String s(Nan::Get(arr, i).ToLocalChecked());
    v.emplace_back(*s);
  }
  return v;
}

template <typename T, typename std::enable_if<std::is_base_of<class WrapperBase, T>::value>::type* = nullptr>
inline bool is_type_of(v8::Local<v8::Value> obj) {
  return Nan::New(T::constructor)->HasInstance(obj);
}

template <typename T, typename std::enable_if<!std::is_base_of<class WrapperBase, T>::value>::type* = nullptr>
inline bool is_type_of(v8::Local<v8::Value> obj) {
  return false;
}

template <>
inline bool is_type_of<float>(v8::Local<v8::Value> obj) {
  return obj->IsNumber();
}

template <>
inline bool is_type_of<std::uint32_t>(v8::Local<v8::Value> obj) {
  return obj->IsNumber();
}

template <>
inline bool is_type_of<std::string>(v8::Local<v8::Value> obj) {
  return obj->IsString();
}

template <>
inline bool is_type_of<bool>(v8::Local<v8::Value> obj) {
  return obj->IsBoolean();
}

template <typename T, typename std::enable_if<std::is_base_of<class WrapperBase, T>::value>::type* = nullptr>
inline decltype(*T::wrapped_)& unwrap(v8::Local<v8::Value> obj) {
  if (Nan::New(T::constructor)->HasInstance(obj)) {
    auto* data = Nan::ObjectWrap::Unwrap<T>(obj->ToObject());
    return *data->wrapped_;
  } else {
    PRIMITIV_THROW_ERROR("invalid arguments");
  }
}

template <typename T, typename std::enable_if<!std::is_base_of<class WrapperBase, T>::value>::type* = nullptr>
inline T unwrap(v8::Local<v8::Value> obj) {
  auto data = Nan::To<T>(obj).FromJust();
  return data;
}

template <>
inline float unwrap<float>(v8::Local<v8::Value> obj) {
  auto data = static_cast<float>(Nan::To<double>(obj).FromJust());
  return data;
}

template <>
inline std::string unwrap<std::string>(v8::Local<v8::Value> obj) {
  if (obj->IsString()) {
    Nan::Utf8String s(obj->ToString());
    return std::string(*s);
  } else {
    PRIMITIV_THROW_ERROR("invalid arguments");
  }
}

template <>
inline std::vector<float> unwrap<std::vector<float>>(v8::Local<v8::Value> obj) {
  if (obj->IsArray()) {
    auto arr = v8::Local<v8::Array>::Cast(obj);
    return jsarray_to_vector<float>(arr);
  } else {
    PRIMITIV_THROW_ERROR("invalid arguments");
  }
}

template <typename T, typename U, typename std::enable_if<std::is_base_of<class WrapperBase, T>::value>::type* = nullptr>
inline v8::Local<v8::Object> wrap(U& data) {
  return T::wrap_cpp(data);
}

template <typename T, typename U, typename std::enable_if<std::is_base_of<class WrapperBase, T>::value>::type* = nullptr>
inline v8::Local<v8::Object> wrap(U&& data) {
  return T::wrap_cpp(std::forward<U>(data));
}

template <typename T, typename U, typename std::enable_if<!std::is_base_of<class WrapperBase, T>::value>::type* = nullptr>
inline auto wrap(U data) -> decltype(Nan::New<T>(data)) {
  return Nan::New<T>(data);
}

#define PRIMITIV_NODE_FUNCTION_WRAPPER_NORETURN(cls, name, func) \
  NAN_METHOD(cls::name) { \
    cls* obj = Nan::ObjectWrap::Unwrap<cls>(info.Holder()); \
    try { \
      obj->wrapped_->func(); \
    } catch (const primitiv::Error& e) { \
      Nan::ThrowError(e.what()); \
    } \
  }

#define PRIMITIV_NODE_FUNCTION_WRAPPER(cls, name, func, rtype) \
  NAN_METHOD(cls::name) { \
    cls* obj = Nan::ObjectWrap::Unwrap<cls>(info.Holder()); \
    try { \
      info.GetReturnValue().Set(local_check(wrap<rtype>(obj->wrapped_->func()))); \
    } catch (const primitiv::Error& e) { \
      Nan::ThrowError(e.what()); \
    } \
  }

#define PRIMITIV_NODE_FUNCTION_WRAPPER_ARG1_NORETURN(cls, name, func, argtype1) \
  NAN_METHOD(cls::name) { \
    cls* obj = Nan::ObjectWrap::Unwrap<cls>(info.Holder()); \
    try { \
      obj->wrapped_->func(unwrap<argtype1>(info[0])); \
    } catch (const primitiv::Error& e) { \
      Nan::ThrowError(e.what()); \
    } \
  }

#define PRIMITIV_NODE_FUNCTION_WRAPPER_ARG1(cls, name, func, rtype, argtype1) \
  NAN_METHOD(cls::name) { \
    cls* obj = Nan::ObjectWrap::Unwrap<cls>(info.Holder()); \
    try { \
      info.GetReturnValue().Set(local_check(wrap<rtype>(obj->wrapped_->func(unwrap<argtype1>(info[0]))))); \
    } catch (const primitiv::Error& e) { \
      Nan::ThrowError(e.what()); \
    } \
  }

#define PRIMITIV_NODE_FUNCTION_WRAPPER_ARG2_NORETURN(cls, name, func, argtype1, argtype2) \
  NAN_METHOD(cls::name) { \
    cls* obj = Nan::ObjectWrap::Unwrap<cls>(info.Holder()); \
    try { \
      obj->wrapped_->func(unwrap<argtype1>(info[0]), unwrap<argtype2>(info[1])); \
    } catch (const primitiv::Error& e) { \
      Nan::ThrowError(e.what()); \
    } \
  }

#define PRIMITIV_NODE_FUNCTION_WRAPPER_ARG2(cls, name, func, rtype, argtype1, argtype2) \
  NAN_METHOD(cls::name) { \
    cls* obj = Nan::ObjectWrap::Unwrap<cls>(info.Holder()); \
    try { \
      info.GetReturnValue().Set(local_check(wrap<rtype>(obj->wrapped_->func(unwrap<argtype1>(info[0]), unwrap<argtype2>(info[1]))))); \
    } catch (const primitiv::Error& e) { \
      Nan::ThrowError(e.what()); \
    } \
  }

#define PRIMITIV_NODE_FUNCTION_DISPATCH_NORETURN(func) \
  if (info.Length() == 0) { \
    func(); \
  } else

#define PRIMITIV_NODE_FUNCTION_DISPATCH_NORETURN_EXT(func, ...) \
  if (info.Length() == 0) { \
    func(__VA_ARGS__); \
  } else

#define PRIMITIV_NODE_FUNCTION_DISPATCH(func, rtype) \
  if (info.Length() == 0) { \
    info.GetReturnValue().Set(local_check(wrap<rtype>(func()))); \
  } else

#define PRIMITIV_NODE_FUNCTION_DISPATCH_EXT(func, rtype, ...) \
  if (info.Length() == 0) { \
    info.GetReturnValue().Set(local_check(wrap<rtype>(func(__VA_ARGS__)))); \
  } else

#define PRIMITIV_NODE_FUNCTION_DISPATCH_ARG1_NORETURN(func, argtype1) \
  if (info.Length() == 1 && is_type_of<argtype1>(info[0])) { \
    func(unwrap<argtype1>(info[0])); \
  } else

#define PRIMITIV_NODE_FUNCTION_DISPATCH_ARG1_NORETURN_EXT(func, argtype1, ...) \
  if (info.Length() == 1 && is_type_of<argtype1>(info[0])) { \
    func(unwrap<argtype1>(info[0], __VA_ARGS__)); \
  } else

#define PRIMITIV_NODE_FUNCTION_DISPATCH_ARG1(func, rtype, argtype1) \
  if (info.Length() == 1 && is_type_of<argtype1>(info[0])) { \
    info.GetReturnValue().Set(local_check(wrap<rtype>(func(unwrap<argtype1>(info[0]))))); \
  } else

#define PRIMITIV_NODE_FUNCTION_DISPATCH_ARG1_EXT(func, rtype, argtype1, ...) \
  if (info.Length() == 1 && is_type_of<argtype1>(info[0])) { \
    info.GetReturnValue().Set(local_check(wrap<rtype>(func(unwrap<argtype1>(info[0]), __VA_ARGS__)))); \
  } else

#define PRIMITIV_NODE_FUNCTION_DISPATCH_ARG2_NORETURN(func, argtype1, argtype2) \
  if (info.Length() == 2 && is_type_of<argtype1>(info[0]) && is_type_of<argtype2>(info[1])) { \
    func(unwrap<argtype1>(info[0]), unwrap<argtype2>(info[1])); \
  } else

#define PRIMITIV_NODE_FUNCTION_DISPATCH_ARG2_NORETURN_EXT(func, argtype1, argtype2, ...) \
  if (info.Length() == 2 && is_type_of<argtype1>(info[0]) && is_type_of<argtype2>(info[1])) { \
    func(unwrap<argtype1>(info[0]), unwrap<argtype2>(info[1]), __VA_ARGS__); \
  } else

#define PRIMITIV_NODE_FUNCTION_DISPATCH_ARG2(func, rtype, argtype1, argtype2) \
  if (info.Length() == 2 && is_type_of<argtype1>(info[0]) && is_type_of<argtype2>(info[1])) { \
    info.GetReturnValue().Set(local_check(wrap<rtype>(func(unwrap<argtype1>(info[0]), unwrap<argtype2>(info[1]))))); \
  } else

#define PRIMITIV_NODE_FUNCTION_DISPATCH_ARG2_EXT(func, rtype, argtype1, argtype2, ...) \
  if (info.Length() == 2 && is_type_of<argtype1>(info[0]) && is_type_of<argtype2>(info[1])) { \
    info.GetReturnValue().Set(local_check(wrap<rtype>(func(unwrap<argtype1>(info[0]), unwrap<argtype2>(info[1]), __VA_ARGS__)))); \
  } else

#define PRIMITIV_NODE_FUNCTION_END_DISPATCH() \
  PRIMITIV_THROW_ERROR("no matching function for specified arguments.");

#define PRIMITIV_NODE_GET_DEVICE(i) \
  primitiv::Device* device = !info[i]->IsUndefined() \
    ? &unwrap<JsDevice>(info[i]) \
    : (JsDevice::default_object != nullptr \
      ? JsDevice::default_object->wrapped_ \
      : nullptr); \
  if (device == nullptr) { Nan::ThrowError("Default object is null."); return; }

#define PRIMITIV_NODE_GET_GRAPH(i) \
  primitiv::Graph* g = !info[i]->IsUndefined() \
    ? &unwrap<JsGraph>(info[i]) \
    : (JsGraph::default_object != nullptr \
      ? JsGraph::default_object->wrapped_ \
      : nullptr); \
  if (g == nullptr) { Nan::ThrowError("Default object is null."); return; }

} // namespace node

} // namespace primitiv

#endif  // PRIMITIV_NODE_SHAPE_H
