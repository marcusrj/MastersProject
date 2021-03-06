//
// Game.h
//
#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include "Shader.h"
#include "modelclass.h"
#include "Light.h"
#include "Input.h"
#include "Camera.h"
#include "RenderTexture.h"
#include "Terrain.h"
#include <string.h>
#include <sstream>
#include <ctime>
#include "HorizontalBlurShader.h"
#include "OrthoWindowClass.h"
#include "Forest.h"
#include "AStar.h"
#include <iostream>

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game final : public DX::IDeviceNotify
{
public:

    Game() noexcept(false);
    ~Game();

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // IDeviceNotify
    virtual void OnDeviceLost() override;
    virtual void OnDeviceRestored() override;

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnWindowSizeChanged(int width, int height);
#ifdef DXTK_AUDIO
    void NewAudioDevice();
#endif

    // Properties
    void GetDefaultSize( int& width, int& height ) const;
	
private:

	struct MatrixBufferType
	{
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;
	}; 

    void Update(DX::StepTimer const& timer);
    void Render();
    void Clear();
    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();
	void SetupGUI();


	void RenderToTexturePass();
	void RenderToTextureHorizontalBlur();
	void RenderToTextureVerticalBlur();
	void RenderToTextureDownSample();
	void RenderToTextureUpSample();

    // Device resources.
    std::unique_ptr<DX::DeviceResources>    m_deviceResources;

    // Rendering loop timer.
    DX::StepTimer                           m_timer;

	//input manager. 
	Input									m_input;
	InputCommands							m_gameInputCommands;

    // DirectXTK objects.
    std::unique_ptr<DirectX::CommonStates>                                  m_states;
    std::unique_ptr<DirectX::BasicEffect>                                   m_batchEffect;	
    std::unique_ptr<DirectX::EffectFactory>                                 m_fxFactory;
    std::unique_ptr<DirectX::SpriteBatch>                                   m_sprites;
    std::unique_ptr<DirectX::SpriteFont>                                    m_font;

	// Scene Objects
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>  m_batch;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>                               m_batchInputLayout;
	std::unique_ptr<DirectX::GeometricPrimitive>                            m_testmodel;

	//lights
	Light																	m_Light;

	//Cameras
	Camera																	m_Camera01;

	//textures 
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>                        m_texture1;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>                        m_texture2;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>                        m_texture3;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>                        m_texGreen;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>                        m_texBlack;

	//Shaders
	Shader																	m_BasicShaderPair;
	HorizontalBlurShader													m_HorizontalBlurShaderPair;

	//Scene. 
	Terrain																	m_Terrain;
	ModelClass																m_BasicModel;
	ModelClass																m_BasicModel2;
	ModelClass																m_BasicModel3;

	ModelClass*																m_treeModels;
	ModelClass*	m_RoadModels;
	ModelClass																m_UFO;
	ModelClass																m_Sphere;

	//RenderTextures
	RenderTexture*															m_FirstRenderPass;
	RenderTexture*															m_DownSamplePass;
	RenderTexture*															m_HorizontalRenderPass;
	RenderTexture*															m_UpSamplePass;
	RenderTexture*															m_VerticalRenderPass;

	RECT																	m_fullscreenRect;
	RECT																	m_CameraViewRect;
	
	//Trees 
	DirectX::SimpleMath::Vector3*											m_trees;

	OrthoWindowClass	m_Window;

	Forest*	m_forests;
	int m_numForests;
	int m_treeCount;

	AStar* m_Roads;
	int m_totalpoints;



#ifdef DXTK_AUDIO
    std::unique_ptr<DirectX::AudioEngine>                                   m_audEngine;
    std::unique_ptr<DirectX::WaveBank>                                      m_waveBank;
    std::unique_ptr<DirectX::SoundEffect>                                   m_soundEffect;
    std::unique_ptr<DirectX::SoundEffectInstance>                           m_effect1;
    std::unique_ptr<DirectX::SoundEffectInstance>                           m_effect2;
#endif
    

#ifdef DXTK_AUDIO
    uint32_t                                                                m_audioEvent;
    float                                                                   m_audioTimerAcc;

    bool                                                                    m_retryDefault;
#endif

    DirectX::SimpleMath::Matrix                                             m_world;
    DirectX::SimpleMath::Matrix                                             m_view;
    DirectX::SimpleMath::Matrix                                             m_projection;
};