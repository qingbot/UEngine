#include "BTDecorator_IsCanFire.h"
#include "AIController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_IsCanFire::UBTDecorator_IsCanFire(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Is Can Fire Or Try Fire";
	INIT_DECORATOR_NODE_NOTIFY_FLAGS();
}

FString UBTDecorator_IsCanFire::GetStaticDescription() const
{
	return FString("Is Can Fire Or Try Fire");
}

bool UBTDecorator_IsCanFire::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAIController* Controller = OwnerComp.GetAIOwner();
	bool Result = Controller->CanFire();
	if(Result) return Result;
	else{
		Controller->OnAnyEnemyEnterToRange();
	}
	return Result;
}
