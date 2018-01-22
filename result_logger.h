//
//  result_logger.hpp
//  FaceDetection
//
//  Created by Lillian on 2018/1/22.
//  Copyright © 2018年 Ran Wang. All rights reserved.
//

#ifndef result_logger_h
#define result_logger_h

#include <vector>
#include <string>

namespace face_detection{
    class ResultLogger {
    public:
        void Init(const std::string& log_dir, const std::string& method);
        void Write();
        void AddDetectionTime(double time);
        void AddDetectionResult(bool detected);
        void AddArticulation(double art);
        void ComputeStatistics(std::vector<double>* info, int* min_time, int* max_time, int* avg_time, int* mid_time, int* var_time);
    private:
        std::vector<double> times;
        std::vector<bool> results;
        std::vector<double> articulations;
        std::string log_dir;
        bool init = false;
    };
}

#endif /* result_logger_h */
