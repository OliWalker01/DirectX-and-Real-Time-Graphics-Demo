////////////////////////////////////////////////////////////////////////////////
// Filename: applicationclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _APPLICATIONCLASS_H_
#define _APPLICATIONCLASS_H_


/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = true; //true;
const bool VSYNC_ENABLED = true;//true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "inputclass.h"
#include "d3dclass.h"
#include "timerclass.h"
#include "positionclass.h"
#include "cameraclass.h"
#include "lightclass.h"
#include "skydomeclass.h"
#include "skydomeshaderclass.h"
#include "skyplaneclass.h"
#include "skyplaneshaderclass.h"
#include "fpsclass.h"
#include "cpuclass.h"
//#include "textclass.h"
#include "rendertextureclass.h"
#include "reflectionshaderclass.h"
#include "modelclass.h"
#include "shadermanagerclass.h"
#include "fireshaderclass.h"
#include "firemodelclass.h"
#include "guitarsoundclass.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: ApplicationClass
////////////////////////////////////////////////////////////////////////////////
class ApplicationClass
{
public:
	ApplicationClass();
	ApplicationClass(const ApplicationClass&);
	~ApplicationClass();

	bool Initialize(HINSTANCE, HWND, int, int);
	void Shutdown();
	bool Frame();

private:
	bool HandleMovementInput(float);
	void RenderRefractionToTexture();
	void RenderReflectionToTexture();
	bool Render();

private:
	InputClass* m_Input;
	D3DClass* m_Direct3D;
	TimerClass* m_Timer;
	PositionClass* m_Position;
	CameraClass* m_Camera;
	LightClass* m_Light;
	SkyDomeClass* m_SkyDome;
	SkyDomeShaderClass* m_SkyDomeShader;
	SkyPlaneClass* m_SkyPlane;
	SkyPlaneShaderClass* m_SkyPlaneShader;
	FpsClass* m_Fps;
	CpuClass* m_Cpu;
	//	TextClass* m_Text;
	RenderTextureClass* m_RefractionTexture, * m_ReflectionTexture;
	ReflectionShaderClass* m_ReflectionShader;
	ShaderManagerClass* m_ShaderManager;

	ModelClass* m_Model1;
	ModelClass* m_Model2;
	ModelClass* m_Model3;
	ModelClass* m_Model4;
	ModelClass* m_Model5;
	ModelClass* m_Model6;
	ModelClass* m_Model7;
	ModelClass* m_Model8;
	ModelClass* m_Model9;
	ModelClass* m_Model10;
	ModelClass* m_Model11;
	ModelClass* m_Model12;
	ModelClass* m_Model13;
	ModelClass* m_Model14;
	ModelClass* m_Model15;
	ModelClass* m_Model16;
	ModelClass* m_Model17;
	ModelClass* m_Model18;
	ModelClass* m_Model19;
	ModelClass* m_Model20;
	ModelClass* m_Model21;
	ModelClass* m_Model22;
	ModelClass* m_Model23;
	ModelClass* m_Model24;
	ModelClass* m_Model25;
	ModelClass* m_Model26;
	ModelClass* m_Model27;

	FireShaderClass* m_FireShader;
	FireModelClass* m_Fire;
	GuitarSoundClass* m_GuitarSound;
};

#endif