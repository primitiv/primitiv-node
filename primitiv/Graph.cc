#include <nan.h>

#include "Device.h"
#include "Shape.h"
#include "Graph.h"
#include "Tensor.h"

#include "function_wrapper.h"

namespace primitiv {

namespace node {

void JsNode::register_functions(v8::Local<v8::Object> target) {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);

  auto classname = Nan::New("Node").ToLocalChecked();

  tpl->SetClassName(classname);
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(tpl, "valid", Valid);
  Nan::SetPrototypeMethod(tpl, "graph", Graph);
  Nan::SetPrototypeMethod(tpl, "operator_id", OperatorId);
  Nan::SetPrototypeMethod(tpl, "value_id", ValueId);
  Nan::SetPrototypeMethod(tpl, "shape", Shape);
  Nan::SetPrototypeMethod(tpl, "device", Device);
  Nan::SetPrototypeMethod(tpl, "to_float", ToFloat);
  Nan::SetPrototypeMethod(tpl, "to_array", ToArray);
  Nan::SetPrototypeMethod(tpl, "argmax", Argmax);
  Nan::SetPrototypeMethod(tpl, "argmin", Argmin);
  Nan::SetPrototypeMethod(tpl, "backward", Backward);

  constructor.Reset(tpl);
  Nan::Set(target, classname, Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(JsNode::New) {
  try {
    if (info.IsConstructCall()) {
      JsNode *obj = new JsNode();
      obj->Wrap(info.This());
      info.GetReturnValue().Set(info.This());
    }
  } catch (const primitiv::Error& e) {
    Nan::ThrowError(e.what());
  }
}

PRIMITIV_NODE_FUNCTION_WRAPPER(JsNode, Valid, valid, v8::Boolean)
PRIMITIV_NODE_FUNCTION_WRAPPER(JsNode, Graph, graph, JsGraph)
PRIMITIV_NODE_FUNCTION_WRAPPER(JsNode, OperatorId, operator_id, v8::Number)
PRIMITIV_NODE_FUNCTION_WRAPPER(JsNode, ValueId, value_id, v8::Number)
PRIMITIV_NODE_FUNCTION_WRAPPER(JsNode, Shape, shape, JsShape)
PRIMITIV_NODE_FUNCTION_WRAPPER(JsNode, Device, device, JsDevice)
PRIMITIV_NODE_FUNCTION_WRAPPER(JsNode, ToFloat, to_float, v8::Number)

NAN_METHOD(JsNode::ToArray) {
  JsNode* obj = Nan::ObjectWrap::Unwrap<JsNode>(info.Holder());
  try {
    auto result = obj->wrapped_->to_vector();
    auto result_arr = vector_to_jsarray(result);
    info.GetReturnValue().Set(result_arr);
  } catch (const primitiv::Error& e) {
    Nan::ThrowError(e.what());
  }
}

NAN_METHOD(JsNode::Argmax) {
  JsNode* obj = Nan::ObjectWrap::Unwrap<JsNode>(info.Holder());
  try {
    auto result = obj->wrapped_->argmax(unwrap<std::uint32_t>(info[0]));
    auto result_arr = vector_to_jsarray(result);
    info.GetReturnValue().Set(result_arr);
  } catch (const primitiv::Error& e) {
    Nan::ThrowError(e.what());
  }
}

NAN_METHOD(JsNode::Argmin) {
  JsNode* obj = Nan::ObjectWrap::Unwrap<JsNode>(info.Holder());
  try {
    auto result = obj->wrapped_->argmin(unwrap<std::uint32_t>(info[0]));
    auto result_arr = vector_to_jsarray(result);
    info.GetReturnValue().Set(result_arr);
  } catch (const primitiv::Error& e) {
    Nan::ThrowError(e.what());
  }
}

PRIMITIV_NODE_FUNCTION_WRAPPER_NORETURN(JsNode, Backward, backward)

Nan::Persistent<v8::FunctionTemplate> JsNode::constructor;
JsNode* JsNode::default_object;

void JsGraph::register_functions(v8::Local<v8::Object> target) {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);

  auto classname = Nan::New("Graph").ToLocalChecked();

  tpl->SetClassName(classname);
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  Nan::SetMethod(tpl, "get_default", GetDefault);
  Nan::SetMethod(tpl, "set_default", SetDefault);

  Nan::SetPrototypeMethod(tpl, "clear", Clear);
  Nan::SetPrototypeMethod(tpl, "forward", Forward);
  Nan::SetPrototypeMethod(tpl, "backward", Backward);
  Nan::SetPrototypeMethod(tpl, "get_shape", GetShape);
  Nan::SetPrototypeMethod(tpl, "get_device", GetDevice);
  Nan::SetPrototypeMethod(tpl, "dump", Dump);
  Nan::SetPrototypeMethod(tpl, "num_operators", NumOperators);

  constructor.Reset(tpl);
  Nan::Set(target, classname, Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(JsGraph::New) {
  try {
    if (info.IsConstructCall()) {
      JsGraph *obj = new JsGraph();
      obj->Wrap(info.This());
      info.GetReturnValue().Set(info.This());
    } else {
      v8::Local<v8::Function> cons = Nan::GetFunction(Nan::New(constructor)).ToLocalChecked();
      info.GetReturnValue().Set(Nan::NewInstance(cons, 0, {}).ToLocalChecked());
    }
  } catch (const primitiv::Error& e) {
    Nan::ThrowError(e.what());
  }
}

NAN_METHOD(JsGraph::GetDefault) {
  if (default_object != nullptr) {
    info.GetReturnValue().Set(default_object->handle());
  } else {
    Nan::ThrowError("Default object is null.");
  }
}

NAN_METHOD(JsGraph::SetDefault) {
  if (Nan::New(JsGraph::constructor)->HasInstance(info[0])) {
    default_object = Nan::ObjectWrap::Unwrap<JsGraph>(info[0]->ToObject());
  } else {
    PRIMITIV_THROW_ERROR("invalid arguments");
  }
}

PRIMITIV_NODE_FUNCTION_WRAPPER_NORETURN(JsGraph, Clear, clear)
PRIMITIV_NODE_FUNCTION_WRAPPER_ARG1(JsGraph, Forward, forward, JsTensor, JsNode)
PRIMITIV_NODE_FUNCTION_WRAPPER_ARG1_NORETURN(JsGraph, Backward, backward, JsNode)
PRIMITIV_NODE_FUNCTION_WRAPPER_ARG1(JsGraph, GetShape, get_shape, JsShape, JsNode)
PRIMITIV_NODE_FUNCTION_WRAPPER_ARG1(JsGraph, GetDevice, get_device, JsDevice, JsNode)
PRIMITIV_NODE_FUNCTION_WRAPPER_ARG1(JsGraph, Dump, dump, v8::String, std::string)
PRIMITIV_NODE_FUNCTION_WRAPPER(JsGraph, NumOperators, num_operators, v8::Number)

Nan::Persistent<v8::FunctionTemplate> JsGraph::constructor;
JsGraph* JsGraph::default_object;

} // namespace node

} // namespace primitiv

