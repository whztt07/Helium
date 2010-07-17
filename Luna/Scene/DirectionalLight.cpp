#include "Precompile.h"
#include "DirectionalLight.h"

#include "Scene.h"
#include "SceneManager.h"
#include "InstanceType.h"

#include "PropertiesGenerator.h"
#include "Application/UI/ArtProvider.h"

#include "PrimitivePointer.h"

// Using
using namespace Math;
using namespace Luna;

// RTTI
LUNA_DEFINE_TYPE(Luna::DirectionalLight);

void DirectionalLight::InitializeType()
{
  Reflect::RegisterClass< Luna::DirectionalLight >( TXT( "Luna::DirectionalLight" ) );

  PropertiesGenerator::InitializePanel( TXT( "DirectionalLight" ), CreatePanelSignature::Delegate( &DirectionalLight::CreatePanel ) );
}

void DirectionalLight::CleanupType()
{
  Reflect::UnregisterClass< Luna::DirectionalLight >();
}

DirectionalLight::DirectionalLight(Luna::Scene* scene)
: Luna::Light (scene, new Content::DirectionalLight() )
{

}

DirectionalLight::DirectionalLight(Luna::Scene* scene, Content::DirectionalLight* light)
: Luna::Light ( scene, light )
{

}

i32 DirectionalLight::GetImageIndex() const
{
  return Nocturnal::GlobalFileIconsTable().GetIconID( TXT( "light" ) );
}

tstring DirectionalLight::GetApplicationTypeName() const
{
  return TXT( "DirectionalLight" );
}

///////////////////////////////////////////////////////////////////////////////
// Returns true if the specified panel is supported by DirectionalLight.
//
bool DirectionalLight::ValidatePanel(const tstring& name)
{
  if (name == TXT( "DirectionalLight" ) )
  {
    return true;
  }

  return __super::ValidatePanel( name );
}

void DirectionalLight::CreatePanel( CreatePanelArgs& args )
{
  args.m_Generator->PushPanel( TXT( "Directional Light" ), true);
  {
    args.m_Generator->PushContainer();
    {
      args.m_Generator->AddLabel( TXT( "Global Sun" ) );
      args.m_Generator->AddCheckBox<DirectionalLight, bool>( args.m_Selection, &DirectionalLight::GetGlobalSun, &DirectionalLight::SetGlobalSun );
    }
    args.m_Generator->Pop();

    args.m_Generator->PushContainer();
    {
      args.m_Generator->AddLabel( TXT( "Shadow Softness" ) );

      args.m_Generator->AddValue<DirectionalLight, float>( args.m_Selection, &DirectionalLight::GetShadowSoftness, &DirectionalLight::SetShadowSoftness );
      Inspect::Slider* slider = args.m_Generator->AddSlider<DirectionalLight, float>( args.m_Selection, &DirectionalLight::GetShadowSoftness, &DirectionalLight::SetShadowSoftness );
    }
    args.m_Generator->Pop();

    args.m_Generator->PushContainer();
    {
      args.m_Generator->AddLabel( TXT( "Soft Shadow Samples" ) );

      args.m_Generator->AddValue<DirectionalLight, int>( args.m_Selection, &DirectionalLight::GetSoftShadowSamples, &DirectionalLight::SetSoftShadowSamples );
      Inspect::Slider* slider = args.m_Generator->AddSlider<DirectionalLight, int>( args.m_Selection, &DirectionalLight::GetSoftShadowSamples, &DirectionalLight::SetSoftShadowSamples );
    }
    args.m_Generator->Pop();
  }
  args.m_Generator->Pop();

}

bool DirectionalLight::GetGlobalSun() const
{
  return GetPackage< Content::DirectionalLight >()->m_GlobalSun;
}

void DirectionalLight::SetGlobalSun( bool globalSun )
{
  GetPackage< Content::DirectionalLight >()->m_GlobalSun = globalSun;
}

float DirectionalLight::GetShadowSoftness() const
{
  return GetPackage< Content::DirectionalLight >()->m_ShadowSoftness;
}

void DirectionalLight::SetShadowSoftness( float multiplier )
{
  GetPackage< Content::DirectionalLight >()->m_ShadowSoftness = multiplier;
}

int DirectionalLight::GetSoftShadowSamples() const
{
  return GetPackage< Content::DirectionalLight >()->m_SoftShadowSamples;
}

void DirectionalLight::SetSoftShadowSamples( int multiplier )
{
  GetPackage< Content::DirectionalLight >()->m_SoftShadowSamples = multiplier;
}
