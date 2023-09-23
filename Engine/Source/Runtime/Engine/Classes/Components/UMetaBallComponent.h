
#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Components/SceneComponent.h"
#include "UMetaBallComponent.generated.h"

class FMetaBallSceneInfo
{
public:
	float Distance;
	FVector3f WorldPos0;
	FVector3f WorldPos1;
	FVector3f WorldPos2;
	FLinearColor BallColor0;
	FLinearColor BallColor1;
	FLinearColor BallColor2;

	float BallSMin;
	float MetaBallRadius;
	float MetaBallTreshold;
	
	FLinearColor MetaBallColor;

	FMetaBallSceneInfo(){};
	FMetaBallSceneInfo(const class UMetaBallComponent* MetaBallComponent);

	// 所有的需要被渲染的Actors 最大支持256个 64个给Player
	TArray<FVector4f> Actors;
	TArray<AActor*> AllMetaBall;
	
	// 当前所有激活的Actor的数量，就是上面这个数组的有效长度
	int ActiveActorsCount = 0;
};

UCLASS(ClassGroup = Rendering, meta=(BlueprintSpawnableComponent))
class ENGINE_API UMetaBallComponent :public USceneComponent
{
	GENERATED_UCLASS_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=InscatteringTexture)
	FLinearColor MetaBallColor;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=InscatteringTexture)
	FLinearColor MetaBallColor0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=InscatteringTexture)
	FLinearColor MetaBallColor1;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=InscatteringTexture)
	FLinearColor MetaBallColor2;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=InscatteringTexture)
	float RayStep;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=InscatteringTexture)
	float MetaBallRadius;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=InscatteringTexture)
	float MetaBallTreshold;

	UPROPERTY()
	float Distance = 1.0f;
private:
	 FMetaBallSceneInfo * MetaBallSceneInfo;
protected:
	
	virtual void CreateRenderState_Concurrent(FRegisterComponentContext* Context) override;
	virtual void SendRenderTransform_Concurrent() override;
};
