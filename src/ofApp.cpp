#include "ofApp.h"
#include <iostream>
#include <chrono>
#include <random>

//--------------------------------------------------------------
void ofApp::setup(){
    
    sampleRate = 44100;
    bufferSize = 512;
    ofBackground(0);
    
    kick.load(ofToDataPath("Bd.wav"));
    snare.load(ofToDataPath("snr.wav"));
    
    clock.setTempo(120);
    clock.setTicksPerBeat(4);
    
    // setup the soundStream
    ofSoundStreamSetup(2, 0, this, sampleRate, bufferSize, 4);
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
}
//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    
    for (int i = 0; i < bufferSize; i++) {
        
        clock.ticker();
        
        if (clock.tick) {
            
            scratch++;
            counter++;
        }
        
        if (clock.tick && counter%8==0) {
            kick.trigger();
        }
        if (clock.tick && counter%16==2) {
            kick.trigger();
        }
        
        
        if (clock.tick && counter%8==4) {
            
            sample.trigger();
            snare.trigger();
        }
        
        if (clock.tick && counter%16==7) {
            snare.trigger();
        }
        
        output[i * nChannels    ]  = kick.playOnce() + snare.playOnce();
        output[i * nChannels + 1]  = output[i * nChannels    ];
    }
}


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

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
