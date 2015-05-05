#ifndef SLIDESHOW_H_
#define SLIDESHOW_H_

using namespace mot;

class TriggerTime : public HeaderParameter
{

public:

	TriggerTime();

	TriggerTime(int timepoint);

	vector<unsigned char> encodeData();

protected:

	bool equals(const HeaderParameter& a) const;

private:

	int timepoint;
};



#endif /* SLIDESHOW_H_ */
