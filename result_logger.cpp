//
//  result_logger.cpp
//  FaceDetection
//
//  Created by Lillian on 2018/1/22.
//  Copyright © 2018年 Ran Wang. All rights reserved.
//

#include "result_logger.h"
#include <fstream>
#include <iostream>

using namespace std;

namespace face_detection {    
    void ResultLogger::Init(const string& log_dir, const string& method) {
        if (log_dir[log_dir.size() - 1] == '/') {
            this->log_dir = log_dir;
        } else {
            this->log_dir = log_dir + "/";
        }
        this->log_dir = this->log_dir + method + "_";
        articulations.clear();
        times.clear();
        results.clear();
        init = true;
    }
    
    void ResultLogger::AddArticulation(double art) {
        if (init) {
            articulations.push_back(art);
        }
    }
    
    void ResultLogger::AddDetectionTime(double time) {
        if (init) {
            times.push_back(time);
        }
    }
    
    void ResultLogger::AddDetectionResult(bool detected) {
        if (init) {
            results.push_back(detected);
        }
    }
    
    void ResultLogger::ComputeStatistics(vector<double>* info, int* min_time, int* max_time, int* avg_time, int* mid_time, int* var_time) {
        sort(info->begin(), info->end());
        *min_time = (*info)[0];
        *max_time = (*info)[info->size() - 1];
        *mid_time = (*info)[info->size() / 2];
        *avg_time = 0;
        for(int i = 0; i < info->size(); i++) {
            *avg_time += (*info)[i];
        }
        *avg_time = *avg_time / info->size();
        for(int i = 0; i < info->size(); i++) {
            *var_time = ((*info)[i] - *avg_time) * ((*info)[i] - *avg_time);
        }
        *var_time = *var_time / info->size();
    }
    
    void ResultLogger::Write() {
        if (!init) {
            cerr << "ResultLogger not initialized!" << endl;
            return;
        }
        const string original_info_path = log_dir + "original.log";
        const string statistics_path = log_dir + "statistics.log";
        ofstream ori_out(original_info_path), stat_out(statistics_path);
        ori_out << "DetectionTime,Articulation,FaceDetected" << endl;
        int min_time, max_time, avg_time, mid_time, var_time;
        int min_art, max_art, avg_art, mid_art, var_art;
        int face_num = 0;
        for(int i = 0; i < times.size(); i++) {
            ori_out << times[i] << "," << articulations[i] << "," << results[i] << endl;
            if (results[i]) {
                face_num++;
            }
        }
        ori_out.close();
        ComputeStatistics(&times, &min_time, &max_time, &avg_time, &mid_time, &var_time);
        ComputeStatistics(&articulations, &min_art, &max_art, &avg_art, &mid_art, &var_art);
        stat_out << "Detection Time:" << endl;
        stat_out << "Min: " << min_time << endl;
        stat_out << "Max: " << max_time << endl;
        stat_out << "Avg: " << avg_time << endl;
        stat_out << "Mid: " << mid_time << endl;
        stat_out << "Var: " << var_time << endl;
        stat_out << "Articulation:" << endl;
        stat_out << "Min: " << min_art << endl;
        stat_out << "Max: " << max_art << endl;
        stat_out << "Avg: " << avg_art << endl;
        stat_out << "Mid: " << mid_art << endl;
        stat_out << "Var: " << var_art << endl;
        stat_out << "Total Frames: " << times.size() << endl;
        stat_out << "Face Frames: " << face_num << endl;
        stat_out.close();
    }
}
