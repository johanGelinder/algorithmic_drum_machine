#include "ofApp.h"
#include <iostream>
#include <chrono>
#include <random>

//--------------------------------------------------------------
void ofApp::setup(){
    
    sampleRate = 44100;
    bufferSize = 512;
    ofBackground(0);
    
    // assign our values using gausian distribution
    g1 = (int)abs(gausianRandom(8, 3));
    g2 =(int)abs(gausianRandom(16, 6));
    g3 = (int)abs(gausianRandom(22, 4));
    
    kick.load(ofToDataPath("snr.wav"));
    snare.load(ofToDataPath("bd.wav"));
    
    // set the tempo and ticks per beat
    clock.setTempo(120);
    clock.setTicksPerBeat(4);
    
    // set the size of the vector equal to our buffersize
    lAudio.assign(bufferSize, 0.0);
    
    // setup the soundStream
    //soundStream.setup(this, 2, 0, sampleRate, bufferSize, 4);
    ofSoundStreamSetup(2, 0, this, sampleRate, bufferSize, 4);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // display the kick and snare speed
    ofDrawBitmapString("Kick Speed: " + ofToString(kickSpeed), 50, 100);
    ofDrawBitmapString("Snare Speed: " + ofToString(snareSpeed), 50, 120);
    
    //----------------------------------------------------------
    // draw the signal using ofVertex
    //----------------------------------------------------------
    ofNoFill();
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(50, 150, 0);
    
    ofSetLineWidth(1);
    ofDrawRectangle(0, 0, 900, 300);
    
    ofSetColor(45, 200, 255);
    ofSetLineWidth(3);
    
    ofBeginShape();
    for (unsigned int i = 0; i < lAudio.size(); i++){
        float x =  ofMap(i, 0, lAudio.size(), 0, 900, true);
        ofVertex(x, 150 -lAudio[i]*180.0f);
    }
    ofEndShape(false);
    
    ofPopMatrix();
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    
    
    for (int i = 0; i < bufferSize; i++) {
        
        clock.ticker();
        
        if (clock.tick) {
            
            // add random values to frequency
            if(!melody){
                freq = 50;
            }else{
                freq += ofRandom(10, 100);
            }
        
        // reset the frequency to loop the random pattern
        // also change the threshold for some nice changes
        if (freq > threshold){
            freq = 50;
            threshold = (int)ofRandom(200, 600);
        }
        
        // increase the counter for each tick
        counter++;
    }
    
    //------------------------------------------------------
    // by using our gausian random distribution function we
    // will always get a new random beat. Once the beat has
    // been trigged, then create a new random value
    //------------------------------------------------------
    if (clock.tick && counter% g1 == 0) {
        g1 = (int)abs(gausianRandom(16, 3));
        kickSpeed = ofRandom(0, 2);
        
        kick.trigger();
    }
    if (clock.tick && counter%g2 == 2) {
        g2 =(int)abs(gausianRandom(32, 6));
        kickSpeed = ofRandom(0, 4);
        kick.trigger();
        freq2 = ofRandom(20, 100);
    }
    
    if (clock.tick && counter%g3 == 4) {
        g3 = (int)abs(gausianRandom(44, 4));
        snareSpeed = ofRandom(0, 2);
        snare.trigger();
    }
    
    if (clock.tick && counter%16 == 7) {
        snareSpeed = ofRandom(0, 2);
        snare.trigger();
        melody = !melody;
    }
    
    // play the kick and snare togehter with the added soundwaves
    double s = kick.playOnce(kickSpeed) + snare.playOnce(snareSpeed) + myOsc.sinewave( freq * myOsc2.square(freq2)) * 0.3;
    
    // mix the signal ofxMaxiMix
    myMix.stereo(s, outputs, 0.5);
    
    output[i * nChannels] = outputs[0];
    output[i * nChannels +1] = outputs[1];
    
    // assign the left channel to lAudio to draw the signal
    lAudio[i] = outputs[0];
}
}

//--------------------------------------------------------------
float ofApp::gausianRandom(float mean, float dist){
    
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    
    std::normal_distribution<double> distribution (mean,dist);
    
    return distribution(generator);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
    
}
