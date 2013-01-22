#ifndef MG_crossProductUCT_H
#define MG_crossProductUCT_H

#include <maya/MPxNode.h>
#include <maya/MGlobal.h>
#include <maya/MTypeId.h>


//Class

class MG_crossProduct : public MPxNode
{
public:
		static void* creator();
 

		static MStatus initialize();
		virtual MStatus compute(const MPlug& plug,MDataBlock& dataBlock);


		//static const MString typeName;

public:
     static MObject vector1;
     static MObject vector2;
     static MObject normalize;
     static MObject crossProductA;
     static MObject reverse;
     static MObject parallelogramA;
     static MObject triangleA;
 



	static MTypeId typeId;


		
};




#endif 