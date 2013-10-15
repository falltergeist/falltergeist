#ifndef FALLTERGEIST_CAMERA_H
#define FALLTERGEIST_CAMERA_H

class Camera
{
protected:
    unsigned int _x;
    unsigned int _y;
public:
    Camera(unsigned int width, unsigned int height, unsigned int x, unsigned int y);
    ~Camera();

    unsigned int x();
    void setX(unsigned int x);

    unsigned int y();
    void setY(unsigned int y);
};

#endif // FALLTERGEIST_CAMERA_H
