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
#include "opencv2/imgproc.hpp"

namespace face_detection {
    bool opencv_vj_detect(const cv::Mat& img, std::vector<int>* face, double min_size = 30, double scale = 1, bool tryflip = true);
}

#endif /* opencv_vj_h */
