#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
    ofSetFrameRate(60);
    ofEnableAlphaBlending();

    ofSetWindowShape(1440,900);
    ofSetFullscreen(true);


    // image filenames referenced in xml will be searched for in the image search directory
    // "data/images/" is the default image search directory if second argument is omitted

    // load gibson xml animations including images mentioned in xml
    gibsonAnimation1 = new ofxXmlGibson("data/badges.xml", "data/images/");
    gibsonAnimation2 = new ofxXmlGibson("data/wristband-intro.xml", "data/images/");
    gibsonAnimation3 = new ofxXmlGibson("data/wristband-jiggle.xml", "data/images/");
}

//--------------------------------------------------------------
void testApp::update() {

}

//--------------------------------------------------------------
void testApp::draw() {
    // fancy background
    ofBackgroundGradient(ofColor::black, ofColor::purple, OF_GRADIENT_LINEAR);

    // draw our animations
    gibsonAnimation1->draw();
    gibsonAnimation2->draw();
    gibsonAnimation3->draw();

    // draw on-screen instructions
    ofPushStyle();
    ofSetColor(ofColor::white);
    ofRect(0,0,260,45);

    ofSetColor(ofColor::black);
    ofDrawBitmapString("'1-3' to restart animations.\n'f' to toggle fullscreen.",20,20);
    ofPopStyle();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {
    if (key == '1')
        gibsonAnimation1->startTimers();

    if (key == '2')
        gibsonAnimation2->startTimers();

    if (key == '3')
        gibsonAnimation3->startTimers();

    if (key == 'f')
        ofToggleFullscreen();
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo) {

}
