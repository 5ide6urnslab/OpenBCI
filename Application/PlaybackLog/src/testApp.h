
/*************************************************************************
 * File Name          : testApp.h
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

#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxCsv.h"
#include "ofxGui.h"

using namespace wng;

#define DEF_OSC_HOST            "127.0.0.1"
#define DEF_OSC_PORT            (7777)

#define DEF_SYSTEM_DIALOG_MSG   "Please select a CSV file"

#define DEF_OSC_MSG_CH1         "/brain/ch/1"
#define DEF_OSC_MSG_CH2         "/brain/ch/2"
#define DEF_OSC_MSG_CH3         "/brain/ch/3"
#define DEF_OSC_MSG_CH4         "/brain/ch/4"
#define DEF_OSC_MSG_CH5         "/brain/ch/5"
#define DEF_OSC_MSG_CH6         "/brain/ch/6"
#define DEF_OSC_MSG_CH7         "/brain/ch/7"
#define DEF_OSC_MSG_CH8         "/brain/ch/8"

#define DEF_GUI_TITLE           "PLAYBACK LOG"
#define DEF_GUI_BTN_PLAYBACK    "PlayBack"
#define DEF_GUI_BTN_FPS         "FPS"
#define DEF_GUI_FPS_INIT        (30)
#define DEF_GUI_FPS_MIN         (1)
#define DEF_GUI_FPS_MAX         (60)

#define DEF_SENSOR_EEG_CH_TOTAL (8)

class testApp : public ofBaseApp{

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
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    void sendOsc();
    void loadCsv();
    
    void onPlaybackPushed(bool &value);

    
    ofxCsv          _csv;
    int             _ch[DEF_SENSOR_EEG_CH_TOTAL];
    int
    unsigned short  _count;
    
    ofxOscSender    _sender;
    ofxOscMessage   _m;
    ofxOscBundle    _b;

    ofxPanel        _gui;
    ofxToggle       _playback;
    ofxIntSlider    _framerate;
    bool            _isPlayback;
    
    string _oscMsgTable[DEF_SENSOR_EEG_CH_TOTAL] = {
        DEF_OSC_MSG_CH1, DEF_OSC_MSG_CH2, DEF_OSC_MSG_CH3, DEF_OSC_MSG_CH4,
        DEF_OSC_MSG_CH5, DEF_OSC_MSG_CH6, DEF_OSC_MSG_CH7, DEF_OSC_MSG_CH8
    };



};
