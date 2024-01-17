

project('webrtcnoisegain_c','c','cpp')

# Get the parmaters

fs = import('fs')
sources   = fs.read('tmp/sources.txt').strip().split('\n')
c_flags   = fs.read('tmp/c_flags.txt').strip().split('\n')
cpp_flags = fs.read('tmp/cpp_flags.txt').strip().split('\n')
include   = fs.read('tmp/include.txt').strip().split('\n')

cpp_flags = c_flags + cpp_flags
sources = ['webrtc_noise_gain_c.cpp'] + sources

# Target static library
inc = include_directories(include)
static_library('webrtcnoisegain_c', sources, c_args: c_flags, cpp_args: cpp_flags, include_directories: inc)
shared_library('webrtcnoisegain_c', sources, c_args: c_flags, cpp_args: cpp_flags, include_directories: inc)



