#include <MG_vecMath.h>




float vecDotProduct (vector<float> vector1,vector <float> vector2)
{
	float dotResult = ((vector1[0]*vector2[0])+(vector1[1]*vector2[1])+(vector1[2]*vector2[2]));


	return dotResult;
}


vector<float> makeVector (float vec[3])
{
	int x=0;
	vector<float> vecRet;
	for (x = 0; x <3; x++)
		vecRet.push_back(vec[x]);

	return vecRet;
} 
// procedures that calculates a vector leght

float vectorLength(vector<float> vec)
{
     /* for 3D just add + (z*z) and
     .. add z to the function */
     return sqrt((vec[0]*vec[0]) + (vec[1]*vec[1])+(vec[2]*vec[2]));
}



//procedure that normalizes a give vector
vector<float> normVector (vector<float> vecToN)
{
	vector<float> vecNorm;
	if (vectorLength (vecToN)!=0)
	{
	vecNorm.push_back(vecToN[0]/vectorLength(vecToN));
	vecNorm.push_back(vecToN[1]/vectorLength(vecToN));
	vecNorm.push_back(vecToN[2]/vectorLength(vecToN));
	}else{
	vecNorm.push_back(0);
	vecNorm.push_back(0);
	vecNorm.push_back(0);

	}



	return vecNorm;

}

//procedure that projects  a vector to another

float projVector (vector<float> vec1,vector<float> vec2)

{

		float proj; 
		float dot = vecDotProduct(vec1,vec2);
		float lenght = vectorLength(vec2);
		if (lenght!=0)
		{
		 proj = dot/lenght;
		}else{
		 proj=0;
		}


		return proj;
}

//procedure that multiplies a vector for a scalar 


vector<float> scalarVector (vector<float> vec , float scalar)
{
	vector<float> vecN;
	vecN.push_back(scalar*vec[0]);
	vecN.push_back(scalar*vec[1]);
	vecN.push_back(scalar*vec[2]);

	return vecN;
}  



//Procedure that calculates the angle inbetween two vectors 
float angleInbetweenVector (vector<float> vec1,vector<float> vec2)
{

	float angleDeg;
	if ((vectorLength(vec1)!=0 &&(vectorLength(vec2)!=0)))
	{
	float cosRad = (vecDotProduct(vec1,vec2)/(vectorLength(vec1)*vectorLength(vec2)));
	 angleDeg = acos (cosRad)*180/PI; 
	
	}else{
		angleDeg=0;
	}

	return angleDeg;
}

//Procedure tha sums two vectors

vector <float> vectorSum(vector<float> vec1,vector<float> vec2)

{
	vector<float> vectorSumResult;

	vectorSumResult.push_back(vec1[0]+vec2[0]);
	vectorSumResult.push_back(vec1[1]+vec2[1]);
	vectorSumResult.push_back(vec1[2]+vec2[2]);

	return vectorSumResult;
}



//procedures that project a vector to a given plane

vector<float> projectVectorOnPlane (vector<float> vec,vector<float> axis1,vector<float> axis2)

{
			float projAxis1;
			float projAxis2;
			vector <float> axis1Norm ;
			vector <float> axis2Norm ;
			vector <float> projAxis1Vec ;
			vector <float> projAxis2Vec ;
			vector <float> projectedVector ;



			projAxis1 = projVector(vec,axis1);
			projAxis2 = projVector(vec,axis2);
			
			axis1Norm = normVector(axis1);
			axis2Norm = normVector(axis2);

			projAxis1Vec =scalarVector(axis1Norm,projAxis1);
			projAxis2Vec =scalarVector(axis2Norm,projAxis2);


			projectedVector = vectorSum(projAxis1Vec,projAxis2Vec);

			return projectedVector;


}


vector <float> vectorCrossProduct(vector<float> vec1,vector<float> vec2)

{
	vector<float> crossResult;
	crossResult.push_back((vec1[1]*vec2[2])-(vec1[2]*vec2[1]));
	crossResult.push_back((vec1[2]*vec2[0])-(vec1[0]*vec2[2]));
	crossResult.push_back((vec1[0]*vec2[1])-(vec1[1]*vec2[0]));
	return crossResult;
}

vector <float> negativeVector(vector<float> vec1)


{
	vector<float> neg;
	neg.push_back(-vec1[0]);
	neg.push_back(-vec1[1]);
	neg.push_back(-vec1[2]);
	return neg;

}