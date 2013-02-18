/** \brief Jiggle motion along vector direction
*/

/**
* @author Marco Giordano
* @date  11/15/2012
* @version latest version : V1
* @version changeload versions : \n
*			V1 : \n
*				- initial release \n								

* node name : MG_jiggleVector.
* 
* details : Jiggle motion along vector direction
*			This node needs the matrix of the target you want to generate the jiggle from
*			and also needs the time node to be connected (usually this node is the time1).
*			With this set you are good to go just connect the output to the translation of 
*			the target node.
*			Use the parameters to se the nodes
*			

* example create node : (MEL) createNode MG_jiggleVector.
* 
*/
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
	/**
	* The node id 
	*/
	static MTypeId typeId;
	/**
	* The output attribute
	*/
	static MObject output;
	/**
	* The output  X for the compound attribute output
	*/
	static MObject outputX;
	/**
	* The output  Y for the compound attribute output
	*/
	static MObject outputY;
	/**
	* The output  Z for the compound attribute output
	*/
	static MObject outputZ;	
	/**
	* This attribute sets how much motion is getting lost 
	*/
	static MObject damping;
	/**
	* This is the vector along you want to jiggle
	*/
	static MObject targetVector ;
	/**
	* The X component of the vector you want to perform the jiggle on
	*/
	static MObject targetVectorX ;
	/**
	* The Y component of the vector you want to perform the jiggle on
	*/
	static MObject targetVectorY ;
	/**
	* The Z component of the vector you want to perform the jiggle on
	*/
	static MObject targetVectorZ ;
	/**
	* This attribute sets how much attraction the source of the juggle apply
	*/
	static MObject stiffness;
	/**
	* Connect to this attribute the maya time or another source of time 
	*/
	static MObject time;
	/**
	* This is the source matrix from which the jiggle is generated from
	*/
	static MObject targetMatrix;
	/**
	* This attribute define if to use or not the start frame to reset the simulation
	*/
	static MObject useStartFrame ;
	/**
	* If useStartFrame attribute is checked then this attribute define which frame is the start frame
	*/
	static MObject  startFrame ;
	/**
	* Reset the jiggle 
	*/
	static MObject reset;
	/**
	* If clamp range is activated this attribute define the max of the range
	*/
	static MObject clampMax;
	/**
	* If clamp range is activated this attribute define the min of the range
	*/
	static MObject clampMin;
	/**
	* This attribute sets the amount of offset to apply to the jiggle
	*/
	static MObject offset;
	/**
	* This is the start position for jiggle
	*/
	static MObject startPosition;
	/**
	* This is X component of  the start position for  jiggle
	*/
	static MObject startPositionX;
	/**
	* This is Y component of  the start position for  jiggle
	*/
	static MObject startPositionY;
	/**
	* This is Z component of  the start position for  jiggle
	*/
	static MObject startPositionZ;
	/**
	* This attribute defines whether to clamp the jiggle or not 
	*/
	static MObject clampRange ;
	/**
	* If the attribute is checked the jiggle will be local to the source of the jiggle
	*/
	static MObject useLocalOutput ;
	/**
	* If checked this attribute scales the jiggle based on the source scale
	*/
	static MObject scaleFix ;


private :
	double smoothSthep (double a , double b , double t);


};




#endif 