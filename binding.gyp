{
  "targets": [
    {
      "target_name": "primitiv",
      "sources": [
        "primitiv/primitiv.cc",
        "primitiv/Device.cc",
        "primitiv/Graph.cc",
        "primitiv/Initializer.cc",
        "primitiv/Optimizer.cc",
        "primitiv/Parameter.cc",
        "primitiv/Shape.cc",
        "primitiv/Tensor.cc",
        "primitiv/devices/Naive.cc",
        "primitiv/functions.cc",
        "primitiv/initializers/Constant.cc",
        "primitiv/initializers/Uniform.cc",
        "primitiv/initializers/Normal.cc",
        "primitiv/initializers/Identity.cc",
        "primitiv/initializers/XavierUniform.cc",
        "primitiv/initializers/XavierNormal.cc",
        "primitiv/initializers/XavierUniformConv2D.cc",
        "primitiv/initializers/XavierNormalConv2D.cc",
        "primitiv/optimizers/SGD.cc"
      ],
      "include_dirs" : [
        "<!(node -e \"require('nan')\")"
      ],
      'cflags': ['-fexceptions', '-std=c++11'],
      'cflags_cc': ['-fexceptions', '-std=c++11'],
      "libraries": [
        "-lprimitiv"
      ]
    }
  ]
}
