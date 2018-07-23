#ifndef PRIMITIV_NODE_OPTIMIZERS_OPTIMIZERS_H
#define PRIMITIV_NODE_OPTIMIZERS_OPTIMIZERS_H

#include <nan.h>

#include "SGD.h"

namespace primitiv {

namespace node {

namespace optimizers {

void register_functions(v8::Local<v8::Object> target) {

  auto optimizers = Nan::New<v8::Object>();
  Nan::Set(target, Nan::New("optimizers").ToLocalChecked(), optimizers);

  JsSGD::register_functions(optimizers);

}

} // namespace optimizers

} // namespace node

} // namespace primitiv

#endif  // PRIMITIV_NODE_OPTIMIZERS_OPTIMIZERS_H
