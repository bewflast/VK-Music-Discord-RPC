#include <DRPC.h>


void DRPC::init()
{
	this->handler = new DiscordEventHandlers();
	this->presence = new DiscordRichPresence();
	Discord_Initialize(this->cid, this->handler, NULL, NULL);
	Discord_UpdatePresence(this->presence);
}

void DRPC::update(t_audioInfo info)
{
	this->presence->largeImageKey = info.cover.c_str();
	this->presence->state = info.artist.c_str();
	this->presence->details = info.title.c_str();
	Discord_UpdatePresence(this->presence);
}

DRPC::DRPC(const char* cID)
{
	this->cid = cID;
	this->init();
}