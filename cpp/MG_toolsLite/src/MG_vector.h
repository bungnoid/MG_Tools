/** \brief lets you quickly create a vector
*/

/**
* @author Marco Giordano
* @date  --/--/2011
* @version latest version : V1
* @version changeload versions : \n
*			V1 : \n
*				- initial release \n				
*
*
* node name : MG_vector.
* 
* details : This node lets you quickly create a vector
*			This node from two matrices generates a vector and calculates its magnitude,
*			also provide an attribute to normalize the output vector if needed
*			
* example create node : (MEL) createNode MG_vector.
*
* @todo  convert the node to a locator and addoption to draw the vector
*
*		  
* 
*/

#ifndef MG_vector_H
#define MG_vector_H

#include <maya/MPxNode.h>


#include <maya/MGlobal.h>

#include <maya/MTypeId.h>


//Class

class MG_vector : public MPxNode
{
public:
		static void* creator();
 

		static MStatus initialize();
		virtual MStatus compute(const MPlug& plug,MDataBlock& dataBlock);


		//static const MString typeName;

public:
	/**
	* The first input matrix attribute
	*/
	static	MObject inputM1;
	/**
	* The second input matrix attribute
	*/
	static	MObject inputM2;
	/**
	* This attribute holds the length of the vector
	*/
	static	MObject magnitude;
	/**
	* The X component of the output vector attribute
	*/
	static	MObject oVecX;
	/**
	* The Y component of the output vector attribute
	*/
	static	MObject oVecY;
	/**
	* The Z component of the output vector attribute
	*/
	static	MObject oVecZ;
	/**
	* The output vector attribute
	*/
	static	MObject oVec;
	/**
	* This attribute if checked normalize the output vector
	*/
	static	MObject normalize;

	/**
	* The node id
	*/
	static MTypeId typeId;


		
};




#endif 