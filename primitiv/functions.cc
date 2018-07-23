#include <nan.h>

#include "Device.h"
#include "Graph.h"
#include "Parameter.h"
#include "Shape.h"
#include "functions.h"

#include "function_wrapper.h"

namespace primitiv {

namespace node {

namespace functions {

#define DISPATCH_FUNCTION_ARG1(func, argtype1) \
  if (is_type_of<argtype1>(info[0])) { \
    info.GetReturnValue().Set(wrap<JsNode>(func(unwrap<argtype1>(info[0])))); \
  } else

#define DISPATCH_FUNCTION_ARG1_EXT(func, argtype1, ...) \
  if (is_type_of<argtype1>(info[0])) { \
    info.GetReturnValue().Set(wrap<JsNode>(func(unwrap<argtype1>(info[0]), __VA_ARGS__))); \
  } else

#define DISPATCH_FUNCTION_ARG2(func, argtype1, argtype2) \
  if (is_type_of<argtype1>(info[0]) && is_type_of<argtype2>(info[1])) { \
    info.GetReturnValue().Set(wrap<JsNode>(func(unwrap<argtype1>(info[0]), unwrap<argtype2>(info[1])))); \
  } else

#define DISPATCH_FUNCTION_ARG2_EXT(func, argtype1, argtype2, ...) \
  if (is_type_of<argtype1>(info[0]) && is_type_of<argtype2>(info[1])) { \
    info.GetReturnValue().Set(wrap<JsNode>(func(unwrap<argtype1>(info[0]), unwrap<argtype2>(info[1]), __VA_ARGS__))); \
  } else

#define DISPATCH_FUNCTION_ARG3(func, argtype1, argtype2, argtype3) \
  if (is_type_of<argtype1>(info[0]) && is_type_of<argtype2>(info[1]) && is_type_of<argtype3>(info[2])) { \
    info.GetReturnValue().Set(wrap<JsNode>(func(unwrap<argtype1>(info[0]), unwrap<argtype2>(info[1]), unwrap<argtype3>(info[2])))); \
  } else

#define DISPATCH_FUNCTION_ARG3_EXT(func, argtype1, argtype2, argtype3, ...) \
  if (is_type_of<argtype1>(info[0]) && is_type_of<argtype2>(info[1])) { \
    info.GetReturnValue().Set(wrap<JsNode>(func(unwrap<argtype1>(info[0]), unwrap<argtype2>(info[1]), unwrap<argtype3>(info[2]), __VA_ARGS__))); \
  } else

#define DISPATCH_FUNCTION_ARG4(func, argtype1, argtype2, argtype3, argtype4) \
  if (is_type_of<argtype1>(info[0]) && is_type_of<argtype2>(info[1]) && is_type_of<argtype3>(info[2]) && is_type_of<argtype4>(info[3])) { \
    info.GetReturnValue().Set(wrap<JsNode>(func(unwrap<argtype1>(info[0]), unwrap<argtype2>(info[1]), unwrap<argtype3>(info[2]), unwrap<argtype4>(info[3])))); \
  } else

#define DISPATCH_FUNCTION_ARG4_EXT(func, argtype1, argtype2, argtype3, argtype4, ...) \
  if (is_type_of<argtype1>(info[0]) && is_type_of<argtype2>(info[1]) && is_type_of<argtype3>(info[2]) && is_type_of<argtype4>(info[3])) { \
    info.GetReturnValue().Set(wrap<JsNode>(func(unwrap<argtype1>(info[0]), unwrap<argtype2>(info[1]), unwrap<argtype3>(info[2]), unwrap<argtype4>(info[3]), __VA_ARGS__))); \
  } else

#define END_DISPATCH() \
  Nan::ThrowError("invalid arguments");

  NAN_METHOD(Positive) {
    try {
      info.GetReturnValue().Set(local_check(wrap<JsNode>(primitiv::functions::positive(unwrap<JsNode>(info[0])))));
    } catch (const primitiv::Error& e) {
      Nan::ThrowError(e.what());
    }
  }

  NAN_METHOD(Negative) {
    try {
      info.GetReturnValue().Set(local_check(wrap<JsNode>(primitiv::functions::negative(unwrap<JsNode>(info[0])))));
    } catch (const primitiv::Error& e) {
      Nan::ThrowError(e.what());
    }
  }

  NAN_METHOD(Add) {
    try {
      DISPATCH_FUNCTION_ARG2(primitiv::functions::add, JsNode, JsNode)
      DISPATCH_FUNCTION_ARG2(primitiv::functions::add, JsNode, float)
      DISPATCH_FUNCTION_ARG2(primitiv::functions::add, float, JsNode)
      END_DISPATCH()
    } catch (const primitiv::Error& e) {
      Nan::ThrowError(e.what());
    }
  }

  NAN_METHOD(Subtract) {
    try {
      DISPATCH_FUNCTION_ARG2(primitiv::functions::subtract, JsNode, JsNode)
      DISPATCH_FUNCTION_ARG2(primitiv::functions::subtract, JsNode, float)
      DISPATCH_FUNCTION_ARG2(primitiv::functions::subtract, float, JsNode)
      END_DISPATCH()
    } catch (const primitiv::Error& e) {
      Nan::ThrowError(e.what());
    }
  }

  NAN_METHOD(Multiply) {
    try {
      DISPATCH_FUNCTION_ARG2(primitiv::functions::multiply, JsNode, JsNode)
      DISPATCH_FUNCTION_ARG2(primitiv::functions::multiply, JsNode, float)
      DISPATCH_FUNCTION_ARG2(primitiv::functions::multiply, float, JsNode)
      END_DISPATCH()
    } catch (const primitiv::Error& e) {
      Nan::ThrowError(e.what());
    }
  }

  NAN_METHOD(Divide) {
    try {
      DISPATCH_FUNCTION_ARG2(primitiv::functions::divide, JsNode, JsNode)
      DISPATCH_FUNCTION_ARG2(primitiv::functions::divide, JsNode, float)
      DISPATCH_FUNCTION_ARG2(primitiv::functions::divide, float, JsNode)
      END_DISPATCH()
    } catch (const primitiv::Error& e) {
      Nan::ThrowError(e.what());
    }
  }

  NAN_METHOD(Pow) {
    try {
      DISPATCH_FUNCTION_ARG2(primitiv::functions::pow, JsNode, JsNode)
      DISPATCH_FUNCTION_ARG2(primitiv::functions::pow, JsNode, float)
      DISPATCH_FUNCTION_ARG2(primitiv::functions::pow, float, JsNode)
      END_DISPATCH()
    } catch (const primitiv::Error& e) {
      Nan::ThrowError(e.what());
    }
  }

  NAN_METHOD(Pown) {
    try {
      DISPATCH_FUNCTION_ARG2(primitiv::functions::pown, JsNode, std::uint32_t)
      END_DISPATCH()
    } catch (const primitiv::Error& e) {
      Nan::ThrowError(e.what());
    }
  }

  NAN_METHOD(InputNode) {
    try {
      PRIMITIV_NODE_GET_DEVICE(2)
      PRIMITIV_NODE_GET_GRAPH(3)
      auto arr = v8::Local<v8::Array>::Cast(info[1]);
      auto data = jsarray_to_vector<float>(arr);
      info.GetReturnValue().Set(wrap<JsNode>(primitiv::functions::input_node(unwrap<JsShape>(info[0]), data, device, g)));
    } catch (const primitiv::Error& e) {
      Nan::ThrowError(e.what());
    }
  }

  NAN_METHOD(ParameterNode) {
    try {
      PRIMITIV_NODE_GET_GRAPH(1)
      DISPATCH_FUNCTION_ARG1_EXT(primitiv::functions::parameter_node, JsParameter, g)
      END_DISPATCH()
    } catch (const primitiv::Error& e) {
      Nan::ThrowError(e.what());
    }
  }

  NAN_METHOD(Copy) {
    try {
      PRIMITIV_NODE_GET_DEVICE(1)
      DISPATCH_FUNCTION_ARG1_EXT(primitiv::functions::copy, JsNode, device)
      END_DISPATCH()
    } catch (const primitiv::Error& e) {
      Nan::ThrowError(e.what());
    }
  }

  NAN_METHOD(Slice) {
    try {
      DISPATCH_FUNCTION_ARG4(primitiv::functions::slice, JsNode, std::uint32_t, std::uint32_t, std::uint32_t)
      END_DISPATCH()
    } catch (const primitiv::Error& e) {
      Nan::ThrowError(e.what());
    }
  }

  NAN_METHOD(Reshape) {
    try {
      DISPATCH_FUNCTION_ARG2(primitiv::functions::reshape, JsNode, JsShape)
      END_DISPATCH()
    } catch (const primitiv::Error& e) {
      Nan::ThrowError(e.what());
    }
  }

  NAN_METHOD(Flatten) {
    try {
      DISPATCH_FUNCTION_ARG1(primitiv::functions::flatten, JsNode)
      END_DISPATCH()
    } catch (const primitiv::Error& e) {
      Nan::ThrowError(e.what());
    }
  }

  NAN_METHOD(Transpose) {
    try {
      DISPATCH_FUNCTION_ARG1(primitiv::functions::transpose, JsNode)
      END_DISPATCH()
    } catch (const primitiv::Error& e) {
      Nan::ThrowError(e.what());
    }
  }

  NAN_METHOD(Matmul) {
    try {
      DISPATCH_FUNCTION_ARG2(primitiv::functions::matmul, JsNode, JsNode)
      END_DISPATCH()
    } catch (const primitiv::Error& e) {
      Nan::ThrowError(e.what());
    }
  }

  NAN_METHOD(Abs) {
    try {
      DISPATCH_FUNCTION_ARG1(primitiv::functions::abs, JsNode)
      END_DISPATCH()
    } catch (const primitiv::Error& e) {
      Nan::ThrowError(e.what());
    }
  }

  NAN_METHOD(Sqrt) {
    try {
      DISPATCH_FUNCTION_ARG1(primitiv::functions::sqrt, JsNode)
      END_DISPATCH()
    } catch (const primitiv::Error& e) {
      Nan::ThrowError(e.what());
    }
  }

  NAN_METHOD(Exp) {
    try {
      DISPATCH_FUNCTION_ARG1(primitiv::functions::exp, JsNode)
      END_DISPATCH()
    } catch (const primitiv::Error& e) {
      Nan::ThrowError(e.what());
    }
  }

  NAN_METHOD(Log) {
    try {
      DISPATCH_FUNCTION_ARG1(primitiv::functions::log, JsNode)
      END_DISPATCH()
    } catch (const primitiv::Error& e) {
      Nan::ThrowError(e.what());
    }
  }

  NAN_METHOD(Tanh) {
    try {
      DISPATCH_FUNCTION_ARG1(primitiv::functions::tanh, JsNode)
      END_DISPATCH()
    } catch (const primitiv::Error& e) {
      Nan::ThrowError(e.what());
    }
  }

  NAN_METHOD(Sigmoid) {
    try {
      DISPATCH_FUNCTION_ARG1(primitiv::functions::sigmoid, JsNode)
      END_DISPATCH()
    } catch (const primitiv::Error& e) {
      Nan::ThrowError(e.what());
    }
  }

  NAN_METHOD(Softplus) {
    try {
      DISPATCH_FUNCTION_ARG1(primitiv::functions::softplus, JsNode)
      END_DISPATCH()
    } catch (const primitiv::Error& e) {
      Nan::ThrowError(e.what());
    }
  }

  NAN_METHOD(Sin) {
    try {
      DISPATCH_FUNCTION_ARG1(primitiv::functions::sin, JsNode)
      END_DISPATCH()
    } catch (const primitiv::Error& e) {
      Nan::ThrowError(e.what());
    }
  }

  NAN_METHOD(Cos) {
    try {
      DISPATCH_FUNCTION_ARG1(primitiv::functions::cos, JsNode)
      END_DISPATCH()
    } catch (const primitiv::Error& e) {
      Nan::ThrowError(e.what());
    }
  }

  NAN_METHOD(Tan) {
    try {
      DISPATCH_FUNCTION_ARG1(primitiv::functions::tan, JsNode)
      END_DISPATCH()
    } catch (const primitiv::Error& e) {
      Nan::ThrowError(e.what());
    }
  }

  NAN_METHOD(Relu) {
    try {
      DISPATCH_FUNCTION_ARG1(primitiv::functions::relu, JsNode)
      END_DISPATCH()
    } catch (const primitiv::Error& e) {
      Nan::ThrowError(e.what());
    }
  }

  NAN_METHOD(Lrelu) {
    try {
      DISPATCH_FUNCTION_ARG1(primitiv::functions::lrelu, JsNode)
      END_DISPATCH()
    } catch (const primitiv::Error& e) {
      Nan::ThrowError(e.what());
    }
  }

  NAN_METHOD(Prelu) {
    try {
      DISPATCH_FUNCTION_ARG2(primitiv::functions::prelu, JsNode, float)
      END_DISPATCH()
    } catch (const primitiv::Error& e) {
      Nan::ThrowError(e.what());
    }
  }

  NAN_METHOD(Elu) {
    try {
      DISPATCH_FUNCTION_ARG2(primitiv::functions::elu, JsNode, float)
      END_DISPATCH()
    } catch (const primitiv::Error& e) {
      Nan::ThrowError(e.what());
    }
  }

  NAN_METHOD(Max) {
    try {
      DISPATCH_FUNCTION_ARG2(primitiv::functions::max, JsNode, std::uint32_t)
      END_DISPATCH()
    } catch (const primitiv::Error& e) {
      Nan::ThrowError(e.what());
    }
  }

  NAN_METHOD(Min) {
    try {
      DISPATCH_FUNCTION_ARG2(primitiv::functions::min, JsNode, std::uint32_t)
      END_DISPATCH()
    } catch (const primitiv::Error& e) {
      Nan::ThrowError(e.what());
    }
  }

  NAN_METHOD(Sum) {
    try {
      DISPATCH_FUNCTION_ARG2(primitiv::functions::sum, JsNode, std::uint32_t)
      END_DISPATCH()
    } catch (const primitiv::Error& e) {
      Nan::ThrowError(e.what());
    }
  }

  NAN_METHOD(Broadcast) {
    try {
      DISPATCH_FUNCTION_ARG3(primitiv::functions::broadcast, JsNode, std::uint32_t, std::uint32_t)
      END_DISPATCH()
    } catch (const primitiv::Error& e) {
      Nan::ThrowError(e.what());
    }
  }

  NAN_METHOD(Logsumexp) {
    try {
      DISPATCH_FUNCTION_ARG2(primitiv::functions::logsumexp, JsNode, std::uint32_t)
      END_DISPATCH()
    } catch (const primitiv::Error& e) {
      Nan::ThrowError(e.what());
    }
  }

  NAN_METHOD(LogSoftmax) {
    try {
      DISPATCH_FUNCTION_ARG2(primitiv::functions::log_softmax, JsNode, std::uint32_t)
      END_DISPATCH()
    } catch (const primitiv::Error& e) {
      Nan::ThrowError(e.what());
    }
  }

  NAN_METHOD(Softmax) {
    try {
      DISPATCH_FUNCTION_ARG2(primitiv::functions::softmax, JsNode, std::uint32_t)
      END_DISPATCH()
    } catch (const primitiv::Error& e) {
      Nan::ThrowError(e.what());
    }
  }

  NAN_METHOD(StopGradient) {
    try {
      DISPATCH_FUNCTION_ARG1(primitiv::functions::stop_gradient, JsNode)
      END_DISPATCH()
    } catch (const primitiv::Error& e) {
      Nan::ThrowError(e.what());
    }
  }

  NAN_METHOD(ConstantNode) {
    try {
      PRIMITIV_NODE_GET_DEVICE(2)
      PRIMITIV_NODE_GET_GRAPH(3)
      DISPATCH_FUNCTION_ARG2_EXT(primitiv::functions::constant_node, JsShape, float, device, g)
      END_DISPATCH()
    } catch (const primitiv::Error& e) {
      Nan::ThrowError(e.what());
    }
  }

  NAN_METHOD(IdentityNode) {
    try {
      PRIMITIV_NODE_GET_DEVICE(1)
      PRIMITIV_NODE_GET_GRAPH(2)
      DISPATCH_FUNCTION_ARG1_EXT(primitiv::functions::identity_node, std::uint32_t, device, g)
      END_DISPATCH()
    } catch (const primitiv::Error& e) {
      Nan::ThrowError(e.what());
    }
  }

  NAN_METHOD(ZerosNode) {
    try {
      PRIMITIV_NODE_GET_DEVICE(1)
      PRIMITIV_NODE_GET_GRAPH(2)
      DISPATCH_FUNCTION_ARG1_EXT(primitiv::functions::zeros_node, JsShape, device, g)
      END_DISPATCH()
    } catch (const primitiv::Error& e) {
      Nan::ThrowError(e.what());
    }
  }

  NAN_METHOD(OnesNode) {
    try {
      PRIMITIV_NODE_GET_DEVICE(1)
      PRIMITIV_NODE_GET_GRAPH(2)
      DISPATCH_FUNCTION_ARG1_EXT(primitiv::functions::ones_node, JsShape, device, g)
      END_DISPATCH()
    } catch (const primitiv::Error& e) {
      Nan::ThrowError(e.what());
    }
  }

  NAN_METHOD(Dropout) {
    try {
      DISPATCH_FUNCTION_ARG3(primitiv::functions::dropout, JsNode, float, bool)
      END_DISPATCH()
    } catch (const primitiv::Error& e) {
      Nan::ThrowError(e.what());
    }
  }

  void register_functions(v8::Local<v8::Object> target) {
    auto functions = Nan::New<v8::Object>();
    Nan::Set(target, Nan::New("functions").ToLocalChecked(), functions);

    Nan::SetMethod(functions, "positive", Positive);
    Nan::SetMethod(functions, "negative", Negative);
    Nan::SetMethod(functions, "add", Add);
    Nan::SetMethod(functions, "subtract", Subtract);
    Nan::SetMethod(functions, "multiply", Multiply);
    Nan::SetMethod(functions, "divide", Divide);
    Nan::SetMethod(functions, "pow", Pow);
    Nan::SetMethod(functions, "pown", Pown);
    Nan::SetMethod(functions, "input_node", InputNode);
    Nan::SetMethod(functions, "input", InputNode);
    Nan::SetMethod(functions, "parameter_node", ParameterNode);
    Nan::SetMethod(functions, "parameter", ParameterNode);
    Nan::SetMethod(functions, "copy", Copy);
//     Nan::SetMethod(functions, "pick", Pick);
    Nan::SetMethod(functions, "slice", Slice);
//     Nan::SetMethod(functions, "split", Split);
//     Nan::SetMethod(functions, "concat", Concat);
    Nan::SetMethod(functions, "reshape", Reshape);
    Nan::SetMethod(functions, "flatten", Flatten);
    Nan::SetMethod(functions, "transpose", Transpose);
    Nan::SetMethod(functions, "matmul", Matmul);
    Nan::SetMethod(functions, "abs", Abs);
    Nan::SetMethod(functions, "sqrt", Sqrt);
    Nan::SetMethod(functions, "exp", Exp);
    Nan::SetMethod(functions, "log", Log);
    Nan::SetMethod(functions, "tanh", Tanh);
    Nan::SetMethod(functions, "sigmoid", Sigmoid);
    Nan::SetMethod(functions, "softplus", Softplus);
    Nan::SetMethod(functions, "sin", Sin);
    Nan::SetMethod(functions, "cos", Cos);
    Nan::SetMethod(functions, "tan", Tan);
    Nan::SetMethod(functions, "relu", Relu);
    Nan::SetMethod(functions, "lrelu", Lrelu);
    Nan::SetMethod(functions, "prelu", Prelu);
    Nan::SetMethod(functions, "elu", Elu);
    Nan::SetMethod(functions, "max", Max);
    Nan::SetMethod(functions, "min", Min);
    Nan::SetMethod(functions, "sum", Sum);
    Nan::SetMethod(functions, "broadcast", Broadcast);
    Nan::SetMethod(functions, "logsumexp", Logsumexp);
    Nan::SetMethod(functions, "log_softmax", LogSoftmax);
    Nan::SetMethod(functions, "softmax", Softmax);
//     Nan::SetMethod(functions, "softmax_cross_entropy", SoftmaxCrossEntropy);
    Nan::SetMethod(functions, "stop_gradient", StopGradient);
//     Nan::SetMethod(functions, "conv2d", Conv2d);
//     Nan::SetMethod(functions, "max_pool2d", MaxPool2d);
    Nan::SetMethod(functions, "constant_node", ConstantNode);
    Nan::SetMethod(functions, "constant", ConstantNode);
    Nan::SetMethod(functions, "identity_node", IdentityNode);
    Nan::SetMethod(functions, "identity", IdentityNode);
//     Nan::SetMethod(functions, "selu", Selu);
//     Nan::SetMethod(functions, "sum", Sum);
//     Nan::SetMethod(functions, "mean", Mean);
    Nan::SetMethod(functions, "zeros_node", ZerosNode);
    Nan::SetMethod(functions, "zeros", ZerosNode);
    Nan::SetMethod(functions, "ones_node", OnesNode);
    Nan::SetMethod(functions, "ones", OnesNode);
    Nan::SetMethod(functions, "dropout", Dropout);

    batch::register_functions(functions);
    random::register_functions(functions);
  }

  namespace batch {

    NAN_METHOD(Slice) {
      try {
        DISPATCH_FUNCTION_ARG3(primitiv::functions::batch::slice, JsNode, std::uint32_t, std::uint32_t)
        END_DISPATCH()
      } catch (const primitiv::Error& e) {
        Nan::ThrowError(e.what());
      }
    }

    NAN_METHOD(Mean) {
      try {
        DISPATCH_FUNCTION_ARG1(primitiv::functions::batch::mean, JsNode)
        END_DISPATCH()
      } catch (const primitiv::Error& e) {
        Nan::ThrowError(e.what());
      }
    }

    NAN_METHOD(Normalize) {
      try {
        DISPATCH_FUNCTION_ARG1(primitiv::functions::batch::normalize, JsNode)
        END_DISPATCH()
      } catch (const primitiv::Error& e) {
        Nan::ThrowError(e.what());
      }
    }

    void register_functions(v8::Local<v8::Object> target) {
      auto batch = Nan::New<v8::Object>();
      Nan::Set(target, Nan::New("batch").ToLocalChecked(), batch);

  //     Nan::SetMethod(batch, "pick", Pick);
      Nan::SetMethod(batch, "slice", Slice);
  //     Nan::SetMethod(batch, "split", Split);
  //     Nan::SetMethod(batch, "concat", Concat);
  //     Nan::SetMethod(batch, "sum", Sum);
      Nan::SetMethod(batch, "mean", Mean);
      Nan::SetMethod(batch, "normalize", Normalize);
    }

  }

  namespace random {

    NAN_METHOD(BernoulliNode) {
      try {
        PRIMITIV_NODE_GET_DEVICE(2)
        PRIMITIV_NODE_GET_GRAPH(3)
        DISPATCH_FUNCTION_ARG2_EXT(primitiv::functions::random::bernoulli_node, JsShape, float, device, g)
        END_DISPATCH()
      } catch (const primitiv::Error& e) {
        Nan::ThrowError(e.what());
      }
    }

    NAN_METHOD(UniformNode) {
      try {
        PRIMITIV_NODE_GET_DEVICE(3)
        PRIMITIV_NODE_GET_GRAPH(4)
        DISPATCH_FUNCTION_ARG3_EXT(primitiv::functions::random::uniform_node, JsShape, float, float, device, g)
        END_DISPATCH()
      } catch (const primitiv::Error& e) {
        Nan::ThrowError(e.what());
      }
    }

    NAN_METHOD(NormalNode) {
      try {
        PRIMITIV_NODE_GET_DEVICE(3)
        PRIMITIV_NODE_GET_GRAPH(4)
        DISPATCH_FUNCTION_ARG3_EXT(primitiv::functions::random::normal_node, JsShape, float, float, device, g)
        END_DISPATCH()
      } catch (const primitiv::Error& e) {
        Nan::ThrowError(e.what());
      }
    }

    NAN_METHOD(LogNormalNode) {
      try {
        PRIMITIV_NODE_GET_DEVICE(3)
        PRIMITIV_NODE_GET_GRAPH(4)
        DISPATCH_FUNCTION_ARG3_EXT(primitiv::functions::random::log_normal_node, JsShape, float, float, device, g)
        END_DISPATCH()
      } catch (const primitiv::Error& e) {
        Nan::ThrowError(e.what());
      }
    }

    NAN_METHOD(GumbelNode) {
      try {
        PRIMITIV_NODE_GET_DEVICE(3)
        PRIMITIV_NODE_GET_GRAPH(4)
        DISPATCH_FUNCTION_ARG3_EXT(primitiv::functions::random::gumbel_node, JsShape, float, float, device, g)
        END_DISPATCH()
      } catch (const primitiv::Error& e) {
        Nan::ThrowError(e.what());
      }
    }

    void register_functions(v8::Local<v8::Object> target) {
      auto random = Nan::New<v8::Object>();
      Nan::Set(target, Nan::New("random").ToLocalChecked(), random);

      Nan::SetMethod(random, "bernoulli_node", BernoulliNode);
      Nan::SetMethod(random, "bernoulli", BernoulliNode);
      Nan::SetMethod(random, "uniform_node", UniformNode);
      Nan::SetMethod(random, "uniform", UniformNode);
      Nan::SetMethod(random, "normal_node", NormalNode);
      Nan::SetMethod(random, "normal", NormalNode);
      Nan::SetMethod(random, "log_normal_node", LogNormalNode);
      Nan::SetMethod(random, "log_normal", LogNormalNode);
      Nan::SetMethod(random, "gumbel_node", GumbelNode);
      Nan::SetMethod(random, "gumbel", GumbelNode);
    }

  }

#undef DISPATCH_FUNCTION_ARG1
#undef DISPATCH_FUNCTION_ARG1_EXT
#undef DISPATCH_FUNCTION_ARG2
#undef DISPATCH_FUNCTION_ARG2_EXT
#undef DISPATCH_FUNCTION_ARG3
#undef DISPATCH_FUNCTION_ARG3_EXT
#undef DISPATCH_FUNCTION_ARG4
#undef DISPATCH_FUNCTION_ARG4_EXT
#undef END_DISPATCH

} // namespace functions

} // namespace node

} // namespace primitiv

