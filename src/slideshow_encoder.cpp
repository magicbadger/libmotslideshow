#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>

#include <mot.h>
#include <contenttypes.h>
#include <datagroups.h>
#include <packets.h>

#include <curl/curl.h>

using namespace std;
using namespace mot;
using namespace msc;

struct MemoryStruct {
  char *memory;
  size_t size;
};

static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;

  mem->memory = (char *)realloc(mem->memory, mem->size + realsize + 1);
  if(mem->memory == nullptr) {
    /* out of memory! */
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }

  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}


int main(int argc, char* argv[])
{
	CURL *curl_handle;
	CURLcode res;

	struct MemoryStruct chunk;

	chunk.memory = (char *)malloc(1);  /* will be grown as needed by the realloc above */
	chunk.size = 0;    /* no data at this point */

	curl_global_init(CURL_GLOBAL_ALL);

	/* init the curl session */
	curl_handle = curl_easy_init();

	/* specify URL to get */
    string url("http://owdo.thisisglobal.com/2.0/id/25/logo/320x240.jpg");
    cout << "downloading image from: " << url << endl;
	curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());

	/* send all data to this function  */
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

	/* we pass our 'chunk' struct to the callback function */
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);

	/* some servers don't like requests that are made without a user-agent
	 field, so we provide one */
	curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

	/* get it! */
	res = curl_easy_perform(curl_handle);

	/* check for errors */
	if(res != CURLE_OK) {
	fprintf(stderr, "curl_easy_perform() failed: %s\n",
			curl_easy_strerror(res));
	}

	/* cleanup curl stuff */
	curl_easy_cleanup(curl_handle);

	// transform to vector
	std::vector<unsigned char> bytes;
	bytes.assign(chunk.memory, chunk.memory + chunk.size);
	printf("%lu bytes retrieved\n", (long)bytes.size());

	if(chunk.memory)
	free(chunk.memory);

	/* we're done with libcurl, so clean it up */
	curl_global_cleanup();

	RandomTransportIdGenerator* id = RandomTransportIdGenerator::getInstance();
	MotObject o(id->next(), "capital.jpg", bytes, ContentTypes::Image::JFIF);
	o.addParameter(new MimeType("image/jpeg"));
	cout << "transport id: " << o.getTransportId() << endl;
	SegmentEncoder segment_encoder;
	vector<Segment*> segments = segment_encoder.encode(o);
	cout << "encoded into " << segments.size() << " segments" << endl;
    DatagroupEncoder datagroup_encoder;
    vector<Datagroup*> datagroups = datagroup_encoder.encode_datagroups(segments);
	cout << "encoded into " << datagroups.size() << " datagroups" << endl;
    PacketEncoder packet_encoder(1, 96);
    vector<Packet*> packets = packet_encoder.encode_packets(datagroups);
	cout << "encoded into " << packets.size() << " packets" << endl;
	for(Packet* packet : packets)
	{
		cout << packet->encode();
    }

  return 0;
}
