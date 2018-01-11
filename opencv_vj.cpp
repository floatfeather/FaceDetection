//
//  opencv_vj.cpp
//  FaceDetection
//
//  Created by Lillian on 2018/1/10.
//  Copyright © 2018年 Ran Wang. All rights reserved.
//

#include "opencv_vj.h"
#include "constants.h"
#include "opencv2/objdetect.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

namespace face_detection {
bool OpenCVExample::face_detect(const Mat& img, vector<int>* face) {
    CascadeClassifier cascade;
    if(!cascade.load(OPENCV_VJ_MODEL_PATH))
    {
        cerr << "ERROR: Could not load classifier cascade" << endl;
        return false;
    }
    vector<Rect> faces;
    Mat gray, smallImg;
    
    cvtColor(img, gray, COLOR_BGR2GRAY);
    equalizeHist(gray, smallImg);
    
    double t = (double)getTickCount();
    cascade.detectMultiScale(smallImg, faces,
                             1.1, 2, 0
                             |CASCADE_FIND_BIGGEST_OBJECT
                             |CASCADE_SCALE_IMAGE,
                             Size(MIN_SIZE, MIN_SIZE));
    if(faces.empty())
    {
        flip(smallImg, smallImg, 1);
        vector<Rect> flip_faces;
        cascade.detectMultiScale(smallImg, flip_faces,
                                 1.1, 2, 0
                                 |CASCADE_FIND_BIGGEST_OBJECT
                                 |CASCADE_SCALE_IMAGE,
                                 Size(MIN_SIZE, MIN_SIZE));
        if (!flip_faces.empty()) {
            Rect r = flip_faces[0];
            faces.push_back(Rect(smallImg.cols - r.x - r.width, r.y, r.width, r.height));
        }
    }
    
    t = (double)getTickCount() - t;
    cout << "detection time = " << t*1000/getTickFrequency() << " ms\n";
    if (!faces.empty()) {
        face->push_back(faces[0].x);
        face->push_back(faces[0].y);
        face->push_back(faces[0].width);
        face->push_back(faces[0].height);
    }
    return true;
}
}