/** \brief let s you perform cross product and related operations
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
* node name : MG_crossProduct.
* 
* details : This node let s you perform crost product and related operations
*			This nodes needs as input two vectors and then in output you get
*			several value and data you can use.
*			Available output attribute :
*			- vector1 : first vector input
*			- vector2 : second vector input
*			- normalize : lets you normalize the crossed vector
*			- reverse : lets you reverse the crossed vector
*			- parallelogram area : this is the area of the paralleogram built with the two vectors
*			- triangle area : this is the areao of the triangle built from the two vectors

* example create node : (MEL) createNode MG_crossProduct.
*
* 
*
*		  
*/

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