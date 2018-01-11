//
//  running_example.hpp
//  FaceDetection
//
//  Created by Lillian on 2018/1/11.
//  Copyright © 2018年 Ran Wang. All rights reserved.
//

#ifndef running_example_hpp
#define running_example_hpp

#include <vector>
#include "opencv2/imgproc.hpp"

namespace face_detection {
class RunningExample {
public:
    int run();
    virtual bool face_detect(const cv::Mat& img, std::vector<int>* face) = 0;
    void draw(const cv::Mat& img, const std::vector<int>& face);
};
}

#endif /* running_example_hpp */
