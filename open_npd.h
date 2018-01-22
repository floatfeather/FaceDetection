//
//  open_npd.hpp
//  FaceDetection
//
//  Created by Lillian on 2018/1/22.
//  Copyright © 2018年 Ran Wang. All rights reserved.
//

#ifndef open_npd_h
#define open_npd_h

#include "face_detector.h"
#include "npddetect.h"

namespace face_detection {
    class OpenNPDDetector : public FaceDetector{
    public:
        OpenNPDDetector();
        virtual ~OpenNPDDetector();
        bool FaceDetect(const cv::Mat& img, std::vector<int>* face);
        std::string MethodName();
    private:
        npd::npddetect *npd;
    };
}

#endif /* open_npd_h */
