#include "Skeleton.h"

namespace Ship
{
    void SkeletonV0::ParseFileBinary(BinaryReader* reader, Resource* res)
    {
        Skeleton* skel = (Skeleton*)res;

        ResourceFile::ParseFileBinary(reader, skel);

        skel->type = (SkeletonType)reader->ReadByte();
        skel->limbType = (LimbType)reader->ReadByte();

        skel->limbCount = reader->ReadUInt32();
        skel->dListCount = reader->ReadUInt32();

        skel->limbTableType = (LimbType)reader->ReadByte();

        int limbTblCnt = reader->ReadUInt32();

        for (int i = 0; i < limbTblCnt; i++)
        {
            std::string limbPath = reader->ReadString();

            skel->limbTable.push_back(limbPath);
        }
    }
}