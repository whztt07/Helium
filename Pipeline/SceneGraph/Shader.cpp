/*#include "Precompile.h"*/
#include "Shader.h"

#include "Foundation/Log.h"

#include "Pipeline/SceneGraph/Render.h"
#include "Pipeline/SceneGraph/Scene.h"

using namespace Helium;
using namespace Helium::SceneGraph;

Profile::MemoryPoolHandle g_ShaderTextureMemoryPool;

REFLECT_DEFINE_CLASS( Shader );

#pragma TODO("Data-hide public reflected fields")

void Shader::AcceptCompositeVisitor( Reflect::Composite& comp )
{
    comp.AddField( &Shader::m_WrapU,      TXT( "m_WrapU" ) );
    comp.AddField( &Shader::m_WrapV,      TXT( "m_WrapV" ) );
    comp.AddField( &Shader::m_RepeatU,    TXT( "m_RepeatU" ) );
    comp.AddField( &Shader::m_RepeatV,    TXT( "m_RepeatV" ) );
    comp.AddField( &Shader::m_BaseColor,  TXT( "m_BaseColor" ) );
    comp.AddField( &Shader::m_AssetPath,  TXT( "m_AssetPath" ) );
}

void Shader::InitializeType()
{
    Reflect::RegisterClassType< Shader >( TXT( "SceneGraph::Shader" ) );

    g_ShaderTextureMemoryPool = Profile::Memory::CreatePool( TXT( "Direct3D Texture Data" ) );
}

void Shader::CleanupType()
{
    Reflect::UnregisterClassType< Shader >();
}

Shader::Shader() 
: m_WrapU( true )
, m_WrapV( true )
, m_RepeatU( 1.0 )
, m_RepeatV( 1.0 )
, m_Alpha( false )
, m_BaseTextureSize( 0 )
, m_BaseTexture( NULL )
{
}

Shader::~Shader()
{

}

int32_t Shader::GetImageIndex() const
{
    return -1; // Helium::GlobalFileIconsTable().GetIconID( TXT( "shader" ) );
}

tstring Shader::GetApplicationTypeName() const
{
    return TXT( "Shader" );
}

void Shader::Create()
{
    __super::Create();

    if ( m_AssetPath.Exists() )
    {
        //m_BaseTexture = SceneGraph::LoadTexture( m_Scene->GetView()->GetDevice(), file, &m_BaseTextureSize, &m_Alpha );

        //Profile::Memory::Allocate( g_ShaderTextureMemoryPool, m_BaseTextureSize );
    }
}

void Shader::Delete()
{
    __super::Delete();

    if ( m_BaseTexture != NULL )
    {
        m_BaseTexture->Release();
        m_BaseTexture = NULL;

        Profile::Memory::Deallocate( g_ShaderTextureMemoryPool, m_BaseTextureSize );
    }
}

bool Shader::GetAlpha() const
{
    return m_Alpha;
}

IDirect3DTexture9* Shader::GetBaseTexture() const
{
    return m_BaseTexture;
}
