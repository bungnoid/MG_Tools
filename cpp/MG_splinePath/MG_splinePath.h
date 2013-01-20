#include <maya/MPxNode.h>
#include <maya/MTypeId.h>
#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MDagPath.h>
#include <maya/MPlug.h>
#include <maya/MPoint.h>
#include <maya/MVector.h>

class MG_splinePath : public MPxNode

{

   public:


      static void *creator();
      static MStatus initialize();
      virtual MStatus compute(const MPlug &plug, MDataBlock &data);
      static MTypeId typeId;
      
      static MObject inputCurve;
      static MObject firstUpVec;
      static MObject firstUpVecX;
      static MObject firstUpVecY;
      static MObject firstUpVecZ;
      static MObject outputTranslateX;
      static MObject outputTranslateY;
      static MObject outputTranslateZ;
      static MObject outputTranslate;
      static MObject outputRotateX;
      static MObject outputRotateY;
      static MObject outputRotateZ;
      static MObject outputRotate;
      static MObject numberOfSamples;
      static MObject numberOfOutput;
      static MObject parentMatrix;
      static MObject offset;
      
      static MObject tangentsAttrX;
      static MObject tangentsAttrY;
      static MObject tangentsAttrZ;
      static MObject tangentsAttr;
      
      static MObject tangentsPosX;
      static MObject tangentsPosY;
      static MObject tangentsPosZ;
      static MObject tangentsPos;
};

