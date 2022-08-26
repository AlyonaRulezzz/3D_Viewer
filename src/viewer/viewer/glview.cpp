#include "glview.h"
#include "ui_glview.h"

glView::glView(QWidget *parent)
    : QOpenGLWidget(parent)
    , ui(new Ui::glView)
{
    ui->setupUi(this);
    setWindowTitle("3D Viewer");
//    setGeometry(400, 200, 800, 600);
    loading(data, (char*)"/Users/gabriela/viewer/pl.obj");
    double array_3d[(data->sum_vertexes+1)*3];
    matrixToArray(data, array_3d);
    v = data->v;
}

glView::~glView()
{
    delete ui;
}

void glView::initializeGL() {
    glEnable(GL_DEPTH_TEST);
}

void glView::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//    glOrtho(-1,1, -1,1, 1,3);
    glFrustum(-1,1, -1,1, 1,3);
}

void glView::paintGL() {
    glClearColor(2, 0, 2, 0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glScaled(1,1,1);
    glTranslated(0, 0, -2);
    glRotated(xRot, 1, 0, 0);
    glRotated(yRot, 0, 1, 0);
//    drawCube(0.5);
    drawObject();
}


void glView::mousePressEvent(QMouseEvent* mo) {
    mPos = mo->pos();
}

void glView::mouseMoveEvent(QMouseEvent* mo) {
    xRot = 1 / M_PI*(mo->pos().y()-mPos.y());
    yRot = 1 / M_PI*(mo->pos().x()-mPos.x());
    update();
}

//void glView::drawCube(double d) {

//    double vertex_array[] = {0,0,0, -d, d, d,     d, d, d,      d, -d, d,     -d, -d, d,
//                                    -d, -d, -d,   -d, d, -d,    d, -d, -d,    d, d, -d};

//    int indexes_array[] = {1,2, 2,3, 3,4, 4,1,
//                           1,4, 4,5, 5,6, 6,1,
//                           2,3, 3,7, 7,8, 8,2,
//                           6,8, 8,7, 7,5, 5,6,
//                           1,2, 2,8, 8,6, 6,1,
//                           4,3, 3,7, 7,5, 5,4};

//    double color_cube[] = {0,0,0};

//    glVertexPointer(3, GL_DOUBLE, 0, vertex_array);
////    glVertexPointer(3, GL_DOUBLE, 0, &data->matrix_3d);
//    glEnableClientState(GL_VERTEX_ARRAY);

//    glColorPointer(3, GL_DOUBLE, 0, &color_cube);
//    glEnableClientState(GL_COLOR_ARRAY);

////        glColor3d(0, 0, 1);
////        glDrawArrays(GL_QUADS, 0, 24);
//        glDrawElements(GL_LINES, 48, GL_UNSIGNED_INT, indexes_array);

//    glDisableClientState(GL_COLOR_ARRAY);
//    glDisableClientState(GL_VERTEX_ARRAY);
//}

void glView::drawObject() {

    t_universe a;
    t_universe *data = &a;

//    loading(data, (char*)ui->lineEdit_oi->text().toStdString().c_str());
    loading(data, (char*)"/Users/gabriela/viewer/pl.obj");
    double array_3d[(data->sum_vertexes+1)*3];
    matrixToArray(data, array_3d);

    double color_cube[] = {0,0,0};

    glVertexPointer(3, GL_DOUBLE, 0, array_3d);
    glEnableClientState(GL_VERTEX_ARRAY);

    glColorPointer(3, GL_DOUBLE, 0, &color_cube);
    glEnableClientState(GL_COLOR_ARRAY);

//        glColor3d(0, 0, 1);
//        glDrawArrays(GL_QUADS, 0, 24);
        glDrawElements(GL_LINES, v*2, GL_UNSIGNED_INT, data->indexes_array);

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

