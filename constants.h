//
//  constants.h
//  FaceDetection
//
//  Created by Lillian on 2018/1/10.
//  Copyright © 2018年 Ran Wang. All rights reserved.
//

#ifndef constants_h
#define constants_h

namespace face_detection {
    const std::string OPENCV_VJ_MODEL_PATH = "../FaceDetection/models/haarcascade_frontalface_alt.xml";
    const std::string PICO_MODEL_PATH = "../FaceDetection/models/facefinder";
    const std::string OPEN_NPD_MODEL_PATH = "../FaceDetection/models/frontal_face_detector.bin";
    const std::string LOGGER_DIR = "../FaceDetection/logs";
    const double MIN_SIZE = 30;
    const double MAX_SIZE = 5000;
    const double CAMERA_WIDTH = 200;
    const double CAMERA_HEIGHT = 200;
}

#endif /* constants_h */
