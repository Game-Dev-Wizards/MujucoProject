// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/MjGlobalSettings.h"
#include "Components/MjScene.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MujocoGIsubsystem.generated.h"

/**
 * 
 */
UCLASS()
class MUJOCOUE_API UMujocoGIsubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
	UFUNCTION(BlueprintCallable)
	UMjScene* GetCurrentMjScene() ;

	UFUNCTION(BlueprintCallable)
	UMjGlobalSettings* GetCurrentMjGlobalSettings() ;
	
private:
	UPROPERTY()
	UMjScene* MjSceneInstance;
	UPROPERTY()
	UMjGlobalSettings* MjGlobalSettings;
};
