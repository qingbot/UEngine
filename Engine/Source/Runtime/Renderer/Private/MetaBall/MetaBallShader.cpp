#include "MetaBallShader.h"
#include "RenderGraphBuilder.h"
#include "SceneRendering.h"
#include "ShaderParameterStruct.h"
#include "DeferredShadingRenderer.h"
#include "ScenePrivate.h"
#include "Components/UMetaBallComponent.h"


IMPLEMENT_GLOBAL_SHADER(FMetaBallVS, "/Engine/Private/MetaBallShader.usf", "MainVS", SF_Vertex);
IMPLEMENT_GLOBAL_SHADER(FMetaBallPS, "/Engine/Private/MetaBallShader.usf", "MainPS",SF_Pixel);


void FMetaBallPS::SetColor(FRHICommandList& RHICmdList, const FLinearColor& Color)
{
	//SetShaderValue(RHICmdList,RHICmdList.GetBoundPixelShader(),MyColor,Color);
}

IMPLEMENT_GLOBAL_SHADER_PARAMETER_STRUCT(FMetaBallUniformBuffer, "MetaBallUniformBuffer");
//IMPLEMENT_GLOBAL_SHADER_PARAMETER_STRUCT(FMetaBallPS::FParameters,"MetaBallShaderParameter");

class FMetaBallVertexDeclaration : public  FRenderResource
{
public:
	FVertexDeclarationRHIRef VertexDeclarationRHI;

	virtual void InitRHI() override
	{
		FVertexDeclarationElementList Elements;
		Elements.Add(FVertexElement(0,0,VET_Float2,0,sizeof(FVector2f)));
		VertexDeclarationRHI = PipelineStateCache::GetOrCreateVertexDeclaration(Elements);
	}

	virtual void ReleaseRHI() override
	{
		VertexDeclarationRHI.SafeRelease();
	}
};

TGlobalResource<FMetaBallVertexDeclaration> GMetaBallVertexDeclaration;
//IMPLEMENT_GLOBAL_SHADER_PARAMETER_STRUCT(FMetaBallParameters,"MetaBallShaderParameter");


void RenderCustomMetaBall(FRHICommandList& RHICommandList,const FViewInfo& View,FMetaBallPS::FParameters& MetaBallParameters)
{
	
	TShaderMapRef<FMetaBallVS> MyVS(View.ShaderMap);
	TShaderMapRef<FMetaBallPS> MyPS(View.ShaderMap);

	FGraphicsPipelineStateInitializer GraphicsPSOInit;

	RHICommandList.ApplyCachedRenderTargets(GraphicsPSOInit);

	GraphicsPSOInit.PrimitiveType = PT_TriangleList;
	GraphicsPSOInit.RasterizerState = TStaticRasterizerState<FM_Solid, CM_None>::GetRHI();
	GraphicsPSOInit.BlendState = TStaticBlendState<CW_RGB, BO_Add, BF_SourceAlpha, BF_InverseSourceAlpha>::GetRHI();

	GraphicsPSOInit.BoundShaderState.VertexShaderRHI = MyVS.GetVertexShader();
	GraphicsPSOInit.BoundShaderState.PixelShaderRHI = MyPS.GetPixelShader();
	GraphicsPSOInit.BoundShaderState.VertexDeclarationRHI = GMetaBallVertexDeclaration.VertexDeclarationRHI;
	// 透明物体，不写入深度，但是要参与深度测试
	GraphicsPSOInit.DepthStencilState = TStaticDepthStencilState<false, CF_Always>::GetRHI();

	
	SetGraphicsPipelineState(RHICommandList,GraphicsPSOInit,0);
	//MetaBallParameters.MyColor = FVector4f(1,0,1,0.5f);
	//SetUniformBufferParameter(RHICommandList, MyPS.GetPixelShader(), )
	SetShaderParameters(RHICommandList, MyPS, MyPS.GetPixelShader(),MetaBallParameters);

	RHICommandList.SetStreamSource(0,GScreenSpaceVertexBuffer.VertexBufferRHI,0);
	RHICommandList.DrawIndexedPrimitive(GTwoTrianglesIndexBuffer.IndexBufferRHI,0,0,4,0,2,1);
}
DECLARE_GPU_STAT(MetaBall)

void FDeferredShadingSceneRenderer::RenderMetaBall(FRDGBuilder& RDG,const FMinimalSceneTextures& SceneTextures)
{
	RDG_EVENT_SCOPE(RDG,"MetaBallRDG");
	RDG_GPU_STAT_SCOPE(RDG,MetaBall);
	
	for(int i = 0 ; i < Views.Num(); ++i)
	{
		const FViewInfo& View = Views[i];
		FMetaBallPS::FParameters* PassParameters = RDG.AllocParameters<FMetaBallPS::FParameters>();
		
		PassParameters->ViewUniformBuffer = GetShaderBinding(View.ViewUniformBuffer);
		PassParameters->SceneTextures = SceneTextures.UniformBuffer;
/*
		FMetaBallUniformBuffer metablluniformBuffer;
		metablluniformBuffer.BallColor0 = Scene->MetaBall->BallColor0;
		metablluniformBuffer.BallColor1 = Scene->MetaBall->BallColor1;
		metablluniformBuffer.BallColor2 = Scene->MetaBall->BallColor2;
		metablluniformBuffer.RayStep = Scene->MetaBall->RayStep;
		metablluniformBuffer.WorldPos0 = Scene->MetaBall->WorldPos0;
		metablluniformBuffer.WorldPos1 = Scene->MetaBall->WorldPos1;
		metablluniformBuffer.WorldPos2 = Scene->MetaBall->WorldPos2;

		
		auto MetaballUniformBuffer = TUniformBufferRef<FMetaBallUniformBuffer>::CreateUniformBufferImmediate(metablluniformBuffer,EUniformBufferUsage::UniformBuffer_SingleDraw);
*/
		
		if(!Scene->MetaBallUniformBuffer.IsValid())return;
		PassParameters->MetaBallUniformBuffer = Scene->MetaBallUniformBuffer;
		
		// UE_LOG(LogTemp, Warning, TEXT("RenderMetaBall"));
		
		PassParameters->MyColor = Scene->MetaBall == NULL ?FVector4f(1,0,0,1):Scene->MetaBall->MetaBallColor;
		PassParameters->RenderTargets[0] = FRenderTargetBinding(SceneTextures.Color.Target, ERenderTargetLoadAction::ELoad);
		PassParameters->RenderTargets.DepthStencil = FDepthStencilBinding(SceneTextures.Depth.Target, ERenderTargetLoadAction::ELoad, ERenderTargetLoadAction::ELoad, FExclusiveDepthStencil::DepthRead_StencilWrite);
		
		//PassParameters->MyColor = FVector4f(1,0,0,1);
		RDG.AddPass(RDG_EVENT_NAME("MetaBall"),PassParameters,ERDGPassFlags::Raster,
			[this,PassParameters,&View](FRHICommandList& RHICmdList)
			{
				RenderCustomMetaBall(RHICmdList,View,*PassParameters);
			});
	}
	
}
