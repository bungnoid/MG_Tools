/** \brief lets you attach object on a curve and slide them
*/

/**
* @author Marco Giordano
* @date  2/15/2013
* @version latest version : V1
* @version changeload versions : \n
*			V1 : \n
*				- initial release \n				
*
*
* node name : MG_splinePath.
* 
* details : This node lets you attach object on a curve and slide them
*			This node is used to safely compute normals along a curve
*			and then attach object to it and let it slide , this node 
*			was initially built to rig a bike chain.
*			This node needs a nurbs curve shape connected to the inputCurve
*			attribute.
*			You need to set the nuber of samples that will be taken along the 
*			curve , they have to be more then the number of outputs.
*			The number of outputs in the array attributes : outputTranslate ,
*			outputRotate   must match the numberOfOutputs attribute.
*			Is suggest you to create those array index by connecting the tartgets 
*			or using get attribute command on the indexes.
*			The outputs are calculated locally , if you want to move them with the curve
*			connect the curve world matrix in the parentMatrix attribute.
*			In the end the firstUpVec attribute sets a vector used as first normal for computing
*			the orient.
*			
* example create node : (MEL) createNode MG_splinePath.
*
* @todo  add different distribuition mode of the objects on the curve
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

class MG_splinePath : public MPxNode

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
	  * The curve we want to attach objects on
	  */
      static MObject inputCurve;
	  /**
	  * The X  first up vector used to calculated the first normal
	  */
      static MObject firstUpVec;
	   /**
	  * The X component of the  first up vector used to calculated the first normal
	  */
      static MObject firstUpVecX;
	  /**
	  * The Y component of the  first up vector used to calculated the first normal
	  */
      static MObject firstUpVecY;
	  /**
	  * The Z component of the  first up vector used to calculated the first normal
	  */
      static MObject firstUpVecZ;
	  /**
	  * The X  compound array component  of positions of the objects
	  */
      static MObject outputTranslateX;
	  /**
	  * The Y  compound array component  of positions of the objects
	  */
      static MObject outputTranslateY;
	  /**
	  * The Z compound array component  of positions of the objects
	  */
      static MObject outputTranslateZ;
	  /**
	  * The compoun array of positions of the objects
	  */
      static MObject outputTranslate;
	  /**
	  * The X  compound array component  of orientation  of the objects
	  */
      static MObject outputRotateX;
	  /**
	  * The Y  compound array component  of orientation  of the objects
	  */
      static MObject outputRotateY;
	  /**
	  * The Z  compound array component  of orientation  of the objects
	  */
      static MObject outputRotateZ;
	  /**
	  * The   compound array  orientation  of the objects
	  */
      static MObject outputRotate;
	  /**
	  * The attribute holding the number of samples 
	  */
      static MObject numberOfSamples;
	   /**
	  * The attribute holding the number of output 
	  */
      static MObject numberOfOutput;
	  /**
	  * The attribute holding the world matrix of the curve
	  */
      static MObject parentMatrix;
	   /**
	  * The attribute holding the offest which lets the objects slide
	  */
      static MObject offset;
      
    
};

