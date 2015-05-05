#include "../../libmot/src/mot.h"

#include "slideshow.h"

TriggerTime::TriggerTime() // NOW
	: HeaderParameter(0x05), timepoint(0)
{ }

TriggerTime::TriggerTime(int timepoint)
	: HeaderParameter(0x05), timepoint(timepoint)
{ }

bool TriggerTime::equals(const HeaderParameter& other) const
{
    const TriggerTime* that = dynamic_cast<const TriggerTime*>(&other);
    return that != nullptr && (this->timepoint == that->timepoint);
}

vector<unsigned char> TriggerTime::encodeData()
{
	return mot::timepoint_to_encoded_utc(timepoint);
}



