project('trktcli', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3','cpp_std=c++20'])

subproject('fmt')
fmt = dependency('fmt', version: '>8.0.0')

exe = executable('trktcli', 'trktcli.cpp',
  dependencies: fmt,
  install : true)

test('basic', exe)
