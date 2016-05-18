// imshowArrange.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"

void imshowArrange(std::vector<cv::Mat> imgList)
{
    //  ���낢�돉����
    int maxHeight = 1080;
    int maxWidth = 1920;
    int max_sz = maxHeight*maxWidth;
    cv::Size monitorSize(maxWidth, maxHeight);
    int titleHeight = 16;
    int boundaryWidth = 8;
    int boundaryHeight = boundaryWidth;    
    
    int num = (int)imgList.size();

    ////  �T�C�Y���ɕ��בւ�
    //std::vector<std::pair<long, cv::Mat>> imgListSort(num, std::make_pair(0, cv::Mat()));
    //for (int i = 0; i < num; i++)
    //{
    //    cv::Mat img = imgList[i];
    //    int sz = img.rows*img.cols;
    //    imgListSort[i] = std::make_pair((long)sz, img);
    //}
    //std::sort(imgListSort.begin(), imgListSort.end());

    //  �L���͈̓}�b�v
    cv::Mat availableMap = cv::Mat::zeros(monitorSize, CV_8UC1);

    //  �撣���ĕ\��
    for (int i = num - 1; i >= 0; i--)
    {
        cv::Mat img = imgList[i];
        cv::Mat availableMapTmp = availableMap.clone();
        while (1)
        {
            //  ���ډ摜�̃T�C�Y
            int height = img.rows + titleHeight + boundaryHeight;
            int width = img.cols + 2 * boundaryWidth;
            //  �������������
            cv::Point p(-1,-1);
            for (int j = 0; j < max_sz; j++)
            if (availableMapTmp.at<uchar>(j) == 0){ p.x = j % maxWidth; p.y = j / maxHeight; break; }
            if (p == cv::Point(-1, -1)) break;  //�S�����܂��Ă�������߂�            
            //  �����ɕ`��ł��邩���`�F�b�N����
            bool showable = true;
            if (p.y + height > maxHeight - 1 || p.x + width > maxWidth - 1)
                showable = false;   //  ���������͂ݏo��
            for (int y = p.y; y < p.y + height; y++)
                for (int x = p.x; x < p.x + width; x++)
                    if (availableMapTmp.at<uchar>(y, x) == 255) showable = false;   //���̕`�挋�ʂɏd�Ȃ�

            //  �`��ł���ꍇ
            if (showable)
            {
                //  �\�����āA�g�����L���̈��h��Ԃ�
                char winName[16];
                sprintf(winName, "%02d", i);
                cv::imshow(winName, img);
                cv::moveWindow(winName, p.x, p.y);
                for (int y = p.y; y < p.y + height; y++)
                for (int x = p.x; x < p.x + width; x++)
                    availableMap.at<uchar>(y, x) = 255;
            }
            //  �`��ł��Ȃ��ꍇ�A���̌���T��
            else
            {
                for (int y = p.y; y < p.y + height; y++)
                {
                    if (y > maxHeight - 1) break;
                    for (int x = p.x; x < p.x + width; x++)
                    {
                        if (x > maxWidth - 1) break;
                        availableMapTmp.at<uchar>(y, x) = 255;
                    }
                }
            }
        }
    }

    cv::waitKey();
}

int main(int argc, _TCHAR* argv[])
{
    std::vector<cv::Mat> imgList{
    cv::Mat(cv::Size(320,240),CV_8UC3,cv::Scalar(0,0,255)),
    cv::Mat(cv::Size(320, 560), CV_8UC3, cv::Scalar(0, 255, 0)),
    cv::Mat(cv::Size(120, 720), CV_8UC3, cv::Scalar(255, 0, 0)),
    cv::Mat(cv::Size(320, 480), CV_8UC3, cv::Scalar(0, 255, 255)),
    cv::Mat(cv::Size(320, 240), CV_8UC3, cv::Scalar(255, 0, 255))
    };
    
    imshowArrange(imgList);
	return 0;
}

