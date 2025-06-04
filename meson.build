project('EPDC', 'c')

gtkdep = dependency('gtk4')

sourcefiles=files(
  'src/main.c',
  'src/ui/setup_style.c',
  'src/ui/header.c',
  'src/ui/main_content.c',
  'src/ui/canvas.c',
  'src/ui/tab_ui.c',
  'src/ui/ope_prop.c',

  'src/model/text_object.c',
  'src/model/object_common.c'
  )

include_dir= include_directories('src/include/ui', 'src/include/model')

executable(
  'EPDC',
  sourcefiles,
  dependencies: gtkdep,
  install: false,
  include_directories: include_dir,
  c_args : [
    '-finput-charset=UTF-8',
    '-fexec-charset=UTF-8'
  ],
)