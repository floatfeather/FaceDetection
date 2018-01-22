//
//  tools.h
//  FaceDetection
//
//  Created by Lillian on 2018/1/13.
//  Copyright © 2018年 Ran Wang. All rights reserved.
//

#ifndef tools_h
#define tools_h

#include <vector>
#include "opencv2/imgproc.hpp"

namespace face_detection {
    void CameraToImage(int nums, int gap, std::vector<cv::Mat>* images);
}

#endif /* tools_h */
