// Vertex shader input structure
struct VertexInput
{
    float3 position : POSITION;
};

// Vertex shader output structure
struct VertexOutput
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

// Vertex shader
VertexOutput VertexMain(VertexInput input)
{
    VertexOutput output;

    // Transform vertex position (for example, using the world, view, and projection matrices)
    output.position = mul(float4(input.position, 1.0f), worldViewProjMatrix);

    // Assign a color to be passed to the pixel shader
    output.color = float4(1.0f, 0.0f, 0.0f, 1.0f); // Red

    return output;
}

// Pixel shader input structure
struct PixelInput
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

// Pixel shader output structure
struct PixelOutput
{
    float4 color : SV_TARGET;
};

// Pixel shader
PixelOutput PixelMain(PixelInput input) : SV_TARGET
{
    PixelOutput output;

// Output the color assigned in the vertex shader
output.color = input.color;

return output;
}
