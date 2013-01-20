#ifndef MG_trigonometry_H
#define MG_trigonometry_H



#include <maya/MTypeId.h>
#include <maya/MPxNode.h>




// --------------------------------------------------------------------------

/*
 * poseReader - Class definition for main pose calc node
 */
class MG_trigonometry : public MPxNode
{
public:
	
	 
	virtual MStatus		compute( const MPlug& plug, MDataBlock& data );


    

	static  void*		creator();
	static  MStatus		initialize();

	static	MTypeId		typeId;

public:
	// Input Attrs

	static MObject input;
	static MObject mathOperation;
	static MObject inverseA;
	static MObject outputValue;
	



	
};

#endif

// --------------------------------------------------------------------------
