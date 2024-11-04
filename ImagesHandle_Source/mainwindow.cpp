#include "mainwindow.h"  // 引入主窗口头文件
#include "ui_mainwindow.h"  // 引入UI头文件
#include <QFileDialog>  // 引入文件对话框头文件
#include <opencv2/core/core.hpp>  // 引入OpenCV核心模块
#include <opencv2/highgui/highgui.hpp>  // 引入OpenCV高层GUI模块
#include <opencv2/opencv.hpp>  // 引入OpenCV主要模块
#include <QLabel>  // 引入标签控件头文件

// 构造函数，初始化主窗口
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);  // 设置UI
    ui->ResizeSlider->setRange(1,200);  // 设置缩放滑块范围
    ui->ResizeSlider->setValue(50);  // 设置滑块初始值为50
    connect(ui->ResizeSlider,SIGNAL(valueChanged(int)),this,SLOT(on_ResizeSlider_valueChanged(int)));  // 连接滑块值变化信号与槽函数
}

// 析构函数，释放UI资源
MainWindow::~MainWindow(){
    delete ui;  // 删除UI对象
}

// 图像居中方法，根据标签大小调整图像大小
QImage MainWindow::imageCenter(QImage qImage, QLabel* qLabel){
    QSize imageSize = qImage.size();  // 获取图像大小
    QSize labelSize = qLabel->size();  // 获取标签大小
    double dWidthRatio = 1.0 * imageSize.width() / labelSize.width();  // 计算宽度比例
    double dHeightRatio = 1.0 * imageSize.height() / labelSize.height();  // 计算高度比例
    if (dWidthRatio > dHeightRatio){  // 如果宽度比例大于高度比例
        return qImage.scaledToWidth(labelSize.width());  // 按宽度缩放图像
    }
    else {
        return qImage.scaledToHeight(labelSize.height());  // 按高度缩放图像
    }
}

// 加载图像按钮点击事件处理函数
void MainWindow::on_btn_Load_clicked(){
    imagePath = QFileDialog::getOpenFileName(this, tr("打开图片"), "C:", "所有图像(*.png *.jpg *.ppm *.bmp)");  // 打开文件对话框选择图像
    if (imagePath.isEmpty()) return;  // 如果未选择图像则返回
    srcImage = cv::imread(imagePath.toStdString());  // 使用OpenCV读取图像
    cv::cvtColor(srcImage, srcImage, cv::COLOR_BGR2RGB);  // 将颜色空间从BGR转换为RGB
    dstImage = srcImage.clone();  // 克隆源图像到目标图像
    originalImage = QImage(srcImage.data, srcImage.cols, srcImage.rows, srcImage.step, QImage::Format_RGB888);  // 创建QImage对象

    QImage displayImage = imageCenter(originalImage, ui->lbl_show1);  // 居中处理图像
    ui->lbl_show1->setPixmap(QPixmap::fromImage(displayImage));  // 显示图像
    ui->led_show1->setText(QString("%1 x %2").arg(srcImage.cols).arg(srcImage.rows));  // 显示图像尺寸
}

// 保存图像按钮点击事件处理函数
void MainWindow::on_btn_Save_clicked(){
    if (dstImage.empty()) return;  // 如果目标图像为空，则返回
    QString savePath = QFileDialog::getSaveFileName(this, tr("保存图片"), "C:", "所有图像(*.png *.jpg *.bmp)");  // 打开保存文件对话框
    if (savePath.isEmpty()) return;  // 如果未选择保存路径，则返回
    bool success = cv::imwrite(savePath.toStdString(), dstImage);  // 使用OpenCV保存图像
    if (!success){  // 如果保存失败
        qDebug() << "Failed to save image to" << savePath;  // 输出调试信息
    }
    else{  // 如果保存成功
        qDebug() << "Image saved successfully to" << savePath;  // 输出调试信息
    }
}

// 转为灰度图像按钮点击事件处理函数
void MainWindow::on_btn_Gray_clicked(){
    cv::Mat resultImage;  // 定义结果图像
    cv::cvtColor(srcImage, resultImage, cv::COLOR_BGR2GRAY);  // 将源图像转换为灰度图像
    resultImage.convertTo(resultImage, CV_8UC1); // 确保数据类型为CV_8UC1
    dstImage = resultImage.clone();  // 克隆灰度图像到目标图像
    processedImage = QImage(resultImage.data, resultImage.cols, resultImage.rows, resultImage.step, QImage::Format_Grayscale8);  // 创建QImage对象

    QImage displayImage = imageCenter(processedImage, ui->lbl_show2);  // 居中处理图像
    ui->lbl_show2->setPixmap(QPixmap::fromImage(displayImage));  // 显示图像
    ui->led_show2->setText(QString("%1 x %2").arg(dstImage.cols).arg(dstImage.rows));  // 显示图像尺寸
}

// 压缩图像按钮点击事件处理函数
void MainWindow::on_btn_Compress_clicked(){
    if (srcImage.empty()) return;  // 如果源图像为空，则返回

    // 将BGR格式转换为RGB格式
    cv::Mat rgbImage;
    cv::cvtColor(srcImage, rgbImage, cv::COLOR_BGR2RGB);  // 转换颜色空间

    std::vector<uchar> compressedData;  // 存储压缩数据
    std::vector<int> params = {cv::IMWRITE_JPEG_QUALITY, 100}; // 用户可配置压缩质量
    cv::imencode(".jpg", rgbImage, compressedData, params); // 使用JPEG格式压缩图像

    QString savePath = QFileDialog::getSaveFileName(this, tr("保存压缩图像"), "C:", "JPEG图像(*.jpg)");  // 打开保存文件对话框
    if (savePath.isEmpty()) return; // 用户取消操作

    QFile file(savePath);  // 创建文件对象
    if (file.open(QIODevice::WriteOnly)){  // 打开文件以进行写入
        file.write(reinterpret_cast<const char*>(compressedData.data()), compressedData.size());  // 写入压缩数据
        file.close();  // 关闭文件
    } else {
        qDebug() << "Failed to open file for writing.";  // 输出调试信息
    }
}

// 解压缩图像按钮点击事件处理函数
void MainWindow::on_btn_Decompress_clicked() {
    QFile file(imagePath);  // 创建文件对象
    if (!file.open(QIODevice::ReadOnly)){  // 打开文件以进行读取
        qDebug() << "Failed to open file for reading.";  // 输出调试信息
        return;
    }
    QByteArray compressedData = file.readAll();  // 读取所有压缩数据
    file.close();  // 关闭文件

    if (compressedData.isEmpty()){  // 如果未读取到数据
        qDebug() << "No data read from file.";  // 输出调试信息
        return;
    }

    std::vector<uchar> buf(compressedData.begin(), compressedData.end());  // 将压缩数据转换为vector
    cv::Mat decompressedImg = cv::imdecode(buf, cv::IMREAD_COLOR);  // 解压缩数据

    if (decompressedImg.empty()){  // 如果解压失败
        qDebug() << "Failed to decompress image.";  // 输出调试信息
        return;
    }

    dstImage = decompressedImg.clone();  // 克隆解压缩图像到目标图像
    // 由于Qt和OpenCV使用的三元组不同需要转换
    processedImage = QImage(dstImage.data, dstImage.cols, dstImage.rows, dstImage.step, QImage::Format_BGR888);  // 创建QImage对象
    QImage showImage = imageCenter(processedImage, ui->lbl_show2);  // 居中处理图像
    ui->lbl_show2->setPixmap(QPixmap::fromImage(showImage));  // 显示图像
    ui->led_show2->setText(QString("%1 x %2").arg(dstImage.cols).arg(dstImage.rows));  // 显示图像尺寸
}

// 处理缩放滑块值变化的槽函数
void MainWindow::on_ResizeSlider_valueChanged(int value){
    if (dstImage.empty()) return;  // 如果目标图像为空，则返回
    double ratio = (double) value / 50;  // 计算缩放比例
    int newWidth = srcImage.cols * ratio;  // 计算新宽度
    int newHeight = srcImage.rows * ratio;  // 计算新高度
    cv::Mat resizedImage;  // 创建缩放后的图像
    cv::resize(srcImage,resizedImage,cv::Size(newWidth,newHeight));  // 调整图像大小
    dstImage = resizedImage.clone();  // 克隆缩放后的图像到目标图像
    cv::cvtColor(dstImage,dstImage,cv::COLOR_BGR2RGB);  // 转换颜色空间
    processedImage = QImage(dstImage.data, dstImage.cols, dstImage.rows, dstImage.step, QImage::Format_BGR888);  // 创建QImage对象
    QImage displayImage = imageCenter(processedImage,ui->lbl_show2);  // 居中处理图像
    ui->lbl_show2->setPixmap(QPixmap::fromImage(displayImage));  // 显示图像

    // 更新分辨率显示
    ui->led_show1->setText(QString("%1 x %2").arg(srcImage.cols).arg(srcImage.rows));  // 显示源图像尺寸
    ui->led_show2->setText(QString("%1 x %2").arg(dstImage.cols).arg(dstImage.rows));  // 显示目标图像尺寸
}

// 下面的代码被注释掉，想实现缩放键复位 但效果不好，暂时不用
// void MainWindow::on_btn_Scale_clicked(){
//     QImage curImage = QImage(dstImage.data, dstImage.cols, dstImage.rows, dstImage.step, QImage::Format_RGB888);
//     QImage displayImage = imageCenter(curImage, ui->lbl_show2);
//     ui->lbl_show2->setPixmap(QPixmap::fromImage(displayImage));
//     ui->led_show2->setText(QString("%1 x %2").arg(dstImage.cols).arg(dstImage.rows));
//     ui->ResizeSlider->setValue(50);
// }
