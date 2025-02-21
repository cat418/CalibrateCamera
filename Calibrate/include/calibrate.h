#ifndef CALIBRATE_H
#define CALIBRATE_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <string>
#include <memory>
#include <chrono>

class Calibrate
{
public:
    //构造函数 析构函数
    Calibrate() = default;
    ~Calibrate() = default;
public:
    //打开相机
    void openAndGet( std::string img_path, std::string style );
    //标定 计算结果
    void calibrate_camera( std::string path, std::string style );
    //输出结果
    void GetResult();
public:
    int m_count;//图片数量
    std::string m_output;//路径
    std::vector<std::string> m_outputPath;//路径+图片名字
    std::unique_ptr<std::vector<std::vector<cv::Point3f>>> all_point_3D = std::make_unique<std::vector<std::vector<cv::Point3f>>>();
    std::vector<cv::Point3f> one_point_3D;
    cv::Point3f realPoint;
    std::vector<std::vector<cv::Point2f>> all_point_2D ;
    std::vector<cv::Point2f> one_point_2D;
    cv::Size realSize = cv::Size( 10, 10 );//棋盘格每个方格的真实尺寸
    cv::Mat m_matrix = cv::Mat ( 3, 3, CV_32FC1, cv::Scalar::all(0));//相机内参矩阵
    cv::Mat m_coeffs = cv::Mat ( 1, 5, CV_32FC1, cv::Scalar::all(0));//相机畸变系数
    cv::Mat m_tvec;//平移矩形
    cv::Mat m_rvec;//旋转矩形
    cv::Size m_imgSize;//图像尺寸
    cv::Size m_board_size;//方格标定板内角点数目
};

#endif //CALIBRATE_H
