// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "mujoco/mujoco.h"
#include "tinyxml2.h"
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
	virtual  void OnSyncState(mjData* data);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	mjtObj* ObjectType;
	virtual bool IsSuppressNameAttribute() const { return false; }
	virtual void ParseMjcf(tinyxml2::XMLElement* mjcf);
	virtual tinyxml2::XMLElement* OnGenerateMjcf(tinyxml2::XMLDocument* doc);
	virtual void OnBindToRuntime(mjModel* model, mjData* data) ;

	virtual void OnEnable() ;

	virtual void Update();



public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void BindToRuntime(mjModel* model, mjData* data);

	tinyxml2::XMLElement* GenerateMjcf(FString name, tinyxml2::XMLDocument* doc);
	void OnApplicationQuit();
	void OnDisable();



private:
	FString MujocoName; // Private variable
	int MujocoID; // Private variable
	bool _sceneExcludesMe = false;
	bool _exiting = false;


};
