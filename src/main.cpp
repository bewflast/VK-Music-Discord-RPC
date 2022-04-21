#include <CURLClient.h>
#include <DRPC.h>
#include <windows.h>

int main()
{
	const char* rpc_client_id;
	const char* vk_page;
	DRPC*		discord_RPC;
	CURLClient* client;
	std::string cur_audio;
	 
	vk_page = ""; // url to your vk page (e.g https://vk.com/durov)
	rpc_client_id = ""; //client id of your app (e.g 961721607396193104)
	discord_RPC = new DRPC(rpc_client_id);
	client = new CURLClient(vk_page);
	cur_audio = "a";

	while (true) 
	{
		Sleep(2500);
		if (client->GetCurrentAudio() != cur_audio)
		{
			cur_audio = client->GetCurrentAudio();
			client->UpdateAudioInfo(cur_audio);
			discord_RPC->update(client->GetAudioInfo());
		}
	};
}

