#ifndef PRIMITIV_NODE_GRAPH_H
#define PRIMITIV_NODE_GRAPH_H

#include <nan.h>

#include <primitiv/primitiv.h>

#include "function_wrapper.h"

namespace primitiv {

namespace node {

class JsNode;
class JsGraph;

class JsNode : public Wrapper<primitiv::Node> {

public:
  JsNode() : Wrapper(std::make_shared<primitiv::Node>()) {}
  explicit JsNode(primitiv::Node& node) : Wrapper(node) {}
  explicit JsNode(primitiv::Node&& node) : Wrapper(std::make_shared<primitiv::Node>(std::forward<primitiv::Node>(node))) {}

  static void register_functions(v8::Local<v8::Object> target);

  static inline v8::Local<v8::Object> wrap_cpp(primitiv::Node& node) {
    auto wrapper = new JsNode(node);
    return wrapper->handle();
  }

  static inline v8::Local<v8::Object> wrap_cpp(primitiv::Node&& node) {
    auto wrapper = new JsNode(std::forward<primitiv::Node>(node));
    v8::Local<v8::Function> cons = Nan::GetFunction(Nan::New(constructor)).ToLocalChecked();
    auto instance = Nan::NewInstance(cons).ToLocalChecked();
    wrapper->Wrap(instance);
    return instance;
  }

  static NAN_METHOD(New);

  static NAN_METHOD(Valid);
  static NAN_METHOD(Graph);
  static NAN_METHOD(OperatorId);
  static NAN_METHOD(ValueId);
  static NAN_METHOD(Shape);
  static NAN_METHOD(Device);
  static NAN_METHOD(ToFloat);
  static NAN_METHOD(ToArray);
  static NAN_METHOD(Argmax);
  static NAN_METHOD(Argmin);
  static NAN_METHOD(Backward);

  static Nan::Persistent<v8::FunctionTemplate> constructor;

  static JsNode* default_object;

};

class JsGraph : public Wrapper<primitiv::Graph> {

public:
  JsGraph() : Wrapper(std::make_shared<primitiv::Graph>()) {}
  explicit JsGraph(primitiv::Graph &graph) : Wrapper(graph) {}

  static inline v8::Local<v8::Object> wrap_cpp(primitiv::Graph& graph) {
    auto wrapper = new JsGraph(graph);
    return wrapper->handle();
  }

  static void register_functions(v8::Local<v8::Object> target);

  static NAN_METHOD(New);

  static NAN_METHOD(GetDefault);
  static NAN_METHOD(SetDefault);

  static NAN_METHOD(Clear);
  static NAN_METHOD(Forward);
  static NAN_METHOD(Backward);
  static NAN_METHOD(GetShape);
  static NAN_METHOD(GetDevice);
  static NAN_METHOD(Dump);
  static NAN_METHOD(NumOperators);

  static Nan::Persistent<v8::FunctionTemplate> constructor;
  static JsGraph* default_object;

};

} // namespace node

} // namespace primitiv

#endif  // PRIMITIV_NODE_GRAPH_H
