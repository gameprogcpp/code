#include "GPMeshExporterPrivatePCH.h"
#include "GPTextureExporterBMP.h"
#include "Logging/MessageLog.h"
#include "Runtime/ImageWrapper/Public/BmpImageSupport.h"

/*------------------------------------------------------------------------------
UTextureExporterBMP implementation.
------------------------------------------------------------------------------*/
UGPTextureExporterBMP::UGPTextureExporterBMP(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SupportedClass = UTexture2D::StaticClass();
	PreferredFormatIndex = 0;
	FormatExtension.Add(TEXT("BMP"));
	FormatDescription.Add(TEXT("Windows Bitmap"));

}

bool UGPTextureExporterBMP::ExportBinary(UObject* Object, const TCHAR* Type, FArchive& Ar, FFeedbackContext* Warn, int32 FileIndex, uint32 PortFlags)
{
	UTexture2D* Texture = CastChecked<UTexture2D>(Object);

	if (!Texture->Source.IsValid() || (Texture->Source.GetFormat() != TSF_BGRA8 && Texture->Source.GetFormat() != TSF_RGBA16))
	{
		return false;
	}

	const bool bIsRGBA16 = Texture->Source.GetFormat() == TSF_RGBA16;
	const int32 SourceBytesPerPixel = bIsRGBA16 ? 8 : 4;

// 	if (bIsRGBA16)
// 	{
// 		FMessageLog ExportWarning("EditorErrors");
// 		FFormatNamedArguments Arguments;
// 		Arguments.Add(TEXT("Name"), FText::FromString(Texture->GetName()));
// 		ExportWarning.Warning(FText::Format(FText("{Name}: Texture is RGBA16 and cannot be represented at such high bit depth in .bmp. Color will be scaled to RGBA8."), Arguments));
// 		ExportWarning.Open(EMessageSeverity::Warning);
// 	}

	int32 SizeX = Texture->Source.GetSizeX();
	int32 SizeY = Texture->Source.GetSizeY();
	TArray<uint8> RawData;
	Texture->Source.GetMipData(RawData, 0);

	FBitmapFileHeader bmf;
	FBitmapInfoHeader bmhdr;

	// File header.
	bmf.bfType = 'B' + (256 * (int32)'M');
	bmf.bfReserved1 = 0;
	bmf.bfReserved2 = 0;
	int32 biSizeImage = SizeX * SizeY * 3;
	bmf.bfOffBits = sizeof(FBitmapFileHeader) + sizeof(FBitmapInfoHeader);
	bmhdr.biBitCount = 24;

	bmf.bfSize = bmf.bfOffBits + biSizeImage;
	Ar << bmf;

	// Info header.
	bmhdr.biSize = sizeof(FBitmapInfoHeader);
	bmhdr.biWidth = SizeX;
	bmhdr.biHeight = SizeY;
	bmhdr.biPlanes = 1;
	bmhdr.biCompression = BCBI_RGB;
	bmhdr.biSizeImage = biSizeImage;
	bmhdr.biXPelsPerMeter = 0;
	bmhdr.biYPelsPerMeter = 0;
	bmhdr.biClrUsed = 0;
	bmhdr.biClrImportant = 0;
	Ar << bmhdr;


	// Upside-down scanlines.
	for (int32 i = SizeY - 1; i >= 0; i--)
	{
		uint8* ScreenPtr = &RawData[i*SizeX*SourceBytesPerPixel];
		for (int32 j = SizeX; j>0; j--)
		{
			if (bIsRGBA16)
			{
				Ar << ScreenPtr[1];
				Ar << ScreenPtr[3];
				Ar << ScreenPtr[5];
				ScreenPtr += 8;
			}
			else
			{
				Ar << ScreenPtr[0];
				Ar << ScreenPtr[1];
				Ar << ScreenPtr[2];
				ScreenPtr += 4;
			}
		}
	}
	return true;
}