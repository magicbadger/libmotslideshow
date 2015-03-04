#include <mot.h>

TriggerTime::TriggerTime() // NOW
	: HeaderParameter(0x05), timepoint(0)
{ }

TriggerTime::TriggerTime(long timepoint)
	: HeaderParameter(0x05), timepoint(timepoint)
{ }

bool TriggerTime::equals(const HeaderParameter& other) const
{
    const TriggerTime* that = dynamic_cast<const TriggerTime*>(&other);
    return that != nullptr && (this->timepoint == that->timepoint);
}

vector<unsigned char> TriggerTime::encode()
{
	bitset<8> bits(charset); // charset(4)

	vector<unsigned char> bytes = bits_to_bytes(bits);
	copy(name.begin(), name.end(), back_inserter(bytes));

	return bytes;
}



