#include "OTRPlayerAnimationFactory.h"

namespace OtrLib
{
    OTRPlayerAnimation* OTRPlayerAnimationFactory::ReadPlayerAnimation(BinaryReader* reader)
    {
        OTRPlayerAnimation* anim = new OTRPlayerAnimation();

        OTRVersion version = (OTRVersion)reader->ReadUInt32();

        switch (version)
        {
        case OTRVersion::Deckard:
        {
            OTRPlayerAnimationV0 otrAnim = OTRPlayerAnimationV0();
            otrAnim.ParseFileBinary(reader, anim);
        }
        break;
        default:
            // VERSION NOT SUPPORTED
            break;
        }

        return anim;

    }
}