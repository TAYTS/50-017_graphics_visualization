#ifndef GROUP_H
#define GROUP_H


#include "Object3D.h"
#include "Ray.h"
#include "Hit.h"
#include <iostream>

using  namespace std;


/// TODO: Implement Group
class Group:public Object3D
{
public:

  Group(){

  }
	
  Group( int num_objects ){
     
  }

  ~Group(){
   
  }

  // TODO
  virtual bool intersect( const Ray& r , Hit& h , float tmin ) {
    
   }
	
  // TODO
  void addObject( int index , Object3D* obj ){

  }

  int getGroupSize(){ 
      return (int)objects.size();
  }

 private:
 
    vector<Object3D*> objects;
};

#endif
	
