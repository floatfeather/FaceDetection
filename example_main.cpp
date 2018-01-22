//
//  example_main.cpp
//  FaceDetection
//
//  Created by Lillian on 2018/1/11.
//  Copyright © 2018年 Ran Wang. All rights reserved.
//

#include "opencv_vj.h"
#include "pico.h"
#include "tools.h"
#include "open_npd.h"
#include "opencv2/highgui.hpp"

using namespace cv;
using namespace std;

void RunOpenCV() {
    face_detection::OpenCVDetector opencv_example;
    opencv_example.RunCamera();
    //opencv_example.RunImage("/Users/lillian/yzkj/code/workspace/FaceDetection/FaceDetection/test_data/lena.jpg", nullptr, true, true);
    //cv::waitKey(0);
//    std::vector<std::string> image_paths;
//    for (int i = 0; i < 200; i++) {
//        char buf[10];
//        std::sprintf(buf, "%d", i);
//        image_paths.push_back("/Users/lillian/yzkj/code/workspace/FaceDetection/FaceDetection/result/image_" + std::string(buf) + ".jpg");
//    }
//    opencv_example.RunImages(image_paths, false, true);
}

void RunPico() {
    face_detection::PicoDetector pico_example;
    pico_example.RunCamera();
//    std::vector<std::string> image_paths;
//    for (int i = 0; i < 200; i++) {
//        char buf[10];
//        std::sprintf(buf, "%d", i);
//        image_paths.push_back("/Users/lillian/yzkj/code/workspace/FaceDetection/FaceDetection/result/image_" + std::string(buf) + ".jpg");
//    }
//    pico_example.RunImages(image_paths, false, true);
}

void RunOpenNPD() {
    face_detection::OpenNPDDetector open_npd_example;
    open_npd_example.RunCamera();
//    std::vector<std::string> image_paths;
//    for (int i = 0; i < 200; i++) {
//        char buf[10];
//        std::sprintf(buf, "%d", i);
//        image_paths.push_back("/Users/lillian/yzkj/code/workspace/FaceDetection/FaceDetection/result/image_" + std::string(buf) + ".jpg");
//    }
//    open_npd_example.RunImages(image_paths, false, true);
}

void GenerateImages() {
    vector<cv::Mat> images;
    face_detection::CameraToImage(202, 0.5, &images);
    for(int i = 2; i < images.size(); i++) {
        imwrite("/Users/lillian/yzkj/code/workspace/FaceDetection/FaceDetection/result/image_" + to_string(i - 2) + ".jpg", images[i]);
    }
}

int main() {
//    RunOpenCV();
    RunPico();
//    RunOpenNPD();
//    GenerateImages();
    return 0;
}
