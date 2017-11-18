#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void audioOut(float * output, int bufferSize, int nChannels);
    
   // void play(double * output);
    double outputs[2];
    float gausianRandom(float mean, float dist);
    
    vector<float> lAudio;
    
    unsigned bufferSize, sampleRate;
    maxiClock clock;
    ofxMaxiOsc myOsc,myOsc2, myOsc3;
    double freq, freq2;
    maxiSample kick, snare, sample;
    maxiEnv env;
    int counter;
    
    ofxMaxiMix myMix;
    
    int g1, g2, g3;
    ofxPanel gui;
    ofParameter<float> feedback;
    ofParameter<float> speed;
    ofParameter<float> depth;
    ofParameter<int> delay;
    
    double kickSpeed, snareSpeed;
    ofxMaxiFilter lowpass;
    maxiFlanger flang;
    
};
