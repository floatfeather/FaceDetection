//
//  open_npd.hpp
//  FaceDetection
//
//  Created by Lillian on 2018/1/22.
//  Copyright © 2018年 Ran Wang. All rights reserved.
//

#ifndef open_npd_h
#define open_npd_h

#include "running_example.h"
#include "npddetect.h"

namespace face_detection {
    class OpenNPDExample : public RunningExample{
    public:
        OpenNPDExample();
        virtual ~OpenNPDExample();
        bool FaceDetect(const cv::Mat& img, std::vector<int>* face);
    private:
        npd::npddetect *npd;
    };
}

#endif /* open_npd_h */
