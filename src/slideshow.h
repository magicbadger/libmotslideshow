#ifndef SLIDESHOW_H_
#define SLIDESHOW_H_

class TriggerTime : public HeaderParameter
{

public:

	TriggerTime(long timepoint);

	vector<unsigned char> encode();

protected:

	bool equals(const HeaderParameter& a) const;

private:
	private long timepoint;
};



#endif /* SLIDESHOW_H_ */
