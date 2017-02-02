
/*************************************************************************
 * File Name          : testApp.cpp
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

#include "testApp.h"

/*! *******************************************************************
 *  @fn         interpret16bitAsInt32
 *  @brief      This function is converter from 16bit to 32bit
 *              of Int, MSB first.
 *
 *
 *  @param[in]  byteArray   :   16bit Int data.
 *  @return     retInt_     :   32bit Int data.
 *  @version    v1.00
 *  @date       01/10/2017 v1.00 Create On.
 **********************************************************************/
int testApp::interpret16bitAsInt32(unsigned char byteArray[]) {
    
    int retInt_ = 0;
    
    retInt_ = (((0xFF & byteArray[0]) << 8) |
               (0xFF & byteArray[1]));
    
    if ((retInt_ & 0x00008000) > 0) retInt_ |= 0xFFFF0000;
    else                            retInt_ &= 0x0000FFFF;
    
    return retInt_;
}

/*! *******************************************************************
 *  @fn         interpret24bitAsInt32
 *  @brief      This function is converter from 24bit to 32bit
 *              of Int, MSB first.
 *
 *  @param[in]  byteArray   :   24bit Int data.
 *  @return     retInt_     :   32bit Int data.
 *  @version    v1.00
 *  @date       01/10/2017 v1.00 Create On.
 **********************************************************************/
int testApp::interpret24bitAsInt32(unsigned char byteArray[]){
    
    int retInt_ = 0;
    
    retInt_ = (((0xFF & byteArray[0]) << 16) |
               ((0xFF & byteArray[1]) << 8) | (0xFF & byteArray[2]));
    
    if ((retInt_ & 0x00800000) > 0) retInt_ |= 0xFF000000;
    else                            retInt_ &= 0x00FFFFFF;
    
    return retInt_;
}

/*! *******************************************************************
 *  @fn         onWorkPushed
 *  @brief      This function is pushed the Toggle Button.
 *
 *  @param[in]  void
 *  @return     void
 *  @version    v1.00
 *  @date       01/10/2017 v1.00 Create On.
 **********************************************************************/
void testApp::onWorkPushed(bool &value){
    return value ? (_serial.writeByte(DEF_SENSOR_STREAMING_START)) :
    (_serial.writeByte(DEF_SENSOR_STREAMING_STOP));
}

/*! *******************************************************************
 *  @fn         setup [Default function]
 *  @brief      This function is the Initilize Process.
 *
 *  @param[in]  void
 *  @return     void
 *  @version    v1.00
 *  @date       01/10/2017 v1.00 Create On.
 **********************************************************************/
void testApp::setup(){
    
    for(unsigned int i = 0; i < DEF_SERIAL_PACKET_CH_TOTAL; ++i)   _eeg[i]   = 0;
    for(unsigned int i = 0; i < DEF_SERIAL_PACKET_AXIS_TOTAL; ++i) _accel[i] = 0;
    
    ofBackground(ofColor::black);
    
    _serial.setup(DEF_SERIAL_PORT, DEF_SERIAL_BAUDRATE);
    
    _gui.setup(DEF_GUI_TITLE);
    _gui.add(_work.setup(DEF_GUI_TOGGLE_WORK, false));
    _work.addListener(this, &testApp::onWorkPushed);
    
    return;
}

/*! *******************************************************************
 *  @fn         update [Default function]
 *  @brief      This function is the Data Update Process.
 *
 *  @param[in]  void
 *  @return     void
 *  @version    v1.00
 *  @date       01/10/2017 v1.00 Create On.
 **********************************************************************/
void testApp::update(){
    
    short         dataCoupling_ = 0;

    unsigned char eop_          = 0;
    unsigned char prefix_       = 0;
    unsigned char msb_          = 0;
    unsigned char lsb_          = 0;
    unsigned char counter_      = 0;
    
    unsigned char eegByteArray_[3];
    unsigned char accelByteArray_[2];
    
    for(unsigned int i = 0; i < 3; ++i) eegByteArray_[i] = 0;
    for(unsigned int i = 0; i < 2; ++i) accelByteArray_[i] = 0;
    
    
    while(_serial.available() > 0){
        eop_ = _serial.readByte();
        
        if(eop_ == DEF_SERIAL_PACKET_EOP){
            prefix_ = _serial.readByte();
            
            if(prefix_ == DEF_SERIAL_PACKET_PREFIX){
                counter_ = _serial.readByte();

                // Channel x 8 (1ch = 3 byte).
                for(unsigned int i = 0; i < DEF_SERIAL_PACKET_CH_TOTAL; ++i){
                    for(unsigned int j = 0; j < 3; ++j){
                        eegByteArray_[j] = _serial.readByte();
                    }
                    _eeg[i] = interpret24bitAsInt32(eegByteArray_);
                }

                // Accel x 3 (x, y, z).
                for(unsigned int i = 0; i < DEF_SERIAL_PACKET_AXIS_TOTAL; ++i){
                    msb_ = _serial.readByte();
                    lsb_ = _serial.readByte();
                    _accel[i] = (msb_ << 8) | lsb_;
                }
            }
        }
    }
    
    return;
}

/*! *******************************************************************
 *  @fn         draw [Default function]
 *  @brief      This function is the Draw Process.
 *
 *  @param[in]  void
 *  @return     void
 *  @version    v1.00
 *  @date       01/10/2017 v1.00 Create On.
 **********************************************************************/
void testApp::draw(){
    
    stringstream reportStr;
    
    _gui.draw();
    
    for(unsigned int i = 0; i < DEF_SERIAL_PACKET_CH_TOTAL; ++i){
        reportStr << " EEG " << (i + 1) << "ch: " << _eeg[i] << endl;
    }

    reportStr << "          " << endl;
  
    for(unsigned int i = 0; i < DEF_SERIAL_PACKET_AXIS_TOTAL; ++i){
        reportStr << " Accel X: " << _accel[i] << endl;
    }

    ofDrawBitmapString(reportStr.str(), 20, 250);
    
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
