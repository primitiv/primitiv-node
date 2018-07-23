#ifndef PRIMITIV_NODE_FUNCTIONS_H
#define PRIMITIV_NODE_FUNCTIONS_H

#include <nan.h>
#include <primitiv/primitiv.h>

#include "function_wrapper.h"

namespace primitiv {

namespace node {

namespace functions {

  NAN_METHOD(Positive);
  NAN_METHOD(Negative);
  NAN_METHOD(Add);
  NAN_METHOD(Subtract);
  NAN_METHOD(Multiply);
  NAN_METHOD(Divide);
  NAN_METHOD(Pow);
  NAN_METHOD(Pown);
  NAN_METHOD(InputNode);
  NAN_METHOD(ParameterNode);
  NAN_METHOD(Copy);
//   NAN_METHOD(Pick);
  NAN_METHOD(Slice);
//   NAN_METHOD(Split);
//   NAN_METHOD(Concat);
  NAN_METHOD(Reshape);
  NAN_METHOD(Flatten);
  NAN_METHOD(Transpose);
  NAN_METHOD(Matmul);
  NAN_METHOD(Abs);
  NAN_METHOD(Sqrt);
  NAN_METHOD(Exp);
  NAN_METHOD(Log);
  NAN_METHOD(Tanh);
  NAN_METHOD(Sigmoid);
  NAN_METHOD(Softplus);
  NAN_METHOD(Sin);
  NAN_METHOD(Cos);
  NAN_METHOD(Tan);
  NAN_METHOD(Relu);
  NAN_METHOD(Lrelu);
  NAN_METHOD(Prelu);
  NAN_METHOD(Elu);
  NAN_METHOD(Max);
  NAN_METHOD(Min);
  NAN_METHOD(Sum);
  NAN_METHOD(Broadcast);
  NAN_METHOD(Logsumexp);
  NAN_METHOD(LogSoftmax);
  NAN_METHOD(Softmax);
//   NAN_METHOD(SoftmaxCrossEntropy);
  NAN_METHOD(StopGradient);
//   NAN_METHOD(Conv2d);
//   NAN_METHOD(MaxPool2d);
  NAN_METHOD(ConstantNode);
  NAN_METHOD(IdentityNode);
//   NAN_METHOD(Selu);
//   NAN_METHOD(Sum);
//   NAN_METHOD(Mean);
  NAN_METHOD(ZerosNode);
  NAN_METHOD(OnesNode);
  NAN_METHOD(Dropout);

  void register_functions(v8::Local<v8::Object> target);

  namespace batch {

//     NAN_METHOD(Pick);
    NAN_METHOD(Slice);
//     NAN_METHOD(Split);
//     NAN_METHOD(Concat);
//     NAN_METHOD(Sum);
    NAN_METHOD(Mean);
    NAN_METHOD(Normalize);

    void register_functions(v8::Local<v8::Object> target);
  }

  namespace random {

    NAN_METHOD(BernoulliNode);
    NAN_METHOD(UniformNode);
    NAN_METHOD(NormalNode);
    NAN_METHOD(LogNormalNode);
    NAN_METHOD(GumbelNode);

    void register_functions(v8::Local<v8::Object> target);
  }
} // namespace functions

} // namespace node

} // namespace primitiv

#endif  // PRIMITIV_NODE_FUNCTIONS_H
