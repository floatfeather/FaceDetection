//
//  opencv_vj.h
//  FaceDetection
//
//  Created by Lillian on 2018/1/10.
//  Copyright © 2018年 Ran Wang. All rights reserved.
//

#ifndef opencv_vj_h
#define opencv_vj_h

#include <vector>
#include "opencv2/objdetect.hpp"
#include "opencv2/imgproc.hpp"
#include "face_detector.h"

namespace face_detection {
class OpenCVDetector : public FaceDetector{
public:
    OpenCVDetector();
    bool FaceDetect(const cv::Mat& img, std::vector<int>* face);
    std::string MethodName();
private:
    cv::CascadeClassifier cascade;
};
}

#endif /* opencv_vj_h */
