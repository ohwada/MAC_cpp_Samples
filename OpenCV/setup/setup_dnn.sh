#!/bin/bash

# setup for dnn models
# 2022-06-01 K.OHWADA

ROOT=/usr/local/share/opencv4
DNN=${ROOT}/dnn
MODELS=${DNN}/models

YUNET=face_detection_yunet_2022mar.onnx
SFACE=face_recognition_sface_2021dec.onnx

mkdir ${DNN}
mkdir ${MODELS}

cd work

wget https://github.com/opencv/opencv_zoo/blob/master/models/face_detection_yunet/${YUNET}?raw=true

wget https://github.com/opencv/opencv_zoo/blob/master/models/face_recognition_sface/${SFACE}?raw=true

mv ${YUNET}?raw=true ${YUNET}

mv ${SFACE}?raw=true ${SFACE}

cp *.onnx ${MODELS}

ln -s ${MODELS}/${YUNET}  ${MODELS}/face_detection_yunet.onnx

ln -s ${MODELS}/${SFACE}  ${MODELS}/face_recognition_sface

ls -la ${MODELS}

