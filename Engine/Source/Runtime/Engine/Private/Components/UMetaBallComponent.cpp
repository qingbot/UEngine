//#include"Components/UMetaBallComponent.h"
#include "Engine/Classes/Components/UMetaBallComponent.h"



FMetaBallSceneInfo::FMetaBallSceneInfo(const UMetaBallComponent* MetaBallComponent)
{
	Distance = MetaBallComponent->Distance;
	MetaBallColor = MetaBallComponent->MetaBallColor;
	WorldPos0 = FVector3f::Zero();
	WorldPos1 = FVector3f::Zero();
	WorldPos2 = FVector3f::Zero();
	BallColor0 = FLinearColor::Black;
	BallColor1 = FLinearColor::Black;
	BallColor2 = FLinearColor::Black;
	RayStep = 1;
	MetaBallRadius = 1;
}

UMetaBallComponent::UMetaBallComponent(const FObjectInitializer& objInit): Super(objInit)
{
	MetaBallSceneInfo = new FMetaBallSceneInfo(this);
}

void UMetaBallComponent::CreateRenderState_Concurrent(FRegisterComponentContext* Context)
{
	Super::CreateRenderState_Concurrent(Context);
	SendRenderTransform_Concurrent();
	//GetWorld()->Scene->AddMetaBallRender(MetaBallSceneInfo);
}

void UMetaBallComponent::SendRenderTransform_Concurrent()
{
	
	GetWorld()->Scene->RemoveMetaBallRender();
	MetaBallSceneInfo->Distance = Distance;
	MetaBallSceneInfo->MetaBallColor = MetaBallColor;

	MetaBallSceneInfo->BallColor0 = MetaBallColor0;
	MetaBallSceneInfo->BallColor1 = MetaBallColor1;
	MetaBallSceneInfo->BallColor2 = MetaBallColor2;

	MetaBallSceneInfo->RayStep = RayStep;
	MetaBallSceneInfo->MetaBallRadius = MetaBallRadius;
	MetaBallSceneInfo->MetaBallTreshold = MetaBallTreshold;

	TArray<TObjectPtr<USceneComponent>> childs = GetAttachChildren();

	if(childs.Num() < 3)
	{
		MetaBallSceneInfo->WorldPos0 = FVector3f::Zero();
		MetaBallSceneInfo->WorldPos1 = FVector3f::Zero();
		MetaBallSceneInfo->WorldPos2 = FVector3f::Zero();
	}
	else{
		
		UE::Math::TVector<double> l0 = childs[0]->GetComponentLocation();
		UE::Math::TVector<double> l1 = childs[1]->GetComponentLocation();
		UE::Math::TVector<double> l2 = childs[2]->GetComponentLocation();
		
		MetaBallSceneInfo->WorldPos0.X = static_cast<float>(l0.X);  
		MetaBallSceneInfo->WorldPos0.Y = static_cast<float>(l0.Y);  
		MetaBallSceneInfo->WorldPos0.Z = static_cast<float>(l0.Z);
	
		MetaBallSceneInfo->WorldPos1.X = static_cast<float>(l1.X);  
		MetaBallSceneInfo->WorldPos1.Y = static_cast<float>(l1.Y);  
		MetaBallSceneInfo->WorldPos1.Z = static_cast<float>(l1.Z);
	
		MetaBallSceneInfo->WorldPos2.X = static_cast<float>(l2.X);  
		MetaBallSceneInfo->WorldPos2.Y = static_cast<float>(l2.Y);  
		MetaBallSceneInfo->WorldPos2.Z = static_cast<float>(l2.Z);
    }
	
	GetWorld()->Scene->AddMetaBallRender(MetaBallSceneInfo);
}
