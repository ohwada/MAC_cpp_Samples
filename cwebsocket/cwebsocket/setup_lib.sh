#!/bin/bash

# setup for header files and lib file
# 2022-10-01 K.OHWADA

ROOT=/usr/local/opt/cwebsocket
INC=${ROOT}/include
LIB=${ROOT}/lib
INC_CWS=${INC}/cwebsocket
INC_SUBPROTOCOL=${INC_CWS}/subprotocol
INC_ECHO=${INC_SUBPROTOCOL}/echo


mkdir ${ROOT}
mkdir ${INC}
mkdir ${LIB}
mkdir ${INC_CWS}
mkdir ${INC_SUBPROTOCOL}
mkdir ${INC_ECHO}

cp src/cwebsocket/*.h ${INC_CWS}
cp src/cwebsocket/subprotocol/echo/*.h ${INC_ECHO}

cp libwsserver.a  ${LIB}
cp libwsclient.a  ${LIB}


ls ${INC}
ls  ${LIB}

