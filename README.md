# qtOpenCVFaceRecognition
Qt5.7. 0+Opencv3.2.0 + opencv_contrib-3.2.0
主要是用于简单测试OPENCV人脸识别测试实例.
可做为开发复杂功能的一个入门参考.

***********comp opencv********************
1.准备文件
cd tool
unzip  opencv-3.2.0.zip              #被解压到了 tool/opencv-3.2.0
tar zxvf opencv_contrib-3.2.0.tar.gz #被解压到了 tool/opencv_contrib-3.2.0.tar.gz
cp opencv-3.0.2/opencv_contrib-3.2.0/model/face opencv-3.0.2/model

[因为opencv默认model里是没有face(人脸识别模块).该模板存放于opencv的contrib扩展库里.所以需要把人脸识别模块放到opencv的mode文件里.编译opencv的时候,人脸模块就会一起被编译.]



2.新建build文件夹存放opencv的编译文件，进入build文件夹代码如下
cd opencv_3.0.2   #进入刚解好的opencv-3.2.0文件夹
mkdir build
mkdir install    //opencv编译好后安装的目录,也可不指定,默认选择/usr/local
cd build


3.配置opencv文件，代码如下：

cmake -D CMAKE_BUILD_TYPE=[Release|Debug] -D CMAKE_INSTALL_PREFIX=/home/家目录名/.../opencv-3.0.2/install ..

*如果是windows可以使用cmake-gui用图形界面编译。

4.进行编译，代码如下：

make

[
	编译过程序中提示ippicv_linux_20151201.tgz downing.....
	是因为Opencv本身带的这个文件的md5值较验不过.(不可思义)
	请把 tool/ippicv_linux_20151201.tgz 替换掉相应文件:

	cp tool/ippicv_linux_20151201.tgz tool/opencv-3.2.0/3rdparty/ippicv/downloads/linux-808b791a6eac9ed78d32a7666804320e/ippicv_linux_20151201.tgz

然后重新make
]

7.安装opencv库到系统，代码如下：

sudo make install

这样OpenCV就可以使用了。可以查看 install目录: tool/install

基他:
程序里库的使用配置,请看 pro文件
模式识别的训练文本请看
data/haarcascade_frontalface_alt.xml        脸部训练文件
 data/~/haarcascade_eye_tree_eyeglasses.xml 眼部训练文件
