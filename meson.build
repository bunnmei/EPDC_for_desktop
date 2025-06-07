project('EPDC', 'c')

gtkdep = dependency('gtk4')
libusb_dep = dependency('libusb-1.0')

sourcefiles=files(
  'src/main.c',
  'src/ui/setup_style.c',
  'src/ui/header.c',
  'src/ui/main_content.c',
  'src/ui/canvas.c',
  'src/ui/tab_ui.c',
  'src/ui/ope_prop.c',
  'src/ui/obj_list.c',
  'src/ui/USB_btn.c',

  'src/controller/add_obj.c',
  'src/controller/draw_canvas.c',
  'src/controller/change_prop.c',
  'src/controller/label_bind.c',
  'src/controller/usb_emit.c',

  'src/model/text_object.c',
  'src/model/object_common.c'
  )

include_dir= include_directories('src/include/ui', 'src/include/model', 'src/include/controller')

executable(
  'EPDC',
  sourcefiles,
  dependencies: [gtkdep, libusb_dep],
  install: false,
  include_directories: include_dir,
  c_args : [
    '-finput-charset=UTF-8',
    '-fexec-charset=UTF-8'
  ],
)