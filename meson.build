project('opengl-course', 'cpp')

inc = include_directories('include', 'vendor')

sources = [ 'src/main.cpp', 'src/mesh.cpp', 'src/shader.cpp', 'src/window.cpp',
            'src/camera.cpp', 'src/texture.cpp', 'src/light.cpp']

imgui_options = ['glfw=enabled', 'opengl=enabled']
imgui_proj = subproject('imgui', default_options: imgui_options )

glad_proj = subproject('glad')

dependency_list = [
  dependency('glfw', fallback: ['glfw', 'glfw_dep']),
  dependency('glm', fallback: ['glm', 'glm_dep']),
  glad_proj.get_variable('glad_dep'),
  imgui_proj.get_variable('imgui_dep')
]

# Setup symlink
setup = find_program('setup.py')
run_command(setup, 'shaders')

executable('opengl-course', sources, dependencies: dependency_list)

meson.add_install_script('install.py')