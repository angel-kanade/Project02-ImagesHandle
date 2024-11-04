#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <opencv2/core.hpp>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QImage imageCenter(QImage qImage, QLabel* qLabel);

private slots:
    void on_btn_Load_clicked();

    void on_btn_Gray_clicked();

    void on_btn_Save_clicked();

    void on_btn_Compress_clicked();

    void on_btn_Decompress_clicked();

    void on_ResizeSlider_valueChanged(int value);

    // void on_btn_Scale_clicked();

private:
    Ui::MainWindow *ui;
    cv::Mat srcImage; //记录原图的变量
    cv::Mat dstImage; //记录处理后的图片
    QString imagePath;
    QImage originalImage;
    QImage processedImage;
};
#endif // MAINWINDOW_H
