project('opengl-course', 'cpp')

inc = include_directories('include')

glfw_proj = subproject('glfw')
glm_proj = subproject('glm')
glad_proj = subproject('glad')

glfw_dep = glfw_proj.get_variable('glfw_dep')
glm_dep = glm_proj.get_variable('glm_dep')
glad_dep = glad_proj.get_variable('glad_dep')

sources = [ 'src/main.cpp', 'src/mesh.cpp', 'src/shader.cpp', 'src/window.cpp', 'src/camera.cpp']

# Setup symlink
setup = find_program('setup.py')
run_command(setup, 'shaders')

executable('opengl-course', sources,
  dependencies: [glad_dep, glfw_dep, glm_dep])
