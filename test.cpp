// test.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <math.h>

using namespace std;

struct Direction{
	double x, y, z;
	bool is3D;

	Direction(){
		x = 0;
		y = 0;
		z = 0;
		is3D = false;
	}
};

struct CartesianPoint{
	double x, y, z;
	string cubeindex;
	bool is3D;

	CartesianPoint(){
		x = 0;
		y = 0;
		z = 0;
		cubeindex = "";
		is3D = false;
	}
};

struct Axis2Placement3D{
	CartesianPoint *originalPoint;
	Direction *Directions1;
	Direction *Directions2;

	Axis2Placement3D(){
		originalPoint = new CartesianPoint();
		Directions1 = new Direction();
		Directions2 = new Direction();
	}
};

struct Axis2Placement2D{
	Direction *direction1;
	Direction *direction2;
	CartesianPoint *point;

	Axis2Placement2D(){
		point = new CartesianPoint();
		direction1 = new Direction();
		direction2 = new Direction();
	}
};

struct LocalPlacement{
	CartesianPoint *originalPoint;
	Direction *Directions1;
	Direction *Directions2;

	LocalPlacement(){
		originalPoint = new CartesianPoint();
		Directions1 = new Direction;
		Directions2 = new Direction;
	}
};

struct PolyLine{
	vector<CartesianPoint *> Points;

	PolyLine(){
		Points.empty();
	}
};

struct PolyLoop{
	vector<CartesianPoint *> Points;
	string cubeindex;

	PolyLoop(){
		Points.empty();
		cubeindex = "";
	}
};

struct ArbitaryClosedProfile{
	PolyLine *pLine;

	ArbitaryClosedProfile(){
		pLine = new PolyLine();
	}
};

struct RectangleProfile{
	Axis2Placement2D *axis;
	double xDim;
	double yDim;
	CartesianPoint *P1;
	CartesianPoint *P2;
	CartesianPoint *P3;
	CartesianPoint *P4;

	RectangleProfile(){
		axis = new Axis2Placement2D();
		xDim = 0.0;
		yDim = 0.0;
		P1 = new CartesianPoint();
		P2 = new CartesianPoint();
		P3 = new CartesianPoint();
		P4 = new CartesianPoint();
	}
};

struct CircleProfile{
	Axis2Placement2D *axis;
	double rad;
	CartesianPoint *t;
	CartesianPoint *b;
	CartesianPoint *l;
	CartesianPoint *r;

	CircleProfile(){
		axis = new Axis2Placement2D();
		rad = 0.0;
		t = new CartesianPoint();
		b = new CartesianPoint();
		l = new CartesianPoint();
		r = new CartesianPoint();
	}
};


/*IFCARBITRARYPROFILEDEFWITHVOIDS
struct ArbitaryVoidProfile{

};
*/

struct FaceBound{
	PolyLoop *Loop;
	string cubeindex;

	FaceBound(){
		Loop = new PolyLoop();
		cubeindex = "";
	}
};

struct FaceOuterBound{
	PolyLoop *Loop;
	string cubeindex;

	FaceOuterBound(){
		Loop = new PolyLoop();
		cubeindex = "";
	}
};

struct Face{
	int FaceMod;			// 0 is FaceOuterBound, 1 is FaceBound + FaceOuterBound, 9 is unincluded Model
	FaceBound * Bound;
	FaceOuterBound *outerBound;
	string cubeindex;

	Face(){
		FaceMod = 0;
		Bound = new FaceBound();
		outerBound = new FaceOuterBound();
		cubeindex = "";
	}
};

struct ClosedShell{
	vector<Face *> faces;
	string cubeindex;

	ClosedShell(){
		faces.empty();
		cubeindex = "";
	}
};

struct FacetedBrep{
	ClosedShell *Shell;
	string cubeindex;

	FacetedBrep(){
		Shell = new ClosedShell();
		cubeindex = "";
	}
};

struct AreaSolid{
	int ProfileMod;			// 0 is ArbitaryClosedProfile, 1 is RectangleProfile, 2 is CircleProfile, 9 is unincluded Model
	ArbitaryClosedProfile *Profile1;
	RectangleProfile *Profile2;
	CircleProfile *Profile3;
	Axis2Placement3D *Axis;
	Direction *Dir;
	double Position;
	string cubeindex;

	AreaSolid(){
		ProfileMod = 0;
		Profile1 = new ArbitaryClosedProfile();
		Profile2 = new RectangleProfile();
		Profile3 = new CircleProfile();
		Axis = new Axis2Placement3D();
		Dir = new Direction();
		Position = 0.0;
		cubeindex = "";
	}
};

struct GeometricRepresentationContext{
	Axis2Placement3D *Axis;
	Direction *Dir;

	GeometricRepresentationContext(){
		Axis = new Axis2Placement3D();
		Dir = new Direction();
	}
};

struct GeometricRepresentationSubContext{
	GeometricRepresentationContext *GRC;

	GeometricRepresentationSubContext(){
		GRC = new GeometricRepresentationContext();
	}
};

struct ShapeRepresentation{
	GeometricRepresentationContext *GRC;
	GeometricRepresentationSubContext *GRSC;
	int GeometricMod;	// 0 is GeometricRepresentationContext, 1 is GeometricRepresentationSubContext, 9 is unincluded Model


	vector<AreaSolid *> aSolid;
	PolyLine *pLine;
	vector<FacetedBrep *> fBs;
	int ShapeMod;	// 0 is AreSolid, 1 is pLine, 2 is FacetedBrep, 9 is unincluded Model

	string cubeindex;

	ShapeRepresentation(){
		GRC = new GeometricRepresentationContext;
		GRSC = new GeometricRepresentationSubContext;
		GeometricMod = 0;
		aSolid.empty();
		pLine = new PolyLine;
		fBs.empty();
		ShapeMod = 0;
		cubeindex = "";
	}

};

struct store{
	unordered_map<int, string> Main_hash;
	unordered_map<int, Direction *> IFCDIRECTION_hash;
	unordered_map<int, CartesianPoint *> IFCCARTESIANPOINT_hash;
	unordered_map<int, Axis2Placement3D *> IFCAXIS2PLACEMENT3D_hash;
	unordered_map<int, Axis2Placement2D *> IFCAXIS2PLACEMENT2D_hash;
	unordered_map<int, LocalPlacement *> IFCLOCALPLACEMENT_hash;
	unordered_map<int, PolyLine *> IFCPOLYLINE_hash;
	unordered_map<int, PolyLoop *> IFCPOLYLOOP_hash;
	unordered_map<int, ArbitaryClosedProfile *> IFCARBITRARYCLOSEDPROFILEDEF_hash;
	unordered_map<int, RectangleProfile *> IFCRECTANGLEPROFILEDEF_hash;
	unordered_map<int, CircleProfile *> IFCCIRCLEPROFILEDEF_hash;
	unordered_map<int, FaceBound *> IFCFACEBOUND_hash;
	unordered_map<int, FaceOuterBound *> IFCFACEOUTERBOUND_hash;
	unordered_map<int, Face *> IFCFACE_hash;
	unordered_map<int, ClosedShell *> IFCCLOSEDSHELL_hash;
	unordered_map<int, FacetedBrep *> IFCFACETEDBREP_hash;
	unordered_map<int, AreaSolid *> IFCEXTRUDEDAREASOLID_hash;
	unordered_map<int, GeometricRepresentationContext *> IFCGEOMETRICREPRESENTATIONCONTEXT_hash;
	unordered_map<int, GeometricRepresentationSubContext *> IFCGEOMETRICREPRESENTATIONSUBCONTEXT_hash;
	unordered_map<int, ShapeRepresentation *> IFCSHAPEREPRESENTATION_hash;

	double xCoordinateMax, yCoordinateMax, zCoordinateMax, xCoordinateMin, yCoordinateMin, zCoordinateMin;

	store(){
		Main_hash.empty();
		IFCDIRECTION_hash.empty();
		IFCCARTESIANPOINT_hash.empty();
		IFCAXIS2PLACEMENT3D_hash.empty();
		IFCAXIS2PLACEMENT2D_hash.empty();
		IFCLOCALPLACEMENT_hash.empty();
		IFCPOLYLINE_hash.empty();
		IFCPOLYLOOP_hash.empty();
		IFCARBITRARYCLOSEDPROFILEDEF_hash.empty();
		IFCRECTANGLEPROFILEDEF_hash.empty();
		IFCCIRCLEPROFILEDEF_hash.empty();
		IFCFACEBOUND_hash.empty();
		IFCFACEOUTERBOUND_hash.empty();
		IFCFACE_hash.empty();
		IFCCLOSEDSHELL_hash.empty();
		IFCFACETEDBREP_hash.empty();
		IFCEXTRUDEDAREASOLID_hash.empty();
		IFCGEOMETRICREPRESENTATIONCONTEXT_hash.empty();
		IFCGEOMETRICREPRESENTATIONSUBCONTEXT_hash.empty();
		IFCSHAPEREPRESENTATION_hash.empty();

		xCoordinateMax = INT_MIN;
		yCoordinateMax = INT_MIN;
		zCoordinateMax = INT_MIN;
		xCoordinateMin = INT_MAX;
		yCoordinateMin = INT_MAX;
		zCoordinateMin = INT_MAX;
	}
};
/*
void ReleaseProfile(AreaSolid *Solid){
	Solid->Profile1->pLine->Points.clear();
	Solid->Profile2->P1->x = 0, Solid->Profile2->P1->y = 0, Solid->Profile2->P1->z = 0, Solid->Profile2->P1->cubeindex = "", Solid->Profile2->P1->is3D = false;
	Solid->Profile2->P2->x = 0, Solid->Profile2->P2->y = 0, Solid->Profile2->P2->z = 0, Solid->Profile2->P2->cubeindex = "", Solid->Profile2->P2->is3D = false;
	Solid->Profile2->P3->x = 0, Solid->Profile2->P3->y = 0, Solid->Profile2->P3->z = 0, Solid->Profile2->P3->cubeindex = "", Solid->Profile2->P3->is3D = false;
	Solid->Profile2->P4->x = 0, Solid->Profile2->P4->y = 0, Solid->Profile2->P4->z = 0, Solid->Profile2->P4->cubeindex = "", Solid->Profile2->P4->is3D = false;
	Solid->Profile2->axis->point->x = 0, Solid->Profile2->axis->point->y = 0, Solid->Profile2->axis->point->z = 0, Solid->Profile2->axis->point->cubeindex = "", Solid->Profile2->axis->point->is3D = false;
	Solid->Profile2->axis->direction1->x = 0, Solid->Profile2->axis->direction1->y = 0, Solid->Profile2->axis->direction1->z = 0, Solid->Profile2->axis->direction1->is3D = false;
	Solid->Profile2->axis->direction2->x = 0, Solid->Profile2->axis->direction2->y = 0, Solid->Profile2->axis->direction2->z = 0, Solid->Profile2->axis->direction2->is3D = false;
	Solid->Profile2->xDim = 0, Solid->Profile2->yDim = 0;
}
*/

bool isContain(string slong, string sshort){
	if(slong.size() <= sshort.size())
		return false;
	for(int i = 0; i <= slong.size() - sshort.size(); i++){
		if(slong[i] == sshort[0]){
			for(int j = i + 1, count = 1; count != sshort.length(); j++, count++){
				if(slong[j] != sshort[count])
					break;
				if(count == sshort.length() - 1)
					return true;
			}
		}
	}
	return false;
}

double CountRadian(double d1, double d2){
	return atan(d1 / d2);
}

CartesianPoint *CountAbsCoordinate(Direction *d1, Direction *d2, CartesianPoint *CurPoint){
	bool d1clined = false;
	bool d2clined = false;
	char clinedCoordinate = NULL;
	char clinedDirection = NULL;
	double clinedCoordinateNumber = 0;
	double clinedDirectionNumber = 0;
	double DirX, DirY, DirZ;
	CartesianPoint *pnt = new CartesianPoint();
	if(d1->x != 1 && d1->x != 0 && d1->x != -1){
		d1clined = true;
		clinedDirection = 'X';
		clinedDirectionNumber = d1->x;
		if(d1->y != 0){
			clinedCoordinate = 'Y';
			clinedCoordinateNumber = d1->y;
		}
		else{
			clinedCoordinate = 'Z';
			clinedCoordinateNumber = d1->z;
		}
	}
	if(d2->x != 1 && d2->x != 0 && d2->x != -1){
		d2clined = true;
		clinedDirection = 'X';
		clinedDirectionNumber = d2->x;
		if(d2->y != 0){
			clinedCoordinate = 'Y';
			clinedCoordinateNumber = d2->y;
		}
		else{
			clinedCoordinate = 'Z';
			clinedCoordinateNumber = d2->z;
		}
	}
	DirX = d1->x == 0? d2->x : d1->x;
	if(d1->y != 1 && d1->y != 0 && d1->y != -1){
		d1clined = true;
		clinedDirection = 'Y';
		clinedDirectionNumber = d1->y;
		if(d1->x != 0){
			clinedCoordinate = 'X';
			clinedCoordinateNumber = d1->x;
		}
		else{
			clinedCoordinate = 'Z';
			clinedCoordinateNumber = d1->z;
		}
	}
	if(d2->y != 1 && d2->y != 0 && d2->y != -1){
		d2clined = true;
		clinedDirection = 'Y';
		clinedDirectionNumber = d2->y;
		if(d2->x != 0){
			clinedCoordinate = 'X';
			clinedCoordinateNumber = d2->x;
		}
		else{
			clinedCoordinate = 'Z';
			clinedCoordinateNumber = d2->z;
		}
	}
	DirY = d1->y == 0? d2->y : d1->y;
	if(d1->z != 1 && d1->z != 0 && d1->z != -1){
		d1clined = true;
		clinedDirection = 'Z';
		clinedDirectionNumber = d1->z;
		if(d1->x != 0){
			clinedCoordinate = 'X';
			clinedCoordinateNumber = d1->x;
		}
		else{
			clinedCoordinate = 'Y';
			clinedCoordinateNumber = d1->y;
		}
	}
	if(d2->z != 1 && d2->z != 0 && d2->z != -1){
		d2clined = true;
		clinedDirection = 'Z';
		clinedDirectionNumber = d2->z;
		if(d2->x != 0){
			clinedCoordinate = 'X';
			clinedCoordinateNumber = d2->x;
		}
		else{
			clinedCoordinate = 'Y';
			clinedCoordinateNumber = d2->y;
		}
	}
	DirZ = d1->z == 0? d2->z : d1->z;
	if(!CurPoint->is3D){
		if(d1clined){
			if(clinedCoordinate == 'Y'){
				CurPoint->y = CurPoint->x;
				CurPoint->x = 0;
			}
			else if(clinedCoordinate == 'Z'){
				CurPoint->z = CurPoint->x;
				CurPoint->x = 0;
			}
		}
		else if(d2clined){
			if(clinedCoordinate == 'X'){
				CurPoint->x = CurPoint->y;
				CurPoint->y = 0;
			}
			else if(clinedCoordinate == 'Z'){
				CurPoint->z = CurPoint->y;
				CurPoint->y = 0;
			}
		}
		//Isn't clined
		else{
			if(d1->y != 0){
				CurPoint->y = CurPoint->x;
				CurPoint->x = 0;
			}
			else if(d1->z != 0){
				CurPoint->z = CurPoint->x;
				CurPoint->x = 0;
			}
			if(d2->x != 0){
				CurPoint->x = CurPoint->y;
				CurPoint->y = 0;
			}
			else if(d2->z != 0){
				CurPoint->z = CurPoint->y;
				CurPoint->y = 0;
			}
		}
	}
	if(d1clined || d2clined){
		double radian = CountRadian(clinedDirectionNumber, clinedCoordinateNumber);
		if(clinedCoordinate == 'X'){
			if(clinedDirection == 'Y'){
				pnt->x = CurPoint->x * cos(radian);
				pnt->y = CurPoint->x * sin(radian);
				pnt->z = CurPoint->z * DirZ;
			}
			else{
				pnt->x = CurPoint->x * cos(radian);
				pnt->y = CurPoint->y * DirY;
				pnt->z = CurPoint->x * sin(radian);
			}
		}
		else if(clinedCoordinate == 'Y'){
			if(clinedDirection == 'X'){
				pnt->x = CurPoint->y * sin(radian);
				pnt->y = CurPoint->y * cos(radian);
				pnt->z = CurPoint->z * DirZ;
			}
			else{
				pnt->x = CurPoint->x * DirX;
				pnt->y = CurPoint->y * cos(radian); 
				pnt->z = CurPoint->y * sin(radian);
			}
		}
		else{
			if(clinedDirection == 'X'){
				pnt->x = CurPoint->z * sin(radian);
				pnt->y = CurPoint->y * DirY;
				pnt->z = CurPoint->z * cos(radian);
			}
			else{
				pnt->x = CurPoint->x * DirX;
				pnt->y = CurPoint->z * sin(radian);
				pnt->z = CurPoint->z * cos(radian);
			}
		}
	}
	else{
		pnt->x = CurPoint->x * DirX;
		pnt->y = CurPoint->y * DirY;
		pnt->z = CurPoint->z * DirZ;
	}
	return pnt;
}

// To Do: Change Pos to binary
string checkSection(double xStartPos, double xEndPos, double yStartPos, double yEndPos, double zStartPos, double zEndPos, double xPos, double yPos, double zPos, int layer, string &binaryPos){
	double xMid = (xStartPos + xEndPos) / 2;
	double yMid = (yStartPos + yEndPos) / 2;
	double zMid = (zStartPos + zEndPos) / 2;

	if(xPos >= xMid && yPos >= yMid && zPos >= zMid){
		binaryPos += '0';
		if(layer < 2)
			return checkSection((xStartPos + xEndPos) / 2, xEndPos, (yStartPos + yEndPos) / 2, yEndPos, (zStartPos + zEndPos) / 2, zEndPos, xPos, yPos, zPos, layer + 1, binaryPos);
	}
	else if(xPos < xMid && yPos >= yMid && zPos >= zMid){
		binaryPos += '1';
		if(layer < 2)
			return checkSection(xStartPos, (xStartPos + xEndPos) / 2, (yStartPos + yEndPos) / 2, yEndPos, (zStartPos + zEndPos) / 2, zEndPos, xPos, yPos, zPos, layer + 1, binaryPos);
	}
	else if(xPos < xMid && yPos < yMid && zPos >= zMid){
		binaryPos += '2';
		if(layer < 2)
			return checkSection(xStartPos, (xStartPos + xEndPos) / 2, yStartPos, (yStartPos + yEndPos) / 2, (zStartPos + zEndPos) / 2, zEndPos, xPos, yPos, zPos, layer + 1, binaryPos);
	}
	else if(xPos >= xMid && yPos < yMid && zPos >= zMid){
		binaryPos += '3';
		if(layer < 2)
			return checkSection((xStartPos + xEndPos) / 2, xEndPos, yStartPos, (yStartPos + yEndPos) / 2, (zStartPos + zEndPos) / 2, zEndPos, xPos, yPos, zPos, layer + 1, binaryPos);
	}
	else if(xPos >= xMid && yPos >= yMid && zPos < zMid){
		binaryPos += '4';
		if(layer < 2)
			return checkSection((xStartPos + xEndPos) / 2, xEndPos, (yStartPos + yEndPos) / 2, yEndPos, zStartPos, (zStartPos + zEndPos) / 2, xPos, yPos, zPos, layer + 1, binaryPos);
	}
	else if(xPos < xMid && yPos >= yMid && zPos < zMid){
		binaryPos += '5';
		if(layer < 2)
			return checkSection(xStartPos, (xStartPos + xEndPos) / 2, (yStartPos + yEndPos) / 2, yEndPos, zStartPos, (zStartPos + zEndPos) / 2, xPos, yPos, zPos, layer + 1, binaryPos);
	}
	else if(xPos < xMid && yPos < yMid && zPos < zMid){
		binaryPos += '6';
		if(layer < 2)
			return checkSection(xStartPos, (xStartPos + xEndPos) / 2, yStartPos, (yStartPos + yEndPos) / 2, zStartPos, (zStartPos + zEndPos) / 2, xPos, yPos, zPos, layer + 1, binaryPos);
	}
	else{
		binaryPos += '7';
		if(layer < 2)
			return checkSection((xStartPos + xEndPos) / 2, xEndPos, yStartPos, (yStartPos + yEndPos) / 2, zStartPos, (zStartPos + zEndPos) / 2, xPos, yPos, zPos, layer + 1, binaryPos);
	}

	return binaryPos;
}

void checkPointPos(store st){
	double xMaxPos = st.xCoordinateMax;
	double yMaxPos = st.yCoordinateMax;
	double zMaxPos = st.zCoordinateMax;
	double xMinPos = st.xCoordinateMin;
	double yMinPos = st.yCoordinateMin;
	double zMinPos = st.zCoordinateMin;
	for(unordered_map<int, CartesianPoint *>::iterator iter = st.IFCCARTESIANPOINT_hash.begin(); iter != st.IFCCARTESIANPOINT_hash.end(); iter++){
		if(iter->second->is3D){
			string binaryPos;
			iter->second->cubeindex = checkSection(xMinPos, xMaxPos, yMinPos, yMaxPos, zMinPos, zMaxPos, iter->second->x, iter->second->y, iter->second->z, 0, binaryPos);
		}
		else
			continue;
	}
}

void checkSinglePointPos(store *st){
	double xMaxPos = st->xCoordinateMax;
	double yMaxPos = st->yCoordinateMax;
	double zMaxPos = st->zCoordinateMax;
	double xMinPos = st->xCoordinateMin;
	double yMinPos = st->yCoordinateMin;
	double zMinPos = st->zCoordinateMin;
	for(unordered_map<int, CartesianPoint *>::iterator iter = st->IFCCARTESIANPOINT_hash.begin(); iter != st->IFCCARTESIANPOINT_hash.end(); iter++){
		string binaryPos;
		iter->second->cubeindex = checkSection(xMinPos, xMaxPos, yMinPos, yMaxPos, zMinPos, zMaxPos, iter->second->x, iter->second->y, iter->second->z, 0, binaryPos);
	}
}

void checkPolyLoopPos(store *st){
	int atLayer = 3;
	for(unordered_map<int, PolyLoop *>::iterator iter = st->IFCPOLYLOOP_hash.begin(); iter != st->IFCPOLYLOOP_hash.end(); iter++){
		string Pos = iter->second->Points[0]->cubeindex;
		for(int i = 0; i != iter->second->Points.size(); i++){
			if(iter->second->Points[i]->cubeindex.substr(0, atLayer) != Pos){
				string Pos1 = iter->second->Points[i]->cubeindex.substr(0, atLayer - 1);
				string Pos2 = Pos.substr(0, atLayer - 1);
				if(Pos1 == Pos2){
					Pos = Pos1;
					atLayer--;
				}
				else{
					Pos1 = iter->second->Points[i]->cubeindex.substr(0, atLayer - 2);
					Pos2 = Pos.substr(0, atLayer - 2);
					if(Pos1 == Pos2){
						Pos = Pos1;
						atLayer -= 2;
					}
					else{
						Pos = Pos.substr(0, atLayer - 3);
						break;
					}
				}
			}
		}
		iter->second->cubeindex = Pos;
	}
}

void checkFaceBoundPos(store *st){
	for(unordered_map<int, FaceBound *>::iterator iter = st->IFCFACEBOUND_hash.begin(); iter != st->IFCFACEBOUND_hash.end(); iter++)
		iter->second->cubeindex = iter->second->Loop->cubeindex;
}

void checkFaceOuterBoundPos(store *st){
	int i = 0;
	for(unordered_map<int, FaceOuterBound *>::iterator iter = st->IFCFACEOUTERBOUND_hash.begin(); iter != st->IFCFACEOUTERBOUND_hash.end(); iter++)
		iter->second->cubeindex = iter->second->Loop->cubeindex;
}

// Dosen't finish when FaceMod==1
void checkFacePos(store *st){
	for(unordered_map<int, Face *>::iterator iter = st->IFCFACE_hash.begin(); iter != st->IFCFACE_hash.end(); iter++){
		if(iter->second->FaceMod == 0)
			iter->second->cubeindex = iter->second->outerBound->cubeindex;
		else if(iter->second->FaceMod == 1)
			iter->second->cubeindex = iter->second->Bound->cubeindex;
	}
}

void checkClosedShellPos(store *st){
	int atLayer = 3;

	for(unordered_map<int, ClosedShell *>::iterator iter = st->IFCCLOSEDSHELL_hash.begin(); iter != st->IFCCLOSEDSHELL_hash.end(); iter++){
		string Pos = iter->second->faces[0]->cubeindex;
		for(int i = 0; i != iter->second->faces.size() && atLayer >= 1; i++){
			if(iter->second->faces[i]->cubeindex.substr(0, atLayer) != Pos){
				string Pos1 = iter->second->faces[i]->cubeindex.substr(0, atLayer - 1);
				string Pos2 = Pos.substr(0, atLayer - 1);
				if(Pos1 == Pos2){
					Pos = Pos1;
					atLayer--;
				}
				else{
					Pos1 = iter->second->faces[i]->cubeindex.substr(0, atLayer - 2);
					Pos2 = Pos.substr(0, atLayer - 2);
					if(Pos1 == Pos2){
						Pos = Pos1;
						atLayer -= 2;
					}
					else{
						Pos = Pos.substr(0, atLayer - 3);
						break;
					}
				}
			}
		}
		iter->second->cubeindex = Pos;
	}
}

void checkFacetedBrepPos(store *st){
	for(unordered_map<int, FacetedBrep *>::iterator iter = st->IFCFACETEDBREP_hash.begin(); iter != st->IFCFACETEDBREP_hash.end(); iter++)
		iter->second->cubeindex = iter->second->Shell->cubeindex;
}

void checkAreaSolidPointsBound(store *st){
	for(unordered_map<int, AreaSolid *>::iterator iter1 = st->IFCEXTRUDEDAREASOLID_hash.begin(); iter1 != st->IFCEXTRUDEDAREASOLID_hash.end(); iter1++){
		if(iter1->second->ProfileMod == 0){
			for(int i = 0; i != iter1->second->Profile1->pLine->Points.size(); i++){
				// Step 1: Points relate to Axis
				CartesianPoint *pnt = CountAbsCoordinate(iter1->second->Axis->Directions1, iter1->second->Axis->Directions2, iter1->second->Profile1->pLine->Points[i]);
				pnt->x += iter1->second->Axis->originalPoint->x;
				pnt->y += iter1->second->Axis->originalPoint->y;
				pnt->z += iter1->second->Axis->originalPoint->z;
				// Step 2: Points relate to Direction
				pnt->x += iter1->second->Position * iter1->second->Dir->x;
				pnt->y += iter1->second->Position * iter1->second->Dir->y;
				pnt->z += iter1->second->Position * iter1->second->Dir->z;
				pnt->is3D = true;

				st->xCoordinateMax = st->xCoordinateMax > pnt->x? st->xCoordinateMax : pnt->x;
				st->xCoordinateMin = st->xCoordinateMin < pnt->x? st->xCoordinateMin : pnt->x;
				st->yCoordinateMax = st->yCoordinateMax > pnt->y? st->yCoordinateMax : pnt->y;
				st->yCoordinateMin = st->yCoordinateMin < pnt->y? st->yCoordinateMin : pnt->y;
				st->zCoordinateMax = st->zCoordinateMax > pnt->z? st->zCoordinateMax : pnt->z;
				st->zCoordinateMin = st->zCoordinateMin < pnt->z? st->zCoordinateMin : pnt->z;

				iter1->second->Profile1->pLine->Points[i] = pnt;	
			}
		}
		else if(iter1->second->ProfileMod == 1){
			CartesianPoint *pnt1 = CountAbsCoordinate(iter1->second->Axis->Directions1, iter1->second->Axis->Directions2, iter1->second->Profile2->P1);
			CartesianPoint *pnt2 = CountAbsCoordinate(iter1->second->Axis->Directions1, iter1->second->Axis->Directions2, iter1->second->Profile2->P2);
			CartesianPoint *pnt3 = CountAbsCoordinate(iter1->second->Axis->Directions1, iter1->second->Axis->Directions2, iter1->second->Profile2->P3);
			CartesianPoint *pnt4 = CountAbsCoordinate(iter1->second->Axis->Directions1, iter1->second->Axis->Directions2, iter1->second->Profile2->P4);

			pnt1->x += iter1->second->Axis->originalPoint->x;
			pnt1->y += iter1->second->Axis->originalPoint->y;
			pnt1->z += iter1->second->Axis->originalPoint->z;

			pnt1->x += iter1->second->Position * iter1->second->Dir->x;
			pnt1->y += iter1->second->Position * iter1->second->Dir->y;
			pnt1->z += iter1->second->Position * iter1->second->Dir->z;
			pnt1->is3D = true;

			st->xCoordinateMax = st->xCoordinateMax > pnt1->x? st->xCoordinateMax : pnt1->x;
			st->xCoordinateMin = st->xCoordinateMin < pnt1->x? st->xCoordinateMin : pnt1->x;
			st->yCoordinateMax = st->yCoordinateMax > pnt1->y? st->yCoordinateMax : pnt1->y;
			st->yCoordinateMin = st->yCoordinateMin < pnt1->y? st->yCoordinateMin : pnt1->y;
			st->zCoordinateMax = st->zCoordinateMax > pnt1->z? st->zCoordinateMax : pnt1->z;
			st->zCoordinateMin = st->zCoordinateMin < pnt1->z? st->zCoordinateMin : pnt1->z;
		
			iter1->second->Profile2->P1 = pnt1;	
			
			pnt2->x += iter1->second->Axis->originalPoint->x;
			pnt2->y += iter1->second->Axis->originalPoint->y;
			pnt2->z += iter1->second->Axis->originalPoint->z;

			pnt2->x += iter1->second->Position * iter1->second->Dir->x;
			pnt2->y += iter1->second->Position * iter1->second->Dir->y;
			pnt2->z += iter1->second->Position * iter1->second->Dir->z;
			pnt2->is3D = true;

			st->xCoordinateMax = st->xCoordinateMax > pnt2->x? st->xCoordinateMax : pnt2->x;
			st->xCoordinateMin = st->xCoordinateMin < pnt2->x? st->xCoordinateMin : pnt2->x;
			st->yCoordinateMax = st->yCoordinateMax > pnt2->y? st->yCoordinateMax : pnt2->y;
			st->yCoordinateMin = st->yCoordinateMin < pnt2->y? st->yCoordinateMin : pnt2->y;
			st->zCoordinateMax = st->zCoordinateMax > pnt2->z? st->zCoordinateMax : pnt2->z;
			st->zCoordinateMin = st->zCoordinateMin < pnt2->z? st->zCoordinateMin : pnt2->z;
		
			iter1->second->Profile2->P2 = pnt2;	

			pnt3->x += iter1->second->Axis->originalPoint->x;
			pnt3->y += iter1->second->Axis->originalPoint->y;
			pnt3->z += iter1->second->Axis->originalPoint->z;			

			pnt3->x += iter1->second->Position * iter1->second->Dir->x;
			pnt3->y += iter1->second->Position * iter1->second->Dir->y;
			pnt3->z += iter1->second->Position * iter1->second->Dir->z;
			pnt3->is3D = true;

			st->xCoordinateMax = st->xCoordinateMax > pnt3->x? st->xCoordinateMax : pnt3->x;
			st->xCoordinateMin = st->xCoordinateMin < pnt3->x? st->xCoordinateMin : pnt3->x;
			st->yCoordinateMax = st->yCoordinateMax > pnt3->y? st->yCoordinateMax : pnt3->y;
			st->yCoordinateMin = st->yCoordinateMin < pnt3->y? st->yCoordinateMin : pnt3->y;
			st->zCoordinateMax = st->zCoordinateMax > pnt3->z? st->zCoordinateMax : pnt3->z;
			st->zCoordinateMin = st->zCoordinateMin < pnt3->z? st->zCoordinateMin : pnt3->z;
		
			iter1->second->Profile2->P3 = pnt3;	

			pnt4->x += iter1->second->Axis->originalPoint->x;
			pnt4->y += iter1->second->Axis->originalPoint->y;
			pnt4->z += iter1->second->Axis->originalPoint->z;
			
			pnt4->x += iter1->second->Position * iter1->second->Dir->x;
			pnt4->y += iter1->second->Position * iter1->second->Dir->y;
			pnt4->z += iter1->second->Position * iter1->second->Dir->z;
			pnt4->is3D = true;

			st->xCoordinateMax = st->xCoordinateMax > pnt4->x? st->xCoordinateMax : pnt4->x;
			st->xCoordinateMin = st->xCoordinateMin < pnt4->x? st->xCoordinateMin : pnt4->x;
			st->yCoordinateMax = st->yCoordinateMax > pnt4->y? st->yCoordinateMax : pnt4->y;
			st->yCoordinateMin = st->yCoordinateMin < pnt4->y? st->yCoordinateMin : pnt4->y;
			st->zCoordinateMax = st->zCoordinateMax > pnt4->z? st->zCoordinateMax : pnt4->z;
			st->zCoordinateMin = st->zCoordinateMin < pnt4->z? st->zCoordinateMin : pnt4->z;
		
			iter1->second->Profile2->P4 = pnt4;	
		}
		else if(iter1->second->ProfileMod == 2){
			CartesianPoint *pnt1 = CountAbsCoordinate(iter1->second->Axis->Directions1, iter1->second->Axis->Directions2, iter1->second->Profile3->t);
			CartesianPoint *pnt2 = CountAbsCoordinate(iter1->second->Axis->Directions1, iter1->second->Axis->Directions2, iter1->second->Profile3->b);
			CartesianPoint *pnt3 = CountAbsCoordinate(iter1->second->Axis->Directions1, iter1->second->Axis->Directions2, iter1->second->Profile3->l);
			CartesianPoint *pnt4 = CountAbsCoordinate(iter1->second->Axis->Directions1, iter1->second->Axis->Directions2, iter1->second->Profile3->r);

			pnt1->x += iter1->second->Axis->originalPoint->x;
			pnt1->y += iter1->second->Axis->originalPoint->y;
			pnt1->z += iter1->second->Axis->originalPoint->z;

			pnt1->x += iter1->second->Position * iter1->second->Dir->x;
			pnt1->y += iter1->second->Position * iter1->second->Dir->y;
			pnt1->z += iter1->second->Position * iter1->second->Dir->z;
			pnt1->is3D = true;

			st->xCoordinateMax = st->xCoordinateMax > pnt1->x? st->xCoordinateMax : pnt1->x;
			st->xCoordinateMin = st->xCoordinateMin < pnt1->x? st->xCoordinateMin : pnt1->x;
			st->yCoordinateMax = st->yCoordinateMax > pnt1->y? st->yCoordinateMax : pnt1->y;
			st->yCoordinateMin = st->yCoordinateMin < pnt1->y? st->yCoordinateMin : pnt1->y;
			st->zCoordinateMax = st->zCoordinateMax > pnt1->z? st->zCoordinateMax : pnt1->z;
			st->zCoordinateMin = st->zCoordinateMin < pnt1->z? st->zCoordinateMin : pnt1->z;
		
			iter1->second->Profile3->t = pnt1;

			pnt2->x += iter1->second->Axis->originalPoint->x;
			pnt2->y += iter1->second->Axis->originalPoint->y;
			pnt2->z += iter1->second->Axis->originalPoint->z;

			pnt2->x += iter1->second->Position * iter1->second->Dir->x;
			pnt2->y += iter1->second->Position * iter1->second->Dir->y;
			pnt2->z += iter1->second->Position * iter1->second->Dir->z;
			pnt2->is3D = true;

			st->xCoordinateMax = st->xCoordinateMax > pnt2->x? st->xCoordinateMax : pnt2->x;
			st->xCoordinateMin = st->xCoordinateMin < pnt2->x? st->xCoordinateMin : pnt2->x;
			st->yCoordinateMax = st->yCoordinateMax > pnt2->y? st->yCoordinateMax : pnt2->y;
			st->yCoordinateMin = st->yCoordinateMin < pnt2->y? st->yCoordinateMin : pnt2->y;
			st->zCoordinateMax = st->zCoordinateMax > pnt2->z? st->zCoordinateMax : pnt2->z;
			st->zCoordinateMin = st->zCoordinateMin < pnt2->z? st->zCoordinateMin : pnt2->z;
		
			iter1->second->Profile3->b = pnt2;

			pnt3->x += iter1->second->Axis->originalPoint->x;
			pnt3->y += iter1->second->Axis->originalPoint->y;
			pnt3->z += iter1->second->Axis->originalPoint->z;

			pnt3->x += iter1->second->Position * iter1->second->Dir->x;
			pnt3->y += iter1->second->Position * iter1->second->Dir->y;
			pnt3->z += iter1->second->Position * iter1->second->Dir->z;
			pnt3->is3D = true;

			st->xCoordinateMax = st->xCoordinateMax > pnt3->x? st->xCoordinateMax : pnt3->x;
			st->xCoordinateMin = st->xCoordinateMin < pnt3->x? st->xCoordinateMin : pnt3->x;
			st->yCoordinateMax = st->yCoordinateMax > pnt3->y? st->yCoordinateMax : pnt3->y;
			st->yCoordinateMin = st->yCoordinateMin < pnt3->y? st->yCoordinateMin : pnt3->y;
			st->zCoordinateMax = st->zCoordinateMax > pnt3->z? st->zCoordinateMax : pnt3->z;
			st->zCoordinateMin = st->zCoordinateMin < pnt3->z? st->zCoordinateMin : pnt3->z;
		
			iter1->second->Profile3->l = pnt3;

			pnt4->x += iter1->second->Axis->originalPoint->x;
			pnt4->y += iter1->second->Axis->originalPoint->y;
			pnt4->z += iter1->second->Axis->originalPoint->z;

			pnt4->x += iter1->second->Position * iter1->second->Dir->x;
			pnt4->y += iter1->second->Position * iter1->second->Dir->y;
			pnt4->z += iter1->second->Position * iter1->second->Dir->z;
			pnt4->is3D = true;

			st->xCoordinateMax = st->xCoordinateMax > pnt4->x? st->xCoordinateMax : pnt4->x;
			st->xCoordinateMin = st->xCoordinateMin < pnt4->x? st->xCoordinateMin : pnt4->x;
			st->yCoordinateMax = st->yCoordinateMax > pnt4->y? st->yCoordinateMax : pnt4->y;
			st->yCoordinateMin = st->yCoordinateMin < pnt4->y? st->yCoordinateMin : pnt4->y;
			st->zCoordinateMax = st->zCoordinateMax > pnt4->z? st->zCoordinateMax : pnt4->z;
			st->zCoordinateMin = st->zCoordinateMin < pnt4->z? st->zCoordinateMin : pnt4->z;
		
			iter1->second->Profile3->r = pnt4;
		}
	}
}

void checkAreaSolidPos(store *st){
	vector<CartesianPoint *> pnts;	
	for(unordered_map<int, AreaSolid *>::iterator iter1 = st->IFCEXTRUDEDAREASOLID_hash.begin(); iter1 != st->IFCEXTRUDEDAREASOLID_hash.end(); iter1++){
		if(iter1->second->ProfileMod == 0){
			for(int i = 0; i != iter1->second->Profile1->pLine->Points.size(); i++){
				CartesianPoint *pnt = iter1->second->Profile1->pLine->Points[i];
				string binaryPos;
				pnt->cubeindex = checkSection(st->xCoordinateMin, st->xCoordinateMax, st->yCoordinateMin, st->yCoordinateMax, st->zCoordinateMin, st->zCoordinateMax, pnt->x, pnt->y, pnt->z, 0, binaryPos);
				iter1->second->Profile1->pLine->Points[i] = pnt;
				pnts.push_back(pnt);
			}
		}
		else if(iter1->second->ProfileMod == 1){
			string binaryPos;
			binaryPos = checkSection(st->xCoordinateMin, st->xCoordinateMax, st->yCoordinateMin, st->yCoordinateMax, st->zCoordinateMin, st->zCoordinateMax, iter1->second->Profile2->P1->x, iter1->second->Profile2->P1->y, iter1->second->Profile2->P1->z, 0, binaryPos);
			iter1->second->Profile2->P1->cubeindex = binaryPos;
			pnts.push_back(iter1->second->Profile2->P1);
			binaryPos = "";
			binaryPos = checkSection(st->xCoordinateMin, st->xCoordinateMax, st->yCoordinateMin, st->yCoordinateMax, st->zCoordinateMin, st->zCoordinateMax, iter1->second->Profile2->P2->x, iter1->second->Profile2->P2->y, iter1->second->Profile2->P2->z, 0, binaryPos);
			iter1->second->Profile2->P2->cubeindex = binaryPos;
			pnts.push_back(iter1->second->Profile2->P2);
			binaryPos = "";
			binaryPos = checkSection(st->xCoordinateMin, st->xCoordinateMax, st->yCoordinateMin, st->yCoordinateMax, st->zCoordinateMin, st->zCoordinateMax, iter1->second->Profile2->P3->x, iter1->second->Profile2->P3->y, iter1->second->Profile2->P3->z, 0, binaryPos);
			iter1->second->Profile2->P3->cubeindex = binaryPos;
			pnts.push_back(iter1->second->Profile2->P3);
			binaryPos = "";
			binaryPos = checkSection(st->xCoordinateMin, st->xCoordinateMax, st->yCoordinateMin, st->yCoordinateMax, st->zCoordinateMin, st->zCoordinateMax, iter1->second->Profile2->P4->x, iter1->second->Profile2->P4->y, iter1->second->Profile2->P4->z, 0, binaryPos);
			iter1->second->Profile2->P4->cubeindex = binaryPos;
			pnts.push_back(iter1->second->Profile2->P4);
			binaryPos = "";
		}
		else if(iter1->second->ProfileMod == 2){
			string binaryPos;
			binaryPos = checkSection(st->xCoordinateMin, st->xCoordinateMax, st->yCoordinateMin, st->yCoordinateMax, st->zCoordinateMin, st->zCoordinateMax, iter1->second->Profile3->t->x, iter1->second->Profile3->t->y, iter1->second->Profile3->t->z, 0, binaryPos);
			iter1->second->Profile3->t->cubeindex = binaryPos;
			pnts.push_back(iter1->second->Profile3->t);
			binaryPos = "";
			binaryPos = checkSection(st->xCoordinateMin, st->xCoordinateMax, st->yCoordinateMin, st->yCoordinateMax, st->zCoordinateMin, st->zCoordinateMax, iter1->second->Profile3->b->x, iter1->second->Profile3->b->y, iter1->second->Profile3->b->z, 0, binaryPos);
			iter1->second->Profile3->b->cubeindex = binaryPos;
			pnts.push_back(iter1->second->Profile3->b);
			binaryPos = "";
			binaryPos = checkSection(st->xCoordinateMin, st->xCoordinateMax, st->yCoordinateMin, st->yCoordinateMax, st->zCoordinateMin, st->zCoordinateMax, iter1->second->Profile3->l->x, iter1->second->Profile3->l->y, iter1->second->Profile3->l->z, 0, binaryPos);
			iter1->second->Profile3->l->cubeindex = binaryPos;
			pnts.push_back(iter1->second->Profile3->l);
			binaryPos = "";
			binaryPos = checkSection(st->xCoordinateMin, st->xCoordinateMax, st->yCoordinateMin, st->yCoordinateMax, st->zCoordinateMin, st->zCoordinateMax, iter1->second->Profile3->r->x, iter1->second->Profile3->r->y, iter1->second->Profile3->r->z, 0, binaryPos);
			iter1->second->Profile3->r->cubeindex = binaryPos;
			pnts.push_back(iter1->second->Profile3->r);
			binaryPos = "";
		}
		// ifc format is unincluded
		else{
			return;
		}
		int atLayer = 3;
		string Pos = pnts[0]->cubeindex;
		for(vector<CartesianPoint *>::iterator iter2 = pnts.begin(); iter2 != pnts.end() && atLayer >= 1; iter2++){
			if((*iter2)->cubeindex.substr(0, atLayer) != Pos){
				string Pos1 = (*iter2)->cubeindex.substr(0, atLayer - 1);
				string Pos2 = Pos.substr(0, atLayer - 1);
				if(Pos1 == Pos2){
					Pos = Pos1;
					atLayer--;
				}
				else{
					Pos1 = (*iter2)->cubeindex.substr(0, atLayer - 2);
					Pos2 = Pos.substr(0, atLayer - 2);
					if(Pos1 == Pos2){
						Pos = Pos1;
						atLayer -= 2;
					}
					else{
						Pos = Pos.substr(0, atLayer - 3);
						break;
					}
				}
			}
		}
		pnts.clear();
		iter1->second->cubeindex = Pos;
	}
}

// Doesn't adjust the coordinate according to the geometric context
void checkShaperRepresentationPos(store *st){
	int atLayer = 3;
	 //0 is AreSolid, 1 is pLine, 2 is FacetedBrep, 9 is unincluded Model
	for(unordered_map<int, ShapeRepresentation *>::iterator iter = st->IFCSHAPEREPRESENTATION_hash.begin(); iter != st->IFCSHAPEREPRESENTATION_hash.end(); iter++){
		if(iter->second->ShapeMod == 0){
			string Pos = iter->second->aSolid[0]->cubeindex;
			for(int i = 0; i != iter->second->aSolid.size(); i++){				
				if(iter->second->aSolid[i]->cubeindex.substr(0, atLayer) != Pos){
					string Pos1 = iter->second->aSolid[i]->cubeindex.substr(0, atLayer - 1);
					string Pos2 = Pos.substr(0, atLayer - 1);
					if(Pos1 == Pos2){
						Pos = Pos1;
						atLayer--;
					}
					else{
						Pos1 = iter->second->aSolid[i]->cubeindex.substr(0, atLayer - 2);
						Pos2 = Pos.substr(0, atLayer - 2);
						if(Pos1 == Pos2){
							Pos = Pos1;
							atLayer -= 2;
						}
						else{
							Pos = Pos.substr(0, atLayer - 3);
							break;
						}
					}
				}
			}
			iter->second->cubeindex = Pos;
		}
		else if(iter->second->ShapeMod == 1){
			if(iter->second->GeometricMod == 0){
				for(int i = 0; i != iter->second->pLine->Points.size(); i++){
					CartesianPoint *pnt = CountAbsCoordinate(iter->second->GRC->Axis->Directions1, iter->second->GRC->Axis->Directions2, iter->second->pLine->Points[i]);

					pnt->x += iter->second->GRC->Axis->originalPoint->x;
					pnt->y += iter->second->GRC->Axis->originalPoint->y;
					pnt->z += iter->second->GRC->Axis->originalPoint->z;

					pnt->is3D = true;

					st->xCoordinateMax = st->xCoordinateMax > pnt->x? st->xCoordinateMax : pnt->x;
					st->xCoordinateMin = st->xCoordinateMin < pnt->x? st->xCoordinateMin : pnt->x;
					st->yCoordinateMax = st->yCoordinateMax > pnt->y? st->yCoordinateMax : pnt->y;
					st->yCoordinateMin = st->yCoordinateMin < pnt->y? st->yCoordinateMin : pnt->y;
					st->zCoordinateMax = st->zCoordinateMax > pnt->z? st->zCoordinateMax : pnt->z;
					st->zCoordinateMin = st->zCoordinateMin < pnt->z? st->zCoordinateMin : pnt->z;
					string binaryPos;
					pnt->cubeindex = checkSection(st->xCoordinateMin, st->xCoordinateMax, st->yCoordinateMin, st->yCoordinateMax, st->zCoordinateMin, st->zCoordinateMax, pnt->x, pnt->y, pnt->z, 0, binaryPos);

					iter->second->pLine->Points[i] = pnt;
				}

			}
			else if(iter->second->GeometricMod == 1){
				for(int i = 0; i != iter->second->pLine->Points.size(); i++){
					CartesianPoint *pnt = CountAbsCoordinate(iter->second->GRSC->GRC->Axis->Directions1, iter->second->GRSC->GRC->Axis->Directions2, iter->second->pLine->Points[i]);

					pnt->x += iter->second->GRSC->GRC->Axis->originalPoint->x;
					pnt->y += iter->second->GRSC->GRC->Axis->originalPoint->y;
					pnt->z += iter->second->GRSC->GRC->Axis->originalPoint->z;

					pnt->is3D = true;

					st->xCoordinateMax = st->xCoordinateMax > pnt->x? st->xCoordinateMax : pnt->x;
					st->xCoordinateMin = st->xCoordinateMin < pnt->x? st->xCoordinateMin : pnt->x;
					st->yCoordinateMax = st->yCoordinateMax > pnt->y? st->yCoordinateMax : pnt->y;
					st->yCoordinateMin = st->yCoordinateMin < pnt->y? st->yCoordinateMin : pnt->y;
					st->zCoordinateMax = st->zCoordinateMax > pnt->z? st->zCoordinateMax : pnt->z;
					st->zCoordinateMin = st->zCoordinateMin < pnt->z? st->zCoordinateMin : pnt->z;	
					string binaryPos;
					pnt->cubeindex = checkSection(st->xCoordinateMin, st->xCoordinateMax, st->yCoordinateMin, st->yCoordinateMax, st->zCoordinateMin, st->zCoordinateMax, pnt->x, pnt->y, pnt->z, 0, binaryPos);
					
					iter->second->pLine->Points[i] = pnt;
				}
			}
			string Pos = iter->second->pLine->Points[0]->cubeindex;
			for(int i = 0; i != iter->second->pLine->Points.size(); i++){				
				if(iter->second->pLine->Points[i]->cubeindex != Pos){
					string Pos1 = iter->second->pLine->Points[i]->cubeindex.substr(0, atLayer - 1);
					string Pos2 = Pos.substr(0, atLayer - 1);
					if(Pos1 == Pos2){
						Pos = Pos1;
						atLayer--;
					}
					else{
						Pos1 = iter->second->pLine->Points[i]->cubeindex.substr(0, atLayer - 2);
						Pos2 = Pos.substr(0, atLayer - 2);
						if(Pos1 == Pos2){
							Pos = Pos1;
							atLayer -= 2;
						}
						else{
							Pos = Pos.substr(0, atLayer - 3);
							break;
						}
					}
				}
			}
			iter->second->cubeindex = Pos;
		}
		else if(iter->second->ShapeMod == 2){
			string Pos = iter->second->fBs[0]->cubeindex;
			for(int i = 0; i != iter->second->fBs.size(); i++){				
				if(iter->second->fBs[i]->cubeindex.substr(0, atLayer) != Pos){
					string Pos1 = iter->second->fBs[i]->cubeindex.substr(0, atLayer - 1);
					string Pos2 = Pos.substr(0, atLayer - 1);
					if(Pos1 == Pos2){
						Pos = Pos1;
						atLayer--;
					}
					else{
						Pos1 = iter->second->fBs[i]->cubeindex.substr(0, atLayer - 2);
						Pos2 = Pos.substr(0, atLayer - 2);
						if(Pos1 == Pos2){
							Pos = Pos1;
							atLayer -= 2;
						}
						else{
							Pos = Pos.substr(0, atLayer - 3);
							break;
						}
					}
				}
			}
			iter->second->cubeindex = Pos;
		}
		else{
		}
		atLayer = 3;
	}
}

void checkPositions(store *st){
	checkAreaSolidPointsBound(st);
	checkSinglePointPos(st);
	checkAreaSolidPos(st);
	checkPolyLoopPos(st);
	checkFaceBoundPos(st);
	checkFaceOuterBoundPos(st);
	checkFacePos(st);
	checkClosedShellPos(st);
	checkFacetedBrepPos(st);
	checkShaperRepresentationPos(st);
}

void ReadIFCDIRECTION(store *st, string file){
	ifstream in(file);
	string line;

	if(in){
		while(getline(in, line)){
			int Pos = 0, lineNumber;
			if(line.empty())
				continue;
			else if(line[Pos] == '#'){
				Pos++;
				lineNumber = line[Pos++] - '0';
				while(Pos != line.length()){
					if(isdigit(line[Pos])){
						lineNumber *= 10;
						lineNumber += (line[Pos++] - '0');
					}
					else
						break;
				}
			}
			else
				continue;
			if(isContain(line, "IFCDIRECTION"))
			{
				int countedNum = 0, expDigits = 0, decimalDigits = 0;
				double coordinate = 0;
				Direction *d = new Direction();
				vector<double> coordinateXYZ;
				bool isDecimal = false;
				bool isMinus = false;
				bool exp = false;
				bool expMinus = false;
				while(Pos != line.length()){
					if(isdigit(line[Pos])){
						while(Pos != line.length() && (isdigit(line[Pos]) || line[Pos] == 'E' || line[Pos] == '-' || line[Pos] == '.')){
							if(isdigit(line[Pos])){
								if(!exp){
									if(!isDecimal){
										coordinate *= 10;
										coordinate += (line[Pos++] - '0');
									}
									else{
										coordinate += (line[Pos++] - '0') * pow(10.0, decimalDigits--);
									}
								}
								else
									expDigits = !expMinus? (line[Pos++] - '0') : -(line[Pos++] - '0');
							}
							else if(line[Pos] == 'E'){
								exp = true;
								Pos++;
							}
							else if(line[Pos] == '-'){
								expMinus = true;
								Pos++;
							}
							else{
								isDecimal = true;
								decimalDigits--;
								Pos++;
							}
						}
						if(exp)
							coordinate *= pow(10.0, expDigits);
						if(isMinus)
							coordinate *= -1;
						coordinateXYZ.push_back(coordinate);
						coordinate = 0;
						decimalDigits = 0;
						isDecimal = false;
						isMinus = false;
						exp = false;
						expMinus = false;
					}
					else if(line[Pos] == '-'){
						isMinus = true;
						Pos++;
					}
					else
						Pos++;
				}
				d->x = coordinateXYZ[0];
				d->y = coordinateXYZ[1];
				if(coordinateXYZ.size() > 2){
					d->z = coordinateXYZ[2];
					d->is3D = true;
				}
				else
					d->is3D = false;

				std::pair<int, string> dpair1(lineNumber, "IFCDIRECTION");
				std::pair<int, Direction *> dpair2(lineNumber, d);
				st->Main_hash.insert(dpair1);
				st->IFCDIRECTION_hash.insert(dpair2);

				//st->Main_hash[lineNumber] = "IFCDIRECTION";
				//st->IFCDIRECTION_hash[lineNumber] = d;
			}
		}
	}
	else
		cout << "no such file" << endl;
}

void ReadIFCAXIS2PLACEMENT3D(store *st, string file){
	ifstream in(file);
	string line;
	if(in){
		while(getline(in, line)){
			int Pos = 0, lineNumber;
			if(line.empty())
				continue;
			else if(line[Pos] == '#'){
				Pos++;
				lineNumber = line[Pos++] - '0';
				while(Pos != line.length()){
					if(isdigit(line[Pos])){
						lineNumber *= 10;
						lineNumber += (line[Pos++] - '0');
					}
					else
						break;
				}
			}
			else
				continue;
			if(isContain(line, "IFCAXIS2PLACEMENT3D"))
			{
				int drctNumber = 0, storeNumbers = 0;
				Axis2Placement3D *A2P = new Axis2Placement3D();
				while(Pos != line.length()){
					if(line[Pos] == '#'){
						Pos++;
						while(Pos != line.length() && isdigit(line[Pos])){
							drctNumber *= 10;
							drctNumber += (line[Pos++] - '0');
						}
						if(storeNumbers == 0){
							A2P->originalPoint->x = 1;
							A2P->originalPoint->x = st->IFCCARTESIANPOINT_hash[drctNumber]->x;
							A2P->originalPoint->y = st->IFCCARTESIANPOINT_hash[drctNumber]->y;
							A2P->originalPoint->z = st->IFCCARTESIANPOINT_hash[drctNumber]->z;
						}
						else if(storeNumbers == 1){
							A2P->Directions1->x = st->IFCDIRECTION_hash[drctNumber]->x;
							A2P->Directions1->y = st->IFCDIRECTION_hash[drctNumber]->y;
							A2P->Directions1->z = st->IFCDIRECTION_hash[drctNumber]->z;
						}
						else{
							A2P->Directions2->x = st->IFCDIRECTION_hash[drctNumber]->x;
							A2P->Directions2->y = st->IFCDIRECTION_hash[drctNumber]->y;
							A2P->Directions2->z = st->IFCDIRECTION_hash[drctNumber]->z;
						}
						storeNumbers++;
						drctNumber = 0;
					}
					else if(line[Pos] == '$'){						
						if(storeNumbers == 0){
							A2P->originalPoint->x = 0;
							A2P->originalPoint->y = 0;
							A2P->originalPoint->z = 0;
						}
						else if(storeNumbers == 1){
							A2P->Directions1->x = 0;
							A2P->Directions1->y = 0;
							A2P->Directions1->z = 0;
						}
						else{
							A2P->Directions2->x = 0;
							A2P->Directions2->y = 0;
							A2P->Directions2->z = 0;
						}
						storeNumbers++;
						Pos++;
					}
					else
						Pos++;
				}

				std::pair<int, string> a2ppair1(lineNumber, "IFCAXIS2PLACEMENT3D");
				std::pair<int, Axis2Placement3D *> a2ppair2(lineNumber, A2P);
				st->Main_hash.insert(a2ppair1);
				st->IFCAXIS2PLACEMENT3D_hash.insert(a2ppair2);

				//st->Main_hash[lineNumber] = "IFCAXIS2PLACEMENT3D";
				//st->IFCAXIS2PLACEMENT3D_hash[lineNumber] = A2P;
			}
		}
	}
}

void ReadIFCAXIS2PLACEMENT2D(store *st, string file){
	ifstream in(file);
	string line;
	if(in){
		while(getline(in, line)){
			int Pos = 0, lineNumber;
			if(line.empty())
				continue;
			else if(line[Pos] == '#'){
				Pos++;
				lineNumber = line[Pos++] - '0';
				while(Pos != line.length()){
					if(isdigit(line[Pos])){
						lineNumber *= 10;
						lineNumber += (line[Pos++] - '0');
					}
					else
						break;
				}
			}
			else
				continue;
			if(isContain(line, "IFCAXIS2PLACEMENT2D"))
			{
				int drctNumber = 0, storeNumbers = 0;
				Axis2Placement2D *A2P = new Axis2Placement2D();
				while(Pos != line.length()){
					if(line[Pos] == '#'){
						Pos++;
						while(Pos != line.length() && isdigit(line[Pos])){
							drctNumber *= 10;
							drctNumber += (line[Pos++] - '0');
						}
						if(storeNumbers == 0){
							A2P->point = st->IFCCARTESIANPOINT_hash[drctNumber];
						}
						else{
							A2P->direction1 = st->IFCDIRECTION_hash[drctNumber];
						}
						storeNumbers++;
						drctNumber = 0;
					}
					else if(line[Pos] == '$'){						
						if(storeNumbers == 0){
							A2P->point->x = 0;
							A2P->point->y = 0;
							A2P->point->z = 0;
						}
						else{
							A2P->direction1->x = 0;
							A2P->direction1->y = 0;
							A2P->direction1->z = 0;
						}
						storeNumbers++;
						Pos++;
					}
					else
						Pos++;
				}

				Direction *dir = new Direction();
				if(A2P->direction1->x >= 0 && A2P->direction1->y >= 0){
					dir->x = -A2P->direction1->y;
					dir->y = A2P->direction1->x;
				}
				else if(A2P->direction1->x < 0 && A2P->direction1->y >= 0){
					dir->x = A2P->direction1->y;
					dir->y = -A2P->direction1->x;
				}
				else if(A2P->direction1->x >= 0 && A2P->direction1->y < 0){
					dir->x = -A2P->direction1->y;
					dir->y = A2P->direction1->x;
				}
				else if(A2P->direction1->x < 0 && A2P->direction1->y < 0){
					dir->x = A2P->direction1->y;
					dir->y = -A2P->direction1->x;
				}
				dir->is3D = false;
				A2P->direction2 = dir;

				std::pair<int, string> a2ppair1(lineNumber, "IFCAXIS2PLACEMENT2D");
				std::pair<int, Axis2Placement2D *> a2ppair2(lineNumber, A2P);
				st->Main_hash.insert(a2ppair1);
				st->IFCAXIS2PLACEMENT2D_hash.insert(a2ppair2);

				//st->Main_hash[lineNumber] = "IFCAXIS2PLACEMENT2D";
				//st->IFCAXIS2PLACEMENT2D_hash[lineNumber] = A2P;
			}
		}
	}
}

void ReadIFCLOCALPLACEMENT(store *st, string file){
	ifstream in(file);
	string line;
	if(in){
		while(getline(in, line)){
			int Pos = 0, lineNumber;
			if(line.empty())
				continue;
			else if(line[Pos] == '#'){
				Pos++;
				lineNumber = line[Pos++] - '0';
				while(Pos != line.length()){
					if(isdigit(line[Pos])){
						lineNumber *= 10;
						lineNumber += (line[Pos++] - '0');
					}
					else
						break;
				}
			}
			else
				continue;
			if(isContain(line, "IFCLOCALPLACEMENT"))
			{
				int ParaNumber = 0, storeNumbers = 0, lastLocalPlacementNum = 0;
				LocalPlacement *LP = new LocalPlacement();
				double lastoriginalPointX = 0;
				double lastoriginalPointY = 0;
				double lastoriginalPointZ = 0;
				bool noLastPlacement = false;				
				while(Pos != line.length()){
					if(line[Pos] == '#'){
						Pos++;
						while(Pos != line.length() && isdigit(line[Pos])){
							ParaNumber *= 10;
							ParaNumber += (line[Pos++] - '0');
						}
						if(storeNumbers == 0){
							lastoriginalPointX = st->IFCLOCALPLACEMENT_hash[ParaNumber]->originalPoint->x;
							lastoriginalPointY = st->IFCLOCALPLACEMENT_hash[ParaNumber]->originalPoint->y;
							lastoriginalPointZ = st->IFCLOCALPLACEMENT_hash[ParaNumber]->originalPoint->z;
							lastLocalPlacementNum = ParaNumber;
						}
						else{// $ problem
							if(!noLastPlacement)
								LP->originalPoint = CountAbsCoordinate(st->IFCLOCALPLACEMENT_hash[lastLocalPlacementNum]->Directions1, st->IFCLOCALPLACEMENT_hash[lastLocalPlacementNum]->Directions2, st->IFCAXIS2PLACEMENT3D_hash[ParaNumber]->originalPoint);
							else{


								// Shouldn't use ifcaixs2placement3d here

								LP->originalPoint->x = st->IFCAXIS2PLACEMENT3D_hash[ParaNumber]->originalPoint->x;
								LP->originalPoint->y = st->IFCAXIS2PLACEMENT3D_hash[ParaNumber]->originalPoint->y;
								LP->originalPoint->z = st->IFCAXIS2PLACEMENT3D_hash[ParaNumber]->originalPoint->z;
							}
							LP->originalPoint->x += lastoriginalPointX;
							LP->originalPoint->y += lastoriginalPointY;
							LP->originalPoint->z += lastoriginalPointZ;
							LP->Directions1 = st->IFCAXIS2PLACEMENT3D_hash[ParaNumber]->Directions1;
							LP->Directions2 = st->IFCAXIS2PLACEMENT3D_hash[ParaNumber]->Directions2;
						}
						storeNumbers++;
						ParaNumber = 0;
					}
					else if(line[Pos] == '$'){						
						if(storeNumbers == 0){
							LP->originalPoint->x = 0;
							LP->originalPoint->y = 0;
							LP->originalPoint->z = 0;
							noLastPlacement = true;
						}
						storeNumbers++;
						Pos++;
					}
					else
						Pos++;
				}

				std::pair<int, string> lppair1(lineNumber, "IFCLOCALPLACEMENT");
				std::pair<int, LocalPlacement *> lppair2(lineNumber, LP);
				st->Main_hash.insert(lppair1);
				st->IFCLOCALPLACEMENT_hash.insert(lppair2);

				//st->Main_hash[lineNumber] = "IFCLOCALPLACEMENT";
				//st->IFCLOCALPLACEMENT_hash[lineNumber] = LP;
			}
		}
	}
}

void ReadIFCCARTESIANPOINT(store *st, string file){
	ifstream in(file);
	string line;

	st->xCoordinateMax = INT_MIN;
	st->yCoordinateMax = INT_MIN;
	st->zCoordinateMax = INT_MIN;
	st->xCoordinateMin = INT_MAX;
	st->yCoordinateMin = INT_MAX;
	st->zCoordinateMin = INT_MAX;
	if(in){
		while(getline(in, line)){
			int Pos = 0, lineNumber;
			if(line.empty())
				continue;
			else if(line[Pos] == '#'){
				Pos++;
				lineNumber = line[Pos++] - '0';
				while(Pos != line.length()){
					if(isdigit(line[Pos])){
						lineNumber *= 10;
						lineNumber += (line[Pos++] - '0');
					}
					else
						break;
				}
			}
			else
				continue;
			if(isContain(line, "IFCCARTESIANPOINT"))
			{
				int countedNum = 0, decimalDigits = 0;
				double coordinate = 0;
				CartesianPoint *p = new CartesianPoint();
				vector<double> coordinateXYZ;
				bool isDecimal = false;
				bool isMinus = false;
				while(Pos != line.length()){
					if(isdigit(line[Pos])){
						while(Pos != line.length() && (isdigit(line[Pos]) || line[Pos] == '.')){
							if(isdigit(line[Pos])){
								if(!isDecimal){
									coordinate *= 10;
									coordinate += (line[Pos++] - '0');
								}
								else{
									coordinate += (line[Pos++] - '0') * pow(10.0, decimalDigits--);
								}
							}
							else{
								isDecimal = true;
								decimalDigits--;
								Pos++;
							}
						}
						if(isMinus)
							coordinate *= -1;
						coordinateXYZ.push_back(coordinate);
						coordinate = 0;
						decimalDigits = 0;
						isDecimal = false;
						isMinus = false;
					}
					else if(line[Pos] == '-'){
						isMinus = true;
						Pos++;
					}
					else
						Pos++;
				}

				p->x = coordinateXYZ[0];
				st->xCoordinateMax = st->xCoordinateMax > p->x? st->xCoordinateMax : p->x;
				st->xCoordinateMin = st->xCoordinateMin < p->x? st->xCoordinateMin : p->x;
				p->y = coordinateXYZ[1];
				st->yCoordinateMax = st->yCoordinateMax > p->y? st->yCoordinateMax : p->y;
				st->yCoordinateMin = st->yCoordinateMin < p->y? st->yCoordinateMin : p->y;
				if(coordinateXYZ.size() > 2){
					p->z = coordinateXYZ[2];
					st->zCoordinateMax = st->zCoordinateMax > p->z? st->zCoordinateMax : p->z;
					st->zCoordinateMin = st->zCoordinateMin < p->z? st->zCoordinateMin : p->z;
					p->is3D = true;
				}
				else
					p->is3D = false;
				
				std::pair<int, string> cppair1(lineNumber, "IFCCARTESIANPOINT");
				std::pair<int, CartesianPoint *> cppair2(lineNumber, p);
				st->Main_hash.insert(cppair1);
				st->IFCCARTESIANPOINT_hash.insert(cppair2);

				//st->Main_hash[lineNumber] = "IFCCARTESIANPOINT";
				//st->IFCCARTESIANPOINT_hash[lineNumber] = p;
			}
		}
	}
	else
		cout << "no such file" << endl;
}

void ReadIFCPOLYLINE(store *st, string file){
	ifstream in(file);
	string line;
	if(in){
		while(getline(in, line)){
			int Pos = 0, lineNumber;
			if(line.empty())
				continue;
			else if(line[Pos] == '#'){
				Pos++;
				lineNumber = line[Pos++] - '0';
				while(Pos != line.length()){
					if(isdigit(line[Pos])){
						lineNumber *= 10;
						lineNumber += (line[Pos++] - '0');
					}
					else
						break;
				}
			}
			else
				continue;
			if(isContain(line, "IFCPOLYLINE"))
			{
				int pntNumber = 0;
				CartesianPoint pnt;
				PolyLine *pLine = new PolyLine();
				while(Pos != line.length()){
					if(line[Pos] == '#'){
						Pos++;
						while(Pos != line.length() && isdigit(line[Pos])){
							pntNumber *= 10;
							pntNumber += (line[Pos++] - '0');
						}
						pLine->Points.push_back(st->IFCCARTESIANPOINT_hash[pntNumber]);
						pntNumber = 0;
					}
					else
						Pos++;
				}

				std::pair<int, string> plpair1(lineNumber, "IFCPOLYLINE");
				std::pair<int, PolyLine *> plpair2(lineNumber, pLine);
				st->Main_hash.insert(plpair1);
				st->IFCPOLYLINE_hash.insert(plpair2);

				//st->Main_hash[lineNumber] = "IFCPOLYLINE";
				//st->IFCPOLYLINE_hash[lineNumber] = pLine;
			}
		}
	}
}

void ReadIFCPOLYLOOP(store *st, string file){
	ifstream in(file);
	string line;
	if(in){
		while(getline(in, line)){
			int Pos = 0, lineNumber;
			if(line.empty())
				continue;
			else if(line[Pos] == '#'){
				Pos++;
				lineNumber = line[Pos++] - '0';
				while(Pos != line.length()){
					if(isdigit(line[Pos])){
						lineNumber *= 10;
						lineNumber += (line[Pos++] - '0');
					}
					else
						break;
				}
			}
			else
				continue;
			if(isContain(line, "IFCPOLYLOOP"))
			{
				int pntNumber = 0;				
				PolyLoop *loop = new PolyLoop();
				CartesianPoint *pnt;
				while(Pos != line.length()){
					if(line[Pos] == '#'){
						Pos++;
						while(Pos != line.length() && isdigit(line[Pos])){
							pntNumber *= 10;
							pntNumber += (line[Pos++] - '0');
						}
						pnt = st->IFCCARTESIANPOINT_hash[pntNumber];
						loop->Points.push_back(pnt);
						pntNumber = 0;
					}
					else
						Pos++;
				}				
				
				std::pair<int, string> lpair1(lineNumber, "IFCPOLYLOOP");
				std::pair<int, PolyLoop *> lpair2(lineNumber, loop);
				st->Main_hash.insert(lpair1);
				st->IFCPOLYLOOP_hash.insert(lpair2);
			}
		}
	}
}

void ReadIFCARBITRARYCLOSEDPROFILEDEF(store *st, string file){
	ifstream in(file);
	string line;
	if(in){
		while(getline(in, line)){
			int Pos = 0, lineNumber;
			if(line.empty())
				continue;
			else if(line[Pos] == '#'){
				Pos++;
				lineNumber = line[Pos++] - '0';
				while(Pos != line.length()){
					if(isdigit(line[Pos])){
						lineNumber *= 10;
						lineNumber += (line[Pos++] - '0');
					}
					else
						break;
				}
			}
			else
				continue;
			if(isContain(line, "IFCARBITRARYCLOSEDPROFILEDEF")){
					int plineNumber = 0;
					ArbitaryClosedProfile *pro = new ArbitaryClosedProfile();
					while(Pos != line.length()){
						if(line[Pos] == '#'){
							Pos++;
							while(Pos != line.length() && isdigit(line[Pos])){
								plineNumber *= 10;
								plineNumber += (line[Pos++] - '0');
							}
						}
						else
							Pos++;
					}
					pro->pLine = st->IFCPOLYLINE_hash[plineNumber];

					std::pair<int, string> cppair1(lineNumber, "IFCARBITRARYCLOSEDPROFILEDEF");
					std::pair<int, ArbitaryClosedProfile *> cppair2(lineNumber, pro);
					st->Main_hash.insert(cppair1);
					st->IFCARBITRARYCLOSEDPROFILEDEF_hash.insert(cppair2);

					//st->Main_hash[lineNumber] = "IFCARBITRARYCLOSEDPROFILEDEF";
					//st->IFCARBITRARYCLOSEDPROFILEDEF_hash[lineNumber] = pro;
			}
		}
	}
}

void ReadIFCRECTANGLEPROFILEDEF(store *st, string file){
	ifstream in(file);
	string line;
	if(in){
		while(getline(in, line)){
			int Pos = 0, lineNumber;
			if(line.empty())
				continue;
			else if(line[Pos] == '#'){
				Pos++;
				lineNumber = line[Pos++] - '0';
				while(Pos != line.length()){
					if(isdigit(line[Pos])){
						lineNumber *= 10;
						lineNumber += (line[Pos++] - '0');
					}
					else
						break;
				}
			}
			else
				continue;
			if(isContain(line, "IFCRECTANGLEPROFILEDEF"))
			{
				int drctNumber = 0, Dim = 0, decimalDigits = 0;
				double coordinate = 0;
				RectangleProfile *rect = new RectangleProfile();
				bool isDecimal = false;
				while(Pos != line.length()){
					if(line[Pos] == '#'){
						Pos++;
						while(Pos != line.length() && isdigit(line[Pos])){
							drctNumber *= 10;
							drctNumber += (line[Pos++] - '0');
						}
						rect->axis = st->IFCAXIS2PLACEMENT2D_hash[drctNumber];
						drctNumber = 0;
					}
					else if(isdigit(line[Pos])){						
						if(Dim == 0){
							while(Pos != line.length() && (isdigit(line[Pos]) || line[Pos] == '.')){
								if(isdigit(line[Pos])){
									if(!isDecimal){
										coordinate *= 10;
										coordinate += (line[Pos++] - '0');
									}
									else{
										coordinate += (line[Pos++] - '0') * pow(10.0, decimalDigits--);
									}
								}
								else{
									isDecimal = true;
									decimalDigits--;
									Pos++;
								}
							}
							rect->xDim = coordinate;
							Dim++;
						}
						else{
							while(Pos != line.length() && (isdigit(line[Pos]) || line[Pos] == '.')){
								if(isdigit(line[Pos])){
									if(!isDecimal){
										coordinate *= 10;
										coordinate += (line[Pos++] - '0');
									}
									else{
										coordinate += (line[Pos++] - '0') * pow(10.0, decimalDigits--);
									}
								}
								else{
									isDecimal = true;
									decimalDigits--;
									Pos++;
								}
							}
							rect->yDim = coordinate;
						}
						coordinate = 0;
						isDecimal = false;
						Pos++;
					}
					else
						Pos++;
				}

				double arc = atan(abs(rect->axis->direction1->y / rect->axis->direction1->x));

				// Not sure if P1 is (0, 0, 0)
				rect->P1->x = 0;
				rect->P1->y = 0;
				rect->P1->z = 0;
				rect->P1->is3D = false;

				rect->P2->x = cos(arc) * rect->xDim;
				rect->P2->x *= rect->axis->direction1->x >= 0? 1 : -1;
				rect->P2->y = sin(arc) * rect->xDim;
				rect->P2->y *= rect->axis->direction1->y >= 0? 1 : -1;
				rect->P2->z = 0;
				rect->P2->is3D = false;

				rect->P3->x = sin(arc) * rect->yDim;
				rect->P3->x *= rect->axis->direction2->x >= 0? 1 : -1;
				rect->P3->y = cos(arc) * rect->yDim;
				rect->P3->y *= rect->axis->direction2->y >= 0? 1 : -1;
				rect->P3->z = 0;
				rect->P3->is3D = false;

				rect->P4->x = rect->P2->x + rect->P3->x;
				rect->P4->y = rect->P2->y + rect->P3->y;
				rect->P4->z = 0;
				rect->P4->is3D = false;

				std::pair<int, string> rppair1(lineNumber, "IFCRECTANGLEPROFILEDEF");
				std::pair<int, RectangleProfile *> rppair2(lineNumber, rect);
				st->Main_hash.insert(rppair1);
				st->IFCRECTANGLEPROFILEDEF_hash.insert(rppair2);

				//st->Main_hash[lineNumber] = "IFCRECTANGLEPROFILEDEF";
				//st->IFCRECTANGLEPROFILEDEF_hash[lineNumber] = rect;
			}
		}
	}
}

void ReadIFCCIRCLEPROFILEDEF(store *st, string file){
	ifstream in(file);
	string line;
	if(in){
		while(getline(in, line)){
			int Pos = 0, lineNumber;
			if(line.empty())
				continue;
			else if(line[Pos] == '#'){
				Pos++;
				lineNumber = line[Pos++] - '0';
				while(Pos != line.length()){
					if(isdigit(line[Pos])){
						lineNumber *= 10;
						lineNumber += (line[Pos++] - '0');
					}
					else
						break;
				}
			}
			else
				continue;
			if(isContain(line, "IFCCIRCLEPROFILEDEF"))
			{
				int drctNumber = 0, Dim = 0, decimalDigits = 0;
				double coordinate = 0;
				CircleProfile *circle = new CircleProfile();
				bool isDecimal = false;
				while(Pos != line.length()){
					if(line[Pos] == '#'){
						Pos++;
						while(Pos != line.length() && isdigit(line[Pos])){
							drctNumber *= 10;
							drctNumber += (line[Pos++] - '0');
						}
						circle->axis = st->IFCAXIS2PLACEMENT2D_hash[drctNumber];
						drctNumber = 0;
					}
					else if(isdigit(line[Pos])){
						while(Pos != line.length() && (isdigit(line[Pos]) || line[Pos] == '.')){
							if(isdigit(line[Pos])){
								if(!isDecimal){
									coordinate *= 10;
									coordinate += (line[Pos++] - '0');
								}
								else{
									coordinate += (line[Pos++] - '0') * pow(10.0, decimalDigits--);
								}
							}
							else{
								isDecimal = true;
								decimalDigits--;
								Pos++;
							}
						}
						circle->rad = coordinate;
						coordinate = 0;
						isDecimal = false;
						Pos++;
					}
					else
						Pos++;
				}

				double arc1 = atan(abs(circle->axis->direction1->y / circle->axis->direction1->x));
				//double arc = atan(abs(rect->axis->direction1->y / rect->axis->direction1->x));
				double arc2 = atan(abs(circle->axis->point->y / circle->axis->point->x));
				double arc = arc1 + arc2;

				double clinedLine = sqrt((circle->axis->point->x * circle->axis->point->x) + (circle->axis->point->y * circle->axis->point->y));

				circle->axis->point->x = cos(arc) * clinedLine;
				circle->axis->point->x = circle->axis->point->x >= 0? 1 : -1;
				circle->axis->point->y = sin(arc) * clinedLine;
				circle->axis->point->y = circle->axis->point->y >= 0? 1 : -1;
				circle->axis->point->is3D = false;

				circle->t->x = circle->axis->point->x;
				circle->t->y = circle->axis->point->y + circle->rad;
				circle->t->is3D = false;

				circle->b->x = circle->axis->point->x;
				circle->b->y = circle->axis->point->y - circle->rad;
				circle->b->is3D = false;

				circle->l->x = circle->axis->point->x - circle->rad;
				circle->l->y = circle->axis->point->y;
				circle->l->is3D = false;

				circle->r->x = circle->axis->point->x + circle->rad;
				circle->r->y = circle->axis->point->y;
				circle->r->is3D = false;

				std::pair<int, string> cppair1(lineNumber, "IFCCIRCLEPROFILEDEF");
				std::pair<int, CircleProfile *> cppair2(lineNumber, circle);
				st->Main_hash.insert(cppair1);
				st->IFCCIRCLEPROFILEDEF_hash.insert(cppair2);

				//st->Main_hash[lineNumber] = "IFCCIRCLEPROFILEDEF";
				//st->IFCCIRCLEPROFILEDEF_hash[lineNumber] = circle;
				//st->IFCRECTANGLEPROFILEDEF_hash[lineNumber] = rect;
			}
		}
	}
}

void ReadIFCFACEBOUND(store *st, string file){
	ifstream in(file);
	string line;
	if(in){
		while(getline(in, line)){
			int Pos = 0, lineNumber;
			if(line.empty())
				continue;
			else if(line[Pos] == '#'){
				Pos++;
				lineNumber = line[Pos++] - '0';
				while(Pos != line.length()){
					if(isdigit(line[Pos])){
						lineNumber *= 10;
						lineNumber += (line[Pos++] - '0');
					}
					else
						break;
				}
			}
			else
				continue;
			if(isContain(line, "IFCFACEBOUND"))
				{
					int loopNumber = 0;
					FaceBound *bound = new FaceBound();
					while(Pos != line.length()){
						if(line[Pos] == '#'){
							Pos++;
							while(Pos != line.length() && isdigit(line[Pos])){
								loopNumber *= 10;
								loopNumber += (line[Pos++] - '0');
							}
						}
						else
							Pos++;
					}
					bound->Loop = st->IFCPOLYLOOP_hash[loopNumber];
					std::pair<int, string> fbpair1(lineNumber, "IFCFACEBOUND");
					std::pair<int, FaceBound *> fbpair2(lineNumber, bound);
					st->Main_hash.insert(fbpair1);
					st->IFCFACEBOUND_hash.insert(fbpair2);
				}
		}
	}
}

void ReadIFCFACEOUTERBOUND(store *st, string file){
	ifstream in(file);
	string line;
	if(in){
		while(getline(in, line)){
			int Pos = 0, lineNumber;
			if(line.empty())
				continue;
			else if(line[Pos] == '#'){
				Pos++;
				lineNumber = line[Pos++] - '0';
				while(Pos != line.length()){
					if(isdigit(line[Pos])){
						lineNumber *= 10;
						lineNumber += (line[Pos++] - '0');
					}
					else
						break;
				}
			}
			else
				continue;
			if(isContain(line, "IFCFACEOUTERBOUND"))
				{
					int loopNumber = 0;
					FaceOuterBound *bound = new FaceOuterBound();
					while(Pos != line.length()){
						if(line[Pos] == '#'){
							Pos++;
							while(Pos != line.length() && isdigit(line[Pos])){
								loopNumber *= 10;
								loopNumber += (line[Pos++] - '0');
							}
						}
						else
							Pos++;
					}
					
					bound->Loop = st->IFCPOLYLOOP_hash[loopNumber];
					std::pair<int, string> fobpair1(lineNumber, "IFCFACEOUTERBOUND");
					std::pair<int, FaceOuterBound *> fobpair2(lineNumber, bound);
					st->Main_hash.insert(fobpair1);
					st->IFCFACEOUTERBOUND_hash.insert(fobpair2);
				}
		}
	}
}

void ReadIFCFACE(store *st, string file){
	ifstream in(file);
	string line;
	if(in){	
		while(getline(in, line)){
			int Pos = 0, lineNumber = 0;
			if(line.empty())
				continue;
			else if(line[Pos] == '#'){
				Pos++;
				lineNumber = line[Pos++] - '0';
				while(Pos != line.length()){
					if(isdigit(line[Pos])){
						lineNumber *= 10;
						lineNumber += (line[Pos++] - '0');
					}
					else
						break;
				}
			}
			else
				continue;
			if(isContain(line, "IFCFACE") && !isContain(line, "IFCFACEOUTERBOUND") && !isContain(line, "IFCFACEBOUND") && !isContain(line, "IFCFACETEDBREP")){
				int boundNumber = 0;
				Face *f = new Face();
				while(Pos != line.length()){
					FaceBound *Bound = new FaceBound();
					FaceOuterBound *outerBound = new FaceOuterBound();
					if(line[Pos] == '#'){
						Pos++;
						while(Pos != line.length() && isdigit(line[Pos])){
							boundNumber *= 10;
							boundNumber += (line[Pos++] - '0');
						}
						if(st->Main_hash[boundNumber] == "IFCFACEBOUND"){
							Bound = st->IFCFACEBOUND_hash[boundNumber];
							f->FaceMod = 1;
							f->Bound = Bound;
						}
						else if(st->Main_hash[boundNumber] == "IFCFACEOUTERBOUND"){
							outerBound = st->IFCFACEOUTERBOUND_hash[boundNumber];
							f->FaceMod = 0;
							f->outerBound = outerBound;
						}
						else{
							f->FaceMod = 9;
						}
					}
					else
						Pos++;
				}
				std::pair<int, string> fpair1(lineNumber, "IFCFACE");
				std::pair<int, Face *> fpair2(lineNumber, f);
				st->Main_hash.insert(fpair1);
				st->IFCFACE_hash.insert(fpair2);
			}
		}
	}
}

void ReadIFCCLOSEDSHELL(store *st, string file){
	ifstream in(file);
	string line;
	if(in){	
		while(getline(in, line)){
			int Pos = 0, lineNumber;
			if(line.empty())
				continue;
			else if(line[Pos] == '#'){
				Pos++;
				lineNumber = line[Pos++] - '0';
				while(Pos != line.length()){
					if(isdigit(line[Pos])){
						lineNumber *= 10;
						lineNumber += (line[Pos++] - '0');
					}
					else
						break;
				}
			}
			else
				continue;
			if(isContain(line, "IFCCLOSEDSHELL")){
				int faceNumber = 0;
				Face *face = new Face();
				ClosedShell *faces = new ClosedShell();
				while(Pos != line.length()){
					if(line[Pos] == '#'){
						Pos++;
						while(Pos != line.length() && isdigit(line[Pos])){
							faceNumber *= 10;
							faceNumber += (line[Pos++] - '0');
						}
						face = st->IFCFACE_hash[faceNumber];
						faces->faces.push_back(face);
						faceNumber = 0;
					}
					else
						Pos++;
				}

				std::pair<int, string> cspair1(lineNumber, "IFCCLOSEDSHELL");
				std::pair<int, ClosedShell *> cspair2(lineNumber, faces);
				st->Main_hash.insert(cspair1);
				st->IFCCLOSEDSHELL_hash.insert(cspair2);

				//st->Main_hash[lineNumber] = "IFCCLOSEDSHELL";
				//st->IFCCLOSEDSHELL_hash[lineNumber] = faces;
			}
		}
	}
}

void ReadIFCFACETEDBREP(store *st, string file){
	ifstream in(file);
	string line;
	if(in){
		while(getline(in, line)){
			int Pos = 0, lineNumber;
			if(line.empty())
				continue;
			else if(line[Pos] == '#'){
				Pos++;
				lineNumber = line[Pos++] - '0';
				while(Pos != line.length()){
					if(isdigit(line[Pos])){
						lineNumber *= 10;
						lineNumber += (line[Pos++] - '0');
					}
					else
						break;
				}
			}
			else
				continue;
			if(isContain(line, "IFCFACETEDBREP"))
				{
					int shellNumber = 0;
					FacetedBrep *fB = new FacetedBrep();
					while(Pos != line.length()){
						if(line[Pos] == '#'){
							Pos++;
							while(Pos != line.length() && isdigit(line[Pos])){
								shellNumber *= 10;
								shellNumber += (line[Pos++] - '0');
							}
						}
						else
							Pos++;
					}

					fB->Shell = st->IFCCLOSEDSHELL_hash[shellNumber];
					std::pair<int, string> fbpair1(lineNumber, "IFCFACETEDBREP");
					std::pair<int, FacetedBrep *> fbpair2(lineNumber, fB);
					st->Main_hash.insert(fbpair1);
					st->IFCFACETEDBREP_hash.insert(fbpair2);
				}
		}
	}
}

void ReadIFCEXTRUDEDAREASOLID(store *st, string file){
	ifstream in(file);
	string line;
	if(in){	
		while(getline(in, line)){
			int Pos = 0, lineNumber;
			if(line.empty())
				continue;
			else if(line[Pos] == '#'){
				Pos++;
				lineNumber = line[Pos++] - '0';
				while(Pos != line.length()){
					if(isdigit(line[Pos])){
						lineNumber *= 10;
						lineNumber += (line[Pos++] - '0');
					}
					else
						break;
				}
			}
			else
				continue;
			if(isContain(line, "IFCEXTRUDEDAREASOLID")){
				int decimalDigits = 0;
				Axis2Placement3D *Axis = new Axis2Placement3D();
				Direction *Dir = new Direction();
				double Position;
				int LineNumber = 0, ParaNumbers = 0;
				bool PositionDecimal = false;
				AreaSolid *ASolid = new AreaSolid;
				while(Pos != line.length()){
					ArbitaryClosedProfile *Profile1 = new ArbitaryClosedProfile();
					RectangleProfile *Profile2 = new RectangleProfile();
					CircleProfile *Profile3 = new CircleProfile();
					if(line[Pos] == '#'){
						Pos++;
						while(Pos != line.length() && isdigit(line[Pos])){
							LineNumber *= 10;
							LineNumber += (line[Pos++] - '0');
						}
						if(ParaNumbers == 0){
							if(st->Main_hash[LineNumber] == "IFCARBITRARYCLOSEDPROFILEDEF"){
								Profile1 = st->IFCARBITRARYCLOSEDPROFILEDEF_hash[LineNumber];
								ASolid->ProfileMod = 0;
								ASolid->Profile1 = Profile1;
							}
							else if(st->Main_hash[LineNumber] == "IFCRECTANGLEPROFILEDEF"){
								Profile2 = st->IFCRECTANGLEPROFILEDEF_hash[LineNumber];		
								ASolid->ProfileMod = 1;
								ASolid->Profile2 = Profile2;
							}
							else if(st->Main_hash[LineNumber] == "IFCCIRCLEPROFILEDEF"){
								Profile3 = st->IFCCIRCLEPROFILEDEF_hash[LineNumber];
								ASolid->ProfileMod = 2;
								ASolid->Profile3 = Profile3;
							}
							else{
								ASolid->ProfileMod = 9;
							}
						}
						else if(ParaNumbers == 1){
							Axis = st->IFCAXIS2PLACEMENT3D_hash[LineNumber];
							ASolid->Axis = Axis;
						}
						else{
							Dir = st->IFCDIRECTION_hash[LineNumber];
							ASolid->Dir = Dir;
						}
						LineNumber = 0;
						ParaNumbers++;
					}
					else if(Pos != line.length() && isdigit(line[Pos]) && ParaNumbers == 3){
						while(Pos != line.length() && (isdigit(line[Pos]) || line[Pos] == '.')){
							if(isdigit(line[Pos])){
								if(!PositionDecimal){
									LineNumber *= 10;
									LineNumber += (line[Pos++] - '0');
								}
								else{
									LineNumber += (line[Pos++] - '0') * pow(10.0, decimalDigits--);
								}
							}
							else{
								PositionDecimal = true;
								decimalDigits--;
								Pos++;
							}
						}
						Position = (double)LineNumber;
						ASolid->Position = Position;
						LineNumber = 0;
					}
					else
						Pos++;
				}

				std::pair<int, string> easpair1(lineNumber, "IFCEXTRUDEDAREASOLID");
				std::pair<int, AreaSolid *> easpair2(lineNumber, ASolid);
				st->Main_hash.insert(easpair1);
				st->IFCEXTRUDEDAREASOLID_hash.insert(easpair2);

				//st->Main_hash[lineNumber] = "IFCEXTRUDEDAREASOLID";
				//st->IFCEXTRUDEDAREASOLID_hash[lineNumber] = ASolid;
				//ReleaseProfile(ASolid);
			}
		}
	}
}

void ReadIFCGEOMETRICREPRESENTATIONCONTEXT(store *st, string file){
	ifstream in(file);
	string line;
	if(in){	
		while(getline(in, line)){
			int Pos = 0, lineNumber = 0;
			if(line.empty())
				continue;
			else if(line[Pos] == '#'){
				Pos++;
				lineNumber = line[Pos++] - '0';
				while(Pos != line.length()){
					if(isdigit(line[Pos])){
						lineNumber *= 10;
						lineNumber += (line[Pos++] - '0');
					}
					else
						break;
				}
			}
			else
				continue;
			if(isContain(line, "IFCGEOMETRICREPRESENTATIONCONTEXT")){
				int LineNumber = 0, ParaNumbers = 0;
				Axis2Placement3D *Axis = new Axis2Placement3D();
				Direction *Dir = new Direction();
				GeometricRepresentationContext *GPC = new GeometricRepresentationContext();

				while(Pos != line.length()){
					if(line[Pos] == '#'){
						Pos++;
						while(Pos != line.length() && isdigit(line[Pos])){
							LineNumber *= 10;
							LineNumber += (line[Pos++] - '0');
						}
						if(ParaNumbers == 0){
							Axis = st->IFCAXIS2PLACEMENT3D_hash[LineNumber];
							GPC->Axis = Axis;
						}
						else if(ParaNumbers == 1){
							Dir = st->IFCDIRECTION_hash[LineNumber];
							GPC->Dir = Dir;
						}
						LineNumber = 0;
						ParaNumbers++;
					}
					else
						Pos++;
				}
				std::pair<int, string> pair1(lineNumber, "IFCGEOMETRICREPRESENTATIONCONTEXT");
				std::pair<int, GeometricRepresentationContext *> pair2(lineNumber, GPC);
				st->Main_hash.insert(pair1);
				st->IFCGEOMETRICREPRESENTATIONCONTEXT_hash.insert(pair2);
			}
		}
	}
}

void ReadIFCGEOMETRICREPRESENTATIONSUBCONTEXT(store *st, string file){
	ifstream in(file);
	string line;
	if(in){	
		while(getline(in, line)){
			int Pos = 0, lineNumber = 0;
			if(line.empty())
				continue;
			else if(line[Pos] == '#'){
				Pos++;
				lineNumber = line[Pos++] - '0';
				while(Pos != line.length()){
					if(isdigit(line[Pos])){
						lineNumber *= 10;
						lineNumber += (line[Pos++] - '0');
					}
					else
						break;
				}
			}
			else
				continue;
			if(isContain(line, "IFCGEOMETRICREPRESENTATIONSUBCONTEXT")){
				int LineNumber = 0;
				GeometricRepresentationContext *GRC = new GeometricRepresentationContext();
				GeometricRepresentationSubContext *GRSC = new GeometricRepresentationSubContext();

				while(Pos != line.length()){
					if(line[Pos] == '#'){
						Pos++;
						while(Pos != line.length() && isdigit(line[Pos])){
							LineNumber *= 10;
							LineNumber += (line[Pos++] - '0');
						}
						GRC = st->IFCGEOMETRICREPRESENTATIONCONTEXT_hash[LineNumber];
						GRSC->GRC = GRC;
						LineNumber = 0;
					}
					else
						Pos++;
				}
				std::pair<int, string> pair1(lineNumber, "IFCGEOMETRICREPRESENTATIONSUBCONTEXT");
				std::pair<int, GeometricRepresentationSubContext *> pair2(lineNumber, GRSC);
				st->Main_hash.insert(pair1);
				st->IFCGEOMETRICREPRESENTATIONSUBCONTEXT_hash.insert(pair2);
			}
		}
	}
}

void ReadIFCSHAPEREPRESENTATION(store *st, string file){
	ifstream in(file);
	string line;
	if(in){	
		while(getline(in, line)){
			int Pos = 0, lineNumber = 0;
			if(line.empty())
				continue;
			else if(line[Pos] == '#'){
				Pos++;
				lineNumber = line[Pos++] - '0';
				while(Pos != line.length()){
					if(isdigit(line[Pos])){
						lineNumber *= 10;
						lineNumber += (line[Pos++] - '0');
					}
					else
						break;
				}
			}
			else
				continue;
			if(isContain(line, "IFCSHAPEREPRESENTATION")){
				int Number = 0, ParaNumbers = 0;
				ShapeRepresentation *sR = new ShapeRepresentation();
				vector<AreaSolid *> aSolid;
				aSolid.empty();
				vector<FacetedBrep *> fBs;
				fBs.empty();
				while(Pos != line.length()){

					GeometricRepresentationContext *GRC = new GeometricRepresentationContext();
					GeometricRepresentationSubContext *GRSC = new GeometricRepresentationSubContext();
					int GeometricMod = 0;
					
					PolyLine *pLine = new PolyLine();
					
					int ShapeMod = 0;

					string cubeindex = "";

					if(line[Pos] == '#'){
						AreaSolid *solid = new AreaSolid();
						FacetedBrep *fB = new FacetedBrep();
						Pos++;
						while(Pos != line.length() && isdigit(line[Pos])){
							Number *= 10;
							Number += (line[Pos++] - '0');
						}
						if(ParaNumbers == 0){
							if(st->Main_hash[Number] == "IFCGEOMETRICREPRESENTATIONCONTEXT"){
								GRC = st->IFCGEOMETRICREPRESENTATIONCONTEXT_hash[Number];
								sR->GeometricMod = 0;
								sR->GRC = GRC;
							}
							else if(st->Main_hash[Number] == "IFCGEOMETRICREPRESENTATIONSUBCONTEXT"){
								GRSC = st->IFCGEOMETRICREPRESENTATIONSUBCONTEXT_hash[Number];
								sR->GeometricMod = 1;
								sR->GRSC = GRSC;
							}
							else{
								sR->GeometricMod = 9;
							}
							ParaNumbers++;
						}
						else if(ParaNumbers == 1){
							if(st->Main_hash[Number] == "IFCEXTRUDEDAREASOLID"){
								solid = st->IFCEXTRUDEDAREASOLID_hash[Number];
								aSolid.push_back(solid);
								sR->ShapeMod = 0;
							}
							else if(st->Main_hash[Number] == "IFCPOLYLINE"){
								pLine = st->IFCPOLYLINE_hash[Number];
								sR->pLine = pLine;
								sR->ShapeMod = 1;
							}
							else if(st->Main_hash[Number] == "IFCFACETEDBREP"){
								fB = st->IFCFACETEDBREP_hash[Number];
								fBs.push_back(fB);
								sR->ShapeMod = 2;
							}
							else{
								sR->ShapeMod = 9;
							}
						}
						Number = 0;
					}
					else
						Pos++;
				}
				sR->aSolid = aSolid;
				sR->fBs= fBs;
				std::pair<int, string> sppair1(lineNumber, "IFCSHAPEREPRESENTATION");
				std::pair<int, ShapeRepresentation *> sppair2(lineNumber, sR);
				st->Main_hash.insert(sppair1);
				st->IFCSHAPEREPRESENTATION_hash.insert(sppair2);
			}
		}
	}
}


// Finish ReadIFCSHAPEREPRESENTATION

int _tmain(int argc, _TCHAR* argv[])
{
	int I = 0;
	char *c = "Hello";
	vector<char **> vc;
	vc.push_back(&c);
	c = "World";
	cout << *vc[0] << endl;

	vector<CartesianPoint *> P;
	CartesianPoint p;
	p.x = 1, p.y = 2, p.z = 3, p.is3D = true, p.cubeindex = "666";
	P.push_back(&p);
	p.x = 3, p.y = 4, p.z = 5;
	string S = P[0]->cubeindex;
	cout << P[0]->cubeindex << endl;
	//cout << *P[0].x << endl;
	//cout << &P[0].x << endl;


	store *st = new store();
	string file = "C:/Users/JLXU/Desktop/AC11-Institute-Var-2-IFC.ifc";
	ReadIFCDIRECTION(st, file);
	ReadIFCCARTESIANPOINT(st, file);
	ReadIFCAXIS2PLACEMENT3D(st, file);
	ReadIFCAXIS2PLACEMENT2D(st, file);
	ReadIFCLOCALPLACEMENT(st, file);
	ReadIFCPOLYLINE(st, file);
	ReadIFCPOLYLOOP(st, file);
	ReadIFCARBITRARYCLOSEDPROFILEDEF(st, file);
	ReadIFCRECTANGLEPROFILEDEF(st, file);
	ReadIFCCIRCLEPROFILEDEF(st, file);
	ReadIFCFACEBOUND(st, file);
	ReadIFCFACEOUTERBOUND(st, file);
	ReadIFCFACE(st, file);
	ReadIFCCLOSEDSHELL(st, file);
	ReadIFCFACETEDBREP(st, file);
	ReadIFCEXTRUDEDAREASOLID(st, file);
	ReadIFCGEOMETRICREPRESENTATIONCONTEXT(st, file);
	ReadIFCGEOMETRICREPRESENTATIONSUBCONTEXT(st, file);
	ReadIFCSHAPEREPRESENTATION(st, file);
	checkPositions(st);
	//string s = "Hello";
	//cout << s.substr(0, 2) << endl;
	//cout << c.IFCPOLYLOOP_hash[68][1] << endl;
	return 0;
}

/* Problems
	
	1. Points may be used in different places.
	2. Bounds cannot be calculated.


*/
