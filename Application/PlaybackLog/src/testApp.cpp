
/*************************************************************************
 * File Name          : testApp.cpp
 * Author             : Show Kawabata(5ide6urns lab)
 * Version            : v1.00
 * Date               : 01/19/2017
 * Parts required     : ofxGui, ofxOsc, ofxXmlSettings, ofxCsv
 * Description        :
 *
 * License            : Released under the MIT license.
 *                      http://opensource.org/licenses/mit-license.php
 *
 * Copyright          : Copyright (C) 2017 5ide6urns lab All right reserved.
 *
 * History            : 01/19/2017 v1.00 Show Kawabata Create On.
 *************************************************************************/

#include "testApp.h"

/*! *******************************************************************
 *  @fn         onPlaybackPushed
 *  @brief      This function is called, 
 *              when the Playback Button is pushed.
 *
 *  @param[in]  value   :   Button Status.(ON: push, OFF: not push)
 *  @return     void
 *  @version    v1.00
 *  @date       01/19/2017 v1.00 Create On.
 **********************************************************************/
void testApp::onPlaybackPushed(bool &value){
    
    if(value){
        _isPlayback = true;
        ofFileDialogResult openFile_ = ofSystemLoadDialog(DEF_SYSTEM_DIALOG_MSG);
        std::string file_ = openFile_.getPath();
        
        if(!(file_.empty())){
            _csv.loadFile(file_);
        }
        else{
            _isPlayback = false;
            ofSystemAlertDialog(DEF_SYSTEM_DIALOG_MSG);
        }
    }
    else{
        _isPlayback = false;
    }
    
    return;
}

/*! *******************************************************************
 *  @fn         sendOsc
 *  @brief      This function is communicated some Log datas by OSC.
 *
 *  @param[in]  void
 *  @return     void
 *  @version    v1.00
 *  @date       01/19/2017 v1.00 Create On.
 **********************************************************************/
void testApp::sendOsc(){
    
    _m.setAddress(DEF_OSC_MSG_CH1);
    _m.addIntArg(_ch[0]);
    _b.addMessage(_m);
    _m.clear();
    
    _m.setAddress(DEF_OSC_MSG_CH2);
    _m.addIntArg(_ch[1]);
    _b.addMessage(_m);
    _m.clear();
    
    _m.setAddress(DEF_OSC_MSG_CH3);
    _m.addFloatArg(_ch[2]);
    _b.addMessage(_m);
    _m.clear();

    _m.setAddress(DEF_OSC_MSG_CH4);
    _m.addFloatArg(_ch[3]);
    _b.addMessage(_m);
    _m.clear();

    _m.setAddress(DEF_OSC_MSG_CH5);
    _m.addFloatArg(_ch[4]);
    _b.addMessage(_m);
    _m.clear();

    _m.setAddress(DEF_OSC_MSG_CH6);
    _m.addFloatArg(_ch[5]);
    _b.addMessage(_m);
    _m.clear();

    _m.setAddress(DEF_OSC_MSG_CH7);
    _m.addFloatArg(_ch[6]);
    _b.addMessage(_m);
    _m.clear();

    _m.setAddress(DEF_OSC_MSG_CH8);
    _m.addFloatArg(_ch[7]);
    _b.addMessage(_m);
    _m.clear();

    _sender.sendBundle(_b);
    _b.clear();

    return;
}

/*! *******************************************************************
 *  @fn         loadCsv
 *  @brief      This function is loaded a CSV file for playbacking.
 *
 *  @param[in]  void
 *  @return     void
 *  @version    v1.00
 *  @date       01/19/2017 v1.00 Create On.
 **********************************************************************/
void testApp::loadCsv(){
    
    if(_count > _csv.numRows) _count = 1;
    
    for(unsigned int i = 0; i < 8; ++i){
        _ch[i] = _csv.getInt(_count, i + 1);
    }
    
    sendOsc();
    _count++;
    
    return;
}

/*! *******************************************************************
 *  @fn         setup [Default function]
 *  @brief      This function is the Initilize process.
 *
 *  @param[in]  void
 *  @return     void
 *  @version    v1.00
 *  @date       01/19/2017 v1.00 Create On.
 **********************************************************************/
void testApp::setup(){
    
    ofBackground(ofColor::black);
    
    _count = 1;
    for(int i = 0; i < 8; ++i) _ch[i] = 0;
    
    _sender.setup(DEF_OSC_HOST, DEF_OSC_PORT);
    
    _gui.setup(DEF_GUI_TITLE);
    _gui.add(_playback.setup(DEF_GUI_BTN_PLAYBACK, false));
    _gui.add(_framerate.setup(DEF_GUI_BTN_FPS, DEF_GUI_FPS_INIT,
                              DEF_GUI_FPS_MIN, DEF_GUI_FPS_MAX));

    _playback.addListener(this, &testApp::onPlaybackPushed);

    return;
}

/*! *******************************************************************
 *  @fn         update [Default function]
 *  @brief      This function is the Data Update process.
 *
 *  @param[in]  void
 *  @return     void
 *  @version    v1.00
 *  @date       01/19/2017 v1.00 Create On. **********************************************************************/
void testApp::update(){
    
    ofSetFrameRate(_framerate);
    
    if(_isPlayback){
        loadCsv();
    }
    else{
        _count = 1;
        for(int i = 0; i < 8; ++i) _ch[i] = 0;
    }
    
    return;
}

/*! *******************************************************************
 *  @fn         draw [Default function]
 *  @brief      This function is the Draw process.
 *
 *  @param[in]  void
 *  @return     void
 *  @version    v1.00
 *  @date       01/19/2017 v1.00 Create On.
 **********************************************************************/
void testApp::draw(){

    stringstream reportStr_;
    
    _gui.draw();
    
    reportStr_ << " FPS:     " << ofGetFrameRate() << endl;
    reportStr_ << "          " << endl;
    reportStr_ << " EEG Ch1: " << _ch[0] << endl;
    reportStr_ << " EEG Ch2: " << _ch[1] << endl;
    reportStr_ << " EEG Ch3: " << _ch[2] << endl;
    reportStr_ << " EEG Ch4: " << _ch[3] << endl;
    reportStr_ << " EEG Ch5: " << _ch[4] << endl;
    reportStr_ << " EEG Ch6: " << _ch[5] << endl;
    reportStr_ << " EEG Ch7: " << _ch[6] << endl;
    reportStr_ << " EEG Ch8: " << _ch[7] << endl;
    
    ofDrawBitmapString(reportStr_.str(), 1, 150);
    
    return;
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
