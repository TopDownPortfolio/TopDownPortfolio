#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_MakeHeightMap.generated.h"

class ALandscape;
class ULandscapeInfo;
enum class ELandscapeImportTransformType : int8;
class UTexture2D;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNPORTFOLIO_API UC_MakeHeightMap : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	ALandscape* m_pLandscape;
	ULandscapeInfo* m_pLandscapeInfo;
	FIntRect m_fLandScapeSize;
	TArray<uint16> m_arHeightData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"), meta = (AllowPrivateAccess = "true"))
	float m_fFactor = 37.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString m_ExportFileName = "Heightmap";
	FString m_ImportFileName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool m_bGenerateHeightMap;
	bool m_bImportHeightMap = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool m_bExportHeightMap;
private:
	int m_nStride;
	int m_nMapSize;
	int m_nDX[4] = { -1,-1,1,1 };
	int m_nDY[4] = { -1,1,-1,1 };
	int m_nSX[4] = { -1,1 ,0,0 };
	int m_nSY[4] = { 0,0,-1 ,1 };
protected:
	virtual void OnRegister() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	bool E_Init_SetLandscapeData();
	bool E_Init_SetData();
	void E_GenerateHeightMap();
	void E_UpdateLandscape();
	void E_ExportHeightMap();
	void E_ImportHeightMap();
	int E_Logic(int nDist);
	void E_CalCul(int X, int Y, const int* dX, const int* dY, uint16 S);

	int E_GetArrIndex(int X, int Y);
	uint16* E_GetHeightMap(int X, int Y);
	float E_GetRoughnessFactor(uint16 S);

	FString E_GetFilePath(FString& strFileName);
private:

	//template<class T>
	//void ImportDataInternal(ULandscapeInfo* LandscapeInfo, const FString& Filename, FName LayerName, bool bSingleFile, bool bFlipYAxis, const FIntRect& ImportRegionVerts, ELandscapeImportTransformType TransformType, FIntPoint Offset, TFunctionRef<void(int32, int32, int32, int32, const TArray<T>&)> SetDataFunc);

};
