project(
    'libDWG',
    'cpp',
    'c',
    version: '1.0.1',
    default_options: ['cpp_std=c++17', 'buildtype=debugoptimized'],
)

build_tests = get_option('build_tests')
build_examples = get_option('build_examples')

iconv_dep = dependency('iconv', required: true)
fmt_dep = dependency('fmt', required: true)

libdwg_version_major = 1
libdwg_version_minor = 0
libdwg_version_patch = 1
libdwg_version_string = '1.0.1'

subdir('include')

configure_file(input: 'include/dwg/dwg_version.h.in', output: 'build/dwg/dwg_version.h')

headers = files('build/dwg/dwg_version.h', 'include/dwg/exports.h')

shared_library(
    'dwg',
    sources: [headers],
    dependencies: [iconv_dep, fmt_dep],
    install: true,
)

if build_examples
    subdir('examples')
endif

if build_tests
    subdir('tests')
endif