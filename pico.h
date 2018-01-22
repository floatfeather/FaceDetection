//
//  pico.h
//  FaceDetection
//
//  Created by Lillian on 2018/1/10.
//  Copyright © 2018年 Ran Wang. All rights reserved.
//

#ifndef pico_h
#define pico_h

#include "running_example.h"
#include "opencv2/highgui/highgui_c.h"

namespace face_detection {
    class PicoExample : public RunningExample {
    public:
        PicoExample();
        virtual ~PicoExample();
        bool FaceDetect(const cv::Mat& img, std::vector<int>* face);
    private:
        bool DetectSingleFrame(const IplImage& frame, std::vector<int>* face);
        int FindObjects(float rcsq[], int maxndetections, void* cascade,
                        void* pixels, int nrows, int ncols, int ldim,
                        float scalefactor, float stridefactor, float minsize, float maxsize);
        void* GetCascade();
        int RunCascade(void* cascade, float* o, int r, int c, int s, void* vppixels, int nrows, int ncols, int ldim);
        int ClusterDetections(float rcsq[], int n);
        int FindConnectedComponents(int a[], float rcsq[], int n);
        void CCDFS(int a[], int i, float rcsq[], int n);
        float GetOverlap(float r1, float c1, float s1, float r2, float c2, float s2);
        void* cascade;
    };
}

#endif /* pico_h */
