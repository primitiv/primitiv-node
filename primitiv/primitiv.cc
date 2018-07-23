#include <nan.h>

#include "Device.h"
#include "Graph.h"
#include "Initializer.h"
#include "Optimizer.h"
#include "Parameter.h"
#include "Shape.h"
#include "Tensor.h"
#include "devices/devices.h"
#include "functions.h"
#include "initializers/initializers.h"
#include "optimizers/optimizers.h"

namespace primitiv {

namespace node {

NAN_MODULE_INIT(Init) {

  primitiv::node::JsDevice::register_functions(target);
  primitiv::node::JsGraph::register_functions(target);
  primitiv::node::JsInitializer::register_functions(target);
  primitiv::node::JsNode::register_functions(target);
  primitiv::node::JsOptimizer::register_functions(target);
  primitiv::node::JsParameter::register_functions(target);
  primitiv::node::JsShape::register_functions(target);
  primitiv::node::JsTensor::register_functions(target);
  primitiv::node::devices::register_functions(target);
  primitiv::node::functions::register_functions(target);
  primitiv::node::initializers::register_functions(target);
  primitiv::node::optimizers::register_functions(target);

}

}

}

NODE_MODULE(primitiv, primitiv::node::Init)
