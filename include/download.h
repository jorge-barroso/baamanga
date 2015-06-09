#ifndef DOWNLOAD_H_INCLUDED
#define DOWNLOAD_H_INCLUDED

void url_download(std::string, std::string,  std::basic_fstream<char, std::char_traits<char> >&);
void pic_download(std::string, std::string, std::basic_ofstream<char, std::char_traits<char> >&);

#endif // DOWNLOAD_H_INCLUDED
