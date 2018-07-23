"use strict";

const {
  Device, Graph, Parameter, Shape, devices, initializers, functions, optimizers
} = require("../../build/Release/primitiv");

const D = devices;
const I = initializers;
const F = functions;
const O = optimizers;

function main() {
  const dev = D.Naive();
  Device.set_default(dev);

  // Parameters
  const pw1 = Parameter(Shape([8, 2]), I.XavierUniform());
  const pb1 = Parameter(Shape([8]), I.Constant(0));
  const pw2 = Parameter(Shape([1, 8]), I.XavierUniform());
  const pb2 = Parameter(Shape([]), I.Constant(0));

  // Optimizer
  const optimizer = O.SGD(0.1);

  // Registers parameters.
  optimizer.add(pw1, pb1, pw2, pb2);

  // Training data
  const input_data = [
     1,  1,  // Sample 1
     1, -1,  // Sample 2
    -1,  1,  // Sample 3
    -1, -1,  // Sample 4
  ];
  const output_data = [
     1,  // Label 1
    -1,  // Label 2
    -1,  // Label 3
     1,  // Label 4
  ];

  const g = Graph();
  Graph.set_default(g);

  for (let i = 0; i < 10; ++i) {
    g.clear();

    // Builds a computation graph.
    const x = F.input(Shape([2], 4), input_data);
    const w1 = F.parameter(pw1);
    const b1 = F.parameter(pb1);
    const w2 = F.parameter(pw2);
    const b2 = F.parameter(pb2);
    const h = F.tanh(F.add(F.matmul(w1, x), b1));
    const y = F.add(F.matmul(w2, h), b2);

    // Obtains values.
    const y_val = y.to_array();
    console.log("epoch " + i + ":");
    for (let j = 0; j < 4; ++j) {
      console.log("  [" + j + "]: " + y_val[j]);
    }
    // Extends the computation graph to calculate loss values.
    const t = F.input(Shape([], 4), output_data);
    const diff = F.subtract(t, y);
    const loss = F.batch.mean(F.multiply(diff, diff));

    // Obtains the loss.
    const loss_val = loss.to_float();
    console.log("  loss: " + loss_val);

    // Updates parameters.
    optimizer.reset_gradients();
    loss.backward();
    optimizer.update();
  }
}

main();

global.gc();
