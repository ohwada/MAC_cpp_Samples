#!/bin/bash

# 2020-07-01 K.OHWADA

# fix missing openssl files in catalina
# reference : https://gist.github.com/llbbl/c54f44d028d014514d5d837f64e60bac

ssl_ver=1.1.1h
dir_ssl_lib=/usr/local/Cellar/openssl@1.1/${ssl_ver}/lib


# echo 'update brew'
# brew update

# echo 'upgrade brew'
# brew upgrade

# echo 'brew install openssl'
# brew install openssl@1.1


if [ ! -e ${dir_ssl_lib}/libssl.1.1.dylib ]; then
    echo 'not found libssl.1.1.dylib'
    echo 'brew install openssl'
    brew install openssl@1.1
fi


echo 'backup existing lib files, if they exist'

if [ -f /usr/local/lib/libssl.dylib ]; then
    mv /usr/local/lib/libssl.dylib /usr/local/lib/libssl_bak.dylib
fi

if [ -f /usr/local/lib/libcrypto.dylib ]; then
    mv /usr/local/lib/libcrypto.dylib /usr/local/lib/libcrypto_bak.dylib
fi

# Leaving some commands to check directory contents 
# ls -al /usr/local/Cellar/openssl@1.1/1.1.1d/lib
# ls -al /usr/local/lib/libssl* && ls -al /usr/local/lib/libcrypto*

echo 'add symlink to missing openssl libs'

if [ -f ${dir_ssl_lib}/libssl.dylib ]; then
    sudo ln -s ${dir_ssl_lib}/libssl.dylib /usr/local/lib/libssl.dylib
fi 

if [ -f ${dir_ssl_lib}/libcrypto.dylib ]; then
    sudo ln -s ${dir_ssl_lib}/libcrypto.dylib /usr/local/lib/libcrypto.dylib
fi

echo
ls -la /usr/local/lib/libssl.dylib
ls -la /usr/local/lib/libcrypto.dylib

