//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------

// World matrix and combined view / projection matrix
matrix <float, 4, 4> WorldMatrix    : WORLD;
matrix <float, 4, 4> ViewProjMatrix : VIEWPROJECTION;
float3 CameraPosition   : CAMERAPOSITION;



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
	float3 WorldPos		: POSITION;
	float3 WorldNormal	: NORMAL;
	float3 CameraPos	: CAMERAPOSITION;
	//float3 DiffuseColour : COLOR0;
	//float3 SpecularColour : COLOR1;
	float2 TexCoord0 : TEXCOORD0;
};

//-----------------------------------------------------------------------------
// Main function
//-----------------------------------------------------------------------------

// Main vertex shader function
void main( in VS_Input i, out VS_Output o ) 
{
	matrix localWorld = WorldMatrix;	// use local world matrix to manipulate

	//float3 CameraPos;
	//CameraPos.x = localWorld._14;
	//CameraPos.y = localWorld._24;
	//CameraPos.z = localWorld._34;

	//localWorld._14 = 0;
	//localWorld._24 = 0;
	//localWorld._34 = 0;

	//const float3 AmbientColour = { 0.5f, 0.5f, 0.5f };
	//const float3 LightColour = { 0.8f, 0.5f, 0.4f };
	//const float3 DirToLight = { 0.408, 0.408, -0.816 };
	//const float SpecularPower = 60.0f;
	

    // Transform model vertex position to world space, then to viewport space, then output it
    float4 WorldPosition = mul( float4(i.Position, 1.0f), localWorld);
    o.Position = mul( WorldPosition, ViewProjMatrix );

	o.WorldPos = WorldPosition.xyz;

	o.WorldNormal = (float3)mul(i.Normal, (float3x3)localWorld);

	o.CameraPos = CameraPosition;

	//float3 WorldNormal = (float3)mul(i.Normal, (float3x3)localWorld);
//	float3 diffuseColour = AmbientColour + LightColour * saturate(dot(normalize(WorldNormal), DirToLight))



//	float3 DiffuseColour = AmbientColour + LightColour * saturate( dot( i.WorldNormal, DirToLight ) );
 //   o.DiffuseColour = float4( DiffuseColour, 1.0f );

	//float3 DirToCamera = normalize( CameraPosition - WorldPosition );
	//float3 H = normalize( DirToCamera + DirToLight );
	//o.SpecularColour = LightColour * pow( saturate( dot(i.Normal, H) ), SpecularPower ); // Phong

    o.TexCoord0 = i.TexCoord0;
}
