// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActorTestAPI.h"

// Sets default values
AMyActorTestAPI::AMyActorTestAPI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyActorTestAPI::BeginPlay()
{
	Super::BeginPlay();


	// Example MJCF model as a string
	const char* xml_string = R"(
<mujoco model="ball">
  <option timestep="0.01"/>
  <worldbody>
    <body name="ball" pos="0 0 1">
      <joint type="free"/>
      <geom type="sphere" size="0.1" rgba="1 0 0 1"/>
    </body>
  </worldbody>
</mujoco>
)";


	// Activate license (optional with latest MuJoCo)
   // mj_activate("mjkey.txt");

	char error[1000];

	// Step 1: Parse XML string to mjSpec*
	mjSpec* spec = mj_parseXMLString(xml_string, nullptr, error, sizeof(error));
	if (!spec) {
		printf("XML Parse Error: %s\n", error);
		return ;
	}

	// Step 2: Compile spec to mjModel*
	mjModel* model = mj_compile(spec, nullptr);
   // Load the model
	//char error[1000] = "Could not load XML model";
	//mjModel* model = mj_loadXML(MODEL_PATH, nullptr, error, 1000);
	//mjModel* model = mj_parseXMLString(xml_string, nullptr, error, sizeof(error));

	if (!model) {
		printf("Error loading model: %s\n", error);
		return ;
	}

	// Create simulation data
	mjData* data = mj_makeData(model);

	// Run a basic simulation loop (e.g., 1000 steps)
	for (int i = 0; i < 1000; ++i) {
		mj_step(model, data);
	}

	// Print final position of the first body
	printf("Final position: x = %.3f y = %.3f z = %.3f\n",
		data->xpos[3 * 1 + 0], data->xpos[3 * 1 + 1], data->xpos[3 * 1 + 2]);

	GEngine->AddOnScreenDebugMessage(
		-1,                 // Key (-1 = auto)
		5.0f,               // Display time in seconds
		FColor::Green,      // Text color
		//TEXT("Hello from C++ in Unreal! %.5f") +// Message
		FString("MyValue: ") + FString::SanitizeFloat(data->xpos[3 * 1 + 2], 6) // 6 = precision
	);
	// Free MuJoCo model and data
	mj_deleteData(data);
	mj_deleteModel(model);
	// mj_deactivate();

	
}

// Called every frame
void AMyActorTestAPI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

