#include <fstream>
#include <curlcpp/curl_easy.h>

void url_download(std::string url, std::string tmpfile, std::basic_fstream<char, std::char_traits<char> >& file)
{
    file.open(tmpfile);
    // Create a curl_ios object to handle the stream
    curl::curl_ios<ostream> curl(file);
    // Pass it to the easy constructor and watch the content returned in that file!
    curl::curl_easy easy(curl);

    easy.add<CURLOPT_URL>(url.c_str());
    easy.add<CURLOPT_FOLLOWLOCATION>(1L);

    try {
        easy.perform();
    }
    catch (curl_easy_exception error) {
        error.print_traceback();
    }

    file.close();
}

void pic_download(std::string url, std::string imgname, std::basic_ofstream<char, std::char_traits<char> >& image)
{
    image.open(imgname);
    // Create a curl_ios object to handle the stream
    curl::curl_ios<ostream> pic(image);
    // Pass it to the easy constructor and watch the content returned in that file!
    curl::curl_easy draw(pic);

    draw.add<CURLOPT_URL>(url.c_str());
    draw.add<CURLOPT_FOLLOWLOCATION>(1L);
    draw.add<CURLOPT_NOPROGRESS>(0L);

    try {
        draw.perform();
    }
    catch (curl_easy_exception error) {
        error.print_traceback();
    }

    image.close();
}
