
#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "MaterialExpressionIO.h"
#include "Materials/MaterialExpression.h"
#include "MaterialExpressionSMin.generated.h"

UCLASS(MinimalAPI)
class UMaterialExpressionSMin : public UMaterialExpression
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to constA"))
	FExpressionInput A;
	
	UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to constB"))
	FExpressionInput B;
	
	UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to constK"))
	FExpressionInput K;

	UPROPERTY(EditAnywhere, Category = MaterialExpressionSMin, meta = (OverridingInputProperty = "A"))
	float ConstA;
	
	UPROPERTY(EditAnywhere, Category = MaterialExpressionSMin, meta = (OverridingInputProperty = "B"))
	float ConstB;

	UPROPERTY(EditAnywhere, Category = MaterialExpressionSMin, meta = (OverridingInputProperty = "K"))
	float ConstK;

#if WITH_EDITOR
	virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;
	virtual void GetCaption(TArray<FString>& OutCaptions) const override;
#endif
};