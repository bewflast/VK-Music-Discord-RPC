#include <CURLClient.h>
#include <DRPC.h>
#include <windows.h>

int main()
{
	const char* rpc_app_id;
	const char* vk_page;
	DRPC*		discord_RPC;
	CURLClient* client;
	std::string cur_audio;
	 
	vk_page = ""; // url to your vk page (e.g https://vk.com/durov)
	rpc_app_id = ""; //client id of your app (e.g 961721607396193104)
	discord_RPC = new DRPC(rpc_app_id);
	client = new CURLClient(vk_page);
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

