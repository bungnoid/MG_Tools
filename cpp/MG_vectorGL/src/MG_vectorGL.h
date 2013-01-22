#ifndef MG_vectorGL_H
#define MG_vectorGL_H



#include <maya/MTypeId.h>
#include <maya/MPxLocatorNode.h>




// --------------------------------------------------------------------------

/*
 * MG_vectorGL - Class definition for main pose calc node
 */
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

	static	MTypeId		typeId;

public:
  	static MObject upVecX ;
	static MObject upVecY ;
	static MObject upVecZ ;
	static MObject upVec ;
	static MObject startPointX ;
	static MObject startPointY ;
	static MObject startPointZ ;
	static MObject startPoint ;
	static MObject fakeOut ;
	static MObject vecX;
	static MObject vecY;
	static MObject vecZ;
	static MObject vecs ;
	static MObject drawIt;
	static MObject arrowSize;


	



	

private:
	
	void drawArrow ( const MVector vec = MVector(1,0,0) ,
			 const MVector upVec = MVector(0,1,0),
			 const double arrowSizeV = 1 ,  const 
			 MPoint startPointV = MPoint(0,0,0));


};

#endif

// --------------------------------------------------------------------------
