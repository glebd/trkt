project('trktcli','cpp',
  version:'0.1',
  default_options:['warning_level=3','cpp_std=c++20'])

conan_pkgs={
  'poco':'poco/1.11.1@', # <- Must contain @, otherwise Conan will think it is a path
}

deps=[]

foreach pkg_name,conan_ref:conan_pkgs
  module_path=meson.current_build_dir()/'conan-cmake'/pkg_name
  run_command('conan','install',conan_ref,'-if',module_path,'-g','cmake_find_package',check:true)
  deps+=dependency(pkg_name,method:'cmake',cmake_module_path:module_path)
endforeach

subproject('fmt')
fmt=dependency('fmt',version:'>=8.0.0')

subproject('spdlog')
spdlog=dependency('spdlog',version:'>=1.9.2')

exe=executable('trktcli','trktcli.cpp',
  dependencies:[fmt, spdlog],
  install:true)

test('basic',exe)
