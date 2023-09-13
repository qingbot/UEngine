#pragma once
#include "GlobalShader.h"
#include "ShaderParameterStruct.h"


// 三个MetaBall的世界坐标 xyzw w = MetaBall的半径
// 当前版本，需要在CPU端为其排序，保证0离摄像机最近
BEGIN_GLOBAL_SHADER_PARAMETER_STRUCT(FMetaBallUniformBuffer,)
	SHADER_PARAMETER(FVector3f, WorldPos0)
	SHADER_PARAMETER(FVector3f, WorldPos1)
	SHADER_PARAMETER(FVector3f, WorldPos2)
	SHADER_PARAMETER(FLinearColor, BallColor0)
	SHADER_PARAMETER(FLinearColor, BallColor1)
	SHADER_PARAMETER(FLinearColor, BallColor2)
	SHADER_PARAMETER(float,RayStep)			// 射线每一步的步长
	SHADER_PARAMETER(float,MetaBallRadius)	// Metaball的阈值，低于此值则不构成MetaBall
	SHADER_PARAMETER(float,MetaBallTreshold)
	SHADER_PARAMETER_ARRAY(FVector4f,Actors,[64])
END_GLOBAL_SHADER_PARAMETER_STRUCT()

class FMetaBallVS :public FGlobalShader
{
public:
	DECLARE_GLOBAL_SHADER(FMetaBallVS);

	FMetaBallVS(){}
	FMetaBallVS(const ShaderMetaType::CompiledShaderInitializerType& Initializer):FGlobalShader(Initializer)
	{}
	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return true;
	}

	static bool ShoudCache(EShaderPlatform Platform)
	{
		return true;
	}
};

class FMetaBallPS :public FGlobalShader
{
public:
	DECLARE_GLOBAL_SHADER(FMetaBallPS);
	SHADER_USE_PARAMETER_STRUCT(FMetaBallPS,FGlobalShader);

	BEGIN_SHADER_PARAMETER_STRUCT(FParameters,)
	SHADER_PARAMETER_STRUCT_REF(FViewUniformShaderParameters, ViewUniformBuffer)
	SHADER_PARAMETER_STRUCT_REF(FMetaBallUniformBuffer, MetaBallUniformBuffer)
	SHADER_PARAMETER(FVector4f,MyColor)
	SHADER_PARAMETER_RDG_UNIFORM_BUFFER(FSceneTextureUniformParameters, SceneTextures)
	RENDER_TARGET_BINDING_SLOTS()
	END_SHADER_PARAMETER_STRUCT()

	
	static void ModifyCompilationEnvironment(FGlobalShaderPermutationParameters Platform,FShaderCompilerEnvironment& outEnvironment)
	{
		FGlobalShader::ModifyCompilationEnvironment(Platform,outEnvironment);
	}static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return true;
	}


	static bool ShouldCache(EShaderPlatform Platform)
	{
		return true;
	}
	void SetColor(FRHICommandList& RHICmdList,const FLinearColor& Color);
	
};


void RenderMetaBall(FRHICommandList&,ERHIFeatureLevel::Type,const FLinearColor&);


// compute shader
class FMetaBallCSOne :public FGlobalShader
{
	 
};

class FMetaBallCSMulti :public FGlobalShader
{
	
};
