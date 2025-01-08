// Copyright Zero Games. All Rights Reserved.

#pragma once

class IZeroGameFrameworkRuntimeModule : public IModuleInterface
{
public:
	static FORCEINLINE IZeroGameFrameworkRuntimeModule& Get()
	{
		static IZeroGameFrameworkRuntimeModule& GSingleton = FModuleManager::LoadModuleChecked<IZeroGameFrameworkRuntimeModule>("ZeroGameFrameworkRuntime");
		return GSingleton;
	}

	static FORCEINLINE bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("ZeroGameFrameworkRuntime");
	}
};


