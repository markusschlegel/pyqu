from distutils.core import setup, Extension

pyqu_module = Extension('pyqu',
                        libraries = ['quantum'],
                        library_dirs = ['lib'],
                        include_dirs = ['inc'],
                        sources = ['src/pyqumodule.c'])

setup(  name = 'Pyqu',
        version = '0.1',
        description = 'Module for quantum computation simulation',
        author = 'Eric Marcos Pitarch',
        author_email = 'ericmarcos.p@gmail.com',
        url = 'http://code.google.com/p/pyqu/',
        long_description = '',
        ext_modules = [pyqu_module])