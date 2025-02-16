#include "calibrate.h"
#include "HikDriver/HikDriver.h"
#include <string>

void Calibrate::openAndGet( std::string img_path, std::string style )
{
    HikDriver hik_drive(0);
    if(hik_drive.isConnected()) {
        // hik_drive.setAutoGain(1);
        // hik_drive.setAutoExposureTime(1);
        hik_drive.setGain(15);
        hik_drive.setExposureTime(30000);
        hik_drive.showParamInfo();
        hik_drive.startReadThread();
    }
    int count =0;
    while(true) {
        HikFrame Frame = hik_drive.getFrame();
        cv::Mat frame = Frame.getRgbFrame()->clone();
        if( frame.empty()) {
            continue;
        }
        imshow( "frame", frame);
        //按空格抓取图片
        int key = cv::waitKey(1);    
        if( key == 32 ) {
            //保存图片
            m_output = img_path;
            std::string num = std::to_string ( count );
            std::string m_style = style;
            std::string outputPath = m_output + num + m_style;
            cv::imwrite( outputPath, frame);
            count ++;
            m_outputPath.push_back( outputPath );
        }
        if(key == 27) {
            std::cout << "停止抓取图片" << std::endl;
            break;
        }
    }
    m_count = count;
    return;
}