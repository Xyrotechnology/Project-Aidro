// Created by Marzouq Abedur Rahman 16/11/2015
// Priority level 1, carry out experiments immediately after Mark 1 arrive.
// This program will only work in direct input, so additional tweaks must be made for the response to be in 'MAVlink'
// format.
// Not a big deal, just use os commands as the raspberry pi will do the image processing.
int main(int argc, char* argv[])
{


    //Matrix to store camera frames
    Mat cameraFeed;
    Mat threshold,thresholdRed,thresholdBlue,thresholdGreen;
    Mat HSV;

    VideoCapture capture;
    capture.open(0);
    capture.set(CV_CAP_PROP_FRAME_WIDTH,FRAME_WIDTH);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT,FRAME_HEIGHT);

    //Create infinite loop
    bool loop = true;
    while(loop)
    {
        capture >> cameraFeed;
        capture.read(cameraFeed);

        //Convert to HSV
        cvtColor(cameraFeed,HSV,COLOR_BGR2HSV);

        //ADD GAUSIAN BLUR
        GaussianBlur(HSV,HSV,Size(5,5),0,0);

        Object groundRobotRed("groundRobotRed");

        //Values taken from trackbars
        groundRobotRed.setHSVmin(Scalar(18, 44, 103));
        groundRobotRed.setHSVmax(Scalar(36,142,249));

        inRange(HSV,groundRobotRed.getHSVmin(),groundRobotRed.getHSVmax(),thresholdRed);
        morphOps(thresholdRed);
        trackFilteredObject(groundRobotRed,thresholdRed,HSV,cameraFeed);

            //Quadcopter Systems Check
            if (flying == 0)
            {
                std::cout<<"hello:"<<std::endl;
                test_control.conn();
                test=test_control.isConnected();
                cout<<"test:"<<test<<endl;
                if (test)
                    testing();
                else
                    loop = false;
            }


         //If object is located on the top of the screen
         if(groundRobotRed.getYPos()<<240)
         {
         //Pitch forward command, insert the mavlink command here
         test_control.transmit(570, 565, 500, 500, 0, 0, 0, 0, 0);
         std:cout<<"Pitch Complete"<<std::endl;
         }
         else
         {
           //Hover command
           test_control.transmit(570,565,500,500,0,0,0,0,0);
         }


            capture.release();
            HSV.release();
            thresholdRed.release();

            capture.open(0);


            imshow(windowName,cameraFeed);
            waitKey(10);


        }

    return 0;
}

