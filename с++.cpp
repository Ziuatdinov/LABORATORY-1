#include <opencv2/core.hpp> 
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// сложение двух чисел в Uint8 (с учетом переполнение)
unsigned char sumUint8(unsigned char a_uchar, unsigned char b_uchar) {
    int a_int = a_uchar;
    int b_int = b_uchar;
    int z_int;
    unsigned char z_uchar;

    if (a_int + b_int <= 255) {
        z_int = a_int + b_int;

    }
    else {
        z_int = 255;
    }

    z_uchar = (unsigned char)z_int;

    return z_uchar;
}

// вычитание двух чисел в Uint8 (с учетом переполнение)
unsigned char differenceUint8(unsigned char a_uchar, unsigned char b_uchar) {
    int a_int = a_uchar;
    int b_int = b_uchar;
    int z_int;
    unsigned char z_uchar;

    if (a_int - b_int >= 0) {
        z_int = a_int - b_int;

    }
    else {
        z_int = 0;
    }

    z_uchar = (unsigned char)z_int;

    return z_uchar;
}

Mat addImages(Mat& img1, Mat& img2) {
    resize(img2, img2, Size(img1.cols, img1.rows));
    Mat img_add = Mat::zeros(img1.rows, img1.cols, CV_8UC3); //Изображения сложения (изначально оно черная)

    for (int i = 0; i < img_add.rows - 1; i++) {
        for (int j = 0; j < img_add.cols - 1; j++) {

            img_add.at<Vec3b>(i, j)[0] = sumUint8(img1.at<Vec3b>(i, j)[0], img2.at<Vec3b>(i, j)[0]); // обращение к элементу матрицы img_add цвета B
            img_add.at<Vec3b>(i, j)[1] = sumUint8(img1.at<Vec3b>(i, j)[1], img2.at<Vec3b>(i, j)[1]);
            img_add.at<Vec3b>(i, j)[2] = sumUint8(img1.at<Vec3b>(i, j)[2], img2.at<Vec3b>(i, j)[2]);
        }
    }
    return img_add;
}

Mat subtractImages(Mat& img1, Mat& img2) {
    resize(img2, img2, Size(img1.cols, img1.rows));
    Mat img_subtract = Mat::zeros(img1.rows, img1.cols, CV_8UC3);

    for (int i = 0; i < img_subtract.rows - 1; i++) {
        for (int j = 0; j < img_subtract.cols - 1; j++) {

            img_subtract.at<Vec3b>(i, j)[0] = differenceUint8(img1.at<Vec3b>(i, j)[0], img2.at<Vec3b>(i, j)[0]);
            img_subtract.at<Vec3b>(i, j)[1] = differenceUint8(img1.at<Vec3b>(i, j)[1], img2.at<Vec3b>(i, j)[1]);
            img_subtract.at<Vec3b>(i, j)[2] = differenceUint8(img1.at<Vec3b>(i, j)[2], img2.at<Vec3b>(i, j)[2]);
        }
    }
    return img_subtract;
}


int main()
{
    Mat img_add;
    Mat img_subtract;
    Mat img_show;



    Mat img1 = imread("Images/ford.jpg");
    Mat img2 = imread("Images/img1.jpg");

    img_add = addImages(img1, img2);
    img_subtract = subtractImages(img1, img2);

    bool flagAdd = true; // ôëàã ñëîæåíèÿ
    bool flagSubtract = true; // ôëàã âû÷èòàíèÿ

    while (1) {

        img_show = img1;

        if (!flagAdd) {
            img_show = img_add;
        }

        if (!flagSubtract) {
            img_show = img_subtract;
        }

        resize(img_show, img_show, Size(1000, 700));
        imshow("Result", img_show);

        int key = waitKey(1);

        if (key == 27) break;

        if (key == 44) {
            flagSubtract = true;
            flagAdd = !flagAdd;
        }

        if (key == 46) {
            flagAdd = true;
            flagSubtract = !flagSubtract;
        }


    }

    destroyAllWindows();

    return 0;
}
