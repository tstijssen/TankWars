//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------

// World matrix, combined view / projection matrix and camera position for transformation
// and lighting calculations
float4x4 WorldMatrix    : WORLD;
float4x4 ViewProjMatrix : VIEWPROJECTION;


//-----------------------------------------------------------------------------
// Input / output structures
//-----------------------------------------------------------------------------

// Input to Vertex Shader - usual position, normal and UVs
struct VS_Input
{
	float3 Position  : POSITION;  // The position of the vertex in model space
	float3 Normal    : NORMAL;
	float2 TexCoord0 : TEXCOORD0;
};

// Output from Vertex Shader. This shader sends the world position and normal to the pixel
// shader to do the lighing calculations. There are no semantics for such a use so we use
// TEXCOORD semantics, this is usual for any non-standard data types passed to a pixel shader.
struct VS_Output
{
	float4 Position      : POSITION;
	float3 CameraPos : CAMERAPOSITION;
	float2 TexCoord0     : TEXCOORD0;
	float3 WorldPosition : TEXCOORD1; // Use TEXCOORD semantic for non-standard data - see above 
	float3 Normal        : TEXCOORD2;
	float3 DiffuseLight  : COLOR0;
	float3 SpecularLight : COLOR1;
};

//-----------------------------------------------------------------------------
// Main function
//-----------------------------------------------------------------------------

// Main vertex shader function. Basic shader that also passes world-space position and normal
// on to the pixel shader

void main( in VS_Input i, out VS_Output o ) 
{
    // Transform model vertex position to world space, then to viewport space. Pass both forms on
    // to the pixel shader
	o.CameraPos.x = WorldMatrix._m03;
	o.CameraPos.y = WorldMatrix._m13;
	o.CameraPos.z = WorldMatrix._m23;

	WorldMatrix._m03 = 0;
	WorldMatrix._m13 = 0;
	WorldMatrix._m23 = 0;

    float4 WorldPosition = mul( float4(i.Position, 1.0f), WorldMatrix );

	float4 WorldNormal = mul(float4(i.Normal, 0.0f), WorldMatrix);
	WorldNormal = normalize(WorldNormal);

    o.Position = mul( float4(WorldPosition, 1.0f), ViewProjMatrix );
    o.WorldPosition = WorldPosition;

    // Transform model normal to world space and pass to the pixel shader
    o.Normal = mul( i.Normal, (float3x3)WorldMatrix );
    
    // Pass texture coordinates directly to pixel shader
    o.TexCoord0 = i.TexCoord0;
}

// myOwn

//float3 lightColour = { 1.0f, 0.0f, 0.5f };
//float3 lightPos = {5.0f, 5.0f, 0.0f};
//float3 ambientColour = {0.0f, 1.0f, 0.0f}

//// lighting
//float3 lightVector = lightPos - WorldPosition.xyz;
//float3 attLight = lightColour / length(lightVector);
//lightVector = normalize(lightVector);

//float3 cameraVector = normalize(o.CameraPos - WorldPosition.xyz);
//float3 halfwayNormal = normalize((lightVector + cameraVector) / 2);

//o.DiffuseLight = 10 * attenuatedLight * max(dot(WorldNormal, lightVector), 0) + ambientColour;
//o.SpecularLight = 10 * attenuatedLight * pow(max(dot(WorldNormal, halfwayNormal), 0), SPecularPower);