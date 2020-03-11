#include "Ball.h"

Ball::Ball(float step,
           float x,
           float y,
           float width,
           float height,
           GLuint textureID,
           GLuint programID,
           GLint positionAttr,
           GLint textureAttr,
           GLint transformationAttr,
           GLfloat * verticesCoords,
           GLfloat * textureCoords,
           GLfloat * matrixCoords,
           Splash * splash) : Object(step,
                                     x,
                                     y,
                                     width,
                                     height,
                                     textureID,
                                     programID,
                                     positionAttr,
                                     textureAttr,
                                     transformationAttr,
                                     verticesCoords,
                                     textureCoords,
                                     matrixCoords ),
                              m_pSplash(splash),
                              DX_MAX(0.06f),
                              DX_MIN(0.03),
                              INCREASE_SPEED_TO(height),
                              DELTA_SPEED(0.0001f),
                              DEFAULT_SPEED(step)
{
    LOGI("Ball::Ball()");
    setDy(Methods::getRandSign() * step);
    m_bIsOut = false;
    m_fSign = 1.0f;
    m_nSpeed = 0;
}

Ball::~Ball() {
    LOGI("Ball::~Ball()");
}


bool Ball::collision(Platform * object) {
    // Cross points
    std::vector<GLfloat> * crossPoint = getCrossPoints();

    setPreviousPoint();
    setQueuePointsForPlume();

    // It's intersect of two objects
    if (Intersect::intersectRect(object->getRectangle(), getRectangle(), crossPoint)) {
        increaseSpeed();
        float width = getWidth();
        float centerX = Line<GLfloat>::getCenter(crossPoint->at(0), crossPoint->at(2));
        float centerY = Methods::getMax(crossPoint->at(1), crossPoint->at(3));
        float shiftY = -1.0f * Intersect::getEps();

        if (getRectangle()->getCenter().y > 0) {
            width = -1.0f * width;
            m_fSign = -1.0f;
            centerY = Methods::getMin(crossPoint->at(1), crossPoint->at(3));
            shiftY += fabsf(*getRectangle()->up.y1) - fabsf(centerY);
        } else {
            shiftY += fabsf(*getRectangle()->down.y1) - fabsf(centerY);
            m_fSign = 1.0f;
        }

        switch(object->getRebound(centerX, centerY, width)) {
            case Platform::LAST_LEFT :
                m_fDY = -1.0f * m_fDY;
                m_fDX = -1.0f * m_fSign * DX_MAX;
                moveY(m_fSign * shiftY);
                LOGI("LAST_LEFT");
                break;
            case Platform::LEFT :
                m_fDY = -1.0f * m_fDY;
                m_fDX = -1.0f * m_fSign * DX_MIN;
                moveY(m_fSign * shiftY);
                LOGI("LEFT");
                break;
            case Platform::CENTER :
                m_fDY = -1.0f * m_fDY;
                m_fDX = 0.0f;
                moveY(m_fSign * shiftY);
                LOGI("CENTER");
                break;
            case Platform::RIGHT :
                m_fDY = -1.0f * m_fDY;
                m_fDX = m_fSign * DX_MIN;
                moveY(m_fSign * shiftY);
                LOGI("RIGHT");
                break;
            case Platform::LAST_RIGHT :
                m_fDY = -1.0f * m_fDY;
                m_fDX = m_fSign * DX_MAX;
                moveY(m_fSign * shiftY);
                LOGI("LAST_RIGHT");
                break;
            case Platform::NONE :
                break;
        }

        m_pSplash->setSplashPosition(centerX, centerY);
        crossPoint->clear();

        return true;
    }

    crossPoint->clear();
    return false;
}

Object::CROSS_SIDE Ball::collision(Object * object) {
    // It's occurs more
    Object::CROSS_SIDE cross_side = collisionLeftRightWall(object);
    if (cross_side != Object::NONE) {
        return cross_side;
    }

    // It's less
    cross_side = collisionUpDownWall(object);
    if (cross_side != Object::NONE) {
        return cross_side;
    }

    return Object::NONE;
}

Object::CROSS_SIDE Ball::collisionLeftRightWall(Object * object) {
    // Cross points
    std::vector<GLfloat> * crossPoint = getCrossPoints();

    // Left wall and up/down ball side
    if (Intersect::intersectSegments(&(object->getRectangle()->left), &(getRectangle()->up), crossPoint)) {
        if (Intersect::intersectSegments(&(object->getRectangle()->left), &(getRectangle()->down), crossPoint)) {
            if (crossPoint->size() >= 4) {
                m_fDX = -1.0f * m_fDX;
                move();
                return Object::LEFT;
            }
        }
    }

    crossPoint->clear();

    // Right wall and up/down ball side
    if (Intersect::intersectSegments(&(object->getRectangle()->right), &(getRectangle()->up), crossPoint)) {
        if (Intersect::intersectSegments(&(object->getRectangle()->right), &(getRectangle()->down), crossPoint)) {
            if (crossPoint->size() >= 4) {
                m_fDX = -1.0f * m_fDX;
                move();
                return Object::RIGHT;
            }
        }
    }

    crossPoint->clear();
    return Object::NONE;
}

Object::CROSS_SIDE Ball::collisionUpDownWall(Object * object) {
    // Cross points
    std::vector<GLfloat> * crossPoint = getCrossPoints();

    // Up wall and left/right ball side
    if (Intersect::intersectSegments(&object->getRectangle()->up, &getRectangle()->left, crossPoint)) {
        if (Intersect::intersectSegments(&object->getRectangle()->up, &getRectangle()->right, crossPoint)) {
            if (crossPoint->size() >= 4) {
                setDefaultPosition();
                m_fDX = 0.0f;
                m_bIsOut = true;
                return Object::UP;
            }
        }
    }

    crossPoint->clear();

    // Down wall and left/right ball side
    if (Intersect::intersectSegments(&object->getRectangle()->down, &getRectangle()->left, crossPoint)) {
        if (Intersect::intersectSegments(&object->getRectangle()->down, &getRectangle()->right, crossPoint)) {
            if (crossPoint->size() >= 4) {
                setDefaultPosition();
                m_fDX = 0.0f;
                m_bIsOut = true;
                return Object::DOWN;
            }
        }
    }

    crossPoint->clear();

    if (!Intersect::between(-1.0f, 1.0f, getRectangle()->getCenter().x) &&
        !Intersect::between(-1.0f, 1.0f, getRectangle()->getCenter().y))
    {
        setDefaultPosition();
        m_fDX = 0.0f;
        m_bIsOut = true;
        return Object::NONE;
    }

    return Object::NONE;
}

void Ball::increaseSpeed() {
    if (m_nSpeed < 100) {
    //if (fabsf(m_fDY) < INCREASE_SPEED_TO * 0.5f) {
        ++m_nSpeed;

        if (m_fDY > 0) {
            m_fDY += DELTA_SPEED * 0.8f;
        } else {
            m_fDY -= DELTA_SPEED * 0.8f;
        }
    }
}

void Ball::setPreviousPoint() {
    while(m_pLastPoint.size() > 2) {
        m_pLastPoint.pop();
    }

    // Save current points of center
    m_pLastPoint.push(getRectangle()->getCenter().x);
    m_pLastPoint.push(getRectangle()->getCenter().y);
}

void Ball::setQueuePointsForPlume() {
    while(m_pPlumePoints.size() > 40) {
        m_pPlumePoints.pop();
    }

    // Save current points of center
    m_pPlumePoints.push(getRectangle()->getCenter().x);
    m_pPlumePoints.push(getRectangle()->getCenter().y);
}
