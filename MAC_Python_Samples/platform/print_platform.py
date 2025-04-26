# Python: platform info
# 2025-04-10  K.OHWADA

# https://docs.python.org/ja/3/library/platform.html

import  platform

print( 'platform: ', platform.platform() )

print( 'architecture: ', platform.architecture() )

print( 'system: ', platform. system() )

print( 'version: ', platform. version() )

print( 'release: ', platform. release() )

print( 'system alias: ', platform. system_alias( platform.system(), platform.release(), platform.version() ) )

print( 'machine: ', platform.machine() )

print( 'processor: ', platform.processor() )

print( 'uname: ', platform. uname() )

print( 'node: ', platform. node() )

print( 'python build: ', platform. python_build() )

print( 'python compiler: ', platform. python_compiler() )

print( 'python branch: ', platform. python_branch() )

print( 'python implementation: ', platform. python_implementation() )

print( 'python version: ', platform. python_version() )

print( 'python revision: ', platform. python_revision() )

print( 'python version tuple: ', platform. python_version_tuple() )

print( 'mac ver: ', platform. mac_ver() )


