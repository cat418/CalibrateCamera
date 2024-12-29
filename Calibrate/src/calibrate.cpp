#include "calibrate.h"

void Calibrate::calibrate_camera() {   
    //读取所有图像
    std::vector<cv::Mat> imgs;
    std::string onePath;
    //创建文本
    std::ofstream output ("calibrate.txt");
    if( !output.is_open() ) {
        std::cout << "为图像路径创建文本失败" << std::endl;
    }
    //将图片路径写入
    for ( int i=0; i < m_count; i ++) {
        output << m_outputPath[i] << std::endl;
    }
    //获取每一个图像的路径
    std::ifstream allPath("calibrate.txt");
    while (std::getline(allPath,onePath)) {
        cv::Mat img = cv::imread( onePath );
        imgs.push_back( img );
    }
    m_board_size = cv::Size(9,6);//方格标定板内角点数目(行,列)
    int num = 0;
    for( int i = 0; i < imgs.size(); i++ ) {
        cv::Mat frame = imgs[i];
        cv::Mat gray;
        cvtColor( frame, gray, cv::COLOR_BGR2GRAY );
        one_point_2D.clear();
        findChessboardCorners( gray, m_board_size, one_point_2D );//计算方格标定板角点
        find4QuadCornerSubpix( gray, one_point_2D, cv::Size(5,5) );//细化方格标定板角点坐标
        //绘制标定结果
        cv::Mat img = frame.clone();
        cv::drawChessboardCorners( img, m_board_size, one_point_2D, true);
        cv::imshow( "num", img);
        all_point_2D.push_back( one_point_2D );
        num ++;
        int key =cv::waitKey(0);
        if( key == 13 ) {
            continue;
        }
    }
    //生成棋盘格每个内角点的空间三维坐标
    cv::Size reallySize = cv::Size(10,10);
    for( int i = 0; i < all_point_2D.size() ; i++ ) {
        one_point_3D.clear();
        for( int j = 0; j < m_board_size.height; j ++) {
            for( int k = 0; k < m_board_size.width; k ++) {
                //假设标定板世界坐标系的z平面
                realPoint.x = j*realSize.width;
                realPoint.y = k*reallySize.height;
                realPoint.z = 0;
                one_point_3D.push_back( realPoint );
            }
        }
        all_point_3D.push_back( one_point_3D );
    }
    //图像尺寸
    m_imgSize.width = imgs[0].cols;
    m_imgSize.height = imgs[0].rows;
}