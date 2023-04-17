project('glad', 'c')

inc = include_directories('include')
sources = [ 'src/glad.c' ]

glad_lib = static_library('glad', 
  sources,
  include_directories: inc
)

glad_dep = declare_dependency(
  include_directories: inc,
  link_with: glad_lib,
)
