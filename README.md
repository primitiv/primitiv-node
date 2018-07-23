# primitiv-node
Node.js binding of primitiv.

# Prerequisites

* *primitiv* core library
* C++11 compiler
* Node.js
  * NAN

# Build

```shell
# Install NAN
$ npm install nan
# Build
$ node-gyp configure build
```

# Run an example

```shell
$ node --expose-gc ./example/xor/xor.js
```
