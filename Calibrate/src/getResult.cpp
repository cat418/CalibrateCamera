#include "calibrate.h"
#include <chrono>

void Calibrate::GetResult() {
    m_matrix.release();
    m_coeffs.release();
    //交互
    std::cout << "计算ing, 时间较长请耐心等待..." << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    double ReprojectionError = calibrateCamera( *all_point_3D, all_point_2D, m_imgSize, m_matrix, m_coeffs, m_rvec, m_tvec, 0);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    cv::destroyAllWindows();
    std::cout << "计算完毕，用时 " << duration.count() / 60 << " min" << std::endl;

    std::cout << "内参矩阵为" << ":" << std::endl << m_matrix << std::endl;
    std::cout << "畸变系数为" << ":" << std::endl << m_coeffs << std::endl;
    std::cout << "误差为" << " "<< ReprojectionError << " " << "个像素" << std::endl;
}