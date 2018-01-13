//
//  running_example.cpp
//  FaceDetection
//
//  Created by Lillian on 2018/1/11.
//  Copyright © 2018年 Ran Wang. All rights reserved.
//

#include "running_example.h"

#include "constants.h"
#include <vector>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

namespace face_detection{
    void RunningExample::DrawArticulation(const Mat& img) {
        Mat imageSobel;
        stringstream meanValueStream;
        Sobel(img, imageSobel, CV_16U, 1, 1);
        string meanValueString;
        meanValueStream << mean(imageSobel)[0] * mean(imageSobel)[0];
        meanValueStream >> meanValueString;
        meanValueString = "Articulation(Variance Method): " + meanValueString;
        putText(img, meanValueString, Point(20, 50), CV_FONT_HERSHEY_COMPLEX, 0.5, Scalar(255, 255, 25));
    }
    
    void RunningExample::ShowAndSave(const Mat& img, bool show, bool save, string save_path) {
        DrawArticulation(img);
        if (show) {
            imshow("result", img);
        }
        if (save) {
            if (save_path.empty()) {
                cerr << "No path specified to save the image." << endl;
                return;
            }
            imwrite(save_path, img);
        }
    }
    
    void RunningExample::Draw(const Mat &img, const vector<int> &face, bool show, bool save, string save_path) {
        if (face.size() != 4) {
            ShowAndSave(img, show, save, save_path);
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
        ShowAndSave(img, show, save, save_path);
    }

    int RunningExample::RunCamera(bool show, bool save) {
        VideoCapture capture;
        Mat frame;
        capture.open(0);
        double total_tick_count = 0;
        int frame_count = 0;
        if(capture.isOpened())
        {
            cout << "Video capturing has been started ..." << endl;
            capture.set(CV_CAP_PROP_FRAME_WIDTH, CAMERA_WIDTH);
            capture.set(CV_CAP_PROP_FRAME_HEIGHT, CAMERA_HEIGHT);
            for(;;)
            {
                capture >> frame;
                if( frame.empty() )
                    break;
                
                frame_count++;
                Mat frame1 = frame.clone();
                vector<int> face;
                
                double t = (double)getTickCount();
                if (!FaceDetect(frame1, &face)) {
                    cerr << "Error encountered in face detection" << endl;
                    return 1;
                }
                t = (double)getTickCount() - t;
                total_tick_count += t*1000/getTickFrequency();
                cout << "detection time = " << t*1000/getTickFrequency() << " ms\n";
                
                Draw(frame1, face, show, save);
                
                char c = (char)waitKey(10);
                if( c == 27 || c == 'q' || c == 'Q' )
                    break;
            }
            cout << "average detection time = " << total_tick_count / frame_count << " ms\n";
        } else {
            cout << "fail to open camera" << endl;
            return 1;
        }
        return 0;
    }

    int RunningExample::RunImage(const string image_path, double* time, bool show, bool save) {
        double t = (double)getTickCount();
        Mat image = imread(image_path, 1);
        vector<int> face;
        if (!FaceDetect(image, &face)) {
            cerr << "Error encountered in face detection: " << image_path << endl;
            return 1;
        }
        t = (double)getTickCount() - t;
        double duration = t*1000/getTickFrequency();
        cout << "detection time = " << duration << " ms\n";
        if (time != nullptr) {
            *time = duration;
        }
        Draw(image, face, show ,save, image_path + "_result.jpg");
        return 0;
    }
    
    int RunningExample::RunImages(const vector<string> image_paths, bool show, bool save) {
        int return_status = 0;
        for(auto image_path : image_paths) {
            double time;
            return_status = return_status | RunImage(image_path, &time, show, save);
        }
        return return_status;
    }
}
