#!/bin/bash

if [ $# -lt 3 ] ; then
	echo "usage: $0 <system> <arch> <build_dir>"
	exit 1
fi

mkdir -p tmp
python c_setup.py $1 $2 sources | grep -v python.cpp > tmp/sources.txt
python c_setup.py $1 $2 extra_compile_args > tmp/c_flags.txt
python c_setup.py $1 $2 include_dirs > tmp/include.txt
python c_setup.py $1 $2 cpp_flags > tmp/cpp_flags.txt

if meson setup $3; then
  pushd $3
  meson compile
  popd
fi

rm -Rf tmp


