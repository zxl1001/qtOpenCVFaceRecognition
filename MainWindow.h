/**
 *******************************************************************************
 *                       Continental Confidential
 *                  Copyright (c) Continental AG. 2017
 *
 *      This software is furnished under license and may be used or
 *      copied only in accordance with the terms of such license.
 *******************************************************************************
 * @file    MainWindow.h
 * @brief
 *******************************************************************************
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QThread>
#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/face.hpp>
#include <opencv2/face/facerec.hpp>
#include "FacePanel.h"

using namespace cv;
using namespace std;

using namespace std;
using namespace cv;
using namespace face;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QImage IplImageToQImage(IplImage *cvimage);

public slots:
    void openCamara();
    void readFarme();

private:
    Ui::MainWindow *ui;
    FacePanel *m_facePanel;
    QTimer    *timer;    //定时器
    QImage    *imag;
    IplImage *pImg;
    QPointF  zxlPos;
    CvCapture *cam;// 视频获取结构， 用来作为视频获取函数的一个参数
    //  IplImage *frame;//申请IplImage类型指针，就是申请内存空间来存放每一帧图像
    cv::Mat frame;//申请IplImage类型指针，就是申请内存空间来存放每一帧图像
    String face_cascade_name ;
    String eyes_cascade_name ;
    CascadeClassifier *face_cascade;
    CascadeClassifier *eyes_cascade;

private:
    void detectAndDisplay( Mat &frame );
    static QImage ConvertToQImage(cv::Mat &mat);
};

#endif // MAINWINDOW_H</span>
