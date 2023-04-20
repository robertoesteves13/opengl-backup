#!/usr/bin/env python3 

import os, glob, shutil, platform

if platform.system() == 'Windows':
    source_root = os.getenv('MESON_SOURCE_ROOT')
    build_root = os.getenv('MESON_BUILD_ROOT')
    dest_dir = 'release'
    install_prefix = os.getcwd()
    bin_dir = os.path.join(install_prefix, dest_dir, 'bin')
    
    if os.path.exists(os.path.join(build_root, dest_dir)):
        shutil.rmtree(os.path.join(build_root, dest_dir))
    
    shutil.copytree(os.path.join(source_root, 'resources'), os.path.join(install_prefix, dest_dir, 'resources'))
    shutil.copytree(os.path.join(source_root, 'shaders'), os.path.join(install_prefix, dest_dir, 'shaders'))
    
    glfw_dll_path = os.path.join(build_root, 'subprojects', 'glfw-*', '*.dll')
    imgui_dll_path = os.path.join(build_root, 'subprojects', 'imgui-*', '*.dll')
    
    shutil.copyfile(glob.glob(glfw_dll_path)[0], os.path.join(install_prefix ,dest_dir, 'glfw3-3.dll'))
    shutil.copyfile(glob.glob(imgui_dll_path)[0], os.path.join(install_prefix, dest_dir, 'imgui.dll'))
    
    shutil.copyfile(os.path.join(build_root, 'opengl-course.exe'), os.path.join(install_prefix, dest_dir, 'opengl-course.exe'))