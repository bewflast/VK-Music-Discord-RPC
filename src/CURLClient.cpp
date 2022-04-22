#include "CURLClient.h"
#include <string>

static std::string cp1251_to_utf8(const char* str)
{
	std::string res;
	int result_u, result_c;
	result_u = MultiByteToWideChar(1251, 0, str, -1, 0, 0);
	if (!result_u) { return 0; }
	wchar_t* ures = new wchar_t[result_u];
	if (!MultiByteToWideChar(1251, 0, str, -1, ures, result_u)) {
		delete[] ures;
		return 0;
	}
	result_c = WideCharToMultiByte(65001, 0, ures, -1, 0, 0, 0, 0);
	if (!result_c) {
		delete[] ures;
		return 0;
	}
	char* cres = new char[result_c];
	if (!WideCharToMultiByte(65001, 0, ures, -1, cres, result_c, 0, 0)) {
		delete[] cres;
		return 0;
	}
	delete[] ures;
	res.append(cres);
	delete[] cres;
	return res;
}

static std::string get_track_info(std::string html)
{
	std::size_t t_info_start;
	std::size_t t_info_end; 

	for (t_info_end = html.find("\"profile_info profile_info_short"); !(html[t_info_end] == 'a' && html[t_info_end - 1] == '/' && html[t_info_end - 2] == '<'); t_info_end--);
	for (t_info_start = t_info_end - 3; html[t_info_start] != '>'; t_info_start--);

	return (cp1251_to_utf8(html.substr(t_info_start + 1, t_info_end - t_info_start - 3).c_str()));
}

std::size_t	curl_write(char* data, size_t size, size_t nmemb, std::string* buffer)
{
	size_t result = 0;

	if (buffer != NULL)
	{
		buffer->append(data, size * nmemb);
		result = size * nmemb;
	}
	return result;
}

void	CURLClient::SetAudioInfo(std::string artist, std::string title, std::string cover)
{
	this->audio.artist = artist;
	this->audio.title = title;
	this->audio.cover = cover;
}

t_audioInfo CURLClient::GetAudioInfo()
{
	return (this->audio);
}

void	CURLClient::initCURL()
{
	curl_easy_setopt(this->curl, CURLOPT_HTTPGET, 1L);
	curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, this->writeFunc);
	curl_easy_setopt(this->curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:57.0) Gecko/20100101 Firefox/57.0");
}

std::string	CURLClient::getHTML(const char* url)
{
	std::string buff;

	this->initCURL();
	curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, &buff);
	curl_easy_setopt(this->curl, CURLOPT_URL, url);
	curl_easy_perform(this->curl);
	curl_easy_reset(this->curl);

	return(buff);
}

bool	CURLClient::isListeningAudio(std::size_t audio_pos, std::string html)
{

	return (audio_pos != html.npos);
}

bool CURLClient::isValidAudio(std::string html)
{
	return (html[0]);
}

void	CURLClient::UpdateAudioInfo(std::string audio_link)
{
	std::size_t delim_pos;
	std::string track_info;
	std::string artist;
	std::string title;
	std::string	html;

	if (!audio_link[0])
	{
		this->SetAudioInfo("Listens nothing", "Idle", "https://buzurdgkp2mzur.ru/images/stories/vk.png");
		return;
	}

	delim_pos = 0;
	html = this->getHTML(this->vk_page);
	track_info = get_track_info(html);

	for (auto c : track_info)
		if ((int)c != -30)
			delim_pos++;
		else
			break;

	artist = track_info.substr(0, delim_pos);
	title = track_info.substr(delim_pos + 4, track_info.length() - artist.length());
	this->SetAudioInfo(artist, title, this->GetAlbumCover(audio_link));
}

std::string	CURLClient::GetCurrentAudio()
{
	std::size_t	audio_link_pos;
	std::string	html;
	std::string	audio_link;

	html = this->getHTML(this->vk_page);
	audio_link_pos = html.find("data-audio=");
	audio_link = "\0";

	if (this->isListeningAudio(audio_link_pos, html))
		audio_link = html.substr(audio_link_pos + 12, html.find("\" data-live=") - audio_link_pos - 12);

	return (audio_link);
}

std::string CURLClient::GetAlbumCover(std::string url)
{
	std::size_t	cover_start_pos;
	std::size_t	cover_end_pos;
	std::string	html;

	html = this->getHTML(("https://vk.com/audio" + url).c_str());

	if (!this->isValidAudio(html))
	{
		std::cout << "Failed to fetch track's cover image! Setting VK's logo." << std::endl;
		return ("https://buzurdgkp2mzur.ru/images/stories/vk.png");
	}

	cover_start_pos = html.find("<div class=\"AudioPlaylistSnippet__cover\" style=\"background-image:url(\'") + 70;
	for (cover_end_pos = cover_start_pos; html[cover_end_pos] != '\''; cover_end_pos++);
	std::cout << "Successfully fetched track's cover image." << std::endl;
	return (html.substr(cover_start_pos, cover_end_pos - cover_start_pos));
}

CURLClient::CURLClient(const char* vk_page)
{
	this->vk_page = vk_page;
	this->curl = curl_easy_init();
	this->writeFunc = curl_write;
}