//
//  face_detector.h
//  FaceDetection
//
//  Created by Lillian on 2018/1/11.
//  Copyright © 2018年 Ran Wang. All rights reserved.
//

#ifndef face_detector_h
#define face_detector_h

#include <vector>
#include "opencv2/imgproc.hpp"
#include "result_logger.h"

namespace face_detection {
//  Framework of face detection, including camera routines, image IO and the display of result.
class FaceDetector {
public:
    // Opens the camera and detects the face in camera video. This function is only tested on MAC.
    int RunCamera(bool show = true, bool save = false);
    // Detects the face in image, which is located in 'image_path'. The detection time is saved in '*time'
    // if 'time' is not null.
    int RunImage(const std::string image_path, double* time = nullptr, bool show = true, bool save = false);
    // Pipeline version of 'RunImage'.
    int RunImages(const std::vector<std::string> image_paths, bool show = true, bool save = false);
    // Core function of face detection. Each face detection algorithm should implement this function.
    // The image is provided in 'img', and the result is saved in '*face'. '*face' should have four
    // elements if a face is detected. The four elements indicate the x-axis, y-axis, width and height
    // of the face.
    virtual bool FaceDetect(const cv::Mat& img, std::vector<int>* face) = 0;
    // Name of the algorithm.
    virtual std::string MethodName() = 0;
    // Begins to log the detection time, articulation and detected result.
    void StartLog();
    // Ends the logging and writes the log to file.
    void EndLog();
private:
    // Draws the face on the image.
    void Draw(const cv::Mat& img, const std::vector<int>& face, bool show, bool save, std::string save_path = "");
    // Draws articulation on the image.
    void DrawArticulation(const cv::Mat& img);
    void ShowAndSave(const cv::Mat& img, bool show, bool save, std::string save_path);
    ResultLogger logger;
};
}

#endif /* face_detector_h */
