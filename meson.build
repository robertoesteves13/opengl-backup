project('opengl-course', 'cpp')

inc = include_directories('include')

glfw_proj = subproject('glfw')
glm_proj = subproject('glm')

glew_dep = dependency('glew')
glfw_dep = glfw_proj.get_variable('glfw_dep')
glm_dep = glm_proj.get_variable('glm_dep')

sources = [ 'src/main.cpp', 'src/mesh.cpp', 'src/shader.cpp', 'src/window.cpp']

executable('opengl-course', sources,
  dependencies: [glew_dep, glfw_dep, glm_dep])
