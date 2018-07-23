#ifndef PRIMITIV_NODE_DEVICES_DEVICES_H
#define PRIMITIV_NODE_DEVICES_DEVICES_H

#include <nan.h>

#include "Naive.h"

namespace primitiv {

namespace node {

namespace devices {

void register_functions(v8::Local<v8::Object> target) {

  auto devices = Nan::New<v8::Object>();
  Nan::Set(target, Nan::New("devices").ToLocalChecked(), devices);

  JsNaive::register_functions(devices);

}

} // namespace devices

} // namespace node

} // namespace primitiv

#endif  // PRIMITIV_NODE_DEVICES_NAIVE_H
