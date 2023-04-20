# About

This is some dump I'm making while following an OpenGL course. You can navigate by commit to see everything I've been working on during the course and compile to see the result (some of them are crazy stuff :D)

# How to build and run

You only need meson and a C/C++ compiler since all the other dependencies are automatically installed by meson.

Setup build directory by running `meson build` and compile with `ninja -C build`. It should create an executable inside the build directory.

## *nix

Run the executable inside the build folder.

## Windows

You might need to setup more things on meson, [see this.](https://mesonbuild.com/Using-with-Visual-Studio.html). To produce a working program, go inside the build directory and run `meson install`. It will create a folder called `release` with the program ready to be run and packaged.