#include <iostream>
#include <opencv2/opencv.hpp>
#include "calibrate.h"
#include <yaml-cpp/yaml.h>

using namespace std;
using namespace cv;

int main()
{
    YAML::Node config = YAML::LoadFile("/home/xzq/project/CalibrateCamera/Calibrate/config/calibrate.yaml");
    bool use_camera = config["use_camera"].as<bool>();
    std::string frame_path = config["frame_path"].as<std::string>();
    std::string style = config["style"].as<std::string>();
    
    Calibrate c;
    if( use_camera ) {
        //打开相机 得到图像
        c.openAndGet( frame_path, style );
    }
    //计算
    c.calibrate_camera( frame_path, style );
    c.GetResult();
}
