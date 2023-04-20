project('opengl-course', 'cpp')

inc = include_directories('include')

sources = [ 'src/main.cpp', 'src/mesh.cpp', 'src/shader.cpp', 'src/window.cpp',
            'src/camera.cpp', 'src/texture.cpp', 'src/light.cpp']

# Setup symlink
setup = find_program('setup.py')
run_command(setup, 'shaders')

executable('opengl-course', sources,
  dependencies: [
      dependency('glfw', fallback: ['glfw', 'glfw_dep']),
      dependency('glew', fallback: ['glew', 'glew_dep']),
      dependency('glad', fallback: ['glad', 'glad_dep']),
      dependency('glm', fallback: ['glm', 'glm_dep']),
      dependency('imgui', fallback: ['imgui', 'imgui_dep']),
      dependency('stb_image', fallback: ['stb_image', 'stb_image_dep']),
    ],
  cpp_args: [ '-fsanitize=address','-Wall', '-Werror' ],
  link_args: ['-fsanitize=address']
)
