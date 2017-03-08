#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_loadimage_clicked();

    void on_spinBox_x_valueChanged(int arg1);

    void on_spinBox_y_valueChanged(int arg2);

    void on_spinBox_z_valueChanged(int arg3);

    void on_binarize_clicked();

    void on_DT_clicked();

    void on_histogram_equilization_clicked();


    void on_ccl_clicked();

private:
    Ui::MainWindow *ui;
    QString base;
    std::string str;
    const char *ch;
    QByteArray filename;
    unsigned short Xdim;
    unsigned short Ydim;
    unsigned short Zdim;
    unsigned short curX;
    unsigned short curY;
    unsigned short curZ;
    void drawimage();
    void drawimage_XY();
    void drawimage_XZ();
    void drawimage_YZ();
    void histogram();
    void readimage();
};

#endif // MAINWINDOW_H
