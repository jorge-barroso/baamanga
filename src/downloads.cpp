#include <fstream>
#include <curlcpp/curl_easy.h>

void url_download(std::string url, std::string tmpfile, std::basic_fstream<char, std::char_traits<char> >& file)
{
curl_writer writer(file);
curl::curl_easy curl(writer);

        file.open(tmpfile, std::fstream::out);
		curl.add(curl_pair<CURLoption,std::string>(CURLOPT_URL, url));
		curl.add(curl_pair<CURLoption,long>(CURLOPT_FOLLOWLOCATION,1L));

        try {
            curl.perform();
        }
        catch (curl_easy_exception error) {
            error.print_traceback();
        }
        file.close();
}

void pic_download(std::string url, std::string imgname, std::basic_ofstream<char, std::char_traits<char> >& image)
{
curl_writer draw(image);
curl::curl_easy pic(draw);

        image.open(imgname);
		pic.add(curl_pair<CURLoption, std::string>(CURLOPT_URL, url));
		pic.add(curl_pair<CURLoption, long>(CURLOPT_FOLLOWLOCATION,1L));
		pic.add(curl_pair<CURLoption, long>(CURLOPT_NOPROGRESS, 0L));

        try {
            pic.perform();
        }
        catch (curl_easy_exception error) {
            error.print_traceback();
        }

        image.close();
}
