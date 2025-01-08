// Copyright Zero Games. All Rights Reserved.

#pragma once

class IZeroGameFrameworkEditorModule : public IModuleInterface
{
public:
	static FORCEINLINE IZeroGameFrameworkEditorModule& Get()
	{
		static IZeroGameFrameworkEditorModule& GSingleton = FModuleManager::LoadModuleChecked<IZeroGameFrameworkEditorModule>("ZeroGameFrameworkEditor");
		return GSingleton;
	}

	static FORCEINLINE bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("ZeroGameFrameworkEditor");
	}
};


