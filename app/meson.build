faltbar_sources = [
  'main.c',
]

deps = [
  dependency('gtk+-3.0', version : '>=3.20'),
  dependency('webkit2gtk-4.0')
]

executable(
  'faltbar',
  sources : [faltbar_sources],
  dependencies : deps,
  link_args: '-lm',
  install : true
)

subdir('webkit-extension')
