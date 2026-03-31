#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

void prep2EinkSPI(const Mat &img, vector<uint8_t> &bytes)
{
    int width = img.cols;
    int height = img.rows;
    int k = 0;

    const uchar *data = img.data;
    int step = img.step;

    for (int y = 0; y < height; y++)
    {
        const uchar *row = data + y * step;
        uint8_t outByte = 0b0;
        

        for (int xByte = 0; xByte < width; xByte++)
        {

            int bite = row[xByte];

            if (bite < 128)
            {
                outByte <<= 1;
                k++;
            }
            else
            {
                outByte <<= 1;
                outByte += 0b1;
                k++;
            }

            if (k == 8)
            {
                k = 0;
                bytes.push_back(outByte);

                outByte = 0b0;
            }
        }
    }
}

vector<uint8_t> img2eink()
{
    Mat img = imread("m.png");

    if (img.empty())
    {
        cout << "Image not found\n";
        exit;
    }

    Mat resized;
    resize(img, resized, Size(184, 88), 0, 0, INTER_AREA);

    Mat rotated;
    rotate(resized, rotated, ROTATE_90_COUNTERCLOCKWISE);

    Mat gray;
    cvtColor(rotated, gray, COLOR_BGR2GRAY);

    Mat lut(1, 256, CV_8U);

    float k = 1.5f;

    for (int i = 0; i < 256; i++)
    {
        int v = (i - 128) * k + 128;

        if (v < 0)
            v = 0;
        if (v > 255)
            v = 255;

        lut.at<uchar>(i) = v;
    }

    Mat lgray;

    LUT(gray, lut, lgray);

    vector<uint8_t> out_im;

    prep2EinkSPI(lgray, out_im);

    return out_im;
}

int main()
{
    int k =0;
    std::vector<uint8_t> data = img2eink();

    for (auto v : data)
    {
        std::cout << (int)v << ", ";
        k++;
    }
    cout << endl << k;
    cin.get();
}
