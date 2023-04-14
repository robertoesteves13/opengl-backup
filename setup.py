#!/usr/bin/env python3 

import os, sys, shutil

def symlink_folders(folder):
    input_path = os.path.join(
        os.getenv('MESON_SOURCE_ROOT'), 
        os.getenv('MESON_SUBDIR'),
        folder)

    output_path = os.path.join(
        os.getenv('MESON_BUILD_ROOT'), 
        os.getenv('MESON_SUBDIR'),
        folder)

    os.symlink(input_path, output_path)

symlink_folders('shaders')
symlink_folders('resources')
