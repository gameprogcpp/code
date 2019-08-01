// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#include "GPMeshExporterPrivatePCH.h"
#include "AnimExporterGP.h"
#include "Animation/AnimSequence.h"

UAnimExporterGP::UAnimExporterGP(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SupportedClass = UAnimSequence::StaticClass();
	bText = true;
	PreferredFormatIndex = 0;
	FormatExtension.Add(TEXT("gpanim"));
	FormatDescription.Add(TEXT("GP Animation File"));
}

bool UAnimExporterGP::ExportText(const FExportObjectInnerContext* Context, UObject* Object, const TCHAR* Type, FOutputDevice& Ar, FFeedbackContext* Warn, uint32 PortFlags /*= 0*/)
{
	UAnimSequence* AnimSeq = CastChecked<UAnimSequence>(Object);

	USkeleton* Skeleton = AnimSeq->GetSkeleton();
	const FReferenceSkeleton& RefSkeleton = Skeleton->GetReferenceSkeleton();
	USkeletalMesh* SkelMesh = Skeleton->GetPreviewMesh();
	if (AnimSeq->SequenceLength == 0.f)
	{
		// something is wrong
		return false;
	}

	int32 NumFrames = AnimSeq->GetRawNumberOfFrames();
	const float FrameRate = NumFrames / AnimSeq->SequenceLength;

	// Open another archive
	FArchive* File = IFileManager::Get().CreateFileWriter(*UExporter::CurrentFilename);

	// Let's try the header...
	File->Logf(TEXT("{"));
	File->Logf(TEXT("\t\"version\":1,"));

	File->Logf(TEXT("\t\"sequence\":{"));
	File->Logf(TEXT("\t\t\"frames\":%d,"), NumFrames);
	File->Logf(TEXT("\t\t\"length\":%f,"), AnimSeq->SequenceLength);
	File->Logf(TEXT("\t\t\"bonecount\":%d,"), RefSkeleton.GetNum());
	File->Logf(TEXT("\t\t\"tracks\":["));

	bool firstOutput = false;

	for (int32 BoneIndex = 0; BoneIndex < RefSkeleton.GetNum(); ++BoneIndex)
	{
		//int32 BoneTreeIndex = Skeleton->GetSkeletonBoneIndexFromMeshBoneIndex(SkelMesh, BoneIndex);
		int32 BoneTrackIndex = Skeleton->GetAnimationTrackIndex(BoneIndex, AnimSeq, true);
		
		if (BoneTrackIndex == INDEX_NONE && BoneIndex != 0)
		{
			// If this sequence does not have a track for the current bone, then skip it
			continue;
		}
	
		if (firstOutput)
		{
			File->Logf(TEXT("\t\t\t},"));
		}

		firstOutput = true;

		File->Logf(TEXT("\t\t\t{"));
		File->Logf(TEXT("\t\t\t\t\"bone\":%d,"), BoneIndex);
		File->Logf(TEXT("\t\t\t\t\"transforms\":["));
		float AnimTime = 0.0f;
		float AnimEndTime = AnimSeq->SequenceLength;
		// Subtracts 1 because NumFrames includes an initial pose for 0.0 second
		double TimePerKey = (AnimSeq->SequenceLength / (NumFrames - 1));
		const float AnimTimeIncrement = TimePerKey;

		bool bLastKey = false;
		// Step through each frame and add the bone's transformation data
		while (!bLastKey)
		{
			const TArray<FBoneNode>& BoneTree = Skeleton->GetBoneTree();

			FTransform BoneAtom;
			if (BoneTrackIndex != INDEX_NONE)
			{
				AnimSeq->GetBoneTransform(BoneAtom, BoneTrackIndex, AnimTime, true);
			}
			else
			{
				BoneAtom.SetIdentity();
			}

			bLastKey = AnimTime >= AnimEndTime;

			File->Logf(TEXT("\t\t\t\t\t{"));

			FQuat rot = BoneAtom.GetRotation();
			// For the root bone, we need to fix-up the rotation because Unreal exports
			// animations with Y-forward for some reason (maybe because Maya?)
			if (BoneIndex == 0)
			{
				FQuat addRot(FVector(0.0f, 0.0f, 1.0f), -1.57f);
				rot = addRot * rot;
			}
			File->Logf(TEXT("\t\t\t\t\t\t\"rot\":[%f,%f,%f,%f],"), rot.X, rot.Y, rot.Z, rot.W);
			FVector trans = BoneAtom.GetTranslation();

			// Sanjay: If it's skeleton retargeting, change the translation to be from the ref pose skeleton
			if (BoneTree[BoneIndex].TranslationRetargetingMode == EBoneTranslationRetargetingMode::Skeleton)
			{
				const FTransform& BoneTransform = RefSkeleton.GetRefBonePose()[BoneIndex];
				trans = BoneTransform.GetTranslation();
			}

			File->Logf(TEXT("\t\t\t\t\t\t\"trans\":[%f,%f,%f]"), trans.X, trans.Y, trans.Z);

			if (!bLastKey)
			{
				File->Logf(TEXT("\t\t\t\t\t},"));
			}
			else
			{
				File->Logf(TEXT("\t\t\t\t\t}"));
			}
			

			AnimTime += AnimTimeIncrement;
		}

		File->Logf(TEXT("\t\t\t\t]"), BoneIndex);
	}

	File->Logf(TEXT("\t\t\t}"));
	File->Logf(TEXT("\t\t]"));
	File->Logf(TEXT("\t}"));

 	File->Logf(TEXT("}"));
 	delete File;

	return true;
}
