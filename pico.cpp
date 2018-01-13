//
//  pico.cpp
//  FaceDetection
//
//  Created by Lillian on 2018/1/10.
//  Copyright © 2018年 Ran Wang. All rights reserved.
//
/*
 *  This code is released under the MIT License.
 *  Copyright (c) 2013 Nenad Markus
 */
#include "pico.h"
#include "constants.h"
#include "opencv2/highgui/highgui_c.h"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

namespace face_detection {
    bool PicoExample::FaceDetect(const Mat& img, vector<int> *face) {
        IplImage frame = img;
        IplImage* framecopy = cvCreateImage(cvSize(frame.width, frame.height), frame.depth, frame.nChannels);
        cvCopy(&frame, framecopy, 0);
        if (!DetectSingleFrame(*framecopy, face)) {
            cvFlip(framecopy, framecopy, 1);
            if (!DetectSingleFrame(*framecopy, face)) {
                return true;
            }
        }
        return true;
    }
    
    void* PicoExample::GetCascade() {
        int size;
        FILE* file = fopen(PICO_MODEL_PATH.c_str(), "rb");
        
        if(!file) {
            cerr << "Cannot read cascade from" << PICO_MODEL_PATH << endl;
            return nullptr;
        }
        
        fseek(file, 0L, SEEK_END);
        size = ftell(file);
        fseek(file, 0L, SEEK_SET);
        
        void* cascade = malloc(size);
        
        if(!cascade || size!=fread(cascade, 1, size, file)) {
            return nullptr;
        }
        
        fclose(file);
        return cascade;
    }
    
    bool PicoExample::DetectSingleFrame(const IplImage& frame, std::vector<int>* face) {
        uint8_t* pixels;
        int nrows, ncols, ldim;
        
    #define MAXNDETECTIONS 2048
        int ndetections;
        float rcsq[4*MAXNDETECTIONS];
        
        static IplImage* gray = 0;
        gray = cvCreateImage(cvSize(frame.width, frame.height), frame.depth, 1);
        
        // get grayscale image
        if(frame.nChannels == 3) {
            cvCvtColor(&frame, gray, CV_RGB2GRAY);
        }
        else {
            cvCopy(&frame, gray, 0);
        }
        
        pixels = (uint8_t*)gray->imageData;
        nrows = gray->height;
        ncols = gray->width;
        ldim = gray->widthStep;
        void* cascade = GetCascade();
        ndetections = FindObjects(rcsq, MAXNDETECTIONS, cascade, pixels, nrows, ncols, ldim, 1.1, 0.1, MIN_SIZE, MIN(nrows, ncols));

        ndetections = ClusterDetections(rcsq, ndetections);
        
        free(cascade);
        
        int x,y,width,height;
        double max_area = 0;
        for(int i=0; i<ndetections; ++i) {
            if(rcsq[4*i+3] >= 5.0f) {// check the confidence threshold
                double area = rcsq[4*i+2] * rcsq[4*i+2];
                if (area > max_area) {
                    x = rcsq[4*i+1] - rcsq[4*i+2]/2;
                    y = rcsq[4*i+0] - rcsq[4*i+2]/2;
                    width = rcsq[4*i+2];
                    height = rcsq[4*i+2];
                    max_area = area;
                }
            }
        }
        if (max_area > 0) {
            face->push_back(x);
            face->push_back(y);
            face->push_back(width);
            face->push_back(height);
            return true;
        } else {
            return false;
        }
    }

    int PicoExample::FindObjects(float rcsq[], int maxndetections,void* cascade,
                                 void* pixels, int nrows, int ncols, int ldim,
                                 float scalefactor, float stridefactor, float minsize, float maxsize) {
        float s;
        int ndetections;
        
        ndetections = 0;
        s = minsize;
        
        while(s<=maxsize)
        {
            float r, c, dr, dc;
            
            //
            dr = dc = MAX(stridefactor*s, 1.0f);
            
            //
            for(r=s/2+1; r<=nrows-s/2-1; r+=dr)
                for(c=s/2+1; c<=ncols-s/2-1; c+=dc)
                {
                    float q;
                    int t;
                    
                    t = RunCascade(cascade, &q, r, c, s, pixels, nrows, ncols, ldim);
                    
                    if(1==t)
                    {
                        if(ndetections < maxndetections)
                        {
                            rcsq[4*ndetections+0] = r;
                            rcsq[4*ndetections+1] = c;
                            rcsq[4*ndetections+2] = s;
                            rcsq[4*ndetections+3] = q;
                            
                            ++ndetections;
                        }
                    }
                }
            s = scalefactor*s;
        }
        
        return ndetections;
    }
    
    int PicoExample::RunCascade(void* cascade, float* o, int r, int c, int s, void* vppixels, int nrows, int ncols, int ldim) {
        int i, j, idx;
        
        uint8_t* pixels;
        
        int tdepth, ntrees, offset;
        
        int8_t* ptree;
        int8_t* tcodes;
        float* lut;
        float thr = 0.0;
        
        pixels = (uint8_t*)vppixels;
        
        tdepth = ((int*)cascade)[2];
        ntrees = ((int*)cascade)[3];
        
        r = r*256;
        c = c*256;
        
        if( (r+128*s)/256>=nrows || (r-128*s)/256<0 || (c+128*s)/256>=ncols || (c-128*s)/256<0 )
            return -1;
        
        offset = ((1<<tdepth)-1)*sizeof(int32_t) + (1<<tdepth)*sizeof(float) + 1*sizeof(float);
        ptree = (int8_t*)cascade + 2*sizeof(float) + 2*sizeof(int);
        
        *o = 0.0f;
        
        for(i=0; i<ntrees; ++i)
        {
            tcodes = ptree - 4;
            lut = (float*)(ptree + ((1<<tdepth)-1)*sizeof(int32_t));
            thr = *(float*)(ptree + ((1<<tdepth)-1)*sizeof(int32_t) + (1<<tdepth)*sizeof(float));
            
            idx = 1;
            
            for(j=0; j<tdepth; ++j)
                idx = 2*idx + (pixels[(r+tcodes[4*idx+0]*s)/256*ldim+(c+tcodes[4*idx+1]*s)/256]<=pixels[(r+tcodes[4*idx+2]*s)/256*ldim+(c+tcodes[4*idx+3]*s)/256]);
            
            *o = *o + lut[idx-(1<<tdepth)];
            
            if(*o<=thr)
                return -1;
            else
                ptree = ptree + offset;
        }
        
        *o = *o - thr;
        
        return +1;
    }
    
    float PicoExample::GetOverlap(float r1, float c1, float s1, float r2, float c2, float s2) {
        float overr, overc;
        
        overr = MAX(0, MIN(r1+s1/2, r2+s2/2) - MAX(r1-s1/2, r2-s2/2));
        overc = MAX(0, MIN(c1+s1/2, c2+s2/2) - MAX(c1-s1/2, c2-s2/2));
        
        return overr*overc/(s1*s1+s2*s2-overr*overc);
    }
    
    void PicoExample::CCDFS(int a[], int i, float rcsq[], int n) {
        int j;
        
        //
        for(j=0; j<n; ++j)
            if(a[j]==0 && GetOverlap(rcsq[4*i+0], rcsq[4*i+1], rcsq[4*i+2], rcsq[4*j+0], rcsq[4*j+1], rcsq[4*j+2])>0.3f)
            {
                //
                a[j] = a[i];
                
                //
                CCDFS(a, j, rcsq, n);
            }
    }
    
    int PicoExample::FindConnectedComponents(int a[], float rcsq[], int n) {
        int i, cc;
        
        if(!n)
            return 0;
        
        for(i=0; i<n; ++i)
            a[i] = 0;
        
        cc = 1;
        
        for(i=0; i<n; ++i) {
            if(a[i] == 0) {
                a[i] = cc;
                
                CCDFS(a, i, rcsq, n);
                
                ++cc;
            }
        }
        
        //
        return cc - 1; // number of connected components
    }
    
    int PicoExample::ClusterDetections(float rcsq[], int n) {
        int idx, ncc, cc;
        int a[4096];
        
        //
        ncc = FindConnectedComponents(a, rcsq, n);
        
        if(!ncc)
            return 0;
        
        //
        idx = 0;
        
        for(cc=1; cc<=ncc; ++cc)
        {
            int i, k;
            
            float sumqs=0.0f, sumrs=0.0f, sumcs=0.0f, sumss=0.0f;
            
            //
            k = 0;
            
            for(i=0; i<n; ++i)
                if(a[i] == cc)
                {
                    sumrs += rcsq[4*i+0];
                    sumcs += rcsq[4*i+1];
                    sumss += rcsq[4*i+2];
                    sumqs += rcsq[4*i+3];
                    
                    ++k;
                }
            
            //
            rcsq[4*idx+0] = sumrs/k;
            rcsq[4*idx+1] = sumcs/k;
            rcsq[4*idx+2] = sumss/k;;
            rcsq[4*idx+3] = sumqs; // accumulated confidence measure
            
            //
            ++idx;
        }
        
        //
        return idx;
    }
}
