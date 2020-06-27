#ifndef GROUP_H
#define GROUP_H

#include "Object3D.h"
#include "Ray.h"
#include "Hit.h"
#include <iostream>

using namespace std;

/// TODO: Implement Group
class Group : public Object3D {
 public:
  Group() {
  }

  Group(int num_objects) {
    // Set space for storing the Object3D
    objects.resize(num_objects);
  }

  ~Group() {
  }

  // TODO
  virtual bool intersect(const Ray& r, Hit& h, float tmin) {
    // check if the ray intersect with one of the object
    bool check = false;
    for (Object3D* obj : objects) {
      if (obj != nullptr) {
        check |= obj->intersect(r, h, tmin);
        if (check) {
          break;
        }
      }
    }

    return check;
  }

  // TODO
  void addObject(int index, Object3D* obj) {
    // Add the Object3D pointer if the index within the range of the storage vector
    if (index >= 0 && index < objects.size()) {
      objects.at(index) = obj;
    }
  }

  int getGroupSize() {
    return (int)objects.size();
  }

 private:
  vector<Object3D*> objects;
};

#endif
