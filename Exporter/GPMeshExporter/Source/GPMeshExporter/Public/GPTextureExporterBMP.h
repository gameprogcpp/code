// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

//=============================================================================
// TextureExporterBMP
//=============================================================================

#pragma once
#include "Exporters/Exporter.h"
#include "GPTextureExporterBMP.generated.h"

UCLASS()
class UGPTextureExporterBMP : public UExporter
{
	GENERATED_UCLASS_BODY()


	bool ExportBinary(UObject* Object, const TCHAR* Type, FArchive& Ar, FFeedbackContext* Warn, int32 FileIndex = 0, uint32 PortFlags = 0) override;
};



