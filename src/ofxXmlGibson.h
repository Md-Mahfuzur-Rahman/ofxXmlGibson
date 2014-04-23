//    Copyright (c) 2014 Keith Simmons <http://ksimmulator.com>
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef _OFXXMLGIBSON
#define _OFXXMLGIBSON

#include "ofMain.h"

typedef struct {
    string fileName;
    ofPixels image;
} QueuedImage;

class ofxXmlGibson {
public:



    int counter;
    queue<QueuedImage> q;
    string prefix;
    string format;

    ofxImageSequenceRecorder(){
        counter=0;

    }

    void setPrefix(string pre){
        prefix = pre;
        counter = 0; // keith
    }

    void setFormat(string fmt){
        format = fmt;
    }

    void threadedFunction() {
        while(isThreadRunning()) {
            if(!q.empty()){
                QueuedImage i = q.front();
                if (i.image.getImageType() == OF_IMAGE_GRAYSCALE)
                    i.image.setImageType(OF_IMAGE_COLOR);
                ofSaveImage(i.image, i.fileName);
                q.pop();
            }
            sleep(1);
        }
    }

    void addFrame(ofImage &img){
        addFrame(img.getPixelsRef());
    }

    void addFrame(ofVideoGrabber &cam){
        addFrame(cam.getPixelsRef());
    }

    void addFrame(ofVideoPlayer &player){
        addFrame(player.getPixelsRef());
    }

    void addFrame(ofPixels imageToSave) {
        char fileName[100];
        sprintf(fileName,  "%s%.4i.%s" , prefix.c_str(), counter, format.c_str());
        counter++;

        QueuedImage qImage;

        qImage.fileName = fileName;
        qImage.image = imageToSave;

        q.push(qImage);
    }
};

#endif

