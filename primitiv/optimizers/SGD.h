#ifndef PRIMITIV_NODE_OPTIMIZERS_SGD_H
#define PRIMITIV_NODE_OPTIMIZERS_SGD_H

#include <nan.h>
#include <primitiv/primitiv.h>

#include "../Optimizer.h"
#include "../function_wrapper.h"

namespace primitiv {

namespace node {

namespace optimizers {

class JsSGD : public Wrapper<primitiv::optimizers::SGD> {
  JsSGD() = delete;
public:
  explicit JsSGD(float eta) : Wrapper(std::make_shared<primitiv::optimizers::SGD>(eta)) {}

  static void register_functions(v8::Local<v8::Object> target);

  static NAN_METHOD(New);

  static NAN_METHOD(Eta);

  static Nan::Persistent<v8::FunctionTemplate> constructor;
};

} // namespace optimizers

} // namespace node

} // namespace primitiv

#endif  // PRIMITIV_NODE_OPTIMIZERS_SGD_H
