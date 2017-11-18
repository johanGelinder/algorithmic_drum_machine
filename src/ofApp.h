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
   
    
    //void drawCircle(boo)
    void audioOut(float * output, int bufferSize, int nChannels);
    
    double outputs[2];
    float gausianRandom(float mean, float dist);
    
    vector<float> lAudio;
    
    unsigned bufferSize, sampleRate;
    maxiClock clock;
    ofxMaxiOsc myOsc,myOsc2, myOsc3;
    double freq, freq2;
    maxiSample kick, snare;
    maxiEnv env;
    int counter;
    int threshold = 800;

    ofxMaxiMix myMix;
    
    int g1, g2, g3;

    double kickSpeed, snareSpeed;
    ofSoundStream soundStream;
    
    bool melody;
};
