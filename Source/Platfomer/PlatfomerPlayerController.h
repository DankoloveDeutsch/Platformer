// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlatfomerPlayerController.generated.h"

class UInputMappingContext;

/**
 *
 */
UCLASS()
class PLATFOMER_API APlatfomerPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	
	// Begin Actor interface
protected:

	virtual void BeginPlay() override;
	
	// End Actor interface
public:
	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;


	void SetinputUIOnly();
};
