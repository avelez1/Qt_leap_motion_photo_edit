/****************************************************************************
**
** Copyright (C) Paul Lemire
** Contact: paul.lemire@epitech.eu
**
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
****************************************************************************/

import QtQuick 2.0
import QtQuick.Window 2.1
import QtLeapMotion 2.0
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.3
import com.myself 1.0
Item {
    id: root
    width : 1000 //Screen.width
    height : Screen.height

    property int oldHandId : -1
    property bool fist : false
    property string sourcePath : "image.png"
    property string imgPath : "image.png"
    property double position_x : 0
    property double position_y : 0

    property bool isPinching : false
    property bool wasPinching : false
    property bool in_root_menu : false
    property bool in_action_menu : false
    property bool in_action_menu1 : false
    property bool in_action_menu2 : true
    property bool in_parameter_menu1: false
    property bool in_parameter_menu2: false
    property bool in_parameter_menu3: false
    property bool in_parameter_menu: true
    property bool color_menu : false
    property bool filter_menu : false
    property bool scale_menu: false

    property bool keyTapped : false
    property bool screenTapped : false
    property int function_called: 0
    property int in_parameter: 0
    property double param1 : 0
    property double param2 : 0
    property double param3 : 0

    property int m1: 1
    property int m2: 1
    property int m3: 2
    property int m4: 1
    property int m5: 1
    property int m6: 1
    property int m7: 2
    property int m8: 1
    property int m9: 3
    property int m : 0

Rectangle
{
    width : 1000 //Screen.width
    height : Screen.height
    color : "#646464"

    Component.onCompleted: console.log("Completed Running!")

    MyObject {
           id: myobject
        }

    HandsMotionArea
    {
        onHandAdded: {
            if (oldHandId === -1)
                oldHandId = hand.id
        }

        onHandRemoved: {
            if (oldHandId !== -1)
            {
                oldHandId = -1;
                fist = false;
            }
        }

        onHandUpdated : {
            if (oldHandId !== -1)
                fist = hand.isFist
            function doSomething(x)                                 // javascript functions
            {
                return x
            }
            console.log(hand.getPosition)
            rect.x = 2*hand.getPosition.x + 500
            rect.y = -2*hand.getPosition.y + 800
            wasPinching = isPinching
            isPinching = false

            if (hand.getPinchStrength > 0.95) {
                wasPinching = isPinching
                isPinching = true
            }

            if ((!isPinching && wasPinching && in_parameter_menu)) {
                var value = (2*hand.getPosition.x + 500 + 200)/200
                switch(in_parameter) {
                case 1:
                    param1 = value
                    break
                case 2:
                    param2 = value
                    break
                case 3:
                    param3 = value
                    break
                default:
                    break
                }



                switch(function_called) {

                case 1:
                    myobject._scaleLin_(param1)
                    break
                case 2:
                    myobject._brightness_(param1)
                    break
                case 3:
                    myobject._contrast_(param1, param2)
                    break
                case 4:
                    myobject._saturate_(param1)
                    break
                case 5:
                    myobject._color2gray_(param1)
                    break
                case 6:
                    myobject._boxBlur_
                    break
                case 7:
                    myobject._gaussianBlur_2D_(param1, param2)
                    break
                case 8:
                    myobject._median_filter_(param1)
                    break
                case 9:
                    myobject._unsharpMask_(param1, param2, param3)
                    break
                default:
                    break
                }


                //tb.text = "Action Taken:Brightness\n Factor: " + Number(value).toLocaleString(Qt.locale("de_DE"))
            }

        }
    }

    SwipeGestureArea {
        id : swipeArea
        anchors.fill: parent

        property int currentGestureId : -1;

        onGestureStarted:
        {

            if (currentGestureId === -1)
            {
                currentGestureId = gesture.id
            }
        }

        onGestureUpdated:
        {
            if (gesture.id === currentGestureId) {
            }
        }

        onGestureEnded:
        {
            if (currentGestureId !== -1)
            {


                if (gesture.speed > 150)
                {
                    var direc = gesture.direction
                    var x_dir = 0
                    var y_dir = 0
                    var z_dir = 0

                    console.log(in_root_menu)
                    if (in_root_menu) {
                        in_root_menu = false

                        var rightToLeft = gesture.startPosition.x < gesture.position.x;
                        if(gesture.startPosition.y > gesture.position.y) {
                            in_action_menu = true
                            if (gesture.startPosition.x < gesture.position.x) {
                                filter_menu = true
                                in_action_menu2 = true
                                console.log("right bottom")

                            } else {
                                color_menu = true
                                in_action_menu1 = true
                                console.log("left bottom")
                            }
                        }

                        if (gesture.startPosition.y < gesture.position.y) {
                            in_action_menu = false
                            scale_menu = true
                            in_parameter_menu = true
                            console.log("top")
                        }

                    }

                    if (in_action_menu) {
                        if (in_action_menu2) {
                            in_action_menu = false
                            in_action_menu2 = false
                            in_parameter_menu = true
                            in_parameter = 1
                            if(function_called == 0 &&  gesture.position.y - gesture.startPosition.y > 30) {
                                function_called = 5
                            }

                            if(function_called == 0 && gesture.position.x - gesture.startPosition.x > 30) {
                                function_called = 6
                            }


                            if(function_called == 0 && gesture.startPosition.y - gesture.position.y > 30) {
                                function_called = 7
                            }


                            if(unction_called == 0 && gesture.startPosition.x - gesture.position.x > 30) {
                                function_called = 8
                            }

                        }

                        if (in_action_menu1) {
                            in_action_menu = false
                            in_action_menu1 = false
                            in_parameter_menu = true
                            in_parameter = 1
                            if(function_called == 0 &&  gesture.position.y - gesture.startPosition.y > 30) {
                                function_called = 1
                            }

                            if(function_called == 0 && gesture.position.x - gesture.startPosition.x > 30) {
                                function_called = 2
                            }


                            if(function_called == 0 && gesture.startPosition.y - gesture.position.y > 30) {
                                function_called = 3
                            }


                            if(unction_called == 0 && gesture.startPosition.x - gesture.position.x > 30) {
                                function_called = 4
                            }

                        }

                    }
                    if (in_parameter_menu) {

                        var param_val = 0

                        rightToLeft = gesture.startPosition.x < gesture.position.x;

                        switch(function_called) {
                        case 1:
                            m = m1
                            break
                        case 2:
                            m = m2
                            break
                        case 3:
                            m = m2
                            break
                        case 4:
                            m = m4
                            break
                        case 5:
                            m = m5
                            break
                        case 6:
                            m = m6
                            break
                        case 7:
                            m = m7
                            break
                        case 8:
                            m = m8
                            break
                        case 9:
                            m = m9
                            break
                        default:
                            break

                        }

                        if (rightToLeft) {
                            if (in_parameter > 1)
                                in_parameter = in_parameter - 1
                            switch(in_parameter) {
                            case 1:
                                param_val = param1
                                break
                            case 2:
                                param_val = param2
                                break
                            case 3:
                                param_val = param3
                                break

                            }

                        } else {
                            if (in_parameter < m) {
                                in_parameter = in_parameter + 1
                                switch(in_parameter) {
                                case 1:
                                    param_val = param1
                                    break
                                case 2:
                                    param_val = param2
                                    break
                                case 3:
                                    param_val = param3
                                    break

                                }
                            }
                        }
                        tb.text = "Parameter " + Number(in_parameter).toLocaleString(Qt.locale("de_DE")) + " " + Number(param_val).toLocaleString(Qt.locale("de_DE"))
                    }
                }
                currentGestureId = -1
//
            }
        }
    }

    CircleGestureArea {
        id : circleArea
        anchors.fill: parent

        property int currentGestureId : -1;

        onGestureStarted:
        {
            if (currentGestureId === -1)
            {
                currentGestureId = gesture.id
            }
        }

        onGestureUpdated:
        {
            if (gesture.id === currentGestureId) {
            }
        }

        onGestureEnded:
        {
            if (currentGestureId !== -1)
            {
                if (gesture.radius > 30)
                {
                    console.log("CIRCLE")
                    currentGestureId = -1;
                    in_root_menu = true
                    in_action_menu = false
                    in_action_menu1 = false
                    in_action_menu2 = true
                    in_parameter_menu1= false
                    in_parameter_menu2= false
                    in_parameter_menu3= false
                    in_parameter_menu= true
                    color_menu = false
                    filter_menu = false
                    scale_menu= false

                    keyTapped = false
                    screenTapped = false
                    function_called = 0
                    in_parameter = 0
                    param1 = 0
                    param2 = 0
                    param3 = 0
                }
                currentGestureId = -1
            }
        }
    }

    ScreenTapGestureArea {
        id : screenTapArea
        anchors.fill: parent

        property int currentGestureId : -1;

        onGestureEnded:
        {
            if (currentGestureId === -1)
            {
                if(gesture.direction.y > 0.8){
                    console.log("Screen Tap Completed")
                    currentGestureId = -1
                    if(in_parameter_menu) {
                        switch(in_parameter) {
                        case 1:
                            param1 = param1 + 1
                            console.log("Param1")
                            console.log(param1)
                            break
                        case 2:
                            param2 = param2 + 1
                            console.log("Param2")
                            console.log(param2)
                            break
                        case 3:
                            param3 = param3 + 1
                            console.log("Param3")
                            console.log(param3)
                            break
                        default:
                            break
                        }

                        switch(function_called) {

                        case 1:
                            myobject._scaleLin_(param1)
                            break
                        case 2:
                            myobject._brightness_(param1)
                            break
                        case 3:
                            myobject._contrast_(param1, param2)
                            break
                        case 4:
                            myobject._saturate_(param1)
                            break
                        case 5:
                            myobject._color2gray_()
                            break
                        case 6:
                            myobject._boxBlur_(param1)
                            break
                        case 7:
                            myobject._gaussianBlur_2D_(param1, param2)
                            break
                        case 8:
                            myobject._median_filter_(param1)
                            break
                        case 9:
                            myobject._unsharpMask_(param1, param2, param3)
                            break
                        default:
                            break
                        }
                    }
                }
                //console.log("Gesture Ended " + gesture + gesture.id)
            }
        }

    }

    KeyTapGestureArea {
        id : keyTapArea
        anchors.fill: parent

        property int currentGestureId : -1;



        onGestureEnded:
        {
            //console.log(gesture.direction)
            if (currentGestureId === -1)
            {
                if(gesture.direction.y < -0.8){
                    currentGestureId = -1
                    console.log("Key Tap Completed")
                    in_parameter = 2

                    if(in_parameter_menu) {
                        switch(in_parameter) {
                        case 1:
                            param1 = param1 - 1
                            console.log("Param1")
                            console.log(param1)
                            break
                        case 2:
                            param2 = param2 - 1
                            console.log("Param2")
                            console.log(param2)
                            break
                        case 3:
                            param3 = param3 - 1
                            console.log("Param3")
                            console.log(param3)
                            break
                        default:
                            break
                        }

                        switch(function_called) {

                        case 1:
                            myobject._scaleLin_(param1)
                            break
                        case 2:
                            myobject._brightness_(param1)
                            break
                        case 3:
                            myobject._contrast_(param1, param2)
                            break
                        case 4:
                            myobject._saturate_(param1)
                            break
                        case 5:
                            myobject._color2gray_()
                            break
                        case 6:
                            myobject._boxBlur_(param1)
                            break
                        case 7:
                            myobject._gaussianBlur_2D_(param1, param2)
                            break
                        case 8:
                            myobject._median_filter_(param1)
                            break
                        case 9:
                            myobject._unsharpMask_(param1, param2, param3)
                            break
                        default:
                            break
                        }
                    }
                }
            }
        }

    }

    anchors.centerIn: parent
    Image {
        id : img
        source: sourcePath
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        cache: false

    }
    Rectangle {
        id: rect
        y: 100; width: 30; height: 30
        radius: width*0.5
        color: "white"
        border.color: "black"
        border.width: 2

    }

    Text {
        id: tb
        y: 10
        anchors.horizontalCenter: parent.horizontalCenter
        text: "UI\n"
        font.family: "Helvetica"
        font.pointSize: 24
        color: "White"
        visible: false
    }

    Text {
        id: tb2
        y: 60
        anchors.horizontalCenter: parent.horizontalCenter
        text: "Hello World\n!"
        font.family: "Helvetica"
        font.pointSize: 16
        color: "White"
        visible: false
    }


}
}
