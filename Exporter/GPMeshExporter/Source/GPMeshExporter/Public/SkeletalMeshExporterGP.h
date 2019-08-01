// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

//=============================================================================
// StaticMeshExporterOBJ
//=============================================================================

#pragma once
#include "Exporters/Exporter.h"
#include "Rendering/SkeletalMeshLODModel.h"
#include "SkeletalMeshExporterGP.generated.h"

UCLASS()
class USkeletalMeshExporterGP : public UExporter
{
	GENERATED_UCLASS_BODY()


	// Begin UExporter Interface
	virtual bool ExportText(const FExportObjectInnerContext* Context, UObject* Object, const TCHAR* Type, FOutputDevice& Ar, FFeedbackContext* Warn, uint32 PortFlags = 0) override;
	// End UExporter Interface
	virtual bool ExportSkeleton(const struct FReferenceSkeleton& RefSkeleton, const FString& currFileName);

	void GetVertices(const class FSkeletalMeshLODModel& Model, TArray<FSoftSkinVertex>& Vertices) const;

	class UGPTextureExporterBMP* BMPExporter;
};



