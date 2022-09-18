#!/bin/bash

# setup for dnn models
# 2022-06-01 K.OHWADA

DLIB=/usr/local/share/dlib
MMOD=mmod_human_face_detector.dat
MMOD_BZ2=${MMOD}.bz2
RESNET=dlib_face_recognition_resnet_model_v1.dat
RESNET_BZ2=${RESNET}.bz2
LANDMARKS=shape_predictor_68_face_landmarks.dat
LANDMARKS_BZ2=${LANDMARKS}.bz2


mkdir ${DLIB}


cd work

wget https://github.com/davisking/dlib-models/blob/master/${MMOD_BZ2}

wget https://github.com/davisking/dlib-models/raw/master/${LANDMARKS_BZ2}

# wget https://github.com/davisking/dlib-models/raw/master/${RESNET_BZ2}


bunzip2 ${MMOD_BZ2}
bunzip2 ${LANDMARKS_BZ2}

# bunzip2 ${RESNET_BZ2}


cp *.dat ${DLIB}

ls -la ${DLIB}

