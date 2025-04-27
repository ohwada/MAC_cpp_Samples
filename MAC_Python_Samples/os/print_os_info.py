# Python: display os info
# 2025-04-10  K.OHWADA

# https://docs.python.org/ja/3/library/os.html

import  os

print( 'login: ', os.getlogin() )

print( 'uid: ', os.getuid() )

print( 'gid: ', os.getgid() )

print( 'egid: ', os.getegid() )

print( 'groups: ', os.getgroups() )



print( 'pid: ', os.getpid() )

print( 'pgrp: ', os.getpgrp() )

print( 'ppid: ', os.getppid() )

print( 'supports_bytes_environ: ', os.supports_bytes_environ )

print( 'ctermid: ', os.ctermid() )

print( 'name: ', os.name )

print( "uname: \n", os.uname() )

print( 'environ: \n', os.environ )

# print( "environb: \n", os.environb )






