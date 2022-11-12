#!/bin/bash

# setup for header files and lib file
# 2022-06-01 K.OHWADA

ROOT=/usr/local/opt/json_dto
INC=${ROOT}/include
INC_JSON_DTO=${INC}/json_dto

mkdir ${ROOT}
mkdir ${INC}
mkdir ${INC_JSON_DTO}

cp dev/json_dto/*.hpp ${INC_JSON_DTO}

ls ${INC}
ls  ${INC_JSON_DTO}

