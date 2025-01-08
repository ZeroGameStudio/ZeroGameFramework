// Copyright Zero Games. All Rights Reserved.

#include "ZeroGameFrameworkRuntimeModule.h"

class FZeroGameFrameworkRuntimeModule : public IZeroGameFrameworkRuntimeModule
{
	// Begin IModuleInterface
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	// End IModuleInterface
};

IMPLEMENT_MODULE(FZeroGameFrameworkRuntimeModule, ZeroGameFrameworkRuntime)

void FZeroGameFrameworkRuntimeModule::StartupModule()
{
}

void FZeroGameFrameworkRuntimeModule::ShutdownModule()
{
}


