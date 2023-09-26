#pragma once

# include <curl/curl.h>
# include <iostream>

typedef struct s_audioInfo
{
	std::string artist;
	std::string title;
	std::string cover;

} t_audioInfo;

class CURLClient
{
	private:
		const char*				vk_page;
		CURL*					curl;
		t_audioInfo				audio;

		std::size_t				(*writeFunc)(char*, size_t, size_t, std::string*);
		std::string				getHTML(const char* url);
		void					initCURL();
		bool					isListeningAudio(std::size_t audio_pos, std::string html);
		std::string				GetAlbumCover(std::string url);
		bool					isValidAudio(std::string html);
		void					SetAudioInfo(std::string artist, std::string title, std::string cover);



	public:
		CURLClient(const char* vk_page);
		std::string		GetCurrentAudio();
		t_audioInfo		GetAudioInfo();
		void			UpdateAudioInfo(std::string audio_link);

};