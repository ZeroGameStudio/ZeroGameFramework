// Copyright Zero Games. All Rights Reserved.

#include "ZeroGameFrameworkEditorModule.h"

class FZeroGameFrameworkEditorModule : public IZeroGameFrameworkEditorModule
{
	// Begin IModuleInterface
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	// End IModuleInterface
};

IMPLEMENT_MODULE(FZeroGameFrameworkEditorModule, ZeroGameFrameworkEditor)

void FZeroGameFrameworkEditorModule::StartupModule()
{
}

void FZeroGameFrameworkEditorModule::ShutdownModule()
{
}


