// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "mujoco/mujoco.h"
#include "Components/ActorComponent.h"
#include "MjComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MUJOCOUE_API UMjComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMjComponent();

	FString GetMujocoName() const; // Public getter
	int GetMujocoID() const; // Public getter
	mjtObj* GetObjectType()const;	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	mjtObj* ObjectType;
	virtual bool IsSuppressNameAttribute() const { return false; }

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;


private:
	FString MujocoName; // Private variable
	int MujocoID; // Private variable
	

};
