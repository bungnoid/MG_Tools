/** \brief lets build a fast and flexible spine
*/

/**
* @author Marco Giordano
* @date  02/10/2013
* @version latest version : V1
* @version changeload versions : \n
*			V1 : \n
*				- initial release \n				
*
*
* node name : MG_pathSpine.
* 
* details : This node lets build a fast and flexible spine with a lot of features like 
*			hardcore twisting , squash and stretch and more.
*			NB : this nodes have as output severl arrays (translate ,rotate and scale),
*			maya is really picky about arrays , if you try to acces an index that is not there
*			well your going to crash.
*			In order to avoid that be sure that the value of the attribute "number of outputs"
*			is equal at the number of index in all output array , even if you dont conncet them create
*			the index , otherwise the compute wont start.
*			Example if you have number of outputs : 20 you will need to have as last index for example 
*			outputTranslate[19] , (array index count starts from 0 ).
*			In order to create index if you dont have to connect them you can simply use a getAttr command on the
*			indexes.
*			Also be sure to set the start length value of the curve.
*			I really hope someone from the community will provide scripts to hook up the node ,
*			I did it for myself but it s based on my pipeline I am currently developing so I can't share.
*
*			
* example create node : (MEL) createNode MG_pathSpine.
*
*
*
*		  
* 
*/

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

class MG_pathSpine : public MPxNode 

{

   public:


      static void *creator();
      static MStatus initialize();
      virtual MStatus compute(const MPlug &plug, MDataBlock &data);
	  /**
		* The node id
		*/
      static MTypeId typeId;
      /**
		* This is the input curve value 
		*/
      static MObject inputCurve;
	  /**
		* This attribute holds the first up vector used to compute the normals on the curve
		*/
      static MObject firstUpVec;
	  /**
		* This attribute holds the X component of the first up vector used to compute the normals on the curve
		*/
      static MObject firstUpVecX;
	  /**
		* This attribute holds the Y component of the first up vector used to compute the normals on the curve
		*/
      static MObject firstUpVecY;
	  /**
		* This attribute holds the Z component of the first up vector used to compute the normals on the curve
		*/
      static MObject firstUpVecZ;
	  
	  /**
		* This is the X component of the output translate array
		*/
      static MObject outputTranslateX;
	  /**
		* This is the Y component of the output translate array
		*/
      static MObject outputTranslateY;
	  /**
		* This is the Z component of the output translate array
		*/
      static MObject outputTranslateZ;
	  /**
		* This is the output translate array
		*/
      static MObject outputTranslate;
	  /**
		* This is the X component of the output Rotate array
		*/
      static MObject outputRotateX;
	  /**
		* This is the Y component of the output Rotate array
		*/
      static MObject outputRotateY;
	  /**
		* This is the Z component of the output Rotate array
		*/
      static MObject outputRotateZ;
	  /**
		* This is the output Rotate array
		*/
      static MObject outputRotate;

	  	  /**
		* This is the X component of the output Scale array
		*/
      static MObject outputScaleX;
	  /**
		* This is the Y component of the output Scale array
		*/
      static MObject outputScaleY;
	  /**
		* This is the Z component of the output Scale array
		*/
      static MObject outputScaleZ;
	  /**
		* This is the output Scale array
		*/
      static MObject outputScale;
	  /**
		*This value sets how many samples are going to be done on the curve , the higher it is the more accurate 
		*is the computation , of course with drops on performance , set a value that gives you the wanted result
		* it has to be higher then then number of outputs , I usually keep it twice the number of outut
		*/
      static MObject numberOfSamples;
	  /**
		* This attribute sets how many outputs will be computed
		*/
      static MObject numberOfOutput;
	  /**
		* This attribute will hold the curve's transform world matrix
		*/
      static MObject parentMatrix;
	  /**
		* This is the starth length of the curve and needs to be set manually 
		*/
      static MObject startLength;
	  /**
		* This attribute the amount of stretch along the curve
		*/
      static MObject stretch;
	  /**
		* This is the input twist 1
		*/
      static MObject twist1;
	  /**
		* This is the input twist 2
		*/
      static MObject twist2;
	  /**
		* This attribute is used to define the shape of the stretched spine
		*/
      static MObject stretchShape;
	  /**
		* This attribute is used to define the shape of the squashed spine
		*/
      static MObject squashShape;
	  /**
		* This attribute is used to multiply the value defined by the stretchShape
		*/
      static MObject stretchMult;
	  /**
		* This attribute is used to multiply the value defined by the squashShape
		*/
      static MObject squashMult;
	  /**
		* This attribute define if to keep volume during twist or not
		*/
      static MObject keepTwistVolume;
	  /**
		* This attribute is used to multiply the keepTwistVolume amount
		*/
      static MObject keepTwistVolumeMult;
	  /**
		* This attribute is used to define the shape of the twisted spine
		*/
      static MObject twistShape;
	  /**
		* This attribute turns on/off the computation of the twist
		*/
	  static MObject computeTwist;
	  /**
		* This attribute turns on/off the computation of the stretch volume
		*/
	  static MObject computeVolumeStretch;
	  /**
		* This attribute turns on/off the computation of the squash volume
		*/
	  static MObject computeVolumeSquash;
	  
	  /**
		* THis attribute is used to fix global scale of the spine
		*/
	  static MObject globalScale;
      
private :
	MQuaternion vecToRotQuat(MVector vec);
  
};

