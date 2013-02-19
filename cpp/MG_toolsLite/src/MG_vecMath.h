#ifndef VECMATH_H
#define VECMATH_H
#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#define PI 3.14159265
using namespace std;



// I bet my penny that out there on the net there are already class and methods about vectors 
// but using them wouldndt have helped my learning process so i decided to write myself 
// the needed vector procedures 



// Procedure for calculating dot product value of two vectord 

float vecDotProduct (vector<float> vector1,vector <float> vector2);


//Procedure for quickly converting an array into a vector  use only with 3D vector

vector<float> makeVector (float vec[3]);


// procedures that calculates a vector leght

float vectorLength(vector<float> vec);




//procedure that normalizes a give vector
vector<float> normVector (vector<float> vecToN);




//procedure that projects  a vector to another

float projVector (vector<float> vec1,vector<float> vec2);



//procedure that multiplies a vector for a scalar 


vector<float> scalarVector (vector<float> vec , float scalar);

//Procedure that calculates the angle inbetween two vectors 
float angleInbetweenVector (vector<float> vec1,vector<float> vec2);
//Procedure tha sums two vectors

vector <float> vectorSum(vector<float> vec1,vector<float> vec2);



//procedures that project a vector to a given plane

vector<float> projectVectorOnPlane (vector<float> vec,vector<float> axis1,vector<float> axis2);


vector <float> vectorCrossProduct(vector<float> vec1,vector<float> vec2);
vector <float> negativeVector(vector<float> vec1);


#endif