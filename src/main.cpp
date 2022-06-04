#include "CURLClient.h"
#include "DRPC.h"
#include <windows.h>

int main()
{
	std::string rpc_app_id;
	std::string vk_page;
	std::string cur_audio;
	DRPC*		discord_RPC;
	CURLClient* client;
	 
	std::cout << "Input url to your VK page: ";
	std::cin >> vk_page;
	
	rpc_app_id = "961771627996143706";

	discord_RPC = new DRPC(rpc_app_id.c_str());
	client = new CURLClient(vk_page.c_str());
	cur_audio = "a";

	while (true) 
	{
		Sleep(2500);
		std::string upd_audio = client->GetCurrentAudio();
		if (upd_audio != cur_audio)
		{
			cur_audio = upd_audio;
			client->UpdateAudioInfo(cur_audio);
			discord_RPC->update(client->GetAudioInfo());
		}
	};
}

