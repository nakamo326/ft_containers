#!/bin/bash

# clone latest library
git clone --depth 1 git@github.com:llvm/llvm-project.git
git clone --depth 1 https://github.com/gcc-mirror/gcc

#copy vector source from llve
cp llvm-project/libcxx/include/vector llvm_vector.cpp
cp llvm-project/libcxx/include/__iterator/iterator_traits.h  llvm_iterator_traits.h
cp llvm-project/libcxx/include/__iterator/wrap_iter.h  llvm_wrap_iter.h

cp gcc/libstdc++-v3/include/bits/stl_vector.h gcc_vector.h