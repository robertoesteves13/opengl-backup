project('stb_image', 'c')

inc = include_directories('include')

stb_image_lib = library('stb_image', 
  include_directories: inc
)

stb_image_dep = declare_dependency(
  include_directories: inc,
  link_with: stb_image_lib,
)
