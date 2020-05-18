project('faltbar', 'c',
  version : '2020.05.17',
  license : 'MIT'
)
prefix = get_option('prefix')
libdir = get_option('libdir')
datadir = get_option('datadir')
webextensionsdir = join_paths(prefix, libdir, meson.project_name(), 'web-extensions')

conf = configuration_data()
conf.set_quoted('VERSION', meson.project_version())
conf.set_quoted('GETTEXT_PACKAGE', meson.project_name())
conf.set_quoted('WEB_EXTENSIONS_DIRECTORY', webextensionsdir)

gtk_dep = dependency('gtk+-3.0')
webkit_dep = dependency('webkit2gtk-4.0')
webkit_web_extension_dep = dependency('webkit2gtk-web-extension-4.0')


#
# PREFIX = get_option('prefix')
# DATA_DIR = join_paths(PREFIX, 'share')
# APP_DIR = join_paths(DATA_DIR, 'com.github.dulnan.faltbar')
# COMMON_DIR = join_paths(APP_DIR, 'common')
# SCRIPTS_DIR = join_paths(APP_DIR, 'scripts')
# WEB_EXTENSIONS_DIRECTORY = join_paths(APP_DIR, 'extensions')
# APPDATA_DIR = join_paths(DATA_DIR, 'metainfo')
#
# EXECUTABLE_NAME = 'faltbar'
#

#
# click_extension = [
#   'app/webkit-extension/click-extension.c'
# ]
#

#
add_global_arguments(
  '-DMARKER_VERSION="@0@"'.format(meson.project_version()),
  '-DWEB_EXTENSIONS_DIRECTORY="@0@"'.format(webextensionsdir),
  language : 'c'
)
#
subdir('app')
# shared_library(
#   'click-extension',
#   sources : [click_extension],
#   dependencies : deps,
#   install : true,
#   link_args: '-lm',
#   install_dir: WEB_EXTENSIONS_DIRECTORY
# )
#
# executable(
#   EXECUTABLE_NAME,
#   sources : [faltbar_sources],
#   dependencies : deps,
#   link_args: '-lm',
#   install : true
# )
