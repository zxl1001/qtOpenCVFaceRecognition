/**
 *******************************************************************************
 *                       Continental Confidential
 *                  Copyright (c) Continental AG. 2017
 *
 *      This software is furnished under license and may be used or
 *      copied only in accordance with the terms of such license.
 *******************************************************************************
 * @file    MainWindow.cpp
 * @brief
 *******************************************************************************
 */
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include<QDebug>
#include<QFileDialog>
#include<QPixmap>
#include<QFile>
#include<QTextStream>
#include <QTimer>

//正面,上,下,左,右5张.阉值85.00



MainWindow::MainWindow(QWidget* parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    face_cascade(NULL),
    eyes_cascade(NULL),
    pImg(NULL)/*,
    m_facePanel(new FacePanel(this))*/
{

    ui->setupUi(this);
//    ui->frame->layout()->addWidget(m_facePanel);
    cam     = NULL;
    timer   = new QTimer(this);
    imag    = new QImage();         // 初始化

//    face_cascade_name = "/home/zxl/haarcascade_frontalface_alt.xml";
    face_cascade_name = "/home/zxl/App/opencv-3.2.0/data/haarcascades/haarcascade_frontalface_alt2.xml";
    eyes_cascade_name = "/home/zxl/haarcascade_eye_tree_eyeglasses.xml";
    face_cascade = new CascadeClassifier;
    eyes_cascade = new CascadeClassifier;


    connect(timer, SIGNAL(timeout()), this, SLOT(readFarme()));  // 时间到，读取当前摄像头信息
    connect(ui->open, SIGNAL(clicked()), this, SLOT(openCamara()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openCamara()
{
    cam = cvCreateCameraCapture(0);//打开摄像头，从摄像头中获取视频
    timer->start(33);              // 开始计时，超时则发出timeout()信号
}

/********* 读取摄像头信息 ***********/
void MainWindow::readFarme()
{

    face_cascade->load( face_cascade_name );
    eyes_cascade->load( eyes_cascade_name );
    pImg = cvQueryFrame(cam);// 从摄像头中抓取并返回每一帧
    frame = cv::cvarrToMat(pImg);
    detectAndDisplay(frame);
    QImage image= ConvertToQImage(frame);      //mat  lei zhuanhua wei QImage lei
//    m_facePanel->setFace(image); //// 将图片显示到label上
    ui->label->setPixmap(QPixmap::fromImage(image));

}




QImage MainWindow::IplImageToQImage(IplImage *cvimage)
{
        QImage destImage(cvimage->width, cvimage->height,QImage::Format_RGB32);
        for(int i = 0; i < cvimage->height; i++)
        {
            for(int j = 0; j < cvimage->width; j++)
            {
                int r,g,b;
                if(3 == cvimage->nChannels)
                {
                    b=(int)CV_IMAGE_ELEM(cvimage,uchar,i,j*3+0);
                    g=(int)CV_IMAGE_ELEM(cvimage,uchar,i,j*3+1);
                    r=(int)CV_IMAGE_ELEM(cvimage,uchar,i,j*3+2);
                }
                else if(1 == cvimage->nChannels)
                {
                    b=(int)CV_IMAGE_ELEM(cvimage,uchar,i,j);
                    g=b;
                    r=b;
                }
                    destImage.setPixel(j,i,qRgb(r,g,b));
             }
        }
        return destImage;
}

void MainWindow::detectAndDisplay(Mat& frame)
{
    std::vector<Rect> faces;
    Mat frame_gray;


    cvtColor( frame, frame_gray, /*COLOR_BGR2GRAY*/COLOR_RGB2GRAY);
    equalizeHist( frame_gray, frame_gray );
    //-- 人脸检测
    face_cascade->detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );


    for( size_t i = 0; i < faces.size(); i++ )
    {
        Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
        ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2), 0, 0, 360, Scalar( 255, 0, 255 ), 2, 8, 0 );
    }
    //-- 显示最终效果图paintEvent
//         imshow( "zhanxialie", frame );
    //          QThread::msleep(100);
}

QImage MainWindow::ConvertToQImage(Mat& mat)
{
    QImage img;
    int nChannel=mat.channels();
    if(nChannel==3)
    {
        cv::cvtColor(mat,mat,CV_BGR2RGB);
        img = QImage((const unsigned char*)mat.data,mat.cols,mat.rows,QImage::Format_RGB888);
    }
    else if(nChannel==4||nChannel==1)
    {
        img = QImage((const unsigned char*)mat.data,mat.cols,mat.rows,QImage::Format_ARGB32);
    }

    return img;
}
