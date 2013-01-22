#ifndef MG_dotProductUCT_H
#define MG_dotProductUCT_H

#include <maya/MPxNode.h>
#include <maya/MGlobal.h>
#include <maya/MTypeId.h>


//Class

class MG_dotProduct : public MPxNode
{
public:
		static void* creator();
 

		static MStatus initialize();
		virtual MStatus compute(const MPlug& plug,MDataBlock& dataBlock);


		//static const MString typeName;

public:
	static MObject vector1;
	static MObject vector2;
	static MObject dotProductA;
	static MObject normalize;
	static MObject dotProductMax;
	static MObject proj1on2;
	static MObject proj2on1;
	static MObject angleInBetweenAttr;
	static MObject angleX;
	static MObject angleY;
	static MObject angleZ;
	static MObject projAxisX;
	static MObject projAxisXa;
	static MObject projAxisXb;
	static MObject projAxisXc;
	static MObject projAxisY;
	static MObject projAxisYa;
	static MObject projAxisYb;
	static MObject projAxisYc;
	static MObject projAxisZ;
	static MObject projAxisZa;
	static MObject projAxisZb;
	static MObject projAxisZc;
 



	static MTypeId typeId;


		
};




#endif 