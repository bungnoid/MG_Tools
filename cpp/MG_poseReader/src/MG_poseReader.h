#ifndef MG_poseReader_H
#define MG_poseReader_H



#include <maya/MTypeId.h>
#include <maya/MPxLocatorNode.h>




// --------------------------------------------------------------------------

/*
 * MG_poseReader - Class definition for main pose calc node
 */
class MG_poseReader : public MPxLocatorNode
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
	// Input Attrs

	static MObject readerMatrix;
	static MObject poseMatrix;
	static MObject size;
	static MObject aimAxis;

	static MObject readerOnOff;
	static MObject axisOnOff;
	static MObject poseOnOff;
	static MObject xPositive;
	static MObject xNegative;
	static MObject yPositive;
	static MObject yNegative;
	static MObject zPositive;
	static MObject zNegative;






	

private:
	
	void drawSphere(const double r, const int lats, const int longs,const MVector position,const double* color);
	void drawArrow (const int aimAxis,const double arrowSizeV);
	void drawArrowMatrix(const int aimAxis,const double arrowSizeV,const MMatrix poseM ,const MMatrix readerM);
	void drawCone (const int coneAxis,const double coneSize,const double angle,const bool targetBalls,const double targetBallSizeV,
		const double off1,const double off2,const double  off3,const double off4,
		const double par1,const double par2,const double par3,const double par4,const bool &numbers,M3dView &view);
	double* blendColor(const double& red,const double& green,const double& blue,const double &alpha );
	void drawText(const MString &text,const double* color, const MPoint &position,M3dView &view);
	
	MMatrix fromVecToMatrix(const MVector vec);
	MVector fromMatrixToVector(const MMatrix mat);
	MVector rotateVector( const int rotateAxis, const MVector vecToRotate, const double angle);
	MVector matrixToAxisMatrix (const int &aimAxis , const MMatrix &matrix,const int normalize);
	double angleToPar(const double &angle, const double &maxAngle,const double &centerAngle);

	MObject makePlane(const MVector& p1,const MVector& p2,const MVector& p3);
	double projVector (MVector vec1,MVector vec2);


};

#endif

// --------------------------------------------------------------------------
