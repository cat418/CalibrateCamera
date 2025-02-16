#include "calibrate.h"

void Calibrate::GetResult() {
    m_matrix.release();
    m_coeffs.release();
    double ReprojectionError = calibrateCamera( all_point_3D, all_point_2D, m_imgSize, m_matrix, m_coeffs, m_rvec, m_tvec, 0);
    std::cout << "内参矩阵为" << ":" << std::endl << m_matrix << std::endl;
    std::cout << "畸变系数为" << ":" << std::endl << m_coeffs << std::endl;
    std::cout << "误差为" << " "<< ReprojectionError << " " << "个像素" << std::endl;
}