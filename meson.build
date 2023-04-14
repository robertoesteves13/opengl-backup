project('opengl-course', 'cpp')

inc = include_directories('include')

glfw_proj = subproject('glfw')
glm_proj = subproject('glm')
glad_proj = subproject('glad')
stb_image_proj = subproject('stb_image')

glfw_dep = glfw_proj.get_variable('glfw_dep')
glm_dep = glm_proj.get_variable('glm_dep')
glad_dep = glad_proj.get_variable('glad_dep')
stb_image_dep = stb_image_proj.get_variable('stb_image_dep')

sources = [ 'src/main.cpp', 'src/mesh.cpp', 'src/shader.cpp', 'src/window.cpp', 'src/camera.cpp', 'src/texture.cpp']

# Setup symlink
setup = find_program('setup.py')
run_command(setup, 'shaders')

executable('opengl-course', sources,
  dependencies: [glad_dep, glfw_dep, glm_dep, stb_image_dep],
  cpp_args: [ '-fsanitize=address','-Wall', '-Werror' ],
  link_args: ['-fsanitize=address']
)
