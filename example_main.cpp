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
#include "opencv2/highgui.hpp"

using namespace cv;
using namespace std;

int main() {
    face_detection::OpenCVExample opencv_example;
//    opencv_example.RunCamera();
//    opencv_example.RunImage("/Users/lillian/yzkj/code/workspace/FaceDetection/FaceDetection/test_data/lena.jpg", nullptr, true, true);
//    cv::waitKey(0);
//    face_detection::PicoExample pico_example;
//    pico_example.Run();
    vector<cv::Mat> images;
    face_detection::CameraToImage(200, 0.5, &images);
    for(int i = 0; i < images.size(); i++) {
        imwrite("/Users/lillian/yzkj/code/workspace/FaceDetection/FaceDetection/result/image_" + to_string(i) + ".jpg", images[i]);
    }
    return 0;
}
