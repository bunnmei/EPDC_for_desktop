$ meson setup _build
$ ninja -C _build && ./_build/EPDC

$ gdb --args ./_build/EPDC ^C
(gdb) run