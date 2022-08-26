#ifndef GLVIEW_H
#define GLVIEW_H

#define GL_SILENCE_DEPRECATION

#include <QtWidgets/QWidget>
#include <QtOpenGL>
#include <QtOpenGLWidgets>

#ifdef __cplusplus
extern "C" {
#endif
#include "../Back.h"
#ifdef __cplusplus
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui { class glView; }
QT_END_NAMESPACE

class glView : public QOpenGLWidget
{
    Q_OBJECT

private:
    double xRot, yRot, zRot;
    QPoint mPos;
    QTimer tmr;
    void drawCube(double d);
    void drawObject();
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

public:
    glView(QWidget *parent = nullptr);
    ~glView();
    int v = 0;
    t_universe a;
    t_universe *data = &a;
private:
    Ui::glView *ui;

};
#endif // GLVIEW_H
