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
        int milliStartTime;

        string srcImgPath;
        string srcImgFileName;



        ofImage img;

        ofPoint anchorPoint;

        vector<float> times;
        vector<ofPoint> positions;
        vector<float> rotations;
        vector<ofPoint> scales;
        vector<float> opacities;

        void startTimer(){
            milliStartTime = ofGetElapsedTimeMillis();
        }

        int findTimeArrayIndex() {
            int returnIndex = times.size()-1;
            float timeElapsedSec = (ofGetElapsedTimeMillis() - milliStartTime)/1000.0f;
            for (int i = 0; i<times.size();i++) {
                if (timeElapsedSec <= times[i]){
                    returnIndex = i;
                    return returnIndex;
                }
            }

            return returnIndex;
        }

        void draw(){
            int timeIndex = findTimeArrayIndex();

            ofPushMatrix();
                ofTranslate(positions[timeIndex]);
                ofScale(scales[timeIndex].x/100.0,scales[timeIndex].y/100.0,scales[timeIndex].z/100.0);

                ofRotate(rotations[timeIndex]);
                ofTranslate(anchorPoint*-1);


                ofSetColor(255,255,255,255.0*opacities[timeIndex]/100.0);
                img.draw(0,0);
            ofPopMatrix();
        }

        GibsonLayer(ofxXmlSettings* xmlParser, int which){
            xmlParser->pushTag("layer", which);

                srcImgPath = xmlParser->getAttribute("source","path","", 0);
                srcImgFileName = ofSplitString(srcImgPath,"/").back();

                cout << "found layer with source: " << srcImgFileName << endl;

                img.loadImage("data/images/" + srcImgFileName);

                // find transform group and push it

                int numGroups = xmlParser->getNumTags("group");
                for(int i = 0; i < numGroups; i++) {
                    if(xmlParser->getAttribute("group","name","", i) == "Transform") {
                        xmlParser->pushTag("group", i);

                        int numProperties = xmlParser->getNumTags("property");
                        for(int j = 0; j < numProperties; j++) {

                            // anchor point
                            if(xmlParser->getAttribute("property","type","", j) == "Anchor_Point") {

                                cout << "Found anchor point: " << endl;
                                xmlParser->pushTag("property",j);

                                    cout << xmlParser->getAttribute("key","value","", 0) << endl;
                                    vector<string> splitPoint = ofSplitString(xmlParser->getAttribute("key","value","", 0),",");
                                    anchorPoint.x = ofToFloat(splitPoint[0]);
                                    anchorPoint.y = ofToFloat(splitPoint[1]);
                                    anchorPoint.z = ofToFloat(splitPoint[2]);

                                xmlParser->popTag(); // property
                            } // if property is anchor point

                            // positions
                            if(xmlParser->getAttribute("property","type","", j) == "Position") {

                                //cout << "Found position: ";// << endl;
                                xmlParser->pushTag("property",j);

                                    int numKeys = xmlParser->getNumTags("key");
                                    for(int k = 0; k < numKeys; k++) {
                                        //cout << xmlParser->getAttribute("key","value","", k) << ",";
                                        vector<string> splitPoint = ofSplitString(xmlParser->getAttribute("key","value","", k),",");

                                        positions.push_back(ofPoint(ofToFloat(splitPoint[0]),ofToFloat(splitPoint[1]),ofToFloat(splitPoint[2])));
                                        times.push_back(xmlParser->getAttribute("key","time",0.0f, k));
                                    }
                                    //cout << endl;

                                xmlParser->popTag(); // property
                            }

                            // rotations
                            if(xmlParser->getAttribute("property","type","", j) == "Rotation") {

                                //cout << "Found rotation: ";// << endl;
                                xmlParser->pushTag("property",j);

                                    int numKeys = xmlParser->getNumTags("key");
                                    for(int k = 0; k < numKeys; k++) {
                                        //cout << xmlParser->getAttribute("key","value",0.0f, k) << ",";

                                        rotations.push_back(xmlParser->getAttribute("key","value",0.0f, 0));
                                    }
                                    //cout << endl;

                                xmlParser->popTag(); // property
                            }

                            // scales
                            if(xmlParser->getAttribute("property","type","", j) == "Scale") {

                                //cout << "Found scale: ";// << endl;
                                xmlParser->pushTag("property",j);

                                    int numKeys = xmlParser->getNumTags("key");
                                    for(int k = 0; k < numKeys; k++) {
                                        //cout << xmlParser->getAttribute("key","value","", k) << ",";

                                        vector<string> splitPoint = ofSplitString(xmlParser->getAttribute("key","value","", k),",");

                                        scales.push_back(ofPoint(ofToFloat(splitPoint[0]),ofToFloat(splitPoint[1]),ofToFloat(splitPoint[2])));
                                    }
                                    //cout << endl;


                                xmlParser->popTag(); // property
                            }

                            // opacities
                            if(xmlParser->getAttribute("property","type","", j) == "Opacity") {

                                //cout << "Found opacities: ";// << endl;
                                xmlParser->pushTag("property",j);

                                    int numKeys = xmlParser->getNumTags("key");
                                    for(int k = 0; k < numKeys; k++) {
                                        //cout << xmlParser->getAttribute("key","value",0.0f, k) << ",";

                                        opacities.push_back(xmlParser->getAttribute("key","value",0.0f,k));
                                    }
                                    //cout << endl;

                                xmlParser->popTag(); // property
                            }
                        }

                        xmlParser->popTag(); // group
                    } // if group is transform
                }

            xmlParser->popTag(); // layer
        }

        ~GibsonLayer(){
            times.clear();
            positions.clear();
            rotations.clear();
            scales.clear();
            opacities.clear();
        }
};

class ofxXmlGibson {
public:

    string gibsonXmlPath;
    int milliStartTime;

    ofxXmlSettings* xmlParser;

    vector<GibsonLayer*> layers;

    ofxXmlGibson(string xmlPath){

        gibsonXmlPath = xmlPath;

        cout << "loading gibsonXmlPath: " << gibsonXmlPath << endl;
        xmlParser = new ofxXmlSettings(gibsonXmlPath);
        //xmlParser->loadFile(gibsonXmlPath);


        //movie //composition //layers


        xmlParser->pushTag("movie", 0);

            xmlParser->pushTag("composition", 0);

                int numLayers = xmlParser->getNumTags("layer");
                for(int i = 0; i < numLayers; i++) {
                    GibsonLayer* tmpLayer = new GibsonLayer(xmlParser,i);
                    if (tmpLayer->img.isAllocated())
                        layers.push_back(tmpLayer);
                    else
                        delete tmpLayer;
                }

            xmlParser->popTag(); // composition

        xmlParser->popTag(); // movie

        startTimers();
    }


    ~ofxXmlGibson(){
    }

    void startTimers(){
        milliStartTime = ofGetElapsedTimeMillis();

        for (int i=0; i<layers.size(); i++){
            layers[i]->startTimer();
        }
    }

    void draw(){
        for (int i=0; i<layers.size(); i++){
            layers[i]->draw();
        }
    }

};

#endif

