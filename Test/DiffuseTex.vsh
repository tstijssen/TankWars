//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------

// World matrix and combined view / projection matrix
matrix WorldMatrix    : WORLD;
matrix ViewProjMatrix : VIEWPROJECTION;
//float3 CameraPosition   : CAMERAPOSITION;



//-----------------------------------------------------------------------------
// Input / output structures
//-----------------------------------------------------------------------------

// Input to Vertex Shader
struct VS_Input
{
	float3 Position : POSITION;
	float3 Normal : NORMAL;
	float2 TexCoord0 : TEXCOORD0;
};

// Output from Vertex Shader
struct VS_Output
{
	float4 Position : POSITION;
	float3 DiffuseColour : COLOR0;
//	float3 SpecularColour : COLOR1;
	float2 TexCoord0 : TEXCOORD0;
};

//-----------------------------------------------------------------------------
// Main function
//-----------------------------------------------------------------------------

// Main vertex shader function
void main( in VS_Input i, out VS_Output o ) 
{
	//float CameraPosX = WorldMatrix._m03;
	//float CameraPosY = WorldMatrix._m13;
	//float CameraPosZ = WorldMatrix._m23;

	//WorldMatrix._m03 = 0;
	//WorldMatrix._m13 = 0;
	//WorldMatrix._m23 = 0;

	const float3 AmbientColour = { 0.5f, 0.5f, 0.5f };
	const float3 LightColour = { 1.0f, 0.3f, 0.0f };
	const float3 DirToLight = { 0.408, 0.408, -0.816 };
//	const float SpecularPower = 30.0f;
	

    // Transform model vertex position to world space, then to viewport space, then output it
    float4 WorldPosition = mul( float4(i.Position, 1.0f), WorldMatrix );
    o.Position = mul( WorldPosition, ViewProjMatrix );

	float3 WorldNormal = (float3)mul(i.Normal, (float3x3)WorldMatrix);
//	float3 diffuseColour = AmbientColour + LightColour * saturate(dot(normalize(WorldNormal), DirToLight))


//	float3 Normal = normalize( mul( float4(i.Normal, 0.0f), WorldMatrix ) ).xyz;  
	float3 DiffuseColour = AmbientColour + LightColour * saturate( dot( WorldNormal, DirToLight ) );
    o.DiffuseColour = float4( DiffuseColour, 1.0f );

//	float3 DirToCamera = normalize( CameraPosition - WorldPosition );
//	float3 H = normalize( DirToCamera + DirToLight );
//	o.SpecularColour = LightColour * pow( saturate( dot(Normal, H) ), SpecularPower ); // Phong

    o.TexCoord0 = i.TexCoord0;
}
