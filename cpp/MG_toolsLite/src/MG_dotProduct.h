/** \brief let s you perform dot product and related operations
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
* node name : MG_dotProduct.
* 
* details : let s you perform dot product and related operations
*			This nodes needs as input two vectors and then in output you get
*			several value and data you can use.
*			Available output attribute :
*			- angleInbetween : the angle between the two vectors
*			- angle X : the extracted angle x between the two vectors
*			- angle Y : the extracted angle y between the two vectors			
*			- angle Z : the extracted angle z between the two vectors
*			- dotProduct : the dot product of the two vectors
*			- dotProductMaxValue : this attribute holds the max possible value for the dot product
*			- normalize : this attribute lets you normalize the vectors and result of the operantions
*			- projectionV1onV2 : this is the value of the projection of V1 on V2
*			- projectionV2onV1 : this is the value of the projection of V2 on V1 
*			- xAxisProjection : default 1,0,0 change this value if you want project the vectors and angles in an not ortogonal world (advanced use only)
*			- yAxisProjection : default 0,1,0 change this value if you want project the vectors and angles in an not ortogonal world (advanced use only)
*			- zAxisProjection : default 0,0,1 change this value if you want project the vectors and angles in an not ortogonal world (advanced use only)
* example create node : (MEL) createNode MG_dotProduct.
*
* 
*
*		  
*/

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