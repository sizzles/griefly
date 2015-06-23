#ifndef QTOPENGL_H
#define QTOPENGL_H

#include <QGLWidget>

class QtOpenGL : public QGLWidget
{
    Q_OBJECT
public:
    explicit QtOpenGL(QWidget *parent = 0);
    ~QtOpenGL();

signals:

public slots:
protected:
    void mousePressEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent* event);

    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
};

QtOpenGL* GetGLWidget();
void MakeCurrentGLContext();
void SetGLContext(QtOpenGL* widget);

#endif // QTOPENGL_H