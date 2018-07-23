#ifndef PRIMITIV_NODE_INITIALIZERS_INITIALIZERS_H
#define PRIMITIV_NODE_INITIALIZERS_INITIALIZERS_H

#include <nan.h>

#include "Constant.h"
#include "Uniform.h"
#include "Normal.h"
#include "Identity.h"
#include "XavierUniform.h"
#include "XavierNormal.h"
#include "XavierUniformConv2D.h"
#include "XavierNormalConv2D.h"

namespace primitiv {

namespace node {

namespace initializers {

void register_functions(v8::Local<v8::Object> target) {

  auto initializers = Nan::New<v8::Object>();
  Nan::Set(target, Nan::New("initializers").ToLocalChecked(), initializers);

  JsConstant::register_functions(initializers);
  JsUniform::register_functions(initializers);
  JsNormal::register_functions(initializers);
  JsIdentity::register_functions(initializers);
  JsXavierUniform::register_functions(initializers);
  JsXavierNormal::register_functions(initializers);
  JsXavierUniformConv2D::register_functions(initializers);
  JsXavierNormalConv2D::register_functions(initializers);

}

} // namespace initializers

} // namespace node

} // namespace primitiv

#endif  // PRIMITIV_NODE_INITIALIZERS_INITIALIZERS_H
