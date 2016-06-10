//
// Created by 诸谦 on 15/12/27.
//

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H
#include <memory>
#include <vector>
#include "../light/Ambient.h"
#include "Shape.h"
#include "../tracer/Tracer.h"

using namespace std;
class Scene {
private:
    Light* mAmbient;//环境光
    vector<Light*> mLights;
    vector<Shape *> mPrimitives;
    Tracer* mTracer;
public:

    Scene();
    unsigned long getLightNum() const;
    Light* ambient() const;
    Light* getLight(const int index) const;

    unsigned long getPrimitiveNum() const;
    Shape * getPrimitive(int index) const;

    void addPrimitive(Shape *);
    void addLight(Light* light);

    virtual ShadeRec hit(const Ray& ray);

    RGB background;

    const Tracer* getTracer() const;
    void setTracer(Tracer*);
};


#endif //RAYTRACER_SCENE_H