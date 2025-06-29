// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MjComponent.h"
#include "mujoco/mujoco.h"

#include "Components/ActorComponent.h"
#include "MjScene.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MUJOCOUE_API UMjScene : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMjScene();

	mjModel* Model;
	mjData* Data;

	bool SceneRecreationAtLateUpdateRequested = false;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;


private:
	TArray<UMjComponent*> orderedComponents;



};
