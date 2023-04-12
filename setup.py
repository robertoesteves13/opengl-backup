#!/usr/bin/env python3 

import os, sys, shutil

input_path = os.path.join(
    os.getenv('MESON_SOURCE_ROOT'), 
    os.getenv('MESON_SUBDIR'),
    'shaders')

output_path = os.path.join(
    os.getenv('MESON_BUILD_ROOT'), 
    os.getenv('MESON_SUBDIR'),
    'shaders')

os.symlink(input_path, output_path)
