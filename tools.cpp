//
//  tools.cpp
//  FaceDetection
//
//  Created by Lillian on 2018/1/13.
//  Copyright © 2018年 Ran Wang. All rights reserved.
//

#include "tools.h"
#include "constants.h"
#include <vector>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <unistd.h>
#include <iostream>

using namespace std;
using namespace cv;

namespace face_detection {
    void CameraToImage(int nums, int gap, vector<Mat>* images) {
        VideoCapture capture;
        capture.open(0);
        if(capture.isOpened()) {
            capture.set(CV_CAP_PROP_FRAME_WIDTH, CAMERA_WIDTH);
            capture.set(CV_CAP_PROP_FRAME_HEIGHT, CAMERA_HEIGHT);
            for(int i = 0; i < nums; i++) {
                Mat frame;
                cout << "Capture frame " << i << endl;
                capture >> frame;
                if(frame.empty())
                    continue;
                images->push_back(frame);
                sleep(gap);
            }
        }
    }
}
