project(
  'game-of-life',
  'cpp',
  version: '2.0.0',
  meson_version: '>= 1.2.0',
  default_options: [
    'warning_level=3',
    'cpp_std=c++17',
    'default_library=static',
  ],
)

add_global_arguments('-Wno-unused', language: 'cpp')

incdir = include_directories('include')

sdl2_dep = dependency('sdl2', required: true)
sdl2_ttf_dep = dependency('sdl2_ttf', required: true)
sdl2_gfx_dep = dependency('sdl2_gfx', required: true)

# this shit is so cursed, how can i include them in the install dir???
install_data('lib/SDL2.dll', install_dir: meson.current_build_dir())
install_data('lib/SDL2_ttf.dll', install_dir: meson.current_build_dir())
install_data('lib/libgcc_s_seh-1.dll', install_dir: meson.current_build_dir())
install_data('lib/libstdc++-6.dll', install_dir: meson.current_build_dir())
install_data('lib/libharfbuzz-0.dll', install_dir: meson.current_build_dir())
install_data('lib/libwinpthread-1.dll', install_dir: meson.current_build_dir())
install_data('lib/libfreetype-6.dll', install_dir: meson.current_build_dir())
install_data('lib/libSDL2_gfx-1-0-0.dll', install_dir: meson.current_build_dir())
install_data('lib/libbz2-1.dll', install_dir: meson.current_build_dir())
install_data('lib/libpng16-16.dll', install_dir: meson.current_build_dir())
install_data('lib/libbrotlidec.dll', install_dir: meson.current_build_dir())
install_data('lib/zlib1.dll', install_dir: meson.current_build_dir())
install_data('lib/libgraphite2.dll', install_dir: meson.current_build_dir())
install_data('lib/libglib-2.0-0.dll', install_dir: meson.current_build_dir())
install_data('lib/libintl-8.dll', install_dir: meson.current_build_dir())
install_data('lib/libbrotlicommon.dll', install_dir: meson.current_build_dir())
install_data('lib/libiconv-2.dll', install_dir: meson.current_build_dir())
install_data('lib/libpcre2-8-0.dll', install_dir: meson.current_build_dir())

executable(
  'game-of-life',
  sources: [
    'src/core/app/app_clean.cpp',
    'src/core/app/app_handle_event.cpp',
    'src/core/app/app_init.cpp',
    'src/core/app/app_render.cpp',
    'src/core/app/app_run.cpp',
    'src/core/app/app_update.cpp',
    'src/core/app/app.cpp',
    'src/helper/logger.cpp',
    'src/main.cpp',
  ],
  include_directories: incdir,
  dependencies: [sdl2_dep, sdl2_ttf_dep, sdl2_gfx_dep],
)