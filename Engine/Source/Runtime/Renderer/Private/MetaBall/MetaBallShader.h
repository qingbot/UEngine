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
	// xy：在xy方向上，将屏幕切分为了几个格子
	// z = Actors的数组长度 w = ActorsIndex的数组长度
	SHADER_PARAMETER(FVector4f,TileSize)	
	SHADER_PARAMETER_ARRAY(FVector4f,Actors,[256])
	// Actor的索引，这其实是个二维数组，将屏幕划分为 m*n个格子
	// 每个格子最多可以支持8个MetaBall，所以需要消耗两个数组元素
	// 索引为 -1 或者说 <0 代表此处没有，索引从0开始，索引就是上面这个数组的索引[0,256]
	SHADER_PARAMETER_ARRAY(FVector4f,ActorsIndex,[512])
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
