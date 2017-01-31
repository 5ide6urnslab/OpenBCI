
/*************************************************************************
 * File Name          : testApp.h
 * Author             : Show Kawabata(5ide6urns lab)
 * Version            : v1.00
 * Date               : 01/10/2017
 * Parts required     : ofxGui
 * Description        :
 *
 * License            : Released under the MIT license.
 *                      http://opensource.org/licenses/mit-license.php
 *
 * Copyright          : Copyright (C) 2017 5ide6urns lab All right reserved.
 *
 * History            : 01/10/2017 v1.00 Show Kawabata Create On.
 *************************************************************************/

#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#define DEF_GUI_TITLE                "CONTROLLING"
#define DEF_GUI_TOGGLE_WORK          "Streaming Start"

#define DEF_SERIAL_PORT              "/dev/cu.usbserial-DJ00IR6Y"
#define DEF_SERIAL_BAUDRATE          (115200)
#define DEF_SERIAL_PACKET_EOP        (0xC0)
#define DEF_SERIAL_PACKET_PREFIX     (0xA0)
#define DEF_SERIAL_PACKET_AXIS_TOTAL (3)
#define DEF_SERIAL_PACKET_CH_TOTAL   (8)

#define DEF_SENSOR_STREAMING_START   (0x62)
#define DEF_SENSOR_STREAMING_STOP    (0x73)


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
    
    void onWorkPushed(bool &value);
    int  interpret24bitAsInt32(unsigned char byteArray[]);
    int  interpret16bitAsInt32(unsigned char byteArray[]);
    
    ofSerial  _serial;
    ofxPanel  _gui;
    ofxToggle _work;
    
    int       _eeg[8];
    int       _accel[3];
    
    
};
