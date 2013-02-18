/** \brief let s you perform some trigonometry operations
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
* node name : rivetNode.
* 
* details : This node let s you perform various trigonometry operations
			Just need to plug the input value and chose which operation 
			to do.
*			
* example create node : (MEL) createNode MG_trigonometry.
*
*
*		  
* 
*/
#ifndef MG_trigonometry_H
#define MG_trigonometry_H



#include <maya/MTypeId.h>
#include <maya/MPxNode.h>





class MG_trigonometry : public MPxNode
{
public:
	
	 
	virtual MStatus		compute( const MPlug& plug, MDataBlock& data );


    

	static  void*		creator();
	static  MStatus		initialize();
	/**
	* The node id
	*/
	static	MTypeId		typeId;

public:
	// Input Attrs

	/**
	*  This is the input value 
	*/
	static MObject input;
	/**
	* This attribute sets the operation to perform
	*/
	static MObject mathOperation;
	/**
	* This attribute sets if to perform the inverse operation of the one set in the mathOperation attribute
	*/
	static MObject inverseFunction;
	/**
	* This is the output attribute holding the computed data
	*/
	static MObject outputValue;
	



	
};

#endif

