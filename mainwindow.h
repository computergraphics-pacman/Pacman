#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void Mouse_Pressed();
    void showMousePosition(QPoint& pos);
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_show_axes_clicked();


    void on_set_point1_clicked();

    void on_set_point2_clicked();

    void on_pushButton_clicked();

    void on_grid_clicked();
    void boundaryFill(int x,int y);
    void boundaryFill(int x,int y,QColor boundaryColor,QColor fillColor);
    void setColor(int x,int y,int a,int b,int c);
    void on_pacman_clicked();
    void fillColor(int x,int y,int a,int b,int c);

private:
    Ui::MainWindow *ui;
    QPoint p1,p2;
    void keyPressEvent(QKeyEvent *);
    void point(int,int);
};

#endif // MAINWINDOW_H
