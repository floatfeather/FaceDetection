//
//  open_npd.cpp
//  FaceDetection
//
//  Created by Lillian on 2018/1/22.
//  Copyright © 2018年 Ran Wang. All rights reserved.
//

#include "open_npd.h"
#include "constants.h"

namespace face_detection {
    
    OpenNPDExample::OpenNPDExample() {
        npd = new npd::npddetect(MIN_SIZE, MAX_SIZE);
        npd->load(OPEN_NPD_MODEL_PATH.c_str());
    }
    
    OpenNPDExample::~OpenNPDExample() {
        free(npd);
    }
    
    bool OpenNPDExample::FaceDetect(const cv::Mat& img, std::vector<int>* face) {
        int n = npd->detect(img.data, img.cols, img.rows);
        vector<int>& Xs = npd->getXs();
        vector<int>& Ys = npd->getYs();
        vector<int>& Ss = npd->getSs();
        double max_area = 0;
        int x, y, width, height;
        for(int i = 0; i < n; i++)
        {
            if (Ss[i] * Ss[i] > max_area) {
                max_area = Ss[i] * Ss[i];
                x = Xs[i];
                y = Ys[i];
                width = Ss[i];
                height = Ss[i];
            }
        }
        if (max_area > 0) {
            face->push_back(x);
            face->push_back(y);
            face->push_back(width);
            face->push_back(height);
        }
        return true;
    }
}
