// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGameLoading.h"
#include "MoviePlayer.h"
#include "SlateBasics.h"
#include "SlateExtras.h"

#define LOADING_SCREEN_MATERIAL_PATH TEXT("/Game/GUI/Materials/LoadingScreen/LoadingScreen.LoadingScreen")

// The brush to use for the loading screen. This is simply our static background image.
struct FValorGameLoadingModuleBrush : public FSlateDynamicImageBrush, public FGCObject
{
	FValorGameLoadingModuleBrush(const FName InTextureName, const FVector2D& InImageSize)
		: FSlateDynamicImageBrush(InTextureName, InImageSize)
	{
		ResourceObject = LoadObject<UObject>(nullptr, *InTextureName.ToString());
	}

	virtual void AddReferencedObjects(FReferenceCollector& Collector)
	{
		if (ResourceObject)
		{
			Collector.AddReferencedObject(ResourceObject);
		}
	}
};

// The widget to use as the in-game loading screen. This widget will display on top
// of any movies we decide to use.
class SValorGameLoadingModuleWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SValorGameLoadingModuleWidget) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs)
	{
		static const FName LoadingBackgroundMaterialPath(LOADING_SCREEN_MATERIAL_PATH);

		LoadingScreenBrush = MakeShareable(new FValorGameLoadingModuleBrush(LoadingBackgroundMaterialPath, FVector2D(1920, 1080)));

		ChildSlot
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SImage)
				.Image(LoadingScreenBrush.Get())
			]
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SSafeZone)
				.VAlign(VAlign_Bottom)
				.HAlign(HAlign_Right)
				.Padding(10.0f)
				.IsTitleSafe(true)
				[
					SNew(SThrobber)
					.Visibility(this, &SValorGameLoadingModuleWidget::GetLoadIndicatorVisibility)
				]
			]
		];
	}

private:
	EVisibility GetLoadIndicatorVisibility() const
	{
		return EVisibility::Visible;
	}

	/** loading screen image brush */
	TSharedPtr<FSlateDynamicImageBrush> LoadingScreenBrush;
};

class FValorGameLoadingModule : public IValorGameLoadingModule
{
public:

	virtual void StartupModule() override
	{
		// Load for cooker reference
		//@TODO This was taken from ShooterGame. Is it actually necessary?
		LoadObject<UObject>(NULL, LOADING_SCREEN_MATERIAL_PATH);

		if (IsMoviePlayerEnabled())
		{
			FLoadingScreenAttributes LoadingScreen;
			LoadingScreen.bAutoCompleteWhenLoadingCompletes = true;
			LoadingScreen.bMoviesAreSkippable = false;
			LoadingScreen.MoviePaths.Add(TEXT("LoadingScreen"));
			GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
		}
	}

	virtual bool IsGameModule() const override
	{
		return true;
	}

	virtual void StartLoadingScreen() override
	{
		FLoadingScreenAttributes LoadingScreen;
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = true;
		//LoadingScreen.WidgetLoadingScreen = SNew(SShooterLoadingScreen2);

		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}
};

IMPLEMENT_GAME_MODULE(FValorGameLoadingModule, ValorGameLoading);