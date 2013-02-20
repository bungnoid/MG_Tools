/** \brief This node let s you read a position based on a sperichal area
*/

/**
* @author Marco Giordano
* @date  10/26/2012
* @version latest version : V1
* @version changeload versions : \n
*			V1 : \n
*				- initial release \n				
*
*
* node name : MG_poseReader.
* 
* details : This node let s you read a position based on a sperichal area ,
*			perfect to trigger blendshapes or rig an autovlavicle and so on.
*			Actually the autoclavicle rig was the reason why I wanted to 
*			create this plugin.
*			This node needs the world space matrix of the poseReader itself to be 
*			connected to the readerMatrix attribute.
*			Beware that the poseReader itself is a shape so you need to plug the 
*			relative transform world matrix.
*			Then you have to connect the world matrix of the object you want to read the pose
*			and also set what axis you want to take in consideration of this object.
*			In the end you have just to plug the data you want to read , possible targets are 
*			- +x
*			- -x
*			- +y
*			- -y
*			- +z
*			- -z
*			
* example create node : (MEL) createNode MG_poseReader.
*
* @todo  implement torque reading
*
*		  
* 
*/


#ifndef MG_poseReader_H
#define MG_poseReader_H



#include <maya/MTypeId.h>
#include <maya/MPxLocatorNode.h>





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
	/**
	* The node id
	*/
	static	MTypeId		typeId;

public:
	// Input Attrs

	/**
	*The world matrix of the poseReader
	*/
	static MObject readerMatrix;
	/**
	* The matrix of the object we want to read the pose
	*/
	static MObject poseMatrix;
	/**
	* The size of the poseReader
	*/
	static MObject size;
	/**
	* Which axis to read of the  object 
	*/
	static MObject aimAxis;
	/**
	* This attribute sets if the reader is visible in viewport or not
	*/
	static MObject readerOnOff;
	/**
	* This attribute sets if the axis targets are  visible in viewport or not
	*/
	static MObject axisOnOff;
	/**
	* This attribute sets if the pose target is visible in viewport or not
	*/
	static MObject poseOnOff;
	/**
	* the positive x value of the pose
	*/

	static MObject xPositive;
	/**
	* the negative x value of the pose
	*/
	static MObject xNegative;
	/**
	* the positive y value of the pose
	*/
	static MObject yPositive;
	/**
	* the negative y value of the pose
	*/
	static MObject yNegative;
	/**
	* the positive y value of the pose
	*/
	static MObject zPositive;
	/**
	* the negative z value of the pose
	*/
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
