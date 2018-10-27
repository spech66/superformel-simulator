//-----------------------------------------------------------------------------
//  Main.h
//  Copyright (C) 2003 by Sebastian Pech
//  http://www.spech.de
//  - Main File -
//-----------------------------------------------------------------------------

#ifndef __MAINH__
#define __MAINH__

//-----------------------------------------------------------------------------
// Engine
//-----------------------------------------------------------------------------
#include "../lightfire3d/src/Main.h"

void Supershape3D(double m1, double n11, double n12, double n13, double theta,
					double m2, double n21, double n22, double n23, double phi,
					LF3D::Vector3 *v);
void GenerateObjectPointList();
void GenerateObjectLineList();

#endif
