#!/bin/bash

export CPUS=`lscpu | grep "CPU(s):" | sed s/"CPU(s):                "//`
node ../../node_modules/node-gyp/bin/node-gyp configure
make -j${CPUS} -C build