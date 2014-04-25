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
#include "ofxXmlSettings.h"

class GibsonLayer {
public:
    GibsonLayer(ofxXmlSettings* xmlParser, int which, string imageSearchDir="data/images/");
    ~GibsonLayer();

    void startTimer();
    int findTimeArrayIndex(); // finds correct key values based on time elapsed
    void draw();

    ofPoint anchorPoint;

    vector<float> times;
    vector<ofPoint> positions;
    vector<float> rotations;
    vector<ofPoint> scales;
    vector<float> opacities;

    int milliStartTime;

    string srcImgPath;
    string srcImgFileName;

    ofImage* img;
};

class ofxXmlGibson {
public:
    ofxXmlGibson(string xmlPath, string searchDir="data/images/");
    ~ofxXmlGibson();

    void startTimers();
    void draw();
    GibsonLayer* getLayerByFileName(string filename);

    string gibsonXmlPath;

    int milliStartTime;
    string imageSearchDir;

    ofxXmlSettings* xmlParser;

    vector<GibsonLayer*> layers;
};

#endif

