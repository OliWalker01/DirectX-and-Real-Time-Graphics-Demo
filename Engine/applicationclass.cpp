////////////////////////////////////////////////////////////////////////////////
// Filename: applicationclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "applicationclass.h"


ApplicationClass::ApplicationClass()
{
	m_Input = 0;
	m_Direct3D = 0;
	m_Timer = 0;
	m_Position = 0;
	m_Camera = 0;
	m_Light = 0;
	m_SkyDome = 0;
	m_SkyDomeShader = 0;
	m_SkyPlane = 0;
	m_SkyPlaneShader = 0;
	m_Fps = 0;
	m_Cpu = 0;
	//m_FontShader = 0;
	//m_Text = 0;
	m_RefractionTexture = 0;
	m_ReflectionTexture = 0;
	m_ReflectionShader = 0;

	m_Model1 = 0;
	m_Model2 = 0;
	m_Model3 = 0;
	m_Model4 = 0;
	m_Model5 = 0;
	m_Model6 = 0;
	m_Model7 = 0;
	m_Model8 = 0;
	m_Model9 = 0;
	m_Model10 = 0;
	m_Model11 = 0;
	m_Model12 = 0;
	m_Model13 = 0;
	m_Model14 = 0;
	m_Model15 = 0;
	m_Model16 = 0;
	m_Model17 = 0;
	m_Model18 = 0;
	m_Model19 = 0;
	m_Model20 = 0;
	m_Model21 = 0;
	m_Model22 = 0;
	m_Model23 = 0;
	m_Model24 = 0;
	m_Model25 = 0;
	m_Model26 = 0;
	m_Model27 = 0;

	m_FireShader = 0;
	m_Fire = 0;
	m_GuitarSound = 0;
}


ApplicationClass::ApplicationClass(const ApplicationClass& other)
{
}


ApplicationClass::~ApplicationClass()
{
}


bool ApplicationClass::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	bool result;
	XMMATRIX baseViewMatrix;
	char videoCard[128];
	int videoMemory;

	
	// Create the input object.  The input object will be used to handle reading the keyboard and mouse input from the user.
	m_Input = new InputClass;
	if(!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	result = m_Input->Initialize(hinstance, hwnd, screenWidth, screenHeight);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}

	// Create the Direct3D object.
	m_Direct3D = new D3DClass;
	if(!m_Direct3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR); //FULL_SCREEN
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize DirectX 11.", L"Error", MB_OK);
		return false;
	}

	// Retrieve the video card information.
	m_Direct3D->GetVideoCardInfo(videoCard, videoMemory);

	// Create the shader manager object.
	m_ShaderManager = new ShaderManagerClass;
	if (!m_ShaderManager)
	{
		return false;
	}

	// Initialize the shader manager object.
	result = m_ShaderManager->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the shader manager object.", L"Error", MB_OK);
		return false;
	}

	// Create the timer object.
	m_Timer = new TimerClass;
	if(!m_Timer)
	{
		return false;
	}

	// Initialize the timer object.
	result = m_Timer->Initialize();
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the timer object.", L"Error", MB_OK);
		return false;
	}

	// Create the position object.
	m_Position = new PositionClass;
	if(!m_Position)
	{
		return false;
	}

	// Set the initial position and rotation of the viewer.
	m_Position->SetPosition(0.0f, 0.0f, -30.0f);
	m_Position->SetRotation(0.0f, 0.0f, 0.0f);
	
	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Initialize a base view matrix with the camera for 2D user interface rendering.
	m_Camera->SetPosition(0.0f, 0.0f, -1.0f);
	m_Camera->GenerateBaseViewMatrix();
	m_Camera->GetBaseViewMatrix(baseViewMatrix);

	// Create the light object.
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.5f, -0.75f, 0.25f);

	// Create the sky dome object.
	m_SkyDome = new SkyDomeClass;
	if(!m_SkyDome)
	{
		return false;
	}

	// Initialize the sky dome object.
	result = m_SkyDome->Initialize(m_Direct3D->GetDevice());
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky dome object.", L"Error", MB_OK);
		return false;
	}

	// Create the sky dome shader object.
	m_SkyDomeShader = new SkyDomeShaderClass;
	if(!m_SkyDomeShader)
	{
		return false;
	}

	// Initialize the sky dome shader object.
	result = m_SkyDomeShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky dome shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the sky plane object.
	m_SkyPlane = new SkyPlaneClass;
	if(!m_SkyPlane)
	{
		return false;
	}

	// Initialize the sky plane object.
	result = m_SkyPlane->Initialize(m_Direct3D->GetDevice(), L"../Engine/data/cloud001.dds", L"../Engine/data/perturb001.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky plane object.", L"Error", MB_OK);
		return false;
	}

	// Create the sky plane shader object.
	m_SkyPlaneShader = new SkyPlaneShaderClass;
	if(!m_SkyPlaneShader)
	{
		return false;
	}

	// Initialize the sky plane shader object.
	result = m_SkyPlaneShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky plane shader object.", L"Error", MB_OK);
		return false;
	}
	
	// Create the fps object.
	m_Fps = new FpsClass;
	if(!m_Fps)
	{
		return false;
	}

	// Initialize the fps object.
	m_Fps->Initialize();

	// Create the cpu object.
	m_Cpu = new CpuClass;
	if(!m_Cpu)
	{
		return false;
	}

	// Initialize the cpu object.
	m_Cpu->Initialize();
	/*
	// Create the font shader object.
	m_FontShader = new FontShaderClass;
	if(!m_FontShader)
	{
		return false;
	}

	// Initialize the font shader object.
	result = m_FontShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the font shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the text object.
	m_Text = new TextClass;
	if(!m_Text)
	{
		return false;
	}

	// Initialize the text object.
	result = m_Text->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}

	// Set the video card information in the text object.
	result = m_Text->SetVideoCardInfo(videoCard, videoMemory, m_Direct3D->GetDeviceContext());
	if(!result)
	{
		MessageBox(hwnd, L"Could not set video card info in the text object.", L"Error", MB_OK);
		return false;
	}
	//*/
	// Create the refraction render to texture object.
	m_RefractionTexture = new RenderTextureClass;
	if(!m_RefractionTexture)
	{
		return false;
	}

	// Initialize the refraction render to texture object.
	result = m_RefractionTexture->Initialize(m_Direct3D->GetDevice(), screenWidth, screenHeight, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the refraction render to texture object.", L"Error", MB_OK);
		return false;
	}

	// Create the reflection render to texture object.
	m_ReflectionTexture = new RenderTextureClass;
	if(!m_ReflectionTexture)
	{
		return false;
	}

	// Initialize the reflection render to texture object.
	result = m_ReflectionTexture->Initialize(m_Direct3D->GetDevice(), screenWidth, screenHeight, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the reflection render to texture object.", L"Error", MB_OK);
		return false;
	}

	// Create the reflection shader object.
	m_ReflectionShader = new ReflectionShaderClass;
	if(!m_ReflectionShader)
	{
		return false;
	}

	// Initialize the reflection shader object.
	result = m_ReflectionShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the reflection shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the f1 car model object.
	m_Model1 = new ModelClass;
	if (!m_Model1)
	{
		return false;
	}

	// Initialize the F1 car object.
	result = m_Model1->Initialize(m_Direct3D->GetDevice(), "../Engine/data/Assignment/F1Car.txt", L"../Engine/data/Assignment/Textures/F1Car.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the first model object.", L"Error", MB_OK);
		return false;
	}

	// Create the tower model object.
	m_Model2 = new ModelClass;
	if (!m_Model2)
	{
		return false;
	}

	// Initialize the tower model object.
	result = m_Model2->Initialize(m_Direct3D->GetDevice(), "../Engine/data/Assignment/Tower.txt", L"../Engine/data/Assignment/Textures/Tower.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the second model object.", L"Error", MB_OK);
		return false;
	}

	// Create the helicopter model object.
	m_Model3 = new ModelClass;
	if (!m_Model3)
	{
		return false;
	}

	// Initialize the Helicopter model object.
	result = m_Model3->Initialize(m_Direct3D->GetDevice(), "../Engine/data/Assignment/Helicopter.txt", L"../Engine/data/Assignment/Textures/Helicopter.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the third model object.", L"Error", MB_OK);
		return false;
	}

	// Create the Track model object.
	m_Model4 = new ModelClass;
	if (!m_Model4)
	{
		return false;
	}


	// Initialize the Track model object.
	result = m_Model4->Initialize(m_Direct3D->GetDevice(), "../Engine/data/Assignment/Track.txt", L"../Engine/data/Assignment/Textures/Track.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize fourth model object.", L"Error", MB_OK);
		return false;
	}

	// Create the grand stand model object.
	m_Model5 = new ModelClass;
	if (!m_Model5)
	{
		return false;
	}


	// Initialize the Grand Stand model object.
	result = m_Model5->Initialize(m_Direct3D->GetDevice(), "../Engine/data/Assignment/GrandStand.txt", L"../Engine/data/Assignment/Textures/GrandStand.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize fifth model object.", L"Error", MB_OK);
		return false;
	}

	// Create the bedroom wall model object.
	m_Model6 = new ModelClass;
	if (!m_Model6)
	{
		return false;
	}


	// Initialize the Bedroom Wall model object.
	result = m_Model6->Initialize(m_Direct3D->GetDevice(), "../Engine/data/Assignment/BedroomWalls.txt", L"../Engine/data/Assignment/Textures/BedroomWalls.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize sixth model object.", L"Error", MB_OK);
		return false;
	}

	// Create the bedroom floor model object.
	m_Model7 = new ModelClass;
	if (!m_Model7)
	{
		return false;
	}


	// Initialize the Bedroom Floor model object.
	result = m_Model7->Initialize(m_Direct3D->GetDevice(), "../Engine/data/Assignment/BedroomFloor.txt", L"../Engine/data/Assignment/Textures/BedroomFloor.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize seventh model object.", L"Error", MB_OK);
		return false;
	}

	// Create the Door model object.
	m_Model8 = new ModelClass;
	if (!m_Model8)
	{
		return false;
	}


	// Initialize the Door model object.
	result = m_Model8->Initialize(m_Direct3D->GetDevice(), "../Engine/data/Assignment/Door.txt", L"../Engine/data/Assignment/Textures/Door.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize eighth model object.", L"Error", MB_OK);
		return false;
	}

	// Create the Bed model object.
	m_Model9 = new ModelClass;
	if (!m_Model9)
	{
		return false;
	}


	// Initialize the Bed model object.
	result = m_Model9->Initialize(m_Direct3D->GetDevice(), "../Engine/data/Assignment/Bed.txt", L"../Engine/data/Assignment/Textures/Bed.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize nineth model object.", L"Error", MB_OK);
		return false;
	}

	// Create the Bedside Table model object.
	m_Model10 = new ModelClass;
	if (!m_Model10)
	{
		return false;
	}


	// Initialize the Bedside Table model object.
	result = m_Model10->Initialize(m_Direct3D->GetDevice(), "../Engine/data/Assignment/BedsideTable.txt", L"../Engine/data/Assignment/Textures/BedsideTable.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize tenth model object.", L"Error", MB_OK);
		return false;
	}

	// Create the TV model object.
	m_Model11 = new ModelClass;
	if (!m_Model11)
	{
		return false;
	}


	// Initialize the TV model object.
	result = m_Model11->Initialize(m_Direct3D->GetDevice(), "../Engine/data/Assignment/TV.txt", L"../Engine/data/Assignment/Textures/TV.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize eleventh model object.", L"Error", MB_OK);
		return false;
	}

	// Create the Drawer object.
	m_Model12 = new ModelClass;
	if (!m_Model12)
	{
		return false;
	}


	// Initialize the Drawer model object.
	result = m_Model12->Initialize(m_Direct3D->GetDevice(), "../Engine/data/Assignment/Drawers.txt", L"../Engine/data/Assignment/Textures/Drawers.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize twelveth model object.", L"Error", MB_OK);
		return false;
	}

	// Create the Desk object.
	m_Model13 = new ModelClass;
	if (!m_Model13)
	{
		return false;
	}


	// Initialize the Desk model object.
	result = m_Model13->Initialize(m_Direct3D->GetDevice(), "../Engine/data/Assignment/Desk.txt", L"../Engine/data/Assignment/Textures/Desk.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize thirteenth model object.", L"Error", MB_OK);
		return false;
	}

	// Create the Monitors object.
	m_Model14 = new ModelClass;
	if (!m_Model14)
	{
		return false;
	}


	// Initialize the Desk model object.
	result = m_Model14->Initialize(m_Direct3D->GetDevice(), "../Engine/data/Assignment/Monitors.txt", L"../Engine/data/Assignment/Textures/Monitors.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize fourteenth model object.", L"Error", MB_OK);
		return false;
	}

	// Create the PC object.
	m_Model15 = new ModelClass;
	if (!m_Model15)
	{
		return false;
	}


	// Initialize the PC model object.
	result = m_Model15->Initialize(m_Direct3D->GetDevice(), "../Engine/data/Assignment/PC.txt", L"../Engine/data/Assignment/Textures/PC.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize fifthteenth model object.", L"Error", MB_OK);
		return false;
	}

	// Create the Keyboard object.
	m_Model16 = new ModelClass;
	if (!m_Model16)
	{
		return false;
	}


	// Initialize the Keyboard object.
	result = m_Model16->Initialize(m_Direct3D->GetDevice(), "../Engine/data/Assignment/Keyboard.txt", L"../Engine/data/Assignment/Textures/Keyboard.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize sixteenth model object.", L"Error", MB_OK);
		return false;
	}

	// Create the Mouse object.
	m_Model17 = new ModelClass;
	if (!m_Model17)
	{
		return false;
	}


	// Initialize the Keyboard object.
	result = m_Model17->Initialize(m_Direct3D->GetDevice(), "../Engine/data/Assignment/Mouse.txt", L"../Engine/data/Assignment/Textures/Mouse.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize seventeenth model object.", L"Error", MB_OK);
		return false;
	}

	// Create the Chair object.
	m_Model18 = new ModelClass;
	if (!m_Model18)
	{
		return false;
	}


	// Initialize the Chair object.
	result = m_Model18->Initialize(m_Direct3D->GetDevice(), "../Engine/data/Assignment/Chair.txt", L"../Engine/data/Assignment/Textures/Chair.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize eighteenth model object.", L"Error", MB_OK);
		return false;
	}

	// Create the Lamp object.
	m_Model19 = new ModelClass;
	if (!m_Model19)
	{
		return false;
	}


	// Initialize the Lamp object.
	result = m_Model19->Initialize(m_Direct3D->GetDevice(), "../Engine/data/Assignment/Lamp.txt", L"../Engine/data/Assignment/Textures/Lamp.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize nineteenth model object.", L"Error", MB_OK);
		return false;
	}

	// Create the Guitar object.
	m_Model20 = new ModelClass;
	if (!m_Model20)
	{
		return false;
	}


	// Initialize the Guitar object.
	result = m_Model20->Initialize(m_Direct3D->GetDevice(), "../Engine/data/Assignment/Guitar.txt", L"../Engine/data/Assignment/Textures/Guitar.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize twentieth model object.", L"Error", MB_OK);
		return false;
	}

	// Create the Rug object.
	m_Model21 = new ModelClass;
	if (!m_Model21)
	{
		return false;
	}


	// Initialize the Rug object.
	result = m_Model21->Initialize(m_Direct3D->GetDevice(), "../Engine/data/Assignment/Rug.txt", L"../Engine/data/Assignment/Textures/Rug.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize twenty-first model object.", L"Error", MB_OK);
		return false;
	}

	// Create the Xbox object.
	m_Model22 = new ModelClass;
	if (!m_Model22)
	{
		return false;
	}


	// Initialize the Xbox object.
	result = m_Model22->Initialize(m_Direct3D->GetDevice(), "../Engine/data/Assignment/Xbox.txt", L"../Engine/data/Assignment/Textures/Xbox.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize twenty-second model object.", L"Error", MB_OK);
		return false;
	}

	// Create the Remote object.
	m_Model23 = new ModelClass;
	if (!m_Model23)
	{
		return false;
	}


	// Initialize the Remote object.
	result = m_Model23->Initialize(m_Direct3D->GetDevice(), "../Engine/data/Assignment/Remote.txt", L"../Engine/data/Assignment/Textures/Remote.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize twenty-third model object.", L"Error", MB_OK);
		return false;
	}

	// Create the Ceiling Object.
	m_Model24 = new ModelClass;
	if (!m_Model24)
	{
		return false;
	}


	// Initialize the Ceiling object.
	result = m_Model24->Initialize(m_Direct3D->GetDevice(), "../Engine/data/Assignment/Ceiling.txt", L"../Engine/data/Assignment/Textures/Ceiling.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize twenty-fourth model object.", L"Error", MB_OK);
		return false;
	}

	// Create the Ceiling Fan Object.
	m_Model25 = new ModelClass;
	if (!m_Model25)
	{
		return false;
	}


	// Initialize the Ceiling Fan object.
	result = m_Model25->Initialize(m_Direct3D->GetDevice(), "../Engine/data/Assignment/CeilingFan.txt", L"../Engine/data/Assignment/Textures/CeilingFan.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize twenty-fifth model object.", L"Error", MB_OK);
		return false;
	}

	// Create the Lamp On Object.
	m_Model26 = new ModelClass;
	if (!m_Model26)
	{
		return false;
	}


	// Initialize the Lamp On object.
	result = m_Model26->Initialize(m_Direct3D->GetDevice(), "../Engine/data/Assignment/Lamp.txt", L"../Engine/data/Assignment/Textures/LampOn.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize twenty-sixth model object.", L"Error", MB_OK);
		return false;
	}

	// Create the Candle Object.
	m_Model27 = new ModelClass;
	if (!m_Model27)
	{
		return false;
	}

	// Initialize the Candle object.
	result = m_Model27->Initialize(m_Direct3D->GetDevice(), "../Engine/data/Assignment/Candle.txt", L"../Engine/data/Assignment/Textures/Candle.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize twenty-seventh model object.", L"Error", MB_OK);
		return false;
	}

	// Create the Fire Object.
	m_Fire = new FireModelClass;
	if (!m_Fire)
	{
		return false;
	}

	// Initialize the fire object.
	result = m_Fire->Initialize(m_Direct3D->GetDevice(), "../Engine/data/Assignment/Fire/square.txt", L"../Engine/data/Assignment/Fire/fire01.dds",
		L"../Engine/data/Assignment/Fire/noise01.dds", L"../Engine/data/Assignment/Fire/alpha01.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the fire model object.", L"Error", MB_OK);
		return false;
	}
	
	// Create the fire shader object.
	m_FireShader = new FireShaderClass;
	if (!m_FireShader)
	{
		return false;
	}

	// Initialize the fire shader object.
	result = m_FireShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the fire shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the guitar sound object.
	m_GuitarSound = new GuitarSoundClass;
	if (!m_GuitarSound)
	{
		return false;
	}

	// Initialize the guitar sound object.
	result = m_GuitarSound->Initialize(hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the guitar sound class object.", L"Error", MB_OK);
		return false;
	}

	return true;
}


void ApplicationClass::Shutdown()
{
	// Release the guitar sound object.
	if (m_GuitarSound)
	{
		m_GuitarSound->Shutdown();
		delete m_GuitarSound;
		m_GuitarSound = 0;
	}

	// Release the fire shader object.
	if (m_FireShader)
	{
		m_FireShader->Shutdown();
		delete m_FireShader;
		m_FireShader = 0;
	}

	// Release the Fire objects.
	if (m_Fire)
	{
		m_Fire->Shutdown();
		delete m_Fire;
		m_Fire = 0;
	}

	// Release the model objects.
	if (m_Model1)
	{
		m_Model1->Shutdown();
		delete m_Model1;
		m_Model1 = 0;
	}

	if (m_Model2)
	{
		m_Model2->Shutdown();
		delete m_Model2;
		m_Model2 = 0;
	}

	if (m_Model3)
	{
		m_Model3->Shutdown();
		delete m_Model3;
		m_Model3 = 0;
	}

	if (m_Model4)
	{
		m_Model4->Shutdown();
		delete m_Model4;
		m_Model4 = 0;
	}

	if (m_Model5)
	{
		m_Model5->Shutdown();
		delete m_Model5;
		m_Model5 = 0;
	}

	if (m_Model6)
	{
		m_Model6->Shutdown();
		delete m_Model6;
		m_Model6 = 0;
	}

	if (m_Model7)
	{
		m_Model7->Shutdown();
		delete m_Model7;
		m_Model7 = 0;
	}

	if (m_Model8)
	{
		m_Model8->Shutdown();
		delete m_Model8;
		m_Model8 = 0;
	}

	if (m_Model9)
	{
		m_Model9->Shutdown();
		delete m_Model9;
		m_Model9 = 0;
	}

	if (m_Model10)
	{
		m_Model10->Shutdown();
		delete m_Model10;
		m_Model10 = 0;
	}

	if (m_Model11)
	{
		m_Model11->Shutdown();
		delete m_Model11;
		m_Model11 = 0;
	}

	if (m_Model12)
	{
		m_Model12->Shutdown();
		delete m_Model12;
		m_Model12 = 0;
	}

	if (m_Model13)
	{
		m_Model13->Shutdown();
		delete m_Model13;
		m_Model13 = 0;
	}

	if (m_Model14)
	{
		m_Model14->Shutdown();
		delete m_Model14;
		m_Model14 = 0;
	}

	if (m_Model15)
	{
		m_Model15->Shutdown();
		delete m_Model15;
		m_Model15 = 0;
	}

	if (m_Model16)
	{
		m_Model16->Shutdown();
		delete m_Model16;
		m_Model16 = 0;
	}

	if (m_Model17)
	{
		m_Model17->Shutdown();
		delete m_Model17;
		m_Model17 = 0;
	}

	if (m_Model18)
	{
		m_Model18->Shutdown();
		delete m_Model18;
		m_Model18 = 0;
	}

	if (m_Model19)
	{
		m_Model19->Shutdown();
		delete m_Model19;
		m_Model19 = 0;
	}

	if (m_Model20)
	{
		m_Model20->Shutdown();
		delete m_Model20;
		m_Model20 = 0;
	}

	if (m_Model21)
	{
		m_Model21->Shutdown();
		delete m_Model21;
		m_Model21 = 0;
	}

	if (m_Model22)
	{
		m_Model22->Shutdown();
		delete m_Model22;
		m_Model22 = 0;
	}

	if (m_Model23)
	{
		m_Model23->Shutdown();
		delete m_Model23;
		m_Model23 = 0;
	}

	if (m_Model24)
	{
		m_Model24->Shutdown();
		delete m_Model24;
		m_Model24 = 0;
	}

	if (m_Model25)
	{
		m_Model25->Shutdown();
		delete m_Model25;
		m_Model25 = 0;
	}

	if (m_Model26)
	{
		m_Model26->Shutdown();
		delete m_Model26;
		m_Model26 = 0;
	}

	if (m_Model27)
	{
		m_Model27->Shutdown();
		delete m_Model27;
		m_Model27 = 0;
	}

	// Release the shader manager object.
	if (m_ShaderManager)
	{
		m_ShaderManager->Shutdown();
		delete m_ShaderManager;
		m_ShaderManager = 0;
	}

	// Release the reflection shader object.
	if(m_ReflectionShader)
	{
		m_ReflectionShader->Shutdown();
		delete m_ReflectionShader;
		m_ReflectionShader = 0;
	}

	// Release the reflection render to texture object.
	if(m_ReflectionTexture)
	{
		m_ReflectionTexture->Shutdown();
		delete m_ReflectionTexture;
		m_ReflectionTexture = 0;
	}

	// Release the refraction render to texture object.
	if(m_RefractionTexture)
	{
		m_RefractionTexture->Shutdown();
		delete m_RefractionTexture;
		m_RefractionTexture = 0;
	}
	/*
	// Release the text object.
	if(m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}

	// Release the font shader object.
	if(m_FontShader)
	{
		m_FontShader->Shutdown();
		delete m_FontShader;
		m_FontShader = 0;
	}
	//*/
	// Release the cpu object.
	if(m_Cpu)
	{
		m_Cpu->Shutdown();
		delete m_Cpu;
		m_Cpu = 0;
	}

	// Release the fps object.
	if(m_Fps)
	{
		delete m_Fps;
		m_Fps = 0;
	}
		
	// Release the sky plane shader object.
	if(m_SkyPlaneShader)
	{
		m_SkyPlaneShader->Shutdown();
		delete m_SkyPlaneShader;
		m_SkyPlaneShader = 0;
	}

	// Release the sky plane object.
	if(m_SkyPlane)
	{
		m_SkyPlane->Shutdown();
		delete m_SkyPlane;
		m_SkyPlane = 0;
	}

	// Release the sky dome shader object.
	if(m_SkyDomeShader)
	{
		m_SkyDomeShader->Shutdown();
		delete m_SkyDomeShader;
		m_SkyDomeShader = 0;
	}

	// Release the sky dome object.
	if(m_SkyDome)
	{
		m_SkyDome->Shutdown();
		delete m_SkyDome;
		m_SkyDome = 0;
	}
	
	// Release the light object.
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}
	
	// Release the position object.
	if(m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}

	// Release the timer object.
	if(m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}

	// Release the Direct3D object.
	if(m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = 0;
	}

	// Release the input object.
	if(m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = 0;
	}

	return;
}


bool ApplicationClass::Frame()
{
	bool result;

	// Update the system stats.
	m_Timer->Frame();
	m_Fps->Frame();
	m_Cpu->Frame();

	// Read the user input.
	result = m_Input->Frame();
	if(!result)
	{
		return false;
	}
	
	// Check if the user pressed escape and wants to exit the application.
	if(m_Input->IsEscapePressed() == true)
	{
		return false;
	}

	// Do the frame input processing.
	result = HandleMovementInput(m_Timer->GetTime());
	if(!result)
	{
		return false;
	}
	/*
	// Update the FPS value in the text object.
	result = m_Text->SetFps(m_Fps->GetFps(), m_Direct3D->GetDeviceContext());
	if(!result)
	{
		return false;
	}
	
	// Update the CPU usage value in the text object.
	result = m_Text->SetCpu(m_Cpu->GetCpuPercentage(), m_Direct3D->GetDeviceContext());
	if(!result)
	{
		return false;
	}
	//*/

	// Do the sky plane frame processing.
	m_SkyPlane->Frame();

	// Render the refraction of the scene to a texture.
	RenderRefractionToTexture();

	// Render the reflection of the scene to a texture.
	RenderReflectionToTexture();

	// Render the graphics.
	result = Render();
	if(!result)
	{
		return false;
	}

	return result;
}


bool ApplicationClass::HandleMovementInput(float frameTime)
{
	bool keyDown, result;
	float posX, posY, posZ, rotX, rotY, rotZ;


	// Set the frame time for calculating the updated position.
	m_Position->SetFrameTime(frameTime);

	// Handle the input.
	keyDown = m_Input->IsLeftPressed();
	m_Position->TurnLeft(keyDown);

	keyDown = m_Input->IsRightPressed();
	m_Position->TurnRight(keyDown);

	keyDown = m_Input->IsUpPressed();
	m_Position->MoveForward(keyDown);

	keyDown = m_Input->IsDownPressed();
	m_Position->MoveBackward(keyDown);

	keyDown = m_Input->IsAPressed();
	m_Position->MoveUpward(keyDown);

	keyDown = m_Input->IsZPressed();
	m_Position->MoveDownward(keyDown);

	keyDown = m_Input->IsPgUpPressed();
	m_Position->LookUpward(keyDown);

	keyDown = m_Input->IsPgDownPressed();
	m_Position->LookDownward(keyDown);

	keyDown = m_Input->IsF1Pressed();
	m_Position->grandStandCamera(keyDown);

	keyDown = m_Input->IsF2Pressed();
	m_Position->towerCamera(keyDown);
	
	keyDown = m_Input->IsFPressed();
	m_Position->setFanSpinning(keyDown);

	keyDown = m_Input->IsCPressed();
	m_Position->setCarSpinning(keyDown);

	keyDown = m_Input->IsLPressed();
	m_Position->setIsLightOn(keyDown);

	keyDown = m_Input->IsWPressed();
	m_Position->sprintForward(keyDown);

	keyDown = m_Input->IsSPressed();
	m_Position->sprintBackwards(keyDown);

	keyDown = m_Input->IsGPressed();
	m_GuitarSound->PlayWaveFile(keyDown);

	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);

	// Set the position of the camera.
	m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetRotation(rotX, rotY, rotZ);

	/*
	// Update the position values in the text object.
	result = m_Text->SetCameraPosition(posX, posY, posZ, m_Direct3D->GetDeviceContext());
	if(!result)
	{
		return false;
	}

	// Update the rotation values in the text object.
	result = m_Text->SetCameraRotation(rotX, rotY, rotZ, m_Direct3D->GetDeviceContext());
	if(!result)
	{
		return false;
	}
	//*/

	return true;
}


void ApplicationClass::RenderRefractionToTexture()
{
	XMFLOAT4 clipPlane;
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;

	// Set the render target to be the refraction render to texture.
	m_RefractionTexture->SetRenderTarget(m_Direct3D->GetDeviceContext());

	// Clear the refraction render to texture.
	m_RefractionTexture->ClearRenderTarget(m_Direct3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the matrices from the camera and d3d objects.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);
	
	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_Direct3D->SetBackBufferRenderTarget();

	// Reset the viewport back to the original.
	m_Direct3D->ResetViewport();

	return;
}


void ApplicationClass::RenderReflectionToTexture()
{
	XMFLOAT4 clipPlane;
	XMMATRIX reflectionViewMatrix, worldMatrix, projectionMatrix;
	XMFLOAT3 cameraPosition;
	
	// Set the render target to be the reflection render to texture.
	m_ReflectionTexture->SetRenderTarget(m_Direct3D->GetDeviceContext());

	// Clear the reflection render to texture.
	m_ReflectionTexture->ClearRenderTarget(m_Direct3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Get the camera reflection view matrix instead of the normal view matrix.
	m_Camera->GetReflectionViewMatrix(reflectionViewMatrix);

	// Get the world and projection matrices from the d3d object.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);

	// Get the position of the camera.
	cameraPosition = m_Camera->GetPosition();

	// Translate the sky dome and sky plane to be centered around the reflected camera position.
	worldMatrix = XMMatrixTranslation(cameraPosition.x, cameraPosition.y, cameraPosition.z);

	// Turn off back face culling and the Z buffer.
	m_Direct3D->TurnOffCulling();
	m_Direct3D->TurnZBufferOff();

	// Render the sky dome using the reflection view matrix.
	m_SkyDome->Render(m_Direct3D->GetDeviceContext());
	m_SkyDomeShader->Render(m_Direct3D->GetDeviceContext(), m_SkyDome->GetIndexCount(), worldMatrix, reflectionViewMatrix, projectionMatrix, 
							m_SkyDome->GetApexColor(), m_SkyDome->GetCenterColor());

	// Enable back face culling.
	m_Direct3D->TurnOnCulling();

	// Enable additive blending so the clouds blend with the sky dome color.
	m_Direct3D->EnableSecondBlendState();

	// Render the sky plane using the sky plane shader.
	m_SkyPlane->Render(m_Direct3D->GetDeviceContext());
	m_SkyPlaneShader->Render(m_Direct3D->GetDeviceContext(), m_SkyPlane->GetIndexCount(), worldMatrix, reflectionViewMatrix, projectionMatrix, 
							 m_SkyPlane->GetCloudTexture(), m_SkyPlane->GetPerturbTexture(), m_SkyPlane->GetTranslation(), m_SkyPlane->GetScale(), 
							 m_SkyPlane->GetBrightness());

	// Turn off blending and enable the Z buffer again.
	m_Direct3D->TurnOffAlphaBlending();
	m_Direct3D->TurnZBufferOn();

	// Reset the world matrix.
	m_Direct3D->GetWorldMatrix(worldMatrix);

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_Direct3D->SetBackBufferRenderTarget();

	// Reset the viewport back to the original.
	m_Direct3D->ResetViewport();

	return;
}


bool ApplicationClass::Render()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix, translateMatrix, rotateMatrix, baseViewMatrix, reflectionViewMatrix;
	bool result;
	XMFLOAT3 cameraPosition;
	XMFLOAT3 scrollSpeeds, scales;
	XMFLOAT2 distortion1, distortion2, distortion3;
	float distortionScale, distortionBias;
	static float frameTime = 0.0f;

	static float rotation = 0.0f;

	// Update the rotation variable each frame.
	rotation += (float)XM_PI * 0.0005f * m_Timer->GetTime();

	// Clear the scene.
	m_Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, projection, ortho, and base view matrices from the camera and Direct3D objects.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);
	m_Direct3D->GetOrthoMatrix(orthoMatrix);
	m_Camera->GetBaseViewMatrix(baseViewMatrix);
	m_Camera->GetReflectionViewMatrix(reflectionViewMatrix);

	// Get the position of the camera.
	cameraPosition = m_Camera->GetPosition();

	// Translate the sky dome to be centered around the camera position.
	worldMatrix = XMMatrixTranslation(cameraPosition.x, cameraPosition.y, cameraPosition.z);

	// Turn off back face culling and the Z buffer.
	m_Direct3D->TurnOffCulling();
	m_Direct3D->TurnZBufferOff();

	// Render the sky dome using the sky dome shader.
	m_SkyDome->Render(m_Direct3D->GetDeviceContext());
	m_SkyDomeShader->Render(m_Direct3D->GetDeviceContext(), m_SkyDome->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_SkyDome->GetApexColor(), m_SkyDome->GetCenterColor());

	// Turn back face culling back on.
	m_Direct3D->TurnOnCulling();

	// Enable additive blending so the clouds blend with the sky dome color.
	m_Direct3D->EnableSecondBlendState();

	// Render the sky plane using the sky plane shader.
	m_SkyPlane->Render(m_Direct3D->GetDeviceContext());
	m_SkyPlaneShader->Render(m_Direct3D->GetDeviceContext(), m_SkyPlane->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_SkyPlane->GetCloudTexture(), m_SkyPlane->GetPerturbTexture(), m_SkyPlane->GetTranslation(), m_SkyPlane->GetScale(),
		m_SkyPlane->GetBrightness());

	// Turn off blending.
	m_Direct3D->TurnOffAlphaBlending();

	// Turn the Z buffer back on.
	m_Direct3D->TurnZBufferOn();

	// Reset the world matrix.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	/*
	// Render the terrain using the terrain shader.
	m_Terrain->Render(m_Direct3D->GetDeviceContext());
	result = m_TerrainShader->Render(m_Direct3D->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Terrain->GetColorTexture(), m_Terrain->GetNormalTexture(), m_Light->GetDiffuseColor(), m_Light->GetDirection(),
		2.0f);
	if (!result)
	{
		return false;
	}

	// Translate to the location of the water and render it.
	worldMatrix = XMMatrixTranslation(240.0f, m_Water->GetWaterHeight(), 250.0f);

	m_Water->Render(m_Direct3D->GetDeviceContext());
	m_WaterShader->Render(m_Direct3D->GetDeviceContext(), m_Water->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, reflectionViewMatrix,
		m_RefractionTexture->GetShaderResourceView(), m_ReflectionTexture->GetShaderResourceView(), m_Water->GetTexture(),
		m_Camera->GetPosition(), m_Water->GetNormalMapTiling(), m_Water->GetWaterTranslation(), m_Water->GetReflectRefractScale(),
		m_Water->GetRefractionTint(), m_Light->GetDirection(), m_Water->GetSpecularShininess());
	*/
	// Setup the rotation and translation of the F1 Car model.
	//set up scaling factors
	XMMATRIX scaleF1Car;
	scaleF1Car = XMMatrixScaling(0.005f, 0.005f, 0.005f);

	worldMatrix = XMMatrixMultiply(worldMatrix, scaleF1Car);

	//self-spinning
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation * 0.0f));

	//set up positioning factors
	translateMatrix = XMMatrixTranslation(5.0f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	//set up rotation factors
	XMVECTOR MyAxis;
	MyAxis = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	if (m_Position->getCarSpinning())
	{
		// Speed at which Car Travels
		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationAxis(MyAxis, (rotation * 3.0f)));
	}
	else if (!m_Position->getCarSpinning())
	{
		// Speed at which Car Travels
		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationAxis(MyAxis, (rotation * 0.0f)));
	}

	// Render the F1 Car model using the texture shader.
	m_Model1->Render(m_Direct3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_Direct3D->GetDeviceContext(), m_Model1->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model1->GetTexture());
	if (!result)
	{
		return false;
	}

	// Setup the rotation and translation of the Tower model.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	XMMATRIX scaleTower;
	scaleTower = XMMatrixScaling(0.05f, 0.05f, 0.05f);
	worldMatrix = XMMatrixMultiply(worldMatrix, scaleTower);

	translateMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation * 0.0f));

	// Render the Tower model using the texture shader.
	m_Model2->Render(m_Direct3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_Direct3D->GetDeviceContext(), m_Model2->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model2->GetTexture());
	if (!result)
	{
		return false;
	}

	// Setup the rotation and translation of the Helicopter model.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	XMMATRIX scaleHelicopter;
	scaleHelicopter = XMMatrixScaling(0.01f, 0.01f, 0.01f);
	worldMatrix = XMMatrixMultiply(worldMatrix, scaleHelicopter);

	//set up positioning factors
	translateMatrix = XMMatrixTranslation(5.0f, 5.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation * 1.5f));

	// Render the Helicopter model using the texture shader.
	m_Model3->Render(m_Direct3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_Direct3D->GetDeviceContext(), m_Model3->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model3->GetTexture());
	if (!result)
	{
		return false;
	}

	// Setup the rotation and translation of the Track model.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	XMMATRIX scaleTrack;
	scaleTrack = XMMatrixScaling(0.135f, 0.1f, 0.135f);
	worldMatrix = XMMatrixMultiply(worldMatrix, scaleTrack);

	translateMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation * 0.0f));

	// Render the Track model using the texture shader.
	m_Model4->Render(m_Direct3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_Direct3D->GetDeviceContext(), m_Model4->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model4->GetTexture());
	if (!result)
	{
		return false;
	}
	
	// Setup the rotation and translation of the Grand Stand model.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	XMMATRIX scaleGrandStand;
	scaleGrandStand = XMMatrixScaling(0.05f, 0.05f, 0.05f);
	worldMatrix = XMMatrixMultiply(worldMatrix, scaleGrandStand);

	translateMatrix = XMMatrixTranslation(7.5f, 0.0f, 7.5f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation * 0.0f));

	// Render the Grand Stand model using the texture shader.
	m_Model5->Render(m_Direct3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_Direct3D->GetDeviceContext(), m_Model5->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model5->GetTexture());
	if (!result)
	{
		return false;
	}

	// Setup the rotation and translation of the Bedroom Wall model.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	XMMATRIX scaleBedroomWall;
	scaleBedroomWall = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, scaleBedroomWall);

	translateMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation * 0.0f));

	// Render the Bedroom Wall model using the texture shader.
	m_Model6->Render(m_Direct3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_Direct3D->GetDeviceContext(), m_Model6->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model6->GetTexture());
	if (!result)
	{
		return false;
	}

	// Setup the rotation and translation of the Bedroom Floor model.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	XMMATRIX scaleBedroomFloor;
	scaleBedroomFloor = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, scaleBedroomFloor);

	translateMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation * 0.0f));

	// Render the Bedroom Floor model using the texture shader.
	m_Model7->Render(m_Direct3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_Direct3D->GetDeviceContext(), m_Model7->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model7->GetTexture());
	if (!result)
	{
		return false;
	}

	// Setup the rotation and translation of the Door model.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	XMMATRIX scaleDoor;
	scaleDoor = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, scaleDoor);

	translateMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation * 0.0f));

	// Render the Door model using the texture shader.
	m_Model8->Render(m_Direct3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_Direct3D->GetDeviceContext(), m_Model8->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model8->GetTexture());
	if (!result)
	{
		return false;
	}

	// Setup the rotation and translation of the Bed model.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	XMMATRIX scaleBed;
	scaleBed = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, scaleBed);

	translateMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation * 0.0f));

	// Render the Bed model using the texture shader.
	m_Model9->Render(m_Direct3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_Direct3D->GetDeviceContext(), m_Model9->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model9->GetTexture());
	if (!result)
	{
		return false;
	}

	// Setup the rotation and translation of the Bedside Table model.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	XMMATRIX scaleBedsideTable;
	scaleBedsideTable = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, scaleBedsideTable);

	translateMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation * 0.0f));

	// Render the Bedside Table model using the texture shader.
	m_Model10->Render(m_Direct3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_Direct3D->GetDeviceContext(), m_Model10->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model10->GetTexture());
	if (!result)
	{
		return false;
	}

	// Setup the rotation and translation of the TV model.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	XMMATRIX scaleTV;
	scaleTV = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, scaleTV);

	translateMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation * 0.0f));

	// Render the TV model using the texture shader.
	m_Model11->Render(m_Direct3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_Direct3D->GetDeviceContext(), m_Model11->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model11->GetTexture());
	if (!result)
	{
		return false;
	}

	// Setup the rotation and translation of the Dresser model.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	XMMATRIX scaleDresser;
	scaleDresser = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, scaleDresser);

	translateMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation * 0.0f));

	// Render the Dresser model using the texture shader.
	m_Model12->Render(m_Direct3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_Direct3D->GetDeviceContext(), m_Model12->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model12->GetTexture());
	if (!result)
	{
		return false;
	}

	// Setup the rotation and translation of the Desk model.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	XMMATRIX scaleDesk;
	scaleDesk = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, scaleDesk);

	translateMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation * 0.0f));

	// Render the Desk model using the texture shader.
	m_Model13->Render(m_Direct3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_Direct3D->GetDeviceContext(), m_Model13->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model13->GetTexture());
	if (!result)
	{
		return false;
	}

	// Setup the rotation and translation of the Monitor model.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	XMMATRIX scaleMonitor;
	scaleMonitor = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, scaleMonitor);

	translateMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation * 0.0f));

	// Render the Monitors model using the texture shader.
	m_Model14->Render(m_Direct3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_Direct3D->GetDeviceContext(), m_Model14->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model14->GetTexture());
	if (!result)
	{
		return false;
	}

	// Setup the rotation and translation of the PC model.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	XMMATRIX scalePC;
	scalePC = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, scalePC);

	translateMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation * 0.0f));

	// Render the PC model using the texture shader.
	m_Model15->Render(m_Direct3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_Direct3D->GetDeviceContext(), m_Model15->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model15->GetTexture());
	if (!result)
	{
		return false;
	}

	// Setup the rotation and translation of the Keyboard model.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	XMMATRIX scaleKeyboard;
	scaleKeyboard = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, scaleKeyboard);

	translateMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation * 0.0f));

	// Render the Keyboard model using the texture shader.
	m_Model16->Render(m_Direct3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_Direct3D->GetDeviceContext(), m_Model16->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model16->GetTexture());
	if (!result)
	{
		return false;
	}

	// Setup the rotation and translation of the Mouse model.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	XMMATRIX scaleMouse;
	scaleMouse = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, scaleMouse);

	translateMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation * 0.0f));

	// Render the Mouse model using the texture shader.
	m_Model17->Render(m_Direct3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_Direct3D->GetDeviceContext(), m_Model17->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model17->GetTexture());
	if (!result)
	{
		return false;
	}

	// Setup the rotation and translation of the Chair model.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	XMMATRIX scaleChair;
	scaleChair = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, scaleChair);

	translateMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation * 0.0f));

	// Render the Chair using the texture shader.
	m_Model18->Render(m_Direct3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_Direct3D->GetDeviceContext(), m_Model18->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model18->GetTexture());
	if (!result)
	{
		return false;
	}

	// Setup the rotation and translation of the Lamp model.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	XMMATRIX scaleLamp;
	scaleLamp = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, scaleLamp);

	translateMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation * 0.0f));

	if (!m_Position->getIsLightOn())
	{
		// Render the Lamp using the texture shader.
		m_Model19->Render(m_Direct3D->GetDeviceContext());
		result = m_ShaderManager->RenderTextureShader(m_Direct3D->GetDeviceContext(), m_Model19->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Model19->GetTexture());
		if (!result)
		{
			return false;
		}
	}
	else if (m_Position->getIsLightOn())
	{
		// Render the Lamp On using the texture shader.
		m_Model26->Render(m_Direct3D->GetDeviceContext());
		result = m_ShaderManager->RenderTextureShader(m_Direct3D->GetDeviceContext(), m_Model26->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Model26->GetTexture());
		if (!result)
		{
			return false;
		}
	}

	// Setup the rotation and translation of the Guitar model.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	XMMATRIX scaleGuitar;
	scaleGuitar = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, scaleGuitar);

	translateMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation * 0.0f));

	// Render the Guitar using the texture shader.
	m_Model20->Render(m_Direct3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_Direct3D->GetDeviceContext(), m_Model20->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model20->GetTexture());
	if (!result)
	{
		return false;
	}

	// Setup the rotation and translation of the Rug model.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	XMMATRIX scaleRug;
	scaleRug = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, scaleRug);

	translateMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation * 0.0f));

	// Render the Guitar using the texture shader.
	m_Model21->Render(m_Direct3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_Direct3D->GetDeviceContext(), m_Model21->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model21->GetTexture());
	if (!result)
	{
		return false;
	}

	// Setup the rotation and translation of the Xbox model.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	XMMATRIX scaleXbox;
	scaleXbox = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, scaleXbox);

	translateMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation * 0.0f));

	// Render the Xbox using the texture shader.
	m_Model22->Render(m_Direct3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_Direct3D->GetDeviceContext(), m_Model22->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model22->GetTexture());
	if (!result)
	{
		return false;
	}

	// Setup the rotation and translation of the Ceiling model.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	XMMATRIX scaleRemote;
	scaleRemote = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, scaleRemote);

	translateMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation * 0.0f));

	// Render the Remote using the texture shader.
	m_Model23->Render(m_Direct3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_Direct3D->GetDeviceContext(), m_Model23->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model23->GetTexture());
	if (!result)
	{
		return false;
	}

	// Setup the rotation and translation of the Ceiling model.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	XMMATRIX scaleCeiling;
	scaleCeiling = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, scaleCeiling);

	translateMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation * 0.0f));

	// Render the Ceiling using the texture shader.
	m_Model24->Render(m_Direct3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_Direct3D->GetDeviceContext(), m_Model24->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model24->GetTexture());
	if (!result)
	{
		return false;
	}

	// Setup the rotation and translation of the Ceiling Fan model.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	XMMATRIX scaleCeilingFan;
	scaleCeilingFan = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, scaleCeilingFan);

	translateMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	if (m_Position->getFanSpinning())
	{
		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation * 5.0f));
	}
	else if (!m_Position->getFanSpinning())
	{
		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation * 0.0f));
	}

	// Render the Ceiling Fan using the texture shader.
	m_Model25->Render(m_Direct3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_Direct3D->GetDeviceContext(), m_Model25->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model25->GetTexture());
	if (!result)
	{
		return false;
	}

	// Setup the rotation and translation of the Candle model.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	XMMATRIX scaleCandle;
	scaleCandle = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, scaleCandle);

	translateMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation * 0.0f));

	// Render the Candle using the texture shader.
	m_Model27->Render(m_Direct3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_Direct3D->GetDeviceContext(), m_Model27->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model27->GetTexture());
	if (!result)
	{
		return false;
	}

	// Increment the frame time counter.
	frameTime += 0.01f;
	if (frameTime > 1000.0f)
	{
		frameTime = 0.0f;
	}

	// Set the three scrolling speeds for the three different noise textures.
	scrollSpeeds = XMFLOAT3(1.3f, 2.1f, 2.3f);

	// Set the three scales which will be used to create the three different noise octave textures.
	scales = XMFLOAT3(1.0f, 2.0f, 3.0f);

	// Set the three different x and y distortion factors for the three different noise textures.
	distortion1 = XMFLOAT2(0.1f, 0.2f);
	distortion2 = XMFLOAT2(0.1f, 0.3f);
	distortion3 = XMFLOAT2(0.1f, 0.1f);

	// The the scale and bias of the texture coordinate sampling perturbation.
	distortionScale = 0.8f;
	distortionBias = 0.5f;

	// Setup the rotation and translation of the Flame model.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	XMMATRIX scaleFlame;
	scaleFlame = XMMatrixScaling(100.0f, 100.0f, 100.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, scaleFlame);

	translateMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation * 0.0f));

	// Render the square model using the fire shader.
	result = m_FireShader->Render(m_Direct3D->GetDeviceContext(), m_Fire->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Fire->GetTexture1(), m_Fire->GetTexture2(), m_Fire->GetTexture3(), frameTime, scrollSpeeds,
		scales, distortion1, distortion2, distortion3, distortionScale, distortionBias);
	if (!result)
	{
		return false;
	}

	// Reset the world matrix.
	m_Direct3D->GetWorldMatrix(worldMatrix);

	// Turn off the Z buffer to begin all 2D rendering.
	m_Direct3D->TurnZBufferOff();

	// Turn on the alpha blending before rendering the text.
	m_Direct3D->TurnOnAlphaBlending();
	/*
	// Render the text user interface elements.
	result = m_Text->Render(m_Direct3D->GetDeviceContext(), m_FontShader, worldMatrix, orthoMatrix);
	if(!result)
	{
		return false;
	}
	//*/
	// Turn off alpha blending after rendering the text.
	m_Direct3D->TurnOffAlphaBlending();

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_Direct3D->TurnZBufferOn();

	// Present the rendered scene to the screen.
	m_Direct3D->EndScene();

	return true;
}