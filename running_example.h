//
//  running_example.hpp
//  FaceDetection
//
//  Created by Lillian on 2018/1/11.
//  Copyright © 2018年 Ran Wang. All rights reserved.
//

#ifndef running_example_h
#define running_example_h

#include <vector>
#include "opencv2/imgproc.hpp"

namespace face_detection {
class RunningExample {
public:
    int RunCamera(bool show = true, bool save = false);
    int RunImage(const std::string image_path, double* time = nullptr, bool show = true, bool save = false);
    int RunImages(const std::vector<std::string> image_paths, bool show = true, bool save = false);
    virtual bool FaceDetect(const cv::Mat& img, std::vector<int>* face) = 0;
    void Draw(const cv::Mat& img, const std::vector<int>& face, bool show, bool save, std::string save_path = "");
    void DrawArticulation(const cv::Mat& img);
    void ShowAndSave(const cv::Mat& img, bool show, bool save, std::string save_path);
};
}

#endif /* running_example_h */
