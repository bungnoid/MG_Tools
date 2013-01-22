#ifndef MG_jiggleVector_H
#define MG_jiggleVector_H

#include <maya/MPxNode.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnStringData.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MSelectionList.h>
#include <maya/MDagPath.h>
#include <maya/MGlobal.h>
#include <maya/MFnGenericAttribute.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MFnCompoundAttribute.h>
#include <maya/MTypeId.h>
#include <maya/MPoint.h>

//Class

class MG_jiggleVector : public MPxNode
{
public:
		static void* creator();
 
		MG_jiggleVector();
		static MStatus initialize();
		virtual MStatus compute(const MPlug& plug,MDataBlock& dataBlock);
		bool init;
		double timeStored;
		MPoint currentPos ;
		MPoint previousPos ;


public:

	static MTypeId typeId;
	static MObject output;
	static MObject outputX;
	static MObject outputY;
	static MObject outputZ;
	static MObject damping;
	static MObject targetVector ;
	static MObject targetVectorX ;
	static MObject targetVectorY ;
	static MObject targetVectorZ ;
	static MObject stiffness;
	static MObject time;
	static MObject targetMatrix;
	static MObject useStartFrame ;
	static MObject  startFrame ;
	static MObject reset;
	static MObject clampMax;
	static MObject clampMin;
	static MObject offset;
	static MObject startPosition;
	static MObject startPositionX;
	static MObject startPositionY;
	static MObject startPositionZ;
	static MObject clampRange ;
	static MObject useLocalOutput ;
	static MObject scaleFix ;


private :
	double smoothSthep (double a , double b , double t);


};




#endif 