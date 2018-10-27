// http://astronomy.swin.edu.au/%7Epbourke/curves/supershape/
// http://www.heise.de/newsticker/meldung/45863
// http://astronomy.swin.edu.au/~pbourke/surfaces/
// http://astronomy.swin.edu.au/~pbourke/surfaces/supershape3d/

#include "main.h"

double m1, n11, n12, n13, m2, n21, n22, n23;
GLuint ObjectDisplayList;

int main(int argc, char** argv)
{
	LF3D::CCore 			Core;
	LF3D::CGraphicDevice 	*GDevice = Core.GetGraphicDevice();
	LF3D::CInputDevice		*InputDevice = Core.GetInputDevice();
	LF3D::CCameraDevice		*CameraDevice = Core.GetCameraDevice();
	LF3D::CFontLoader		*FontLoader = Core.GetFontLoader();
	
	GDevice->Init(1, 640, 480, 32);
	GDevice->SetWindowText("Superformel 0.3 - by SPech http://www.spech.de");
	
	string Font = "";
	#if defined(LF3DPLATFORM_LINUX)
		Font = "-*-helvetica-*-*-*-*-*-180-*-*-*-*-*-*";
	#elif  defined(LF3DPLATFORM_WINDOWS)
		Font = "Arial";
	#else
		#error Win\Lin!
	#endif
	FontLoader->LoadFont(Font);
	
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);

	CameraDevice->MoveCamera(0.0f, 0.0f, 0.0f);
	CameraDevice->RotateCamera(45.0f, 0.0f, 45.0f);
	CameraDevice->ZoomCamera(24.0f);
			
	m1 = 5.0;	n11 = 0.1;	n12 = 1.7;	n13 = 1.7;
	m2 = 1.0; 	n21 = 0.3; 	n22 = 0.5; 	n23 = 0.5;
	bool Points = true;
	ObjectDisplayList = 0;
	GenerateObjectPointList();
	
	unsigned long FrameTime = SDL_GetTicks();
	unsigned long DeltaTime = 0;
	while(GDevice->IsRunning())
	{
		DeltaTime = SDL_GetTicks() - FrameTime;
		FrameTime = SDL_GetTicks();
		
		InputDevice->UpdateInput();
		bool ObjectModified = false;
		if(InputDevice->GetKeyState(SDLK_ESCAPE)) GDevice->Quit();
		if(InputDevice->GetTextInput() == "q") { m1 += 0.01; ObjectModified = true; }
		if(InputDevice->GetTextInput() == "a") { m1 -= 0.01; ObjectModified = true; }
		if(InputDevice->GetTextInput() == "w") { n11 += 0.01; ObjectModified = true; }
		if(InputDevice->GetTextInput() == "s") { n11 -= 0.01; ObjectModified = true; }
		if(InputDevice->GetTextInput() == "e") { n12 += 0.01; ObjectModified = true; }
		if(InputDevice->GetTextInput() == "d") { n12 -= 0.01; ObjectModified = true; }
		if(InputDevice->GetTextInput() == "r") { n13 += 0.01; ObjectModified = true; }
		if(InputDevice->GetTextInput() == "f") { n13 -= 0.01; ObjectModified = true; }
		if(InputDevice->GetTextInput() == "Q") { m1 += 0.1; ObjectModified = true; }
		if(InputDevice->GetTextInput() == "A") { m1 -= 0.1; ObjectModified = true; }
		if(InputDevice->GetTextInput() == "W") { n11 += 0.1; ObjectModified = true; }
		if(InputDevice->GetTextInput() == "S") { n11 -= 0.1; ObjectModified = true; }
		if(InputDevice->GetTextInput() == "E") { n12 += 0.1; ObjectModified = true; }
		if(InputDevice->GetTextInput() == "D") { n12 -= 0.1; ObjectModified = true; }
		if(InputDevice->GetTextInput() == "R") { n13 += 0.1; ObjectModified = true; }
		if(InputDevice->GetTextInput() == "F") { n13 -= 0.1; ObjectModified = true; }
		
		if(InputDevice->GetTextInput() == "z") { m2 += 0.01; ObjectModified = true; }
		if(InputDevice->GetTextInput() == "h") { m2 -= 0.01; ObjectModified = true; }
		if(InputDevice->GetTextInput() == "u") { n21 += 0.01; ObjectModified = true; }
		if(InputDevice->GetTextInput() == "j") { n21 -= 0.01; ObjectModified = true; }
		if(InputDevice->GetTextInput() == "i") { n22 += 0.01; ObjectModified = true; }
		if(InputDevice->GetTextInput() == "k") { n22 -= 0.01; ObjectModified = true; }
		if(InputDevice->GetTextInput() == "o") { n23 += 0.01; ObjectModified = true; }
		if(InputDevice->GetTextInput() == "l") { n23 -= 0.01; ObjectModified = true; }
		if(InputDevice->GetTextInput() == "Z") { m2 += 0.1; ObjectModified = true; }
		if(InputDevice->GetTextInput() == "H") { m2 -= 0.1; ObjectModified = true; }
		if(InputDevice->GetTextInput() == "U") { n21 += 0.1; ObjectModified = true; }
		if(InputDevice->GetTextInput() == "J") { n21 -= 0.1; ObjectModified = true; }
		if(InputDevice->GetTextInput() == "I") { n22 += 0.1; ObjectModified = true; }
		if(InputDevice->GetTextInput() == "K") { n22 -= 0.1; ObjectModified = true; }
		if(InputDevice->GetTextInput() == "O") { n23 += 0.1; ObjectModified = true; }
		if(InputDevice->GetTextInput() == "L") { n23 -= 0.1; ObjectModified = true; }
		
		if(InputDevice->GetKeyState(SDLK_UP))	CameraDevice->ZoomCamera(DeltaTime * -0.01f);
		if(InputDevice->GetKeyState(SDLK_DOWN))	CameraDevice->ZoomCamera(DeltaTime * 0.01f);
		if(InputDevice->GetKeyState(SDLK_LEFT))	CameraDevice->RotateCamera(0.0f, DeltaTime * 0.1f, 0.0f);
		if(InputDevice->GetKeyState(SDLK_RIGHT))CameraDevice->RotateCamera(0.0f, DeltaTime * -0.1f, 0.0f);
		if(!InputDevice->GetKeyState(SDLK_LEFT) && !InputDevice->GetKeyState(SDLK_RIGHT))
			CameraDevice->RotateCamera(0.0f, DeltaTime * 0.1f, 0.0f);
			
		if(InputDevice->GetTextInput() == " ") { Points = !Points; ObjectModified = true; }
		
		if(ObjectModified && Points)
			GenerateObjectPointList();
		else if(ObjectModified && !Points)
			GenerateObjectLineList();
		
						
		GDevice->BeginRender();
		GDevice->SetPerspectiveView();
		CameraDevice->UpdateObjectAlignedCamera();
		
		glCallList(ObjectDisplayList);
		
		GDevice->SetOrthoView();
		char FPS[256];
		glColor3ub(255, 255, 255);
		sprintf(FPS, "FPS: %i", GDevice->GetFPS());
		FontLoader->SetPosition(4, 18);
		FontLoader->PrintText(Font, FPS);
		sprintf(FPS, "1: m: %f - n1: %f - n2: %f - n3: %f ", m1, n11, n12, n13);
		FontLoader->SetPosition(4, 36);
		FontLoader->PrintText(Font, FPS);
		sprintf(FPS, "2: m: %f - n1: %f - n2: %f - n3: %f ", m2, n21, n22, n23);
		FontLoader->SetPosition(4, 54);
		FontLoader->PrintText(Font, FPS);
				
		GDevice->EndRender();
	}

	return 0;
}

void Supershape3D(double m1, double n11, double n12, double n13, double theta,
					double m2, double n21, double n22, double n23, double phi,
					LF3D::Vector3 *v)
{
	double r1, r2;
	double t11, t12, t21, t22;
	double a1 = 1.0, b1 = 1.0;
	double a2 = 1.0, b2 = 1.0;
	
	t11 = cos(m1 * theta / 4) / a1;
	t11 = abs(t11);
	t11 = pow(t11,n12);
	
	t12 = sin(m1 * theta / 4) / b1;
	t12 = abs(t12);
	t12 = pow(t12,n13);

	t21 = cos(m2 * phi / 4) / a2;
	t21 = abs(t21);
	t21 = pow(t21,n22);
	
	t22 = sin(m2 * phi / 4) / b2;
	t22 = abs(t22);
	t22 = pow(t22,n23);
		
	r1 = pow(t11 + t12, 1 / n11);
	r2 = pow(t21 + t22, 1 / n21);

	r1 = 1 / r1;
	r2 = 1 / r2;
	v->x = r1*cos(theta) * r2*cos(phi);
	v->y = r1*sin(theta) * r2*cos(phi);
	v->z = r2*sin(phi);
}

void GenerateObjectPointList()
{
	if(ObjectDisplayList)	glDeleteLists(ObjectDisplayList, 1);
	ObjectDisplayList = glGenLists(1);
	glNewList(ObjectDisplayList, GL_COMPILE);

	glBegin(GL_POINTS);
	for(int h = -100 ; h <= 100; h++)
	{
		for(int i = -100 ; i <= 100; i++)
		{
			glColor3ub(i*3+50, h*3+50, 255);
			LF3D::Vector3 TempVec;
			double theta = h * (2*PI) / 201;
			double phi = i * (PI) / 201;
			Supershape3D(m1, n11, n12, n13, theta, m2, n21, n22, n23, phi, &TempVec);
			glVertex3f(TempVec.x*10.f, TempVec.y*10.f, TempVec.z*10.0f);
		}
	}
	glEnd();
		
	glEndList();
}

void GenerateObjectLineList()
{
	if(ObjectDisplayList)	glDeleteLists(ObjectDisplayList, 1);
	ObjectDisplayList = glGenLists(1);
	glNewList(ObjectDisplayList, GL_COMPILE);

	glBegin(GL_LINES);
	for(int h = -50 ; h <= 50; h++)
	{
		for(int i = -50 ; i <= 50; i++)
		{
			glColor3ub(i*3+50, h*3+50, 255);
			LF3D::Vector3 TempVec;
			double theta = h * (2*PI) / 101;
			double phi = i * (PI) / 101;
			Supershape3D(m1, n11, n12, n13, theta, m2, n21, n22, n23, phi, &TempVec);
			glVertex3f(TempVec.x*10.f, TempVec.y*10.f, TempVec.z*10.0f);
			
			theta = (h+1) * (2*PI) / 101;
			phi = (i+1) * (PI) / 101;
			Supershape3D(m1, n11, n12, n13, theta, m2, n21, n22, n23, phi, &TempVec);
			glVertex3f(TempVec.x*10.f, TempVec.y*10.f, TempVec.z*10.0f);
		}
	}
	glEnd();

	glEndList();
}
