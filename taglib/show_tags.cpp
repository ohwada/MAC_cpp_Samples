/**
 * taglib Sample
 * 2020-03-01 K.OHWADA
 */

// show id3 tags
// reference : https://taglib.org/api/

#include <taglib/taglib.h>
#include <taglib/fileref.h>


#include <string>
#include <iostream>

using namespace std;


/**
 * main
 */
int main(int argc, char** argv)
{

    if (argc != 2){
        cout << "Usage: " << argv[0] << " <mp3File> "  << endl;
        return EXIT_FAILURE;
    }

    char *filepath = argv[1];

   TagLib::FileRef f( filepath);

   TagLib::Tag *tag = f.tag();

   TagLib::String tag_title = tag->title();

   string str_title = (char*)tag_title.toCString(true);

   TagLib::String tag_artist = tag->artist();

    string str_artist = (char*)tag_artist.toCString(true);

   TagLib::String album = tag->album();
   TagLib::String genre = tag->genre();
   TagLib::String comment = tag->comment();
    int year = tag->year();
    int track = tag->track();

    cout << "Title: " << str_title << endl;
    cout << "Artist: " << str_artist << endl;
    cout << "Album: " << album << endl;
    cout << "Genre: " << genre << endl;
    cout << "Year: " << year << endl;
    cout << "Comment: " << comment << endl;

    return EXIT_SUCCESS;
}

