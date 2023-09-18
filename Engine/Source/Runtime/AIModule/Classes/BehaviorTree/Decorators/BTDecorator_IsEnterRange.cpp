#include "BTDecorator_IsEnterRange.h"
#include "AIController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_IsEnterRange::UBTDecorator_IsEnterRange(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Is Enter Range";
	INIT_DECORATOR_NODE_NOTIFY_FLAGS();
}

FString UBTDecorator_IsEnterRange::GetStaticDescription() const
{
	return FString("Target Actor is In Range");
}

bool UBTDecorator_IsEnterRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
	UObject* KeyValue = MyBlackboard->GetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID());
	const AActor* TargetActor = Cast<AActor>(KeyValue);

	if(TargetActor)
	{
		FVector Vector = TargetActor->GetActorLocation() - OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();
		return Vector.Length() <= Range;
	}
	return false;
}

