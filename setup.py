from distutils.core import setup, Extension

sources = ['chili_tag_detector.cpp']

chili_tag_detector = Extension('chili_tag_detector',
                                      sources = sources,
                                      include_dirs= ['/usr/include', '/usr/local/include/chilitags'],
                                      libraries = ['opencv_core', 'opencv_highgui', 'opencv_imgcodecs', 'chilitags'],
                                      library_dirs = ['/usr/local/lib'],                  
                                      extra_link_args=['-lstdc++'],
                                      extra_compile_args=['-std=c++11'],
                                      language='c++11')

setup(name = 'chili_tag_detector',
      version = '1.0',
      description = 'Python Wrapper for chili tag detection functionality',
      ext_modules = [chili_tag_detector],
      author='Philipp Becker',
      author_email='philippbecker93@googlemail.com')
