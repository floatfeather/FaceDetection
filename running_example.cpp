//
//  running_example.cpp
//  FaceDetection
//
//  Created by Lillian on 2018/1/11.
//  Copyright © 2018年 Ran Wang. All rights reserved.
//

#include "running_example.h"

#include <vector>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

namespace face_detection{
void RunningExample::draw(const Mat &img, const vector<int> &face) {
    if (face.size() != 4) {
        imshow( "result", img );
        return;
    }
    Rect face_rect(face[0], face[1], face[2], face[3]);
    Scalar color = Scalar(255,0,0);
    
    double aspect_ratio = (double)face_rect.width / face_rect.height;
    if( 0.75 < aspect_ratio && aspect_ratio < 1.3 )
    {
        Point center;
        center.x = cvRound((face_rect.x + face_rect.width*0.5));
        center.y = cvRound((face_rect.y + face_rect.height*0.5));
        int radius = cvRound((face_rect.width + face_rect.height)*0.25);
        circle(img, center, radius, color, 3, 8, 0);
    }
    else {
        rectangle(img, cvPoint(cvRound(face_rect.x), cvRound(face_rect.y)),
                  cvPoint(cvRound((face_rect.x + face_rect.width-1)), cvRound((face_rect.y + face_rect.height-1))), color, 3, 8, 0);
    }
    imshow( "result", img );
}

int RunningExample::run() {
    VideoCapture capture;
    Mat frame;
    capture.open(0);
    if(capture.isOpened())
    {
        cout << "Video capturing has been started ..." << endl;
        capture.set(CV_CAP_PROP_FRAME_WIDTH, 200);
        capture.set(CV_CAP_PROP_FRAME_HEIGHT, 200);
        for(;;)
        {
            capture >> frame;
            if( frame.empty() )
                break;
            
            Mat frame1 = frame.clone();
            vector<int> face;
            if (!face_detect(frame1, &face)) {
                cerr << "Error encountered in face detection" << endl;
                return 1;
            }
            
            draw(frame1, face);
            
            char c = (char)waitKey(10);
            if( c == 27 || c == 'q' || c == 'Q' )
                break;
        }
    } else {
        Mat image = imread("../FaceDetection/test_data/lena.jpg", 1);
        vector<int> face;
        if (!face_detect(image, &face)) {
            cerr << "Error encountered in face detection" << endl;
            return 1;
        }
        draw(image, face);
        waitKey(0);
    }
    
    return 0;
}
}
