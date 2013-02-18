/** \brief let s you draw an array of vectors in maya viewport

/**
* @author Marco Giordano
* @date  02/11/2013
* @version latest version : V1
* @version changeload versions : \n
*			V1 : \n
*				- initial release \n				
*
*
* node name : MG_vectorGL.
* 
* details : This nodelet s you draw an array of vectors in maya viewport.
*			This node is used for debugging purpose , connect in the vecs attribute
*			all the vectors you want to draw and in the startPoits array all the 
*			base positions for the vectors, connect the fake out attribute
*			to something in order to force the compute
*			
* example create node : (MEL) createNode MG_vectorGL.
*
* 
*		  
* 
*/

#ifndef MG_vectorGL_H
#define MG_vectorGL_H



#include <maya/MTypeId.h>
#include <maya/MPxLocatorNode.h>




class MG_vectorGL : public MPxLocatorNode
{
public:

	virtual MStatus		compute( const MPlug& plug, MDataBlock& data );

    virtual void draw( M3dView&,
						const MDagPath&,
						M3dView::DisplayStyle,
						M3dView::DisplayStatus);

    virtual bool	isBounded() const;

	static  void*		creator();
	static  MStatus		initialize();
	/**
	* The node id
	*/
	static	MTypeId		typeId;

public:
	/**
	* The X component of the upVec used to draw the arrows
	*/
  	static MObject upVecX ;
	/**
	* The Y component of the upVec used to draw the arrows
	*/
	static MObject upVecY ;
	/**
	* The Z component of the upVec used to draw the arrows
	*/
	static MObject upVecZ ;
	/**
	* The  upVec used to draw the arrows
	*/
	static MObject upVec ;
	/**
	* The X component of the start point used to draw the vecs
	*/
	static MObject startPointX ;
	/**
	* The Y component of the start point used to draw the vecs
	*/
	static MObject startPointY ;
	/**
	* The Z component of the start point used to draw the vecs
	*/
	static MObject startPointZ ;
	/**
	* The the start point used to draw the vecs
	*/
	static MObject startPoint ;
	/**
	* The fake attribute used to force the compute to evaluate
	*/
	static MObject fakeOut ;
	/**
	* The X component of the  vecs
	*/
	static MObject vecX;
	/**
	* The Y component of the  vecs
	*/
	static MObject vecY;
	/**
	* The Z component of the  vecs
	*/
	static MObject vecZ;
	/**
	* The  the  vecs attribute
	*/
	static MObject vecs ;
	/**
	* This attribute sets whether or not to draw the arrows
	*/
	static MObject drawIt;
	/**
	* This attribute sets the arrow size
	*/
	static MObject arrowSize;


	



	

private:
	
	void drawArrow ( const MVector vec = MVector(1,0,0) ,
			 const MVector upVec = MVector(0,1,0),
			 const double arrowSizeV = 1 ,  const 
			 MPoint startPointV = MPoint(0,0,0));


};

#endif
