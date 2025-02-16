#include "calibrate.h"
#include <string>

void Calibrate::calibrate_camera( bool use_camera, std::string path, int frame_num, std::string style ) {   
    //读取所有图像
    std::vector<cv::Mat> imgs;
    std::string onePath;

    //使用通配符 递归查找path下的图像
    std::vector<cv::String> filePaths;
    std::string frame_path = path + style;
    std::cout << "Searching in: " << frame_path << std::endl;
    cv::glob( frame_path, filePaths, true );
    for( const auto& filePath :filePaths ) {
        cv::Mat img = cv::imread( filePath );
        if( !img.empty() ) {
            imgs.push_back( img );
        } else {
            std::cerr << "无法加载图像: " << filePath << std::endl;
        }
    }

    m_board_size = cv::Size(9,6);//方格标定板内角点数目(行,列)
    int num = 0;
    for( int i = 0; i < imgs.size(); i++ ) {
        cv::Mat frame = imgs[i];
        cv::Mat gray;
        cvtColor( frame, gray, cv::COLOR_BGR2GRAY );
        one_point_2D.clear();
        bool find = findChessboardCorners( gray, m_board_size, one_point_2D );//计算方格标定板角点
        if( !find ) { continue; };
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