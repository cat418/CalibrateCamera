#include <iostream>
#include <opencv2/opencv.hpp>
#include "calibrate.h"

using namespace std;
using namespace cv;

int main()
{
    Calibrate c;
    c.openAndGet();
    c.calibrate_camera();
    c.GetResult();
}
