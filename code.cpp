#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    // 1. Cargar imágenes estéreo en escala de grises
    cv::Mat imgLeft = cv::imread("Left.jpeg", cv::IMREAD_GRAYSCALE);
    cv::Mat imgRight = cv::imread("Right.jpeg", cv::IMREAD_GRAYSCALE);

    if (imgLeft.empty() || imgRight.empty())
    {
        std::cerr << "No se pudieron cargar las imágenes." << std::endl;
        return -1;
    }

    // Asegurar mismo tamaño
    if (imgLeft.size() != imgRight.size())
    {
        std::cout << "Redimensionando" << std::endl;
        cv::resize(imgRight, imgRight, imgLeft.size());
    }

    // 2. Crear objeto StereoBM
    int numDisparities = 64; // múltiplo de 16
    int blockSize = 15;      // tamaño de ventana SAD (impar)
    cv::Ptr<cv::StereoBM> stereo = cv::StereoBM::create(numDisparities, blockSize);

    // 3. Calcular mapa de disparidad
    cv::Mat disparity16S, disparity8U;
    stereo->compute(imgLeft, imgRight, disparity16S);

    disparity16S.convertTo(disparity8U, CV_8U, 255 / (numDisparities * 16.0));

    cv::imshow("Mapa de disparidad", disparity8U);
    cv::waitKey(0);

    // 4. Reproyección 3D (opcional)
    cv::Mat Q = (cv::Mat_<double>(4, 4) <<
        1, 0, 0, -imgLeft.cols/2.0,
        0, -1, 0, imgLeft.rows/2.0,
        0, 0, 0, -500.0,   // distancia focal simulada
        0, 0, 1, 0);

    cv::Mat points3D;
    cv::reprojectImageTo3D(disparity16S, points3D, Q, true);

    // 5. Mostrar algunos puntos 3D de ejemplo
    for (int y = 0; y < imgLeft.rows; y += imgLeft.rows / 10)
    {
        for (int x = 0; x < imgLeft.cols; x += imgLeft.cols / 10)
        {
            cv::Vec3f p = points3D.at<cv::Vec3f>(y, x);
            std::cout << "Punto (" << x << "," << y << "): ["
                      << p[0] << ", " << p[1] << ", " << p[2] << "]" << std::endl;
        }
    }

    return 0;
}
