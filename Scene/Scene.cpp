//
// Created by 诸谦 on 15/12/27.
//

#include "Scene.h"
#include "../tracer/CommonTracer.h"
#include "../light/ambient.h"
#include "diffgeom.h"

unsigned long Scene::getLightNum() const {
  return mLights.size();
}

Reference<Light> Scene::ambient() const {
 return mAmbient;
}

Reference<Light> Scene::getLight(const int index)const {
    return mLights[index];
}

Scene::Scene():mAmbient(Reference<Light>(new Ambient())),background(RGB(0,0,0)),mTracer(new CommonTracer(*this)),mPrimitives(){

}

unsigned long Scene::getPrimitiveNum() const {
    return mPrimitives.size();
}

Reference<Shape> Scene::getPrimitive(int index) const{
    return mPrimitives[index];
}

ShadeRec Scene::hit(const Ray &ray) {
    ShadeRec sr(*this,ray);
    double t=999999;
    float dist=0;
    float e;
    Vector normal;
    Material* material;
    DifferentialGeometry dg;

    for(std::vector<Reference<Shape>>::iterator it = mPrimitives.begin(); it != mPrimitives.end(); it++)
    {
        if((*it)->hit(ray,&dist,&e,&dg,sr) && t>dist){
            t=dist;
            sr.hitAnObject=true;
            sr.hitPoint=ray.o+ray.d*t;
            normal=Vector(dg.nn);
            material=sr.material;
        }
    }

    if(sr.hitAnObject){
        sr.normal=normal;
        sr.distance=t;
        sr.material=material;
    }

    return (sr);
}

void Scene::addPrimitive(const Reference<Shape> primitive) {
    mPrimitives.push_back(primitive);
}

void Scene::addLight(const Reference<Light> light) {
    mLights.push_back(light);
}
