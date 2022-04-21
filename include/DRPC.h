#ifndef DRPC_H
#define DRPC_H

# include <discord_register.h>
# include <discord_rpc.h>
# include <CURLClient.h>
# include <iostream>
# include <ctime>

class DRPC
{
	private:
		DiscordEventHandlers *handler;
		DiscordRichPresence *presence;
		const char* cid;

	public:
		DRPC(const char* cID);
		void init();
		void update(t_audioInfo info);

};

#endif 
