#pragma once
#include "GameFramework/PlayerController.h"
#include "DrForkPlayerController.generated.h"

UCLASS()
class ADrForkPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ADrForkPlayerController(const FObjectInitializer& ObjectInitializer);
};